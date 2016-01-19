// -----------------------------------------------------------------------------
// FILE:        "Top_Module.h"
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
// FILE: 		Top_Module.h
// DESCRIPTION:	Header for TopModule.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef Top_Module_H
#define Top_Module_H
//---------------------------------------------------------------------------
#include "common.h"
#include <fstream>
#include "iniParser.h"

class Main_Module;

using namespace std;
typedef INI <string, string, string> ini_t;

//---------------------------------------------------------------------------
class Top_Module
{
public:
    Top_Module();
    ~Top_Module();

//======================Iterface===============================================
    void setDecode(int index);
    int getDecode();

    void setSpiMode(int index);
    int getSpiMode();

    void setDsmRst(int index);
    int getDsmRst();

    void setRxTestModeEn(bool state);
    bool getRxTestModeEn();

    void setSpiClkBuf(int index, bool state);
    bool getSpiClkBuf(int index);
    void SpiClkBufUpdate();

    void setRFLB(int index);
    int getRFLB();

    void setLpfCalRst(bool state);
    bool getLpfCalRst();

    void setLpfCalEn(bool state);
    bool getLpfCalEn();

    void setLpfCalEnEnf(bool state);
    bool getLpfCalEnEnf();

    void setLpfCalCode(int index);
    int getLpfCalCode();

    void setLpfCalBw(int index);
    int getLpfCalBw();

    void setPwrTopMods(bool state);
    bool getPwrTopMods();

    void setPwrSoftTx(bool state);
    bool getPwrSoftTx();

    void setPwrSoftRx(bool state);
    bool getPwrSoftRx();

    void setPwrLpfCal(bool state);
    bool getPwrLpfCal();

    void setPwrRfLbsw(bool state);
    bool getPwrRfLbsw();

    void setDCCalAddr(int index);
    int getDCCalAddr();

    void swResetOn();
    void swResetOff();

    void setBBLB(int index);
    int getBBLB();

    void setCLKSEL_LPFCAL(int index);
    int getCLKSEL_LPFCAL();

    void setPD_CLKLPFCAL(bool state);
    bool getPD_CLKLPFCAL();

    void setRXOUTSW(int index);
    int getRXOUTSW();

    void setFDDTDD(int index);
    int getFDDTDD();

    void setTDDMOD(int index);
    int getTDDMOD();

    void setPDXCOBUF(bool state);
    bool getPDXCOBUF();

    void setSLFBXCOBUF(bool state);
    bool getSLFBXCOBUF();

    void setBYPXCOBUF(bool state);
    bool getBYPXCOBUF();

    void ReadRCCALValues(int &rccal);
    void DCResetCalibration();
    void DCLoadValues(unsigned int value);
    void DCStartCalibration();

    void DCGetCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);
//=============================================================================

    void Initialize(Main_Module *pMain, char MAddr);
    void SetDefaults();
    sPrData *GetPrData()
    {
        return &m_psD;
    };
    void MakeWriteAll();
    void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
    void MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A);        //Writes RFIF register format to the file.
    void MakeRegisterFile(ofstream &out);   //Writes register map to the file. According to the customer wish.
    bool ChipVsGui(ofstream &out, string Caption, bool bWrAll); //When bWrAll = false, it writes the differences between Chip and GUI, when true, writes all configuration.
    bool SetGUIUnderReadback();
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

    void EnableAllSPIClocks();    //Enables all SPI clock buffers
    void EnableSPIClocksByMask(int mask);    //Enables all SPI clock buffers by mask
    void RestoreAllSPIClocks();   //Restores SPI clock bufer states according to GUI settings

    void CustSet_Tia2OutON();
    void CustSet_Tia2OutOFF();
    void CustSet_LPFBandwidth(int ind);
    void CustSet_SetRFLB(int ind);
    void CustSet_SetBBLB(int ind);
    void TopPowerOn(bool On);
    void CustSet_EnableLPFCAL(bool On);
    void CustSet_ResetLPFCAL(bool Active);
    void CustGet_LPFCALVal(int &DCCALVal, int &LPFCALVal);
    bool CustGet_PD_CLKLPFCAL();
    void CustSet_PD_CLKLPFCAL(bool Val);
    void CustSet_rgrRXOUTSW(int Ind);
    void CustSet_PLLCLKOUT(bool Enabled);
    bool CustSet_SofTxOnOff(bool On);
    bool CustSet_SofRxOnOff(bool On);

    int GetLPFTuningClockInd();
    void SetLPFTuningClockInd(int Ind);
    void RT_SetTestMask(char Mask);

protected:
    char m_cMAddr;
    sPrData m_psD;
    bool m_bAllowSend;
    int m_DCClbrV[DCClbrCnt];

    void MakeData(int rAddr);

private:
    Main_Module *pMainModule;

    //XCO Buffer
    BoolCheckBox chbPDXCOBUF;
    BoolCheckBox chbSLFBXCOBUF;
    BoolCheckBox chbBYPXCOBUF;

    // Power Control
    BoolCheckBox chbPwrTopMods;
    BoolCheckBox chbPwrSoftTx;
    BoolCheckBox chbPwrSoftRx;
    BoolCheckBox chbPwrLpfCal;
    BoolCheckBox chbPwrRfLbsw;

    // TRX LPD Calibration
    BoolCheckBox chbPD_CLKLPFCAL;
    BoolCheckBox chbLpfCalRst;
    BoolCheckBox chbLpfCalEnEnf;
    BoolCheckBox chbLpfCalEn;

    // Rx Bypass Mode
    BoolCheckBox chbRxTestModeEn;

    // Global Reset
    BoolCheckBox chbReset;

    // RF Loopback Control
    SelectionContainer rgrRFLB;

    // BB Loopback Control
    SelectionContainer rgrBBLB;

    // RX Out/ADC In Switch
    SelectionContainer rgrRXOUTSW;

    // TDD Mode Selection
    SelectionContainer rgrTDDMOD;

    // FDD/TDD Selection
    SelectionContainer rgrFDDTDD;

    // Decode
    SelectionContainer rgrDecode;

    // SPI Port Mode
    SelectionContainer rgrSpiMode;

    // LPF Tuning Clock
    SelectionContainer rgrCLKSEL_LPFCAL;

    // DSM Soft Reset
    SelectionContainer rgrDsmRst;

    //Clock Buffers
    bool chbaSpiClkBuf[7];

    // CAL Module Address
    SelectionContainer cmbDCCalAddr;

    SelectionContainer rgrCalVal;

    // Calibration Value
    SelectionContainer rgrLpfCalCode;
    SelectionContainer rgrLpfCalBw;

    // form data
    int lblDC_REGVAL;		//CalibrationValue;
    int lblDC_LOCK;			//LockPattern;
    int lblDC_CLBR_DONE;	//CalibrationStatus
    int lblDC_UD;			//ComparatorValue
    int lblRCCAL_LPFCAL;
};

#endif  // topModule_H
