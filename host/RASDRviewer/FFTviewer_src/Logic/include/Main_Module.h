// -----------------------------------------------------------------------------
// FILE: 		Main_Module.h
// DESCRIPTION:	Header for Main_Module.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
#ifndef Main_Module_H
#define Main_Module_H
// ----------------------------------------------------------------------------

#ifdef WIN32


	#include <windows.h>
#endif

#include "iniParser.h"
#include "clUARFCN.h"
#include "common.h"
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

#include "Top_Module.h"
#include "TxLpf_Module.h"
#include "TxRf_Module.h"
#include "RxVGA2_Module.h"
#include "RxFe_Module.h"
#include "TxPLL_Module.h"
#include "ADDC_Module.h"
#include "TxRf_Module.h"
#include "RegisterTest.h"
#include "Board2_Module.h"
#include "TestingModule.h"
#include "Transmitter.h"
#include "ADF_Module.h"

class ConnectionManager;
class Top_Module;
class TxLPF_Module;
class TxPLL_Module;
class TxPLL_Module;
class TxRf_Module;
class RxVGA2_Module;
class RxFe_Module;
class ADDC_Module;
class Board2_Module;
class ADF_Module;
class TestingModule;
class Transmitter;

enum eMessageLogCodes
{
	PROJECT_FILE_OPENED = 0,
	PROJECT_FILE_CREATED,
	PROJECT_FILE_SAVED_AS,
	PROJECT_FILE_SAVED,
	DEFAULT_CONFIG_LOADED,
	CONFIGURATION_SENT_TO_HARDWARE,
	PARALLEL_PORT_INITIALIZED,
	RESET_SIGNAL_ACTIVE,
	RESET_SIGNAL_INACTIVE,
	AUTOMATIC_DOWNLOAD_MODE,
	MANUAL_DOWNLOAD_MODE,
	SERIAL_PORT_INITIALIZED,
	SERIAL_PORT_NOT_ACCESSABLE
};

// ----------------------------------------------------------------------------
class Main_Module
{

public:
	static Main_Module *g_pMain;


	int StartMessagePump();
	int StopMessagePump();

	#ifdef WIN32
	static LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static DWORD WINAPI WinMessagePump(void *param);
	#endif

	void (*updateInterfaceCallback)(int, char *);
	void UpdateInterface(int code, char *opt_Msg);

	Main_Module();
	~Main_Module();
	void initialize();

	void slLogMesg(int num);
	void slLogMesg(const char *msg);

	void FileNewExecute();
	void FileOpenExecute(string link);
	void FileSaveAs(string link);
	void FileSave();

	string getFileName();
	string getApplicationName();
	void getVerRevMask(int &ver, int &rev, int &mask);

	void setAutoDownload(bool state);
	bool getAutoDownload();
	void ReadConfiguration(string link);

	void Download();
	void LoadConfiguration(string sIniName);

	void setRefClk(double dRefClk_Hz);
	double getRefClk();

// ------------------------------------------------------------------------------
// Customer Interface
// ------------------------------------------------------------------------------
	void Cust_CalibrateTx();
	void Cust_CalibrateRx();
	void Cust_CalibrateRxTIA();

	void Cust_setLNASEL(int index);

	void Cust_setRxBypass(int index);
	void Cust_setTxBypass(int index);
	void Cust_setLoopback(int index);

	void Cust_setDLTXBand(int index);
	void Cust_setDLTXChannel(int index);

	void Cust_setULRXBand(int index);
	void Cust_setULRXChannel(int index);

	const string *Cust_getDLTXBands(int &count) const ;
	const string *Cust_getULRXBands(int &count) const ;
	const string *Cust_getDLTXChannels(int &count) const ;
	const string *Cust_getULRXChannels(int &count) const ;

	double Cust_getDLTXFreq()
	{
		return m_UARFCNDef.m_dDLTXFreq;
	};

	double Cust_getULRXFreq()
	{
		return m_UARFCNDef.m_dULRXFreq;
	};

	void CompareChipToGUI();
	void SaveRegisters(string link);
	void MatchGUIToChip();

	void CMLog(int LParam);
	void CMRead(int Wparam, int addr);
	void CMAutoDownload(char addr);
	void CMResetAct();
	void CMResetInAct();
	void CMADDC2LPF(int addr);
	void CMUpdateLNA(int LParam);
	void CMSoftTxPD(int LParam);

	void ShowMessage(string msg);

	void SaveRefClkToReg(double Freq);
	double ReadRefClkFromReg(void);

	void CalLPFCore();
	void SaveUnderRVF_Format(string link, int dec);
	// dec = 1 if format is decimal, dec = 0 if format is hexadecimal;
	void SaveUnderRFIF_Format(string link, int rfifParam);

	bool TestRegisters();
	bool TestRegistersTrial();
   	void EnableSPIClockByMask(int Mask);
	void EnableAllSPIClocks();
	void RestoreAllSPIClocks();
	void setCurrentFileName(string fileName);

	CUARFCN* getUARFCNdata();

	ConnectionManager *getSerPort() { return m_serPort;};
	Top_Module *getTop() { return m_TopModule;};
	TxPLL_Module *getTxPLL() {return m_TxPLLModule;};
	TxPLL_Module *getRxPLL() {return m_RxPLLModule;};
	TxLPF_Module *getTxLpf() {return m_TxLpfModule;};
	TxLPF_Module *getRxLpf() {return m_RxLpfModule;};
	TxRf_Module *getTxRf() {return m_TxRfModule;};
	RxVGA2_Module *getRxVga2() {return m_RxVga2Module;};
	RxFe_Module *getRxFe() {return m_RxFeModule;};
	ADDC_Module *getADDC() {return m_ADDCModule;};
	Board2_Module *getBoard2() {return m_Board2Module;};
	ADF_Module *getADF() { return m_ADFModule;};

	TestingModule *getTesting() { return m_testModule;};
	Transmitter *getTransmitter() { return m_transmitter;};

	RegisterTest *dRegTest;
	TextLog messagesLog;

	void UpdateVerRevMask();

private:
    bool m_initialized;
    TestingModule* m_testModule;
    Transmitter* m_transmitter;

	ConnectionManager *m_serPort;
	Top_Module *m_TopModule;
	TxPLL_Module *m_TxPLLModule;
	TxPLL_Module *m_RxPLLModule;
	TxLPF_Module *m_TxLpfModule;
	TxLPF_Module *m_RxLpfModule;
	TxRf_Module *m_TxRfModule;
	RxVGA2_Module *m_RxVga2Module;
	RxFe_Module *m_RxFeModule;
	ADDC_Module *m_ADDCModule;
	Board2_Module *m_Board2Module;
	ADF_Module *m_ADFModule;

	CUARFCN m_UARFCNDef;
	sPrData m_sInterPD; // Interprocess communication data

	char m_ver;
	char m_rev;
	char m_mask;

	bool autoDownload;
	string sbMain[2];

	string m_sFileName;
	string Caption; // application name

	int m_RFIFParam;

	void SetLnaChain(int iChain);
	void SetBypassLoopback();
	bool FileIsNotEmpty(string filename);
	void LoadAdditionalSettings();


	int m_iRefVCnt;
	double *m_dFVco1;
	double *m_dFVco2;
	double *m_dFVco3;
	double *m_dFVco4;
	int *m_iCVco1;
	int *m_iCVco2;
	int *m_iCVco3;
	int *m_iCVco4;

	// Reference clock MHz
	double m_RefClk;
	char cTempChar;

	// ---System fields-----
	SelectionContainer cmbLNASEL_Cust;
	SelectionContainer cmbRxBypass;
	SelectionContainer cmbTxBypass;
	SelectionContainer cmbLoopback;
};
// ----------------------------------------------------------------------------
#endif //Main_Module_H
