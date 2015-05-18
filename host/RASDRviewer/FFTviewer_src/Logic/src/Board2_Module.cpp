// -----------------------------------------------------------------------------
// FILE: 		Board2_Module.cpp
// DESCRIPTION:	Header for Board2_Module.cpp
// DATE:		2013-07-17
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "Board2_Module.h"
#include "ConnectionManager.h"
#include <math.h>
#include <iomanip>
#include "TimeCounter.h"
// ---------------------------------------------------------------------------

// Comands
// I2C FPGA
#define CFG_ADDR 0xAA
#define CMD_CFG_I2C_WR 0x14
#define CMD_CFG_I2C_RD 0x15

// LMS6002D
#define CMD_LMS_WR 0x16
#define CMD_LMS_RD 0x17

// I2C Si5356A
#define FSN_ADDR 0xE0
#define SI5338_DELAY 12 //12ms

#define LOCK_MASK 0x19
#define LOS_MASK 0x08

// ---------------------------------------------------------------------------
Board2_Module::Board2_Module()
{
    m_crystalFreq = 0;
    m_inputCLKIN = 1;
    DRVA_INV = 0;
	DRVB_INV = 0;
	DRVC_INV = 0;
	DRVD_INV = 0;

	DRVA_FMT = 3;
	DRVB_FMT = 3;
	DRVC_FMT = 3;
	DRVD_FMT = 3;
    freqMHz = 10;
	device = NULL;
}
// ---------------------------------------------------------------------------

Board2_Module::~Board2_Module()
{

}

/**
    @brief Sends Configuration to Si5356A chip
*/
void Board2_Module::ConfigureSi5356A()
{
	unsigned char out[64];
	unsigned char in[64];
	long length = 64;

	if (!device)
		return;

	Reg_Data curr;
	char curr_chip_val, clear_curr_val, clear_new_val, combined, reg;

    //Disable outputs
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 230;
	out[5] = 0x10;
	out[6] = 241;
	out[7] = 0xE5; // 0xE5;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// for all the register values in the Reg_Store array
	// get each value and mask and apply it to the Si5338  for(int i=0; i<NUM_REGS_MAX; i++)
	for (int i = 0; i < NUM_REGS_MAX; i++)
	{
		curr = Reg_Store[i];

		memset(out, 0x00, length);
		memset(in, 0x00, length);

		if (curr.Reg_Mask != 0x00)
		{
			if (curr.Reg_Mask == 0xFF)
			{
				// do a write transaction only
				// since the mask is all ones
				// Write data
				out[0] = CMD_CFG_I2C_WR;
				out[1] = FSN_ADDR;
				out[2] = 1;
				//
				out[4] = curr.Reg_Addr;
				out[5] = curr.Reg_Val;

				device->SendDataDirectly(out, length);
				device->ReadDataDirectly(in, length);
				// I2C_ByteWrite(curr.Reg_Addr, curr.Reg_Val);
			}
			else
			{
				// do a read-modify-write
				// Write data
				out[0] = CMD_CFG_I2C_RD;
				out[1] = FSN_ADDR;
				out[2] = 1;
				//
				out[4] = curr.Reg_Addr;

				device->SendDataDirectly(out, length);
				device->ReadDataDirectly(in, length);

				curr_chip_val = in[0];

				// curr_chip_val = 0xFF; //I2C_ByteRead(curr.Reg_Addr);
				clear_curr_val = curr_chip_val&~curr.Reg_Mask;
				clear_new_val = curr.Reg_Val & curr.Reg_Mask;
				combined = clear_new_val | clear_curr_val;

				// I2C_ByteWrite(curr.Reg_Addr, combined);
				// Write data
				out[0] = CMD_CFG_I2C_WR;
				out[1] = FSN_ADDR;
				out[2] = 1;
				//
				out[4] = curr.Reg_Addr;
				out[5] = combined;

				device->SendDataDirectly(out, length);
				device->ReadDataDirectly(in, length);

			}
		}
	};

	// I2C_ByteWrite(246, 2); //soft reset
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 246;
	out[5] = 2;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// I2C_ByteWrite(230, 0x00); // OEB_ALL = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 230;
	out[5] = 0x00;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	return;

	// check LOS alarm for the xtal input
	// on IN1 and IN2 (and IN3 if necessary) -
	// change this mask if using inputs on IN4, IN5, IN6
	do
	{
		memset(out, 0x00, length);
		memset(in, 0x00, length);

		// Read data
		out[0] = CMD_CFG_I2C_RD;
		out[1] = FSN_ADDR;
		out[2] = 1;
		//
		out[4] = 218;
		device->SendDataDirectly(out, length);
		device->ReadDataDirectly(in, length);
		reg = in[0] & LOS_MASK;
	}
	while (reg != 0);

	// I2C_ByteWrite(49, I2C_ByteRead(49) & 0x7F); //FCAL_OVRD_EN = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	out[5] = in[0] & 0x7F;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// I2C_ByteWrite(246, 2); //soft reset
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 246;
	out[5] = 2;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// I2C_ByteWrite(241, 0x65); //DIS_LOL = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 241;
	out[5] = 0x65;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// wait for Si5338 to be ready after calibration (ie, soft reset)
	// counter = 0;
	// while(counter < SI5338_DELAY) { counter++; }
	milSleep(SI5338_DELAY);
	// counter = 0;
	// while(counter < SI5338_DELAY) { counter++; }
	milSleep(SI5338_DELAY);

	// make sure the device locked by checking PLL_LOL and SYS_CAL
	/*
	 reg = I2C_ByteRead(218) & LOCK_MASK;
	 while(reg != 0)
	 {
	 reg = I2C_ByteRead(218) & LOCK_MASK;
	 }
	 */
	do
	{
		memset(out, 0x00, length);
		memset(in, 0x00, length);

		// Read data
		out[0] = CMD_CFG_I2C_RD;
		out[1] = FSN_ADDR;
		out[2] = 1;
		//
		out[4] = 218;
		device->SendDataDirectly(out, length);
		device->ReadDataDirectly(in, length);
		reg = in[0] & LOCK_MASK;
	}
	while (reg != 0);

	// copy FCAL values
	// I2C_ByteWrite(45, I2C_ByteRead(235));
	// I2C_ByteWrite(46, I2C_ByteRead(236));
	memset(out, 0x00, length);
	memset(in, 0x00, length);

	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 235;
	out[5] = 236;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 45;
	out[5] = in[0];
	out[6] = 46;
	out[7] = in[1];
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// clear bits 0 and 1 from 47 and
	// combine with bits 0 and 1 from 237
	// reg = (I2C_ByteRead(47) & 0xFC) | (I2C_ByteRead(237) & 3);
	// I2C_ByteWrite(47, reg);
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 47;
	out[5] = 237;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 47;
	out[5] = (in[0] & 0xFC) | (in[1] & 3);
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// I2C_ByteWrite(49, I2C_ByteRead(49) | 0x80); // FCAL_OVRD_EN = 1
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	out[5] = in[0] | 0x80;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// I2C_ByteWrite(230, 0x00); // OEB_ALL = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 230;
	out[5] = 0x00;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);
}
// ---------------------------------------------------------------------------

void Board2_Module::LmsRead()
{
	// int iVal;
	unsigned char out[64];
	unsigned char in[64];
	long length = 64;

	if (!device)
		return;
	if (!m_bAllowSend)
		return;

	// iVal = cmbOvs->ItemIndex;

	// Read data from address 0x04
	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_LMS_RD;
	out[1] = CFG_ADDR;
	out[2] = 1;
	//
	out[4] = 0x04; // SPI Instruction
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// Write 0x0F to address 0x07
	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_LMS_WR;
	out[1] = CFG_ADDR;
	out[2] = 1;
	//
	out[4] = 0x87; // SPI Instruction
	out[5] = 0x0F; // SPI Data
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	// Read data from address 0x07
	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_LMS_RD;
	out[1] = CFG_ADDR;
	out[2] = 1;
	//
	out[4] = 0x07; // SPI Instruction
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);

	/*
	 memset(out, 0x00, length);
	 //Write data
	 //out[0] = CMD_CFG_I2C_WR;
	 out[0] = CMD_CFG_I2C_RD;
	 out[1] = CFG_ADDR;
	 out[2] = 1;
	 //
	 out[4] = 0x00;  //SPI Instruction

	 device->SendDataDirectly(out, length);
	 device->ReadDataDirectly(in, length);
	 */

}
// ---------------------------------------------------------------------------
/**
    @brief Sets connection manager to use for data transferring and configures Si5356A
    @param mng connection manager for data transferring
*/
void Board2_Module::Initialize(ConnectionManager *mng)
{
	device = mng;

	if (device)
	{
		m_bAllowSend = true;
		ConfigureSi5356A();
	}
	else
	{
		m_bAllowSend = false;
	}
}

/**
    @brief Loads register values for Si5356A from file
    @param FName input filename
*/
bool Board2_Module::LoadRegValuesFromFile(string FName)
{
	FILE *in;
	char inStr[128];
	int iEntry = 0;
	int Rez;

	int iReg_Addr;
	int iReg_Val;
	int iReg_Mask;

	if ((in = fopen(FName.c_str(), "rt")) == NULL)
	{
		return false;
	};

	while (!feof(in))
	{
		fgets(inStr, 127, in);
		if (inStr[0] == '{')
		{
			Rez = sscanf(&inStr[1], "%d,%i,%i", &iReg_Addr, &iReg_Val,
				&iReg_Mask);
			if (Rez == 3)
			{
				Reg_Store[iEntry].Reg_Addr = iReg_Addr;
				Reg_Store[iEntry].Reg_Val = iReg_Val;
				Reg_Store[iEntry].Reg_Mask = iReg_Mask;
			};
			iEntry++;
		};
	};
	fclose(in);
	return true;
};

// ---------------------------------------------------------------------------

void Board2_Module::ReadMem()
{
	int iVal;
	unsigned char out[64];
	unsigned char in[64];
	long length = 64;

	if (!device)
		return;
	if (!m_bAllowSend)
		return;

	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = CFG_ADDR;
	out[2] = 16;
	//
	for (int i = 0; i < 16; i++)
	{
		out[4 + i] = i;
	}
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(in, length);
}

/**
    @brief Sets frequency for desired clock
    @param clkID clock id
    @param refClkMHz reference clock frequency in MHz
    @param clkMHz clock output frequency
*/
void Board2_Module::SetFrequency(unsigned int clkID, float refClkMHz, float clkMHz)
{
    freqMHz = clkMHz;
    fpfdMHz = refClkMHz;
    Reg_Data reg;
    //reference clock configuration

    char hw_name[128];
    device->GetCustomParameter("HW_DigiRed", hw_name);

    if(m_inputCLKIN)
    {
        for(int i=0; i<4; i++)
        {
            unsigned char cval = 0;
            cval = GetReg(31+i);
            cval &= 0x1F;
            cval |= 0xC0;
            SetReg(31+i, cval);
        }

        if(fpfdMHz > 5 && fpfdMHz <= 40)
        {
            SetReg(28, 0x37);
            SetReg(29, 0x20);
            SetReg(30, 0x08);
        }
        else if(fpfdMHz > 40) //CLKIN > 40 MHz
        {
           /* m_regmap[28] &= 0x37;
            m_regmap[29] &= 0xE0;
            m_regmap[30] &= 0x08; //need to set PDIV*/
        }
    }
    else //xoclk
    {
        if(m_crystalFreq = 0) // xoclk 25MHz
            SetReg(28, 0x36);
        else // xoclk 27MHz
            SetReg(28, 0x37);
        SetReg(29, 0x80);
        SetReg(30, 0x00);
    }

    //configuring PLL parameters
    unsigned int K = 0;
    if( fpfdMHz >= 15)
    {
        K = 925;
        SetReg(49, 0x10); //VCO_GAIN, RSEL, BWSEL
    }
    else if(fpfdMHz >= 8 && fpfdMHz < 15)
    {
        K = 325;
        SetReg(49, 0x15);
    }
    else if(fpfdMHz >= 5 && fpfdMHz < 8)
    {
        K = 185;
        SetReg(49, 0x1E);
    }
    else
    {
        return;
    }
    SetReg(51, 0x07); // MS_PEC[2:0]

    unsigned int PLL_KPHI = round( (1.51 * K)/fpfdMHz );
    SetReg( 48, PLL_KPHI );

    //feedback multisynth
    unsigned int MSN_P1 = floor( 281600/fpfdMHz) - 512;
    SetReg(99, ( (MSN_P1 >> 16) & 0x03  ) );
    SetReg(98, ( (MSN_P1 >> 8) & 0xFF  ) );
    SetReg(97, (MSN_P1 & 0xFF  ));

    unsigned int MSN_P2 = floor( pow(10, 9) * (281600/fpfdMHz - MSN_P1 - 512) );
    MSN_P2 = MSN_P2 << 2;
    SetReg(102, (MSN_P2 >> 24));
    SetReg(101, (MSN_P2 >> 16) & 0xFF);
    SetReg(100, (MSN_P2 >> 8) & 0xFF);
    SetReg(99, MSN_P2 & 0xFC);

    unsigned int MSN_P3 = pow(10, 9);
    SetReg(106, (MSN_P3 >> 24) & 0x3F);
    SetReg(105, (MSN_P3 >> 16) & 0xFF);
    SetReg(104, (MSN_P3 >> 8) & 0xFF);
    SetReg(103, MSN_P3 & 0xFF);

    //Configuring output driver
    //enabling clocks

    unsigned int MSx_P1 = floor( (281600/freqMHz) - 512 );
    unsigned int MSx_P2 = floor( pow(10, 9) * ( 281600/freqMHz - MSx_P1 - 512 ));
    unsigned int MSx_P3 = 0x01;

    unsigned int MSx_P1addr = 53;

    switch(clkID)
    {
    case 0:
        MSx_P1addr = 53;
        break;
    case 1:
        MSx_P1addr = 64;
        break;
    case 2:
        MSx_P1addr = 75;
        break;
    case 3:
        MSx_P1addr = 86;
        break;
    }

    SetReg( MSx_P1addr, MSx_P1 & 0xFF);
    SetReg( MSx_P1addr+1, (MSx_P1 >> 8) & 0xFF);
    SetReg( MSx_P1addr+2, (MSx_P1 >> 16) & 0x03);

    MSx_P2 = MSx_P2 << 2;
    SetReg( MSx_P1addr+2, (MSx_P2 & 0xFC) | ((MSx_P1 >> 16) & 0x03));
    SetReg( MSx_P1addr+3, (MSx_P2 >> 8) & 0xFF);
    SetReg( MSx_P1addr+4, (MSx_P2 >> 16) & 0xFF);
    SetReg( MSx_P1addr+5, (MSx_P2 >> 24) & 0xFF);

    SetReg( MSx_P1addr+6, MSx_P3 & 0xFF);
    SetReg( MSx_P1addr+7, (MSx_P3 >> 8) & 0xFF);
    SetReg( MSx_P1addr+8, (MSx_P3 >> 16) & 0xFF);
    SetReg( MSx_P1addr+9, (MSx_P3 >> 24) & 0x3F);
}

/**
    @brief Sets clock inversions
    @param clkID clock id
    @param inversion
        - 0 : no inversion
        - 1 : invert even
        - 2 : invert odd
        - 3 : invert both
*/
void Board2_Module::SetInvertClock(unsigned int clkID, unsigned int inversion)
{
    unsigned char val = 0;
    int addr = 0;
    switch(clkID)
    {
    case 0:
        addr = 36;
        break;
    case 1:
        addr = 37;
        break;
    case 2:
        addr = 38;
        break;
    case 3:
        addr = 39;
        break;
    }
    val = GetReg(addr);
    val = val & 0x07;
    val |= (inversion << 3);
    SetReg(addr, val);
}

/**
    @brief Power up clocks by id
    @param clkID clock id
    @param powered power up clock
*/
void Board2_Module::PowerUpClock(unsigned int clkID, bool powered)
{
    unsigned char val = 0;
    int addr = 0;
    switch(clkID)
    {
    case 0:
        addr = 31;
        break;
    case 1:
        addr = 32;
        break;
    case 2:
        addr = 33;
        break;
    case 3:
        addr = 34;
        break;
    }
    val = GetReg(addr);
    val = val & 0xFC;
    val |= !powered;
    val |= (!powered) << 1;
    SetReg(addr, val);
}

void Board2_Module::EnableClock(unsigned int clkID, bool enabled)
{
    unsigned char val = 0;
    int addr = 230;
    unsigned char param = !enabled;
    param = param << (clkID);
    unsigned char mask = ~(1 << (clkID));

    val = GetReg(addr);
    val = val & mask;
    val |= param;
    SetReg(addr, val);
}

/**
    @brief Sets clock output format
    @param clkID clock id
    @param enabled
        - 0 : reserved
        - 1 : even=on, odd=off
        - 2 : even=off, odd=on
        - 3 : even=on, odd=on
*/
void Board2_Module::SetOutputFormat(unsigned int clkID, unsigned int format)
{
    unsigned char val = 0;
    int addr = 0;
    switch(clkID)
    {
    case 0:
        addr = 36;
        break;
    case 1:
        addr = 37;
        break;
    case 2:
        addr = 38;
        break;
    case 3:
        addr = 39;
        break;
    }
    val = GetReg(addr);
    val = val & 0xF8;
    val |= format;
    SetReg(addr, val);
}

void Board2_Module::SetRefClockInput(bool CLKIN)
{
    m_inputCLKIN = CLKIN;
}

/**
    @brief Selects crystal frequency
    @param freqID
        - 0 : 25 MHz
        - 1 : 27 MHz
*/
void Board2_Module::SetCrystalFreq(unsigned int freqID)
{
    m_crystalFreq = freqID;
}

/**
    @brief Returns value from registers list
    @param addr register address
    @return register value
*/
unsigned char Board2_Module::GetReg(unsigned int addr)
{
    Reg_Data reg;
    reg = Reg_Store[addr];
    return reg.Reg_Val;
}

/**
    @brief Sets value in registers list
    @param addr register address
    @param Value register value
*/
void Board2_Module::SetReg(unsigned int addr, unsigned char Value)
{
    Reg_Data reg;
    reg = Reg_Store[addr];
    reg.Reg_Val = Value;

    Reg_Store[addr] = reg;
}

