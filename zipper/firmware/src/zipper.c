/*
             LUFA Library
     Copyright (C) Dean Camera, 2009, 2013 Lime Microsystems.
              
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
  
  Lime Microsystems modified this source. Left the main part of 
  the code which implements virtual COM port functionality. 
  Added additional functionality for LMS board controlling.
*/
#include "zipper.h"
#include "global.h"
#include "libs/i2c/i2csw.h"
#include "libs/mipi_rffe/mipi_rffe.h"
#include "LMS_defines.h"

/* Scheduler Task List */
TASK_LIST
{
	{ .Task = USB_USBTask          , .TaskStatus = TASK_STOP },
	{ .Task = CDC_Task             , .TaskStatus = TASK_STOP },
	{ .Task = Main_Task             , .TaskStatus = TASK_STOP },
};

/* Globals: */
/** Contains the current baud rate and other settings of the virtual serial port.
 *
 *  These values are set by the host via a class-specific request, and the physical USART should be reconfigured to match the
 *  new settings each time they are changed by the host.
 */
CDC_Line_Coding_t LineCoding = { .BaudRateBPS = 9600,
                                 .CharFormat  = OneStopBit,
                                 .ParityType  = Parity_None,
                                 .DataBits    = 8            };

/** Ring (circular) buffer to hold the RX data - data from the host to the attached device on the serial port. */
RingBuff_t Rx_Buffer;

/** Ring (circular) buffer to hold the TX data - data from the attached device on the serial port to the host. */
RingBuff_t Tx_Buffer;

/* some global variables used throughout */
unsigned char tx_buff[LMS_CTRL_PACKET_SIZE], rx_buff[LMS_CTRL_PACKET_SIZE], count, reg_idx, Exp_board_id;

tLMS_Ctrl_Packet *LMS_Ctrl_Packet_Tx = (tLMS_Ctrl_Packet*)tx_buff;
tLMS_Ctrl_Packet *LMS_Ctrl_Packet_Rx = (tLMS_Ctrl_Packet*)rx_buff;

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1); // with 8MHz crystal, this means CLK=8000000

	/* Hardware Initialization */
	
	//set outputs directions
	// Prepare PortB for SPI - set PB0(^SS), PB1(SCK), PB2(MOSI) as output as well as all other pins except PB3(MISO)
	sbi (DDRB, SPI_NCS_0);
	sbi (DDRB, SPI_CLK);
	sbi (DDRB, SPI_MOSI);
	sbi (DDRB, RESET);
	sbi (DDRB, SPI_NCS_1);
	sbi (DDRB, SPI_NCS_2);
	sbi (DDRB, LED);
	
	sbi (DDRC, GPIO0);
	sbi (DDRC, GPIO1);
	
	sbi (DDRD, GPIO2);
	sbi (DDRD, GPIO3);
	sbi (DDRB, SPI_NCS_3);

	//set outputs levels
	sbi(PORTB, SPI_NCS_0); // make sure the ^SS select pin is high (disabled)
	sbi(PORTB, SPI_NCS_1); // make sure the ^SS select pin is high (disabled)
	sbi(PORTB, SPI_NCS_2); // make sure the ^SS select pin is high (disabled)
	sbi(PORTB, RESET); // make sure the ^Reset pin is high
	
	Reconfigure_SPI_for_LMS();
	i2cInit();
	MIPI_RFFE_Init ();
	

	/* 16-bit Timer1 Initialization */
	TCCR1A = 0; //start the timer
	//TCCR1B = (1 << CS10); // no Timer1 prescaling, use CLK
	TCCR1B = (1 << CS12); // prescale Timer1 by CLK/256
	// 8000000 / 256 = 31250 ticks per second
	// 16-bit = 2^16 = 65536 maximum ticks for Timer1
	// 65536 / 31250 =~ 2.1
	// so Timer1 will overflow back to 0 about every 2 seconds

	/* Ring buffer Initialization */
	Buffer_Initialize(&Rx_Buffer);
	Buffer_Initialize(&Tx_Buffer);

	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Connect(void)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);

	/* Indicate USB enumerating */
	//UpdateStatus(Status_USBEnumerating);
}

/** Event handler for the USB_Disconnect event. This stops the USB management and CDC management tasks.
 */
void EVENT_USB_Disconnect(void)
{
	/* Stop running CDC and USB management tasks */
	Scheduler_SetTaskMode(CDC_Task, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	
	/* Reset Tx and Rx buffers, device disconnected */
	Buffer_Initialize(&Rx_Buffer);
	Buffer_Initialize(&Tx_Buffer);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the CDC management task started.
 */
void EVENT_USB_ConfigurationChanged(void)
{
	/* Setup CDC Notification, Rx and Tx Endpoints */
	Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, CDC_NOTIFICATION_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC_TX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC_RX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Start CDC task */
	Scheduler_SetTaskMode(CDC_Task, TASK_RUN);
	Scheduler_SetTaskMode(Main_Task, TASK_RUN);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the CDC control commands,
 *  which are all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
void EVENT_USB_UnhandledControlPacket(void)
{
	uint8_t* LineCodingData = (uint8_t*)&LineCoding;

	/* Process CDC specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{	
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();

				/* Write the line coding data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(LineCodingData, sizeof(LineCoding));
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearOUT();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();

				/* Read the line coding data in from the host into the global struct */
				Endpoint_Read_Control_Stream_LE(LineCodingData, sizeof(LineCoding));

				/* Finalize the stream transfer to clear the last packet from the host */
				Endpoint_ClearIN();
				
				/* Reconfigure the USART with the new settings */
				Reconfigure_SPI_for_LMS();
			}
	
			break;
		case REQ_SetControlLineState:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{				
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();
				
				/* NOTE: Here you can read in the line state mask from the host, to get the current state of the output handshake
				         lines. The mask is read in from the wValue parameter in USB_ControlRequest, and can be masked against the
						 CONTROL_LINE_OUT_* masks to determine the RTS and DTR line states using the following code:
				*/

				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}
	
			break;
	}
}

/** Task to manage CDC data transmission and reception to and from the host, from and to the physical USART. */
TASK(CDC_Task)
{
	if (USB_IsConnected)
	{
		/* Select the Serial Rx Endpoint */
		Endpoint_SelectEndpoint(CDC_RX_EPNUM);
		
		/* Check to see if a packet has been received from the host */
		if (Endpoint_IsOUTReceived())
		{
			/* Read the bytes in from the endpoint into the buffer while space is available */
			while (Endpoint_BytesInEndpoint() && (BUFF_STATICSIZE - Rx_Buffer.Elements))
			{
				/* Store each character from the endpoint */
				Buffer_StoreElement(&Rx_Buffer, Endpoint_Read_Byte());
			}
			
			/* Check to see if all bytes in the current packet have been read */
			if (!(Endpoint_BytesInEndpoint()))
			{
				/* Clear the endpoint buffer */
				Endpoint_ClearOUT();
			}
		}
		
		/* Select the Serial Tx Endpoint */
		Endpoint_SelectEndpoint(CDC_TX_EPNUM);

		/* Check if the Tx buffer contains anything to be sent to the host */
		if (Tx_Buffer.Elements)
		{
			/* Wait until Serial Tx Endpoint Ready for Read/Write */
			while (!(Endpoint_IsReadWriteAllowed()));
			
			/* Write the bytes from the buffer to the endpoint while space is available */
			while (Tx_Buffer.Elements && (Endpoint_BytesInEndpoint() < CDC_TXRX_EPSIZE))
			{
				/* Write each byte retreived from the buffer to the endpoint */
				Endpoint_Write_Byte(Buffer_GetElement(&Tx_Buffer));
			}
			
			/* Remember if the packet to send completely fills the endpoint */
			bool IsFull = (Endpoint_BytesInEndpoint() == CDC_TXRX_EPSIZE);
			
			/* Send the data */
			Endpoint_ClearIN();

			/* If no more data to send and the last packet filled the endpoint, send an empty packet to release
			 * the buffer on the receiver (otherwise all data will be cached until a non-full packet is received) */
			if (IsFull && !(Tx_Buffer.Elements))
			{
				/* Wait until Serial Tx Endpoint Ready for Read/Write */
				while (!(Endpoint_IsReadWriteAllowed()));

				/* Send an empty packet to terminate the transfer */
				Endpoint_ClearIN();
			}
		}
	}
}


/** After the device is connected to a Host, this task will run periodically,
		even if the device is disconnected.
	Your application code should go here
*/
TASK(Main_Task)
{
	uint8_t block;
	uint16_t cmd_errors;

	if(Rx_Buffer.Elements == LMS_CTRL_PACKET_SIZE) //receveid full packet?
	{
		sbi (PORTB, LED);
		cmd_errors = 0;
		for (count =0; count <LMS_CTRL_PACKET_SIZE; count++) //get all packets bytes
		{
			rx_buff[count] = Buffer_GetElement(&Rx_Buffer);
		}
		
		memset (tx_buff, 0, sizeof(tx_buff)); //fill whole tx buffer with zeros
		
		LMS_Ctrl_Packet_Tx->Header.Command = LMS_Ctrl_Packet_Rx->Header.Command;
		LMS_Ctrl_Packet_Tx->Header.Data_blocks = LMS_Ctrl_Packet_Rx->Header.Data_blocks;
		LMS_Ctrl_Packet_Tx->Header.Status = STATUS_BUSY_CMD;
		
		switch(LMS_Ctrl_Packet_Rx->Header.Command)
		{
			case CMD_GET_INFO:
				Exp_board_detection ();
				
				LMS_Ctrl_Packet_Tx->Data_field[0] = FW_VER;
				LMS_Ctrl_Packet_Tx->Data_field[1] = DEV_TYPE;
				LMS_Ctrl_Packet_Tx->Data_field[2] = LMS_PROTOCOL_VER;
				LMS_Ctrl_Packet_Tx->Data_field[3] = HW_VER;
				LMS_Ctrl_Packet_Tx->Data_field[4] = Exp_board_id;
				
				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;
				
			case CMD_SI5351_WR:
				if(Check_many_blocks (2)) break;
				
				for(block = 0; block < LMS_Ctrl_Packet_Rx->Header.Data_blocks; block++)
				{
					if (!i2cSend(SI5351_I2C_ADDR, LMS_Ctrl_Packet_Rx->Data_field[block * 2], 1, &LMS_Ctrl_Packet_Rx->Data_field[1 + (block * 2)])) cmd_errors++;
				}
				
				if(cmd_errors) LMS_Ctrl_Packet_Tx->Header.Status = STATUS_ERROR_CMD;
				else LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;
				
			case CMD_SI5351_RD:
				if(Check_many_blocks (2)) break;
				
				for(block = 0; block < LMS_Ctrl_Packet_Rx->Header.Data_blocks; block++)
				{
					LMS_Ctrl_Packet_Tx->Data_field[block * 2] = LMS_Ctrl_Packet_Rx->Data_field[block];
					if (!i2cReceive(SI5351_I2C_ADDR, LMS_Ctrl_Packet_Rx->Data_field[block], 1, &LMS_Ctrl_Packet_Tx->Data_field[1 + block * 2])) cmd_errors++;
				}
				
				if(cmd_errors) LMS_Ctrl_Packet_Tx->Header.Status = STATUS_ERROR_CMD;
				else LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;

				break;
				
			case CMD_LMS_RST:
				switch (LMS_Ctrl_Packet_Rx->Data_field[0])
				{
					case LMS_RST_DEACTIVATE:
						sbi(PORTB, RESET); //high level
						break;
					
					case LMS_RST_ACTIVATE:
						cbi(PORTB, RESET); //low level
						break;
						
					case LMS_RST_PULSE:
						cbi(PORTB, RESET); //low level
						Delay_us (10*1000); //wait ~10 ms
						sbi(PORTB, RESET); //high level
						break;
						
					default:
						cmd_errors++;
						break;
				}
				
				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;
				
			/*case CMD_LMS_LNA:
				if(LMS_Ctrl_Packet_Rx->Data_field[0] & 0x01) sbi(PORTD, GPIO0); else cbi(PORTD, GPIO0); //LNA0
				if(LMS_Ctrl_Packet_Rx->Data_field[0] & 0x02) sbi(PORTD, GPIO1); else cbi(PORTD, GPIO1); //LNA1

				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;

			case CMD_LMS_PA:
				if(LMS_Ctrl_Packet_Rx->Data_field[0] & 0x01) sbi(PORTD, GPIO2); else cbi(PORTD, GPIO2); //PA0
			
				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;*/
				
			case CMD_LMS6002_WR:
				if(Check_many_blocks (2)) break;
				
				cbi (PORTB, SPI_NCS_0); //Enable LMS's SPI
				
				for(block = 0; block < LMS_Ctrl_Packet_Rx->Header.Data_blocks; block++)
				{
					//set reg addr
					sbi(LMS_Ctrl_Packet_Rx->Data_field[0 + (block * 2)], 7); //set write bit
					
					SPI_SendByte(LMS_Ctrl_Packet_Rx->Data_field[0 + (block * 2)]); //reg addr with write bit
					
					//write reg data
					SPI_SendByte(LMS_Ctrl_Packet_Rx->Data_field[1 + (block * 2)]); //reg data
				}
				
				sbi (PORTB, SPI_NCS_0); //Disable LMS's SPI
				
				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				
				break;
				
			case CMD_LMS6002_RD:
				if(Check_many_blocks (2)) break;
			
				cbi (PORTB, SPI_NCS_0); //Enable LMS's SPI

				for(block = 0; block < LMS_Ctrl_Packet_Rx->Header.Data_blocks; block++)
				{
					//write reg addr
					cbi(LMS_Ctrl_Packet_Rx->Data_field[block], 7); //clear write bit
					
					SPI_SendByte(LMS_Ctrl_Packet_Rx->Data_field[block]); //reg addr MSB
					
					LMS_Ctrl_Packet_Tx->Data_field[0 + (block * 2)] = LMS_Ctrl_Packet_Rx->Data_field[block];
					
					//read reg data
					LMS_Ctrl_Packet_Tx->Data_field[1 + (block * 2)] = SPI_TransferByte(0x00); //reg data MSB

				}
				
				sbi (PORTB, SPI_NCS_0); //Disable LMS's SPI
				
				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;
				
			case CMD_ADF4002_WR:
				if(Check_many_blocks (3)) break;
	
				for(block = 0; block < LMS_Ctrl_Packet_Rx->Header.Data_blocks; block++)
				{
					cbi (PORTB, SPI_NCS_1); //Enable ADF's SPI
					SPI_SendByte(LMS_Ctrl_Packet_Rx->Data_field[0 + (block*3)]);
					SPI_SendByte(LMS_Ctrl_Packet_Rx->Data_field[1 + (block*3)]);
					SPI_SendByte(LMS_Ctrl_Packet_Rx->Data_field[2 + (block*3)]);
					sbi (PORTB, SPI_NCS_1); //Disable ADF's SPI
				}
	
				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;
				
			case CMD_PE636040_WR:
				if(Check_many_blocks (3)) break;
	
				for(block = 0; block < LMS_Ctrl_Packet_Rx->Header.Data_blocks; block++)
				{
					switch (LMS_Ctrl_Packet_Rx->Data_field[0 + (block*3)]) //tuner ID
					{
						case 0:
							MIPI_RFFE_Write (PA_IN_RFFE_ADDR, LMS_Ctrl_Packet_Rx->Data_field[1 + (block*3)], LMS_Ctrl_Packet_Rx->Data_field[2 + (block*3)]);
							break;
						
						case 1:
							MIPI_RFFE_Write (PA_OUT_RFFE_ADDR, LMS_Ctrl_Packet_Rx->Data_field[1 + (block*3)], LMS_Ctrl_Packet_Rx->Data_field[2 + (block*3)]);
							break;
							
						default:
							cmd_errors++;
							break;
					}
				}

				
				/*MIPI_RFFE_Write (0x26, 2, 0xAB);
				MIPI_RFFE_Write (0x27, 2, 0xAC);*/
				if(cmd_errors) LMS_Ctrl_Packet_Tx->Header.Status = STATUS_ERROR_CMD;
					else LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;
				
			case CMD_PE636040_RD:
			
				if(Check_many_blocks (3)) break;
	
				for(block = 0; block < LMS_Ctrl_Packet_Rx->Header.Data_blocks; block++)
				{
					LMS_Ctrl_Packet_Tx->Data_field[0 + (block * 3)] = LMS_Ctrl_Packet_Rx->Data_field[0 + (block*2)];
					LMS_Ctrl_Packet_Tx->Data_field[1 + (block * 3)] = LMS_Ctrl_Packet_Rx->Data_field[1 + (block*2)];
					
					switch (LMS_Ctrl_Packet_Rx->Data_field[0 + (block*2)]) //tuner ID
					{
						case 0:
							LMS_Ctrl_Packet_Tx->Data_field[2 + (block * 3)] = MIPI_RFFE_Read (PA_IN_RFFE_ADDR, LMS_Ctrl_Packet_Rx->Data_field[1 + (block*2)]);
							break;
						
						case 1:
							LMS_Ctrl_Packet_Tx->Data_field[2 + (block * 3)] = MIPI_RFFE_Read (PA_OUT_RFFE_ADDR, LMS_Ctrl_Packet_Rx->Data_field[1 + (block*2)]);
							break;
							
						default:
							cmd_errors++;
							break;
					}
				}

				/*LMS_Ctrl_Packet_Tx->Data_field[0] = MIPI_RFFE_Read (0x26, 2);
				LMS_Ctrl_Packet_Tx->Data_field[1] = MIPI_RFFE_Read (0x27, 2);*/
				
				if(cmd_errors) LMS_Ctrl_Packet_Tx->Header.Status = STATUS_ERROR_CMD;
					else LMS_Ctrl_Packet_Tx->Header.Status = STATUS_COMPLETED_CMD;
				break;			

			case CMD_MYRIAD_GPIO_WR:
				Exp_board_detection ();
			
				//GPIO0 control
				if (LMS_Ctrl_Packet_Rx->Data_field[0] & 0x01) sbi(PORTC, GPIO0);
					else cbi(PORTC, GPIO0);
				
				//GPIO1 control	
				if (LMS_Ctrl_Packet_Rx->Data_field[0] & 0x02) sbi(PORTC, GPIO1);
					else cbi(PORTC, GPIO1);
				
				//GPIO2 control depends on MYriad RF version
				if (Exp_board_id == EXP_BOARD_MYRIAD2)
				{
					if (LMS_Ctrl_Packet_Rx->Data_field[0] & 0x04) cbi(PORTD, GPIO2);
						else sbi(PORTD, GPIO2);
				}
				else
				{
					if (LMS_Ctrl_Packet_Rx->Data_field[0] & 0x04) sbi(PORTD, GPIO2);
						else cbi(PORTD, GPIO2);
				}
				
				//GPIO3 control
				if (LMS_Ctrl_Packet_Rx->Data_field[0] & 0x08) sbi(PORTD, GPIO3);
					else cbi(PORTD, GPIO3);
				
				break;
			
			default:
				
				LMS_Ctrl_Packet_Tx->Header.Status = STATUS_UNKNOWN_CMD;
				break;
		}
		
		//send prepared tx buffer to pc
		for (count =  0; count < LMS_CTRL_PACKET_SIZE; count++)
		{
			Buffer_StoreElement(&Tx_Buffer, tx_buff[count]);
		}
		cbi (PORTB, LED);
	}
}

/** Reconfigures SPI to match the current serial port settings issued by the host. */
void Reconfigure_SPI_for_LMS(void)
{
	uint8_t SPCRmask = (1 << SPE) | (1 << MSTR); // always enable SPI as Master
	uint8_t SPSRmask = 0;

	/* Determine stop bits - 1.5 stop bits is set as 1 stop bit due to hardware limitations */
	/* For SPI, determine whether format is LSB or MSB */
	if (LineCoding.CharFormat == TwoStopBits) {	
		SPCRmask |= (1 << DORD);
	} else if (LineCoding.CharFormat == OneStopBit) {
		SPCRmask |= (0 << DORD);
	}

	/* Determine data size - 5, 6, 7, or 8 bits are supported */
	/* Changing line coding changes SPI Mode
		CPOL=0, CPHA=0 Sample (Rising) Setup (Falling) SPI-Mode0 == 8 bits line coding
		CPOL=0, CPHA=1 Setup (Rising) Sample (Falling) SPI-Mode1 == 7 bits line coding
		CPOL=1, CPHA=0 Sample (Falling) Setup (Rising) SPI-Mode2 == 6 bits line coding
		CPOL=1, CPHA=1 Setup (Falling) Sample (Rising) SPI-Mode3 == 5 bits line coding
	*/
	if (LineCoding.DataBits == 5) {
		SPCRmask |= ((1 << CPOL) | (1 << CPHA));
	} else if (LineCoding.DataBits == 6) {
		SPCRmask |= ((1 << CPOL) | (0 << CPHA));
	} else if (LineCoding.DataBits == 7) {
		SPCRmask |= ((0 << CPOL) | (1 << CPHA));
	} else if (LineCoding.DataBits == 8) {
		SPCRmask |= ((0 << CPOL) | (0 << CPHA));
	}


	/* Set the USART baud rate register to the desired baud rate value */
	/* also alter the SPI speed via value of baud rate */
	if        (LineCoding.BaudRateBPS == 9600) {	// 4Mhz SPI (Fosc / 2)
		SPCRmask |= ((0 << SPR1) | (0 << SPR0));
		SPSRmask |= (1 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 14400) {	// 2Mhz SPI (Fosc / 4)
		SPCRmask |= ((0 << SPR1) | (0 << SPR0));
		SPSRmask |= (0 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 19200) {	// 1MHz SPI (Fosc / 8)
		SPCRmask |= ((0 << SPR1) | (1 << SPR0));
		SPSRmask |= (1 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 38400) {	// 500kHz SPI (Fosc / 16)
		SPCRmask |= ((0 << SPR1) | (1 << SPR0));
		SPSRmask |= (0 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 57600) {	// 250kHz SPI (Fosc / 32)
		SPCRmask |= ((1 << SPR1) | (0 << SPR0));
		SPSRmask |= (1 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 115200) {	// 125kHz SPI (Fosc / 64)
		SPCRmask |= ((1 << SPR1) | (0 << SPR0));
		SPSRmask |= (0 << SPI2X);
	}
	
	/*SPCRmask |= ((0 << SPR1) | (1 << SPR0)); // 500kHz SPI (Fosc / 16)
	SPSRmask |= (0 << SPI2X);*/

	SPCR = SPCRmask;
	SPSR = SPSRmask;
}


/**	Inaccurate software delay function to get required delay in microseconds. */
void Delay_us (unsigned int cycles)
{
	while (cycles--)
	{
		asm volatile("nop"); 
		asm volatile("nop"); 
		asm volatile("nop");
	}	
}

/**	This function checks if all blocks could fit in data field.
*	If blocks will not fit, function returns TRUE. */
unsigned char Check_many_blocks (unsigned char block_size)
{
	if (LMS_Ctrl_Packet_Rx->Header.Data_blocks > (sizeof(LMS_Ctrl_Packet_Tx->Data_field)/block_size)) 
	{
		LMS_Ctrl_Packet_Tx->Header.Status = STATUS_MANY_BLOCKS_CMD;
		return TRUE;
	}
	else return FALSE;
}

/**	This function searches for register addres position in RX buffer's data field from given position 
*	till it finds matching register addres or reaches data field boundary.
*	If the register address has been found function returns TRUE and writes its index to global variable "reg_idx". */
unsigned char Search_reg_idx (unsigned char from_idx, unsigned char search_reg_addr)
{
	for (reg_idx = from_idx; reg_idx < LMS_Ctrl_Packet_Rx->Header.Data_blocks; reg_idx++)
	{
		if (LMS_Ctrl_Packet_Rx->Data_field[reg_idx] == search_reg_addr)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void Exp_board_detection ()
{
	unsigned char spi_data, rffe_data;
	
	Exp_board_id = EXP_BOARD_UNKNOWN;
	
	cbi (PORTB, SPI_NCS_0); //Enable LMS's SPI
	SPI_SendByte(0x04); //reg addr MSB
	spi_data = SPI_TransferByte(0x00); //reg data MSB
	sbi (PORTB, SPI_NCS_0); //Disable LMS's SPI
	
	if ((spi_data != 0x00) && (spi_data != 0xFF)) Exp_board_id = EXP_BOARD_MYRIAD1;
	
	rffe_data = MIPI_RFFE_Read (PA_IN_RFFE_ADDR, 0x1F);
	
	if (rffe_data == PA_IN_RFFE_ADDR) Exp_board_id = EXP_BOARD_MYRIAD2;
}

