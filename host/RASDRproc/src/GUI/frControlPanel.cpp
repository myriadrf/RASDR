// -----------------------------------------------------------------------------
// FILE:        "frControlPanel.cpp"
// DESCRIPTION: "Source Code File"
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
#include "frControlPanel.h"
#include "ctr_6002dr2_LogicDLL.h"
#include "CallbackCodes.h"
#include "CommonFile.h"
#include <wx/msgdlg.h>
#include "dlgRefClk.h"
#include "dlgSerPort.h"
#include "dlgRegTest.h"
#include <wx/time.h>
//(*InternalHeaders(frControlPanel)
#include <wx/artprov.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/toolbar.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
#include <wx/statusbr.h>
//*)

#include <wx/numdlg.h>

//(*IdInit(frControlPanel)
const long frControlPanel::ID_PANEL2 = wxNewId();
const long frControlPanel::ID_PANEL3 = wxNewId();
const long frControlPanel::ID_PANEL4 = wxNewId();
const long frControlPanel::ID_PANEL5 = wxNewId();
const long frControlPanel::ID_PANEL6 = wxNewId();
const long frControlPanel::ID_PANEL7 = wxNewId();
const long frControlPanel::ID_PANEL8 = wxNewId();
const long frControlPanel::ID_PANEL9 = wxNewId();
const long frControlPanel::ID_PANEL10 = wxNewId();
const long frControlPanel::ID_PANEL11 = wxNewId();
const long frControlPanel::ID_PANEL13 = wxNewId();
const long frControlPanel::ID_PANEL1 = wxNewId();
const long frControlPanel::ID_NOTEBOOK1 = wxNewId();
const long frControlPanel::ID_RICHTEXTCTRL1 = wxNewId();
const long frControlPanel::ID_MENUITEM1 = wxNewId();
const long frControlPanel::ID_MENUITEM2 = wxNewId();
const long frControlPanel::ID_MENUITEM3 = wxNewId();
const long frControlPanel::ID_MENUITEM4 = wxNewId();
const long frControlPanel::ID_MENUITEM9 = wxNewId();
const long frControlPanel::ID_MENUITEM10 = wxNewId();
const long frControlPanel::ID_MENUITEM5 = wxNewId();
const long frControlPanel::ID_MENUITEM6 = wxNewId();
const long frControlPanel::ID_MENUITEM7 = wxNewId();
const long frControlPanel::ID_MENUITEM8 = wxNewId();
const long frControlPanel::ID_TOOLBARITEM1 = wxNewId();
const long frControlPanel::ID_TOOLBARITEM2 = wxNewId();
const long frControlPanel::ID_TOOLBARITEM3 = wxNewId();
const long frControlPanel::ID_TOOLBARITEM4 = wxNewId();
const long frControlPanel::ID_TOOLBAR1 = wxNewId();
const long frControlPanel::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(frControlPanel,wxFrame)
	//(*EventTable(frControlPanel)
	//*)
END_EVENT_TABLE()

frControlPanel* frmMain = NULL;

frControlPanel::frControlPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    frmMain = this;
	BuildContent(parent,id,pos,size);
    //SetIcon(wxICON(aaaa));
	//dSerPort = new dlgSerPort();
	if (! LMAL_IsOpen())
	{
		tbtnDownload->Enable(false);
	}
	else
	{
		tbtnDownload->Enable(true);
	};
	ShowReferenceClk(LMAL_GetReferenceClock());

}

void frControlPanel::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxLongLong t1 = wxGetUTCTimeMillis();
    Freeze();
	//(*Initialize(frControlPanel)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Control panel"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxSTATIC_BORDER, _T("wxID_ANY"));
	SetClientSize(wxSize(900,680));
	SetMinSize(wxSize(900,680));
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	pcSPIS = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(900,450), wxNO_FULL_REPAINT_ON_RESIZE, _T("ID_NOTEBOOK1"));
	m_Customer = new pnlCustomer(pcSPIS, ID_PANEL2, wxDefaultPosition, wxSize(792,527), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	m_top = new pnlTop(pcSPIS, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	m_TxPLL = new pnlTxPLL(pcSPIS, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	m_RxPLL = new pnlRxPLL(pcSPIS, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	m_TxLPF = new pnlTxLPF(pcSPIS, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	m_TxRF = new pnlTxRF(pcSPIS, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	m_RxLPF = new pnlRxLPF(pcSPIS, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
	m_RxVGA2 = new pnlRxVGA2(pcSPIS, ID_PANEL9, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
	m_RxFE = new pnlRxFE(pcSPIS, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
	m_ADDC = new pnlADDC(pcSPIS, ID_PANEL11, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
	m_Board = new pnlBoard(pcSPIS, ID_PANEL13, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
	m_ADF = new pnlADF(pcSPIS, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	pcSPIS->AddPage(m_Customer, _("System"), false);
	pcSPIS->AddPage(m_top, _("Top"), false);
	pcSPIS->AddPage(m_TxPLL, _("Tx PLL + DSM"), false);
	pcSPIS->AddPage(m_RxPLL, _("Rx PLL + DSM"), false);
	pcSPIS->AddPage(m_TxLPF, _("Tx LPF"), false);
	pcSPIS->AddPage(m_TxRF, _("Tx RF"), false);
	pcSPIS->AddPage(m_RxLPF, _("Rx LPF"), false);
	pcSPIS->AddPage(m_RxVGA2, _("Rx VGA2"), false);
	pcSPIS->AddPage(m_RxFE, _("Rx FE"), false);
	pcSPIS->AddPage(m_ADDC, _("ADC / DAC"), false);
	pcSPIS->AddPage(m_Board, _("Board"), false);
	pcSPIS->AddPage(m_ADF, _("ADF4002"), false);
	FlexGridSizer1->Add(pcSPIS, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lbMsgs = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, _("Text"), wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
		wxRichTextAttr rchtxtAttr_1;
	lbMsgs->SetMinSize(wxSize(-1,100));
	FlexGridSizer1->Add(lbMsgs, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	mnuNew = new wxMenuItem(Menu1, ID_MENUITEM1, _("New project"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(mnuNew);
	mnuOpen = new wxMenuItem(Menu1, ID_MENUITEM2, _("Open project"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(mnuOpen);
	mnuSave = new wxMenuItem(Menu1, ID_MENUITEM3, _("Save"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(mnuSave);
	mnuSaveAs = new wxMenuItem(Menu1, ID_MENUITEM4, _("Save as"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(mnuSaveAs);
	Menu1->AppendSeparator();
	mnuReadRVF_rfif = new wxMenuItem(Menu1, ID_MENUITEM9, _("Save under RFIF"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(mnuReadRVF_rfif);
	Menu1->AppendSeparator();
	mnuChipToGUI = new wxMenuItem(Menu1, ID_MENUITEM10, _("Chip --> GUI"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(mnuChipToGUI);
	MenuBar1->Append(Menu1, _("File"));
	Menu2 = new wxMenu();
	mnuAutoDwnld = new wxMenuItem(Menu2, ID_MENUITEM5, _("Auto Download"), wxEmptyString, wxITEM_CHECK);
	Menu2->Append(mnuAutoDwnld);
	mnuAutoDwnld->Check(true);
	mnuRefClk = new wxMenuItem(Menu2, ID_MENUITEM6, _("Reference Clock"), wxEmptyString, wxITEM_NORMAL);
	Menu2->Append(mnuRefClk);
	CommunicationSettings1 = new wxMenuItem(Menu2, ID_MENUITEM7, _("Communication Settings"), wxEmptyString, wxITEM_NORMAL);
	Menu2->Append(CommunicationSettings1);
	MenuBar1->Append(Menu2, _("Options"));
	Menu3 = new wxMenu();
	RegisterTest1 = new wxMenuItem(Menu3, ID_MENUITEM8, _("Registers test"), wxEmptyString, wxITEM_NORMAL);
	Menu3->Append(RegisterTest1);
	MenuBar1->Append(Menu3, _("Tools"));
	SetMenuBar(MenuBar1);
	ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_HORZ_TEXT|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBarItem1 = ToolBar1->AddTool(ID_TOOLBARITEM1, _("New"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
	ToolBarItem2 = ToolBar1->AddTool(ID_TOOLBARITEM2, _("Open"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
	ToolBarItem3 = ToolBar1->AddTool(ID_TOOLBARITEM3, _("Save"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
	ToolBar1->AddSeparator();
	tbtnDownload = ToolBar1->AddTool(ID_TOOLBARITEM4, _("Send configuration"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FLOPPY")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Send all configuration"), wxEmptyString);
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	dlgOpen = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	sbMain = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
	int __wxStatusBarWidths_1[3] = { 10, -10, -10 };
	int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
	sbMain->SetFieldsCount(3,__wxStatusBarWidths_1);
	sbMain->SetStatusStyles(3,__wxStatusBarStyles_1);
	SetStatusBar(sbMain);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuNewSelected);
	Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuOpenSelected);
	Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuSaveSelected);
	Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuSaveAsSelected);
	Connect(ID_MENUITEM9,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuReadRVF_rfifSelected);
	Connect(ID_MENUITEM10,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuChipToGUISelected);
	Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuAutoDwnldSelected1);
	Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnmnuRefClkSelected1);
	Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnCommunicationSettings1Selected1);
	Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&frControlPanel::OnRegisterTest1Selected);
	Connect(ID_TOOLBARITEM1,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frControlPanel::OnmnuNewSelected);
	Connect(ID_TOOLBARITEM2,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frControlPanel::OnmnuOpenSelected);
	Connect(ID_TOOLBARITEM3,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frControlPanel::OnmnuSaveSelected);
	Connect(ID_TOOLBARITEM4,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&frControlPanel::OntbtnDownloadClicked);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&frControlPanel::OnClose);
	//*)
	t1 = wxGetUTCTimeMillis();
	// Clear Messages
	lbMsgs->Clear();
	m_top->Initialize();
	m_RxLPF->Initialize(m_ADDC);
	m_TxLPF->Initialize(NULL);
	m_TxRF->Initialize();
	m_RxVGA2->Initialize();
	m_RxFE->Initialize();
	m_TxPLL->Initialize();
	m_RxPLL->Initialize();
	m_ADDC->Initialize();
	m_Customer->Initialize();
	m_Board->Initialize();
	t1 = wxGetUTCTimeMillis();
	// m_frmBoard->Initialize();

	// Project by default
	Thaw();
	setCurrentFileName("untitled.prj");

#ifndef CUSTOMER_MODE
	//double Freq = ReadRefClkFromReg();
	//ShowReferenceClk(Freq);
#endif

#ifdef CUSTOMER_MODE
	if (FileExists(ChangeFileExt(Application->ExeName, ".prj")))
	{
		if (!FileIsNotEmpty(ChangeFileExt(Application->ExeName, ".prj")))
		{
			ShowMessage("Configuration file is corrupt.\n\n\
        Contact Lime Microsystems\n\
        Unit 57 Surrey Tech Centre Occam Road\n\
        The Surrey Research Park Guildford Surrey\n\
        GU2 7YG\n\n\
        Tel: +44 (0)1483 684801, +44(0)142 8653335\n\
        Fax: +44(0) 1428656662\n\n\
		info@limemicro.com");
			Application->Terminate();
		};

		setCurrentFileName(ChangeFileExt(Application->ExeName, ".prj"));
		LoadConfiguration(m_sFileName);
		tbtnDownload->Click();
	}
	else
	{
		// Close();
		ShowMessage("You need configuration file to run this software.\n\n\
      Contact Lime Microsystems\n\
      Unit 57 Surrey Tech Centre Occam Road\n\
      The Surrey Research Park Guildford Surrey\n\
      GU2 7YG\n\n\
      Tel: +44 (0)1483 684801, +44(0)142 8653335\n\
      Fax: +44(0) 1428656662\n\n\
      info@limemicro.com");

		Application->Terminate();
	};
#endif

	// ===============================================================
	//LoadAdditionalSettings();
	// ===============================================================

	// slLogMesg(4);
	UpdateVerRevMask();
	pcSPIS->SetSelection(0);
	char updateAllInterface = 0xff;
	UpdateInterface(2, &updateAllInterface);
	slLogMesg(15);
}

frControlPanel::~frControlPanel()
{

	//(*Destroy(frControlPanel)
	//*)

}



void frControlPanel::OnmnuNewSelected(wxCommandEvent& event)
{
    LMAL_MainFileNewExecute();
	setCurrentFileName("untitled.prj");
	m_top->SetGuiDefaults();
	m_TxLPF->SetGuiDefaults();
	m_RxLPF->SetGuiDefaults();
	m_TxRF->SetGuiDefaults();
	m_RxVGA2->SetGuiDefaults();
	m_RxFE->SetGuiDefaults();
	m_TxPLL->SetGuiDefaults();
	m_RxPLL->SetGuiDefaults();
	m_ADDC->SetGuiDefaults();
	//m_frmBoard->SetGuiDefaults();

	LoadAdditionalSettings();

	// slLogMesg(1);
}

void frControlPanel::OnmnuOpenSelected(wxCommandEvent& event)
{
    wxFileDialog *openFileDialog = new wxFileDialog(this, _("Open project file"), "", "", "Project-Files (*.prj)|*.prj", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog->ShowModal() == wxID_CANCEL)
        return;

    setCurrentFileName(openFileDialog->GetPath().ToStdString().c_str());
    LMAL_MainOpenFile( (char*)openFileDialog->GetPath().ToStdString().c_str());

    m_top->UpdateGUI();
    m_RxLPF->UpdateGUI();
    m_TxLPF->UpdateGUI();
    m_TxRF->UpdateGUI();
    m_RxVGA2->UpdateGUI();
    m_RxFE->UpdateGUI();
    m_TxPLL->UpdateGUI();
    m_RxPLL->UpdateGUI();
    //tbtnDownload->Click();
}

void frControlPanel::OnmnuSaveSelected(wxCommandEvent& event)
{
	if (m_sFileName == "untitled.prj")
	{
		OnmnuSaveAsSelected(event);
	}
	else
	{
		LMAL_MainFileSave();
	};
}

void frControlPanel::OnmnuSaveAsSelected(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save project"), "", "", "Project-Files (*.prj)|*.prj", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    setCurrentFileName(saveFileDialog.GetPath().ToStdString().c_str());
    LMAL_MainFileSaveAs( (char*)toCString(m_sFileName));
}

void frControlPanel::OnmnuAutoDwnldSelected(wxCommandEvent& event)
{
}

void frControlPanel::OnCommunicationSettings1Selected(wxCommandEvent& event)
{
}

void frControlPanel::OnRegisterTest1Selected(wxCommandEvent& event)
{
    TestRegisters();
}

void frControlPanel::OnmnuAboutSelected(wxCommandEvent& event)
{
}

// ---------------------------------------------------------------------------
bool frControlPanel::FileIsNotEmpty(wxString filename)
{
	long curpos, length;
	FILE *stream;

	stream = fopen(toCString(filename), "r");

	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fclose(stream);

	return (length > 0);
}

// ---------------------------------------------------------------------------
void frControlPanel::LoadConfiguration(wxString sIniName)
{
	LMAL_MainOpenFile((char*)toCString(sIniName));
	ShowReferenceClk(LMAL_GetReferenceClock());
};

// ---------------------------------------------------------------------------
void frControlPanel::EnableAllSPIClocks()
{
	LMAL_EnableAllSPIClocks();
};

// ---------------------------------------------------------------------------
void frControlPanel::RestoreAllSPIClocks()
{
	LMAL_RestoreAllSPIClocks();
};

// ------------------------------------------------------------------------------
// Overwrite hardware defaults
// ------------------------------------------------------------------------------
void frControlPanel::LoadAdditionalSettings()
{
	// Top SPI
	// 1.a. When Soft Tx is Enabled it automatically enables Tx DSM SPI
	// Figured out in event handler;
	// 1.b. When Soft Rx is Enabled it automatically enables Rx DSM SPI
	// Figured out in event handler;
	// 1.c. Enable Rx OUT/ADC In Switch
	// ? m_MainModule->getTop()->CustSet_rgrRXOUTSW(1);
	// 1.d. Disable PLLCLKOUT
	// ? m_MainModule->getTop()->CustSet_PLLCLKOUT(false);
	m_top->UpdateGUI();

	// Tx/RxPLL SPIs
	// 2.a. Set CP Up Offset to 30 uA
	LMLL_TxPLLSetOFFUP(3);
	LMLL_RxPLLSetOFFUP(3);
	m_TxPLL->UpdateGUI();
	m_RxPLL->UpdateGUI();

	// Rx VGA2
	// 3.a. VGA2 CM Voltage set to 12.
	// m_RxVGA2->CustSet_cmbVCM(12);
	//LMLL_RxVGA2_SetVCMfromOrderedList(13);
	LMLL_RxVGA2SetVCM(9);
	m_RxVGA2->UpdateGUI();

	// Rx FE
	// 4.a. LNA Load Resistor set to 55
	LMLL_RxFESetRDLINT_LNA_RXFE(55);
	m_RxFE->UpdateGUI();

	// ADC /DAC
	// 5.a. ADC Common Mode Adj. set to 960mV
	LMLL_ADDCSetCoomonModeAdj(1);
	LMLL_ADDCSetRefGainAdj(1);
	m_ADDC->UpdateGUI();

	// Tx RF
	// Set "LO Buffer Bias Current" to 6
	LMLL_TxRfSetICT_TXLOBUF(4);
	m_TxRF->UpdateGUI();
};

/*
// ---------------------------------------------------------------------------
void __fastcall frControlPanel::ChipGUI1Click(wxCommandEvent& event)
{
	LMAL_MainCompareChipToGUI();
}

// ---------------------------------------------------------------------------
void __fastcall frControlPanel::mnuReadConfigurationClick(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open file"), "", "", "rdb files (*.rdb)|*.rdb", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LMAL_MainReadConfiguration( (char*)toCString(openFileDialog.GetPath());
}

// ---------------------------------------------------------------------------
void frControlPanel::DevicesChanged()
{
	if( !LMAL_IsOpen() )
	{
		tbtnDownload->Enabled = false;
	}
	else
	{
		tbtnDownload->Enabled = true;
	}
}

// ---------------------------------------------------------------------------
void __fastcall frControlPanel::CMUpdateInterface(TMessage Message)
{
	switch (Message.LParam)
	{
	case TxPllAddr:
		m_TxPLL->UpdateGUI();
		break;
	case RxPllAddr:
		m_RxPLL->UpdateGUI();
		break;
	}
};

// ---------------------------------------------------------------------------
void __fastcall frControlPanel::CMLog(TMessage &Message)
{
	slLogMesg(Message.LParam);
};

// ---------------------------------------------------------------------------
void __fastcall frControlPanel::CMRead(TMessage &Message)
{
	// ? m_MainModule->CMRead(Message.WParam, Message.LParam);
}

// ---------------------------------------------------------------------------
void __fastcall frControlPanel::CMAutoDownload(TMessage &Message)
{
	if (!mnuAutoDwnld->Checked)
		return;

	mnuAutoDwnld->Enabled = false;
	// ? m_MainModule->CMAutoDownload(Message.LParam);
	mnuAutoDwnld->Enabled = true;
}
*/
// ----------------------------------------------------------------------------
// Writes to the log
// ----------------------------------------------------------------------------
void frControlPanel::slLogMesg(const char *msg)
{
	lbMsgs->AppendText(msg);
	lbMsgs->AppendText("\n");
	//lbMsgs->ItemIndex = lbMsgs->Items->Count - 1;
}

void frControlPanel::slLogMesg(int num)
{
	wxString message;

	switch (num)
	{
	case 0:
		message = "Project file opened: ";
		message = message + m_sFileName;
		lbMsgs->AppendText(message);
		break;

	case 1:
		message = "Project file created: ";
		message = message + m_sFileName;
		lbMsgs->AppendText(message);
		break;

	case 2:
		message = "Project file saved as: ";
		message = message + m_sFileName;
		lbMsgs->AppendText(message);
		break;

	case 3:
		message = "Project file saved: ";
		message = message + m_sFileName;
		lbMsgs->AppendText(message);
		break;

	case 4:
		message = "Default configuration loaded to the GUI.";
		lbMsgs->AppendText(message);
		break;

	case 5:
		message = "Configuration downloaded to the hardware.";
		lbMsgs->AppendText(message);
		break;

	case 6:
		message = "Parallel port initialized successfully.";
		lbMsgs->AppendText(message);
		break;

	case 8:
		// message =	"Reset signal sent to the Chip.";
		// lbMsgs->AppendText(message);
		break;

	case 9:
		message = "Reset signal is ACTIVE.";
		//lbMsgs->AppendText(message);
		break;

	case 10:
		message = "Reset signal is INACTIVE.";
		//lbMsgs->AppendText(message);
		break;

	case 11:
		message = " Automatic Download Mode ";
		lbMsgs->AppendText(message);
		break;

	case 12:
		message = " Manual Download Mode ";
		lbMsgs->AppendText(message);
		break;

	case 13:
		message = "Serial port initialized successfully.";
		lbMsgs->AppendText(message);
		break;

	case 14:
		message =
			"You are not able to control the board since serial port is not";
		lbMsgs->AppendText(message);
		message =
			"accessable. Check if USB to Serial board is connected to the PC USB port.";
		lbMsgs->AppendText(message);
		message =
			"To be able to download configuration, fix the problem and run software again.";
		lbMsgs->AppendText(message);
		break;
	case 15:
		unsigned int bufLen = LMAL_MainGetMessageLogLength();
		char *tempBuf = new char [bufLen];
		memset(tempBuf, 0, bufLen);
		LMAL_MainGetMessageLogMessages(tempBuf);
		lbMsgs->AppendText(tempBuf);
		delete []tempBuf;

		break;
	};
	lbMsgs->AppendText("\n");

	//lbMsgs->ItemIndex = lbMsgs->Items->Count - 1;
};

// ----------------------------------------------------------------------------
// Sets name of the current project
// ----------------------------------------------------------------------------
void frControlPanel::setCurrentFileName(wxString fileName)
{
	LMAL_MainSetCurrentFileName((char*)fileName.ToStdString().c_str());
	this->m_sFileName = fileName;

#ifdef ALTERA_EDITION
	wxString shownName = "6002Dr2 Altera Edition. ";
#else
	wxString shownName = "6002Dr2 Test. ";
#endif

	if (fileName.Length() == 0)
		shownName = shownName + "untitled.prj";
	else
		shownName = shownName + fileName;

	shownName = shownName + " - Project File";

	this->SetTitle(shownName);
}

// ---------------------------------------------------------------------------
void frControlPanel::ShowReferenceClk(double Val)
{
	sbMain->SetStatusText(" Ref. Clock, Hz: ", 2);
	sbMain->SetStatusText(sbMain->GetStatusText(2) + wxString::Format("%.0f",Val), 2);
}
/*
// ---------------------------------------------------------------------------
// dec = 1 if format is decimal, dec = 0 if format is hexadecimal;
// ---------------------------------------------------------------------------
void frControlPanel::SaveUnderRVF_Format(int dec)
{
	char drive[MAXDRIVE] = "";
	char dir[MAXDIR] = "";
	char file[MAXFILE] = "";
	char ext[MAXEXT] = "";
	char s[MAX_PATH] = "";
	ofstream outf;

	memset(s, '\0', sizeof(s));
	memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
	fnsplit(s, drive, dir, file, ext);

	dlgSave->DefaultExt = "rvf";
	dlgSave->FileName = "*.rvf";
	dlgSave->Filter = "rvf files (*.rvf)|*.rvf";
	// *DLG dlgSave->InitialDir = drive;
	// *DLG dlgSave->InitialDir = dlgSave->InitialDir + dir;

	if (dlgSave->Execute())
	{
		LMAL_MainSaveUnderRVF_Format( (char*)toCString(dlgSave->FileName), dec);
	};
}
*/
// ---------------------------------------------------------------------------
void frControlPanel::mnuReadRVFClick(wxCommandEvent& event)
{
	//SaveUnderRVF_Format(1);
}

// ---------------------------------------------------------------------------
void frControlPanel::mnuReadRVF_hexClick(wxCommandEvent& event)
{
	//SaveUnderRVF_Format(0);
}

/*
// ---------------------------------------------------------------------------
void frControlPanel::ChipGUI2Click(wxCommandEvent& event)
{
	LMAL_MainReadSettingsFromChip();
	m_top->UpdateGUI();
	m_RxLPF->UpdateGUI();
	m_TxLPF->UpdateGUI();
	m_TxRF->UpdateGUI();
	m_RxVGA2->UpdateGUI();
	m_RxFE->UpdateGUI();
	m_TxPLL->UpdateGUI();
	m_RxPLL->UpdateGUI();
}
*/

// ---------------------------------------------------------------------------
// Register Map Test
// ---------------------------------------------------------------------------
bool frControlPanel::TestRegisters()
{
	dlgRegTest *dRegTest = new dlgRegTest(this);
	dRegTest->Show();
	char ctmp[80];
	memset(ctmp, 0, 80);
	bool success = LMAL_TestRegisters();

/*
	if(success)
		ShowMessage("test OK");
	else
		ShowMessage("test fail");
*/
	unsigned int logLen = LMAL_MainRegTestGetLogLength();
	char *messageLog = new char[logLen];
	memset(messageLog, 0, logLen);
	LMAL_MainRegTestGetLogMessages(messageLog);

	dRegTest->AddLine(messageLog);

	delete []messageLog;

	return success;
};

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void frControlPanel::UpdateVerRevMask()
{
	int ver = 0 , rev = 0, mask = 0;
	LMAL_GetVerRevMask(ver, rev, mask);

	wxString Str = "Chip Ver: ";
	Str << ver;
	Str << " Rev: " << rev;
	Str << " Msk: " << mask;
	sbMain->SetStatusText(Str, 1);
}
// ---------------------------------------------------------------------------
void frControlPanel::UpdateInterface(int code, const char *opt_Msg)
{
	if(frmMain)
	{
		switch(code)
		{
			case NOTHING: //does nothing
				break;
			case SHOW_POPUP_MESSAGE: //show pop up message
				wxMessageBox( opt_Msg, _("Message"), wxICON_QUESTION | wxYES_NO, frmMain);
				break;
			case UPDATE_INTERFACE_DATA: // updates interface data
				if(opt_Msg)
				switch(*opt_Msg)
				{
					case TopAddr:
						frmMain->m_top->UpdateGUI();
						break;
					case TxLpfAddr:
						frmMain->m_TxLPF->UpdateGUI();
						break;
					case RxLpfAddr:
						frmMain->m_RxLPF->UpdateGUI();
						break;
					case RxVGA2Addr:
						frmMain->m_RxVGA2->UpdateGUI();
						break;
					case RxPllAddr:
						frmMain->m_RxPLL->UpdateGUI();
						break;
					case TxPllAddr:
						frmMain->m_TxPLL->UpdateGUI();
						break;
					case TxRFAddr:
						frmMain->m_TxRF->UpdateGUI();
						break;
					case RxFEAddr:
						frmMain->m_RxFE->UpdateGUI();
						break;
					//case ADFAddr:
					//	frmMain->m_frmBoard->UpdateGUI();
					//	break;
					case 0xFF: // updates all modules interfaces
						frmMain->m_top->UpdateGUI();
						frmMain->m_TxLPF->UpdateGUI();
						frmMain->m_RxLPF->UpdateGUI();
						frmMain->m_RxVGA2->UpdateGUI();
						frmMain->m_RxPLL->UpdateGUI();
						frmMain->m_TxPLL->UpdateGUI();
						frmMain->m_TxRF->UpdateGUI();
						frmMain->m_RxFE->UpdateGUI();
						//frmMain->m_frmBoard->UpdateGUI();
                    	break;
				}
				break;
			case SHOW_LOG_MESSAGE: // show received message in log
				frmMain->slLogMesg(opt_Msg);
				break;
			case READ_ALL_LOG_MESSAGES: // reads messages from logic part log
				frmMain->slLogMesg(15);
				break;
			case UPDATE_VER_REV_MASK: // update chip version, revision, mask, and check connection
				frmMain->UpdateVerRevMask();
				if( !LMAL_IsOpen() )
					frmMain->tbtnDownload->Enable(false);
				else
					frmMain->tbtnDownload->Enable(true);
				break;
			case CHIP_CONNECTED: //chip has been connected

				break;
			case CHIP_DISCONNECTED: //chip has been disconnected

				break;
		}
		//frmMain->ChipGUI2Click(Application);
	}
}

//---------------------------------------------------------------------------



void frControlPanel::OntbtnDownloadClicked(wxCommandEvent& event)
{
    tbtnDownload->Enable(false);
	LMAL_MainDownload();
	tbtnDownload->Enable(true);
	// slLogMesg(5);
}

void frControlPanel::OnmnuAutoDwnldSelected1(wxCommandEvent& event)
{
    //mnuAutoDwnld->Check(!mnuAutoDwnld->IsChecked());
	LMAL_MainSetAutoDownload(mnuAutoDwnld->IsChecked());

	if (mnuAutoDwnld->IsChecked())
	{

		sbMain->SetStatusText(" Automatic Download Mode", 1);
	}
	else
	{
		sbMain->SetStatusText(" Manual Download Mode", 1);
	};
}

void frControlPanel::OnCommunicationSettings1Selected1(wxCommandEvent& event)
{
    dlgSerPort *dlg = new dlgSerPort(this);

    dlg->ShowModal();

    delete dlg;
}

void frControlPanel::OnmnuRefClkSelected1(wxCommandEvent& event)
{
    dlgRefClk *dlg = new dlgRefClk(this);
    dlg->txtRefClk->SetValue( wxString::Format("%.6f", LMAL_GetReferenceClock()/1000000 ));
    if( dlg->ShowModal() == wxOK)
    {
        double MHz = 0;
        dlg->txtRefClk->GetValue().ToDouble(&MHz);
        LMAL_SetReferenceClock(MHz*1000000);
		ShowReferenceClk(MHz*1000000);
    }
    delete dlg;
}

void frControlPanel::OnmnuChipToGUISelected(wxCommandEvent& event)
{
    LMAL_MainReadSettingsFromChip();
	m_top->UpdateGUI();
	m_RxLPF->UpdateGUI();
	m_TxLPF->UpdateGUI();
	m_TxRF->UpdateGUI();
	m_RxVGA2->UpdateGUI();
	m_RxFE->UpdateGUI();
	m_TxPLL->UpdateGUI();
	m_RxPLL->UpdateGUI();
}

void frControlPanel::OnClose(wxCloseEvent& event)
{
    this->Show(false);
//    Destroy();
}

void frControlPanel::OnmnuReadRVFSelected(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "Text-Files (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LMAL_MainSaveUnderRVF_Format(saveFileDialog.GetPath().ToStdString().c_str(), 1);
}

void frControlPanel::OnmnuReadRVF_hexSelected(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "Text-Files (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LMAL_MainSaveUnderRVF_Format(saveFileDialog.GetPath().ToStdString().c_str(), 0);
}

void frControlPanel::OnmnuReadRVF_rfifSelected(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "sh files (*.sh)|*.sh", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    int rfifparam = wxGetNumberFromUser("", "rfif parameter", "Enter rfif Parameter", 0, 0, 100, NULL );

    if ( rfifparam != -1)
    {
        LMAL_MainSaveUnderRFIF_Format( (char*)saveFileDialog.GetPath().ToStdString().c_str(), rfifparam);
    };
}

void frControlPanel::OnmnuSaveRegistersSelected(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save registers"), "", "", "Text-Files (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LMAL_MainSaveRegisters(saveFileDialog.GetPath().ToStdString().c_str());
}

void frControlPanel::Onm_CustomerPaint(wxPaintEvent& event)
{
}
