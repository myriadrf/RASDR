/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Board specific Buttons driver header for AVRopendous boards.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Buttons driver
 *        dispatch header located in LUFA/Drivers/Board/Buttons.h.
 */

#ifndef __BUTTON1_USBKEY_H__
#define __BUTTON1_USBKEY_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>

		#include "../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(INCLUDE_FROM_BUTTON1_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
		#endif
		
	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Button mask for the HWB button on the board. */
            #if (defined(__AVR_AT90USB162__)  || defined(__AVR_AT90USB82__))
                #define BUTTON1                      (1 << PD7)
                #define BUTTON1_PORT           PORTD
                #define BUTTON1_PORTDD      DDRD
                #define BUTTON1_PORTIN        PIND
            #endif

            #if (defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__))
                #define BUTTON1                      (1 << PE2)
                #define BUTTON1_PORT           PORTE
                #define BUTTON1_PORTDD      DDRE
                #define BUTTON1_PORTIN        PINE
            #endif

            #if (defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__) ||  \
                    defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) ||  \
                    defined(__AVR_ATmega32U6__))
                #define BUTTON1                      (1 << PE2)
                #define BUTTON1_PORT           PORTE
                #define BUTTON1_PORTDD      DDRE
                #define BUTTON1_PORTIN        PINE
            #endif


		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void BUTTON1_Init(void)
			{
				BUTTON1_PORTDD  &= ~BUTTON1;
				BUTTON1_PORT |=  BUTTON1;
			}

			static inline uint8_t BUTTON1_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t BUTTON1_GetStatus(void)
			{
				return ((BUTTON1_PORTIN & BUTTON1) ^ BUTTON1);
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

