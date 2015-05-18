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
