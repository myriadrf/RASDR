/*
 ## Cypress USB 3.0 Platform header file (cyfxbulksrcsink.h)
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
 ## ===========================
*/

/* This file contains the constants used by the bulk source sink application example */

#ifndef _INCLUDED_CYFXBULKSRCSINK_H_
#define _INCLUDED_CYFXBULKSRCSINK_H_

#include "cyu3types.h"
#include "cyu3usbconst.h"
#include "cyu3externcstart.h"

#define CY_FX_BULKSRCSINK_DMA_TX_SIZE        (0)                       /* DMA transfer size is set to infinite */
#define CY_FX_BULKSRCSINK_THREAD_STACK       (0x1000)                  /* Bulk loop application thread stack size */
#define CY_FX_BULKSRCSINK_THREAD_PRIORITY    (8)                       /* Bulk loop application thread priority */

/* TODO: User can change the data pattern bleow that is sent by FX3 to the host */
#define CY_FX_BULKSRCSINK_PATTERN            (0xAA)                    /* 8-bit pattern to be loaded to the source buffers. */

/* Endpoint and socket definitions for the bulk source sink application */

/* To change the producer and consumer EP enter the appropriate EP numbers for the #defines.
 * In the case of IN endpoints enter EP number along with the direction bit.
 * For eg. EP 6 IN endpoint is 0x86
 *     and EP 6 OUT endpoint is 0x06.
 * To change sockets mention the appropriate socket number in the #defines. */

/* Note: For USB 2.0 the endpoints and corresponding sockets are one-to-one mapped
         i.e. EP 1 is mapped to UIB socket 1 and EP 2 to socket 2 so on */

#define CY_FX_EP_PRODUCER               0x01    /* EP 1 OUT */
#define CY_FX_EP_CONSUMER               0x81    /* EP 1 IN */

#define CY_FX_EP_PRODUCER_SOCKET        CY_U3P_UIB_SOCKET_PROD_1    /* Socket 1 is producer */
#define CY_FX_EP_CONSUMER_SOCKET        CY_U3P_UIB_SOCKET_CONS_1    /* Socket 1 is consumer */

/* Burst mode definitions: Only for super speed operation. The maximum burst mode 
 * supported is limited by the USB hosts available. The maximum value for this is 16
 * and the minimum (no-burst) is 1. */


/* Burst length in 1 KB packets. Only applicable to USB 3.0. */
#ifndef CY_FX_EP_BURST_LENGTH

/* TODO: Modify the burst length from 1 to 16. Setting less bandwidth will give less
  USB throughput. Changing the burst length will also change the buffer size */
#define CY_FX_EP_BURST_LENGTH           (16)
#endif

/*TODO: Modify the DMA multiplier to change the buffer size: Set the value from 1 to 3 */
#define CY_FX_DMA_MULTIPLIER			(2)

/* Size of each DMA buffer. This should ideally be set to 2X the EP burst size. */
#ifndef CY_FX_BULKSRCSINK_DMA_BUF_SIZE
#define CY_FX_BULKSRCSINK_DMA_BUF_SIZE  (CY_FX_DMA_MULTIPLIER * CY_FX_EP_BURST_LENGTH * 1024)
#endif

/* Number of DMA buffers used for the DMA channel. */
#ifndef CY_FX_BULKSRCSINK_DMA_BUF_COUNT
#define CY_FX_BULKSRCSINK_DMA_BUF_COUNT (2)
#endif

#define LED_GPIO						(54)				/* Configure GPIO54 for LED blinking */
#define LED_BLINK_RATE_CHANGE			(0xAA)				/* Vendor command for changing the ON-time and OFF-time
															 *of LED in terms of 100ms */

#define SUPERSPEED_BLINK_RATE			(50)				/*Sets the blink rate of LED in terms of milliseconds
															 *when connected to 3.0 port*/

#define CY_FX_FULL_SPEED_EP_SIZE		(64)				/* Sets the end-point size to 64 bytes for full speed */
#define CY_FX_HIGH_SPEED_EP_SIZE		(512)				/* Sets the end-point size to 512 bytes for high speed */
#define CY_FX_SUPER_SPEED_EP_SIZE		(1024)				/* Sets the end-point size to 512 bytes for SuperSpeed */
#define CY_FX_DEBUG_PRIORITY			(4)					/* Sets the debug print priority level */

/* Extern definitions for the USB Descriptors */
extern const uint8_t CyFxUSB20DeviceDscr[];
extern const uint8_t CyFxUSB30DeviceDscr[];
extern const uint8_t CyFxUSBDeviceQualDscr[];
extern const uint8_t CyFxUSBFSConfigDscr[];
extern const uint8_t CyFxUSBHSConfigDscr[];
extern const uint8_t CyFxUSBBOSDscr[];
extern const uint8_t CyFxUSBSSConfigDscr[];
extern const uint8_t CyFxUSBStringLangIDDscr[];
extern const uint8_t CyFxUSBManufactureDscr[];
extern const uint8_t CyFxUSBProductDscr[];
extern const uint8_t CyFxUsbOSDscr[];

#include <cyu3externcend.h>

#endif /* _INCLUDED_CYFXBULKSRCSINK_H_ */

/*[]*/
