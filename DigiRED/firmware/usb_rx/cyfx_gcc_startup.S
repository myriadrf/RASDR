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

# Cypress FX3 Firmware Startup code

.section .text
.code 32

.global jump
jump:
    bx  R0

.global CyU3PToolChainInit
CyU3PToolChainInit:

# clear the BSS area
__main:
	mov	R0, #0
	ldr	R1, =_bss_start
	ldr	R2, =_bss_end
1:	cmp	R1, R2
	strlo	R0, [R1], #4
	blo	1b

	b	main


.global __user_initial_stackheap
__user_initial_stackheap:

# The tool chain is not expected to place the stack.
# No heap is expected to be used by USB 3.0 platform drivers.
# Place them as required by the user code
.if  INTER == TRUE
    bx      lr                 
.else
    mov     pc, lr             
.endif

.end

# []
