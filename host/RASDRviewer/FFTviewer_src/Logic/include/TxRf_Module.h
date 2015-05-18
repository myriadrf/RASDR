// -----------------------------------------------------------------------------
// FILE: 		TxRf_Module.h
// DESCRIPTION:	Header for TxRf_Module.cpp
// DATE:		2013-05-06
// AUTHOR(s):   Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef TxRf_Module_H
#define TxRf_Module_H
//---------------------------------------------------------------------------
#include "common.h"
#include <fstream>
#include "iniParser.h"

class Main_Module;
using namespace std;
//---------------------------------------------------------------------------
class TxRf_Module
{
public:
	TxRf_Module();
	~TxRf_Module(void);
	void Initialize(Main_Module *pMain, char MAddr);
	char getAddr();
	void SetDefaults();
	sPrData *GetPrData(){return &m_psD;};
	void MakeWriteAll();
	bool ChipVsGui(ofstream &out, string Caption, bool bWrAll);
	void MakeRegisterFile(ofstream &out);
	void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
	void MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A);        //Writes RFIF register format to the file.
	bool SetGUIUnderReadback();
	void SaveConf(ini_t *pini);
	void ReadConf(ini_t *pini);
	void RT_SetTestMask(char Mask);
	void UpdateVerRevMask(char Ver, char Rev, char Mask);

	void CustSet_cmbICT_TXLOBUF(int Ind);

	void setPwrTxRfMods(bool state);
	bool getPwrTxRfMods();

	void setDecode(int index);
	int getDecode();

	void setVga1G_u(int index);
	int getVga1G_u();

	void setVga1DcI(int index);
	int getVga1DcI();

	void setVga1DcQ(int index);
	int getVga1DcQ();

	void setPA(int index);
	int getPA();

	void setVga2G_u(int index);
	int getVga2G_u();

	void setPwrVga1_I(bool state);
	bool getPwrVga1_I();

	void setPwrVga2(bool state);
	bool getPwrVga2();

	void setVga1G_t(int index);
	int getVga1G_t();

	void setVga2G_t(int index);
	int getVga2G_t();

	void setPwrVga1_Q(bool state);
	bool getPwrVga1_Q();

	void setLOOPBBEN(int index);
	int getLOOPBBEN();

	void setPD_DRVAUX(bool state);
	bool getPD_DRVAUX();

	void setPD_PKDET(bool state);
	bool getPD_PKDET();

	void setENVD(int index);
	int getENVD();

	void setENVD2(int index);
	int getENVD2();

	void setPKDBW(int index);
	int getPKDBW();

	void setFST_PKDET(bool state);
	bool getFST_PKDET();

	void setFST_TXHFBIAS(bool state);
	bool getFST_TXHFBIAS();

	void setICT_TXLOBUF(int index);
	int getICT_TXLOBUF();

	void setVBCAS_TXDRV(int index);
	int getVBCAS_TXDRV();

	void setICT_TXMIX(int index);
	int getICT_TXMIX();

	void setICT_TXDRV(int index);
	int getICT_TXDRV();

	void setPD_TXLOBUF(bool state);
	bool getPD_TXLOBUF();

	void setPD_TXDRV(bool state);
	bool getPD_TXDRV();

protected:
	void MakeData(int rAddr);

	char m_cMAddr;
	sPrData m_psD;
	bool m_bAllowSend;
	char m_cVer;
	char m_cRev;
	char m_cMask;
	Main_Module *pMainModule;

private:
	SelectionContainer rgrDecode;
	BoolCheckBox chbPwrTxRfMods;
	SelectionContainer cmbVga1G_u;
	SelectionContainer cmbVga1DcI;
	SelectionContainer cmbVga1DcQ;
	SelectionContainer cmbVga1G_t;
	SelectionContainer cmbVga2G_u;
	SelectionContainer cmbVga2G_t;
	SelectionContainer rgrLOOPBBEN;
	BoolCheckBox chbPD_DRVAUX;
	BoolCheckBox chbPD_PKDET;
	SelectionContainer rgrPA;
	SelectionContainer cmbENVD;
	SelectionContainer cmbENVD2;
	SelectionContainer cmbPKDBW;
	BoolCheckBox chbFST_PKDET;
	BoolCheckBox chbFST_TXHFBIAS;
	SelectionContainer cmbICT_TXLOBUF;
	SelectionContainer cmbVBCAS_TXDRV;
	SelectionContainer cmbICT_TXMIX;
	SelectionContainer cmbICT_TXDRV;
	BoolCheckBox chbPwrVga1_I;
	BoolCheckBox chbPwrVga1_Q;
	BoolCheckBox chbPwrVga2;
	BoolCheckBox chbPD_TXLOBUF;
	BoolCheckBox chbPD_TXDRV;
};
#endif // TxRf_Module_H

