// -----------------------------------------------------------------------------
// FILE:        "ADF_Module.h"
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
// FILE: 		ADF_Module.h
// DESCRIPTION:	Header for ADF module
// DATE:
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef ADF_MODULE_H
#define ADF_MODULE_H

#include "common.h"
#include <fstream>
using namespace std;

class Main_Module;

class ADF_Module
{
public:
    ADF_Module();
    ~ADF_Module();

    void SendConfig();

    sPrData *GetPrData(){return &m_psD;};
    void SetDefaults();
    void Initialize(Main_Module* pMain, char MAddr);
    void MakeRFIFFile(ofstream &out, char *FRIF_SPI_A);

    void MakeData(int rAddr);
    void UpdateADFFvco();
    void CalculateRN();

    int txtRCnt;
    SelectionContainer cmbABW;
    SelectionContainer cmbLDP;
    int txtNCnt;
    SelectionContainer cmbCPG;
    SelectionContainer rgrCR_i;
    SelectionContainer rgrPD1_i;
    SelectionContainer rgrPD2_i;
    SelectionContainer cmbMOC_i;
    SelectionContainer rgrPDP_i;
    SelectionContainer rgrCPS_i;
    SelectionContainer cmbTC_i;
    SelectionContainer cmbCS1_i;
    SelectionContainer cmbCS2_i;
    SelectionContainer rgrCR_f;
    SelectionContainer rgrPD1_f;
    SelectionContainer rgrPD2_f;
    SelectionContainer cmbMOC_f;
    SelectionContainer rgrPDP_f;
    SelectionContainer rgrCPS_f;
    SelectionContainer cmbTC_f;
    SelectionContainer cmbCS1_f;
    SelectionContainer cmbCS2_f;
    SelectionContainer cmbFL_f;
    SelectionContainer cmbFL_i;
    float txtFref;
    float txtFvco;


protected:
    Main_Module *pMainModule;
    char m_cMAddr;
    sPrData m_psD;
};

#endif // ADF_MODULE_H
