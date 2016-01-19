// -----------------------------------------------------------------------------
// FILE:        "TxPLL_Module.h"
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
// FILE: 		TxPLL_Module.h
// DESCRIPTION:	Header for TxPLL_Module.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef TxPLL_Module_H
#define TxPLL_Module_H
//---------------------------------------------------------------------------
#include "data_FreqVsCap.h"
#include "TextLog.h"
#include "common.h"
#include <iostream>
#include "iniParser.h"
#include <math.h>
#include <string>

class Main_Module;
using namespace std;

//---------------------------------------------------------------------------
// Save PLL settings while calibrating LPF CAL Core
//---------------------------------------------------------------------------
struct F320M_Data
{
    int F320M_rgrDecode;
    bool F320M_chbPwrPllMods;
    int F320M_rgrMODE;
    int F320M_cmbVCOCAP;
    int F320M_rgrSELVCO;
    int F320M_rgrFRANGE;
    double F320M_txtDesFreq;
};

//---------------------------------------------------------------------------
class TxPLL_Module
{
public:
    TxPLL_Module();
    ~TxPLL_Module();
    void Initialize(Main_Module *pMain, char MAddr);
    char getAddr();
    void SetDefaults();
    sPrData *GetPrData()
    {
        return &m_psD;
    };
    void MakeWriteAll();
    void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
    void MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A);        //Writes RFIF register format to the file.
    bool ChipVsGui(ofstream &out, string Caption, bool bWrAll);
    bool SetGUIUnderReadback();
    void MakeRegisterFile(ofstream &out);
    void SaveConf(ini_t *pini);
    void ReadConf(ini_t *pini);
    void SetRefClk(double RefClk);
    double GetRefClk();

    int GetVTuneState();
    void CapAutoTune_D();     //Method according to Danny. Stops, when reaches 0.5V or 2.8V value of Vtune.
    int CapAutoTune_S(TextLog *dVcoCapLog);     //Method according to Srdjan. Founds Cap values for 0.5V and 2.8V value of Vtune and then calculates Cap value for Vtune 1.5V.
    int LookForCap(TextLog *dVcoCapLog);
    bool CapDecrement(int UntilState, TextLog *VcoCapLog);
    bool CapIncrement(int UntilState, TextLog *VcoCapLog);
    int GetVTuneState(int vco, int cap);

    void CustSet_ActiveLOBuff(int ind);
    void CustSet_LoadFrequency(double FreqGHz);

    void PLLPowerOn(bool on);
    void CustSet_cmbOFFUP(int Ind);

    void RT_SetTestMask(char Mask);

    bool BIST_GetState();
    string getBIST_Signature();
    unsigned int BIST_GetSignature();
    void ReadBISTSignature();
    void BIST_ShowSignature(int Signature);
    void BIST_Start();

    void SetPLLTo320MHz();
    void RestoreAfterSetPLLTo320MHz();

    void Calculate();
    double getFrequency();
    void btnChooseVcoCapClick();

    void setDITHEN(int index);
    int getDITHEN();

    void setDITHN(int index);
    int getDITHN();

    void setPwrPllMods(bool checked);
    bool getPwrPllMods();

    void setDecode(int index);
    int getDecode();

    void setMODE(int index);
    int getMODE();

    void setSELVCO(int index);
    int getSELVCO();

    void setFRANGE(int index);
    int getFRANGE();

    void setSELOUT(int index);
    int getSELOUT();

    void setICHP(int index);
    int getICHP();

    void setOFFUP(int index);
    int getOFFUP();

    void setOFFDOWN(int index);
    int getOFFDOWN();

    void setVCOCAP(int index);
    int getVCOCAP();

    void setBCODE(int index);
    int getBCODE();

    void setACODE(int index);
    int getACODE();

    void setENLOBUF(bool checked);
    bool getENLOBUF();

    void setENLAMP(bool checked);
    bool getENLAMP();

    void setPFDPD(bool checked);
    bool getPFDPD();

    void setENFEEDDIV(bool checked);
    bool getENFEEDDIV();

    void setPD_VCOCOMP_SX(bool checked);
    bool getPD_VCOCOMP_SX();

    void setOEN_TSTD_SX(bool checked);
    bool getOEN_TSTD_SX();

    void setPASSEN_TSTOD_SD(bool checked);
    bool getPASSEN_TSTOD_SD();

    void btnReadVtuneClick();
    void Tune();

    void setPFDCLKP(bool checked);
    bool getPFDCLKP();

    void setTRI(bool checked);
    bool getTRI();

    void setPOL(bool checked);
    bool getPOL();

    void setAUTOBYP(bool checked);
    bool getAUTOBYP();

    void setEN_PFD_UP(bool checked);
    bool getEN_PFD_UP();

    void setBYPVCOREG(bool checked);
    bool getBYPVCOREG();

    void setPDVCOREG(bool checked);
    bool getPDVCOREG();

    void setFSTVCOBG(bool checked);
    bool getFSTVCOBG();

    void setVOVCOREG(int index);
    int getVOVCOREG();

    void setBCLKSEL(int index);
    int getBCLKSEL();

    void setBINSEL(int index);
    int getBINSEL();

    int lblNint_info;
    int lblNfrac_info;
    double lblDiv_info;
    double lblROutF_info;
    double lblVcoF_info;

    int lblN_info;
    double lblFvcoInt_info;
    double lblFvco2Int_info;
    double lblFvco4Int_info;
    double lblFvco8Int_info;
    double lblFvco16Int_info;

    //VCO Comparators
    LabelString lblVTUNE_H;
    LabelString lblVTUNE_L;

    TextLog *dlgVcoCapLog;
    Data_FreqVsCap *m_FreqVsCap;

protected:
    Main_Module *pMainModule;
    char m_cMAddr;
    sPrData m_psD;
    F320M_Data m_F320M_Data;

    double m_dRefF;
    int m_iPrevVCO;
    bool m_bAllowSend;

    void MakeData(int rAddr);
    void CalcFreq(double dDF, double &rdRF, double &dDiv, int &iDInd, int &Nint, int &Nfrac, int &iVCO, double &Fvco);
    void CalcFreqDannyWhish(double dDF, double &rdRF, double &dDiv, int &iDInd, int &Nint, int &Nfrac, int &iVCO, double &Fvco);
    void CalcPLLData();
    int AutoSelectVcoCap(double Freq, int iVcoInd);
    void ChooseVcoCap();
    void CalcIntPllData();

private:
    // Decoding
    SelectionContainer rgrDecode;

    //Test Signal
    BoolCheckBox chbOEN_TSTD_SX;
    BoolCheckBox chbPASSEN_TSTOD_SD;

    //Power Control
    BoolCheckBox chbPwrPllMods;
    BoolCheckBox chbENLOBUF;
    BoolCheckBox chbENLAMP;
    BoolCheckBox chbENFEEDDIV;
    BoolCheckBox chbPFDPD;
    BoolCheckBox chbPD_VCOCOMP_SX;
    BoolCheckBox chbAUTOBYP;
    BoolCheckBox chbEN_PFD_UP;
    BoolCheckBox chbPFDCLKP;
    BoolCheckBox chbTRI;
    BoolCheckBox chbPOL;

    //VCO Output
    SelectionContainer rgrVOVCOREG;

    //Various VCO Controls
    BoolCheckBox chbBYPVCOREG;
    BoolCheckBox chbPDVCOREG;
    BoolCheckBox chbFSTVCOBG;


    //VCO Capacitance
    LabelString lblAutoTuneStatus;
    BoolCheckBox chbCapLog;
    SelectionContainer rgrVCOCAP;

    //CP Current and Offset
    SelectionContainer rgrICHP;
    SelectionContainer rgrOFFUP;
    SelectionContainer rgrOFFDOWN;

    //Output Buffer
    SelectionContainer rgrSELOUT;

    //Dithering Control
    BoolCheckBox chbDITHEN;
    SelectionContainer rgrDITHN;

    //=======Frequency control============
    //PLL Mode
    SelectionContainer rgrMODE;

    //Current VCO
    SelectionContainer rgrSELVCO;

    //MUX/DIV Selection
    SelectionContainer rgrFRANGE;

    //A and B Counter Values
    SelectionContainer rgrACODE;
    SelectionContainer rgrBCODE;

    //Output Frequency, GHz
    double dblDesFreq;

    //========================================

    //=================BIST Control===========
    // DSMN/BIST Clock
    SelectionContainer rgrBCLKSEL;
    // DSMN/BIST Input
    SelectionContainer rgrBINSEL;

    //BIST State

    //BIST Signature
    LabelString lblBSIG;

    //========================================
};
#endif  // TxPLL_Module_H
