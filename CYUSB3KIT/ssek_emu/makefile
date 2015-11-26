## Copyright Cypress Semiconductor Corporation, 2010-2011,
## All Rights Reserved
## UNPUBLISHED, LICENSED SOFTWARE.
##
## CONFIDENTIAL AND PROPRIETARY INFORMATION
## WHICH IS THE PROPERTY OF CYPRESS.
##
## Use of this file is governed
## by the license agreement included in the file
##
##      <install>/license/license.txt
##
## where <install> is the Cypress software
## installation root directory path.
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

FX3FWROOT=../..
FX3PFWROOT=../../u3p_firmware

all:compile

include $(FX3FWROOT)/common/fx3_build_config.mak

MODULE = cyfxbulksrcsink


SOURCE += $(MODULE).c
SOURCE += cyfxbulkdscr.c

C_OBJECT=$(SOURCE:%.c=./%.o)
A_OBJECT=$(SOURCE_ASM:%.S=./%.o)

EXES = $(MODULE).$(EXEEXT)

$(MODULE).$(EXEEXT): $(A_OBJECT) $(C_OBJECT)
	$(LINK)

$(C_OBJECT) : %.o : %.c cyfxbulksrcsink.h
	$(COMPILE)

$(A_OBJECT) : %.o : %.S
	$(ASSEMBLE)

clean:
	rm -f ./$(MODULE).$(EXEEXT)
	rm -f ./$(MODULE).map
	rm -f ./*.o

compile: $(C_OBJECT) $(A_OBJECT) $(EXES)

#[]#
