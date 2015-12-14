/*
 ## Cypress USB 3.0 Platform source file (cyfxbulksrcsink.c)
 ## ===========================
 ##
 ##  Copyright Cypress Semiconductor Corporation, 2010-2011,
 ##  All Rights Reserved
 ##  UNPUBLISHED, LICENSED SOFTWARE.
 ##
 ##  CONFIDENTIAL AND PROPRIETARY INFORMATION
 ##  WHICH IS THE PROPERTY OF CYPRESS.
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
 ##  This source code is derived from the Cypress SS Explorer Kit Example:
 ##  'USBBulkSourceSinkLED'.  As per clause 1.1 of the above license,
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

/* This file illustrates the bulk source sink LED application example using the DMA MANUAL_IN
   and DMA MANUAL_OUT mode */

/*
   This example illustrates on how to configure the GPIO as an output and drive the LED.
   The LED will blink at different rates if the FX3 DVK is connected to a SuperSpeed USB port. The LED
   be mostly on for SS, 50%on for HISPEED, mostly off for LOWSPEED.

   This example also illustrates USB endpoint data source and data sink mechanism. The example
   comprises of vendor class USB enumeration descriptors with 2 bulk endpoints. A bulk OUT
   endpoint acts as the producer of data and acts as the sink to the host. A bulk IN endpoint
   acts as the consumer of data and acts as the source to the host.

   The data source and sink is achieved with the help of a DMA MANUAL IN channel and a DMA
   MANUAL OUT channel. A DMA MANUAL IN channel is created between the producer USB bulk
   endpoint and the CPU. A DMA MANUAL OUT channel is created between the CPU and the consumer
   USB bulk endpoint. Data is received in the IN channel DMA buffer from the host through the
   producer endpoint. CPU is signaled of the data reception using DMA callbacks. The CPU
   discards this buffer. This leads to the sink mechanism. A constant pattern data is loaded
   onto the OUT Channel DMA buffer whenever the buffer is available. CPU issues commit of
   the DMA data transfer to the consumer endpoint which then gets transferred to the host.
   This leads to a constant source mechanism.

   The DMA buffer size is defined based on the USB speed. 64 for full speed, 512 for high speed
   and 1024 for super speed. CY_FX_APP_DMA_BUF_COUNT in the header file defines the
   number of DMA buffers.
   
   For performance optimizations refer the readme.txt
 */

#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyfx_app.h"
#include "cyu3usb.h"
#include "cyu3uart.h"
//#include "cyu3gpif.h"
//#include "cyu3pib.h"
//#include "pib_regs.h"

#include "cyu3gpio.h"
//#include "cyu3i2c.h"
//#include "cyu3spi.h"
#include "cyu3utils.h"

//#include "cyfxgpif2config.h"

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

#define GPIO_LED1		54
#define GPIO_LED2		xx
#define GPIO_LED3		xx

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

CyU3PThread     bulkSrcSinkAppThread;	 /* Application thread structure */
CyU3PDmaChannel glChHandleBulkSink;      /* DMA MANUAL_IN channel handle.          */
CyU3PDmaChannel glChHandleBulkSrc;       /* DMA MANUAL_OUT channel handle.         */

CyBool_t glIsApplnActive = CyFalse;      /* Whether the source sink application is active or not. */
uint32_t glDMARxCount = 0;               /* Counter to track the number of buffers received. */
uint32_t glDMATxCount = 0;               /* Counter to track the number of buffers transmitted. */
CyBool_t glDataTransStarted = CyFalse;   /* Whether DMA transfer has been started after enumeration. */
CyBool_t StandbyModeEnable  = CyFalse;   /* Whether standby mode entry is enabled. */
CyBool_t TriggerStandbyMode = CyFalse;   /* Request to initiate standby entry. */
CyBool_t glForceLinkU2      = CyFalse;   /* Whether the device should try to initiate U2 mode. */

volatile uint32_t glEp0StatCount = 0;           /* Number of EP0 status events received. */
//uint8_t glEp0Buffer[32] __attribute__ ((aligned (32))); /* Local buffer used for vendor command handling. */
uint8_t glEp0Buffer_Rx[64] __attribute__ ((aligned (32)));
uint8_t glEp0Buffer_Tx[64] __attribute__ ((aligned (32)));
int glEp0Buffer_Tx_Expected = 0;

uint16_t on_time = 0, off_time = 0;

/* Control request related variables. */
CyU3PEvent glBulkLpEvent;       /* Event group used to signal the thread that there is a pending request. */
uint32_t   gl_setupdat0;        /* Variable that holds the setupdat0 value (bmRequestType, bRequest and wValue). */
uint32_t   gl_setupdat1;        /* Variable that holds the setupdat1 value (wIndex and wLength). */
#define CYFX_USB_CTRL_TASK      (1 << 0)        /* Event that indicates that there is a pending USB control request. */
#define CYFX_USB_HOSTWAKE_TASK  (1 << 1)        /* Event that indicates the a Remote Wake should be attempted. */

/* Buffer used for USB event logs. */
uint8_t *gl_UsbLogBuffer = NULL;
#define CYFX_USBLOG_SIZE        (0x1000)

/* GPIO used for testing IO state retention when switching from boot firmware to full firmware. */
#define FX3_GPIO_TEST_OUT               (50)
#define FX3_GPIO_TO_LOFLAG(gpio)        (1 << (gpio))
#define FX3_GPIO_TO_HIFLAG(gpio)        (1 << ((gpio) - 32))

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
    		CyU3PGpioSetValue(GPIO_LED1, CyFalse);	// ON
    		CyU3PThreadSleep(ERR_DIGIT_ON);
    		CyU3PGpioSetValue(GPIO_LED1, CyTrue);	// OFF
    		CyU3PThreadSleep(ERR_DIGIT_OFF);
    	}
    	//for( ;cc<10;cc++) CyU3PThreadSleep(ERR_DIGIT_ON+ERR_DIGIT_OFF);

    	// space between digit1 and digit0:
    	CyU3PThreadSleep(ERR_DIGIT_SPACE);

    	// digit0:
    	for(cc=0;cc<digit0;cc++) {
    		CyU3PGpioSetValue(GPIO_LED1, CyFalse);	// ON
    		CyU3PThreadSleep(ERR_DIGIT_ON);
    		CyU3PGpioSetValue(GPIO_LED1, CyTrue);	// OFF
    		CyU3PThreadSleep(ERR_DIGIT_OFF);
    	}
    	//for( ;cc<10;cc++) CyU3PThreadSleep(ERR_DIGIT_ON+ERR_DIGIT_OFF);

    	// space after digit0:
    	CyU3PThreadSleep(ERR_DIGIT_END);
    }
}

/* This function initializes the debug module. The debug prints
 * are routed to the UART and can be seen using a UART console
 * running at 115200 baud rate. */
void
CyFxBulkSrcSinkApplnDebugInit (void)
{
	CyU3PUartConfig_t uartConfig;
	CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;


    /* Initialize the UART for printing debug messages */
    apiRetStatus = CyU3PUartInit();
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        /* Error handling */
        CyFxAppErrorHandler(apiRetStatus, 41);
    }

    /* Set UART configuration */
    CyU3PMemSet ((uint8_t *)&uartConfig, 0, sizeof (uartConfig));
    uartConfig.baudRate = CY_U3P_UART_BAUDRATE_115200;
    uartConfig.stopBit = CY_U3P_UART_ONE_STOP_BIT;
    uartConfig.parity = CY_U3P_UART_NO_PARITY;
    uartConfig.txEnable = CyTrue;
    uartConfig.rxEnable = CyFalse;
    uartConfig.flowCtrl = CyFalse;
    uartConfig.isDma = CyTrue;

    apiRetStatus = CyU3PUartSetConfig (&uartConfig, NULL);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        CyFxAppErrorHandler(apiRetStatus, 42);
    }

    /* Set the UART transfer to a really large value. */
    apiRetStatus = CyU3PUartTxSetBlockXfer (0xFFFFFFFF);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        CyFxAppErrorHandler(apiRetStatus,43);
    }

    /* Initialize the debug module. */
    apiRetStatus = CyU3PDebugInit (CY_U3P_LPP_SOCKET_UART_CONS, 8);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        CyFxAppErrorHandler(apiRetStatus,44);
    }

    CyU3PDebugPreamble(CyFalse);
}

/* Callback function for the DMA event notification. */
void
CyFxBulkSrcSinkDmaCallback (
        CyU3PDmaChannel   *chHandle, /* Handle to the DMA channel. */
        CyU3PDmaCbType_t  type,      /* Callback type.             */
        CyU3PDmaCBInput_t *input)    /* Callback status.           */
{
    CyU3PDmaBuffer_t buf_p;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    glDataTransStarted = CyTrue;

    if (type == CY_U3P_DMA_CB_PROD_EVENT)
    {
        /* This is a produce event notification to the CPU. This notification is 
         * received upon reception of every buffer. We have to discard the buffer
         * as soon as it is received to implement the data sink. */
        status = CyU3PDmaChannelDiscardBuffer (chHandle);
        if (status != CY_U3P_SUCCESS)
        {
            //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelDiscardBuffer failed, Error code = %d\n", status);
        	CyFxAppErrorHandler(status,30);
        }

        /* Increment the counter. */
        glDMARxCount++;
    }
    if (type == CY_U3P_DMA_CB_CONS_EVENT)
    {
        /* This is a consume event notification to the CPU. This notification is 
         * received when a buffer is sent out from the device. We have to commit
         * a new buffer as soon as a buffer is available to implement the data
         * source. The data is preloaded into the buffer at that start. So just
         * commit the buffer. */
        status = CyU3PDmaChannelGetBuffer (chHandle, &buf_p, CYU3P_NO_WAIT);
        if (status == CY_U3P_SUCCESS)
        {
            /* Commit the full buffer with default status. */
            status = CyU3PDmaChannelCommitBuffer (chHandle, buf_p.size, 0);
            if (status != CY_U3P_SUCCESS)
            {
                //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelCommitBuffer failed, Error code = %d\n", status);
        	    CyFxAppErrorHandler(status,31);
            }
        }
        else
        {
            //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelGetBuffer failed, Error code = %d\n", status);
        	CyFxAppErrorHandler(status,32);
        }

        /* Increment the counter. */
        glDMATxCount++;
    }
}

/* This function starts the application. This is called
 * when a SET_CONF event is received from the USB host. The endpoints
 * are configured and the DMA pipe is setup in this function. */
void
CyFxBulkSrcSinkApplnStart (
        void)
{
    uint16_t size = 0, index = 0;
    CyU3PEpConfig_t epCfg;
    CyU3PDmaBuffer_t buf_p;
    CyU3PDmaChannelConfig_t dmaCfg;
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
        on_time  = SUPERSPEED_BLINK_ON_TIME;
        off_time = XSPEED_BLINK_PERIOD-SUPERSPEED_BLINK_ON_TIME;
        break;

    default:
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "Error! Invalid USB speed.\n");
        CyFxAppErrorHandler (CY_U3P_ERROR_FAILURE, 1);
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
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler (apiRetStatus,2);
    }

    /* Consumer endpoint configuration */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_CONSUMER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler (apiRetStatus,3);
    }

    /* Flush the endpoint memory */
    CyU3PUsbFlushEp(CY_FX_EP_PRODUCER);
    CyU3PUsbFlushEp(CY_FX_EP_CONSUMER);

    /* Create a DMA MANUAL_IN channel for the producer socket. */
    CyU3PMemSet ((uint8_t *)&dmaCfg, 0, sizeof (dmaCfg));

    /* Set the DMA buffer size and count based on constants defined in the header file. */
    dmaCfg.size  = CY_FX_APP_DMA_BUF_SIZE;
    dmaCfg.count = CY_FX_APP_DMA_BUF_COUNT;
    dmaCfg.prodSckId = CY_FX_EP_PRODUCER_SOCKET;
    dmaCfg.consSckId = CY_U3P_CPU_SOCKET_CONS;
    dmaCfg.dmaMode = CY_U3P_DMA_MODE_BYTE;
    dmaCfg.notification = CY_U3P_DMA_CB_PROD_EVENT;
    dmaCfg.cb = CyFxBulkSrcSinkDmaCallback;
    dmaCfg.prodHeader = 0;
    dmaCfg.prodFooter = 0;
    dmaCfg.consHeader = 0;
    dmaCfg.prodAvailCount = 0;

    apiRetStatus = CyU3PDmaChannelCreate (&glChHandleBulkSink,
            CY_U3P_DMA_TYPE_MANUAL_IN, &dmaCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelCreate failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,4);
    }

    /* Create a DMA MANUAL_OUT channel for the consumer socket. */
    dmaCfg.notification = CY_U3P_DMA_CB_CONS_EVENT;
    dmaCfg.prodSckId = CY_U3P_CPU_SOCKET_PROD;
    dmaCfg.consSckId = CY_FX_EP_CONSUMER_SOCKET;
    apiRetStatus = CyU3PDmaChannelCreate (&glChHandleBulkSrc,
            CY_U3P_DMA_TYPE_MANUAL_OUT, &dmaCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelCreate failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,4);
    }

    /* Set DMA Channel transfer size */
    apiRetStatus = CyU3PDmaChannelSetXfer (&glChHandleBulkSink, CY_FX_APP_DMA_TX_SIZE);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelSetXfer failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,4);
    }

    apiRetStatus = CyU3PDmaChannelSetXfer (&glChHandleBulkSrc, CY_FX_APP_DMA_TX_SIZE);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelSetXfer failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,4);
    }

    /* Now preload all buffers in the MANUAL_OUT pipe with the required data. */
    for (index = 0; index < CY_FX_APP_DMA_BUF_COUNT; index++)
    {
        apiRetStatus = CyU3PDmaChannelGetBuffer (&glChHandleBulkSrc, &buf_p, CYU3P_NO_WAIT);
        if (apiRetStatus != CY_U3P_SUCCESS)
        {
            //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelGetBuffer failed, Error code = %d\n", apiRetStatus);
            CyFxAppErrorHandler(apiRetStatus,4);
        }
        CyU3PMemSet (buf_p.buffer, CY_FX_APP_PATTERN, buf_p.size);
        apiRetStatus = CyU3PDmaChannelCommitBuffer (&glChHandleBulkSrc, buf_p.size, 0);
        if (apiRetStatus != CY_U3P_SUCCESS)
        {
            //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDmaChannelCommitBuffer failed, Error code = %d\n", apiRetStatus);
            CyFxAppErrorHandler(apiRetStatus,4);
        }
    }

    /* Update the flag so that the application thread is notified of this. */
    glIsApplnActive = CyTrue;
}

/* This function stops the application. This shall be called whenever a RESET
 * or DISCONNECT event is received from the USB host. The endpoints are
 * disabled and the DMA pipe is destroyed by this function. */
void
CyFxBulkSrcSinkApplnStop (
        void)
{
    CyU3PEpConfig_t epCfg;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Update the flag so that the application thread is notified of this. */
    glIsApplnActive = CyFalse;

    /* Destroy the channels */
    CyU3PDmaChannelDestroy (&glChHandleBulkSink);
    CyU3PDmaChannelDestroy (&glChHandleBulkSrc);

    /* Flush the endpoint memory */
    CyU3PUsbFlushEp(CY_FX_EP_PRODUCER);
    CyU3PUsbFlushEp(CY_FX_EP_CONSUMER);

    /* Disable endpoints. */
    CyU3PMemSet ((uint8_t *)&epCfg, 0, sizeof (epCfg));
    epCfg.enable = CyFalse;

    /* Producer endpoint configuration. */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_PRODUCER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler (apiRetStatus,5);
    }

    /* Consumer endpoint configuration. */
    apiRetStatus = CyU3PSetEpConfig(CY_FX_EP_CONSUMER, &epCfg);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PSetEpConfig failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler (apiRetStatus,6);
    }
}

/* Callback to handle the USB setup requests. */
CyBool_t
CyFxBulkSrcSinkApplnUSBVendorCB (
        uint32_t setupdat0, /* SETUP Data 0 */
        uint32_t setupdat1  /* SETUP Data 1 */
    )
{
    uint8_t  bRequest;  //, bReqType;
//    uint8_t  bType, bTarget;
//    uint16_t wValue, wIndex, wLength;
    CyBool_t isHandled = CyFalse;
//    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
//    uint8_t   I2C_Addr;
//    CyU3PI2cPreamble_t preamble;
    uint8_t   gpio_num;
    uint8_t  *serial_num;
    CyBool_t  tx_id;
    uint16_t  i;

    /* Decode the fields from the setup request. */
//    bReqType = (setupdat0 & CY_U3P_USB_REQUEST_TYPE_MASK);
//    bType    = (bReqType & CY_U3P_USB_TYPE_MASK);
//    bTarget  = (bReqType & CY_U3P_USB_TARGET_MASK);
    bRequest = ((setupdat0 & CY_U3P_USB_REQUEST_MASK) >> CY_U3P_USB_REQUEST_POS);
//    wValue   = ((setupdat0 & CY_U3P_USB_VALUE_MASK)   >> CY_U3P_USB_VALUE_POS);
//    wIndex   = ((setupdat1 & CY_U3P_USB_INDEX_MASK)   >> CY_U3P_USB_INDEX_POS);
//    wLength  = ((setupdat1 & CY_U3P_USB_LENGTH_MASK)  >> CY_U3P_USB_LENGTH_POS);

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

    	//CyU3PGpioSetValue (GPIO_LED3, CyTrue);
    	//config_led = 1;
    	CyU3PUsbSendEP0Data (64, glEp0Buffer_Tx);

    	break;

    case 0xC1: //write

    	//CyU3PGpioSetValue (GPIO_LED3, CyTrue);
    	//config_led = 2;
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

#if 0
/*
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

                    // NOTE: Emulation does not talk to I2C
    		        //CyU3PI2cReceiveBytes (&preamble, &glEp0Buffer_Tx[i], 1, 0);
    			};
*/
#endif

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

#if 0
/*
    		  	I2C_Addr = glEp0Buffer_Rx[1];
    			for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			{
        			//write byte
        	        preamble.length    = 2;
        	        preamble.buffer[0] = 0xE0; //write h70;
        	        preamble.buffer[1] = glEp0Buffer_Rx[4+i*2]; //reg to write
        	        preamble.ctrlMask  = 0x0000;

                    // NOTE: Emulation does not talk to I2C
        	        //CyU3PI2cTransmitBytes (&preamble, &glEp0Buffer_Rx[5+i*2], 1, 0);
    			};
*/
#endif

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

                // NOTE: Emulation does not talk to device
    			//for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			//{
    			//	if(glEp0Buffer_Rx[4+i] & 0x01) CyU3PGpioSetValue (GPIO_LNA0, CyTrue); else CyU3PGpioSetValue (GPIO_LNA0, CyFalse); //LNA0
    			//	if(glEp0Buffer_Rx[4+i] & 0x02) CyU3PGpioSetValue (GPIO_LNA1, CyTrue); else CyU3PGpioSetValue (GPIO_LNA1, CyFalse); //LNA1
    			//};

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

                // NOTE: Emulation does not talk to device
    			//for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			//{
    			//	if(glEp0Buffer_Rx[4+i] & 0x01) CyU3PGpioSetValue (GPIO_PA0, CyTrue); else CyU3PGpioSetValue (GPIO_PA0, CyFalse); //PA0
    			//};

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

                // NOTE: Emulation does not talk to device
		        //for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			//{
    			//	//change reset pin level
    			//	if(glEp0Buffer_Rx[4+i]) CyU3PGpioSetValue (GPIO_RESET, CyTrue); //Reset high
    			//		else CyU3PGpioSetValue (GPIO_RESET, CyFalse); //Reset low
    			//};

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

                // NOTE: Emulation does not talk to device
  		        //CyU3PGpioSetValue (GPIO_SPI_SSN, CyFalse);
    			//for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			//{
        		//  	CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4+i], 1);//read reg addr
        		//  	CyU3PSpiReceiveWords (&glEp0Buffer_Tx[i], 1);//data
    			//};
    			//CyU3PGpioSetValue (GPIO_SPI_SSN, CyTrue);

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

                // NOTE: Emulation does not talk to device
    		  	//CyU3PGpioSetValue (GPIO_SPI_SSN, CyFalse);
				//for(i=0; i<glEp0Buffer_Rx[2]; i++)
				//{
				//  CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4+2*i], glEp0Buffer_Rx[2]*2);//reg + data
				//}
    		  	////CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4], glEp0Buffer_Rx[2]*2);//data
    		  	//CyU3PGpioSetValue (GPIO_SPI_SSN, CyTrue);

    		break;

    	  case	CMD_GET_INFO:

	          glEp0Buffer_Tx_Expected = 52;

    		  serial_num = (uint8_t *)CyFxUSBSerialDscr;

    		  CyU3PGpioGetValue (GPIO_TX_ID, &tx_id);
    		  glEp0Buffer_Tx[0] = tx_id;
    		  //CyU3PGpifGetSMState(&glEp0Buffer_Tx[1]);
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

                // NOTE: Emulation does not talk to device
    			//for(i=0; i<glEp0Buffer_Rx[2]; i++)
    			//{
				//	CyU3PGpioSetValue (GPIO_SBEN, CyFalse);
				//	CyU3PSpiTransmitWords (&glEp0Buffer_Rx[4]+i*(ADF_WORDLEN/8), (ADF_WORDLEN/8));//data
				//	CyU3PGpioSetValue (GPIO_SBEN, CyTrue);
    			//}

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
                    (void)CyU3PDeviceGpioOverride (gpio_num, CyTrue);
                    (void)CyU3PGpioSetSimpleConfig(gpio_num, &gpioConfig);
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
                    (void)CyU3PDeviceGpioOverride (gpio_num, CyTrue);
                    (void)CyU3PGpioSetSimpleConfig(gpio_num, &gpioConfig);
     		        CyU3PGpioSetValue(gpio_num, pin);
                    if(pin) glEp0Buffer_Tx[0] = 1;
                    else    glEp0Buffer_Tx[0] = 0;
                }

    		  break;
    	}

    	//config_led = 1;
    	break;

    default:
        /* This is unknown request. */
        isHandled = CyFalse;
        break;
    }
    
    return isHandled;
}

/* Callback to handle the USB setup requests. */
CyBool_t
CyFxBulkSrcSinkApplnUSBSetupCB (
        uint32_t setupdat0, /* SETUP Data 0 */
        uint32_t setupdat1  /* SETUP Data 1 */
    )
{
    /* Fast enumeration is used. Only requests addressed to the interface, class,
     * vendor and unknown control requests are received by this function.
     * This application does not support any class or vendor requests. */

    uint8_t  bRequest, bReqType;
    uint8_t  bType, bTarget;
    uint16_t wValue, wIndex;  //, wLength;
    CyBool_t isHandled = CyFalse;
//    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Decode the fields from the setup request. */
    bReqType = (setupdat0 & CY_U3P_USB_REQUEST_TYPE_MASK);
    bType    = (bReqType & CY_U3P_USB_TYPE_MASK);
    bTarget  = (bReqType & CY_U3P_USB_TARGET_MASK);
    bRequest = ((setupdat0 & CY_U3P_USB_REQUEST_MASK) >> CY_U3P_USB_REQUEST_POS);
    wValue   = ((setupdat0 & CY_U3P_USB_VALUE_MASK)   >> CY_U3P_USB_VALUE_POS);
    wIndex   = ((setupdat1 & CY_U3P_USB_INDEX_MASK)   >> CY_U3P_USB_INDEX_POS);
//    wLength  = ((setupdat1 & CY_U3P_USB_LENGTH_MASK)  >> CY_U3P_USB_LENGTH_POS);

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
                CyU3PUsbAckSetup ();

                /* As we have only one interface, the link can be pushed into U2 state as soon as
                   this interface is suspended.
                 */
                if (bRequest == CY_U3P_USB_SC_SET_FEATURE)
                {
                    glDataTransStarted = CyFalse;
                    glForceLinkU2      = CyTrue;
                }
                else
                {
                    glForceLinkU2 = CyFalse;
                }
            }
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
                if (wIndex == CY_FX_EP_PRODUCER)
                {
                    CyU3PDmaChannelReset (&glChHandleBulkSink);
                    CyU3PUsbFlushEp(CY_FX_EP_PRODUCER);
                    CyU3PUsbResetEp (CY_FX_EP_PRODUCER);
                    CyU3PDmaChannelSetXfer (&glChHandleBulkSink, CY_FX_APP_DMA_TX_SIZE);
                    CyU3PUsbStall (wIndex, CyFalse, CyTrue);
                    isHandled = CyTrue;
                    CyU3PUsbAckSetup ();
                }

                if (wIndex == CY_FX_EP_CONSUMER)
                {
                    CyU3PDmaChannelReset (&glChHandleBulkSrc);
                    CyU3PUsbFlushEp(CY_FX_EP_CONSUMER);
                    CyU3PUsbResetEp (CY_FX_EP_CONSUMER);
                    CyU3PDmaChannelSetXfer (&glChHandleBulkSrc, CY_FX_APP_DMA_TX_SIZE);
                    CyU3PUsbStall (wIndex, CyFalse, CyTrue);
                    isHandled = CyTrue;
                    CyU3PUsbAckSetup ();
                }
            }
        }
    }

    /* Handle supported vendor requests. */
    if ((bType == CY_U3P_USB_VENDOR_RQT) && (bTarget == CY_U3P_USB_TARGET_DEVICE))
    {
        isHandled = CyFxBulkSrcSinkApplnUSBVendorCB( setupdat0, setupdat1 );
    }

    return isHandled;
}

/* This is the callback function to handle the USB events. */
void
CyFxBulkSrcSinkApplnUSBEventCB (
    CyU3PUsbEventType_t evtype, /* Event type */
    uint16_t            evdata  /* Event data */
    )
{
    static uint32_t num_connect    = 0;
    static uint32_t num_disconnect = 0;

    switch (evtype)
    {
    case CY_U3P_USB_EVENT_CONNECT:
      ++num_connect;
      //CyU3PDebugPrint (CY_FX_DEBUG_PRIORITY, "CY_U3P_USB_EVENT_CONNECT detected (%d)\n\r",
      //                 num_connect);
      break;

    case CY_U3P_USB_EVENT_SETCONF:
        /* If the application is already active
         * stop it before re-enabling. */
        if (glIsApplnActive)
        {
            CyFxBulkSrcSinkApplnStop ();
        }

        /* Start the source sink function. */
        CyFxBulkSrcSinkApplnStart ();
        break;

    case CY_U3P_USB_EVENT_RESET:
    case CY_U3P_USB_EVENT_DISCONNECT:
        glForceLinkU2 = CyFalse;

        /* Stop the source sink function. */
        if (glIsApplnActive)
        {
            CyFxBulkSrcSinkApplnStop ();
        }
        glDataTransStarted = CyFalse;

        if (evtype == CY_U3P_USB_EVENT_DISCONNECT) {
            ++num_disconnect;
            //CyU3PDebugPrint (CY_FX_DEBUG_PRIORITY, "CY_U3P_USB_EVENT_DISCONNECT detected (%d)\n\r",
            //                 num_disconnect);
        }
        break;

    case CY_U3P_USB_EVENT_EP0_STAT_CPLT:
        glEp0StatCount++;
        break;

    case CY_U3P_USB_EVENT_VBUS_REMOVED:
        if (StandbyModeEnable)
        {
            TriggerStandbyMode = CyTrue;
            StandbyModeEnable  = CyFalse;
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
CyFxBulkSrcSinkApplnLPMRqtCB (
        CyU3PUsbLinkPowerMode link_mode)
{
    return CyTrue;
}

/* This function configures the GPIOs
 */
void
CyFxConfigureGPIO (void)
{
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    CyU3PGpioClock_t  gpioClock;
	CyU3PGpioSimpleConfig_t gpioConfig;

	/* Initialize the GPIO block. If we are transitioning from the boot app, we can verify whether the GPIO
	   state is retained. */
	gpioClock.fastClkDiv = 2;
	gpioClock.slowClkDiv = 32;
	gpioClock.simpleDiv  = CY_U3P_GPIO_SIMPLE_DIV_BY_16;
	gpioClock.clkSrc     = CY_U3P_SYS_CLK_BY_2;
	gpioClock.halfDiv    = 0;
	apiRetStatus = CyU3PGpioInit (&gpioClock, NULL);

	/* Override GPIO 54 as this pin is associated with UART CTS signal.
	 * The IO cannot be selected as GPIO by CyU3PDeviceConfigureIOMatrix call
	 * as it is part of the GPIF IOs. Override API call must be made with
	 * caution as this will change the functionality of the pin. If the IO
	 * line is used as part of UART and is connected to some external device,
	 * then the line will no longer behave as a UART CTS line.. Here CTS line is
	 * not used and so it is safe to override.  */
    apiRetStatus = CyU3PDeviceGpioOverride (GPIO_LED1, CyTrue);
	if (apiRetStatus != 0)
	{
		//CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PDeviceGpioOverride failed, error code = %d\n", apiRetStatus);
		CyFxAppErrorHandler(apiRetStatus,45);
	}

	/* Configure GPIO 54 as output */
	gpioConfig.outValue = CyTrue;
	gpioConfig.driveLowEn = CyTrue;
	gpioConfig.driveHighEn = CyTrue;
	gpioConfig.inputEn = CyFalse;
	gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
	apiRetStatus = CyU3PGpioSetSimpleConfig(GPIO_LED1, &gpioConfig);	/* Set GPIO54 as an output pin to drive the LED */
	if (apiRetStatus != CY_U3P_SUCCESS)
	{
		//CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PGpioSetSimpleConfig failed, error code = %d\n", apiRetStatus);
		CyFxAppErrorHandler(apiRetStatus,46);
	}
}

/* This function initializes the USB Module, sets the enumeration descriptors.
 * This function does not start the bulk streaming and this is done only when
 * SET_CONF event is received. */
void
CyFxBulkSrcSinkApplnInit (void)
{
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    CyBool_t no_renum = CyFalse;

    //CyFxConfigurePPort();

    CyFxConfigureGPIO();

    ///* Start the state machine. */
    //apiRetStatus = CyU3PGpifSMStart (START, ALPHA_START);
    //if (apiRetStatus != CY_U3P_SUCCESS)
    //{
    //    //CyU3PDebugPrint (4, "CyU3PGpifSMStart failed, Error Code = %d\n",apiRetStatus);
    //    CyFxAppErrorHandler(apiRetStatus,9);
    //}

    /* Start the USB functionality. */
    apiRetStatus = CyU3PUsbStart();
    if (apiRetStatus == CY_U3P_ERROR_NO_REENUM_REQUIRED)
        no_renum = CyTrue;
    else if (apiRetStatus != CY_U3P_SUCCESS)
    {
        //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "CyU3PUsbStart failed to Start, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,20);
    }

    /* The fast enumeration is the easiest way to setup a USB connection,
     * where all enumeration phase is handled by the library. Only the
     * class / vendor requests need to be handled by the application. */
    CyU3PUsbRegisterSetupCallback(CyFxBulkSrcSinkApplnUSBSetupCB, CyTrue);

    /* Setup the callback to handle the USB events. */
    CyU3PUsbRegisterEventCallback(CyFxBulkSrcSinkApplnUSBEventCB);

    /* Register a callback to handle LPM requests from the USB 3.0 host. */
    CyU3PUsbRegisterLPMRequestCallback(CyFxBulkSrcSinkApplnLPMRqtCB);

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
        //CyU3PDebugPrint (CY_FX_DEBUG_PRIORITY, "USB set string descriptor failed, Error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus,61);
    }

    /* Register a buffer into which the USB driver can log relevant events. */
    gl_UsbLogBuffer = (uint8_t *)CyU3PDmaBufferAlloc (CYFX_USBLOG_SIZE);
    if (gl_UsbLogBuffer)
        CyU3PUsbInitEventLog (gl_UsbLogBuffer, CYFX_USBLOG_SIZE);

    //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "About to connect to USB host\r\n");

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
            CyFxBulkSrcSinkApplnStop ();
        CyFxBulkSrcSinkApplnStart ();
    }
    //CyU3PDebugPrint (CY_FX_DEBUG_PRIORITY, "CyFxBulkSrcSinkApplnInit complete\r\n");
}

/* Entry function for the BulkSrcSinkAppThread. */
void
BulkSrcSinkAppThread_Entry (
        uint32_t input)
{
    CyU3PReturnStatus_t stat;
    uint32_t eventMask = CYFX_USB_CTRL_TASK | CYFX_USB_HOSTWAKE_TASK;   /* Mask representing events that we are interested in. */
    uint32_t eventStat;                                                 /* Variable to hold current status of the events. */
    uint16_t prevUsbLogIndex = 0, tmp1, tmp2;
    CyU3PUsbLinkPowerMode curState;

    /* Initialize the debug module */
    CyFxBulkSrcSinkApplnDebugInit();
    //CyU3PDebugPrint (1, "UART debug initialized\r\n");

    //CyFxI2cInit ();
    //CyFxSpiInit (LMS6_WORDLEN);

    /* Initialize the application */
    CyFxBulkSrcSinkApplnInit();

    for (;;)
    {
    	/* LED toggling function start */
    	if(on_time != 0)
    	{
			CyU3PGpioSetValue (GPIO_LED1, CyFalse);			/* Turn LED-ON	*/
			CyU3PThreadSleep(on_time);						/* ON-time	*/
    	}

    	if (off_time != 0)
    	{
			CyU3PGpioSetValue (GPIO_LED1, CyTrue);			/* Turn LED-OFF */
			CyU3PThreadSleep(off_time);						/* OFF-time	*/
    	}
    	/* LED toggling function end  */

        /* The following call will block until at least one of the events enabled in eventMask is received.
           The eventStat variable will hold the events that were active at the time of returning from this API.
           The CLEAR flag means that all events will be atomically cleared before this function returns.
          
           We cause this event wait to time out every 10 milli-seconds, so that we can periodically get the FX3
           device out of low power modes.
         */
        stat = CyU3PEventGet (&glBulkLpEvent, eventMask, CYU3P_EVENT_OR_CLEAR, &eventStat, 10);
        if (stat == CY_U3P_SUCCESS)
        {
            /* If the HOSTWAKE task is set, send a DEV_NOTIFICATION (FUNCTION_WAKE) or remote wakeup signalling
               based on the USB connection speed. */
            if (eventStat & CYFX_USB_HOSTWAKE_TASK)
            {
                CyU3PThreadSleep (1000);
                if (CyU3PUsbGetSpeed () == CY_U3P_SUPER_SPEED)
                    stat = CyU3PUsbSendDevNotification (1, 0, 0);
                else
                    stat = CyU3PUsbDoRemoteWakeup ();

                if (stat != CY_U3P_SUCCESS)
                    //CyU3PDebugPrint (2, "Remote wake attempt failed with code: %d\r\n", stat);
                    CyFxAppErrorHandler(stat,65);
            }
        }

        /* Try to get the USB 3.0 link back to U0. */
        if (glForceLinkU2)
        {
            stat = CyU3PUsbGetLinkPowerState (&curState);
            while ((glForceLinkU2) && (stat == CY_U3P_SUCCESS) && (curState == CyU3PUsbLPM_U0))
            {
                /* Repeatedly try to go into U2 state.*/
                CyU3PUsbSetLinkPowerState (CyU3PUsbLPM_U2);
                CyU3PThreadSleep (5);
                stat = CyU3PUsbGetLinkPowerState (&curState);
            }
        }
        else
        {

            /* Once data transfer has started, we keep trying to get the USB link to stay in U0. If this is done
               before data transfers have started, there is a likelihood of failing the TD 9.24 U1/U2 test. */
            if ((CyU3PUsbGetSpeed () == CY_U3P_SUPER_SPEED) && (glDataTransStarted))
            {
                /* If the link is in U1/U2 states, try to get back to U0. */
                stat = CyU3PUsbGetLinkPowerState (&curState);
                while ((stat == CY_U3P_SUCCESS) && (curState >= CyU3PUsbLPM_U1) && (curState <= CyU3PUsbLPM_U3) &&
                        (glDataTransStarted))
                {
                    CyU3PUsbSetLinkPowerState (CyU3PUsbLPM_U0);
                    CyU3PThreadSleep (1);
                    stat = CyU3PUsbGetLinkPowerState (&curState);
                }
            }
        }

        if (TriggerStandbyMode)
        {
            TriggerStandbyMode = CyFalse;

            CyU3PConnectState (CyFalse, CyTrue);
            CyU3PUsbStop ();
            CyU3PDebugDeInit ();
            CyU3PUartDeInit ();

            /* VBus has been turned off. Go into standby mode and wait for VBus to be turned on again.
               The I-TCM content and GPIO register state will be backed up in the memory area starting
               at address 0x40060000. */
            stat = CyU3PSysEnterStandbyMode (CY_U3P_SYS_USB_VBUS_WAKEUP_SRC, CY_U3P_SYS_USB_VBUS_WAKEUP_SRC,
                    (uint8_t *)0x40060000);
            if (stat != CY_U3P_SUCCESS)
            {
                CyFxBulkSrcSinkApplnDebugInit ();
                //CyU3PDebugPrint(CY_FX_DEBUG_PRIORITY, "Enter standby returned %d\r\n", stat);
                CyFxAppErrorHandler (stat, 62);
            }

            /* If the entry into standby succeeds, the CyU3PSysEnterStandbyMode function never returns. The
               firmware application starts running again from the main entry point. Therefore, this code
               will never be executed. */
            CyFxAppErrorHandler (1, 63);
        }
        else
        {
            /* Compare the current USB driver log index against the previous value. */
            tmp1 = CyU3PUsbGetEventLogIndex ();
            if (tmp1 != prevUsbLogIndex)
            {
                tmp2 = prevUsbLogIndex;
                while (tmp2 != tmp1)
                {
                    tmp2++;
                    if (tmp2 == CYFX_USBLOG_SIZE)
                        tmp2 = 0;
                }
            }

            /* Store the current log index. */
            prevUsbLogIndex = tmp1;
        }
    }
}

/* Application define function which creates the threads. */
void
CyFxApplicationDefine (
        void)
{
    void *ptr = NULL;
    uint32_t ret = CY_U3P_SUCCESS;

    /* Create an event flag group that will be used for signalling the application thread. */
    ret = CyU3PEventCreate (&glBulkLpEvent);
    if (ret != 0)
    {
        CyFxAppErrorHandler(ret,64);
    }

    /* Allocate the memory for the threads */
    ptr = CyU3PMemAlloc (CY_FX_APP_THREAD_STACK);

    /* Create the thread for the application */
    ret = CyU3PThreadCreate (&bulkSrcSinkAppThread,                /* App thread structure */
                          "21:Bulk_src_sink",                      /* Thread ID and thread name */
                          BulkSrcSinkAppThread_Entry,              /* App thread entry function */
                          0,                                       /* No input parameter to thread */
                          ptr,                                     /* Pointer to the allocated thread stack */
                          CY_FX_APP_THREAD_STACK,                  /* App thread stack size */
                          CY_FX_APP_THREAD_PRIORITY,               /* App thread priority */
                          CY_FX_APP_THREAD_PRIORITY,               /* App thread priority */
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

    /* Initialize the device */
    CyU3PSysClockConfig_t clockConfig;
    clockConfig.setSysClk400  = CyTrue;
    clockConfig.cpuClkDiv     = 2;
    clockConfig.dmaClkDiv     = 2;
    clockConfig.mmioClkDiv    = 2;
    clockConfig.useStandbyClk = CyFalse;
    clockConfig.clkSrc         = CY_U3P_SYS_CLK;
    status = CyU3PDeviceInit (&clockConfig);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Initialize the caches. Enable Instruction Cache and Disable Data caches. */
    status = CyU3PDeviceCacheControl (CyTrue, CyFalse, CyFalse);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Configure the IO matrix for the device. On the FX3 DVK board, the COM port 
     * is connected to the IO(53:56). This means that either DQ32 mode should be
     * selected or lppMode should be set to UART_ONLY. Here we are choosing
     * UART_ONLY configuration. */
    io_cfg.isDQ32Bit = CyFalse;
    io_cfg.useUart   = CyTrue;
    io_cfg.useI2C    = CyFalse;
    io_cfg.useI2S    = CyFalse;
    io_cfg.useSpi    = CyFalse;
    io_cfg.lppMode   = CY_U3P_IO_MATRIX_LPP_UART_ONLY;

    io_cfg.gpioSimpleEn[0]  = 0;
    io_cfg.gpioSimpleEn[1]  = 0;
    io_cfg.gpioComplexEn[0] = 0;
    io_cfg.gpioComplexEn[1] = 0;
    status = CyU3PDeviceConfigureIOMatrix (&io_cfg);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* This is a non returnable call for initializing the RTOS kernel */
    CyU3PKernelEntry ();

    /* Dummy return to make the compiler happy */
    return 0;

handle_fatal_error:

    /* Cannot recover from this error. */
    while (1);
}

/* [ ] */

