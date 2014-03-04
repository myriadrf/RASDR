/**
Copyright 2013 Lime Microsystems

-- ----------------------------------------------------------------------------	
-- FILE:	mipi_rffe.c
-- DESCRIPTION:	 
-- DATE:	2013.11.21
-- AUTHOR(s):	Lime Microsystems
-- REVISION: v0r2
-- ----------------------------------------------------------------------------	
*/

#include <avr/io.h>
#include "mipi_rffe.h"
#include "global.h"

#define QDEL	asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop");
#define HDEL	asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop");


//************************
//* MIPI public functions *
//************************

//! Initialize MIPI communication
void MIPI_RFFE_Init (void)
{
	cbi (SCLK_PORT, SCLK);
	cbi (SDATA_PORT, SDATA);

	sbi( SDATA_DDR, SDATA);			// set SDATA as output
	sbi( SCLK_DDR, SCLK);			// set SCLK as output
}

void MIPI_RFFE_Write (unsigned char slave_addr, unsigned char reg_addr, unsigned char reg_data)
{
	unsigned char i, parity, cmd = 2;
	//printf("\n\n\rMIPI_write  slave_addr:0x%02x reg_addr:0x%02x reg_data:0x%02x\n\r", slave_addr, reg_addr, reg_data);
	cbi (SCLK_PORT, SCLK);
	cbi (SDATA_PORT, SDATA);
	sbi (SDATA_DDR, SDATA);// change direction to output on SDATA line
	
	//Send SSC (sequence start condition)
	//printf("\n\rSend SSC ");
	sbi (SDATA_PORT, SDATA);
	QDEL;
	cbi (SDATA_PORT, SDATA);
	
	parity = 1;
	
	//Send Slave addr
	//printf("\n\rSend Slave addr ");
	for (i=4; i> 0; i--)//MSB First
	{
		sbi (SCLK_PORT, SCLK);
		
		if(bit_is_set(slave_addr,(i-1))) //if current bit is 1
		{
			sbi (SDATA_PORT, SDATA);
			parity ^= 1; 
		}
		else
		{
			cbi (SDATA_PORT, SDATA);
		}
		
		cbi (SCLK_PORT, SCLK);
		//wait???
	}
	
	if(reg_addr == 0) //special case
	{
		//Send CMD Register 0 Write
		//printf("\n\rSend CMD Register 0 Write ");
		sbi (SCLK_PORT, SCLK);
		sbi (SDATA_PORT, SDATA);
		parity ^= 1; 
		//wait???
		cbi (SCLK_PORT, SCLK);
		//wait???
		
		//Send Data
		//printf("\n\rSend Data ");
		for (i=7; i> 0; i--)//MSB First
		{
			sbi (SCLK_PORT, SCLK);
			
			if(bit_is_set(reg_data,(i-1))) //if current bit is 1
			{
				sbi (SDATA_PORT, SDATA);
			}
			else
			{
				cbi (SDATA_PORT, SDATA);
			}
			cbi (SCLK_PORT, SCLK);
			//wait???
		}
	}
	else //writing to other registers
	{
		//Send CMD Register Write
		//printf("\n\rSend CMD ");
		for (i=3; i> 0; i--)//MSB First
		{
			sbi (SCLK_PORT, SCLK);
			
			if(bit_is_set(cmd,(i-1))) //if current bit is 1
			{
				sbi (SDATA_PORT, SDATA);
				parity ^= 1; 
			}
			else
			{
				cbi (SDATA_PORT, SDATA);
			}
			
			cbi (SCLK_PORT, SCLK);
			//wait???
		}
		
		//Send Reg Addr
		//printf("\n\rSend Reg Addr ");
		for (i=5; i> 0; i--)//MSB First
		{
			sbi (SCLK_PORT, SCLK);
			
			if(bit_is_set(reg_addr,(i-1))) //if current bit is 1
			{
				sbi (SDATA_PORT, SDATA);
				parity ^= 1; 
			}
			else
			{
				cbi (SDATA_PORT, SDATA);
			}
			
			cbi (SCLK_PORT, SCLK);
			//wait???
		}
		
		//Send Parity
		//printf("\n\rSend Parity ");
		sbi (SCLK_PORT, SCLK);
		if(parity) sbi (SDATA_PORT, SDATA);
			else cbi (SDATA_PORT, SDATA); 
		//wait???
		cbi (SCLK_PORT, SCLK);
		//wait???
		
		parity = 1;
		
		//Send Data
		//printf("\n\rSend Data ");
		for (i=8; i> 0; i--)//MSB First
		{
			sbi (SCLK_PORT, SCLK);
			
			if(bit_is_set(reg_data,(i-1))) //if current bit is 1
			{
				sbi (SDATA_PORT, SDATA);
				parity ^= 1; 
			}
			else
			{
				cbi (SDATA_PORT, SDATA);
			}
			cbi (SCLK_PORT, SCLK);
			//wait???
		}
	}
	
	//Send Parity
	//printf("\n\rSend Parity ");
	sbi (SCLK_PORT, SCLK);
	if(parity) sbi (SDATA_PORT, SDATA);
		else cbi (SDATA_PORT, SDATA); 
	//wait???
	cbi (SCLK_PORT, SCLK);
	//wait???
	
	//Bus Park
	//printf("\n\rBus Park ");
	sbi (SCLK_PORT, SCLK);
	
	cbi (SDATA_PORT, SDATA);
	cbi (SDATA_DDR, SDATA);// change direction to input on SDATA line
	//wait???
	cbi (SCLK_PORT, SCLK);
}

unsigned char MIPI_RFFE_Read (unsigned char slave_addr, unsigned char reg_addr)
{
	unsigned char i, parity, cmd = 3, reg_data, received_parity;
	//printf("\n\n\rMIPI_Read  slave_addr:0x%02x reg_addr:0x%02x reg_data:0x%02x\n\r", slave_addr, reg_addr, reg_data);
	cbi (SCLK_PORT, SCLK);
	cbi (SDATA_PORT, SDATA);
	sbi (SDATA_DDR, SDATA);// change direction to output on SDATA line
	
	//Send SSC (sequence start condition)
	//printf("\n\rSend SSC ");
	sbi (SDATA_PORT, SDATA);
	QDEL;
	cbi (SDATA_PORT, SDATA);
	
	parity = 1;
	
	//Send Slave addr
	//printf("\n\rSend Slave addr ");
	for (i=4; i> 0; i--)//MSB First
	{
		sbi (SCLK_PORT, SCLK);
		
		if(bit_is_set(slave_addr,(i-1))) //if current bit is 1
		{
			sbi (SDATA_PORT, SDATA);
			parity ^= 1; 
		}
		else
		{
			cbi (SDATA_PORT, SDATA);
		}
		
		cbi (SCLK_PORT, SCLK);
		//wait???
	}

	//Send CMD Register Read
	//printf("\n\rSend CMD ");
	for (i=3; i> 0; i--)//MSB First
	{
		sbi (SCLK_PORT, SCLK);
		
		if(bit_is_set(cmd,(i-1))) //if current bit is 1
		{
			sbi (SDATA_PORT, SDATA);
			parity ^= 1; 
		}
		else
		{
			cbi (SDATA_PORT, SDATA);
		}
		
		cbi (SCLK_PORT, SCLK);
		//wait???
	}
	
	//Send Reg Addr
	//printf("\n\rSend Reg Addr ");
	for (i=5; i> 0; i--)//MSB First
	{
		sbi (SCLK_PORT, SCLK);
		
		if(bit_is_set(reg_addr,(i-1))) //if current bit is 1
		{
			sbi (SDATA_PORT, SDATA);
			parity ^= 1; 
		}
		else
		{
			cbi (SDATA_PORT, SDATA);
		}
		
		cbi (SCLK_PORT, SCLK);
		//wait???
	}
	
	//Send Parity
	//printf("\n\rSend Parity ");
	sbi (SCLK_PORT, SCLK);
	if(parity) sbi (SDATA_PORT, SDATA);
		else cbi (SDATA_PORT, SDATA); 
	//wait???
	cbi (SCLK_PORT, SCLK);
	//wait???
	
	//Bus Park
	//printf("\n\rBus Park ");
	sbi (SCLK_PORT, SCLK);
	
	cbi (SDATA_PORT, SDATA);
	cbi (SDATA_DDR, SDATA);// change direction to input on SDATA line
	//wait???
	cbi (SCLK_PORT, SCLK);
	
	parity = 1;
	
	reg_data=0;
	//Read Data
	//printf("\n\rRead Data ");
	for (i=8; i> 0; i--)//MSB First
	{
		sbi (SCLK_PORT, SCLK);
		cbi (SCLK_PORT, SCLK);
		//wait???
		
		//sample data
		if((SDATA_PIN >> SDATA)&1) 
		{
			sbi (reg_data, (i-1));
			parity ^= 1; 
		}
	}

	//read paRITY BIT
	sbi (SCLK_PORT, SCLK);
	cbi (SCLK_PORT, SCLK);	
	received_parity = (SDATA_PIN >> SDATA)&1;
	
	//Bus Park
	//printf("\n\rBus Park ");
	sbi (SCLK_PORT, SCLK);
	
	cbi (SDATA_PORT, SDATA);
	cbi (SDATA_DDR, SDATA);// change direction to input on SDATA line
	//wait???
	cbi (SCLK_PORT, SCLK);
	
	//chek parity???
	if(parity != received_parity)
	{
	}
	
	return reg_data;
}