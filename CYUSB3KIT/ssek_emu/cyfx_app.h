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

/* This file contains the constants used by the bulk source sink application example */

#ifndef _INCLUDED_CYFX_APP_H_
#define _INCLUDED_CYFX_APP_H_

#include "cyu3types.h"
#include "cyu3usbconst.h"
#include "cyu3externcstart.h"

#define CY_FX_APP_GPIF_16_32BIT_CONF_SELECT (0)
#define CY_FX_APP_DMA_TX_SIZE        (0)                       /* DMA transfer size is set to infinite */
#define CY_FX_APP_THREAD_STACK       (0x1000)                  /* Application thread stack size */
#define CY_FX_APP_THREAD_PRIORITY    (8)                       /* Application thread priority */
#define CY_FX_APP_PATTERN            (0xAA)                    /* 8-bit pattern to be loaded to the source buffers. */

/* Endpoint and socket definitions for the application */

/* To change the Producer and Consumer EP enter the appropriate EP numbers for the #defines.
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

/* Used with FX3 Silicon. */
#define CY_FX_PRODUCER_PPORT_SOCKET    CY_U3P_PIB_SOCKET_0    /* P-port Socket 0 is producer */
#define CY_FX_CONSUMER_PPORT_SOCKET    CY_U3P_PIB_SOCKET_3    /* P-port Socket 3 is consumer */

/* Burst mode definitions: Only for super speed operation. The maximum burst mode 
 * supported is limited by the USB hosts available. The maximum value for this is 16
 * and the minimum (no-burst) is 1. */


/* Burst length in 1 KB packets. Only applicable to USB 3.0. */
#define CY_FX_EP_BURST_LENGTH           (4)                       /* 1 to 16.  More is faster, but uses more buffer memory */
#define CY_FX_DMA_MULTIPLIER			(2)                       /* 1 to 3 */

/* Size of each DMA buffer. This should ideally be set to 2X the EP burst size. */
#define CY_FX_APP_DMA_BUF_SIZE			(CY_FX_DMA_MULTIPLIER * CY_FX_EP_BURST_LENGTH * 1024)
/* Number of DMA buffers used for the DMA channel. */
#define CY_FX_APP_DMA_BUF_COUNT			(2)

#define XSPEED_BLINK_PERIOD             (1000)				/* in ms units */
#define FULLSPEED_BLINK_ON_TIME         (100)				/* in ms units */
#define HIGHSPEED_BLINK_ON_TIME         (900)				/* in ms units */
#define SUPERSPEED_BLINK_ON_TIME        (500)				/* in ms units */

/* General Base Sizes for the different endpoints */
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
extern const uint8_t CyFxUSBSerialDscr[];
extern const uint8_t CyFxUSBOSDscr[];

#include <cyu3externcend.h>

#endif /* _INCLUDED_CYFX_APP_H_ */

/*[]*/
