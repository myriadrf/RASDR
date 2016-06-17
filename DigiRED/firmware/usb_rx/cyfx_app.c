/*
 ## Cypress USB 3.0 Platform source file (cyfxslfifosync.c)
 ## ===========================
 ##
 ##  Copyright Cypress Semiconductor Corporation, 2010-2014,
 ##  All Rights Reserved
 ##
 ##  Use of this file is governed
 ##  by the license agreement included in the file
 ##
 ##     <install>/license/license.txt
 ##
 ##  where <install> is the Cypress software
 ##  installation root directory path.
 ##
 ##  Published with permission, Case #2427983098, Cypress Semiconductor Corp.
 ##
 ##  This source code is derived from the Cypress EZ-USB SDK Example:
 ##  'Slave FIFO Synchronous Mode'.  As per clause 1.1 of the above license,
 ##  it is a derivative work of The Society of Amateur Radio Astronomers,
 ##  who retain copyright, all rights reserved.  The modifications to the
 ##  example that are made by the Society of Amateur Radio Astronomers, are
 ##  in turn made available to you under the GNU Public License, Version 2.
 ##
 ##  You should have received a copy of the GNU General Public License
 ##  along with this source code; see the file COPYING.  If not, write to
 ##  the Free Software Foundation, Inc., 51 Franklin Street,
 ##  Boston, MA 02110-1301, USA.
 ##  
 ##  This entire code is distributed in the hope that it will be useful but
 ##  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 ##  DISCLAIMED. This includes but is not limited to warranties of
 ##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ##
 ## ===========================
*/

/* This file illustrates the Slave FIFO Synchronous mode example */

/*
   This interface comprises of two USB bulk endpoints. A bulk OUT endpoint
   acts as the producer of data from the host. A bulk IN endpoint acts as
   the consumer of data to the host. Appropriate vendor class USB enumeration
   descriptors with these two bulk endpoints are implemented.

   The GPIF configuration data for the Synchronous Slave FIFO operation is loaded onto
   the appropriate GPIF registers. The p-port data transfers are done via the producer
   p-port socket and the consumer p-port socket.

   This application implements two DMA Channels in MANUAL mode one for P to U data transfer
   and one for U to P data transfer.

   The U to P DMA channel connects the USB producer (OUT) endpoint to the CPU
   socket. The P to U DMA channel connects the producer p-port socket to the USB 
   consumer (IN) endpoint.

   CPU is signaled of the data reception using DMA callbacks. The CPU
   discards this buffer. This leads to the sink mechanism. A callback is raised whenever
   a buffer is available on the producer p-port socket.  The CPU commits this to 
   the DMA data transfer to the consumer endpoint which then gets transferred to the host.

   Upon every reception of data in the DMA buffer from the host or from the p-port, the
   CPU is signalled using DMA callbacks. There are two DMA callback functions implemented
   each for U to P and P to U data paths. The CPU then commits the DMA buffer received so
   that the data is transferred to the consumer.

   The DMA buffer size for each channel is defined based on the USB speed. 64
   for full speed, 512 for high speed and 1K for super speed. The number of
   DMA buffers is defined by CY_FX_DMA_BUF_COUNT.

   The firmware implements vendor commands 0xC0 and 0xC1 on control EP0
   to perform programmed I/O read or write firmware operations, respectively.
   All firmware transactions are performed as a sequence of 0xC1 (WRITE, CMD)
   followed by a 0xC0 (READ STATUS).  The 0xC0 allows the host to obtain the
   result of the 0xC1 command or the data requested by it.  Refer to the
   RASDR API document for details on the available functions and return codes.
  */

#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyfx_app.h"
#include "cyu3usb.h"
#include "cyu3uart.h"
#include "cyu3gpif.h"
#include "cyu3pib.h"
#include "pib_regs.h"

#include "cyu3gpio.h"
#include "cyu3i2c.h"
#include "cyu3spi.h"
#include "cyu3utils.h"

#include "cyfxgpif2config.h"

//serial interfaces bitrates
#define I2C_BITRATE        (400000)
#define SPI_BITRATE        (1000000)

//SPI SSNs
#define GPIO_SPI_SSN	49
#define GPIO_SBEN		27

//SPI wordlen
#define LMS6_WORDLEN	8    // LMS6002D(?)
#define LMS7_WORDLEN	16   // LMS7002M(?)
#define ADF_WORDLEN		24

//TX chip ID pin
#define GPIO_TX_ID		23

//LMS control pins
#define GPIO_LNA0		40
#define GPIO_LNA1		41
#define GPIO_PA0		42
#define GPIO_RESET		43

#define GPIO_LED1		46
#define GPIO_LED2		47
#define GPIO_LED3		48

#define LED_ON          CyTrue      // depends on HW circuit design
#define LED_OFF         CyFalse     // depends on HW circuit design

//X3 Connector Pins
#define GPIO_X33		25  // X3.3
#define GPIO_X35		26  // X3.5
#define GPIO_X37		44  // X3.7
#define GPIO_X39		45  // X3.9

//gpif interface control signals - not used
#define GPIO_SLCS		33
#define GPIO_SLWR		34
#define GPIO_SLOE		35
#define GPIO_SLRD		36
#define GPIO_PKTEND		37
#define GPIO_A0			38
#define GPIO_A1			39

//USB control endpoint commands
#define CFG_ADDR			0xAA
#define SC18IS602_ADDR		0x28

#define CMD_CFG_I2C_WR		0x14
#define CMD_CFG_I2C_RD		0x15

#define CMD_SET_LNA			0x30
#define CMD_SET_PA			0x31

#define CMD_GPIO_RD         0x19
#define CMD_GPIO_WR			0x20

//LMS6002D
#define CMD_LMS_RESET		0x10
#define CMD_LMS_WR			0x16
#define CMD_LMS_RD			0x17

//FX2 Configuration
#define CMD_FX2				0x40
#define CMD_GET_INFO		0x50
#define CMD_ADF_WR			0xAD

CyU3PThread     AppThread;	             /* Application thread structure */
//CyU3PDmaChannel glChHandleUtoP;          /* DMA Channel handle for USB->FX3 transfer. */
CyU3PDmaMultiChannel glChHandlePtoU;     /* DMA Channel handle for FX3->USB transfer. */

volatile uint32_t glDMARxCount = 0;      /* Counter to track the number of buffers received from USB. */
volatile uint32_t glDMATxCount = 0;      /* Counter to track the number of buffers sent to USB. */
CyBool_t glIsApplnActive    = CyFalse;   /* Whether the application is active or not. */
CyBool_t glIsApplnFaulted    = CyFalse;  /* Whether the application is faulted or not. */


uint8_t glEp0Buffer_Rx[64] __attribute__ ((aligned (32)));
uint8_t glEp0Buffer_Tx[64] __attribute__ ((aligned (32)));
int glEp0Buffer_Tx_Expected = 0;

volatile uint8_t config_led = 0;
uint16_t on_time = 0, off_time = 0;
CyBool_t tx_id;

//extern CyU3PReturnStatus_t CyU3PUsbSetTxSwing(uint32_t swing);

void
CyFxPtoUDmaAcctCallback(
        CyU3PDmaMultiChannel *multiChHandle,
        CyU3PDmaCbType_t      type,
        CyU3PDmaCBInput_t    *input
        )
{
	CyU3PGpioSetValue(GPIO_LED3, LED_ON);
    //glDMATxCount += 2;
}

#define ERR_DIGIT_ON	100
#define ERR_DIGIT_OFF	400
#define ERR_DIGIT_SPACE	250
#define ERR_DIGIT_END   750

/* Application Error Handler */
void
CyFxAppErrorHandler(
        CyU3PReturnStatus_t apiRetStatus,    /* API return status */
        int code
        )
{
    /* Application failed with the error code apiRetStatus */
    //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyFxAppErrorHandler, Error code = %d\n", apiRetStatus);
	glIsApplnFaulted = CyTrue;

    /* Add custom debug or recovery actions here */
	if( code > 99 ) code = 99;

    /* Loop Indefinitely */
    for (;;)
    {
    	int digit1 = code / 10;
    	int digit0 = code % 10;
    	int cc;

    	// marker:
		CyU3PGpioSetValue(GPIO_LED3, LED_ON);
    	CyU3PThreadSleep(ERR_DIGIT_SPACE);
		CyU3PGpioSetValue(GPIO_LED2, LED_ON);
    	CyU3PThreadSleep(ERR_DIGIT_SPACE);
		CyU3PGpioSetValue(GPIO_LED1, LED_ON);
    	CyU3PThreadSleep(ERR_DIGIT_SPACE);
		CyU3PGpioSetValue(GPIO_LED3, LED_OFF);
		CyU3PGpioSetValue(GPIO_LED2, LED_OFF);
		CyU3PGpioSetValue(GPIO_LED1, LED_OFF);
    	CyU3PThreadSleep(ERR_DIGIT_SPACE);

    	// digit1:
    	for(cc=0;cc<digit1;cc++) {
    		CyU3PGpioSetValue(GPIO_LED3, LED_ON);
    		CyU3PGpioSetValue(GPIO_LED2, LED_ON);
    		CyU3PGpioSetValue(GPIO_LED1, LED_ON);
    		CyU3PThreadSleep(ERR_DIGIT_ON);
    		CyU3PGpioSetValue(GPIO_LED3, LED_OFF);
    		CyU3PGpioSetValue(GPIO_LED2, LED_OFF);
    		CyU3PGpioSetValue(GPIO_LED1, LED_OFF);
    		CyU3PThreadSleep(ERR_DIGIT_OFF);
    	}
    	for( ;cc<10;cc++) CyU3PThreadSleep(ERR_DIGIT_ON+ERR_DIGIT_OFF);

    	// space between digit1 and digit0:
    	CyU3PThreadSleep(ERR_DIGIT_SPACE);

    	// digit0:
    	for(cc=0;cc<digit0;cc++) {
    		CyU3PGpioSetValue(GPIO_LED3, LED_ON);
    		CyU3PGpioSetValue(GPIO_LED2, LED_ON);
    		CyU3PGpioSetValue(GPIO_LED1, LED_ON);
    		CyU3PThreadSleep(ERR_DIGIT_ON);
    		CyU3PGpioSetValue(GPIO_LED3, LED_OFF);
    		CyU3PGpioSetValue(GPIO_LED2, LED_OFF);
    		CyU3PGpioSetValue(GPIO_LED1, LED_OFF);
    		CyU3PThreadSleep(ERR_DIGIT_OFF);
    	}
    	for( ;cc<10;cc++) CyU3PThreadSleep(ERR_DIGIT_ON+ERR_DIGIT_OFF);

    	// space after digit0:
    	CyU3PThreadSleep(ERR_DIGIT_END);
    }
}

/* SPI initialization for application. */
CyU3PReturnStatus_t
CyFxSpiInit(uint8_t wordLen)
{
    CyU3PSpiConfig_t spiConfig;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Start the SPI module and configure the master. */
    status = CyU3PSpiInit();
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Start the SPI master block. Run the SPI clock at 8MHz
     * and configure the word length to 8 bits. Also configure
     * the slave select using FW. */
    CyU3PMemSet((uint8_t *)&spiConfig, 0, sizeof(spiConfig));
    spiConfig.isLsbFirst = CyFalse;
    spiConfig.cpol       = CyFalse;
    spiConfig.ssnPol     = CyFalse;
    spiConfig.cpha       = CyFalse;
    spiConfig.leadTime   = CY_U3P_SPI_SSN_LAG_LEAD_HALF_CLK;
    spiConfig.lagTime    = CY_U3P_SPI_SSN_LAG_LEAD_HALF_CLK;
    spiConfig.ssnCtrl    = CY_U3P_SPI_SSN_CTRL_NONE;
    spiConfig.clock      = SPI_BITRATE;
    spiConfig.wordLen    = wordLen;

    status = CyU3PSpiSetConfig(&spiConfig, NULL);

    return status;
}

/* I2c initialization for EEPROM programming. */
CyU3PReturnStatus_t
CyFxI2cInit()
    {
    CyU3PI2cConfig_t i2cConfig;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Initialize and configure the I2C master module. */
    status = CyU3PI2cInit();
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Start the I2C master block. The bit rate is set at 100KHz.
     * The data transfer is done via DMA. */
    CyU3PMemSet((uint8_t *)&i2cConfig, 0, sizeof(i2cConfig));
    i2cConfig.bitRate    = I2C_BITRATE;
    i2cConfig.busTimeout = 0xFFFFFFFF;
    i2cConfig.dmaTimeout = 0xFFFF;
    i2cConfig.isDma      = CyFalse;

    status = CyU3PI2cSetConfig(&i2cConfig, NULL);
    return status;
}

/* This function starts the application. This is called
 * when a SET_CONF event is received from the USB host. The endpoints
 * are configured and the DMA pipe is setup in this function. */
void
CyFxApplnStart(void)
{
    uint16_t size = 0;
    uint8_t burstLength = 1;
    CyU3PEpConfig_t epCfg;
    CyU3PDmaMultiChannelConfig_t dmaMultiConfig;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    CyU3PUSBSpeed_t usbSpeed = CyU3PUsbGetSpeed();

    /* First identify the usb speed. Once that is identified,
     * create a DMA channel and start the transfer on this. */

    /* Based on the Bus Speed configure the endpoint packet size */
    switch (usbSpeed)
    {
    case CY_U3P_FULL_SPEED:
        size = CY_FX_FULL_SPEED_EP_SIZE;							/* If connected to full speed, the endpoint size should be 64 bytes */
        on_time  = FULLSPEED_BLINK_ON_TIME;
        off_time = XSPEED_BLINK_PERIOD-FULLSPEED_BLINK_ON_TIME;
        break;

    case CY_U3P_HIGH_SPEED:
        size = CY_FX_HIGH_SPEED_EP_SIZE;							/* If connected to high speed, the endpoint size should be 512 bytes */
        on_time  = HIGHSPEED_BLINK_ON_TIME;
        off_time = XSPEED_BLINK_PERIOD-HIGHSPEED_BLINK_ON_TIME;
        break;

    case  CY_U3P_SUPER_SPEED:
        size = CY_FX_SUPER_SPEED_EP_SIZE;						/* If connected to Super-speed, the endpoint size should be 1024 bytes */
        burstLength = CY_FX_EP_BURST_LENGTH;
        on_time  = SUPERSPEED_BLINK_ON_TIME;
        off_time = XSPEED_BLINK_PERIOD-SUPERSPEED_BLINK_ON_TIME;
        break;

    default:
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "Error! Invalid USB speed.\n");
        CyFxAppErrorHandler(CY_U3P_ERROR_FAILURE, 1);
        break;
    }

    CyU3PMemSet((uint8_t *)&epCfg, 0, sizeof (epCfg));
    epCfg.enable = CyTrue;
    epCfg.epType = CY_U3P_USB_EP_BULK;
    epCfg.burstLen = burstLength;
    epCfg.streams = 0;
    epCfg.pcktSize = size;

    /* Producer endpoint configuration */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_PRODUCER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,2);
    }

    /* Consumer endpoint configuration */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_CONSUMER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,3);
    }

	/* Create a AUTO_MANY_TO_ONE channel for the consumer USB socket. */
	CyU3PMemSet ((uint8_t *)&dmaMultiConfig, 0, sizeof (dmaMultiConfig));
	/* The buffer size will be same as packet size for the
	 * full speed, high speed and super speed non-burst modes.
	 * For super speed burst mode of operation, the buffers will be
	 * 1024 * burst length so that a full burst can be completed.
	 * This will mean that a buffer will be available only after it
	 * has been filled or when a short packet is received. */
    dmaMultiConfig.size           = 4*1024;
    dmaMultiConfig.count          = 4;
    dmaMultiConfig.validSckCount  = 2;
    dmaMultiConfig.prodSckId[0]   = (CyU3PDmaSocketId_t)CY_U3P_PIB_SOCKET_0;
    dmaMultiConfig.prodSckId[1]   = (CyU3PDmaSocketId_t)CY_U3P_PIB_SOCKET_1;
    dmaMultiConfig.consSckId[0]   = CY_FX_EP_CONSUMER_SOCKET;
    // NB: zeroed by memset above
    //dmaMultiConfig.prodAvailCount = 0;
    //dmaMultiConfig.prodHeader     = 0;
    //dmaMultiConfig.prodFooter     = 0;
    //dmaMultiConfig.consHeader     = 0;
    dmaMultiConfig.dmaMode        = CY_U3P_DMA_MODE_BYTE;
    dmaMultiConfig.notification   = 0xFF;
    dmaMultiConfig.cb             = CyFxPtoUDmaAcctCallback;

    apiRetStatus = CyU3PDmaMultiChannelCreate(&glChHandlePtoU, CY_U3P_DMA_TYPE_AUTO_MANY_TO_ONE,
            &dmaMultiConfig);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaMultiChannelCreate Failed, Error Code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,4);
    }

    CyU3PUsbFlushEp(CY_FX_EP_CONSUMER);
	CyU3PUsbFlushEp(CY_FX_EP_PRODUCER);

	apiRetStatus = CyU3PDmaMultiChannelSetXfer(&glChHandlePtoU, 0, 0);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaMultiChannelSetXfer failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,4);
    }

    /* Update the flag so that the application thread is notified of this. */
    glIsApplnActive = CyTrue;
}

/* This function stops the application. This shall be called whenever a RESET
 * or DISCONNECT event is received from the USB host. The endpoints are
 * disabled and the DMA pipe is destroyed by this function. */
void
CyFxApplnStop(
        void)
{
    CyU3PEpConfig_t epCfg;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Update the flag so that the application thread is notified of this. */
    glIsApplnActive = CyFalse;

    /* Destroy the channels */
    //CyU3PDmaChannelDestroy(&glChHandleUtoP);
    CyU3PDmaMultiChannelDestroy(&glChHandlePtoU);

    /* Flush the endpoint memory */
    CyU3PUsbFlushEp(CY_FX_EP_PRODUCER);
    CyU3PUsbFlushEp(CY_FX_EP_CONSUMER);

    /* Disable endpoints */
    CyU3PMemSet((uint8_t *)&epCfg, 0, sizeof (epCfg));
    epCfg.enable = CyFalse;

    /* Producer endpoint configuration. */
    //apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_PRODUCER, &epCfg);
    //if (apiRetStatus != CY_U3P_SUCCESS)
    //{
    //    //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
    //    CyFxAppErrorHandler(apiRetStatus,5);
    //}

    /* Consumer endpoint configuration. */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_CONSUMER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,6);
    }
}

/* Callback to handle the USB vendor requests */
CyBool_t
CyFxApplnUSBVendorCB (
        uint32_t setupdat0,
        uint32_t setupdat1
    )
{
    uint8_t  bRequest;  //, bReqType;
    CyBool_t isHandled = CyFalse;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint8_t   I2C_Addr;
	CyU3PI2cPreamble_t preamble;
    uint8_t   gpio_num;
    uint8_t  *serial_num;
    CyBool_t  tx_id;
    uint16_t  i;

    /* Decode the fields from the setup request. */
    bRequest = ((setupdat0 & CY_U3P_USB_REQUEST_MASK) >> CY_U3P_USB_REQUEST_POS);

    isHandled = CyTrue;
    switch (bRequest)
    {
    case 0xC0: //read

	    if( glEp0Buffer_Tx_Expected == 0 )
	    {
	    	// a previous command that filled the buffer did
	    	// not actually fill the buffer.  Consider this
	    	// a software fault and halt further processing to
	    	// help diagnose HOST software issues.
	    	CyFxAppErrorHandler(CY_U3P_ERROR_INVALID_SEQUENCE,60);
	    }
	    glEp0Buffer_Tx_Expected = 0;

    	CyU3PGpioSetValue(GPIO_LED3, LED_ON);
    	config_led = 1;
    	CyU3PUsbSendEP0Data (64, glEp0Buffer_Tx);

    	break;

    case 0xC1: //write

    	CyU3PGpioSetValue(GPIO_LED3, LED_ON);
    	config_led = 2;
    	CyU3PUsbGetEP0Data (64, glEp0Buffer_Rx, NULL);

	    if( glEp0Buffer_Tx_Expected != 0 )
	    {
	    	// a previous command that filled the buffer did
	    	// not actually readback the buffer.  Consider this
	    	// a software fault and halt further processing to
	    	// help diagnose HOST software issues.  The value
	    	// will indicate the command code that did not complete
	    	CyFxAppErrorHandler(CY_U3P_ERROR_INVALID_SEQUENCE,glEp0Buffer_Tx_Expected);
	    }

    	switch(glEp0Buffer_Rx[0]) //which command to execute
    	{
    	case CMD_FX2:
    			//Command format:
    			//src[0] : Op code i.e. Command to the FX2 microcontroller
    			//src[1] : Command code: 0x10 - Reset EP6
    			//src[2] : reserved
    			//src[3] : reserved
    			// Data block:
    			// src[4] : register address
    			// ...

    		    glEp0Buffer_Tx_Expected = 53;

    		break;

		case CMD_CFG_I2C_RD:
    			//Command format:
    			//src[0] : Op code i.e. read from the FPGA Configuration via I2C
    			//src[1] : I2C address
    			//src[2] : Data blocks in buffer
    			//src[3] : reserved
    			// Data block:
    			// src[4] : register address
    			// ...

    		  	glEp0Buffer_Tx_Expected = 50;

    		  	I2C_Addr = glEp0Buffer_Rx[1];
    			for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
    		        //read byte
    		        preamble.length    = 3;

    		        I2C_Addr &= ~(1 << 0);//write addr
    		        preamble.buffer[0] = I2C_Addr;//0xE0; //write h70;

    		        preamble.buffer[1] = glEp0Buffer_Rx[4+i]; //reg to read

    		        I2C_Addr |= 1 << 0;	//read addr

    		        preamble.buffer[2] = I2C_Addr;//0xE1; //read h70
    		        preamble.ctrlMask  = 0x0002;

    		        CyU3PI2cReceiveBytes(&preamble, &glEp0Buffer_Tx[i], 1, 0);

    			};

    		break;

    	  case CMD_CFG_I2C_WR:
    			//Command format:
    			//src[0] : Op code i.e. write to the FPGA Configuration via I2C
    			//src[1] : I2C address
    			//src[2] : Data blocks in buffer
    			//src[3] : reserved
    			// Data block:
    			// src[4] : register address
    			// src[5] : data to write
    			// ...

    		    glEp0Buffer_Tx_Expected = 54;

    		  	I2C_Addr = glEp0Buffer_Rx[1];
    			for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
        			//write byte
        	        preamble.length    = 2;
        	        preamble.buffer[0] = 0xE0; //write h70;
        	        preamble.buffer[1] = glEp0Buffer_Rx[4+i*2]; //reg to write
        	        preamble.ctrlMask  = 0x0000;

        	        CyU3PI2cTransmitBytes(&preamble, &glEp0Buffer_Rx[5+i*2], 1, 0);
    			};

    		break;

    	  case CMD_SET_LNA:
    			//Command format:
    			//src[0] : Op code i.e. set LNA
    			//src[1] : reserved
    			//src[2] : Data blocks in buffer
    			//src[3] : reserved
    			// Data block:
    			// src[4] : new LNA value
    			// ...

    		    glEp0Buffer_Tx_Expected = 55;

    			for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
    				if(glEp0Buffer_Rx[4+i] & 0x01) CyU3PGpioSetValue(GPIO_LNA0, CyTrue); else CyU3PGpioSetValue(GPIO_LNA0, CyFalse); //LNA0
    				if(glEp0Buffer_Rx[4+i] & 0x02) CyU3PGpioSetValue(GPIO_LNA1, CyTrue); else CyU3PGpioSetValue(GPIO_LNA1, CyFalse); //LNA1
    			};

    		break;

    	  case CMD_SET_PA:
    			//Command format:
    			//src[0] : Op code i.e. set PA
    			//src[1] : reserved
    			//src[2] : Data blocks in buffer
    			//src[3] : reserved
    			// Data block:
    			// src[4] : new PA value
    			// ...

  		        glEp0Buffer_Tx_Expected = 56;

    			for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
    				if(glEp0Buffer_Rx[4+i] & 0x01) CyU3PGpioSetValue(GPIO_PA0, CyTrue); else CyU3PGpioSetValue(GPIO_PA0, CyFalse); //PA0
    			};

    		break;

    	  case CMD_LMS_RESET:
    			//Command format:
    			//src[0] : Op code i.e. set reset pin level
    			//src[1] : reserved - FPGA Configuration I2C address
    			//src[2] : Data blocks in buffer
    			//src[3] : reserved
    			// Data block:
    			// src[4] : new reset pin level: 0 - low, 1 - high
    			// ...

		        glEp0Buffer_Tx_Expected = 57;

		        for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
    				//change reset pin level

    				if(glEp0Buffer_Rx[4+i]) CyU3PGpioSetValue(GPIO_RESET, CyTrue); //Reset high
    					else CyU3PGpioSetValue(GPIO_RESET, CyFalse); //Reset low
    			};

    		break;

    	  case CMD_LMS_RD:
    			//Command format:
    			//src[0] : Op code i.e. read from the LMS6002D Configuration via I2C/SPI
    			//src[1] : reserved - FPGA Configuration I2C address
    			//src[2] : Data blocks in buffer
    			//src[3] : reserved
    			// Data block:
    			// src[4] : SPI Instruction (W/R + module addr + register address )
    			// ...

		        glEp0Buffer_Tx_Expected = 51;

  		        CyU3PGpioSetValue(GPIO_SPI_SSN, CyFalse);

    			for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
        		  	CyU3PSpiTransmitWords(&glEp0Buffer_Rx[4+i], 1);//read reg addr
        		  	CyU3PSpiReceiveWords(&glEp0Buffer_Tx[i], 1);//data
    			};

    			CyU3PGpioSetValue(GPIO_SPI_SSN, CyTrue);

    		break;

    	  case CMD_LMS_WR:
    			//Command format:
    			//src[0] : Op code i.e. read from the LMS6002D Configuration via I2C/SPI
    			//src[1] : reserved - FPGA Configuration I2C address
    			//src[2] : Data blocks in buffer
    			//src[3] : reserved
    			// Data block:
    			// src[4] : SPI Instruction (W/R + module addr + register address )
    			// src[5] : SPI Data
    			// ...

	            glEp0Buffer_Tx_Expected = 58;

    		  	CyU3PGpioSetValue(GPIO_SPI_SSN, CyFalse);

				for(i=0; i<glEp0Buffer_Rx[2]; i++)
				{

				  CyU3PSpiTransmitWords(&glEp0Buffer_Rx[4+2*i], glEp0Buffer_Rx[2]*2);//reg + data
				};
    		  	//CyU3PSpiTransmitWords(&glEp0Buffer_Rx[4], glEp0Buffer_Rx[2]*2);//data
    		  	CyU3PGpioSetValue(GPIO_SPI_SSN, CyTrue);
    		break;

    	  case	CMD_GET_INFO:

	          glEp0Buffer_Tx_Expected = 52;

    		  serial_num = (uint8_t *)CyFxUSBSerialDscr;

    		  CyU3PGpioGetValue (GPIO_TX_ID, &tx_id);
    		  glEp0Buffer_Tx[0] = tx_id;
    		  CyU3PGpifGetSMState(&glEp0Buffer_Tx[1]);
    		  for(i=0,serial_num = (uint8_t *)CyFxUSBSerialDscr;i<8;i++)
    		  {
    			  glEp0Buffer_Tx[i+2] = serial_num[(i*2)+2];
    		  }
    		  CyU3PMemSet ((uint8_t *)&glEp0Buffer_Tx[10], 0, 6);	// [10-15] reserved
    		  CyU3PMemCopy((uint8_t *)&glEp0Buffer_Tx[16], (uint8_t *)&glDMARxCount, sizeof (uint32_t));
    		  CyU3PMemSet ((uint8_t *)&glEp0Buffer_Tx[20], 0, 4);	// [20-23] reserved
    		  CyU3PMemCopy((uint8_t *)&glEp0Buffer_Tx[24], (uint8_t *)&glDMATxCount, sizeof (uint32_t));
    		  glEp0Buffer_Tx[29] = 0x0E;	// END-of-buffer mark
    		  glEp0Buffer_Tx[30] = 0x0F;	// "

    		  break;

    	  case CMD_ADF_WR:
    		  	//Command format:
				//src[0] : Op code i.e. Write Data to ADF4002 chip (0xAD)
				//src[1] : reserved - FPGA Configuration I2C address   /ignored???????
				//src[2] : Data blocks in buffer
				//src[3] : reserved
				// Data block:
				// src[4] : data_h
				// src[5] : data
				// src[6] : data_l
				// ...

	            glEp0Buffer_Tx_Expected = 59;

    			for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
					CyU3PGpioSetValue(GPIO_SBEN, CyFalse);
					CyU3PSpiTransmitWords(&glEp0Buffer_Rx[4]+i*(ADF_WORDLEN/8), (ADF_WORDLEN/8));//data
					CyU3PGpioSetValue(GPIO_SBEN, CyTrue);
    			}

    		  break;

    	  case CMD_GPIO_RD:
    			//Command format:
    			//src[0] : Op code i.e. Command to read GPIO
    			//src[1] : GPIO pin number to read
    			//src[2] : reserved
    			//src[3] : reserved
    			// Data block:
    			//src[4] : reserved
    			//...

	            glEp0Buffer_Tx_Expected = 60;

                glEp0Buffer_Tx[0] = -1;
                     if( glEp0Buffer_Rx[1] == 1) gpio_num = GPIO_X33;
                else if( glEp0Buffer_Rx[1] == 2) gpio_num = GPIO_X35;
                else if( glEp0Buffer_Rx[1] == 3) gpio_num = GPIO_X37;
                else if( glEp0Buffer_Rx[1] == 4) gpio_num = GPIO_X39;
                else break;
                {
                    CyU3PGpioSimpleConfig_t gpioConfig;
                    //CyU3PReturnStatus_t status;
                    CyBool_t pin;

                    gpioConfig.outValue = CyFalse;
                    gpioConfig.inputEn = CyTrue;
                    gpioConfig.driveLowEn = CyFalse;
                    gpioConfig.driveHighEn = CyFalse;
                    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
                    status = CyU3PDeviceGpioOverride(gpio_num, CyTrue);
                    status = CyU3PGpioSetSimpleConfig(gpio_num, &gpioConfig);
     		        CyU3PGpioGetValue(gpio_num, &pin);
                    if(pin) glEp0Buffer_Tx[0] = 1;
                    else    glEp0Buffer_Tx[0] = 0;
                }

    		  break;

    	  case CMD_GPIO_WR:
    			//Command format:
    			//src[0] : Op code i.e. Command to read GPIO
    			//src[1] : GPIO pin number to write
    			//src[2] : reserved
    			//src[3] : reserved
    			// Data block:
    			//src[4] : value to set.  0=off, 1=on
    			//...

	            glEp0Buffer_Tx_Expected = 61;

                glEp0Buffer_Tx[0] = -1;
                     if( glEp0Buffer_Rx[1] == 1) gpio_num = GPIO_X33;
                else if( glEp0Buffer_Rx[1] == 2) gpio_num = GPIO_X35;
                else if( glEp0Buffer_Rx[1] == 3) gpio_num = GPIO_X37;
                else if( glEp0Buffer_Rx[1] == 4) gpio_num = GPIO_X39;
                else break;
                {
                    CyU3PGpioSimpleConfig_t gpioConfig;
                    //CyU3PReturnStatus_t status;
                    CyBool_t pin = glEp0Buffer_Rx[4] ? CyTrue : CyFalse;

                    gpioConfig.outValue = pin;
                    gpioConfig.inputEn = CyFalse;
                    gpioConfig.driveLowEn = CyTrue;
                    gpioConfig.driveHighEn = CyTrue;
                    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
                    status = CyU3PDeviceGpioOverride(gpio_num, CyTrue);
                    status = CyU3PGpioSetSimpleConfig(gpio_num, &gpioConfig);
     		        CyU3PGpioSetValue(gpio_num, pin);
                    if(pin) glEp0Buffer_Tx[0] = 1;
                    else    glEp0Buffer_Tx[0] = 0;
                }

    		  break;
    	}
    	break;

        default:
            /* This is unknown request. */
            isHandled = CyFalse;
            break;
    }

    /* If there was any error, return not handled so that the library will
     * stall the request. Alternatively EP0 can be stalled here and return
     * CyTrue. */
    if (status != CY_U3P_SUCCESS)
    {
        isHandled = CyFalse;
    }
    return isHandled;
}

/* Callback to handle the USB setup requests. */
CyBool_t
CyFxApplnUSBSetupCB (
        uint32_t setupdat0,
        uint32_t setupdat1
    )
{
    /* Fast enumeration is used. Only requests addressed to the interface, class,
     * vendor and unknown control requests are received by this function.
     * This application does not support any class or vendor requests. */

    uint8_t  bRequest, bReqType;
    uint8_t  bType, bTarget;
    uint16_t wValue, wIndex;
    CyBool_t isHandled = CyFalse;

    /* Decode the fields from the setup request. */
    bReqType = (setupdat0 & CY_U3P_USB_REQUEST_TYPE_MASK);
    bType    = (bReqType & CY_U3P_USB_TYPE_MASK);
    bTarget  = (bReqType & CY_U3P_USB_TARGET_MASK);
    bRequest = ((setupdat0 & CY_U3P_USB_REQUEST_MASK) >> CY_U3P_USB_REQUEST_POS);
    wValue   = ((setupdat0 & CY_U3P_USB_VALUE_MASK)   >> CY_U3P_USB_VALUE_POS);
    wIndex   = ((setupdat1 & CY_U3P_USB_INDEX_MASK)   >> CY_U3P_USB_INDEX_POS);

    if (bType == CY_U3P_USB_STANDARD_RQT)
    {
        /* Handle SET_FEATURE(FUNCTION_SUSPEND) and CLEAR_FEATURE(FUNCTION_SUSPEND)
         * requests here. It should be allowed to pass if the device is in configured
         * state and failed otherwise. */
        if ((bTarget == CY_U3P_USB_TARGET_INTF) && ((bRequest == CY_U3P_USB_SC_SET_FEATURE)
                    || (bRequest == CY_U3P_USB_SC_CLEAR_FEATURE)) && (wValue == 0))
        {
            if (glIsApplnActive)
            {
                CyU3PUsbAckSetup();
            }
            else
                CyU3PUsbStall(0, CyTrue, CyFalse);

            isHandled = CyTrue;
        }

        /* CLEAR_FEATURE request for endpoint is always passed to the setup callback
         * regardless of the enumeration model used. When a clear feature is received,
         * the previous transfer has to be flushed and cleaned up. This is done at the
         * protocol level. Since this is just a loopback operation, there is no higher
         * level protocol. So flush the EP memory and reset the DMA channel associated
         * with it. If there are more than one EP associated with the channel reset both
         * the EPs. The endpoint stall and toggle / sequence number is also expected to be
         * reset. Return CyFalse to make the library clear the stall and reset the endpoint
         * toggle. Or invoke the CyU3PUsbStall (ep, CyFalse, CyTrue) and return CyTrue.
         * Here we are clearing the stall. */
        if ((bTarget == CY_U3P_USB_TARGET_ENDPT) && (bRequest == CY_U3P_USB_SC_CLEAR_FEATURE)
                && (wValue == CY_U3P_USBX_FS_EP_HALT))
        {
            if (glIsApplnActive)
            {
                CyU3PUsbStall(wIndex, CyFalse, CyTrue);
                isHandled = CyTrue;
            }
        }
    }

    /* Handle supported vendor requests. */
    if ((bType == CY_U3P_USB_VENDOR_RQT) && (bTarget == CY_U3P_USB_TARGET_DEVICE))
    {
        isHandled = CyFxApplnUSBVendorCB( setupdat0, setupdat1 );
    }

    return isHandled;
}

/* This is the callback function to handle the USB events. */
void
CyFxApplnUSBEventCB (
    CyU3PUsbEventType_t evtype,
    uint16_t            evdata
    )
{
    switch (evtype)
    {
    case CY_U3P_USB_EVENT_CONNECT:
      //++num_connect;
      break;

    case CY_U3P_USB_EVENT_SETCONF:
        /* Stop the application before re-starting. */
        if (glIsApplnActive)
        {
            CyFxApplnStop();
        }
        // Cypress AN65974, pg. 58
        // NOTE: may cause USB compliance fail
        //CyU3PUsbLPMDisable();
        CyFxApplnStart();
        break;

    case CY_U3P_USB_EVENT_RESET:
    case CY_U3P_USB_EVENT_DISCONNECT:
        if (glIsApplnActive)
        {
            CyFxApplnStop();
        }
        break;

    default:
        break;
    }
}

/* Callback function to handle LPM requests from the USB 3.0 host. This function is invoked by the API
   whenever a state change from U0 -> U1 or U0 -> U2 happens. If we return CyTrue from this function, the
   FX3 device is retained in the low power state. If we return CyFalse, the FX3 device immediately tries
   to trigger an exit back to U0.

   This application does not have any state in which we should not allow U1/U2 transitions; and therefore
   the function always return CyTrue.
 */
CyBool_t
CyFxApplnLPMRqtCB (
        CyU3PUsbLinkPowerMode link_mode)
{
    return CyTrue;
}

/* This function initializes the USB Module, sets the enumeration descriptors.
 * This function does not start the bulk streaming and this is done only when
 * SET_CONF event is received. */
void
CyFxApplnInit(void)
{
    CyU3PPibClock_t pibClock;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    CyBool_t no_renum = CyFalse;

    /* Initialize the p-port block. */
    pibClock.clkDiv = 2;
    pibClock.clkSrc = CY_U3P_SYS_CLK;
    pibClock.isHalfDiv = CyFalse;
    /* Disable DLL for sync GPIF */
    pibClock.isDllEnable = CyFalse;
    apiRetStatus = CyU3PPibInit(CyTrue, &pibClock);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "P-port Initialization failed, Error Code = %d\n",apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,7);
    }

    /* Load the GPIF configuration for Slave FIFO sync mode. */
    apiRetStatus = CyU3PGpifLoad(&CyFxGpifConfig);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PGpifLoad failed, Error Code = %d\n",apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,8);
    }

    /* Start the state machine. */
    apiRetStatus = CyU3PGpifSMStart(START, ALPHA_START);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PGpifSMStart failed, Error Code = %d\n",apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,9);
    }

    /* Start the USB functionality. */
    apiRetStatus = CyU3PUsbStart();
    if (apiRetStatus == CY_U3P_ERROR_NO_REENUM_REQUIRED)
        no_renum = CyTrue;
    else if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PUsbStart failed to Start, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,20);
    }

    //CyU3PUsbSetTxSwing(127); //TX Amplitude swing of the electrical signalling on the USB superspeed lines in 10 mV units. Should be less than 1.28V.

    /* The fast enumeration is the easiest way to setup a USB connection,
     * where all enumeration phase is handled by the library. Only the
     * class / vendor requests need to be handled by the application. */
    CyU3PUsbRegisterSetupCallback(CyFxApplnUSBSetupCB, CyTrue);

    /* Setup the callback to handle the USB events. */
    CyU3PUsbRegisterEventCallback(CyFxApplnUSBEventCB);

    /* Register a callback to handle LPM requests from the USB 3.0 host. */
    //CyU3PUsbRegisterLPMRequestCallback(CyFxApplnLPMRqtCB);
	CyU3PUsbLPMDisable() ;//lpm disable

    /* Set the USB Enumeration descriptors */

    /* Super speed device descriptor. */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_DEVICE_DESCR, 0, (uint8_t *)CyFxUSB30DeviceDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set device descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,10);
    }

    /* High speed device descriptor. */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_HS_DEVICE_DESCR, 0, (uint8_t *)CyFxUSB20DeviceDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set device descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,11);
    }

    /* BOS descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_BOS_DESCR, 0, (uint8_t *)CyFxUSBBOSDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set configuration descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,12);
    }

    /* Device qualifier descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_DEVQUAL_DESCR, 0, (uint8_t *)CyFxUSBDeviceQualDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set device qualifier descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,13);
    }

    /* Super speed configuration descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_CONFIG_DESCR, 0, (uint8_t *)CyFxUSBSSConfigDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set configuration descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,14);
    }

    /* High speed configuration descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_HS_CONFIG_DESCR, 0, (uint8_t *)CyFxUSBHSConfigDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB Set Other Speed Descriptor failed, Error Code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,15);
    }

    /* Full speed configuration descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_FS_CONFIG_DESCR, 0, (uint8_t *)CyFxUSBFSConfigDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB Set Configuration Descriptor failed, Error Code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,16);
    }

    /* String descriptor 0 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 0, (uint8_t *)CyFxUSBStringLangIDDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,17);
    }

    /* String descriptor 1 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 1, (uint8_t *)CyFxUSBManufactureDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,18);
    }

    /* String descriptor 2 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 2, (uint8_t *)CyFxUSBProductDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,19);
    }

    // TODO: read EEPROM for Serial Number

    /* String descriptor 3 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 3, (uint8_t *)CyFxUSBSerialDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,61);
    }

    /* Connect the USB Pins with super speed operation enabled. */
    if (!no_renum) {
        apiRetStatus = CyU3PConnectState(CyTrue, CyTrue);
        if (apiRetStatus != CY_U3P_SUCCESS)
        {
            //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "USB Connect failed, Error code = %d\n", apiRetStatus);
            CyFxAppErrorHandler(apiRetStatus,21);
        }
    }
    else
    {
        /* USB connection is already active. Configure the endpoints and DMA channels. */
        if (glIsApplnActive)
            CyFxApplnStop();
        CyFxApplnStart();
    }
    //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyFxApplnInit complete\r\n");
}

/* Entry function for the AppThread. */
void
AppThread_Entry (
        uint32_t input)
{
	CyU3PDmaState_t state;
	uint32_t prodXferCount, consXferCount, count_new, count_old;
	uint8_t sckIndex;

    /* Initialize the peripheral modules */
    //CyFxApplnDebugInit();
    //CyU3PDebugPrint(1, "UART debug initialized\r\n");
    CyFxI2cInit();
    CyFxSpiInit(LMS6_WORDLEN);  // TODO: will need to detect LMS7002M

    /* Initialize the application */
    CyFxApplnInit();

    for (;;)
    {
    	if (glIsApplnFaulted == CyTrue) break;

        /* LED toggling function start */
        if(on_time != 0)
        {
            CyU3PGpioSetValue(GPIO_LED1, LED_ON);
            CyU3PThreadSleep(on_time);
        }
        if (off_time != 0)
        {
            CyU3PGpioSetValue(GPIO_LED1, LED_OFF);
            CyU3PThreadSleep(off_time);
        }
        /* LED toggling function end  */

    	count_old = prodXferCount;
    	sckIndex = 0;
        CyU3PDmaMultiChannelGetStatus(&glChHandlePtoU, &state, &prodXferCount, &consXferCount, sckIndex);
        count_new = prodXferCount;

        if (count_new != count_old) CyU3PGpioSetValue(GPIO_LED2, LED_ON);
        else CyU3PGpioSetValue(GPIO_LED2, LED_OFF);

        // TEST ERROR HANDLER
        //CyFxAppErrorHandler(0,99);

        if(config_led==1)
        {
            CyU3PGpioSetValue(GPIO_LED3, LED_ON);
            config_led--;
        }
        else CyU3PGpioSetValue(GPIO_LED3, LED_OFF);
    }
}

/* Application define function which creates the threads. */
void
CyFxApplicationDefine(
        void)
{
    void *ptr = NULL;
    uint32_t ret = CY_U3P_SUCCESS;

    /* Allocate the memory for the thread */
    ptr = CyU3PMemAlloc(CY_FX_APP_THREAD_STACK);

    /* Create the thread for the application */
    ret = CyU3PThreadCreate(&AppThread,                            /* App thread structure */
                          "21:Slave_FIFO_sync",                    /* Thread ID and thread name */
                          AppThread_Entry,                         /* App thread entry function */
                          0,                                       /* No input parameter to thread */
                          ptr,                                     /* Pointer to the allocated thread stack */
                          CY_FX_APP_THREAD_STACK,                  /* App thread stack size */
                          CY_FX_APP_THREAD_PRIORITY,               /* App thread priority */
                          CY_FX_APP_THREAD_PRIORITY,               /* App thread pre-emption threshold */
                          CYU3P_NO_TIME_SLICE,                     /* No time slice for the application thread */
                          CYU3P_AUTO_START                         /* Start the thread immediately */
                          );

    /* Check the return code */
    if (ret != 0)
    {
        /* Thread Creation failed with the error code retThrdCreate */

        /* Add custom recovery or debug actions here */
    	CyFxAppErrorHandler(0,40);

        /* Application cannot continue */
        /* Loop indefinitely */
        while(1);
    }
}

/*
 * Main function
 */
int
main (void)
{
    CyU3PIoMatrixConfig_t io_cfg;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    CyU3PSysClockConfig_t clkCfg;

    // AN65974 pg. 59
    clkCfg.setSysClk400  = CyTrue;
    clkCfg.cpuClkDiv     = 2;
    clkCfg.dmaClkDiv     = 2;
    clkCfg.mmioClkDiv    = 2;
    clkCfg.useStandbyClk = CyFalse;
    clkCfg.clkSrc        = CY_U3P_SYS_CLK;

    /* Initialize the device */
    status = CyU3PDeviceInit(&clkCfg);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Initialize the caches. Enable instruction cache and keep data cache disabled.
     * The data cache is useful only when there is a large amount of CPU based memory
     * accesses. When used in simple cases, it can decrease performance due to large 
     * number of cache flushes and cleans and also it adds to the complexity of the
     * code. */
    //status = CyU3PDeviceCacheControl(CyTrue, CyFalse, CyFalse);
    status = CyU3PDeviceCacheControl(CyTrue, CyTrue, CyTrue);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Configure the IO matrix for the device. On the FX3 DVK board, the COM port 
     * is connected to the IO(53:56). So since we need to use SPI, we will have to
     * either not use UART or use an external UART controller on the IO(46:49). */
    CyU3PMemSet((uint8_t *)&io_cfg, 0, sizeof(io_cfg));
    io_cfg.isDQ32Bit = CyFalse;
    io_cfg.useUart   = CyFalse;
    io_cfg.useI2C    = CyTrue;
    io_cfg.useI2S    = CyFalse;
    io_cfg.useSpi    = CyTrue;
    io_cfg.lppMode   = CY_U3P_IO_MATRIX_LPP_SPI_ONLY;

    /* No GPIOs are enabled. */
    io_cfg.gpioSimpleEn[0]  = 0;
    io_cfg.gpioSimpleEn[1]  = 0;
    io_cfg.gpioComplexEn[0] = 0;
    io_cfg.gpioComplexEn[1] = 0;
    status = CyU3PDeviceConfigureIOMatrix(&io_cfg);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Init the GPIO module */
    CyU3PGpioClock_t gpioClock;
    CyU3PGpioSimpleConfig_t gpioConfig;

    gpioClock.fastClkDiv = 2;
    gpioClock.slowClkDiv = 0;
    gpioClock.simpleDiv = CY_U3P_GPIO_SIMPLE_DIV_BY_2;
    gpioClock.clkSrc = CY_U3P_SYS_CLK;
    gpioClock.halfDiv = 0;

    status = CyU3PGpioInit(&gpioClock, NULL);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_LED1, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LED1, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_LED2, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LED2, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_LED3, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LED3, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyTrue;
    gpioConfig.driveLowEn = CyFalse;
    gpioConfig.driveHighEn = CyFalse;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_TX_ID, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_TX_ID, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_LNA0, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LNA0, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_LNA1, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LNA1, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_PA0, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_PA0, &gpioConfig);

    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_RESET, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_RESET, &gpioConfig);

    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_SPI_SSN, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_SPI_SSN, &gpioConfig);

    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride(GPIO_SBEN, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_SBEN, &gpioConfig);

    /* This is a non returnable call for initializing the RTOS kernel */
    CyU3PKernelEntry();

    /* Dummy return to make the compiler happy */
    return 0;

handle_fatal_error:

    /* Cannot recover from this error. */
    while (1);
}

/* [ ] */

