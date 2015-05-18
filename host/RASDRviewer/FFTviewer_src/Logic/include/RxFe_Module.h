// -----------------------------------------------------------------------------
// FILE: 		RxFe_Module.h
// DESCRIPTION:	Header for RxFe_Module.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef RxFe_Module_H
#define RxFe_Module_H
//---------------------------------------------------------------------------
#include "common.h"
#include <fstream>
#include "iniParser.h"

class Main_Module;
using namespace std;
//---------------------------------------------------------------------------
class RxFe_Module
{
	public:		// User declarations
	RxFe_Module();
	~RxFe_Module();
	void Initialize(Main_Module *pMain, char MAddr);
	char getAddr();
	void SetDefaults();
	//void SetGuiDecode();
	sPrData *GetPrData(){return &m_psD;};
	void MakeWriteAll();
	bool ChipVsGui(ofstream &out, string Caption, bool bWrAll);
	void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
	void MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A);        //Writes RFIF register format to the file.
	bool SetGUIUnderReadback();
	void MakeRegisterFile(ofstream &out);
	void SaveConf(ini_t *pini);
	void ReadConf(ini_t *pini);
	void RT_SetTestMask(char Mask);

	void CustSet_ActiveLNA(int ind);
	void PowerOn(bool on);
	void LNAPowerOn(bool on);
	void CustSet_cmbRDLINT_LNA_RXFE(int Ind);

	void CustSet_DCOffsetCancellationI(int ind);
	void CustSet_DCOffsetCancellationQ(int ind);
	int  CustGet_DCOffsetCancellationI();
	int  CustGet_DCOffsetCancellationQ();

	void setDecode(int index);
	int getDecode();

	void setPwrRxFeMods(bool state);
	bool getPwrRxFeMods();

	void setIN1SEL_MIX_RXFE(int index);
	int getIN1SEL_MIX_RXFE();

	void setDCOFF_I_RXFE(int index);
	int getDCOFF_I_RXFE();

	void setINLOAD_LNA_RXFE(bool state);
	bool getINLOAD_LNA_RXFE();

	void setDCOFF_Q_RXFE(int index);
	int getDCOFF_Q_RXFE();

	void setXLOAD_LNA_RXFE(bool state);
	bool getXLOAD_LNA_RXFE();

	void setIP2TRIM_I_RXFE(int index);
	int getIP2TRIM_I_RXFE();

	void setIP2TRIM_Q_RXFE(int index);
	int getIP2TRIM_Q_RXFE();

	void setG_LNA_RXFE(int index);
	int getG_LNA_RXFE();

	void setLNASEL_RXFE(int index);
	int getLNASEL_RXFE();

	void setCBE_LNA_RXFE(int index);
	int getCBE_LNA_RXFE();

	void setRFB_TIA_RXFE(int index);
	int getRFB_TIA_RXFE();

	void setCFB_TIA_RXFE(int index);
	int getCFB_TIA_RXFE();

	void setRDLEXT_LNA_RXFE(int index);
	int getRDLEXT_LNA_RXFE();

	void setRDLINT_LNA_RXFE(int index);
	int getRDLINT_LNA_RXFE();

	void setICT_MIX_RXFE(int index);
	int getICT_MIX_RXFE();

	void setICT_LNA_RXFE(int index);
	int getICT_LNA_RXFE();

	void setICT_TIA_RXFE(int index);
	int getICT_TIA_RXFE();

	void setICT_MXLOB_RXFE(int index);
	int getICT_MXLOB_RXFE();

	void setLOBN_MIX_RXFE(int index);
	int getLOBN_MIX_RXFE();

	void setPD_TIA_RXFE(bool state);
	bool getPD_TIA_RXFE();

	void setPD_MXLOB_RXFE(bool state);
	bool getPD_MXLOB_RXFE();

	void setPD_MIX_RXFE(bool state);
	bool getPD_MIX_RXFE();

	void setPD_LNA_RXFE(bool state);
	bool getPD_LNA_RXFE();

	void setRINEN_MIX_RXFE(bool state);
	bool getRINEN_MIX_RXFE();

	void setG_FINE_LNA3_RXFE(int index);
	int getG_FINE_LNA3_RXFE();

protected:
	char m_cMAddr;
	sPrData m_psD;
	bool m_bAllowSend;
	void MakeData(int rAddr);

	Main_Module *pMainModule;

private:
	SelectionContainer cmbDCOFF_I_RXFE;
	SelectionContainer cmbDCOFF_Q_RXFE;
	SelectionContainer cmbIP2TRIM_I_RXFE;
	SelectionContainer cmbIP2TRIM_Q_RXFE;
	SelectionContainer rgrDecode;
	SelectionContainer cmbICT_MIX_RXFE;
	SelectionContainer cmbICT_MXLOB_RXFE;
	SelectionContainer cmbLOBN_MIX_RXFE;
	BoolCheckBox chbPwrRxFeMods;
	BoolCheckBox chbINLOAD_LNA_RXFE;
	BoolCheckBox chbXLOAD_LNA_RXFE;
	SelectionContainer cmbG_LNA_RXFE;
	SelectionContainer cmbLNASEL_RXFE;
	SelectionContainer cmbRDLEXT_LNA_RXFE;
	SelectionContainer cmbRDLINT_LNA_RXFE;
	SelectionContainer cmbICT_LNA_RXFE;
	SelectionContainer cmbCBE_LNA_RXFE;
	SelectionContainer cmbRFB_TIA_RXFE;
	SelectionContainer cmbCFB_TIA_RXFE;
	SelectionContainer cmbICT_TIA_RXFE;
	BoolCheckBox chbPD_TIA_RXFE;
	BoolCheckBox chbPD_MXLOB_RXFE;
	BoolCheckBox chbPD_LNA_RXFE;
	BoolCheckBox chbPD_MIX_RXFE;
	SelectionContainer cmbIN1SEL_MIX_RXFE;
	BoolCheckBox chbRINEN_MIX_RXFE;
	SelectionContainer cmbG_FINE_LNA3_RXFE;
};
#endif	// RxFe_Module_H
