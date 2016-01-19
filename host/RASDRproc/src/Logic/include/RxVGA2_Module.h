// -----------------------------------------------------------------------------
// FILE:        "RxVGA2_Module.h"
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
// FILE: 		RxVGA2_Module.h
// DESCRIPTION:	Header for RxVGA2_Module.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ---------------------------------------------------------------------------
#ifndef RxVGA2_Module_H
#define RxVGA2_Module_H
// ---------------------------------------------------------------------------
#include "common.h"
#include <fstream>
#include "iniParser.h"

class Main_Module;
using namespace std;

// ---------------------------------------------------------------------------
class RxVGA2_Module
{
public: // User declarations
	RxVGA2_Module();
	~RxVGA2_Module(void);
	void Initialize(Main_Module *pMain, char MAddr);
	char getAddr();
	void SetDefaults();
	sPrData *GetPrData()
	{
		return &m_psD;
	};
	void MakeWriteAll();
	bool ChipVsGui(ofstream &out, string Caption, bool bWrAll);
	void MakeRVFFile(ofstream &out);
	// Writes Register - Value format to the file.
	void MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A);
	// Writes RFIF register format to the file.
	bool SetGUIUnderReadback();
	void MakeRegisterFile(ofstream &out);
	void UpdateFormData();
	void SaveConf(ini_t *pini);
	void ReadConf(ini_t *pini);
	void DownloadAllDCCalValues();

	int GetCalVal(int Addr);
	void SetCalVal(int Addr, int Val);
	void SetCalAddr(int Addr);
	void StartCalibration(int Addr);
	char GetCalStatus();
	void SetCalDefaults();
	void RT_SetTestMask(char Mask);
	void UpdateVerRevMask(char Ver, char Rev, char Mask);

	void DCResetCalibration();
	void DCLoadValues(unsigned int value);
	void DCStartCalibration();
	void DCGetCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);

	void RxVGA2PowerOn(bool on);

	int getRXVGA2Gain();
	void setRXVGA2Gain(int Ind);

	void setPwrVGA2Mods(bool state);
	bool getPwrVGA2Mods();

	void setDecode(int index);
	int getDecode();

	void setVga2G_u(int index);
	int getVga2G_u();

	void setPwrDCCurrR(bool state);
	bool getPwrDCCurrR();

	void setPwrDCDACB(bool state);
	bool getPwrDCDACB();

	void setPwrDCCmpB(bool state);
	bool getPwrDCCmpB();

	void setPwrDCDACA(bool state);
	bool getPwrDCDACA();

	void setPwrDCCmpA(bool state);
	bool getPwrDCCmpA();

	void setPwrBG(bool state);
	bool getPwrBG();

	void setPwrBypAB(bool state);
	bool getPwrBypAB();

	void setPwrBypB(bool state);
	bool getPwrBypB();

	void setPwrBypA(bool state);
	bool getPwrBypA();

	void setPwrCurrRef(bool state);
	bool getPwrCurrRef();

	void setVga2GB_t(int index);
	int getVga2GB_t();

	void setVga2GA_t(int index);
	int getVga2GA_t();

	void setDCCalAddr(int index);
	int getDCCalAddr();

	void setVCM(int index);
	int getVCM();

	int lbDC_REGVAL;
	int lblDC_LOCK;
	int lblDC_CLBR_DONE;
	int lblDC_UD;

protected:
	char m_cMAddr;
	sPrData m_psD;
	bool m_bAllowSend;
	int m_DCClbrV[DCClbrCnt];
	char m_cVer;
	char m_cRev;
	char m_cMask;

	void MakeData(int rAddr);

	// VCM code to combobox index recalculation
	int VCM2CMB(int code);
	int CMB2VCM(int cmb);

	Main_Module *pMainModule;

private:
	SelectionContainer cmbDCCalAddr;
	SelectionContainer cmbCalVal;
	SelectionContainer rgrDecode;
	BoolCheckBox chbPwrVGA2Mods;
	BoolCheckBox chbPwrDCCurrR;
	BoolCheckBox chbPwrDCDACB;
	BoolCheckBox chbPwrDCCmpB;
	BoolCheckBox chbPwrDCDACA;
	SelectionContainer cmbVga2G_u;
	SelectionContainer cmbVga2GA_t;
	SelectionContainer cmbVga2GB_t;
	BoolCheckBox chbPwrDCCmpA;
	BoolCheckBox chbPwrBG;
	BoolCheckBox chbPwrBypAB;
	BoolCheckBox chbPwrBypB;
	BoolCheckBox chbPwrBypA;
	BoolCheckBox chbPwrCurrRef;
	SelectionContainer cmbVCM;
};

#endif
