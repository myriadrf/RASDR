# change location of fx2libdir if needed
FX2LIBDIR=../fx2lib
FX2LIB = $(FX2LIBDIR)/lib/fx2.lib
LIBS = fx2.lib -L$(FX2LIBDIR)/lib

# change to be your own vid/pid if needed
VID=0x04B4 # default Cypress VID
PID=0x8613 # default Cypress PID

# possible env flags
# -D DEBUG_FIRMWARE - enable stdio & printf on sio-0 (57600 baud)
SDCCFLAGS := $(SDCCFLAGS)

###
# dscr is under 200 bytes currently
# int2jt is under 200 bytes
# 400 bytes for xram

# usbjt 4000 - 100(256) = 3f00 (must lie on page boundary) 
# dscr 3f00 - 100(256) = 3e00 
# xram 3e00 - 200(512) = 3c00 
###

BASENAME = firmware

SOURCES =	serial1.c \
			zt_i2c.c \
			firmware.c \
			app.c
A51_SOURCES = descriptors.a51


include $(FX2LIBDIR)/lib/fx2.mk

cleanall:
	rm -f build/*.{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix,iic,hex} 



