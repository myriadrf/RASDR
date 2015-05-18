// -----------------------------------------------------------------------------
// FILE:        "TxLpf_Module.h"
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
// FILE: 		TxLPF_Module.h
// DESCRIPTION:	Header for TxLPF_Module.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef TxLPF_Module_H
#define TxLPF_Module_H
//---------------------------------------------------------------------------
#include "common.h"

#include <fstream>
#include "iniParser.h"
class Main_Module;
class ADDC_Module;
using namespace std;
//---------------------------------------------------------------------------
class TxLPF_Module
{
public:
	TxLPF_Module();
	~TxLPF_Module(void);
	void Initialize(Main_Module *pMain, char MAddr, ADDC_Module *ADDC);
	char getAddr();
	void SetDefaults();
	sPrData *GetPrData(){return &m_psD;};
	void MakeWriteAll();
	bool ChipVsGui(ofstream &out, string Caption, bool bWrAll);
	void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
	void MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A);        //Writes RFIF register format to the file.
	bool SetGUIUnderReadback();
	void UpdateFormData();
	void SaveConf(ini_t *pini);
	void ReadConf(ini_t *pini);
	void MakeRegisterFile(ofstream &out);
	void DownloadAllDCCalValues();
	void JoinADDC(int addr);

	void RT_SetTestMask(char Mask);
	void UpdateVerRevMask(char Ver, char Rev, char Mask);
	void StartCalibration(int Addr);

	void DCResetCalibration();
	void DCLoadValues(unsigned int value);
	void DCStartCalibration();
	int DCGetCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);

	int GetCalVal(int Addr);
	void SetCalVal(int Addr, int Val);

	char GetCalStatus();
	void SetCalDefaults();

	int  CustGet_DecodeState();
	void CustSet_DecodeState(int ind);
	int  CustGet_LPFTestState();
	void CustSet_LPFTestState(int ind);
	bool CustGet_PwrLpfMods();
	bool CustGet_PwrLpf();
	bool CustGet_PwrDCDac();
	bool CustGet_PwrDCRef();
	bool CustGet_PwrDCCmpr();
	void CustSet_PwrLpfMods(bool state);
	void CustSet_PwrLpf(bool state);
	void CustSet_PwrDCDac(bool state);
	void CustSet_PwrDCRef(bool state);
	void CustSet_PwrDCCmpr(bool state);

	void CustSet_BypassLpfON();
	void CustSet_BypassLpfOFF();
	void LpfPowerOn(bool on);

	void CustSet_EnableDCOffsetCompOnly();
	void CustSet_RestoreDCOffsetCompOnly();
	void CustSet_BypassLPFOnlyOn();
	void CustSet_BypassLPFOnlyOff();
	void CustSet_LPFCALVAL(int Val);
	void CustSet_LPFDCVAL(int Val);

	void setDecode(int index);
	int getDecode();

	void setLpfBw(int index);
	int getLpfBw();

	void setDCOffset(int index);
	int getDCOffset();

	void setRcCal(int index);
	int getRcCal();

	void setPwrLpf(bool state);
	bool getPwrLpf();

	void setPwrDCDac(bool state);
	bool getPwrDCDac();

	void setPwrDCRef(bool state);
	bool getPwrDCRef();

	void setPwrDCCmpr(bool state);
	bool getPwrDCCmpr();

	void setDCCalAddr(int index);
	int getDCCalAddr();

	void setPwrLpfMods(bool state);
	bool getPwrLpfMods();

	void setLpfByp(int index);
	int getLpfByp();

	void setTX_DACBUF_EN(bool state);
	bool getTX_DACBUF_EN();

	int lbDC_REGVAL;
	int lblDC_LOCK;
	int lblDC_CLBR_DONE;
	int lblDC_UD;

protected:
	void MakeData(int rAddr);

	char m_cMAddr;
	sPrData m_psD;
	bool m_bAllowSend;
	int m_DCClbrV[DCClbrCnt];
	ADDC_Module *m_ADDCmodule;
	char m_cVer;
	char m_cRev;
	char m_cMask;
	Main_Module *pMainModule;

private:
	SelectionContainer cmbDCCalAddr;

	SelectionContainer cmbCalVal;
	SelectionContainer rgrDecode;

	BoolCheckBox chbPwrLpfMods;
	BoolCheckBox chbPwrLpf;
	BoolCheckBox chbPwrDCDac;
	BoolCheckBox chbPwrDCRef;
	BoolCheckBox chbPwrDCCmpr;

	SelectionContainer cmbDCOffset;
	SelectionContainer cmbRcCal;

	SelectionContainer cmbLpfBw;
	SelectionContainer rgrLpfByp;
	BoolCheckBox chbTX_DACBUF_EN;

};
#endif // TxLPF_Module_H
