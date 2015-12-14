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

   The GPIF configuration data for the Synchronous Slave FIFO operation is
   loaded onto the appropriate GPIF registers. The p-port data transfers are
   done via the producer p-port socket and the consumer p-port socket.

   This interface implements one DMA Channels in AUTO mode one for P to U data
   transfer.  There is no implementation of the U to P data transfer, and the
   firmware will cause a fatal error to occur if any data is attempted to be
   sent to the OUT endpoint.

   The P to U DMA channel connects the producer p-port socket to the USB
   consumer (IN) endpoint.

   Upon every reception of data in the DMA buffer from the host, the
   CPU is signalled using DMA callbacks. There are two DMA callback functions
   implemented each for U to P and P to U data paths. The CPU then commits the
   DMA buffer received so that the data is transferred to the consumer.

   The DMA buffer size for each channel is defined based on the USB speed. 64
   for full speed, 512 for high speed and 1K for super speed. The number of
   DMA buffers is 4.

   The constant CY_FX_SLFIFO_GPIF_16_32BIT_CONF_SELECT in the header file is
   used to select 16bit GPIF data bus configuration.

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
#include "cyu3usb.h"
#include "cyu3uart.h"
#include "cyfx_app.h"
#include "cyu3gpif.h"
#include "cyu3pib.h"
#include "pib_regs.h"

#include "cyu3gpio.h"
#include "cyu3i2c.h"
#include "cyu3spi.h"

#include "cyfxgpif2config.h"

//serial interfaces bitrates
#define I2C_BITRATE        (400000)
#define SPI_BITRATE        (1000000)

//SPI SSNs
#define GPIO_SPI_SSN	49
#define GPIO_SBEN		27

//SPI wordlen
#define LMS6_WORDLEN	8
#define LMS7_WORDLEN	16
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

//X3 Connector Pins
#define GPIO_X33		25  // X3.3
#define GPIO_X35		26  // X3.5
#define GPIO_X37		44  // X3.7
#define GPIO_X39		45  // X3.9

//gpif interface control signals - not ussed
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

CyU3PThread slFifoAppThread;	        /* Slave FIFO application thread structure */
CyU3PDmaChannel glChHandleSlFifoUtoP;   /* DMA Channel handle for U2P transfer. */
CyU3PDmaChannel glChHandleSlFifoPtoU;   /* DMA Channel handle for P2U transfer. */

uint32_t glDMARxCount = 0;               /* Counter to track the number of buffers received from USB. */
uint32_t glDMATxCount = 0;               /* Counter to track the number of buffers sent to USB. */
CyBool_t glIsApplnActive = CyFalse;      /* Whether the loopback application is active or not. */
CyU3PDmaMultiChannel glChHandleUVCStream;               /* DMA multi-channel handle. */
CyU3PDmaMultiChannelConfig_t dmaMultiConfig;

uint8_t config_led=0, glEp0Buffer[64], glEp0Buffer_Rx[64], glEp0Buffer_Tx[64] __attribute__ ((aligned (32))); //4096
CyBool_t tx_id;
int glEp0Buffer_Tx_Expected = 0;

extern CyU3PReturnStatus_t CyU3PUsbSetTxSwing (uint32_t swing);

void
CyFxUvcApplnDmaCallback (
        CyU3PDmaMultiChannel *multiChHandle,
        CyU3PDmaCbType_t      type,
        CyU3PDmaCBInput_t    *input
        )
{
	CyU3PGpioSetValue (GPIO_LED3, CyTrue);
}

#define ERR_DIGIT_ON	100
#define ERR_DIGIT_OFF	400
#define ERR_DIGIT_SPACE	1000
#define ERR_DIGIT_END   3000

/* Application Error Handler */
void
CyFxAppErrorHandler (
        CyU3PReturnStatus_t apiRetStatus,    /* API return status */
        int code
        )
{
    /* Application failed with the error code apiRetStatus */
    //CyU3PDebugPrint (4, "CyFxAppErrorHandler, Error code = %d\n", apiRetStatus);

    /* Add custom debug or recovery actions here */
	if( code > 99 ) code = 99;

    /* Loop Indefinitely */
    for (;;)
    {
    	int digit1 = code / 10;
    	int digit0 = code % 10;
    	int cc;

    	// digit1:
    	for(cc=0;cc<digit1;cc++) {
    		CyU3PGpioSetValue(GPIO_LED3, CyTrue);
    		CyU3PThreadSleep(ERR_DIGIT_ON);
    		CyU3PGpioSetValue(GPIO_LED3, CyFalse);
    		CyU3PThreadSleep(ERR_DIGIT_OFF);
    	}
    	for( ;cc<10;cc++) CyU3PThreadSleep(ERR_DIGIT_ON+ERR_DIGIT_OFF);

    	// space between digit1 and digit0:
    	CyU3PThreadSleep(ERR_DIGIT_SPACE);

    	// digit0:
    	for(cc=0;cc<digit0;cc++) {
    		CyU3PGpioSetValue(GPIO_LED3, CyTrue);
    		CyU3PThreadSleep(ERR_DIGIT_ON);
    		CyU3PGpioSetValue(GPIO_LED3, CyFalse);
    		CyU3PThreadSleep(ERR_DIGIT_OFF);
    	}
    	for( ;cc<10;cc++) CyU3PThreadSleep(ERR_DIGIT_ON+ERR_DIGIT_OFF);

    	// space between digit0 and digit1:
    	CyU3PThreadSleep(ERR_DIGIT_END);
    }
}

/* SPI initialization for application. */
CyU3PReturnStatus_t
CyFxSpiInit (uint8_t wordLen)
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
    CyU3PMemSet ((uint8_t *)&spiConfig, 0, sizeof(spiConfig));
    spiConfig.isLsbFirst = CyFalse;
    spiConfig.cpol       = CyFalse;
    spiConfig.ssnPol     = CyFalse;
    spiConfig.cpha       = CyFalse;
    spiConfig.leadTime   = CY_U3P_SPI_SSN_LAG_LEAD_HALF_CLK;
    spiConfig.lagTime    = CY_U3P_SPI_SSN_LAG_LEAD_HALF_CLK;
    spiConfig.ssnCtrl    = CY_U3P_SPI_SSN_CTRL_NONE;
    spiConfig.clock      = SPI_BITRATE;
    spiConfig.wordLen    = wordLen;

    status = CyU3PSpiSetConfig (&spiConfig, NULL);

    return status;
}

/* I2c initialization for EEPROM programming. */
CyU3PReturnStatus_t
CyFxI2cInit ()
    {
    CyU3PI2cConfig_t i2cConfig;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Initialize and configure the I2C master module. */
    status = CyU3PI2cInit ();
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Start the I2C master block. The bit rate is set at 100KHz.
     * The data transfer is done via DMA. */
    CyU3PMemSet ((uint8_t *)&i2cConfig, 0, sizeof(i2cConfig));
    i2cConfig.bitRate    = I2C_BITRATE;
    i2cConfig.busTimeout = 0xFFFFFFFF;
    i2cConfig.dmaTimeout = 0xFFFF;
    i2cConfig.isDma      = CyFalse;

    status = CyU3PI2cSetConfig (&i2cConfig, NULL);
    return status;
}

/* DMA callback function to handle the produce events for U to P transfers. */
void
CyFxSlFifoUtoPDmaCallback (
        CyU3PDmaChannel   *chHandle,
        CyU3PDmaCbType_t  type,
        CyU3PDmaCBInput_t *input
        )
{
	// we do not expect transfers *TO* the LIME on this interface
	CyFxAppErrorHandler(CY_U3P_ERROR_INVALID_SEQUENCE,30);
#if 0
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    if (type == CY_U3P_DMA_CB_PROD_EVENT)
    {
        /* This is a produce event notification to the CPU. This notification is 
         * received upon reception of every buffer. The buffer will not be sent
         * out unless it is explicitly committed. The call shall fail if there
         * is a bus reset / usb disconnect or if there is any application error. */
        status = CyU3PDmaChannelCommitBuffer (chHandle, input->buffer_p.count, 0);
        if (status != CY_U3P_SUCCESS)
        {
            //CyU3PDebugPrint (4, "CyU3PDmaChannelCommitBuffer failed, Error code = %d\n", status);
        	CyFxAppErrorHandler(status,30);
        }

        /* Increment the counter. */
        glDMARxCount++;
    }
#endif
}

/* DMA callback function to handle the produce events for P to U transfers. */
void
CyFxSlFifoPtoUDmaCallback (
        CyU3PDmaChannel   *chHandle,
        CyU3PDmaCbType_t  type,
        CyU3PDmaCBInput_t *input
        )
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    if (type == CY_U3P_DMA_CB_PROD_EVENT)
    {
        /* This is a produce event notification to the CPU. This notification is 
         * received upon reception of every buffer. The buffer will not be sent
         * out unless it is explicitly committed. The call shall fail if there
         * is a bus reset / usb disconnect or if there is any application error. */
        status = CyU3PDmaChannelCommitBuffer (chHandle, input->buffer_p.count, 0);
        if (status != CY_U3P_SUCCESS)
        {
            //CyU3PDebugPrint (4, "CyU3PDmaChannelCommitBuffer failed, Error code = %d\n", status);
        	CyFxAppErrorHandler(status,31);
        }

        /* Increment the counter. */
        glDMATxCount++;
    }
}

/* This function starts the slave FIFO loop application. This is called
 * when a SET_CONF event is received from the USB host. The endpoints
 * are configured and the DMA pipe is setup in this function. */
void
CyFxSlFifoApplnStart (
        void)
{
    uint16_t size = 0;
    CyU3PEpConfig_t epCfg;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    CyU3PUSBSpeed_t usbSpeed = CyU3PUsbGetSpeed();

    /* First identify the usb speed. Once that is identified,
     * create a DMA channel and start the transfer on this. */

    /* Based on the Bus Speed configure the endpoint packet size */
    switch (usbSpeed)
    {
        case CY_U3P_FULL_SPEED:
            size = 64;
            break;

        case CY_U3P_HIGH_SPEED:
            size = 512;
            break;

        case  CY_U3P_SUPER_SPEED:
            size = 1024;
            break;

        default:
            //CyU3PDebugPrint (4, "Error! Invalid USB speed.\n");
            CyFxAppErrorHandler (CY_U3P_ERROR_FAILURE,1);
            break;
    }

    CyU3PMemSet ((uint8_t *)&epCfg, 0, sizeof (epCfg));
    epCfg.enable = CyTrue;
    epCfg.epType = CY_U3P_USB_EP_BULK;
    epCfg.burstLen = (usbSpeed == CY_U3P_SUPER_SPEED) ? (CY_FX_EP_BURST_LENGTH) : 1;
    epCfg.streams = 0;
    epCfg.pcktSize = size;

    /* Producer endpoint configuration */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_PRODUCER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler (apiRetStatus,2);
    }

    /* Consumer endpoint configuration */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_CONSUMER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,3);
    }

    /* Create a DMA Auto channel*/
    dmaMultiConfig.size           = 4*1024;//4k
    dmaMultiConfig.count          = 4;
    dmaMultiConfig.validSckCount  = 2;
    dmaMultiConfig.prodSckId [0]  = (CyU3PDmaSocketId_t)CY_U3P_PIB_SOCKET_0;
    dmaMultiConfig.prodSckId [1]  = (CyU3PDmaSocketId_t)CY_U3P_PIB_SOCKET_1;
    dmaMultiConfig.consSckId [0]  = CY_FX_CONSUMER_USB_SOCKET;
    dmaMultiConfig.prodAvailCount = 0;
    dmaMultiConfig.prodHeader     = 0;
    dmaMultiConfig.prodFooter     = 0;
    dmaMultiConfig.consHeader     = 0;
    dmaMultiConfig.dmaMode        = CY_U3P_DMA_MODE_BYTE;
    dmaMultiConfig.notification   = 0xFF;//CY_U3P_DMA_CB_CONS_EVENT;
    dmaMultiConfig.cb             = CyFxUvcApplnDmaCallback;
    apiRetStatus = CyU3PDmaMultiChannelCreate (&glChHandleUVCStream, CY_U3P_DMA_TYPE_AUTO_MANY_TO_ONE,
            &dmaMultiConfig);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        /* Error handling */
        //CyU3PDebugPrint (4, "DMA Channel Creation Failed, Error Code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,4);
    }

    CyU3PUsbFlushEp (CY_FX_EP_CONSUMER);
	CyU3PUsbFlushEp (CY_FX_EP_PRODUCER);

	CyU3PDmaMultiChannelSetXfer (&glChHandleUVCStream, 0, 0);

    /* Update the status flag. */
    glIsApplnActive = CyTrue;
}

/* This function stops the slave FIFO loop application. This shall be called
 * whenever a RESET or DISCONNECT event is received from the USB host. The
 * endpoints are disabled and the DMA pipe is destroyed by this function. */
void
CyFxSlFifoApplnStop (
        void)
{
    CyU3PEpConfig_t epCfg;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Update the flag. */
    glIsApplnActive = CyFalse;

    /* Flush the endpoint memory */
    CyU3PUsbFlushEp(CY_FX_EP_PRODUCER);
    CyU3PUsbFlushEp(CY_FX_EP_CONSUMER);

    /* Destroy the channel */
    CyU3PDmaChannelDestroy (&glChHandleSlFifoUtoP);
    CyU3PDmaChannelDestroy (&glChHandleSlFifoPtoU);

    /* Disable endpoints. */
    CyU3PMemSet ((uint8_t *)&epCfg, 0, sizeof (epCfg));
    epCfg.enable = CyFalse;

    /* Producer endpoint configuration. */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_PRODUCER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler (apiRetStatus,5);
    }

    /* Consumer endpoint configuration. */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_CONSUMER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler (apiRetStatus,6);
    }
}

/* Callback to handle the USB setup requests. */
CyBool_t
CyFxSlFifoApplnUSBSetupCB (
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
    unsigned char i;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

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
                CyU3PUsbAckSetup ();
            else
                CyU3PUsbStall (0, CyTrue, CyFalse);

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
                CyU3PUsbStall (wIndex, CyFalse, CyTrue);
                isHandled = CyTrue;
            }
        }
    }


    /* Handle supported vendor requests. */
    if (bType == CY_U3P_USB_VENDOR_RQT)
    {
        uint8_t   I2C_Addr;
    	CyU3PI2cPreamble_t preamble;
        uint8_t   gpio_num;
        uint8_t  *serial_num;

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

        	CyU3PGpioSetValue (GPIO_LED3, CyTrue);
        	config_led = 1;
        	CyU3PUsbSendEP0Data (64, glEp0Buffer_Tx);

        	break;

        case 0xC1: //write

        	CyU3PGpioSetValue (GPIO_LED3, CyTrue);
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

        		        CyU3PI2cReceiveBytes (&preamble, &glEp0Buffer_Tx[i], 1, 0);

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

            	        CyU3PI2cTransmitBytes (&preamble, &glEp0Buffer_Rx[5+i*2], 1, 0);
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
        				if(glEp0Buffer_Rx[4+i] & 0x01) CyU3PGpioSetValue (GPIO_LNA0, CyTrue); else CyU3PGpioSetValue (GPIO_LNA0, CyFalse); //LNA0
        				if(glEp0Buffer_Rx[4+i] & 0x02) CyU3PGpioSetValue (GPIO_LNA1, CyTrue); else CyU3PGpioSetValue (GPIO_LNA1, CyFalse); //LNA1
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
        				if(glEp0Buffer_Rx[4+i] & 0x01) CyU3PGpioSetValue (GPIO_PA0, CyTrue); else CyU3PGpioSetValue (GPIO_PA0, CyFalse); //PA0
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

        				if(glEp0Buffer_Rx[4+i]) CyU3PGpioSetValue (GPIO_RESET, CyTrue); //Reset high
        					else CyU3PGpioSetValue (GPIO_RESET, CyFalse); //Reset low
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

      		        CyU3PGpioSetValue (GPIO_SPI_SSN, CyFalse);

        			for(i=0; i<glEp0Buffer_Rx[2]; i++)
        			{
            		  	CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4+i], 1);//read reg addr
            		  	CyU3PSpiReceiveWords (&glEp0Buffer_Tx[i], 1);//data
        			};

        			CyU3PGpioSetValue (GPIO_SPI_SSN, CyTrue);

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

        		  	CyU3PGpioSetValue (GPIO_SPI_SSN, CyFalse);

					for(i=0; i<glEp0Buffer_Rx[2]; i++)
					{

					  CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4+2*i], glEp0Buffer_Rx[2]*2);//reg + data
					};
        		  	//CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4], glEp0Buffer_Rx[2]*2);//data
        		  	CyU3PGpioSetValue (GPIO_SPI_SSN, CyTrue);
        		break;

        	  case	CMD_GET_INFO:

		          glEp0Buffer_Tx_Expected = 52;

        		  CyU3PGpifGetSMState(&glEp0Buffer_Tx[1]);
        		  serial_num = (uint8_t *)CyFxUSBSerialDscr;

        		  CyU3PGpioGetValue (GPIO_TX_ID, &tx_id);
        		  glEp0Buffer_Tx[0] = tx_id;
        		  //CyU3PGpifGetSMState(), above.
        		  for(i=0,serial_num = (uint8_t *)CyFxUSBSerialDscr;i<8;i++)
        		  {
        			  glEp0Buffer_Tx[i+2] = serial_num[(i*2)+2];
        		  }

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
						CyU3PGpioSetValue (GPIO_SBEN, CyFalse);
						CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4]+i*(ADF_WORDLEN/8), (ADF_WORDLEN/8));//data
						CyU3PGpioSetValue (GPIO_SBEN, CyTrue);
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
                        CyU3PReturnStatus_t status;
                        CyBool_t pin;

                        gpioConfig.outValue = CyFalse;
                        gpioConfig.inputEn = CyTrue;
                        gpioConfig.driveLowEn = CyFalse;
                        gpioConfig.driveHighEn = CyFalse;
                        gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
                        status = CyU3PDeviceGpioOverride (gpio_num, CyTrue);
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
                        CyU3PReturnStatus_t status;
                        CyBool_t pin = glEp0Buffer_Rx[4] ? CyTrue : CyFalse;

                        gpioConfig.outValue = pin;
                        gpioConfig.inputEn = CyFalse;
                        gpioConfig.driveLowEn = CyTrue;
                        gpioConfig.driveHighEn = CyTrue;
                        gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
                        status = CyU3PDeviceGpioOverride (gpio_num, CyTrue);
                        status = CyU3PGpioSetSimpleConfig(gpio_num, &gpioConfig);
         		        CyU3PGpioSetValue(gpio_num, pin);
                        if(pin) glEp0Buffer_Tx[0] = 1;
                        else    glEp0Buffer_Tx[0] = 0;
                    }

        		  break;
        	}

        	config_led = 1;
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
    }

    return isHandled;
}

/* This is the callback function to handle the USB events. */
void
CyFxSlFifoApplnUSBEventCB (
    CyU3PUsbEventType_t evtype,
    uint16_t            evdata
    )
{
    switch (evtype)
    {
        case CY_U3P_USB_EVENT_SETCONF:
            /* Stop the application before re-starting. */
            if (glIsApplnActive)
            {
                CyFxSlFifoApplnStop ();
            }
            /* Start the loop back function. */
            CyFxSlFifoApplnStart ();
            break;

        case CY_U3P_USB_EVENT_RESET:
        case CY_U3P_USB_EVENT_DISCONNECT:
            /* Stop the loop back function. */
            if (glIsApplnActive)
            {
                CyFxSlFifoApplnStop ();
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

/* This function initializes the GPIF interface and initializes
 * the USB interface. */
void
CyFxSlFifoApplnInit (void)
{
    CyU3PPibClock_t pibClock;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Initialize the p-port block. */
    pibClock.clkDiv = 2;
    pibClock.clkSrc = CY_U3P_SYS_CLK;
    pibClock.isHalfDiv = CyFalse;
    /* Disable DLL for sync GPIF */
    pibClock.isDllEnable = CyFalse;
    apiRetStatus = CyU3PPibInit(CyTrue, &pibClock);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "P-port Initialization failed, Error Code = %d\n",apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,7);
    }

    /* Load the GPIF configuration for Slave FIFO sync mode. */
    apiRetStatus = CyU3PGpifLoad (&CyFxGpifConfig);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "CyU3PGpifLoad failed, Error Code = %d\n",apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,8);
    }

    /* Start the state machine. */
    apiRetStatus = CyU3PGpifSMStart (START, ALPHA_START);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "CyU3PGpifSMStart failed, Error Code = %d\n",apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,9);
    }

    /* Start the USB functionality. */
    apiRetStatus = CyU3PUsbStart();
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "CyU3PUsbStart failed to Start, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,20);
    }

    CyU3PUsbSetTxSwing(127); //TX Amplitude swing of the electrical signalling on the USB superspeed lines in 10 mV units. Should be less than 1.28V.

    /* The fast enumeration is the easiest way to setup a USB connection,
     * where all enumeration phase is handled by the library. Only the
     * class / vendor requests need to be handled by the application. */
    CyU3PUsbRegisterSetupCallback(CyFxSlFifoApplnUSBSetupCB, CyTrue);

    /* Setup the callback to handle the USB events. */
    CyU3PUsbRegisterEventCallback(CyFxSlFifoApplnUSBEventCB);

    /* Register a callback to handle LPM requests from the USB 3.0 host. */
    //CyU3PUsbRegisterLPMRequestCallback(CyFxApplnLPMRqtCB);
	CyU3PUsbLPMDisable() ;//lpm disable

    /* Set the USB Enumeration descriptors */

    /* Super speed device descriptor. */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_DEVICE_DESCR, NULL, (uint8_t *)CyFxUSB30DeviceDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set device descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,10);
    }

    /* High speed device descriptor. */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_HS_DEVICE_DESCR, NULL, (uint8_t *)CyFxUSB20DeviceDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set device descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,11);
    }

    /* BOS descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_BOS_DESCR, NULL, (uint8_t *)CyFxUSBBOSDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set configuration descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,12);
    }

    /* Device qualifier descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_DEVQUAL_DESCR, NULL, (uint8_t *)CyFxUSBDeviceQualDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set device qualifier descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,13);
    }

    /* Super speed configuration descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_CONFIG_DESCR, NULL, (uint8_t *)CyFxUSBSSConfigDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set configuration descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,14);
    }

    /* High speed configuration descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_HS_CONFIG_DESCR, NULL, (uint8_t *)CyFxUSBHSConfigDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB Set Other Speed Descriptor failed, Error Code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,15);
    }

    /* Full speed configuration descriptor */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_FS_CONFIG_DESCR, NULL, (uint8_t *)CyFxUSBFSConfigDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB Set Configuration Descriptor failed, Error Code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,16);
    }

    /* String descriptor 0 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 0, (uint8_t *)CyFxUSBStringLangIDDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,17);
    }

    /* String descriptor 1 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 1, (uint8_t *)CyFxUSBManufactureDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,18);
    }

    /* String descriptor 2 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 2, (uint8_t *)CyFxUSBProductDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,19);
    }

    // TODO: read EEPROM for Serial Number

    /* String descriptor 3 */
    apiRetStatus = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 3, (uint8_t *)CyFxUSBSerialDscr);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,61);
    }

    /* Connect the USB Pins with super speed operation enabled. */
    apiRetStatus = CyU3PConnectState(CyTrue, CyTrue);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint (4, "USB Connect failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,21);
    }
}

/* Entry function for the slFifoAppThread. */
void
SlFifoAppThread_Entry (
        uint32_t input)
{
	CyU3PDmaState_t state;
	uint32_t prodXferCount, consXferCount, count_new, count_old;
	uint8_t sckIndex;

    /* Initialize the debug module */
    //CyFxSlFifoApplnDebugInit();

    CyFxI2cInit ();

    /* Initialize the SPI interface. */
    CyFxSpiInit (8);//LMS6_WORDLEN);

    /* Initialize the slave FIFO application */
    CyFxSlFifoApplnInit();

    for (;;)
    {
        CyU3PThreadSleep (250);
        CyU3PGpioSetValue (GPIO_LED1, CyFalse);
    	CyU3PThreadSleep (250);
    	CyU3PGpioSetValue (GPIO_LED1, CyTrue);

    	count_old = prodXferCount;
    	sckIndex = 0;
        CyU3PDmaMultiChannelGetStatus(&glChHandleUVCStream, &state, &prodXferCount, &consXferCount, sckIndex);
        count_new = prodXferCount;

        if (count_new != count_old) CyU3PGpioSetValue (GPIO_LED2, CyTrue);
        else CyU3PGpioSetValue (GPIO_LED2, CyFalse);

        // TEST ERROR HANDLER
        //CyFxAppErrorHandler(0,99);

        if(config_led==1)
        {
            CyU3PGpioSetValue (GPIO_LED3, CyTrue);
            config_led--;
        }
        else CyU3PGpioSetValue (GPIO_LED3, CyFalse);

#if 0
        if (glIsApplnActive)
        {
            /* Print the number of buffers received so far from the USB host. */
            CyU3PDebugPrint (6, "Data tracker: buffers received: %d, buffers sent: %d.\r\n",  glDMARxCount, glDMATxCount);

            sckIndex = 0;
            CyU3PDmaMultiChannelGetStatus(&glChHandleUVCStream, &state, &prodXferCount, &consXferCount, sckIndex);
            CyU3PDebugPrint (6, "DMA state: %d prodXferCount: %d consXferCount: %d sckIndex: %d.\r\n",  state, prodXferCount, consXferCount, sckIndex);

            sckIndex = 1;
            CyU3PDmaMultiChannelGetStatus(&glChHandleUVCStream, &state, &prodXferCount, &consXferCount, sckIndex);
            CyU3PDebugPrint (6, "DMA state: %d prodXferCount: %d consXferCount: %d sckIndex: %d.\r\n",  state, prodXferCount, consXferCount, sckIndex);


            CyU3PGpifGetSMState(&sstate);
            CyU3PDebugPrint (6, "Sstate: %d.\r\n",  sstate);
        }
#endif

    }
}

/* Application define function which creates the threads. */
void
CyFxApplicationDefine (
        void)
{
    void *ptr = NULL;
    uint32_t retThrdCreate = CY_U3P_SUCCESS;

    /* Allocate the memory for the thread */
    ptr = CyU3PMemAlloc (CY_FX_SLFIFO_THREAD_STACK);

    /* Create the thread for the application */
    retThrdCreate = CyU3PThreadCreate (&slFifoAppThread,           /* Slave FIFO app thread structure */
                          "21:Slave_FIFO_sync",                    /* Thread ID and thread name */
                          SlFifoAppThread_Entry,                   /* Slave FIFO app thread entry function */
                          0,                                       /* No input parameter to thread */
                          ptr,                                     /* Pointer to the allocated thread stack */
                          CY_FX_SLFIFO_THREAD_STACK,               /* App Thread stack size */
                          CY_FX_SLFIFO_THREAD_PRIORITY,            /* App Thread priority */
                          CY_FX_SLFIFO_THREAD_PRIORITY,            /* App Thread pre-emption threshold */
                          CYU3P_NO_TIME_SLICE,                     /* No time slice for the application thread */
                          CYU3P_AUTO_START                         /* Start the thread immediately */
                          );

    /* Check the return code */
    if (retThrdCreate != 0)
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

    /* Initialize the device */
    status = CyU3PDeviceInit (NULL);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Initialize the caches. Enable both Instruction and Data Caches. */
    status = CyU3PDeviceCacheControl (CyTrue, CyTrue, CyTrue);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Configure the IO matrix for the device. On the FX3 DVK board, the COM port 
     * is connected to the IO(53:56). So since we need to use SPI, we will have to
     * either not use UART or use an external UART controller on the IO(46:49). */
    CyU3PMemSet ((uint8_t *)&io_cfg, 0, sizeof(io_cfg));
    io_cfg.isDQ32Bit = CyFalse;
    io_cfg.useUart   = CyFalse;
    io_cfg.useI2C    = CyTrue;
    io_cfg.useI2S    = CyFalse;
    io_cfg.useSpi    = CyTrue;
    io_cfg.lppMode   = CY_U3P_IO_MATRIX_LPP_SPI_ONLY;//CY_U3P_IO_MATRIX_LPP_DEFAULT;

    /* No GPIOs are enabled. */
    io_cfg.gpioSimpleEn[0]  = 0;
    io_cfg.gpioSimpleEn[1]  = 0;//0x1C000,//46,47,48;
    io_cfg.gpioComplexEn[0] = 0;
    io_cfg.gpioComplexEn[1] = 0;
    status = CyU3PDeviceConfigureIOMatrix (&io_cfg);
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
    status = CyU3PDeviceGpioOverride (GPIO_LED1, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LED1, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_LED2, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LED2, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_LED3, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LED3, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyTrue;
    gpioConfig.driveLowEn = CyFalse;
    gpioConfig.driveHighEn = CyFalse;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_TX_ID, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_TX_ID, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_LNA0, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LNA0, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_LNA1, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_LNA1, &gpioConfig);

    gpioConfig.outValue = CyFalse;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_PA0, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_PA0, &gpioConfig);

    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_RESET, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_RESET, &gpioConfig);

    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_SPI_SSN, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_SPI_SSN, &gpioConfig);

    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    status = CyU3PDeviceGpioOverride (GPIO_SBEN, CyTrue);
    status = CyU3PGpioSetSimpleConfig(GPIO_SBEN, &gpioConfig);

    /* This is a non returnable call for initializing the RTOS kernel */
    CyU3PKernelEntry ();

    /* Dummy return to make the compiler happy */
    return 0;

handle_fatal_error:

    /* Cannot recover from this error. */
    while (1);
}

/* [ ] */

