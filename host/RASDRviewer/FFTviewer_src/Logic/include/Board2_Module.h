// -----------------------------------------------------------------------------
// FILE: 		Board2_Module.h
// DESCRIPTION:	Header for Board2_Module.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef BOARD2_MODULE_H
#define BOARD2_MODULE_H
//---------------------------------------------------------------------------
#ifdef WIN32


#include "windows.h"
#include "CyAPI.h"
#endif

#include "common.h"
#include "register_map.h"
#include <stdio.h>
#include <string>
//---------------------------------------------------------------------------

class ConnectionManager;
class Board2_Module
{
public:
	Board2_Module();
	~Board2_Module();
	void Initialize(ConnectionManager *mng);
	bool LoadRegValuesFromFile(string FName);
	void SetInvertClock(unsigned int clkID, unsigned int inversion);
	void PowerUpClock(unsigned int clkID, bool powered);
	void EnableClock(unsigned int clkID, bool enabled);
	void SetOutputFormat(unsigned int clkID, unsigned int format);
	void SetFrequency(unsigned int clkID, float refClkMHz, float clkMHz);
	void SetRefClockInput(bool CLKIN);
	void SetCrystalFreq(unsigned int freqID);
	void ConfigureSi5356A();
	void LmsRead();
	void ReadMem();

private:
    unsigned char GetReg(unsigned int addr);
    void SetReg(unsigned int addr, unsigned char Value);
    ConnectionManager *device;
	bool m_bAllowSend;
	bool m_inputCLKIN;
	unsigned int m_crystalFreq;
	float freqMHz;
	float fpfdMHz;

	unsigned int DRVA_INV;
	unsigned int DRVB_INV;
	unsigned int DRVC_INV;
	unsigned int DRVD_INV;

	unsigned int DRVA_FMT;
	unsigned int DRVB_FMT;
	unsigned int DRVC_FMT;
	unsigned int DRVD_FMT;
};

#endif
