/***************************************************************
 * Name:      FFTviewerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2013-05-08
 * Copyright: Lime Microsystems ()
 * License:
 **************************************************************/

#include "FFTviewerMain.h"
#include <wx/msgdlg.h>

#include "ctr_6002dr2_LogicDLL.h"
#include "CallbackCodes.h"
#include "frControlPanel.h"
#include "version.h"
#include <dbt.h>

//(*InternalHeaders(FFTviewerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(FFTviewerFrame)
const long FFTviewerFrame::ID_PANEL1 = wxNewId();
const long FFTviewerFrame::ID_PANEL2 = wxNewId();
const long FFTviewerFrame::ID_NOTEBOOK1 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM1 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM2 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM3 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM4 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM5 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM6 = wxNewId();
const long FFTviewerFrame::idMenuAbout = wxNewId();
const long FFTviewerFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long FFTviewerFrame::ID_CONTROL_PANEL = wxNewId();

BEGIN_EVENT_TABLE(FFTviewerFrame,wxFrame)
    //(*EventTable(FFTviewerFrame)
    //*)
END_EVENT_TABLE()

FFTviewerFrame* frmFFTMainWindow = NULL;

FFTviewerFrame::FFTviewerFrame(wxWindow* parent,wxWindowID id)
{
    m_ControlPanel = NULL;
    LMAL_Initialize();
    m_ControlPanel = new frControlPanel(this, ID_CONTROL_PANEL);
    //(*Initialize(FFTviewerFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("FFT viewer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(900,700));
    SetMinSize(wxSize(900,700));
    FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(800,600), 0, _T("ID_NOTEBOOK1"));
    Notebook1->SetMinSize(wxSize(900,500));
    mSpectrum = new pnlSpectrum(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    mTransmitter = new pnlSamplesGenerator(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Notebook1->AddPage(mSpectrum, _("Spectrum"), false);
    Notebook1->AddPage(mTransmitter, _("Transmitter"), false);
    FlexGridSizer1->Add(Notebook1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Close\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM2, _("Start capturing samples"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, ID_MENUITEM3, _("Stop capturing samples"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem5 = new wxMenuItem(Menu1, ID_MENUITEM4, _("Read settings"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu1, ID_MENUITEM5, _("Send settings"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem7 = new wxMenuItem(Menu3, ID_MENUITEM6, _("Control Panel"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuBar1->Append(Menu3, _("Tools"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    mStatusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { 10, -128, -550 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    mStatusBar->SetFieldsCount(3,__wxStatusBarWidths_1);
    mStatusBar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(mStatusBar);
    SetSizer(FlexGridSizer1);
    Layout();

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnQuit);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuStartCaptureSelected);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuStopCaptureSelected);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuReadSettingsSelected);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuSendSettingsSelected);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuItem7Selected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&FFTviewerFrame::OnClose);
    //*)

    frmFFTMainWindow = this;
    //initialize library and set callback functions

	LMAL_MainSetCallbackInterfaceUpdate(UpdateInterface);
	LMLL_Testing_SetCallbackUpdateInterface(UpdateInterface);

	this->SetTitle(this->GetTitle() + " v" + AutoVersion::FULLVERSION_STRING);
	UpdateInterface(UPDATE_VER_REV_MASK, NULL);

    #ifdef WIN32
	SetIcon(wxICON(aaaa));
	#endif
}

FFTviewerFrame::~FFTviewerFrame()
{
    //(*Destroy(FFTviewerFrame)
    //*)
}

void FFTviewerFrame::OnQuit(wxCommandEvent& event)
{
    if(mSpectrum)
        mSpectrum->StopCapturing();
    LMAL_Quit();
}

void FFTviewerFrame::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    wxString msg = "FFT viewer v";
    msg.Append(AutoVersion::FULLVERSION_STRING);
    msg.Append("\nBuild date: ");
    msg.Append(AutoVersion::YEAR);
    msg.Append("-");
    msg.Append(AutoVersion::MONTH);
    msg.Append("-");
    msg.Append(AutoVersion::DATE);
    wxMessageDialog* dlg;
    dlg = new wxMessageDialog(this, msg, _("Welcome to..."));
    dlg->ShowModal();
    delete dlg;
}

void FFTviewerFrame::OnClose(wxCloseEvent& event)
{
    if(mSpectrum)
        mSpectrum->StopCapturing();
    Destroy();
}

/**
	@brief Callback functions to receive messages from library
	@param code update code
	@param *param additional params for code
*/
void FFTviewerFrame::UpdateInterface(int code, char* param)
{
	if(frmFFTMainWindow)
	{
		int version = 0;
		int revision = 0;
		int mask = 0;

		switch(code)
		{
			case UPDATE_VER_REV_MASK:
				LMAL_GetVerRevMask(version, revision, mask);
				frmFFTMainWindow->ShowChipVerRevMask(version, revision, mask);
				break;
			case CHIP_CONNECTED:
				LMAL_GetVerRevMask(version, revision, mask);
				frmFFTMainWindow->ShowChipVerRevMask(version, revision, mask);
				if(frmFFTMainWindow->mSpectrum != NULL)
                    frmFFTMainWindow->mSpectrum->onChipConnect();
				break;
			case CHIP_DISCONNECTED:
				frmFFTMainWindow->ShowChipVerRevMask(0, 0, 0);
				if(frmFFTMainWindow->mSpectrum != NULL)
					frmFFTMainWindow->mSpectrum->onChipDisconnect();
				break;
			case SHOW_LOG_MESSAGE:
				frmFFTMainWindow->PrintStatus(param);
				break;
		}
		//resend message to control panel
		frmFFTMainWindow->m_ControlPanel->UpdateInterface(code, param);
	}
}

void FFTviewerFrame::ShowChipVerRevMask(char ver, char rev, char mask)
{
	char str[176];
	sprintf(str, "Chip - ver: %i rev: %i mask: %i", ver, rev, mask);
	mStatusBar->SetStatusText(str, 1);
}

/**
	@brief Displays message in status bar
	@param *msg message to show
*/
void FFTviewerFrame::PrintStatus(const char *msg)
{
	if( strlen(msg) > 0 )
	{
		mStatusBar->SetStatusText(msg, 2);
	}
}

void FFTviewerFrame::OnMenuItem7Selected(wxCommandEvent& event)
{
    if(m_ControlPanel != NULL)
        m_ControlPanel->Show();
}

void FFTviewerFrame::OnMenuReadSettingsSelected(wxCommandEvent& event)
{
    mSpectrum->ReadSettings();
}

void FFTviewerFrame::OnMenuSendSettingsSelected(wxCommandEvent& event)
{
    mSpectrum->SendSettings();
}

void FFTviewerFrame::OnMenuStartCaptureSelected(wxCommandEvent& event)
{
    mSpectrum->StartCapturing();
}

void FFTviewerFrame::OnMenuStopCaptureSelected(wxCommandEvent& event)
{
    mSpectrum->StopCapturing();
}
