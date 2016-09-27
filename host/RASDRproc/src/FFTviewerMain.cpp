// -----------------------------------------------------------------------------
// FILE:        "FFTviewerMain.cpp"
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
/***************************************************************
 * Name:      FFTviewerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2013-05-08
 * Copyright: Lime Microsystems ()
 * License:
 **************************************************************/

#include "FFTviewerMain.h"
#include "globals.h"
#include <wx/msgdlg.h>
#include "ctr_6002dr2_LogicDLL.h"
#include "CallbackCodes.h"
#include "frControlPanel.h"
#include "version.h"
#include <dbt.h>
#include "PopList.h"
#include "PopTuning.h"
//#include "PopTimeSpan.h"
#include "PopSetupRSS.h"
#include "SetupFFTout.h"
#include "SetupPWROut.h"
#include "SeupPulsePeriod.h"
#include "SetupDMOut.h"
#include "Setup_Simulator.h"
//#include <errno.h>

//(*InternalHeaders(FFTviewerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(FFTviewerFrame)
const long FFTviewerFrame::ID_PANEL1 = wxNewId();
const long FFTviewerFrame::ID_NOTEBOOK1 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM1 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM2 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM3 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM5 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM6 = wxNewId();
const long FFTviewerFrame::idFrameDelay = wxNewId();
const long FFTviewerFrame::idTuningParameters = wxNewId();
const long FFTviewerFrame::ID_MENUITEM4 = wxNewId();
const long FFTviewerFrame::ID_MENUITEM7 = wxNewId();
const long FFTviewerFrame::idRssParameters = wxNewId();
const long FFTviewerFrame::idMenuAbout = wxNewId();
const long FFTviewerFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long FFTviewerFrame::ID_CONTROL_PANEL = wxNewId();
pnlSpectrum *mSpectrum;

BEGIN_EVENT_TABLE(FFTviewerFrame,wxFrame)
    //(*EventTable(FFTviewerFrame)
    //*)

END_EVENT_TABLE()

FFTviewerFrame* frmFFTMainWindow = NULL;

FFTviewerFrame::FFTviewerFrame(wxWindow* parent,wxWindowID id) :
    m_CFG_FileClassPtr(NULL)
{
    m_ControlPanel = NULL;
    mSpectrum = NULL;
    m_CFG_FileClassPtr = NULL;
    LMAL_Initialize();
    m_ControlPanel = new frControlPanel(this, ID_CONTROL_PANEL);

    //(*Initialize(FFTviewerFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("RASDRproc"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX, _T("wxID_ANY"));
    SetClientSize(wxSize(1200,900));
    SetMinSize(wxSize(1200,900));
    FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(1072,678), 0, _T("ID_NOTEBOOK1"));
    Notebook1->SetMinSize(wxSize(1072,678));
    mSpectrum = new pnlSpectrum(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_PANEL1"));
    Notebook1->AddPage(mSpectrum, _("Spectrum"), false);
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
    MenuItem6 = new wxMenuItem(Menu1, ID_MENUITEM5, _("Save Configuration"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem7 = new wxMenuItem(Menu3, ID_MENUITEM6, _("Control Panel"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuBar1->Append(Menu3, _("Tools"));
    Menu4 = new wxMenu();
    MenuItem8 = new wxMenuItem(Menu4, idFrameDelay, _("Frame Delay"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem8);
    MenuItem8B = new wxMenuItem(Menu4, idTuningParameters, _("Tuning Parameters"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem8B);
    MenuBar1->Append(Menu4, _("Performance Parameters"));
    Menu5 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu5, ID_MENUITEM4, _("Setup FFT  Output"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem5);
    MenuItem9 = new wxMenuItem(Menu5, ID_MENUITEM7, _("Setup Power Output"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu5, idRssParameters, _("Setup RSS Output"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem10);
    MenuBar1->Append(Menu5, _("Define Output"));
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

    mSpectrum->Connect(wxEVT_PAINT,(wxObjectEventFunction)&FFTviewerFrame::OnmSpectrumPaint,0,this);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnQuit);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuStartCaptureSelected);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuStopCaptureSelected);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuItemSaveConfigSelected);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnMenuItem7Selected);
    Connect(idFrameDelay,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnFrameDelaySelected);
    Connect(idTuningParameters,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnTuningParametersSelected);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnSetupFFTOutSelected);
    Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnSetupPWROutSelected);
    Connect(idRssParameters,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnRSSParametersSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&FFTviewerFrame::OnClose);
    //*)
//    Connect(wxID_YES,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FFTviewerFrame::OnFFTfileYESbtnClick);
    frmFFTMainWindow = this;
//cout << "Before 1st Yield in Main" << endl;
    wxYield();
    //initialize library and set callback functions
//cout << "Before set call back in viewer main" << endl;
	LMAL_MainSetCallbackInterfaceUpdate(UpdateInterface);
	LMLL_Testing_SetCallbackUpdateInterface(UpdateInterface);

	this->SetTitle(this->GetTitle() + " v" + AutoVersion::FULLVERSION_STRING);
	UpdateInterface(UPDATE_VER_REV_MASK, NULL);
//    wxYield();
//    cout <<"After 2nd Yield in Main" << endl;
    #ifdef WIN32
	SetIcon(wxICON(aaaa));
	#endif
//	cout << "After SetIcon in viewer main" << endl;
}

FFTviewerFrame::~FFTviewerFrame()
{
    if(CLOSE_DEBUG) cout << "Entering ~FFTviewerFrame()" << endl;
/*
cout << "Before Notebook1 Destroy " << endl;
    if(Notebook1 != NULL) {
        Notebook1->Destroy();
        Notebook1 = NULL;
        cout << "After Notebook1 Destroy" << endl;
        mSpectrum = NULL;}
    Sleep(1000); */

 /*   if(mSpectrum != NULL) {
//        if(mSpectrum->m_capturingData) mSpectrum->StopCapturing();
        mSpectrum->Destroy();}

    cout << "After return from mSpectrum->Destory" << endl; */
 //   wxFrame::Destroy();
    //GetParent()->Close(true);
//    Exit(0);
  //  GetParent()->Destroy();
//    CloseWindow(FFTviewerFrame);
//    Close();
//   Show(false);

  //  Destroy();

    //(*Destroy(FFTviewerFrame)
    //*)
    if( m_CFG_FileClassPtr != NULL) {
        m_CFG_FileClassPtr->Close();
        delete m_CFG_FileClassPtr;
        m_CFG_FileClassPtr = NULL;
    }
    if(CLOSE_DEBUG) cout << "Exiting ~FFTviewerFrame()" << endl;
}

void FFTviewerFrame::OnQuit(wxCommandEvent& event)
{
    if(CLOSE_DEBUG) cout << "Entering FFTviewerFrame::OnQuit()" << endl << flush;
    shutdown();
    if(CLOSE_DEBUG) cout << "After FFTviewerFrame::shutdown()" << endl << flush;
    Destroy();
    if(CLOSE_DEBUG) cout << "After FFTviewerFrame::Destroy()" << endl << flush;
    if(CLOSE_DEBUG) cout << "Exiting FFTviewerFrame::OnQuit()" << endl << flush;
}
string DelayStr;

void FFTviewerFrame::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    wxString msg = "RASDRproc v";
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
/*
void FFTviewerFrame::term_error(int num)
{
    cout<<"term_error exit"<<endl;
    exit(-1);
} */
void FFTviewerFrame::OnClose(wxCloseEvent& event)
{
    if(CLOSE_DEBUG) cout << "Entering FFTviewerFrame::OnClose()" << endl << flush;
    shutdown();
    if(CLOSE_DEBUG) cout << "After FFTviewerFrame::shutdown()" << endl << flush;
    Destroy();
    if(CLOSE_DEBUG) cout << "After FFTviewerFrame::Destroy()" << endl << flush;
    if(CLOSE_DEBUG) cout << "Exiting FFTviewerFrame::OnClose()" << endl << flush;
};
void FFTviewerFrame :: shutdown()
{
    //Avoid redundant processing
  //  Disconnect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FFTviewerFrame::OnQuit);


    SaveConfiguration();

/*
    if(mWaterfall != NULL) {
        mWaterfall->Destroy();
        mWaterfall = NULL;
        cout << "mWaterfall Destroyed " << endl;}
*/

//    g_frame_delay = 0; // Release any data in processing.

    if(mSpectrum != NULL) {
        // Turn off Power recording
//        if(g_PWRfileRecording) g_PWRfileRecording = false;
        if(mSpectrum->m_capturingData) {
                mSpectrum->StopCapturing();
                if(CLOSE_DEBUG) cout << "Capturing Stopped" << endl; }
//        ogl_FFTline->Destroy();
//        ogl_IQline->Destroy();
//        ogl_IQscatter->Destroy();
//        mSpectrum->Destroy();
 //       mSpectrum = NULL;
 //       wxYield();
 //       m_updateTimer->Destroy();

        mSpectrum->Disconnect(wxEVT_PAINT,(wxObjectEventFunction)&FFTviewerFrame::OnmSpectrumPaint,0,this);

    }
 /*      if(m_ControlPanel != NULL) {
        m_ControlPanel->Destroy();
        m_ControlPanel = NULL;
        cout << " After Control Panel Destroy()" << endl;} */

 /*   if(MenuItem8 != NULL) {
        MenuItem8->Destroy();
        MenuItem8 = NULL;  }*/

/*   if(MenuItem8B != NULL) {
        MenuItem8B->Destroy();
        MenuItem8B = NULL;  }*/

   /* if(MenuItem7 != NULL) {
        MenuItem7->Destroy();
        MenuItem7 = NULL;  }*/

   /* if(MenuItem5 != NULL) {
        MenuItem5->Destroy();
        MenuItem5 = NULL;  }*/

   /* if(Menu3 != NULL) {
        Menu3->Destroy();
        Menu3 = NULL;  }*/

   /* if(Menu4 != NULL) {
        Menu4->Destroy();
        Menu4 = NULL;  }*/
/*
    if(mStatusBar != NULL) {
        mStatusBar->Destroy();
        mStatusBar = NULL;
        cout << "mStatusBar Destroyed" << endl;
    }
*/
  //  SetMenu(false);
/*
    if(MenuBar1 != NULL) {
        MenuBar1->Destroy();
        MenuBar1 = NULL);
    } */
//    MenuBar1.Destroy();

/*    FFTviewerApp *parent = GetParent();
    parent->Close(); */
//    GetParent()->CloseWindow();
//    GetParent()->Destroy);
//    Destroy();
//    GetParent()->Destroy();
//   exit(-1);
//    CleanUp();
//    GetTopWindow(NULL)->CleanUp();
//    wxGetActiveWindow()->DeletePendingEvents();
//    wxGetActiveWindow()->ClearEventHashTable();
  //  GetParent()->DestroyChildren();

 //   wxGetActiveWindow()->Destroy();
//    FFTviewerFrame = NULL;
/*
    if(frmFFTMainWindow != NULL) {
        frmFFTMainWindow->Destroy();
        frmFFTMainWindow = NULL; }
*/

//MenuBar1->Destroy();

//cout << "After menubar1` Destroy" << endl;

  if(mSpectrum != NULL) {

    if(mSpectrum->m_updateTimer!=NULL) {
            if(mSpectrum->m_updateTimer->IsRunning()) {
                    mSpectrum->m_updateTimer->Stop();
                    mSpectrum->m_updateTimer->DeletePendingEvents();
                    if(CLOSE_DEBUG) cout << "m_updateTimer stoped" << endl;}
//            m_updateTimer->Delete();
//            mSpectrum->m_updateTimer = NULL;
            }

        LMAL_Quit();
        if(CLOSE_DEBUG) {
            cout<< "After LMAL_quit" << endl;
            Sleep(1000); }

        mSpectrum -> shutdown();

        if(CLOSE_DEBUG) {
            cout << "After mSpectrum -> Shutdown()" << endl;
            Sleep(1000); }

        mSpectrum->Destroy();
        if(CLOSE_DEBUG) cout << "After mSpectrum->Destroy()" <<endl;
        mSpectrum = NULL;
        if(CLOSE_DEBUG) Sleep(1000);
        Destroy();

/*
        mSpectrum->Destroy();
        cout << "After mSpectrum->Destroy()" << endl;

        mSpectrum = NULL; */
  }
  /*
cout << "Before Notebook1 Destroy " << endl;
    if(Notebook1 != NULL) {
        Notebook1->Destroy();
        Notebook1 = NULL;
        cout << "After Notebook1 Destroy" << endl; }
    Sleep(1000); */


//  Sleep(1000);

//mSpectrum = NULL;
/*
cout << "Before Destroy in fftviewermain()" << endl;
    Sleep(1000);
    Destroy();
    Sleep(1000); */
/*
cout << "After Destroy in fftviewermain" << endl;

  LMAL_Quit(); */
/*
    if(m_ControlPanel != NULL) {
        m_ControlPanel->Destroy();
        m_ControlPanel = NULL;
        cout << "After Control Panel Destroy" << endl;} */


return;
}

/**
	@brief Callback functions to receive messages from library
	@param code update code
	@param *param additional params for code
*/
void FFTviewerFrame::UpdateInterface(int code, const char* param)
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
    char sn[512], *p;
    memset(sn, 0, 512);
    LMAL_DeviceName(sn, LMAL_CurrentDevice());
    p = strrchr(sn,'-');    // "nnn-nnnnn"
    if(p) p -= 3;
    else { sprintf(sn,"UNKNOWN"); p = sn; }

	char str[176];
	sprintf(str, "Chip - ver:%i.%i.%i, Board - S/N:%s", ver, rev, mask, p);
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
	else
    {
        mStatusBar->SetStatusText("", 2);
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

void FFTviewerFrame::OnFrameDelaySelected(wxCommandEvent& event)
{
  PopList dialog(this);
  dialog.ShowModal();
}

void FFTviewerFrame::OnTuningParametersSelected(wxCommandEvent& event)
{
  PopTuning dialog(this);
  dialog.ShowModal();
}

void FFTviewerFrame::OnRSSParametersSelected(wxCommandEvent& event)
{
  PopSetupRSS dialog(this);
  dialog.ShowModal();
}

void FFTviewerFrame::OnmSpectrumPaint(wxPaintEvent& event)
{
}

/*void FFTviewerFrame::OnmTransmitterPaint(wxPaintEvent& event)
{
}
*/

bool FFTviewerFrame::SaveConfiguration()
{
    char outbuf[80];
    char newline[3];
    memset(outbuf,0,sizeof(outbuf));
#define _N  (sizeof(outbuf)-1)
    wxSprintf(newline,"\r\n");
    if(g_CfgChanged) {
            g_CfgChanged = false; //Avoid repeated writes
            if(m_CFG_FileClassPtr == NULL) m_CFG_FileClassPtr = new wxFile();
            m_CFG_FileClassPtr->Create(g_CfgFileName,TRUE,wxS_DEFAULT);
            if(!m_CFG_FileClassPtr->IsOpened()) {
                cout << "CFG File Open Fail" << endl;
                if(m_CFG_FileClassPtr != NULL) {
                    m_CFG_FileClassPtr->Close();
                    delete m_CFG_FileClassPtr;
                    m_CFG_FileClassPtr = NULL;
                }
                return(false);
            }
            wxSnprintf(outbuf,_N,"RASDRproc Version %s - NOTE: Limit to 80 column to avoid problems %s",
                       AutoVersion::FULLVERSION_STRING,"...............................................................");
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%.12f // Center Frequency (GHz)",mSpectrum->m_RxFreq);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14g // Frequency Step",mSpectrum->m_frequencyStep);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // LPF Bandwidth (index)",LMLL_RxLPFGetLpfBw());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // VGA1 Gain (index)",LMLL_RxFEGetRFB_TIA_RXFE());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // VGA2 Gain (index)",LMLL_RxVGA2GetVga2G_u());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // LNA Gain (index)",LMLL_RxFEGetG_LNA_RXFE());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // Enable Averaging (0=no, 1=yes)",mSpectrum->chkAverage->GetValue());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // Number of frames to average",mSpectrum->spinAvgCount->GetValue());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // FFT log2(Samples/Frame) (N=2^integer; 10=1024, 11=2048, etc)",mSpectrum->spinFFTsamples->GetValue());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // Sampling Frequency (MHz, integer, min=2, max=32)",mSpectrum->spinSamplingFreq->GetValue());
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // FFTOutput - Multiple Control (1=single 2=multiple suffixed)",g_NumbFFTFiles);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // FFTOutput - File Type Control (0=.csv for excel 1=General)",g_FFTFileType);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // FFTOutput - Time Standard Control (0=Local Time 1=UTC)",g_FFT_TimeStandard);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // FFTOutput - Number of Frames To Skip (integer)",g_FFTframeSkip);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // FFTOutput - Number of Frames to Write (integer)",g_FFTframesOut);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // PWROutput - Multiple Control (1=single 2=multiple suffixed)",g_NumbPWRFiles);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // PWROutput - File Type Control",g_PWRFileType);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // PWROutput - Time Standard Control (0=Local Time 1=UTC)",g_PWRTimeStandard);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // PWROutput - Recording Rate (seconds/sample)",g_PwrRecordRate);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // PWROutput - Plot Span (seconds)",g_PwrSpanSec);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // FFTOutput - Record Span (0=full range, 1=zoom/span)",g_FFTDataSource);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
 /*           m_CFG_FileClassPtr->Write(g_FFTfileName);
            m_CFG_FileClassPtr->Write(newline); */
#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
            wxSnprintf(outbuf,_N,"%-14d // Background Subtraction Code (bit encoded, try 71, bit0=en)",g_backgroundDebugCfg);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%.12f // Integration Gain",g_integrationGain);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%14.10f // DC Offset for I samples",(g_DcOffsetI == 0.0?g_avgI:g_DcOffsetI));
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%14.10f // DC Offset for Q samples",(g_DcOffsetQ == 0.0?g_avgQ:g_DcOffsetQ));
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // Unlimited Averaging (0=no, 1=yes)", g_UnlimitedAveraging);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
#endif // defined
            // RSS Integration
            wxSnprintf(outbuf,_N,"%-14s // RSS Server IP",g_RSS_IP);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14hu // RSS Server Port (default=8888)", g_RSS_Port);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // RSS Channels (range is 100 to 512 unless extensions enabled)", g_RSS_Channels);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // RSS Server Enabled (0=disabled, 1=enabled)", g_RSS_Enable?1:0);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            // RSS RASDR Extension
            wxSnprintf(outbuf,_N,"%14.10f // RSS Frequency Offset (GHz)",g_RSS_FrequencyOffset);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%-14d // RSS Extensions Enabled (0=disabled, 1=enabled)", g_RSS_Extension?1:0);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%14.10f // RSS Channel Offset Adjustment",g_RSS_Offset);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%14.10f // RSS Channel Gain Adjustment",g_RSS_Gain);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%14.10f // RSS Channel Bias Adjustment",g_RSS_Bias);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%14.9f // RSS Channel Minimum Output Value",g_RSS_MinValue);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            wxSnprintf(outbuf,_N,"%14.9f // RSS Channel Maximum Output Value",g_RSS_MaxValue);
            m_CFG_FileClassPtr->Write(outbuf);
            m_CFG_FileClassPtr->Write(newline);
            //
            m_CFG_FileClassPtr->Flush();
            m_CFG_FileClassPtr->Close();
            delete m_CFG_FileClassPtr;
            m_CFG_FileClassPtr = NULL;

            cout << "Configuration Saved" << endl;
    }
    return(true);
}

void FFTviewerFrame::OnMenuItemSaveConfigSelected(wxCommandEvent& event)
{
    SaveConfiguration();
}

//void FFTviewerFrame::OnDispTimeSelected(wxCommandEvent& event)
//{
//    DispTime->Enable(false); // Prevents multiple uses
//    PopTimeSpan dialog(this);
//    dialog.ShowModal();
//}

void FFTviewerFrame::OnSetupFFTOutSelected(wxCommandEvent& event)
{
    SetupFFTout dialog(this);
    dialog.ShowModal();
    if(g_FFTfileSetup) {
            if(mSpectrum) {
 //                   cout << "Before Stop Capturing\n" << endl;
 //                   if(mSpectrum->m_capturingData) mSpectrum->StopCapturing();
 //                   cout << "After Stop Capturing\n" << endl;
  //                  while(mSpectrum->m_capturingData); //Wait ofr stop
 //                   mSpectrum->OpenFFTfile();
                    cout << "SetupFFTout Dialog Completed OK"<<endl;
                    if(g_NumbFFTFiles == 2) mSpectrum->SuffixFFTFileName(); // sanitize the name
                    cout << g_FFTfileName << " Selected" << endl;
                    cout << "FFT File Type = " << g_FFTFileType << endl;
                    cout << "Number of FFT Files = " << g_NumbFFTFiles << endl;
                    cout << "Time Standard = " << g_FFT_TimeStandard << endl;
                    cout << "Source = " << g_FFTDataSource << endl;
                    g_FFTfileIsDefined = true;
                    mSpectrum->EnableFFTRecord(true);
            }
            g_FFTfileSetup = false;
    }
}

void FFTviewerFrame::OnSetupPWROutSelected(wxCommandEvent& event)
{
    SetupPWROut dialog(this);
    dialog.ShowModal();

cout << "OnSetupPWROutSelected" << endl;

 //   bool iscapturing = false;
    if(g_PWRfileSetup) {
            if(mSpectrum) {
 //                   cout << "Before Stop Capturing\n" << endl;
 //                   if(mSpectrum->m_capturingData)  mSpectrum->StopCapturing();
 //                   cout << "After Stop Capturing\n" << endl;
  //                  while(mSpectrum->m_capturingData); //Wait ofr stop
//                    mSpectrum->OpenPWRfile();
//                    if(iscapturing) mSpectrum->StartCapturing();
 //                   g_PWRfileSetup = true;
                    cout<<"SetupPWRout Dialog Completed OK"<<endl;
                    if(g_NumbPWRFiles == 2) mSpectrum->SuffixPWRFileName(); // sanitize the name
                    cout << g_PWRfileName << " Selected" << endl;
                    cout << "PWR File Type = " << g_PWRFileType << endl;
                    cout << "Number of PWR Files = " << g_NumbPWRFiles << endl;
                    cout << "Time Standard = " << g_PWRTimeStandard << endl;
                    g_PWRfileIsDefined = true;
                    mSpectrum->EnablePWRRecord(true);
                    }
                g_PWRfileSetup = false;
        }
}

void FFTviewerFrame::OnSetupPulsePeriodOutSelected(wxCommandEvent& event)
{
    SeupPulsePeriod dialog(this);
    dialog.ShowModal();
}

/*void FFTviewerFrame::OnSetupPulseTimeDomainOutSelected(wxCommandEvent& event)
{
    SetupPulseTimeDomain dialog(this);
    dialog.ShowModal();
}


void FFTviewerFrame::OnMenuItem12Selected(wxCommandEvent& event)
{
    SetupDMOut dialog(this);
    dialog.ShowModal();
}*/

void FFTviewerFrame::OnSetupDMOutSelected(wxCommandEvent& event)
{
    SetupDMOut dialog(this);
    dialog.ShowModal();
}

void FFTviewerFrame::OnSetup_SimSelected(wxCommandEvent& event)
{
    Setup_Simulator dialog(this);
    dialog.ShowModal();
    /*
    cout << "Sim DM = " << g_Sim_DM;
    cout << " Sim Period = " << g_Sim_Period;
    cout << " Sim Duty = " << g_Sim_Duty;
    cout << " % Sim Factor = " << g_Sim_Factor << endl;
    */
}
