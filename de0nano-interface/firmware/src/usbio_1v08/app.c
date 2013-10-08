/**
 * Copyright (C) 2012,2013 Lime Microsystems Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 **/

#include <fx2regs.h>
#include <fx2macros.h>
#include <delay.h>
#include <autovector.h> 
#include "zt_i2c.h"
#include "serial1.h"
#include <setupdat.h>
#include <serial.h>
#include <eputils.h>

#define SYNCDELAY SYNCDELAY4

//Commands
//I2C FPGA
#define CFG_ADDR 0xAA
#define SC18IS602_ADDR 0x28

#define CMD_CFG_I2C_WR 0x14
#define CMD_CFG_I2C_RD 0x15

#define CMD_SET_LNA 0x30 
#define CMD_SET_PA 0x31

//LMS6002D
#define CMD_LMS_RESET 0x10
#define CMD_LMS_WR 0x16
#define CMD_LMS_RD 0x17

//FX2 Configuration
#define CMD_FX2 0x40

enum
{
	Alt0_BulkIN = 0,
	Alt1_BulkOUT,
	Alt2_BulkINOUT,
	Alt3_IsocIN,
	Alt4_IsocOUT,
	Alt5_IsocIN,
	Alt6_IsocINOUT
};

enum {
	Full_Alt0_BulkIN = 0,
	Full_Alt1_BulkOUT,
	Full_Alt2_IsocIN,
	Full_Alt3_IsocOUT
};

BYTE    Configuration;      // Current configuration
BYTE    AlternateSetting = Alt0_BulkIN;   // Alternate settings

void SC18IS602_Init (void);


//-----------------------------------------------------------------------------
// Task Dispatcher hooks
//   The following hooks are called by the task dispatcher.
//-----------------------------------------------------------------------------

void main_init(void)             // Called once at startup
{
	// Internally clocked (48MHz) sync slave fifo mode.
	// Output to IFCLK is enabled (set bit5 to enable).
	IFCONFIG = 0xE3;
	/*
	IFCLKSRC = 1, Internal FIFOS and GPIF clock selected
	3048MHZ = 1,  Internal FIFO & GPIF clock frequency selected to 48 MHz
	IFCLKOE = 1, IFCLK pin CLOCK output enableb, mode = drive
	IFCLKPOL = 0, Clock has the polarity shown in timing diagrams in manual
	ASYNC = 0, FIFO/GPIF operate synchronously: a clock is supplied either internally; the FIFO control signals function as read and write enable signals for the clock signal.
	GSTATE = 0, Pins which indicate GPIF states is not used
	IFCFG[1:0]=11, Interface mode: Slave FIFO Interface (external master)	
	*/
	SYNCDELAY;
	
	REVCTL = 0x03; //Chip Revision Control
	/*
	DYN_OUT=1, the core disables auto-arming of the endpoints when AUTOOUT transitions from 0 to 1. This feature allows CPU intervention when switching between AUTO and Manual mode without having to reset the endpoint.
	ENH_PKT=1, CPU has capabilities: OUT packets: Skip, Commit, or Edit/Source; IN packets: Skip, Commit, or Edit/Source;
	
	When DYN_OUT=1 and AUTOOUT=1, the CPU is responsible for “priming the pump”by initially arming the endpoints (OUTPKTEND w/SKIP=1 to pass packets to host).
	*/
	SYNCDELAY;  // See TRM...
	
	EP6CFG = 0xE0; // Configure EP6 (IN) for bulk input, quad-buffered (4*512 bytes). 
	SYNCDELAY;
	
	EP2CFG = 0xA0; // Configure EP2 (OUT) for bulk output, quad-buffered (4*512 bytes).
	SYNCDELAY;
	
	// Configure EP1 endpoints
	EP1OUTCFG = 0xA0; //Activates EP1OUT  and set type Bulk
	SYNCDELAY;
	
	EP1INCFG = 0xA0; //Activates EP1IN  and set type Bulk 
	SYNCDELAY;
	
	//Even though these buffers are 64 bytes in size, they are reported as 512 for USB 2.0 compliance.
	//The user must never transfer packets larger than 64 bytes to EP1.
	
	EP1INCS = 0x00;  //BUSY and STALL flags cleared
	SYNCDELAY;

	//not used endpoints
	EP4CFG = (EP4CFG & 0x7F); //deactivate EP4
	SYNCDELAY;
	
	EP8CFG = (EP8CFG & 0x7F); //deactivate EP8
	SYNCDELAY;
	
	//Reset FIFOs
	FIFORESET = 0x80;  SYNCDELAY;  // NAK all requests from host.
	FIFORESET = 0x82;  SYNCDELAY;  // reset EP2
	FIFORESET = 0x84;  SYNCDELAY;  // reset EP4
	FIFORESET = 0x86;  SYNCDELAY;  // reset EP6
	FIFORESET = 0x88;  SYNCDELAY;  // reset EP8
	FIFORESET = 0x00;  SYNCDELAY;  // Restore normal operation.

	EP1OUTBC = 0x40; //Endpoint 1 OUT Byte Count
	SYNCDELAY;

	//Arm all 4 EP2 buffers to "prime the pump" 
	OUTPKTEND = 0x82; //arm first buffer by writing OUTPKTEND w/skip=1
	SYNCDELAY; 
	OUTPKTEND = 0x82; // arm second buffer by writing OUTPKTEND w/skip=1
	SYNCDELAY; 
	OUTPKTEND = 0x82; // arm third buffer by writing OUTPKTEND w/skip=1
	SYNCDELAY; 
	OUTPKTEND = 0x82; // arm fourth buffer by writing OUTPKTEND w/skip=1
	SYNCDELAY; 
 	
	EP6FIFOCFG = 0x0D; // Configure EP6 for AUTOIN, ZEROLENIN, 16bit WORDWIDE (wide bus).
	EP2FIFOCFG = 0x15; // Configure EP2 for AUTOOUT, ZEROLENIN, 16bit wide bus. 
	//Zero length packet will be sent when PKTEND is activated and there are no bytes in the current packet.
	SYNCDELAY;

	//PA config
	PORTACFG = 0x00; // No alternate functions for the PORTA pins
	SYNCDELAY;

	OEA = 0x8A;//set I/O direction for each pin (0 = input, 1 = output)
	IOA = 0x0A;//Values written to IOx appear on the pins which are configured as outputs
	
	FIFOPINPOLAR = 0x00; // All default polarities: SLWR active low,... 
	SYNCDELAY;
    
	// This determines how much data is accumulated in the FIFOs before a
	// USB packet is committed. Use 512 bytes to be sure.
	EP6AUTOINLENH = 0x02; SYNCDELAY;  // MSB
	EP6AUTOINLENL = 0x00; SYNCDELAY;  // LSB
 
	ENABLE_SOF(); // We want to get SOF interrupts 

    remote_wakeup_allowed = TRUE;                 // Enable remote-wakeup

	SC18IS602_Init (); //I2C SPI bridge init
}

void SC18IS602_Init (void) //I2C SPI bridge init
{
	unsigned char i2c_data[2], i2c_addr = SC18IS602_ADDR, i2c_fid;
	
	i2c_fid = 0xF6; //GPIO enable
	i2c_data[0]=0x0F; //enable RESET (GPIO1) and SPI_NCSO (GPIO0)
	i2c_write(i2c_addr, 1, &i2c_fid, 1, i2c_data, 1);
	
	i2c_fid = 0xF7; //GPIO config 
	i2c_data[0]=0x55; //all GPIO push pull
	i2c_write(i2c_addr, 1, &i2c_fid, 1, i2c_data, 1);
	
	i2c_fid = 0xF4; //GPIO write 
	i2c_data[0]=0x03; //RESET and SPI_NCSO high
	i2c_write(i2c_addr, 1, &i2c_fid, 1, i2c_data, 1); 
	
	i2c_fid = 0xF6; //GPIO enable
	i2c_data[0]=0x02; //disable SPI_NCSO (GPIO0) for automatic control
	i2c_write(i2c_addr, 1, &i2c_fid, 1, i2c_data, 1);
	
	i2c_fid = 0xF0; //configure spi
	i2c_data[0]=0x00; // MSB word first, Mode 0 (CPOL = 0, CPHA = 0), 1.843 MHz
	i2c_write(i2c_addr, 1, &i2c_fid, 1, i2c_data, 1);
}

static void ProcessSendData(void)
{
	xdata const unsigned char *src = EP1OUTBUF;
	xdata unsigned char *dest = EP1INBUF;
	unsigned int len = EP1OUTBC;
	unsigned int tx_len = 0;
	unsigned int i;
	unsigned char i2c_data[10], i2c_addr, i2c_fid, IOA_new;
	BOOL btmp;
	
	/*
	fill fifo with 0A
	for testing purposes
	*/
	for(i=0; i<len; i++,src++,dest++)
	{
		*dest=0x0A;
	};

	src = EP1OUTBUF;
	dest = EP1INBUF;
	
	tx_len = 64;

	switch(src[0]) //which command to execute
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
			if(src[1] == 0x10)
			{
				//Reset FIFOs
				FIFORESET = 0x80;  SYNCDELAY;  // NAK all requests from host.
				EP6FIFOCFG = 0x01; SYNCDELAY;
				FIFORESET = 0x06;  SYNCDELAY;  // reset EP6
				FIFORESET = 0x00;  SYNCDELAY;  // Restore normal operation.
				EP6FIFOCFG = 0x0D; SYNCDELAY;
			}
			
		break;

	  case CMD_CFG_I2C_RD:
			//Command format:
			//src[0] : Op code i.e. read from the FPGA Configuration via I2C
			//src[1] : FPGA Configuration I2C address
			//src[2] : Data blocks in buffer
			//src[3] : reserved
			// Data block:
			// src[4] : register address 
			// ...
			
			for(i=0; i<src[2]; i++)
			{
				btmp = i2c_write(((src[1]>>1)&0x7F), 1, &src[4+i], 0, NULL, 0);
				btmp = i2c_read (((src[1]>>1)&0x7F), 1, &dest[i]);	
			};
		break;

	  case CMD_CFG_I2C_WR:
			//Command format:
			//src[0] : Op code i.e. write to the FPGA Configuration via I2C
			//src[1] : FPGA Configuration I2C address
			//src[2] : Data blocks in buffer
			//src[3] : reserved
			// Data block:
			// src[4] : register address
			// src[5] : data to write
			// ...

			for(i=0; i<src[2]; i++)
			{
				btmp = i2c_write(((src[1]>>1)&0x7F), 2, &src[4+i*2], 0, NULL, 1);
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
			
			IOA_new = IOA; //get current register value

			for(i=0; i<src[2]; i++)
			{
				if(src[4+i] & 0x01) IOA_new |= (1<<(1)); else IOA_new &= ~(1<<(1)); //LNA0
				if(src[4+i] & 0x02) IOA_new |= (1<<(3)); else IOA_new &= ~(1<<(3)); //LNA1
			};
			
			IOA = IOA_new; //update gpio

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
			
			IOA_new = IOA;  //get current register value 

			for(i=0; i<src[2]; i++)
			{
				if(src[4+i] & 0x01) IOA_new |= (1<<(7)); else IOA_new &= ~(1<<(7)); //PA0
			};
			
			IOA = IOA_new;  //update gpio

		break;
	  
	  case CMD_LMS_RESET: 
			//Command format:
			//src[0] : Op code i.e. set reset pin level
			//src[1] : FPGA Configuration I2C address
			//src[2] : Data blocks in buffer
			//src[3] : reserved
			// Data block:
			// src[4] : new reset pin level: 0 - low, 1 - high
			// ...

			i2c_addr = src[1]; 

			for(i=0; i<src[2]; i++)
			{
				//change reset pin level
				i2c_fid = 0xF4; //GPIO write 
				if(src[4+i]) i2c_data[0]=0x03; //Reset high
					else i2c_data[0]=0x00; //Reset low 
				i2c_write(i2c_addr, 1, &i2c_fid, 1, i2c_data, 1); 

				if(src[2] >1) delay(10); //delay if more than one change
			};

		break;
		
	  case CMD_LMS_RD:
			//Command format:
			//src[0] : Op code i.e. read from the LMS6002D Configuration via I2C/SPI
			//src[1] : FPGA Configuration I2C address
			//src[2] : Data blocks in buffer
			//src[3] : reserved
			// Data block:
			// src[4] : SPI Instruction (W/R + module addr + register address )
			// ...
			
			i2c_addr = src[1];
			
			for(i=0; i<src[2]; i++)
			{
				//get data from LMS to SC18IS602
				i2c_fid = 0x01; //write spi SS0 to read
				i2c_data[0] = src[4+i]; //read reg addr
				i2c_data[1] = 0x00; //fake byte for spi shift
				i2c_write(i2c_addr, 1, &i2c_fid, 2, i2c_data, 1); 
				
				while (!i2c_read( i2c_addr, 2, i2c_data)); //get data from SC18IS602
				dest[i] = i2c_data[1]; //place data				
				
			};
		break;

	  case CMD_LMS_WR:
			//Command format:
			//src[0] : Op code i.e. read from the LMS6002D Configuration via I2C/SPI
			//src[1] : FPGA Configuration I2C address
			//src[2] : Data blocks in buffer
			//src[3] : reserved
			// Data block:
			// src[4] : SPI Instruction (W/R + module addr + register address )
			// src[5] : SPI Data
			// ...
			
			i2c_addr = src[1];
			
			for(i=0; i<src[2]; i++)
			{
				i2c_fid = 0x01; //write spi SS0
				i2c_data[0] = src[4+i*2]; //write reg addr
				i2c_data[1] = src[4+i*2+1]; //data
				i2c_write(i2c_addr, 1, &i2c_fid, 2, i2c_data, 1);
			};
		break;
	}

	// "Skip" the received OUT packet to "forget" it (see TRM p. 9-26): 
	//SYNCDELAY;  OUTPKTEND = 0x82;
	// Note: Setting EP2BCL would source a packet into the GPIF side. 
	
	// Arm the endpoint. Be sure to set BCH before BCL because BCL access 
	// actually arms the endpoint. 
	SYNCDELAY;
	if(tx_len) EP1INBC = len;
	SYNCDELAY;
} 

void main_loop(void)             // Called repeatedly while the device is idle
{
	// Wait for input on EP1 (EP1 non-empty).
	if(!(EP1OUTCS & 0x02))
	{
		while(EP1INCS & 0x02); // Wait for EP1 buffer to become non-full so that we don't overwrite content.
		ProcessSendData();
		EP1OUTBC = 0x40; SYNCDELAY;
	};

}


//-----------------------------------------------------------------------------
// Device Request hooks
//   The following hooks are called by the end point 0 device request parser.
//-----------------------------------------------------------------------------

BOOL handle_set_configuration(BYTE cfg)   // Called when a Set Configuration command is received
{
	Configuration = cfg;
	return(TRUE);            // Handled by user code
}

BYTE handle_get_configuration ()   // Called when a Get Configuration command is received
{
	return Configuration;
}


BOOL handle_vendorcommand(BYTE cmd)
{
	return FALSE;
}

BOOL handle_get_interface(BYTE ifc, BYTE* alt)
{
	*alt=AlternateSetting;
	return TRUE;
}

BOOL handle_set_interface(BYTE ifc, BYTE alt)       // Called when a Set Interface command is received
{
   return(TRUE);            // Handled by user code
}

//-----------------------------------------------------------------------------
// USB Interrupt Handlers
//   The following functions are called by the USB interrupt jump table.
//-----------------------------------------------------------------------------
void sof_isr() interrupt SOF_ISR
{
	CLEAR_SOF();
}
void sutok_isr() interrupt SUTOK_ISR {}
void ep0ack_isr() interrupt EP0ACK_ISR {}
void ep0in_isr() interrupt EP0IN_ISR {}
void ep0out_isr() interrupt EP0OUT_ISR {}
void ep1in_isr() interrupt EP1IN_ISR {}
void ep1out_isr() interrupt EP1OUT_ISR {}
void ep2_isr() interrupt EP2_ISR {}
void ep4_isr() interrupt EP4_ISR {}
void ep6_isr() interrupt EP6_ISR {}
void ep8_isr() interrupt EP8_ISR {}
void ibn_isr() interrupt IBN_ISR {}
void ep0ping_isr() interrupt EP0PING_ISR {}
void ep1ping_isr() interrupt EP1PING_ISR {}
void ep2ping_isr() interrupt EP2PING_ISR {}
void ep4ping_isr() interrupt EP4PING_ISR {}
void ep6ping_isr() interrupt EP6PING_ISR {}
void ep8ping_isr() interrupt EP8PING_ISR {}
void errlimit_isr() interrupt ERRLIMIT_ISR {}
void ep2isoerr_isr() interrupt EP2ISOERR_ISR {}
void ep4isoerr_isr() interrupt EP4ISOERR_ISR {}
void ep6isoerr_isr() interrupt EP6ISOERR_ISR {}
void ep8isoerr_isr() interrupt EP8ISOERR_ISR {}
void spare_isr() interrupt RESERVED_ISR {}
void ep2pf_isr() interrupt EP2PF_ISR{}
void ep4pf_isr() interrupt EP4PF_ISR{}
void ep6pf_isr() interrupt EP6PF_ISR{}
void ep8pf_isr() interrupt EP8PF_ISR{}
void ep2ef_isr() interrupt EP2EF_ISR{}
void ep4ef_isr() interrupt EP4EF_ISR{}
void ep6ef_isr() interrupt EP6EF_ISR{}
void ep8ef_isr() interrupt EP8EF_ISR{}
void ep2ff_isr() interrupt EP2FF_ISR{}
void ep4ff_isr() interrupt EP4FF_ISR{}
void ep6ff_isr() interrupt EP6FF_ISR{}
void ep8ff_isr() interrupt EP8FF_ISR{}
void gpifdone_isr() interrupt GPIFDONE_ISR{}
void gpifwf_isr() interrupt GPIFWF_ISR{}
