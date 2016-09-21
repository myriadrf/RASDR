// -----------------------------------------------------------------------------
// FILE: 		Main_Module.cpp
// DESCRIPTION:
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "Main_Module.h"
#include "ConnectionManager.h"

#include "TestingModule.h"
#include "CallbackCodes.h"
#include "Board2_Module.h"
#include "ADF_Module.h"
#include "TimeCOunter.h"

#ifdef WIN32
    #include <windows.h>
    #include <dbt.h>
	HINSTANCE hinst;
	HWND hwnd;
	DWORD threadID;
	HANDLE threadHandle;
#endif
// ---------------------------------------------------------------------
using namespace std;

GUID allGUIDs = {0xA5DCBF10L, 0x6530, 0x11D2, {0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED}};

Main_Module* Main_Module::g_pMain = NULL;

/**
	Creates thread that runs Windows message loop. It is needed
	to be able to detect chip connection and disconnection.
*/
int Main_Module::StartMessagePump()
{
#ifdef WIN32
	threadHandle = CreateThread(NULL, 0, WinMessagePump, NULL, 0, &threadID);
	if (threadID == NULL)
    {
		return 0;
    }
#endif
	return 1;
}

/**
	Stops windows message loop thread.
*/
int Main_Module::StopMessagePump()
{
    #ifdef WIN32
	if(threadID != NULL)
	{
		CloseHandle(threadHandle);
		return 1;
	}
	#endif
	return 0;
}

/**
	Processes Windows messages, reacts to device changes.
*/
#ifdef WIN32
LRESULT CALLBACK Main_Module::WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage (0);
        return 0;
    case WM_DEVICECHANGE:
        PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;
        string devname;
        string stemp;
        bool chipEvent = false;
        if(pHdr)
        {
            switch( pHdr->dbch_devicetype )
            {
                //check if device pid and vid matches chip
                case DBT_DEVTYP_DEVICEINTERFACE:
                    PDEV_BROADCAST_DEVICEINTERFACE pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
                    devname = pDevInf->dbcc_name;
                    int p1 = devname.find_first_of('#');
                    if(p1 != string::npos )
                        ++p1;
                    stemp = devname.substr(p1, 4);
                    transform(stemp.begin(), stemp.end(),stemp.begin(), ::toupper);
                    if(stemp == "VID_")
                    {
                        stemp = devname.substr(p1+4, 4);
                        transform(stemp.begin(), stemp.end(),stemp.begin(), ::toupper);
                        if(stemp == "04B4")
                            chipEvent = true;
                        else
                            break;
                    }
                    stemp = devname.substr(p1+9, 4);
                    transform(stemp.begin(), stemp.end(),stemp.begin(), ::toupper);
                    if(stemp == "PID_")
                    {
                        stemp = devname.substr(p1+13, 4);
                        transform(stemp.begin(), stemp.end(),stemp.begin(), ::toupper);
                        if(stemp == "00F1")
                            chipEvent = true;
                        else
                            break;
                    }
                    if(chipEvent)
                    {
                        g_pMain->getTesting()->StopSdramRead();
                        g_pMain->getSerPort()->DevicesChanged();
                    }
                    break;
            }
        }
        break;
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}
#endif

/**
	Creates invisible window to receive Windows messages and runs Windows messages loop
*/
#ifdef WIN32
DWORD WINAPI Main_Module::WinMessagePump(void *param)
{
	MSG msg;
	WNDCLASS wc;
    HANDLE hInstance = GetModuleHandle(NULL);
    wc.style = 0;                                   // Class style
    wc.lpfnWndProc = (WNDPROC) WndProc;             // Window procedure address
    wc.cbClsExtra = 0;                              // Class extra bytes
    wc.cbWndExtra = 0;                              // Window extra bytes
    wc.hInstance = (HINSTANCE)hInstance;            // Instance handle
    wc.hIcon = LoadIcon (NULL, IDI_WINLOGO);        // Icon handle
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);      // Cursor handle
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); // Background color
    wc.lpszMenuName = NULL;                         // Menu name
    wc.lpszClassName = "MyWndClass";                // WNDCLASS name

    if( !RegisterClass (&wc) )
        cout << "problems registering hidden window" << endl;

	hwnd = CreateWindow (
               "MyWndClass",               // WNDCLASS name
               "InvisibleWindowForNotifications",      // Window title
               WS_DISABLED,                // Window style
               CW_USEDEFAULT,              // Horizontal position
               CW_USEDEFAULT,              // Vertical position
               CW_USEDEFAULT,              // Initial width
               CW_USEDEFAULT,              // Initial height
               //HWND_DESKTOP,               // Handle of parent window
               NULL,               // Handle of parent window
               NULL,                       // Menu handle
               NULL,                       // Application's instance handle
               NULL                        // Window-creation data
           );

	UpdateWindow (hwnd);

	//register device guid for notifications
    DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;

    ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
    NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    NotificationFilter.dbcc_classguid = allGUIDs;

    HDEVNOTIFY hDeviceNotify = RegisterDeviceNotification(
        hwnd,                       // events recipient
        &NotificationFilter,        // type of device
        DEVICE_NOTIFY_WINDOW_HANDLE // type of recipient handle
        );

    BOOL bRet;
    while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
			TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    // Return the exit code to the system.
    return msg.wParam;
}
#endif

/**
	Initializes main module variables and callback function pointers.
*/
Main_Module::Main_Module()
{
    m_initialized = false;
	g_pMain = this;
	m_RefClk = 0;

	sbMain[1] = " Automatic Download Mode";
	updateInterfaceCallback = NULL;

	m_TopModule = NULL;
	m_RxLpfModule = NULL;
	m_TxLpfModule = NULL;
	m_TxRfModule = NULL;
	m_RxVga2Module = NULL;
	m_RxFeModule = NULL;
	m_TxPLLModule = NULL;
	m_RxPLLModule = NULL;
	m_ADDCModule = NULL;
	m_Board2Module = NULL;
	m_ADFModule = NULL;
	m_serPort = new ConnectionManager(this);
	if (!m_serPort->IsOpen())
	{
		autoDownload = false;
		slLogMesg(SERIAL_PORT_NOT_ACCESSABLE);
	}
	else
	{
		autoDownload = true;
		slLogMesg(SERIAL_PORT_INITIALIZED);
	};


	m_iRefVCnt = 3;
	m_dFVco1 = new double[m_iRefVCnt];
	m_dFVco2 = new double[m_iRefVCnt];
	m_dFVco3 = new double[m_iRefVCnt];
	m_dFVco4 = new double[m_iRefVCnt];
	m_iCVco1 = new int[m_iRefVCnt];
	m_iCVco2 = new int[m_iRefVCnt];
	m_iCVco3 = new int[m_iRefVCnt];
	m_iCVco4 = new int[m_iRefVCnt];
	memset(m_dFVco1, 0, sizeof(double)*m_iRefVCnt);
	memset(m_dFVco2, 0, sizeof(double)*m_iRefVCnt);
	memset(m_dFVco3, 0, sizeof(double)*m_iRefVCnt);
	memset(m_dFVco4, 0, sizeof(double)*m_iRefVCnt);

	// For interprocess communication
	m_sInterPD.iLen = 1;
	m_sInterPD.cCmdW = new char[m_sInterPD.iLen];
	m_sInterPD.cDataW = new char[m_sInterPD.iLen];
	m_sInterPD.cCmdR = new char[m_sInterPD.iLen];
	m_sInterPD.cDataR = new char[m_sInterPD.iLen];
	m_sInterPD.iRInd = new int[m_sInterPD.iLen];
	m_sInterPD.iWInd = new int[m_sInterPD.iLen];
	memset(m_sInterPD.cCmdW, 0, m_sInterPD.iLen);
	memset(m_sInterPD.cDataW, 0, m_sInterPD.iLen);
	memset(m_sInterPD.cCmdR, 0, m_sInterPD.iLen);
	memset(m_sInterPD.cDataR, 0, m_sInterPD.iLen);
	memset(m_sInterPD.iRInd, 0, m_sInterPD.iLen*sizeof(int));
	memset(m_sInterPD.iWInd, 0, m_sInterPD.iLen*sizeof(int));
	m_sInterPD.iToR = m_sInterPD.iLen;
	m_sInterPD.iToW = m_sInterPD.iLen;

	sbMain[1] = " Automatic Download Mode";
	sbMain[2] = " Ref. Clock, Hz: 40000000";

	m_ver = 0;
	m_rev = 0;
	m_mask = 0;
}

/**
	Deletes dynamic variables and stop windows message loop.
*/
Main_Module::~Main_Module()
{
	g_pMain = NULL;

	delete[]m_sInterPD.cCmdW;
	delete[]m_sInterPD.cDataW;
	delete[]m_sInterPD.cCmdR;
	delete[]m_sInterPD.cDataR;
	delete[]m_sInterPD.iRInd;
	delete[]m_sInterPD.iWInd;

	delete[]m_dFVco1;
	delete[]m_dFVco2;
	delete[]m_dFVco3;
	delete[]m_dFVco4;

	delete[]m_iCVco1;
	delete[]m_iCVco2;
	delete[]m_iCVco3;
	delete[]m_iCVco4;

	StopMessagePump();
}

/**
	Creates new project file and sets configuration to default values.
*/
void Main_Module::FileNewExecute()
{
	setCurrentFileName("untitled.prj");

	m_TopModule->SetDefaults();
	m_TxLpfModule->SetDefaults();
	m_RxLpfModule->SetDefaults();
	m_TxRfModule->SetDefaults();
	m_RxVga2Module->SetDefaults();
	m_RxFeModule->SetDefaults();
	m_TxPLLModule->SetDefaults();
	m_RxPLLModule->SetDefaults();
	m_ADDCModule->SetDefaults();
	//m_BoardModule->SetDefaults();

	LoadAdditionalSettings();

	slLogMesg(PROJECT_FILE_CREATED);
}

/**
	Checks if given file is not empty.
*/
bool Main_Module::FileIsNotEmpty(string filename)
{
	long length;
	FILE *stream;

	stream = fopen(filename.c_str(), "r");

	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fclose(stream);

	return (length > 0);
}

/**
	Loads configuration settings from file.
*/
void Main_Module::LoadConfiguration(string sIniName)
{
	ini_t *ini;
	ini = new ini_t(sIniName); // we will serialize the data from the file
	ini->Parse();

	m_UARFCNDef.ReadConf(ini);
	m_TopModule->ReadConf(ini);
	m_TxLpfModule->ReadConf(ini);
	m_RxLpfModule->ReadConf(ini);
	m_TxRfModule->ReadConf(ini);
	m_RxVga2Module->ReadConf(ini);
	m_RxFeModule->ReadConf(ini);
	m_TxPLLModule->ReadConf(ini);
	m_RxPLLModule->ReadConf(ini);
	m_ADDCModule->ReadConf(ini);

	m_RefClk = m_TxPLLModule->GetRefClk();

	delete ini;

	slLogMesg(PROJECT_FILE_OPENED);
};

/**
	Loads given configuration file and send configuration to the chip.
	@param filename filename or full path to file.
*/
void Main_Module::FileOpenExecute(string filename)
{
	setCurrentFileName(filename);
	LoadConfiguration(filename);
	slLogMesg(PROJECT_FILE_OPENED);

	Download();
}

/**
	Enables all SPI clocks in Top SPI.
*/
void Main_Module::EnableAllSPIClocks()
{
	// Enable all SPI clocks in TopSPI
	m_TopModule->EnableAllSPIClocks();
	m_serPort->SPI_Write(m_TopModule->GetPrData());
	milSleep(5);
};

/**
	Restores all SPI clocks in Top SPI.
*/
void Main_Module::RestoreAllSPIClocks()
{
	// Enable all SPI clocks in TopSPI
	m_TopModule->RestoreAllSPIClocks();
	m_serPort->SPI_Write(m_TopModule->GetPrData());
	milSleep(5);
};

/**
	Resets chip and sends all configuration to the chip.
*/
void Main_Module::Download()
{
	// ==== Perform Global Reset First ===
	m_serPort->SPI_Rst();
	milSleep(5);
	// ===================================

	m_TopModule->MakeWriteAll();
	m_TxLpfModule->MakeWriteAll();
	m_RxLpfModule->MakeWriteAll();
	m_TxRfModule->MakeWriteAll();
	m_RxVga2Module->MakeWriteAll();
	m_RxFeModule->MakeWriteAll();
	m_TxPLLModule->MakeWriteAll();
	m_RxPLLModule->MakeWriteAll();

	// Enable all SPI clocks in TopSPI
	// EnableAllSPIClocks();

	// TxLpf
	m_serPort->SPI_Write(m_TxLpfModule->GetPrData());
	m_TxLpfModule->DownloadAllDCCalValues();
	milSleep(5);
	// RxLpf
	m_serPort->SPI_Write(m_RxLpfModule->GetPrData());
	m_RxLpfModule->DownloadAllDCCalValues();
	milSleep(5);
	// TxRf
	m_serPort->SPI_Write(m_TxRfModule->GetPrData());
	milSleep(5);

	// RxVga2
	m_serPort->SPI_Write(m_RxVga2Module->GetPrData());
	m_RxVga2Module->DownloadAllDCCalValues();
	milSleep(5);

	// RxFe
	m_serPort->SPI_Write(m_RxFeModule->GetPrData());
	milSleep(5);	// TxPLL
	m_serPort->SPI_Write(m_TxPLLModule->GetPrData());
	milSleep(5);

	// RxPLL
	m_serPort->SPI_Write(m_RxPLLModule->GetPrData());
	milSleep(5);	// Top
	m_TopModule->MakeWriteAll();
	m_serPort->SPI_Write(m_TopModule->GetPrData());
	milSleep(5);

	slLogMesg(CONFIGURATION_SENT_TO_HARDWARE);
}

/**
	Saves chip configuration to file.
*/
void Main_Module::FileSave()
{
	ini_t *ini;
	ini = new ini_t(m_sFileName);

	m_UARFCNDef.SaveConf(ini);
	m_TopModule->SaveConf(ini);
	m_TxLpfModule->SaveConf(ini);
	m_RxLpfModule->SaveConf(ini);
	m_TxRfModule->SaveConf(ini);
	m_RxVga2Module->SaveConf(ini);
	m_RxFeModule->SaveConf(ini);
	m_TxPLLModule->SaveConf(ini);
	m_RxPLLModule->SaveConf(ini);
	m_ADDCModule->SaveConf(ini);

	ini->Save();

	slLogMesg(PROJECT_FILE_SAVED);
	delete ini;
}

/**
	Returns current project name
*/
string Main_Module::getFileName()
{
	return m_sFileName;
}

/**
	Returns full application name including project directory.
*/
string Main_Module::getApplicationName()
{
	return Caption;
}

/**
	Returns chip version, revision and mask
*/
void Main_Module::getVerRevMask(int &ver, int &rev, int &mask)
{
	ver = (int)m_ver;
	rev = (int)m_rev;
	mask = (int)m_mask;
}


/**
	Initializes main module also creates and initializes Top, RxLpf, TxLpf,
	TxRf, RxVGA2, RxFe, TxPLL, RxPLL, ADDC, Board submodules. Sends additional settings
	to the chip to override default hardware settings.
*/
void Main_Module::initialize()
{
    if(m_initialized)
        return;
    m_initialized = true;

	dRegTest = new RegisterTest();
	m_testModule = new TestingModule(this);
//test 12/7	m_transmitter = new Transmitter(this);
	StartMessagePump();
	autoDownload = true;
	// Clear Messages log
	messagesLog.Clear();

	m_TopModule = new Top_Module();
	m_RxLpfModule = new TxLPF_Module();
	m_TxLpfModule = new TxLPF_Module();
	m_TxRfModule = new TxRf_Module();
	m_RxVga2Module = new RxVGA2_Module();
	m_RxFeModule = new RxFe_Module();
	m_TxPLLModule = new TxPLL_Module();
	m_RxPLLModule = new TxPLL_Module();
	m_ADDCModule = new ADDC_Module();
	m_Board2Module = new Board2_Module();
	m_ADFModule = new ADF_Module();

	assert(m_TopModule != NULL);
	assert(m_RxLpfModule != NULL);
	assert(m_TxLpfModule != NULL);
	assert(m_TxRfModule != NULL);
	assert(m_RxVga2Module != NULL);
	assert(m_RxFeModule != NULL);
	assert(m_TxPLLModule != NULL);
	assert(m_RxPLLModule != NULL);
	assert(m_ADDCModule != NULL);
	assert(m_Board2Module != NULL);
	assert(m_ADFModule != NULL);

	m_TopModule->Initialize(this, TopAddr);
	m_ADDCModule->Initialize(this, RxLpfAddr);
	m_RxLpfModule->Initialize(this, RxLpfAddr, m_ADDCModule);
	m_TxLpfModule->Initialize(this, TxLpfAddr, NULL);
	m_TxRfModule->Initialize(this, TxRFAddr);
	m_RxVga2Module->Initialize(this, RxVGA2Addr);
	m_RxFeModule->Initialize(this, RxFEAddr);
	m_TxPLLModule->Initialize(this, TxPllAddr);
	m_RxPLLModule->Initialize(this, RxPllAddr);
	m_Board2Module->Initialize(getSerPort());
	m_ADFModule->Initialize(this, ADFAddr);

	m_UARFCNDef.Initialize();
	//m_UARFCNDef->LoadBands();

	// Project by default
	setCurrentFileName("untitled.prj");
	setRefClk(30720000);

	// ===============================================================
	LoadAdditionalSettings();
	// ===============================================================

	slLogMesg(DEFAULT_CONFIG_LOADED);
	UpdateVerRevMask();

	m_testModule->SetConnectionManager(getSerPort());
}

/**
	Overwrites hardware defaults
*/
void Main_Module::LoadAdditionalSettings()
{
	// Top SPI
	// 1.a. When Soft Tx is Enabled it automatically enables Tx DSM SPI
	// Figured out in event handler;
	// 1.b. When Soft Rx is Enabled it automatically enables Rx DSM SPI
	// Figured out in event handler;
	// 1.c. Enable Rx OUT/ADC In Switch
	m_TopModule->CustSet_rgrRXOUTSW(1);
	// 1.d. Disable PLLCLKOUT
	m_TopModule->CustSet_PLLCLKOUT(false);

	// Tx/RxPLL SPIs
	// 2.a. Set CP Up Offset to 30 uA
	m_TxPLLModule->CustSet_cmbOFFUP(3);
	m_RxPLLModule->CustSet_cmbOFFUP(3);

	// Rx VGA2
	// 3.a. VGA2 CM Voltage set to 12.
	// m_RxVga2Module->CustSet_cmbVCM(12);
	//m_RxVga2Module->CustSet_cmbVCM(13);
	m_RxVga2Module->setVCM(9);

	// Rx FE
	// 4.a. LNA Load Resistor set to 55
	m_RxFeModule->CustSet_cmbRDLINT_LNA_RXFE(55);

	// ADC /DAC
	// 5.a. ADC Common Mode Adj. set to 960mV
	m_ADDCModule->CustSet_cmbCoomonModeAdj(1);
	m_ADDCModule->setRefGainAdj(1);

	// Tx RF
	// Set "LO Buffer Bias Current" to 6
	m_TxRfModule->CustSet_cmbICT_TXLOBUF(4);
};

/**
	Enables or disables automatic configuration sending to chip.
*/
void Main_Module::setAutoDownload(bool state)
{
	autoDownload = state;

	if (autoDownload)
	{
		//slLogMesg(11);
		sbMain[1] = " Automatic Download Mode";
	}
	else
	{
		//slLogMesg(12);
		sbMain[1] = " Manual Download Mode";
	};
}

/**
	@return auto download state.
*/
bool Main_Module::getAutoDownload()
{
	return autoDownload;
}

/**
	Reads all configuration settings from the chip and compares it to configurations currently
	set in each control module.
*/
void Main_Module::CompareChipToGUI()
{
	ofstream outf;

	// Read Data from chip
	m_serPort->SPI_Read(m_TopModule->GetPrData());
	m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
	m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
	m_serPort->SPI_Read(m_TxRfModule->GetPrData());
	m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
	m_serPort->SPI_Read(m_RxFeModule->GetPrData());
	m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
	m_serPort->SPI_Read(m_RxPLLModule->GetPrData());

	// Write read data to the text file
	outf.open("ChipVsGui.txt", ios::out);
	m_TopModule->ChipVsGui(outf, "Top Modules:", false);
	m_RxLpfModule->ChipVsGui(outf, "RxLPF Modules:", false);
	m_TxLpfModule->ChipVsGui(outf, "TxLPF Modules:", false);
	m_TxRfModule->ChipVsGui(outf, "TxRF Modules:", false);
	m_RxVga2Module->ChipVsGui(outf, "RxVGA2 Modules:", false);
	m_RxFeModule->ChipVsGui(outf, "RxFE Modules:", false);
	m_TxPLLModule->ChipVsGui(outf, "TxPLL Modules:", false);
	m_RxPLLModule->ChipVsGui(outf, "RxPLL Modules:", false);
	outf.close();
}

/**
	Reads configuration from the chip, then writes current GUI settings
	and current chip settings into file.
	@param file output file
*/
void Main_Module::ReadConfiguration(string file)
{
	ofstream outf;
	outf.open(file.c_str(), ios::out);
	if (outf.is_open())
	{
		m_serPort->SPI_Read(m_TopModule->GetPrData());
		m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
		m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
		m_serPort->SPI_Read(m_TxRfModule->GetPrData());
		m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
		m_serPort->SPI_Read(m_RxFeModule->GetPrData());
		m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
		m_serPort->SPI_Read(m_RxPLLModule->GetPrData());

		// Lets write read data to the text file

		m_TopModule->ChipVsGui(outf, "Top Modules:", true);
		m_RxLpfModule->ChipVsGui(outf, "RxLPF Modules:", true);
		m_TxLpfModule->ChipVsGui(outf, "TxLPF Modules:", true);
		m_TxRfModule->ChipVsGui(outf, "TxRF Modules:", true);
		m_RxVga2Module->ChipVsGui(outf, "RxVGA2 Modules:", true);
		m_RxFeModule->ChipVsGui(outf, "RxFE Modules:", true);
		m_TxPLLModule->ChipVsGui(outf, "TxPLL Modules:", true);
		m_RxPLLModule->ChipVsGui(outf, "RxPLL Modules:", true);
	}
	outf.close();
}

/**
	Logs predefined message based on given parameter.
	@param LParam message code.
*/
void Main_Module::CMLog(int LParam)
{
	slLogMesg(LParam);
};

/**
	Reads data from the chip and updates values shown in interface.
	@param addr address of module which to update.
	@param WParam when updating Top module, 1-updates DC calibration, 2-updates RCCAL data.
*/
void Main_Module::CMRead(int WParam, int addr)
{
	cTempChar = addr;
	switch (addr)
	{
	case TopAddr:
		m_serPort->SPI_Read(m_TopModule->GetPrData());
		if (WParam == 1)
		{
			//m_TopModule->UpdateFormData();
			UpdateInterface(UPDATE_INTERFACE_DATA, &cTempChar);
		}
		else if (WParam == 2)
		{
			//m_TopModule->UpdateRCCALData();
			UpdateInterface(UPDATE_INTERFACE_DATA, &cTempChar);
		}
		break;

	case TxLpfAddr:
		m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
		if (WParam)
		{
			//m_TxLpfModule->UpdateFormData();
			UpdateInterface(UPDATE_INTERFACE_DATA, &cTempChar);
		}
		break;

	case RxLpfAddr:
		m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
		if (WParam)
		{
			//m_RxLpfModule->UpdateFormData();
			UpdateInterface(UPDATE_INTERFACE_DATA, &cTempChar);
		}
		break;

	case RxVGA2Addr:
		m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
		if (WParam)
		{
			m_RxVga2Module->UpdateFormData();
			UpdateInterface(UPDATE_INTERFACE_DATA, &cTempChar);
		}
		break;

	case RxPllAddr:
		m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
		break;

	case TxPllAddr:
		m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
		break;
	};
}


/**
	Sends changed configuration data to chip.
	@param Addr Address of module to which send data.
*/
void Main_Module::CMAutoDownload(char Addr)
{
	if (!autoDownload)
		return;

	switch (Addr)
	{
	case TopAddr:
		autoDownload = false;
		m_serPort->SPI_Write(m_TopModule->GetPrData());
		autoDownload = true;
		break;

	case TxLpfAddr:
		autoDownload = false;
		m_serPort->SPI_Write(m_TxLpfModule->GetPrData());
		autoDownload = true;
		break;

	case RxLpfAddr:
		autoDownload = false;
		m_serPort->SPI_Write(m_RxLpfModule->GetPrData());
		autoDownload = true;
		break;

	case TxRFAddr:
		autoDownload = false;
		m_serPort->SPI_Write(m_TxRfModule->GetPrData());
		autoDownload = true;
		break;

	case RxVGA2Addr:
		autoDownload = false;
		m_serPort->SPI_Write(m_RxVga2Module->GetPrData());
		autoDownload = true;
		break;

	case RxFEAddr:
		autoDownload = false;
		m_serPort->SPI_Write(m_RxFeModule->GetPrData());
		autoDownload = true;
		break;

	case TxPllAddr:
		autoDownload = false;
		m_serPort->SPI_Write(m_TxPLLModule->GetPrData());
		autoDownload = true;
		break;

	case RxPllAddr:
		autoDownload = false;
		m_serPort->SPI_Write(m_RxPLLModule->GetPrData());
		autoDownload = true;
		break;

	case ADFAddr:
		autoDownload = false;
		m_serPort->SPI_Wr_ADF(m_ADFModule->GetPrData());
		autoDownload = true;
		break;
	};
}

/**
	Writes predefined message to the message log based on received number.
	@param num Message code.
*/
void Main_Module::slLogMesg(int num)
{
	string message;

	switch (num)
	{
	case PROJECT_FILE_OPENED:
		message = "Project file opened: ";
		message = message + m_sFileName;
		break;

	case PROJECT_FILE_CREATED:
		message = "Project file created: ";
		message = message + m_sFileName;
		break;

	case PROJECT_FILE_SAVED_AS:
		message = "Project file saved as: ";
		message = message + m_sFileName;
		break;

	case PROJECT_FILE_SAVED:
		message = "Project file saved: ";
		message = message + m_sFileName;
		break;

	case DEFAULT_CONFIG_LOADED:
		message = "Default configuration loaded to the GUI.";
		break;

	case CONFIGURATION_SENT_TO_HARDWARE:
		message = "Configuration downloaded to the hardware.";
		break;

	case PARALLEL_PORT_INITIALIZED:
		message = "Parallel port initialized successfully.";
		break;
	/*
	case 8:
		// message =	"Reset signal sent to the Chip.";
		break;
	*/
	case RESET_SIGNAL_ACTIVE:
		message = "Reset signal is ACTIVE.";
		break;

	case RESET_SIGNAL_INACTIVE:
		message = "Reset signal is INACTIVE.";
		break;

	case AUTOMATIC_DOWNLOAD_MODE:
		message = "Automatic Download Mode ";
		break;

	case MANUAL_DOWNLOAD_MODE:
		message = "Manual Download Mode ";
		break;

	case SERIAL_PORT_INITIALIZED:
		message = "Serial port initialized successfully.";
		break;

	case SERIAL_PORT_NOT_ACCESSABLE:
		message = "You are not able to control the board since serial port is not\n";
		message += "accessable. Check if USB to Serial board is connected to the PC USB port.\n";
		message += "To be able to download configuration, fix the problem and run software again.";
		break;
	};
	slLogMesg(message.c_str());
	//UpdateInterface(SHOW_LOG_MESSAGE, message.c_str());
};

/**
	Adds given message to message log.
*/
void Main_Module::slLogMesg(const char *msg)
{
	messagesLog.AddLine(msg);
	//UpdateInterface(SHOW_LOG_MESSAGE, msg);
}
/**
	Sets name of the current project.
*/
void Main_Module::setCurrentFileName(string fileName)
{
	this->m_sFileName = fileName;

#ifdef ALTERA_EDITION
	string shownName = "6002Dr2 Altera Edition. ";
#else
	string shownName = "6002Dr2 Test. ";
#endif

	if (fileName.length() == 0)
		shownName = shownName + "untitled.prj";
	else
		shownName = shownName + fileName;

	shownName = shownName + " - Project File";

	this->Caption = shownName;
}

/**
	Saves configuration to ini file.
*/
void Main_Module::FileSaveAs(string filename)
{
	ini_t *ini;
	ini = new ini_t(filename);

	m_UARFCNDef.SaveConf(ini);
	m_TopModule->SaveConf(ini);
	m_TxLpfModule->SaveConf(ini);
	m_RxLpfModule->SaveConf(ini);
	m_TxRfModule->SaveConf(ini);
	m_RxVga2Module->SaveConf(ini);
	m_RxFeModule->SaveConf(ini);
	m_TxPLLModule->SaveConf(ini);
	m_RxPLLModule->SaveConf(ini);
	m_ADDCModule->SaveConf(ini);
	ini->Save();

	slLogMesg(PROJECT_FILE_SAVED_AS);
	delete ini;
}

// ---------------------------------------------------------------------------
void Main_Module::CMADDC2LPF(int addr)
{
	m_RxLpfModule->JoinADDC(addr);
};

// ----------------------------------------------------------------------------
void Main_Module::CMResetAct()
{
	m_serPort->SPI_RstAct();
	slLogMesg(RESET_SIGNAL_ACTIVE);
};

// ----------------------------------------------------------------------------
void Main_Module::CMResetInAct()
{
	m_serPort->SPI_RstInact();
	// m_TopModule->SetDefaults();
	// m_TxLpfModule->SetDefaults();
	// m_RxLpfModule->SetDefaults();
	// m_TxRfModule->SetDefaults();
	// m_RxVga2Module->SetDefaults();
	// m_RxFeModule->SetDefaults();
	// m_TxPLLModule->SetDefaults();
	// m_RxPLLModule->SetDefaults();

	m_TopModule->SetCalDefaults();
	m_TxLpfModule->SetCalDefaults();
	m_RxLpfModule->SetCalDefaults();
	m_RxVga2Module->SetCalDefaults();

	slLogMesg(RESET_SIGNAL_INACTIVE);
};

/**
	Sets reference clock in TxPLL and RxPLL
	@param dRefClk_Hz Reference clock in Hz
*/
void Main_Module::setRefClk(double dRefClk_Hz)
{
	m_RefClk = dRefClk_Hz;
	m_TxPLLModule->SetRefClk(dRefClk_Hz);
	m_RxPLLModule->SetRefClk(dRefClk_Hz);
}


/**
	@brief Returns reference clock
	@return Reference clock in Hz.
*/
double Main_Module::getRefClk()
{
	return m_RefClk;
}

/**
	Saves given reference clock to Windows registers.
	@param Freq Reference clock frequency.
*/
void Main_Module::SaveRefClkToReg(double Freq)
{
#ifdef WIN32
	DWORD lRv;
	HKEY hKey;

	//Check if the registry exists
	lRv = RegOpenKeyEx( HKEY_CURRENT_USER, RegistryString, 0, KEY_WRITE, &hKey);

	if (lRv != ERROR_SUCCESS)
	{
		DWORD dwDisposition;
		// Create a key if it did not exist
		lRv = RegCreateKeyEx(HKEY_CURRENT_USER, RegistryString,
			0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,
			&dwDisposition);
	}
		float dwValue = m_RefClk;

		RegSetValueEx(hKey, "RefClk", 0, REG_BINARY, reinterpret_cast<BYTE *>(&dwValue), sizeof(dwValue));
		RegCloseKey(hKey);
#endif
};

/**
	Reads reference clock from Windows registers.
	@return Reference clock frequency in Hz.
*/
double Main_Module::ReadRefClkFromReg(void)
{
    #ifdef WIN32
	double Freq = 30720000;
	HKEY hKey;

	// Check if the registry exists
	DWORD lRv = RegOpenKeyEx(HKEY_CURRENT_USER, RegistryString, 0, KEY_READ, &hKey);

	char temp[100];

	memset(temp, 0, 100);

	if (lRv == ERROR_SUCCESS)
	{
		DWORD BufferSize = sizeof(DWORD);
		DWORD dwRet;
		DWORD cbData;
		float cbVal = 0;

		dwRet = RegQueryValueEx(hKey, "RefClk", NULL, NULL,	(LPBYTE) &cbVal, &cbData);

		Freq = cbVal;

		if (dwRet == ERROR_SUCCESS)
			return cbVal;
	}
	return Freq;
#else
    return 0;
#endif

};

/**
	Work around, to not power down TxRF, while after that LO DACs doesn't recover.
*/
void Main_Module::CMSoftTxPD(int LParam)
{
	// m_frmCustomer->cmbLNASEL_Cust.itemIndex = Message.LParam;
	// Cust_setLNASEL(Application);

	// EnableAllSPIClocks();

	if (LParam)
	{
		m_TxLpfModule->LpfPowerOn(true);
		m_TxPLLModule->PLLPowerOn(true);
	}
	else
	{
		m_TxLpfModule->LpfPowerOn(false);
		m_TxPLLModule->PLLPowerOn(false);
	};
	// RestoreAllSPIClocks();
};

/**

*/
void Main_Module::EnableSPIClockByMask(int Mask)
{
	// Enable all SPI clocks in TopSPI
	m_TopModule->EnableSPIClocksByMask(Mask);
	m_serPort->SPI_Write(m_TopModule->GetPrData());
	milSleep(5);
};

// ---------------------------------------------------------------------------
// Functions for customer mode interface
// ---------------------------------------------------------------------------
/**
	Selects current LNA chain
	@param index 0 - disabled, 1,2,3 - active LNA index
*/
void Main_Module::Cust_setLNASEL(int index)
{
	//EnableAllSPIClocks();
	cmbLNASEL_Cust.itemIndex = index;
	SetLnaChain(cmbLNASEL_Cust.itemIndex);
	//RestoreAllSPIClocks();
}

/**
	Sets current LNA chain.
	@param iChain LNA chain index.
*/
void Main_Module::SetLnaChain(int iChain)
{
	switch (iChain)
	{
	case 0:
		m_RxFeModule->CustSet_BoardLNA(0);
		m_RxFeModule->CustSet_ActiveLNA(0);
		m_RxPLLModule->CustSet_ActiveLOBuff(0);
		break;

	case 1:
		m_RxFeModule->CustSet_BoardLNA(1);
		m_RxFeModule->CustSet_ActiveLNA(1);
		m_RxPLLModule->CustSet_ActiveLOBuff(1);
		break;

	case 2:
		m_RxFeModule->CustSet_BoardLNA(2);
		m_RxFeModule->CustSet_ActiveLNA(2);
		m_RxPLLModule->CustSet_ActiveLOBuff(2);
		break;

	case 3:
		m_RxFeModule->CustSet_BoardLNA(3);
		m_RxFeModule->CustSet_ActiveLNA(3);
		m_RxPLLModule->CustSet_ActiveLOBuff(3);
		break;
	};
};

/**
	Performs transmitter calibration.
*/
void Main_Module::Cust_CalibrateTx()
{
	int iTryDone, iTryComplete;
	char cTmp;

	// EnableAllSPIClocks();
	// Enable TxLPF DC CAL Clock
	EnableSPIClockByMask(0x02);

	// Set I Channel DC Calibration chain
	m_TxLpfModule->setDCCalAddr(0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_TxLpfModule->StartCalibration(0);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_TxLpfModule->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("I Done OK");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_TxLpfModule->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("I Lock OK");
			break;
		};
	}
	while (iTryComplete);

	// Q Channel
	m_TxLpfModule->setDCCalAddr(1);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_TxLpfModule->StartCalibration(1);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_TxLpfModule->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("Q Done OK");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_TxLpfModule->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("Q Lock OK");
			break;
		};
	}
	while (iTryComplete);

	RestoreAllSPIClocks();

	slLogMesg("Tx Calibration Done");
}

/**
	Performs receiver calibration.
*/
void Main_Module::Cust_CalibrateRx()
{
	int iTryDone, iTryComplete;
	char cTmp;
	int iRxVGA2Gain_ind;

	// EnableAllSPIClocks();

	// =================== Remember RxVGA2 gain =====================================
	iRxVGA2Gain_ind = m_RxVga2Module->getRXVGA2Gain();

	// =================== Set RxVGA2 gain to 30dB ==================================
	m_RxVga2Module->setRXVGA2Gain(10);

	// =================== Rx LPF DC Calibration Begin ==============================

	// Enable RxLPF DC CAL Clock
	EnableSPIClockByMask(0x08);

	// Set I Channel DC Calibration chain
	m_RxLpfModule->setDCCalAddr(0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_RxLpfModule->StartCalibration(0);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_RxLpfModule->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("RxLPF I Done OK");
				break;
			};
			// Application->ProcessMessages();
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_RxLpfModule->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("RxLPF I Lock OK");
			break;
		};
		// Application->ProcessMessages();
	}
	while (iTryComplete);

	// Q Channel
	m_RxLpfModule->setDCCalAddr(1);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_RxLpfModule->StartCalibration(1);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_RxLpfModule->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("RxLPF Q Done OK");
				break;
			};
			// Application->ProcessMessages();
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_RxLpfModule->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("RxLPF Q Lock OK");
			break;
		};
		// Application->ProcessMessages();
	}
	while (iTryComplete);

	// Restore all SPI Clokcs
	RestoreAllSPIClocks();
	// =================== Rx LPF DC Calibration End ================================

	// =================== Rx VGA2 DC Calibration Begin =============================

	// Enable RxVGA2 DC CAL Clock
	EnableSPIClockByMask(0x10);

	// REF Channel
	m_RxVga2Module->SetCalAddr(0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_RxVga2Module->StartCalibration(0);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_RxVga2Module->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("RxVGA2 REF Done OK");
				break;
			};
			// Application->ProcessMessages();
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_RxVga2Module->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("RxVGA2 REF Lock OK");
			break;
		};
		// Application->ProcessMessages();
	}
	while (iTryComplete);

	// dc2a_vga2_i Channel
	m_RxVga2Module->SetCalAddr(1);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_RxVga2Module->StartCalibration(1);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_RxVga2Module->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("RxVGA2 DC2A_I Done OK");
				break;
			};
			// Application->ProcessMessages();
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_RxVga2Module->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("RxVGA2 DC2A_I Lock OK");
			break;
		};
		// Application->ProcessMessages();
	}
	while (iTryComplete);

	// dc2a_vga2_q Channel
	m_RxVga2Module->SetCalAddr(2);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_RxVga2Module->StartCalibration(2);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_RxVga2Module->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("RxVGA2 DC2A_Q Done OK");
				break;
			};
			// Application->ProcessMessages();
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_RxVga2Module->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("RxVGA2 DC2A_Q Lock OK");
			break;
		};
		// Application->ProcessMessages();
	}
	while (iTryComplete);

	// dc2b_vga2_i Channel
	m_RxVga2Module->SetCalAddr(3);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_RxVga2Module->StartCalibration(3);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_RxVga2Module->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("RxVGA2 DC2B_I Done OK");
				break;
			};
			// Application->ProcessMessages();
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_RxVga2Module->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("RxVGA2 DC2B_I Lock OK");
			break;
		};
		// Application->ProcessMessages();
	}
	while (iTryComplete);

	// dc2b_vga2_q Channel
	m_RxVga2Module->SetCalAddr(4);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_RxVga2Module->StartCalibration(4);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = m_RxVga2Module->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("RxVGA2 DC2B_Q Done OK");
				break;
			};
			// Application->ProcessMessages();
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_RxVga2Module->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("RxVGA2 DC2B_Q Lock OK");
			break;
		};

		// Application->ProcessMessages();
	}
	while (iTryComplete);

	// Restore all SPI Clokcs
	RestoreAllSPIClocks();

	// =================== Restore RxVGA2 gain =====================================
	m_RxVga2Module->setRXVGA2Gain(iRxVGA2Gain_ind);

	// =================== Rx VGA2 DC Calibration End ===============================

	// RestoreAllSPIClocks();

	slLogMesg("RxLPF and RxVGA2 Calibration Done");
}

/**

*/
void Main_Module::Cust_setRxBypass(int index)
{
	cmbRxBypass.itemIndex = index;
	SetBypassLoopback();
}

/**

*/
void Main_Module::Cust_setLoopback(int index)
{
	cmbLoopback.itemIndex = index;
	SetBypassLoopback();
}

/**

*/
void Main_Module::Cust_setTxBypass(int index)
{
	// EnableAllSPIClocks();
	switch (index)
	{
		// Turn off all Bypass Modes
	case 0:
		m_TxLpfModule->CustSet_BypassLpfOFF();
		break;

		// Bypass RxLPF:
		// 1. Power Down TxLPF;
		// 2. Select Bypass Mode.
	case 1:
		// Turn off other bypass

		// Turn on required bypass mode
		m_TxLpfModule->CustSet_BypassLpfON();
		break;
	};
	// RestoreAllSPIClocks();
}

/**

*/
void Main_Module::SetBypassLoopback()
{
	int iBB = cmbRxBypass.itemIndex;
	int iLB = cmbLoopback.itemIndex;

	// Turn Off all bypass modes
	// EnableAllSPIClocks();
	m_TopModule->CustSet_Tia2OutOFF();
	m_RxLpfModule->CustSet_BypassLpfOFF();
	m_RxVga2Module->RxVGA2PowerOn(true);
	// RestoreAllSPIClocks();

	// Turn Off all loopback modes
	// EnableAllSPIClocks();
	cmbLNASEL_Cust.itemIndex = 1;
	SetLnaChain(cmbLNASEL_Cust.itemIndex);
	m_TopModule->CustSet_SetRFLB(0);
	m_TopModule->CustSet_SetBBLB(0);
	m_RxFeModule->LNAPowerOn(true);
	m_RxFeModule->PowerOn(true);
	m_RxLpfModule->LpfPowerOn(true);
	m_RxVga2Module->RxVGA2PowerOn(true);
	// RestoreAllSPIClocks();

	// RxLPF Bypass, LBEN_LPFIN ON
	if ((iLB == 0x01) && (iBB == 0x01))
	{
		// EnableAllSPIClocks();
		m_RxLpfModule->CustSet_BypassLpfON();
		// Turns Bypas RxLPF switch ON, powers down LPF
		m_RxFeModule->PowerOn(false); // Powers down TIA, RxMIX, RxLNA
		m_TopModule->CustSet_SetBBLB(1);
		// RestoreAllSPIClocks();
		return;
	};

	// RxVGA2 and RxLPF Bypass, LBEN_LPFIN ON
	if ((iLB == 0x01) && (iBB == 0x02))
	{
		// EnableAllSPIClocks();
		m_RxFeModule->PowerOn(false); // Powers down TIA, RxMIX, RxLNA
		m_RxVga2Module->RxVGA2PowerOn(false); // Powers down RxVGA2
		m_RxLpfModule->LpfPowerOn(false); // Powers down RxLPF
		m_TopModule->CustSet_Tia2OutON();
		m_TopModule->CustSet_SetBBLB(1);
		// RestoreAllSPIClocks();
		return;
	};

	// Illegal combination
	if (((iLB == 0x02) || (iLB == 0x03)) && ((iBB == 0x01) || (iBB == 0x02)))
	{
		ShowMessage("Illegal Baseband Bypass and Baseband Loopback mode.\n");
		return;
	};

	//
	switch (iBB)
	{
		// Bypass RxLPF:
		// 1. Power Down RxLPF;
		// 2. Select Bypass Mode.
	case 1:
		// Turn on required bypass mode
		// EnableAllSPIClocks();
		m_RxLpfModule->CustSet_BypassLpfON();
		// RestoreAllSPIClocks();
		break;

		// Bypass RxLPF, RxVGA2:
		// 1. Power Down RxLPF;
		// 2. Power Down RxVGA2;
		// 3. Select RxTIA Connected to Output Pins
	case 2:
		// Turn on required bypass mode
		// EnableAllSPIClocks();
		m_RxVga2Module->RxVGA2PowerOn(false);
		m_RxLpfModule->LpfPowerOn(false);
		m_TopModule->CustSet_Tia2OutON();
		// RestoreAllSPIClocks();
		break;
	};

	//
	switch (iLB)
	{
		// To RxLPF input
	case 1:
		// Turn off other bypass

		// Turn on required bypass mode
		// EnableAllSPIClocks();
		m_RxFeModule->PowerOn(false);
		m_RxLpfModule->LpfPowerOn(true);
		m_RxVga2Module->RxVGA2PowerOn(true);
		m_TopModule->CustSet_SetBBLB(1);
		// RestoreAllSPIClocks();
		break;

		// To RxVGA2 input
	case 2:
		// Turn off other bypass

		// Turn on required bypass mode
		// EnableAllSPIClocks();
		m_RxFeModule->PowerOn(false);
		m_RxLpfModule->LpfPowerOn(false);
		m_RxVga2Module->RxVGA2PowerOn(true);
		m_TopModule->CustSet_SetBBLB(2);
		// RestoreAllSPIClocks();
		break;

		// To output pins
	case 3:
		// Turn off other bypass

		// Turn on required bypass mode
		// EnableAllSPIClocks();
		m_RxFeModule->PowerOn(false);
		m_RxLpfModule->LpfPowerOn(false);
		m_RxVga2Module->RxVGA2PowerOn(false);
		m_TopModule->CustSet_SetBBLB(3);
		// RestoreAllSPIClocks();
		break;

		//
	case 4:
		// Turn off other bypass

		// Turn on required bypass mode
		// EnableAllSPIClocks();
		cmbLNASEL_Cust.itemIndex = 1;
		SetLnaChain(cmbLNASEL_Cust.itemIndex);
		m_RxFeModule->LNAPowerOn(false);
		m_TopModule->CustSet_SetRFLB(1);
		// RestoreAllSPIClocks();
		break;

	case 5:
		// Turn off other bypass

		// Turn on required bypass mode
		// EnableAllSPIClocks();
		cmbLNASEL_Cust.itemIndex = 2;
		SetLnaChain(cmbLNASEL_Cust.itemIndex);
		m_RxFeModule->LNAPowerOn(false);
		m_TopModule->CustSet_SetRFLB(2);
		// RestoreAllSPIClocks();
		break;

	case 6:
		// Turn off other bypass

		// Turn on required bypass mode
		// EnableAllSPIClocks();
		cmbLNASEL_Cust.itemIndex = 3;
		SetLnaChain(cmbLNASEL_Cust.itemIndex);
		m_RxFeModule->LNAPowerOn(false);
		m_TopModule->CustSet_SetRFLB(3);
		// RestoreAllSPIClocks();
		break;
	};

};

/**
	@return Pointer to array of strings with DLTX band names.
*/
const string *Main_Module::Cust_getDLTXBands(int &count) const
{
	count = m_UARFCNDef.cmbDLTXBands.sItems.size();
	string *Strings = new string[count];
	for (int i = 0; i < count; i++)
	{
		Strings[i] = m_UARFCNDef.cmbDLTXBands.sItems[i];
	}
	return Strings;
}

/**
	@return Pointer to array of strings with ULRX band names.
*/
const string *Main_Module::Cust_getULRXBands(int &count) const
{
	count = m_UARFCNDef.cmbULRXBands.sItems.size();
	string *Strings = new string[count];
	for (int i = 0; i < count; i++)
	{
		Strings[i] = m_UARFCNDef.cmbULRXBands.sItems[i];
	}
	return Strings;
}

/**
	@return pointer to array of strings which contain available downlink channels.
*/
const string *Main_Module::Cust_getDLTXChannels(int &count) const
{
	count = m_UARFCNDef.cmbDLTXChan.sItems.size();
	string *Strings = new string[count];
	for (int i = 0; i < count; i++)
	{
		Strings[i] = m_UARFCNDef.cmbDLTXChan.sItems[i];
	}
	return Strings;
}

/**
	@return pointer to array of strings which contain available uplink channels.
*/
const string *Main_Module::Cust_getULRXChannels(int &count) const
{
	count = m_UARFCNDef.cmbULRXChan.sItems.size();
	string *Strings = new string[count];
	for (int i = 0; i < count; i++)
	{
		Strings[i] = m_UARFCNDef.cmbULRXChan.sItems[i];
	}
	return Strings;
}

/**
	Selects downlink band.
	@param index Downlink band index.
*/
void Main_Module::Cust_setDLTXBand(int index)
{
	double dFreq;
	dFreq = m_UARFCNDef.selectBand(false, index);
	if (dFreq > 0)
	{
		m_TxPLLModule->CustSet_LoadFrequency(dFreq / 1000);
		char addr = TxPllAddr;
		UpdateInterface(UPDATE_INTERFACE_DATA, &addr);
	}
}

/**
	Selects downlink channel.
	@param index Downlink channel index.
*/
void Main_Module::Cust_setDLTXChannel(int index)
{
	double dFreq;
	dFreq = m_UARFCNDef.selectChannel(false, index);
	if (dFreq > 0)
	{
		m_TxPLLModule->CustSet_LoadFrequency(dFreq / 1000);
		char addr = TxPllAddr;
		UpdateInterface(UPDATE_INTERFACE_DATA, &addr);
	}
}

/**
	Selects uplink band
	@param index Uplink band index.
*/
void Main_Module::Cust_setULRXBand(int index)
{
	double dFreq;
	dFreq = m_UARFCNDef.selectBand(true, index);
	if (dFreq > 0)
	{
		m_RxPLLModule->CustSet_LoadFrequency(dFreq / 1000);
		char addr = RxPllAddr;
		UpdateInterface(UPDATE_INTERFACE_DATA, &addr);
	}
}

/**
	Selects uplink channel
	@param index Uplink channel index.
*/
void Main_Module::Cust_setULRXChannel(int index)
{
	double dFreq;
	dFreq = m_UARFCNDef.selectChannel(true, index);
	if (dFreq > 0)
	{
		m_RxPLLModule->CustSet_LoadFrequency(dFreq / 1000);
		char addr = RxPllAddr;
		UpdateInterface(UPDATE_INTERFACE_DATA, &addr);
	}
}

/**
	Performs RxTIA calibration.
*/
void Main_Module::Cust_CalibrateRxTIA()
{
	char cTmp;
	ofstream outf;

// ============ Saved and restored values includes: ===========================
	int DCOffsetCancellationI, DCOffsetCancellationQ;
	int DCCalValI, DCCalValQ;
	int RxLPFDecode;
	int RxLPFBypass;
	bool PwrLpfMods, PwrLpf, PwrDCDac, PwrDCRef, PwrDCCmpr;
	// 1. SPI Clock Enables in TopSPI.
	// 2. DCOffsetCancellationI, DCOffsetCancellationQ in RxFESPI.
	// 3. DC Calibration values from RxLPF I and Q channels.
	// 4. "Decode Signals" Control State in RxLPF.
	// 5. LPF Bypass (Test) state.
	// 6. Power Control States.

	outf.open("RxTIAClbr.txt", ios::out);
	outf << left;
	outf << "RxTIA Calibration" << endl;
	outf << endl;
	outf << "------------------" << endl;
	outf.width(6);
	outf << "| DAC I";
	outf.width(3);
	outf << " | ";
	outf.width(7);
	outf << "COMP I";
	outf.width(1);
	outf << "|";
	outf << endl;
	outf << "--------+---------" << endl;

	EnableAllSPIClocks();
	// Read the cmbDCOFF_I_RXFE and cmbDCOFF_Q_RXFE states from RxFESPI
	DCOffsetCancellationI = m_RxFeModule->CustGet_DCOffsetCancellationI();
	DCOffsetCancellationQ = m_RxFeModule->CustGet_DCOffsetCancellationQ();
	DCCalValI = m_RxLpfModule->GetCalVal(0x00);
	DCCalValQ = m_RxLpfModule->GetCalVal(0x01);
	RxLPFDecode = m_RxLpfModule->CustGet_DecodeState();
	RxLPFBypass = m_RxLpfModule->CustGet_LPFTestState();
	PwrLpfMods = m_RxLpfModule->CustGet_PwrLpfMods();
	PwrLpf = m_RxLpfModule->CustGet_PwrLpf();
	PwrDCDac = m_RxLpfModule->CustGet_PwrDCDac();
	PwrDCRef = m_RxLpfModule->CustGet_PwrDCRef();
	PwrDCCmpr = m_RxLpfModule->CustGet_PwrDCCmpr();

	m_RxLpfModule->CustSet_EnableDCOffsetCompOnly();
	m_RxLpfModule->CustSet_BypassLPFOnlyOn();

	// Channel I
	m_RxLpfModule->setDCCalAddr(0);
	for (int i = 0; i < 128; i++)
	{
		m_RxFeModule->CustSet_DCOffsetCancellationI(i);
		cTmp = m_RxLpfModule->GetCalStatus();

		outf.width(2);
		outf << "|";
		outf.width(5);
		outf << i;
		outf.width(3);
		outf << " | ";
		outf.width(6);
		if (cTmp & 0x01)
			cTmp = '1';
		else
			cTmp = '0';
		outf << cTmp;
		outf.width(2);
		outf << " |";
		outf << endl;
	};
	outf << "------------------" << endl;

	// Channel Q
	outf << endl;
	outf << "------------------" << endl;
	outf.width(6);
	outf << "| DAC Q";
	outf.width(3);
	outf << " | ";
	outf.width(7);
	outf << "COMP Q";
	outf.width(1);
	outf << "|";
	outf << endl;
	outf << "--------+---------" << endl;
	m_RxLpfModule->setDCCalAddr(1);
	for (int i = 0; i < 128; i++)
	{
		m_RxFeModule->CustSet_DCOffsetCancellationQ(i);
		cTmp = m_RxLpfModule->GetCalStatus();

		outf.width(2);
		outf << "|";
		outf.width(5);
		outf << i;
		outf.width(3);
		outf << " | ";
		outf.width(6);
		if (cTmp & 0x01)
			cTmp = '1';
		else
			cTmp = '0';
		outf << cTmp;
		outf.width(2);
		outf << " |";
		outf << endl;
	};
	outf << "------------------" << endl;

	outf.close();

	m_RxLpfModule->CustSet_RestoreDCOffsetCompOnly();
	m_RxLpfModule->CustSet_BypassLPFOnlyOff();
	// Restore the cmbDCOFF_I_RXFE and cmbDCOFF_Q_RXFE states from RxFESPI
	m_RxFeModule->CustSet_DCOffsetCancellationI(DCOffsetCancellationI);
	m_RxFeModule->CustSet_DCOffsetCancellationQ(DCOffsetCancellationQ);
	m_RxLpfModule->SetCalVal(0x00, DCCalValI);
	m_RxLpfModule->SetCalVal(0x01, DCCalValQ);
	m_RxLpfModule->CustSet_DecodeState(RxLPFDecode);
	m_RxLpfModule->CustSet_LPFTestState(RxLPFBypass);
	m_RxLpfModule->CustSet_PwrLpfMods(PwrLpfMods);
	m_RxLpfModule->CustSet_PwrLpf(PwrLpf);
	m_RxLpfModule->CustSet_PwrDCDac(PwrDCDac);
	m_RxLpfModule->CustSet_PwrDCRef(PwrDCRef);
	m_RxLpfModule->CustSet_PwrDCCmpr(PwrDCCmpr);

	RestoreAllSPIClocks();

	slLogMesg("RxTIA Calibration Done");
}

/**
	Calibration of LPF CAL CORE.
*/
void Main_Module::CalLPFCore()
{
	int iDCCalValue, iLPFCALValue;
	int iTryDone, iTryComplete;
	int iLPFTuningClockInd;
	char cTmp;
	bool bPD_CLKLPFCAL; // remember Divide TxPLL freq by 8 setting
	bool bSoftTx;

	// =========== I. TOP SPI DC Calibration for CAL Core LPF =====================
	// Steps:
	// 1. Turn off module power supplies in TopSPI;
	// 2. Perform calibration in chain address 0;
	// 3. Read DC Calibration value from DC CAlibration chain number 0 into iDCCalValue variable;
	// 4. Turn on module power supplies in TopSPI;

	// =========== Step 1 =========================================================
	// m_TopModule->CustSet_TopPowerON(false);

	// =========== Step 2 =========================================================
	// Set 0 address DC Calibration chain
	m_TopModule->SetCalAddr(0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		m_TopModule->StartCalibration(0);

		// Whait for calibration complete
		do
		{
			iTryDone--;
			cTmp = m_TopModule->GetCalStatus();
			if (((cTmp >> 1) & 0x01) ^ 0x01)
			{
				slLogMesg("DC Channel Done OK");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = m_TopModule->GetCalStatus();
		if ((((cTmp >> 2) & 0x07) == 0x05) || (((cTmp >> 2) & 0x07) == 0x02))
		{
			slLogMesg("DC Channel Lock OK");
			break;
		};
	}
	while (iTryComplete);

	// =========== Step 3 =========================================================
	// iDCCalValue = m_TopModule->GetCalVal(0);

	// =========== Step 4 =========================================================
	// m_TopModule->CustSet_TopPowerON(true);

	// ========== II. LPF CAL Core Calibration in TOP SPI =========================
	// Steps:
	// 1. Set 2.5MHz in "LPF Bandwidth:" control in TopSPI;
	// 2. Enable RxPLL SPI Clock in TopSPI;
	// 2.a) Get "LPF Tuning Clock" index;
	// 2.b) If RefCLK != 40MHz, Set "LPF Tuning Clock" index to 0; Enable Soft TX;
	// 2.c) If RefCLK != 40MHz, Set TxPLL for 320MHz;
	// 2.d) If RefCLK != 40MHz, Divide TxPLL freq by 8;
	// 3. Set "Enable LPFCAL" (check) in TopSPI;
	// 4. Toggle "Reset LPFCAL" checkbox (check and uncheck) in TopSPI;
	// 5. Read LPFCAL value from TopSPI into variable .......;
	// 6. Unset "Enable LPFCAL" (uncheck) in TopSPI;
	// 7. Restore Clock Enables in TopSPI
	// 7.a) If RefCLK != 40MHz, Restore Divide TxPLL freq by 8 settings;
	// 7.b) If RefCLK != 40MHz, Restore "LPF Tuning Clock" index;
	// 7.c) If RefCLK != 40MHz, Restore TxPLL settings; Restore SoftTX Enable;

	// =========== Step 1 =========================================================
	m_TopModule->CustSet_LPFBandwidth(9);

	// =========== Step 2 =========================================================
	 m_TopModule->EnableAllSPIClocks();

	// =========== Step 2.a) ======================================================
	iLPFTuningClockInd = m_TopModule->GetLPFTuningClockInd();

	// =========== Step 2.b) ======================================================
	if (m_TxPLLModule->GetRefClk() != 40000000)
	{
		m_TopModule->SetLPFTuningClockInd(0);
		// Enable SoftTX
		bSoftTx = m_TopModule->CustSet_SofTxOnOff(true);
		m_serPort->SPI_Write(m_TopModule->GetPrData());
	};

	// =========== Step 2.c) ======================================================
	if (m_TxPLLModule->GetRefClk() != 40000000)
		m_TxPLLModule->SetPLLTo320MHz();

	// =========== Step 2.d) ======================================================
	if (m_TxPLLModule->GetRefClk() != 40000000)
		bPD_CLKLPFCAL = m_TopModule->CustGet_PD_CLKLPFCAL();
	if (m_TxPLLModule->GetRefClk() != 40000000)
		m_TopModule->CustSet_PD_CLKLPFCAL(false);

	// =========== Step 3 =========================================================
	m_TopModule->CustSet_EnableLPFCAL(true);

	// =========== Step 4 =========================================================
	m_TopModule->CustSet_ResetLPFCAL(true);
	m_TopModule->CustSet_ResetLPFCAL(false);

	// =========== Step 5 =========================================================
	m_TopModule->CustGet_LPFCALVal(iDCCalValue, iLPFCALValue);

	// =========== Step 6 =========================================================
	m_TopModule->CustSet_EnableLPFCAL(false);

	// =========== Step 7 =========================================================
	m_TopModule->RestoreAllSPIClocks();

	// =========== Step 7.a) ======================================================
	if (m_TxPLLModule->GetRefClk() != 40000000)
		m_TopModule->CustSet_PD_CLKLPFCAL(bPD_CLKLPFCAL);

	// =========== Step 7.b) ======================================================
	if (m_TxPLLModule->GetRefClk() != 40000000)
		m_TopModule->SetLPFTuningClockInd(iLPFTuningClockInd);

	// =========== Step 7.c) ======================================================
	if (m_TxPLLModule->GetRefClk() != 40000000)
	{
		m_TxPLLModule->RestoreAfterSetPLLTo320MHz();
		// Restore SoftTX Enable
		m_TopModule->CustSet_SofTxOnOff(bSoftTx);
		m_serPort->SPI_Write(m_TopModule->GetPrData());
	};

	// ========= III. Write Calibration Values to Tx and Rx LPFs ==================
	// Steps:
	// 1. Enable All SPI Clocks in TopSPI;
	// 2. Write "DC Offset Resistor" value to the RxLPF;
	// 3. Write "From TRX_LPF_CAL" value to the RxLPF;
	// 4. Write "DC Offset Resistor" value to the TxLPF;
	// 5. Write "From TRX_LPF_CAL" value to the TxLPF;
	// 6. Restore All SPI Clocks in TopSPI.

	// =========== Step 1 =========================================================
	m_TopModule->EnableAllSPIClocks();

	// =========== Step 2 =========================================================
	m_RxLpfModule->CustSet_LPFDCVAL(iDCCalValue);

	// =========== Step 3 =========================================================
	m_RxLpfModule->CustSet_LPFCALVAL(iLPFCALValue);

	// =========== Step 4 =========================================================
	m_TxLpfModule->CustSet_LPFDCVAL(iDCCalValue);

	// =========== Step 5 =========================================================
	m_TxLpfModule->CustSet_LPFCALVAL(iLPFCALValue);

	// =========== Step 6 =========================================================
	m_TopModule->RestoreAllSPIClocks();

	slLogMesg("LPF Core Calibration Done");
}

/**
	Saves configuration to file under RVF format.
	@param link Filename or full path to file.
	@param dec = 1 if format is decimal, dec = 0 if format is hexadecimal;
*/
void Main_Module::SaveUnderRVF_Format(string link, int dec)
{
	ofstream outf;
	/*
	 //*** Comented to create file from GUI data instead of chip registers data

	 //Lets Read Data from chip
	 m_serPort->SPI_Read(m_TopModule->GetPrData());
	 m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
	 m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
	 m_serPort->SPI_Read(m_TxRfModule->GetPrData());
	 m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
	 m_serPort->SPI_Read(m_RxFeModule->GetPrData());
	 m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
	 m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
	 */
	// Lets write read data to the text file
	outf.open(link.c_str(), ios::out);
	if (dec == 1)
	{
		outf.flags(ios::left | ios::dec);
	}
	else
	{
		outf.flags(ios::left | ios::hex | ios::uppercase | ios::showbase);
	};
	m_TopModule->MakeRVFFile(outf);
	m_TxPLLModule->MakeRVFFile(outf);
	m_RxPLLModule->MakeRVFFile(outf);
	m_TxLpfModule->MakeRVFFile(outf);
	m_TxRfModule->MakeRVFFile(outf);
	m_RxLpfModule->MakeRVFFile(outf);
	m_RxVga2Module->MakeRVFFile(outf);
	m_RxFeModule->MakeRVFFile(outf);
	outf.close();
};

/**
	Saves chip configuration to file using FRIF format.
	@param link Filename or full path to file.
	@param rfifParam
*/
void Main_Module::SaveUnderRFIF_Format(string link, int rfifParam)
{
	ofstream outf;

	string ValStr;
	/*
	 //*** Comented to create file from GUI data instead of chip registers data

	 //Lets Read Data from chip
	 m_serPort->SPI_Read(m_TopModule->GetPrData());
	 m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
	 m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
	 m_serPort->SPI_Read(m_TxRfModule->GetPrData());
	 m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
	 m_serPort->SPI_Read(m_RxFeModule->GetPrData());
	 m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
	 m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
	 */
    m_RFIFParam = rfifParam;
	//ValStr = ",";
	char ctmp[10];
	m_RFIFParam = rfifParam;
	sprintf(ctmp, "%i", rfifParam);
	ValStr.append(ctmp);
	// Lets write read data to the text file
	outf.open(link.c_str(), ios::out);
	m_TopModule->MakeRFIFFile(outf, ValStr.c_str());
	m_TxPLLModule->MakeRFIFFile(outf, ValStr.c_str());
	m_RxPLLModule->MakeRFIFFile(outf, ValStr.c_str());
	m_TxLpfModule->MakeRFIFFile(outf, ValStr.c_str());
	m_TxRfModule->MakeRFIFFile(outf, ValStr.c_str());
	m_RxLpfModule->MakeRFIFFile(outf, ValStr.c_str());
	m_RxVga2Module->MakeRFIFFile(outf, ValStr.c_str());
	m_RxFeModule->MakeRFIFFile(outf, ValStr.c_str());
	outf.close();

}

/**
	Saves all registers to file.
	@param link Filename or full path to file.
*/
void Main_Module::SaveRegisters(string link)
{
	ofstream outf;
	/*
	 //*** Comented to create file from GUI data instead of chip registers data

	 //Lets Read Data from chip
	 m_serPort->SPI_Read(m_TopModule->GetPrData());
	 m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
	 m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
	 m_serPort->SPI_Read(m_TxRfModule->GetPrData());
	 m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
	 m_serPort->SPI_Read(m_RxFeModule->GetPrData());
	 m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
	 m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
	 */

	// Lets write read data to the text file
	outf.open(link.c_str(), ios::out);
	m_TopModule->MakeRegisterFile(outf);
	m_TxPLLModule->MakeRegisterFile(outf);
	m_RxPLLModule->MakeRegisterFile(outf);
	m_TxLpfModule->MakeRegisterFile(outf);
	m_TxRfModule->MakeRegisterFile(outf);
	m_RxLpfModule->MakeRegisterFile(outf);
	// Makes register map for ADDC as well.
	m_RxVga2Module->MakeRegisterFile(outf);
	m_RxFeModule->MakeRegisterFile(outf);
	outf.close();
}

/**
	Sets control software's configuration according to configuration received from chip.
*/
void Main_Module::MatchGUIToChip()
{
	// Lets Read Data from chip
	m_serPort->SPI_Read(m_TopModule->GetPrData());

	// EnableAllSPIClocks();

	m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
	m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
	m_serPort->SPI_Read(m_TxRfModule->GetPrData());
	m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
	m_serPort->SPI_Read(m_RxFeModule->GetPrData());
	m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
	m_serPort->SPI_Read(m_RxPLLModule->GetPrData());

	// RestoreAllSPIClocks();

	// Lets set GUI according read data
	m_TopModule->SetGUIUnderReadback();
	m_RxLpfModule->SetGUIUnderReadback();
	m_TxLpfModule->SetGUIUnderReadback();
	m_TxRfModule->SetGUIUnderReadback();
	m_RxVga2Module->SetGUIUnderReadback();
	m_RxFeModule->SetGUIUnderReadback();
	m_TxPLLModule->SetGUIUnderReadback();
	m_RxPLLModule->SetGUIUnderReadback();
}

/**
	Performs register map test
	@return True if success, False if fail.
*/
bool Main_Module::TestRegisters()
{
	int regTestCode = UPDATE_PROGRESS_BAR;
	bool bTestStatus = true;
	bool bSoftTx;
	bool bSoftRx;

	if (dRegTest != NULL)
	{
		delete dRegTest;
		dRegTest = NULL;
	}
	dRegTest = new RegisterTest();

	// Enable SoftTX
	// bool bSoftTx = m_TopModule->CustSet_SofTxOnOff(true);
	// m_serPort->SPI_Write(m_TopModule->GetPrData());
	// Enable SoftRX
	// bool bSoftRx = m_TopModule->CustSet_SofRxOnOff(true);
	// m_serPort->SPI_Write(m_TopModule->GetPrData());

	// x EnableAllSPIClocks();

	// Check TxRF
	dRegTest->AddLine("addr: 0x04");
	dRegTest->AddLine("Testing TxRF SPI, Mask 0xAA:");
	m_TxRfModule->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_TxRfModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TxRfModule->GetPrData()) & bTestStatus;

	dRegTest->AddLine("Testing TxRF SPI, Mask 0x55:");
	m_TxRfModule->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_TxRfModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TxRfModule->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// Check RxFE
	dRegTest->AddLine("addr: 0x07");
	dRegTest->AddLine("Testing RxFE SPI, Mask 0xAA:");
	m_RxFeModule->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_RxFeModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxFeModule->GetPrData()) & bTestStatus;

	dRegTest->AddLine("Testing RxFE SPI, Mask 0x55:");
	m_RxFeModule->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_RxFeModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxFeModule->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// Check RxVGA2
	dRegTest->AddLine("addr: 0x06");
	dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
	m_RxVga2Module->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxVga2Module->GetPrData()) & bTestStatus;

	dRegTest->AddLine("addr: 0x05");
	dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
	m_RxVga2Module->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxVga2Module->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// Check RxLPF
	dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
	m_RxLpfModule->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxLpfModule->GetPrData()) & bTestStatus;

	dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
	m_RxLpfModule->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxLpfModule->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// Check TxLPF
	dRegTest->AddLine("addr: 0x03");
	dRegTest->AddLine("Testing TxLPF SPI, Mask 0xAA:");
	m_TxLpfModule->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TxLpfModule->GetPrData()) & bTestStatus;

	dRegTest->AddLine("Testing TxLPF SPI, Mask 0x55:");
	m_TxLpfModule->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TxLpfModule->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// Check TxPLL
	dRegTest->AddLine("addr: 0x01");
	dRegTest->AddLine("Testing TxPLL SPI, Mask 0xAA:");
	m_TxPLLModule->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TxPLLModule->GetPrData()) & bTestStatus;

	dRegTest->AddLine("Testing TxPLL SPI, Mask 0x55:");
	m_TxPLLModule->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TxPLLModule->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// Check RxPLL
	dRegTest->AddLine("addr: 0x02");
	dRegTest->AddLine("Testing RxPLL SPI, Mask 0xAA:");
	m_RxPLLModule->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxPLLModule->GetPrData()) & bTestStatus;

	dRegTest->AddLine("Testing RxPLL SPI, Mask 0x55:");
	m_RxPLLModule->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_RxPLLModule->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// Check Top
	dRegTest->AddLine("addr: 0x00");
	dRegTest->AddLine("Testing Top SPI, Mask 0xAA:");
	m_TopModule->RT_SetTestMask(0xAA);
	m_serPort->SPI_Read(m_TopModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TopModule->GetPrData()) & bTestStatus;

	dRegTest->AddLine("Testing Top SPI, Mask 0x55:");
	m_TopModule->RT_SetTestMask(0x55);
	m_serPort->SPI_Read(m_TopModule->GetPrData());
	bTestStatus = dRegTest->Compare(m_TopModule->GetPrData()) & bTestStatus;
	dRegTest->AddLine("");
	UpdateInterface(regTestCode, NULL);

	// x RestoreAllSPIClocks();

	// Download current configuration from GUI
	Download();

	// ==== VTUNE test ====//
	int iCmpMin, iCmpMax;
	// Enable SoftTX
	bSoftTx = m_TopModule->CustSet_SofTxOnOff(true);
	m_serPort->SPI_Write(m_TopModule->GetPrData());
	// Enable TxPLL clock
	EnableSPIClockByMask(0x01);

	// Sleep(1000);

	// Apply reset
	// m_serPort->SPI_Rst();
	// x EnableAllSPIClocks();

	// Enable TxPLL clock
	// EnableSPIClockByMask(0x01);
	// Enable SoftTX
	// bSoftTxRx = m_TopModule->CustSet_SofTxOnOff(true);
	// m_serPort->SPI_Write(m_TopModule->GetPrData());
	milSleep(5);

	// Check TxPLL VTUNE
	dRegTest->AddLine("Testing TxPLL VTUNE registers:");
	iCmpMin = m_TxPLLModule->GetVTuneState(1, 0);
	iCmpMax = m_TxPLLModule->GetVTuneState(4, 63);
	bTestStatus = dRegTest->Comparators(iCmpMin, iCmpMax) & bTestStatus;
	UpdateInterface(regTestCode, NULL);
	dRegTest->AddLine("");

	RestoreAllSPIClocks();

	milSleep(5);
	// Restore SoftTX Enable
	m_TopModule->CustSet_SofTxOnOff(bSoftTx);
	m_serPort->SPI_Write(m_TopModule->GetPrData());
	// Enable RxPLL clock
	EnableSPIClockByMask(0x04);
	// Enable SoftRX
	bSoftRx = m_TopModule->CustSet_SofRxOnOff(true);
	m_serPort->SPI_Write(m_TopModule->GetPrData());
	milSleep(5);
	// Check RxPLL VTUNE
	dRegTest->AddLine("Testing RxPLL VTUNE registers:");
	iCmpMin = m_RxPLLModule->GetVTuneState(1, 0);
	iCmpMax = m_RxPLLModule->GetVTuneState(4, 63);
	bTestStatus = dRegTest->Comparators(iCmpMin, iCmpMax) & bTestStatus;
	UpdateInterface(regTestCode, NULL);

	// Restore SoftRX Enable
	// m_TopModule->CustSet_SofRxOnOff(bSoftTxRx);
	// m_serPort->SPI_Write(m_TopModule->GetPrData());

	RestoreAllSPIClocks();

	// Download current configuration from GUI
	Download();

	// delete dRegTest;

	return bTestStatus;
};

/**
	Performs register map test.
	@return True if success, False if fail.
*/
bool Main_Module::TestRegistersTrial()
{
	bool testResult = false;
	if (dRegTest != NULL)
	{
		delete dRegTest;
		dRegTest = NULL;
	}
	dRegTest = new RegisterTest();

	// goto RxPLL;

	// x EnableAllSPIClocks();
	for (int i = 0; i < 100; i++)
	{
		// Check TxRF
		dRegTest->AddLine("Testing TxRF SPI, Mask 0xAA:");
		m_TxRfModule->RT_SetTestMask(0xAA);
		m_serPort->SPI_Read(m_TxRfModule->GetPrData());
		testResult = dRegTest->Compare(m_TxRfModule->GetPrData()) & testResult;

		dRegTest->AddLine("Testing TxRF SPI, Mask 0x55:");
		m_TxRfModule->RT_SetTestMask(0x55);
		m_serPort->SPI_Read(m_TxRfModule->GetPrData());
		testResult = dRegTest->Compare(m_TxRfModule->GetPrData())  & testResult;
		dRegTest->AddLine("");

		// Check RxFE
		dRegTest->AddLine("Testing RxFE SPI, Mask 0xAA:");
		m_RxFeModule->RT_SetTestMask(0xAA);
		m_serPort->SPI_Read(m_RxFeModule->GetPrData());
		testResult = dRegTest->Compare(m_RxFeModule->GetPrData()) & testResult;

		dRegTest->AddLine("Testing RxFE SPI, Mask 0x55:");
		m_RxFeModule->RT_SetTestMask(0x55);
		m_serPort->SPI_Read(m_RxFeModule->GetPrData());
		testResult = dRegTest->Compare(m_RxFeModule->GetPrData()) & testResult;
		dRegTest->AddLine("");

		// Check RxVGA2
		dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
		m_RxVga2Module->RT_SetTestMask(0xAA);
		m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
		testResult = dRegTest->Compare(m_RxVga2Module->GetPrData()) & testResult;

		dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
		m_RxVga2Module->RT_SetTestMask(0x55);
		m_serPort->SPI_Read(m_RxVga2Module->GetPrData());
		testResult = dRegTest->Compare(m_RxVga2Module->GetPrData()) & testResult;
		dRegTest->AddLine("");

		// Check RxLPF
		dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
		m_RxLpfModule->RT_SetTestMask(0xAA);
		m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
		testResult = dRegTest->Compare(m_RxLpfModule->GetPrData()) & testResult;

		dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
		m_RxLpfModule->RT_SetTestMask(0x55);
		m_serPort->SPI_Read(m_RxLpfModule->GetPrData());
		testResult = dRegTest->Compare(m_RxLpfModule->GetPrData()) & testResult;
		dRegTest->AddLine("");

		// Check TxLPF
		dRegTest->AddLine("Testing TxLPF SPI, Mask 0xAA:");
		m_TxLpfModule->RT_SetTestMask(0xAA);
		m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
		testResult = dRegTest->Compare(m_TxLpfModule->GetPrData()) & testResult;

		dRegTest->AddLine("Testing TxLPF SPI, Mask 0x55:");
		m_TxLpfModule->RT_SetTestMask(0x55);
		m_serPort->SPI_Read(m_TxLpfModule->GetPrData());
		testResult = dRegTest->Compare(m_TxLpfModule->GetPrData()) & testResult;
		dRegTest->AddLine("");

		// Check TxPLL
		dRegTest->AddLine("Testing TxPLL SPI, Mask 0xAA:");
		m_TxPLLModule->RT_SetTestMask(0xAA);
		m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
		testResult = dRegTest->Compare(m_TxPLLModule->GetPrData()) & testResult;

		dRegTest->AddLine("Testing TxPLL SPI, Mask 0x55:");
		m_TxPLLModule->RT_SetTestMask(0x55);
		m_serPort->SPI_Read(m_TxPLLModule->GetPrData());
		testResult = dRegTest->Compare(m_TxPLLModule->GetPrData()) & testResult;
		dRegTest->AddLine("");

		// RxPLL:
		// m_RxPLLModule->RT_SetTestMask(0x55);
		// m_RxPLLModule->RT_SetTestMask(0xAA);

		// for(int i=0; i<100; i++)
		// {
		// Check RxPLL
		dRegTest->AddLine("Testing RxPLL SPI, Mask 0xAA:");
		m_RxPLLModule->RT_SetTestMask(0xAA);
		m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
		testResult = dRegTest->Compare(m_RxPLLModule->GetPrData()) & testResult;
		// };
		// return true;

		dRegTest->AddLine("Testing RxPLL SPI, Mask 0x55:");
		m_RxPLLModule->RT_SetTestMask(0x55);
		m_serPort->SPI_Read(m_RxPLLModule->GetPrData());
		testResult = dRegTest->Compare(m_RxPLLModule->GetPrData()) & testResult;
		dRegTest->AddLine("");

		// x RestoreAllSPIClocks();
	};

	// Download current configuration from GUI
	Download();

	return true;

	// ==== VTUNE test ====//
	int iCmpMin, iCmpMax;

	// Apply reset
	// m_serPort->SPI_Rst();
	milSleep(5);
	// x EnableAllSPIClocks();

	// Check TxPLL VTUNE
	dRegTest->AddLine("Testing TxPLL VTUNE registers:");
	iCmpMin = m_TxPLLModule->GetVTuneState(1, 0);
	iCmpMax = m_TxPLLModule->GetVTuneState(4, 63);
	testResult = dRegTest->Comparators(iCmpMin, iCmpMax) & testResult;
	dRegTest->AddLine("");

	// Check RxPLL VTUNE
	dRegTest->AddLine("Testing RxPLL VTUNE registers:");
	iCmpMin = m_RxPLLModule->GetVTuneState(1, 0);
	iCmpMax = m_RxPLLModule->GetVTuneState(4, 63);
	testResult = dRegTest->Comparators(iCmpMin, iCmpMax) & testResult;
	dRegTest->AddLine("");

	// x RestoreAllSPIClocks();

	// Download current configuration from GUI
	Download();

	// delete dRegTest;
	return true;
};

/**
	Reads version, revision and mask from the chip and sets received information to submodules.
*/
void Main_Module::UpdateVerRevMask()
{
	char maddr = 0x00; // Top
	char raddr = 0x04;
	int tmp;

	char rez = m_serPort->SPI_Read_OneByte(maddr | raddr);

	tmp = (rez >> 4) & 0x0F;
	m_ver = (char)tmp;

	tmp = rez & 0x0F;
	m_rev = (char)tmp;

	// Read Mask version
	raddr = 0x0E;
	rez = m_serPort->SPI_Read_OneByte(maddr | raddr);
	m_mask = (char)rez;

	m_RxLpfModule->UpdateVerRevMask(m_ver, m_rev, m_mask);
	m_TxLpfModule->UpdateVerRevMask(m_ver, m_rev, m_mask);
	m_TxRfModule->UpdateVerRevMask(m_ver, m_rev, m_mask);
	m_RxVga2Module->UpdateVerRevMask(m_ver, m_rev, m_mask);
	UpdateInterface(UPDATE_VER_REV_MASK, NULL);
}

/**
	Sends given message to interface update callback function.
	@param msg Message to send.
*/
void Main_Module::ShowMessage(string msg)
{
	if(updateInterfaceCallback)
		UpdateInterface(SHOW_POPUP_MESSAGE, msg.c_str());
}

/**

*/
CUARFCN* Main_Module::getUARFCNdata()
{
	return &m_UARFCNDef;
}

/**
	Informs user interface when changes happen.
	@param code Code of the event that happened.
	@param opt_Msg Optional c-string message to pass together with code, used for warning and log messages.
*/
void Main_Module::UpdateInterface(int code, const char *opt_Msg)
{
	if(updateInterfaceCallback && code != 0)
		updateInterfaceCallback(code, opt_Msg);
}
