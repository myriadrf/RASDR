/**
-- ----------------------------------------------------------------------------	
-- FILE:	LMS_defines.h
-- DESCRIPTION:	defines 
-- DATE:	2013.11.14
-- AUTHOR(s):	Lime Microsystems
-- REVISION: v0r4
-- ----------------------------------------------------------------------------	

*/

#ifndef _LMS_DEFINES_H_
#define _LMS_DEFINES_H_

enum eLMS_DEV {LMS_DEV_UNKNOWN, LMS_DEV_EVB6, LMS_DEV_DIGIGREEN, LMS_DEV_DIGIRED, LMS_DEV_EVB7, LMS_DEV_ZIPPER, LMS_DEV_ZIPPER2};

enum eEXP_BOARD {EXP_BOARD_UNKNOWN, EXP_BOARD_UNSUPPORTED, EXP_BOARD_NO, EXP_BOARD_MYRIAD1, EXP_BOARD_MYRIAD2};

#define LMS_PROTOCOL_VER		1
#define LMS_CTRL_PACKET_SIZE	64

//commands
#define CMD_GET_INFO	0x00

#define CMD_SI5356_WR 	0x11
#define CMD_SI5356_RD	0x12
#define CMD_SI5351_WR 	0x13
#define CMD_SI5351_RD	0x14

#define CMD_LMS_RST		0x20
#define CMD_LMS7002_WR	0x21
#define CMD_LMS7002_RD	0x22
#define CMD_LMS6002_WR	0x23
#define CMD_LMS6002_RD	0x24


//#define CMD_LMS_LNA		0x2A bus MCU_WR
//#define CMD_LMS_PA		0x2B bus MCU_RD
#define CMD_PROG_MCU	0x2C

#define CMD_ADF4002_WR	0x31

//#define CMD_MIPI_RFFE_WR	0x41
//#define CMD_MIPI_RFFE_RD	0x42

#define CMD_PE636040_WR		0x41
#define CMD_PE636040_RD		0x42

#define CMD_MYRIAD_GPIO_WR	0x51
#define CMD_MYRIAD_GPIO_RD	0x52

//status
#define STATUS_COMPLETED_CMD	1
#define STATUS_UNKNOWN_CMD		2
#define STATUS_BUSY_CMD			3
#define STATUS_MANY_BLOCKS_CMD	4
#define STATUS_ERROR_CMD		5
#define STATUS_WRONG_ORDER_CMD	6

//CMD_LMS_RST
#define LMS_RST_DEACTIVATE	0
#define LMS_RST_ACTIVATE	1
#define LMS_RST_PULSE		2


typedef struct{
    unsigned char Command;
    unsigned char Status;
	unsigned char Data_blocks;
	unsigned char reserved[5];
}tLMS_Ctrl_Header;

typedef struct{
    tLMS_Ctrl_Header Header;
	unsigned char Data_field[LMS_CTRL_PACKET_SIZE - sizeof(tLMS_Ctrl_Header)];
}tLMS_Ctrl_Packet;

#endif
