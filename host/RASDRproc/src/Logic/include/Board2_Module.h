// -----------------------------------------------------------------------------
// FILE:        "Board2_Module.h"
// DESCRIPTION: "Header File"
// DATE:        "05/09/2015 06:44 AM "
// AUTHOR(s):   Lime Microsystems, Paul L. Oxley
// Copyright:   Society of Amateur Radio Astronomers (2014-2015)
//
// Based on original work from Zydrunas Tamosevicius (Lime Microsystems, Ltd.)
// and distributed under the Apache License 2.0 at:
// https://github.com/myriadrf/myriadrf-utils
//
// The RASDRviewer version has been specifically modified for Radio Astronomy
// by Paul L. Oxley for the Society of Amateur Radio Astronomers.  These
// modifications are provided to you under the Gnu Public License version 2.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// REVISIONS:   as appropriate
// -----------------------------------------------------------------------------
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
