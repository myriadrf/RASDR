/*
 ## Cypress USB 3.0 Platform linker script file (fx3.ld) for CY3011 (256KB RAM)
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

/*
   This is the GNU linker file for FX3 memory map.
   The FX3 device has 16 KB of I-TCM memory which can be used for
   code (typically ISRs) and 256 KB of SYSTEM RAM which is shared
   between code, data and DMA buffers.

   The MODIFIED memory map used for FX3-CY3011 applications is as follows:

   Descriptor area Base: 0x40000000 Size: 12KB
   Code area       Base: 0x40003000 Size: 100KB
   Data area       Base: 0x4001C000 Size: 8KB
   Driver heap     Base: 0x4001F000 Size: 32KB  (Update cyfxtx.c to change this.)
   Buffer area     Base: 0x40027000 Size: 68KB  (Update cyfxtx.c to change this.)
   2-stage boot    Base: 0x40038000 Size: 32KB  (Update cyfxtx.c to change this.)

   Interrupt handlers to be placed in I-TCM (16KB).
   The first 256 bytes of ITCM are reserved for Exception Vectors.
   These vectors will be loaded to ITCM at address 0x0 as part of
   device initialization.

   Kernel stacks are to be placed in the D-TCM (8KB).
   This is done internal to the library as part of CyU3PFirmwareEntry()
   and is not expected to be modified by the FX3 application.
   SYS_STACK       Base: 0x10000000 Size 2KB
   ABT_STACK       Base: 0x10000800 Size 256B
   UND_STACK       Base: 0x10000900 Size 256B
   FIQ_STACK       Base: 0x10000A00 Size 512B
   IRQ_STACK       Base: 0x10000C00 Size 1KB
   SVC_STACK       Base: 0x10001000 Size 4KB
*/

ENTRY(CyU3PFirmwareEntry);

MEMORY
{
    I-TCM       : ORIGIN = 0x100,       LENGTH = 0x3F00
    SYS_MEM     : ORIGIN = 0x40003000   LENGTH = 0x19000
    DATA        : ORIGIN = 0x4001C000   LENGTH = 0x2000
}

SECTIONS
{
	. = 0x100;
	.vectors :
	{
		*(CYU3P_ITCM_SECTION);
                tx_thread_irq_nesting*(.text)
                tx_thread_context*(.text)
                tx_thread_vectored*(.text)
		. = ALIGN(4);
	} >I-TCM

	. = 0x40003000;
	.text :
	{
		*(.text*)
		*(.rodata*)
		*(.constdata)
		*(.emb_text)
		*(CYU3P_EXCEPTION_VECTORS);
		_etext = .;
		. = ALIGN(4);
	} > SYS_MEM

	. = 0x4001C000;
	.data :
	{
		_data = .;
		*(.data*)
		* (+RW, +ZI)
		_edata = .;
		. = ALIGN(4);
	} > DATA

	.bss :
	{
		_bss_start = .;
		*(.bss*)
		. = ALIGN(4);
	} >DATA 
	_bss_end = . ;

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		. = ALIGN(4);
	} > DATA

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		. = ALIGN(4);
	} > DATA
	__exidx_end = .;
}

