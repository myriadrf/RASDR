// -----------------------------------------------------------------------------
// FILE:        "pnlSpectrum.cpp"
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
#include "pnlSpectrum.h"
#include "GUIUtils.h"
#include "ctr_6002dr2_LogicDLL.h"
#include "pnlBoard.h"
#include "..\globals.h"
#include "wx/file.h"
#include "wx/datetime.h"
#include "wx/textfile.h"
#include "wx/string.h"
//#include "wx/Coulor.h"
#define MIN_THRESH 20.0 //uW
#define MAX_THRESH 800.0 //uW
//#include <math.h>

//(*InternalHeaders(pnlSpectrum)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/spinctrl.h>
#include <wx/tglbtn.h>
#include <wx/font.h>
#include <wx/choice.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/spinbutt.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlSpectrum)
const long pnlSpectrum::ID_CHECKBOX3 = wxNewId();
const long pnlSpectrum::ID_CHECKBOX4 = wxNewId();
const long pnlSpectrum::ID_CHECKBOX5 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT9 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT10 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT11 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT16 = wxNewId();
const long pnlSpectrum::ID_PANEL1 = wxNewId();
const long pnlSpectrum::ID_GLCANVAS1 = wxNewId();
const long pnlSpectrum::ID_PANEL6 = wxNewId();
const long pnlSpectrum::ID_GLCANVAS2 = wxNewId();
const long pnlSpectrum::ID_PANEL7 = wxNewId();
const long pnlSpectrum::ID_SPLITTERWINDOW2 = wxNewId();
const long pnlSpectrum::ID_GLCANVAS3 = wxNewId();
const long pnlSpectrum::ID_BUTTON5 = wxNewId();
const long pnlSpectrum::ID_BUTTON6 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT12 = wxNewId();
const long pnlSpectrum::ID_SPINCTRL1 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT13 = wxNewId();
const long pnlSpectrum::ID_SPINCTRL2 = wxNewId();
const long pnlSpectrum::ID_BUTTON4 = wxNewId();
const long pnlSpectrum::ID_BUTTON10 = wxNewId();
const long pnlSpectrum::ID_TOGGLEBUTTON1 = wxNewId();
const long pnlSpectrum::ID_BUTTON8 = wxNewId();
const long pnlSpectrum::ID_TEXTCTRL1 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT17 = wxNewId();
const long pnlSpectrum::ID_PANEL4 = wxNewId();
const long pnlSpectrum::ID_PANEL3 = wxNewId();
const long pnlSpectrum::ID_SPLITTERWINDOW1 = wxNewId();
const long pnlSpectrum::ID_BUTTON1 = wxNewId();
const long pnlSpectrum::ID_BUTTON2 = wxNewId();
const long pnlSpectrum::ID_CHECKBOX1 = wxNewId();
const long pnlSpectrum::ID_SPINCTRL4 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT14 = wxNewId();
const long pnlSpectrum::ID_TEXTCTRL3 = wxNewId();
const long pnlSpectrum::ID_SPINBUTTON3 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT15 = wxNewId();
const long pnlSpectrum::ID_SPINCTRL3 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT5 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX4 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT6 = wxNewId();
const long pnlSpectrum::ID_TEXTCTRL2 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT7 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX5 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT8 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX6 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT1 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX7 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT3 = wxNewId();
const long pnlSpectrum::ID_BUTTON3 = wxNewId();
const long pnlSpectrum::ID_GLCANVAS4 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT2 = wxNewId();
const long pnlSpectrum::ID_SPINCTRL5 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT4 = wxNewId();
const long pnlSpectrum::ID_CHOICE1 = wxNewId();
const long pnlSpectrum::ID_PANEL5 = wxNewId();
const long pnlSpectrum::ID_PANEL10 = wxNewId();
const long pnlSpectrum::ID_PANEL2 = wxNewId();
//*)

const int pnlSpectrum::GRAPH_UPDATE_MESSAGE_ID = 100000;
//const int pnlSpectrum::FFT_FILE_OK_BTN_MESSAGE_ID = 100001;

BEGIN_EVENT_TABLE(pnlSpectrum,wxPanel)
	//(*EventTable(pnlSpectrum)
	//*)
END_EVENT_TABLE()

pnlSpectrum::pnlSpectrum(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString str) :
    m_buffersCount(1024),
    m_IchannelData(NULL), m_QchannelData(NULL), m_FFTfrequencies(NULL), m_FFTamplitudes(NULL), m_FFTbackground(NULL),
    m_FFTMaxAmplitudes(NULL), m_PWRvalues(NULL), m_FFTamplitudesBuffer(NULL),
    m_FFTFileClassPtr(NULL), m_PWRFileClassPtr(NULL), m_CFG_File(NULL)
//#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
    , m_FFTbackgroundAvg(NULL), m_FFTbackgroundDb(NULL)
//#endif BACKGROUND_DEBUG
//#if defined(CSV_DEBUG)
    , m_CSVFileClassPtr(NULL)
//#endif CSV_DEBUG

//pnlSpectrum::pnlSpectrum(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString str) : m_buffersCount(64)
{
    m_PwrIntTime = 1;
    m_PwrMax = 30;
    m_PwrMin = 20;
    m_lastUpdate = 0;
//    m_capturingData = false;
    m_updating = false;
    m_time = 0;
    m_frames = 0;
    m_PWRSpanSecChanged = false;

    m_addingMarkers = false;
	m_fftxaxisValues = NULL;
	m_MaxHold = false;
//	m_TxFreq = 2.200;
    m_CFG_File = NULL;
	m_RxFreq = 1.42;
	m_frequencyStep = 0.1; //MHz
	m_RxVGA2Sel = 1;
	m_RxVGA1Sel = 120;
	m_IchannelData = NULL;
	m_QchannelData = NULL;
	m_FFTfrequencies = NULL;
	m_FFTamplitudes = NULL;
	m_FFTMaxAmplitudes = NULL;
	m_PWRvalues = NULL;
	samplesXaxis = NULL;
	PwrcountXaxis = NULL;
	m_PwrCount = 0;
	m_Index = 0;
	m_PlottingLow = true;
	//m_PWRdataSize changed to Global variable for user changes
//	m_PWRdataSize = 60000; // Greater than 30 minutes at 32 updates/S
//	m_PWRdataSize = 38000; // Test

    BuildContent(parent,id,pos,size);
    m_FFTsamplesCount = twotoN(spinFFTsamples->GetValue());
    if(ogl_IQline) ogl_IQline->SetDisplayArea(0, m_FFTsamplesCount, -2048, 2048);
    m_samplingFrequency = 1;

    //parameters for FFT results averaging
	m_buffersCountMask = m_buffersCount;
	m_FFTamplitudesBuffer = NULL;

	allocateMemory(m_FFTsamplesCount);
    generateFFTxaxis(spinSamplingFreq->GetValue());

    m_updateTimer = new wxTimer(this, GRAPH_UPDATE_MESSAGE_ID);
    m_firststart = true;
    m_MinCurPwrIndex = 0;
// BUG: makes unterminated strings.  Globals shall be initialized in globals.cpp
//    strncpy(g_FFTfileName,"FFTOut.csv",10) ;
//    strncpy(g_PWRfileName,"PowerOut.csv",12) ;
    m_FFTFileClassPtr = NULL;
    m_FFTCounter = 0;
    m_FFTsRecorded = 0;
    char outbuf[80];
    sprintf(outbuf,"%d",m_FFTsRecorded);
    FFTsREC->SetValue(outbuf);
    m_PwrRefIsSet = false;
    m_PwrRefOffset = 0;
    m_PwrAccum = 0;
    m_PwrAveCount = 0;
    m_PwrAve = 0;
    m_PWRRecordCount = 0;
    m_PWRRecordAccum = 0;
    m_FFTChartCenter = 0;
    m_FFTChartSpan = 10000;
//    cout << "Exiting pnlSpectrum Constructor" << endl;
}

void pnlSpectrum::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlSpectrum)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(1000,600), 0, _T("wxID_ANY"));
	SetMinSize(wxSize(1000,500));
	wxFont thisFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	SetFont(thisFont);
	FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetMinSize(wxSize(800,32));
	chkUpdateGraphs = new wxCheckBox(Panel1, ID_CHECKBOX3, _("Update graphs"), wxPoint(25,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkUpdateGraphs->SetValue(true);
	chkIchannelEnabled = new wxCheckBox(Panel1, ID_CHECKBOX4, _("I channel"), wxPoint(144,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkIchannelEnabled->SetValue(true);
	chkQchannelEnabled = new wxCheckBox(Panel1, ID_CHECKBOX5, _("Q channel"), wxPoint(224,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkQchannelEnabled->SetValue(true);
	StaticText9 = new wxStaticText(Panel1, ID_STATICTEXT9, _("Data rate KB/s:"), wxPoint(320,8), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	lblDataRate = new wxStaticText(Panel1, ID_STATICTEXT10, _("0"), wxPoint(440,8), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	lblFPS = new wxStaticText(Panel1, ID_STATICTEXT11, _("30"), wxPoint(720,8), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticText14 = new wxStaticText(Panel1, ID_STATICTEXT16, _("Updates per second:"), wxPoint(550,8), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer1->Add(Panel1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
	SplitterWindow1->SetMinSize(wxSize(150,150));
	SplitterWindow1->SetMinimumPaneSize(150);
	SplitterWindow1->SetSashGravity(0.5);
	SplitterWindow2 = new wxSplitterWindow(SplitterWindow1, ID_SPLITTERWINDOW2, wxDefaultPosition, wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW2"));
	SplitterWindow2->SetMinSize(wxSize(140,140));
	SplitterWindow2->SetMinimumPaneSize(140);
	SplitterWindow2->SetSashGravity(0.5);
	Panel6 = new wxPanel(SplitterWindow2, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	int GLCanvasAttributes_1[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE,      16,
		WX_GL_STENCIL_SIZE,    0,
		0, 0 };
	ogl_IQline = new OpenGLGraph(Panel6, ID_GLCANVAS1, wxDefaultPosition, wxSize(485,120), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
	BoxSizer1->Add(ogl_IQline, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6->SetSizer(BoxSizer1);
	BoxSizer1->Fit(Panel6);
	BoxSizer1->SetSizeHints(Panel6);
	Panel7 = new wxPanel(SplitterWindow2, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	int GLCanvasAttributes_2[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE,      16,
		WX_GL_STENCIL_SIZE,    0,
		0, 0 };
	ogl_IQscatter = new OpenGLGraph(Panel7, ID_GLCANVAS2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS2"), GLCanvasAttributes_2);
	BoxSizer2->Add(ogl_IQscatter, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel7);
	BoxSizer2->SetSizeHints(Panel7);
	SplitterWindow2->SplitVertically(Panel6, Panel7);
	SplitterWindow2->SetSashPosition(300);
	Panel3 = new wxPanel(SplitterWindow1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	Panel3->SetMinSize(wxSize(100,100));
	FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	int GLCanvasAttributes_3[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE,      16,
		WX_GL_STENCIL_SIZE,    0,
		0, 0 };
	ogl_FFTline = new OpenGLGraph(Panel3, ID_GLCANVAS3, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS3"), GLCanvasAttributes_3);
	FlexGridSizer2->Add(ogl_FFTline, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(Panel3, ID_PANEL4, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	btnAddMarker = new wxButton(Panel4, ID_BUTTON5, _("Add Mkr"), wxPoint(356,0), wxSize(65,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	btnRemoveMarker = new wxButton(Panel4, ID_BUTTON6, _("Remove Mkr"), wxPoint(424,0), wxSize(115,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	StaticText10 = new wxStaticText(Panel4, ID_STATICTEXT12, _("Zoom Center (KHz)"), wxPoint(0,4), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	spinCenterFreq = new wxSpinCtrl(Panel4, ID_SPINCTRL1, _T("0"), wxPoint(124,0), wxSize(72,21), 0, -32000, 32000, 0, _T("ID_SPINCTRL1"));
	spinCenterFreq->SetValue(_T("0"));
	StaticText11 = new wxStaticText(Panel4, ID_STATICTEXT13, _("Span (KHz)"), wxPoint(199,4), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	spinSpanFreq = new wxSpinCtrl(Panel4, ID_SPINCTRL2, _T("10000"), wxPoint(275,0), wxSize(88,21), 0, 1, 32000, 10000, _T("ID_SPINCTRL2"));
	spinSpanFreq->SetValue(_T("10000"));
	FFTRec_btn = new wxButton(Panel4, ID_BUTTON4, _("Record FFT"), wxPoint(540,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FFTRec_btn->Disable();
	 RecordPWR = new wxButton(Panel4, ID_BUTTON10, _("Record PWR"), wxPoint(850,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	 RecordPWR->Disable();
	wxFont  RecordPWRFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	 RecordPWR->SetFont( RecordPWRFont);
	PwrRef = new wxToggleButton(Panel4, ID_TOGGLEBUTTON1, _("SetPwrRef"), wxPoint(752,0), wxSize(95,25), 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
	PwrRef->Disable();
	MaxHold = new wxButton(Panel4, ID_BUTTON8, _("MaxHoldFFT"), wxPoint(955,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	wxFont MaxHoldFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	MaxHold->SetFont(MaxHoldFont);
	FFTsREC = new wxTextCtrl(Panel4, ID_TEXTCTRL1, _("0"), wxPoint(635,2), wxSize(40,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText15 = new wxStaticText(Panel4, ID_STATICTEXT17, _("FFTs REC "), wxPoint(680,3), wxDefaultSize, wxALIGN_LEFT, _T("ID_STATICTEXT17"));
	wxFont StaticText15Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText15->SetFont(StaticText15Font);
	FlexGridSizer2->Add(Panel4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel3);
	FlexGridSizer2->SetSizeHints(Panel3);
	SplitterWindow1->SplitHorizontally(SplitterWindow2, Panel3);
	FlexGridSizer1->Add(SplitterWindow1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(500,10), wxSize(1000,178), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel9 = new wxPanel(Panel2, ID_PANEL10, wxPoint(8,8), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
	FlexGridSizer7 = new wxFlexGridSizer(1, 4, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(7, 1, 0, 0);
	btnStartCapture = new wxButton(Panel9, ID_BUTTON1, _("Start capturing samples"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer8->Add(btnStartCapture, 0, wxTOP|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnStopCapture = new wxButton(Panel9, ID_BUTTON2, _("Stop capturing samples"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer8->Add(btnStopCapture, 1, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
	chkAverage = new wxCheckBox(Panel9, ID_CHECKBOX1, _("Ave Ovr Frames:"), wxDefaultPosition, wxSize(133,24), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkAverage->SetValue(false);
	FlexGridSizer12->Add(chkAverage, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	spinAvgCount = new wxSpinCtrl(Panel9, ID_SPINCTRL4, _T("4"), wxDefaultPosition, wxSize(63,21), 0, 1, 1000000, 4, _T("ID_SPINCTRL4"));
	spinAvgCount->SetValue(_T("4"));
	FlexGridSizer12->Add(spinAvgCount, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText12 = new wxStaticText(Panel9, ID_STATICTEXT14, _("Samps/Frame:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer8->Add(StaticText12, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	// TODO: coordinate with pnlSpectrum.cpp, Packets.h, TestingModule.h/.cpp, globals.cpp and pnlSpectrum.wxs
	txtFFTsamples = new wxTextCtrl(Panel9, ID_TEXTCTRL3, _("16384"), wxDefaultPosition, wxSize(56,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	txtFFTsamples->Disable();
	FlexGridSizer9->Add(txtFFTsamples, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	spinFFTsamples = new wxSpinButton(Panel9, ID_SPINBUTTON3, wxDefaultPosition, wxSize(17,22), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON3"));
	spinFFTsamples->SetValue(14);
	spinFFTsamples->SetRange(4, 14);
	FlexGridSizer9->Add(spinFFTsamples, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer8->Add(FlexGridSizer9, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(Panel9, ID_STATICTEXT15, _("Samp Rate (MS/S):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer8->Add(StaticText13, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	spinSamplingFreq = new wxSpinCtrl(Panel9, ID_SPINCTRL3, _T("10"), wxDefaultPosition, wxDefaultSize, 0, 1, 32, 10, _T("ID_SPINCTRL3"));
	spinSamplingFreq->SetValue(_T("10"));
	FlexGridSizer8->Add(spinSamplingFreq, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 4);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel9, wxEmptyString);
	FlexGridSizer5 = new wxFlexGridSizer(3, 2, 0, 0);
	StaticText5 = new wxStaticText(Panel9, ID_STATICTEXT5, _("Bw (MHz):"), wxDefaultPosition, wxSize(91,16), 0, _T("ID_STATICTEXT5"));
	FlexGridSizer5->Add(StaticText5, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRxFilter = new wxComboBox(Panel9, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(75,24), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	cmbRxFilter->Append(_("28"));
	cmbRxFilter->Append(_("20"));
	cmbRxFilter->Append(_("14"));
	cmbRxFilter->Append(_("12"));
	cmbRxFilter->SetSelection( cmbRxFilter->Append(_("10")) );
	cmbRxFilter->Append(_("8.75"));
	cmbRxFilter->Append(_("7"));
	cmbRxFilter->Append(_("6"));
	cmbRxFilter->Append(_("5.5"));
	cmbRxFilter->Append(_("5"));
	cmbRxFilter->Append(_("3.84"));
	cmbRxFilter->Append(_("3"));
	cmbRxFilter->Append(_("2.75"));
	cmbRxFilter->Append(_("2.5"));
	cmbRxFilter->Append(_("1.75"));
	cmbRxFilter->Append(_("1.5"));
	FlexGridSizer5->Add(cmbRxFilter, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText6 = new wxStaticText(Panel9, ID_STATICTEXT6, _("RF Ctr Freq (MHz)"), wxDefaultPosition, wxSize(-1,19), 0, _T("ID_STATICTEXT6"));
	FlexGridSizer5->Add(StaticText6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	txtRxFrequencyMHz = new wxTextCtrl(Panel9, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(75,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer6->Add(txtRxFrequencyMHz, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(Panel9, ID_STATICTEXT7, _("VGA1 Gain(dB):"), wxDefaultPosition, wxSize(-1,13), 0, _T("ID_STATICTEXT7"));
	FlexGridSizer5->Add(StaticText7, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRxFEVGA1 = new wxComboBox(Panel9, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(85,24), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer5->Add(cmbRxFEVGA1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(Panel9, ID_STATICTEXT8, _("VGA2 Gain(dB):"), wxDefaultPosition, wxSize(101,16), 0, _T("ID_STATICTEXT8"));
	FlexGridSizer5->Add(StaticText8, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRxVGA2 = new wxComboBox(Panel9, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(91,24), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	FlexGridSizer5->Add(cmbRxVGA2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(Panel9, ID_STATICTEXT1, _("LNA Gain Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbLNAGainMode = new wxComboBox(Panel9, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	cmbLNAGainMode->Append(_("Bypass"));
	cmbLNAGainMode->SetSelection( cmbLNAGainMode->Append(_("-6 dB")) );
	cmbLNAGainMode->Append(_("Max gain"));
	FlexGridSizer5->Add(cmbLNAGainMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel9, ID_STATICTEXT3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer5->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Apply_btn = new wxButton(Panel9, ID_BUTTON3, _("APPLY"), wxDefaultPosition, wxSize(88,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	Apply_btn->Disable();
	FlexGridSizer5->Add(Apply_btn, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 1);
	FlexGridSizer7->Add(StaticBoxSizer2, 1, wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(1, 2, 0, 0);
	int GLCanvasAttributes_4[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE,      16,
		WX_GL_STENCIL_SIZE,    0,
		0, 0 };
	oglPWRChart = new OpenGLGraph(Panel9, ID_GLCANVAS4, wxPoint(-1,-1), wxDefaultSize, wxSIMPLE_BORDER, _T("ID_GLCANVAS4"), GLCanvasAttributes_4);
	oglPWRChart->SetMinSize(wxSize(400,150));
	wxFont oglPWRChartFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	oglPWRChart->SetFont(oglPWRChartFont);
	FlexGridSizer3->Add(oglPWRChart, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Panel5 = new wxPanel(Panel9, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	StaticText2 = new wxStaticText(Panel5, ID_STATICTEXT2, _("Pwr Span (1 to 1440 Min)"), wxDefaultPosition, wxSize(156,17), 0, _T("ID_STATICTEXT2"));
	BoxSizer3->Add(StaticText2, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	PwrSpan = new wxSpinCtrl(Panel5, ID_SPINCTRL5, _T("15"), wxDefaultPosition, wxDefaultSize, 0, 1, 1440, 15, _T("ID_SPINCTRL5"));
	PwrSpan->SetValue(_T("15"));
	BoxSizer3->Add(PwrSpan, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText4 = new wxStaticText(Panel5, ID_STATICTEXT4, _("Integration Time (S)"), wxDefaultPosition, wxSize(126,18), 0, _T("ID_STATICTEXT4"));
	BoxSizer3->Add(StaticText4, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Integration_Time = new wxChoice(Panel5, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Integration_Time->SetSelection( Integration_Time->Append(_("1")) );
	Integration_Time->Append(_("5"));
	Integration_Time->Append(_("10"));
	BoxSizer3->Add(Integration_Time, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Panel5->SetSizer(BoxSizer3);
	BoxSizer3->Fit(Panel5);
	BoxSizer3->SetSizeHints(Panel5);
	FlexGridSizer3->Add(Panel5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel9->SetSizer(FlexGridSizer7);
	FlexGridSizer7->Fit(Panel9);
	FlexGridSizer7->SetSizeHints(Panel9);
	FlexGridSizer1->Add(Panel2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnchkIchannelEnabledClick1);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnchkQchannelEnabledClick1);
	ogl_FFTline->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&pnlSpectrum::Onogl_FFTlineLeftDown,0,this);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnAddMarkerClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnRemoveMarkerClick);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlSpectrum::OnspinCenterFreqChange);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlSpectrum::OnspinSpanFreqChange);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnRecordFFTClick);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnPwrRecordClick);
	Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnPwrRefClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnMaxHoldClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnStartCaptureClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnStopCaptureClick);
	Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlSpectrum::OnspinAvgCountChange);
	Connect(ID_SPINBUTTON3,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&pnlSpectrum::OnspinFFTsamplesChange);
	Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlSpectrum::OnspinSamplingFreqChange1);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbRxFilterSelected);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&pnlSpectrum::OntxtRxFrequencyMHzText);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlSpectrum::OntxtRxFrequencyMHzText);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbRxFEVGA1Selected);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbRxVGA2Selected);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbLNAGainModeSelected);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnApply_btnClick);
	Connect(ID_SPINCTRL5,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlSpectrum::OnPwrSpanChange);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OnIntegration_TimeSelect);
	//*)
	//Additional events
	Connect(ID_SPINCTRL3,wxEVT_TEXT,(wxObjectEventFunction)&pnlSpectrum::OnspinSamplingFreqChange);
    Connect(GRAPH_UPDATE_MESSAGE_ID,wxEVT_TIMER,(wxObjectEventFunction)&pnlSpectrum::UpdateGraphs);

//	Connect(wxID_YES,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnFFTfileYESbtnClick);
	Initialize();
//	cout << "Exiting Buildcontent" <<endl;
}

pnlSpectrum::~pnlSpectrum()
{
    if(CLOSE_DEBUG) cout << "Entering ~pnlSpectrum()" << endl;
#ifdef CSV_DEBUG
    if(m_CSVFileClassPtr != NULL) {
        m_CSVFileClassPtr->Close();
        delete m_CSVFileClassPtr;
        m_CSVFileClassPtr = NULL;
    }
#endif
    if(m_FFTFileClassPtr != NULL) {
        m_FFTFileClassPtr->Close();
        delete m_FFTFileClassPtr;
        m_FFTFileClassPtr = NULL;
    }
    if(m_PWRFileClassPtr != NULL) {
        m_PWRFileClassPtr->Close();
        delete m_PWRFileClassPtr;
        m_PWRFileClassPtr = NULL;
    }
    if(m_CFG_File != NULL ) {
        m_CFG_File->Close();
        delete m_CFG_File;
        m_CFG_File = NULL;
    }
    if(CLOSE_DEBUG) cout << "Exiting ~pnlSpectrum()" << endl;
}

void pnlSpectrum::shutdown()
{
    if(CLOSE_DEBUG) cout << "Entering pnlSpectrum::shutdown()" << endl << flush;
    m_updating = false; // Added 1/7/14
    Disconnect(GRAPH_UPDATE_MESSAGE_ID,wxEVT_TIMER,(wxObjectEventFunction)&pnlSpectrum::UpdateGraphs);

	Disconnect(ID_SPINCTRL3,wxEVT_TEXT,(wxObjectEventFunction)&pnlSpectrum::OnspinSamplingFreqChange);

    chkUpdateGraphs->SetValue(false);
    chkIchannelEnabled->SetValue(false);
    chkQchannelEnabled->SetValue(false);

    if(m_updateTimer!=NULL) {
            if(m_updateTimer->IsRunning()) {
                    m_updateTimer->Stop();
                    m_updateTimer->DeletePendingEvents();}
//            m_updateTimer->Delete();
            m_updateTimer = NULL; }

    if(CLOSE_DEBUG) cout << "After m_updateTimer stop" << endl;

//    wxFlushEvents();
//    wxYield();  //Wait for timeeer to stop by uielding to other work.

    ogl_FFTline->Disconnect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&pnlSpectrum::Onogl_FFTlineLeftDown,0,this);
	Disconnect(ID_SPINCTRL3,wxEVT_TEXT,(wxObjectEventFunction)&pnlSpectrum::OnspinSamplingFreqChange);
    Disconnect(GRAPH_UPDATE_MESSAGE_ID,wxEVT_TIMER,(wxObjectEventFunction)&pnlSpectrum::UpdateGraphs);

    if(CLOSE_DEBUG) cout << "After Disconnect Events" << endl;

	//free all used memory
    freeMemory();

    if(CLOSE_DEBUG) {
        cout << "After freeMemory()" << endl;
            Sleep(g_closedelay);}

	if( m_fftxaxisValues) {
		delete []m_fftxaxisValues;
//    Destroy();

    if(CLOSE_DEBUG) {
            cout << "After delete fftxAxisValues" << endl;
            Sleep(g_closedelay);}
	}
    if( samplesXaxis) {
		delete []samplesXaxis;
//    Destroy();

    if(CLOSE_DEBUG) {
            cout << "After delete samplesXAxis" << endl;
            Sleep(g_closedelay);}
	}

if(ogl_FFTline != NULL) {
    ogl_FFTline -> Destroy();
    ogl_FFTline = NULL;

    if(CLOSE_DEBUG) {
            Sleep(g_closedelay);
            cout << "After FFT deleted" << endl;}
}
if(ogl_IQline != NULL) {
    ogl_IQline -> Destroy();
    ogl_IQline = NULL;


    if(CLOSE_DEBUG) {
            cout << "After IQ Line deleted" << endl;
            Sleep(g_closedelay);}
}
if(ogl_IQscatter != NULL) {
    ogl_IQscatter -> Destroy();
    ogl_IQscatter = NULL;

    if(CLOSE_DEBUG) {
            cout << "After IQ Scatter deleted" << endl;
            Sleep(g_closedelay); }
}

/*
if(Panel1 != NULL) {
    Panel1->Destroy();
    Panel1 = NULL;
    if(CLOSE_DEBUG) {
            cout << "Panel1 destroyed" << endl;
            Sleep(g_closedelay);}
}

if(Panel6 != NULL) {
    Panel6->Destroy();
    Panel6 = NULL;
    if(CLOSE_DEBUG) {
        cout << "Panel6 destroyed" << endl;
        Sleep(g_closedelay);}
}

if(Panel4 != NULL) {
    Panel4->Destroy();
    Panel4 = NULL;
    if(CLOSE_DEBUG) {
        cout << "Panel4 destroyed" << endl;
        Sleep(g_closedelay);}
}

if(Panel3 != NULL) {
    Panel3->Destroy();
    Panel3 = NULL;
    if(CLOSE_DEBUG) {
        cout << "Panel3 destroyed" << endl;
        Sleep(g_closedelay);}
}

if(Panel7 != NULL) {
    Panel7->Destroy();
    Panel7 = NULL;
    if(CLOSE_DEBUG) {
        cout << "Panel7 destroyed" << endl;
        Sleep(g_closedelay); }
}
*/
/*
if(lblDataRate !=NULL) {
    lblDataRate->Destroy();
    lblDataRate = NULL;
    cout << "lblDataRate Destroyed" << endl;
}
*/
/*
if(lblFPS!=NULL) {
    lblFPS->Destroy();
    lblFPS = NULL;
    cout << "lblFPS Destroyed" << endl;
}
*/
/*if(Panel8 != NULL) {
    cout << "Before Panel8 Destroy" <<endl;
    Panel8->Destroy();
    Panel8 = NULL;
    cout << "Panel8 destroyed" << endl;
    Sleep(g_closedelay);
}
if(Panel5 != NULL) {
    cout << "Before Panel5 Destroy" <<endl;
    Panel5->Destroy();
    Panel5 = NULL;
    cout << "Panel5 destroyed" << endl;
    Sleep(g_closedelay);
}
if(Panel2 != NULL) {
    if(CLOSE_DEBUG) cout << "Before Panel2 Destroy" <<endl;
    Panel2->Destroy();
    Panel2 = NULL;
    if(CLOSE_DEBUG) {
        cout << "Panel2 destroyed" << endl;
        Sleep(g_closedelay); }
}
*/
/*
if(SplitterWindow2 != NULL) {
    SplitterWindow2->Destroy();
    SplitterWindow2 = NULL;
    if(CLOSE_DEBUG) {
        cout << "SplitterWindow2 destroyed" << endl;
        Sleep(g_closedelay);}
}

if(SplitterWindow1 != NULL) {
    SplitterWindow1->Destroy();
    SplitterWindow1 = NULL;
    if(CLOSE_DEBUG) {
        cout << "SplitterWindow1 destroyed" << endl;
        Sleep(g_closedelay); }
} */
/*
    LMAL_Quit();

    return;
*/


//	Destroy();

    if(CLOSE_DEBUG) cout << "Exiting pnlSpectrum::shutdown()" << endl << flush;
	return;
}
int pnlSpectrum::twotoN(int N)
{
    int i;
    int val = 1;
    if(N < 0) return -1; // Fail
    if(N==0) return 1;
    for(i = 1; i < N+1; i++) val = val * 2;
    return val;
}

/**
    @brief Initializes panel graphs
*/
void pnlSpectrum::initializeGraphs()
{
    if(ogl_IQline)
	{
	    ogl_IQline->settings.useVBO = true;
        ogl_IQline->AddSeries();
        ogl_IQline->AddSeries();
        ogl_IQline->SetInitialDisplayArea(0, g_MaxFFTbins, -2048, 2048);
        ogl_IQline->settings.marginLeft = 80;
        ogl_IQline->settings.marginBottom = 35;
        ogl_IQline->settings.title = "IQ samples";
        ogl_IQline->series[0]->color = 0xFF0000FF;
        ogl_IQline->series[1]->color = 0x0000FFFF;
	}
	if(ogl_IQscatter)
    {
        ogl_IQscatter->settings.useVBO = true;
        ogl_IQscatter->AddSeries();
        ogl_IQscatter->SetInitialDisplayArea(-2048, 2048, -2048, 2048);
        ogl_IQscatter->SetDrawingMode(GLG_POINTS);
        ogl_IQscatter->settings.title = "I versus Q";
        ogl_IQscatter->settings.titleXaxis = "I";
        ogl_IQscatter->settings.titleYaxis = "Q";
        ogl_IQscatter->settings.gridXlines = 8;
        ogl_IQscatter->settings.gridYlines = 8;
        ogl_IQscatter->settings.marginLeft = 64;
        ogl_IQscatter->settings.marginBottom = 35;
    }
	if(oglPWRChart)
    {
        oglPWRChart->settings.useVBO = true;
        oglPWRChart->AddSeries();
        oglPWRChart->series[0]->color = 0xFF0000FF; //Red initially
        oglPWRChart->SetInitialDisplayArea(0, 3600, 1, 100);
        oglPWRChart->SetDrawingMode(GLG_LINE);
        oglPWRChart->settings.title = "Integrated ADC Power";
        oglPWRChart->settings.titleXaxis = "";
        oglPWRChart->settings.titleYaxis = "";
        oglPWRChart->settings.gridXlines = 10;
        oglPWRChart->settings.gridYlines = 10;
        oglPWRChart->settings.marginLeft = 50;
        oglPWRChart->settings.marginRight = 0;
        oglPWRChart->settings.marginBottom = 20;
        oglPWRChart->settings.xUnits = " S";
        oglPWRChart->settings.yUnits = " uW";
  //      oglPWRChart->ZoomX(g_DisplayFrames/2,g_DisplayFrames); //Initial Span
    }
    if(ogl_FFTline)
    {
        ogl_FFTline->settings.useVBO = true;
        ogl_FFTline->AddSeries();
#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
        ogl_FFTline->AddSeries();   // for background
#endif
        ogl_FFTline->SetDrawingMode(GLG_LINE);
        ogl_FFTline->settings.gridXlines = 4;
        ogl_FFTline->SetInitialDisplayArea(-16.0, 16.0, -70, 70);

        ogl_FFTline->settings.title = "FFT";
        ogl_FFTline->settings.marginLeft = 75;
        ogl_FFTline->settings.marginBottom = 35;
        ogl_FFTline->settings.titleXaxis = "Center Offset Frequency";
        ogl_FFTline->settings.titleYaxis = "Amplitude";
        ogl_FFTline->settings.xUnits = " MHz";
        ogl_FFTline->settings.yUnits = " dB";
        ogl_FFTline->markersEnabled = true;
    }
}

/**
	@brief Allocates memory for FFT samples and FFT data
	@param samples number of FFT samples
*/
void pnlSpectrum::allocateMemory(unsigned int samples)
{
	m_IQdataSize = samples;
	m_FFTdataSize = samples-1;
	if(m_IchannelData)
		delete []m_IchannelData;
	m_IchannelData = new float[samples];

	if(m_QchannelData)
		delete []m_QchannelData;
	m_QchannelData = new float[samples];

	if(m_FFTfrequencies)
		delete []m_FFTfrequencies;
	m_FFTfrequencies = new float[samples];

	if(m_FFTamplitudes)
		delete []m_FFTamplitudes;
	m_FFTamplitudes = new float[samples];

	if(m_FFTbackground)
		delete []m_FFTbackground;
	m_FFTbackground = new float[samples];
	for(int i;i<samples;i++) m_FFTbackground[i] = 0.0;

#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
	if(m_FFTbackgroundAvg)
		delete []m_FFTbackgroundAvg;
	m_FFTbackgroundAvg = new float[samples];
	for(int i;i<samples;i++) m_FFTbackgroundAvg[i] = 0.0;

	if(m_FFTbackgroundDb)
		delete []m_FFTbackgroundDb;
	m_FFTbackgroundDb = new float[samples];
	for(int i;i<samples;i++) m_FFTbackgroundDb[i] = -370.0;
#endif  // BACKGROUDND_DEBUG

	if(m_FFTMaxAmplitudes)
		delete []m_FFTMaxAmplitudes;
	m_FFTMaxAmplitudes = new float[samples];

	if(m_PWRvalues)
        delete []m_PWRvalues;
    m_PWRvalues = new float[g_MaxPwrSpanSec];
 //   m_PWRvalues = new float[g_MaxDispFrames];

    // Initialize data to negative value
    for(int i = 0; i < g_MaxPwrSpanSec; i++) m_PWRvalues[i] = -1;
//    for(int i = 0; i < g_MaxDispFrames; i++) m_PWRvalues[i] = 0;

	m_FFTamplitudesBuffer = new float*[m_buffersCount+1];
	for(int i=0; i<m_buffersCount+1; i++)
		m_FFTamplitudesBuffer[i] = new float[m_FFTsamplesCount];
	bufferPos = 0;
	m_YCent = new float[7];
	m_YCent[0] = 2.5;
	m_YCent[1] = 5;
	m_YCent[2] = 7.5;
	m_YCent[3] = 15;
	m_YCent[4] = 37.5;
	m_YCent[5] = 75;
	m_YCent[6] = 150;
	m_YSPan = new float[7];
	m_YSPan[0] = 5;
	m_YSPan[1] = 10;
	m_YSPan[2] = 15;
	m_YSPan[3] = 30;
	m_YSPan[4] = 75;
	m_YSPan[5] = 150;
	m_YSPan[6] = 300;
	m_curYstep = 6;
	//Set spansec to saved configuration
	PwrSpan->SetValue(g_PwrSpanSec/60);
}

/**
	@brief Deallocates memory used for FFT samples and data
*/
void pnlSpectrum::freeMemory()
{
	m_IQdataSize = 0;
	m_FFTdataSize = 0;
	if(m_IchannelData)
		delete []m_IchannelData;
    m_IchannelData = NULL;

	if(m_QchannelData)
		delete []m_QchannelData;
    m_QchannelData = NULL;

	if(m_FFTfrequencies)
		delete []m_FFTfrequencies;
    m_FFTfrequencies = NULL;

	if(m_FFTamplitudes)
		delete []m_FFTamplitudes;
    m_FFTamplitudes = NULL;

	if(m_FFTbackground)
		delete []m_FFTbackground;
	m_FFTbackground = NULL;

#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
	if(m_FFTbackgroundAvg)
		delete []m_FFTbackgroundAvg;
	m_FFTbackgroundAvg = NULL;

	if(m_FFTbackgroundDb)
		delete []m_FFTbackgroundDb;
	m_FFTbackgroundDb = NULL;
#endif

	if(m_FFTMaxAmplitudes)
		delete []m_FFTMaxAmplitudes;
    m_FFTMaxAmplitudes = NULL;

    if(m_PWRvalues)
		delete []m_PWRvalues;
    m_PWRvalues = NULL;

    if(m_FFTamplitudesBuffer)
    {
        for(int i=0; i<m_buffersCount; ++i)
            delete []m_FFTamplitudesBuffer[i];
// BUG: already deleted aove
//        delete []m_FFTamplitudes;
//        delete []m_FFTMaxAmplitudes;
    }
    m_FFTamplitudesBuffer = NULL;
}

/**
	@brief Initializes GUI elements
*/
void pnlSpectrum::GetConfiguration()
{
    int line = 0;
    char inbuf[80];
    if(m_CFG_File == NULL)
    {
        m_CFG_File = new wxTextFile();
        if(m_CFG_File->Open(g_CfgFileName))
        {
            cout << m_CFG_File->GetFirstLine() << " Config file First Line" << endl;
            while(!m_CFG_File->Eof())
            {
                line++;
                memset(inbuf,0,sizeof(inbuf));
                strncpy(inbuf,m_CFG_File->GetNextLine(),sizeof(inbuf)-1);
//                if(m_CFG_File->Eof()) break;
                cout << inbuf << endl;
                if(line == 1)  m_RxFreq = atof(inbuf);
                if(line == 2)  m_frequencyStep = atof(inbuf);
                if(line == 3) cmbRxFilter->SetSelection( atoi(inbuf));
                if(line == 4) m_RxVGA1Sel = atoi(inbuf);
                if(line == 5) m_RxVGA2Sel = atoi(inbuf);
                if(line == 6) cmbLNAGainMode->SetSelection(atoi(inbuf));
                if(line == 7) chkAverage->SetValue(atoi(inbuf));
                if(line == 8) spinAvgCount->SetValue(atoi(inbuf));
                if(line == 9) {
                    m_FFTsamplesCount = twotoN(atoi(inbuf));
                    spinFFTsamples->SetValue(atoi(inbuf));
                    txtFFTsamples->SetValue(wxString::Format("%i",m_FFTsamplesCount));}
                if(line == 10) {spinSamplingFreq->SetValue(atoi(inbuf));
                                changeSamplingFrequency(atoi(inbuf)); }
 //                               m_samplingFrequency = atoi(inbuf);
  //                              generateFFTxaxis((unsigned long)m_samplingFrequency);
  //                              allocateMemory(m_FFTsamplesCount);
  //                              generateFFTxaxis(m_samplingFrequency);}
                if(line == 11) g_NumbFFTFiles = atoi(inbuf);
                if(line == 12) g_FFTFileType = atoi(inbuf);
                if(line == 13) g_FFT_TimeStandard = atoi(inbuf);
                if(line == 14) g_FFTframeSkip = atoi(inbuf);
                if(line == 15) g_FFTframesOut = atoi(inbuf);
                if(line == 16) g_NumbPWRFiles = atoi(inbuf);
                if(line == 17) g_PWRFileType = atoi(inbuf);
                if(line == 18) g_PWRTimeStandard = atoi(inbuf);
                if(line == 19) g_PwrRecordRate = atoi(inbuf);
                if(line == 20) g_PwrSpanSec = atoi(inbuf);
                if(line == 21) g_FFTDataSource = atoi(inbuf);
 //               if(line == 22) strncpy(g_FFTfileName,inbuf,1023);
#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
                if(line == 22) g_backgroundDebugCfg = atoi(inbuf);
                if(line == 23) g_integrationGain = atof(inbuf);
                if(line == 24) g_DcOffsetI = atof(inbuf);
                if(line == 25) g_DcOffsetQ = atof(inbuf);
                if(line == 26) g_UnlimitedAveraging = atoi(inbuf);
#endif
            }
            m_CFG_File->Close();
        } else {
            // BUG: a non-existent configuration file would crash RASDRviewer 1.2.2.1
            cout << " Configuration File doesn't Exist; using internal defaults..." << endl;
            cout << m_RxFreq << endl;           // if(line == 1)
            cout << m_frequencyStep << endl;    // if(line == 2)
            cout << 15 << endl;                 // if(line == 3)
                cmbRxFilter->SetSelection( 15 );
            cout << m_RxVGA1Sel << endl;        // if(line == 4)
            cout << m_RxVGA2Sel << endl;        // if(line == 5)
            cout << 2 << endl;                  // if(line == 6)
                cmbLNAGainMode->SetSelection( 2 );
            cout << 1 << endl;                  // if(line == 7)
                chkAverage->SetValue( 1 );
            cout << 1 << endl;                  // if(line == 8)
                spinAvgCount->SetValue( 1 );
            cout << 11 << endl;                 // if(line == 9)
                m_FFTsamplesCount = twotoN(11);
                spinFFTsamples->SetValue( 11 );
                txtFFTsamples->SetValue(wxString::Format("%i",m_FFTsamplesCount));
            cout << 2 << endl;                  // if(line == 10)
                spinSamplingFreq->SetValue( 2 );
                changeSamplingFrequency(2);
            cout << g_NumbFFTFiles << endl;     // if(line == 11)
            cout << g_FFTFileType << endl;      // if(line == 12)
            cout << g_FFT_TimeStandard << endl; // if(line == 13)
            cout << g_FFTframeSkip << endl;     // if(line == 14)
            cout << g_FFTframesOut << endl;     // if(line == 15)
            cout << g_NumbPWRFiles << endl;     // if(line == 16)
            cout << g_PWRFileType << endl;      // if(line == 17)
            cout << g_PWRTimeStandard << endl;  // if(line == 18)
            cout << g_PwrRecordRate << endl;    // if(line == 19)
            cout << g_PwrSpanSec << endl;       // if(line == 20)
            cout << g_FFTDataSource << endl;    // if(line == 21)
#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
            cout << g_backgroundDebugCfg << endl;// if(line == 22)
            cout << g_integrationGain << endl;// if(line == 23)
            cout << g_DcOffsetI << endl;// if(line == 24)
            cout << g_DcOffsetQ << endl;// if(line == 25)
            cout << g_UnlimitedAveraging << endl;// if(line == 26)
#endif
        }
        delete m_CFG_File;
        m_CFG_File = NULL;
    }
//cout<<"Exiting Get Configuration()" << endl;
}
void pnlSpectrum::Initialize()
{
    GetConfiguration();
    initializeInterfaceValues();
 //   cout << "After InitializeInterfaeValues()" << endl;
	char ctemp[80];
//	sprintf(ctemp, "%2.3f", m_TxFreq);
//	txtTxFrequencyGHz->SetValue(ctemp);
	sprintf(ctemp, "%.6f", m_RxFreq * 1000);
	txtRxFrequencyMHz->SetValue(ctemp);

	m_buffersCountMask = spinAvgCount->GetValue();

	initializeGraphs();
//	cout << "After InitializeGraphs()" << endl;
	if( LMAL_IsOpen() )
	{
		btnStartCapture->Enable(true);
		onChipConnect();
	}
	else
    {
        btnStartCapture->Enable(false);
        btnStopCapture->Enable(false);
    }
//    cout << "Exiting Initialize()" << endl;
}

void pnlSpectrum::OnApply_btnClick(wxCommandEvent& event)
{
    BOOL running;
    //Disable Data Collection for changes
    if(g_capturingData) {
            running = true;
            StopCapturing();}
    else running = false;
    double freq;
    //Set RX frequency
    txtRxFrequencyMHz->GetValue().ToDouble(&freq);
    if(m_RxFreq != freq / 1000) {
            g_CfgChanged = true;
            m_RxFreq = freq / 1000;
    }
	if( m_RxFreq > 0.2 && m_RxFreq < 5)
		LMAL_RxPLL_SetFrequency(m_RxFreq);
	else
	{
		m_RxFreq = 0.3;
//		txtRxFrequencyMHz->SetValue( "300");
		txtRxFrequencyMHz->SetValue( wxString::Format("%i", 300));
	}

	// Set the Reference Frequency in the ADF Chip

	// ADF Reference Counter Latch Default Values
	int ldp = 3;
	int abw = 2.9;
	int rcount = 125;
	LMLL_ADF_SetReferenceCounterLatch(ldp,abw,rcount);
	// ADF n counter latch Defaults
	int cpGain = 0;
	int nCounter = 384;
	LMLL_ADF_SetNCounterLatch(cpGain,nCounter);
	// ADF function Latch
	int currsetting1 = 7;
	int currsetting2 = 7;
	int tcounter = 3;
	int fastlock = 0; // Disabled
	int muxcontrol = 1; // Digital Lock
	int pdpol = 1; // Positive
	int pd1 = 0;
	int pd2 = 0;
	int counterReset = 0; // Normal
	int cpState = 0; // Normal
	LMLL_ADF_SetFunctionLatch(currsetting1,currsetting2,tcounter,fastlock,muxcontrol);
	LMLL_ADF_SetFunctionLatchRgr(pdpol,pd1,pd2,counterReset,cpState);
	// Initialization Latch
    LMLL_ADF_SetInitializationLatch(currsetting1,currsetting2,tcounter,fastlock,muxcontrol);
    LMLL_ADF_SetInitializationLatchRgr(pdpol,pd1,pd2,counterReset,cpState);
    // ADF default frequencies
    double fref = 10; // 10 MHz referencey input
    double fvco = 30.72; // VCO frequency
    LMLL_ADF_SetFrefFvco(fref,fvco,rcount,nCounter);
    // Send ADF
    LMLL_ADF_SendConfig();

	//set the sampling rate
	double samprate = (double)(1e6*spinSamplingFreq->GetValue());
	double clockrate = samprate * 2 / 1e6;
	//cout << samprate << endl;
	//cout << clockrate << endl;

    LMLL_BoardSetFrequency(2,30.72,clockrate);	// ADC Clock 2,30.72 MHz reference input
    LMLL_BoardSetClockInversion(2,0); // Clock2 No Inversion
    LMLL_BoardSetClockOutputFormat(2,3); // Clock 2 Both on
    LMLL_BoardConfigureSi5356A(); // Boots Chip to activate Values

	if(spinSpanFreq->GetValue()/1e3>samprate/1e6)spinSpanFreq->SetValue(samprate/1e3);	// Match the Span to the Sample rate
//	ogl_FFTline->ZoomX(spinCenterFreq->GetValue(),samprate);
//    ogl_FFTline->SetDisplayArea(-samprate/2,samprate/2,-70,70);
    ogl_FFTline->SetDisplayArea(-samprate/2e6,samprate/2e6,-70,70);
    ogl_FFTline->ZoomX(spinCenterFreq->GetValue()/1e3, spinSpanFreq->GetValue()/1e3);
    if(LMLL_Testing_SetFFTSamplesCount(m_FFTsamplesCount))
    {
        allocateMemory(m_FFTsamplesCount);
        generateFFTxaxis(samprate/1e6);
    }
    changeSamplingFrequency(samprate/1e6);
    //Set the LNA gain
    LMLL_RxFESetG_LNA_RXFE(cmbLNAGainMode->GetSelection());
    //SEt VGA1 gain
    LMLL_RxFESetRFB_TIA_RXFE(cmbRxFEVGA1->GetSelection());
    //Set VGA2 gain
    LMLL_RxVGA2SetVga2G_u(cmbRxVGA2->GetSelection());
    // Set Bandwidth
    LMLL_RxLPFSetLpfBw(cmbRxFilter->GetSelection()); // Index matches table for all items

    Apply_btn->Enable(false);
	//Rstore Data Collection if applicable
	if(running) StartCapturing();
}
/**
	@brief Actions made when chip is connected
*/
void pnlSpectrum::onChipConnect()
{
	btnStartCapture->Enable(true);
	btnStopCapture->Enable(false);
	LMLL_TopResetOn();
	LMLL_TopResetOff();
	LMAL_CalibrateRx();
	LMAL_CalibrateTx();
	disableDCComparators();

	LMLL_ADDCSetTX_FSYNC_P(1);
	LMLL_ADDCSetRefGainAdj(1);
//	LMLL_TxRfSetPA(1);
	LMAL_SelectActiveLNA(1);
	LMLL_TopSetRXOUTSW(0);
	SendSettings();

	wxCommandEvent dummy;
	OnApply_btnClick(dummy); //Set Freq,BW and Samp rate


//	LMLL_Testing_SetRxDataSource(rgrDataSource->GetSelection());
}

/**
	@brief Actions made when chip is disconnected
*/
void pnlSpectrum::onChipDisconnect()
{
	btnStartCapture->Enable(false);
	btnStopCapture->Enable(false);
}

/**
	@brief Initiates samples capturing
*/
void pnlSpectrum::OnbtnStartCaptureClick(wxCommandEvent& event)
{
    wxCommandEvent dummy;
    OnApply_btnClick(dummy);
    Integration_Time->Enable(FALSE);
    StartCapturing();
}

/**
	@brief Stops samples capturing
*/
void pnlSpectrum::OnbtnStopCaptureClick(wxCommandEvent& event)
{
    Integration_Time->Enable(TRUE);
    StopCapturing();
}

void pnlSpectrum::OnchkIchannelEnabledClick(wxCommandEvent& event)
{
    ogl_IQline->series[0]->visible = chkIchannelEnabled->GetValue();
}

void pnlSpectrum::OnchkQchannelEnabledClick(wxCommandEvent& event)
{
    ogl_IQline->series[1]->visible = chkQchannelEnabled->GetValue();
}

void pnlSpectrum::OnchkDCcorrectionClick(wxCommandEvent& event)
{
//    LMLL_Testing_SetDCCorrection(chkDCcorrection->GetValue());
}
//16777216
/* Disabled 1/7/14
void pnlSpectrum::OnrgrDataSourceSelect(wxCommandEvent& event)
{
//    int selection = rgrDataSource->GetSelection();
//    LMLL_Testing_SetRxDataSource(selection);
    LMLL_Testing_SetRxDataSource(TRUE);
}
/*
void pnlSpectrum::OnrgrTxDataSourceSelect(wxCommandEvent& event)
{
//    LMLL_Testing_SetTxDataSource(rgrTxDataSource->GetSelection());
} */

void pnlSpectrum::OnComboBox1Selected(wxCommandEvent& event)
{
 //   LMLL_RxFESetG_LNA_RXFE(cmbLNAGainMode->GetSelection());
    Apply_btn->Enable(true);
}
void pnlSpectrum::disableDCComparators()
{
	LMLL_RxVGA2SetPwrDCCmpA(false);
	LMLL_RxVGA2SetPwrDCCmpB(false);
}

/**
	@brief Generates values inside GUI combo boxes and selects default values
*/
void pnlSpectrum::initializeInterfaceValues()
{
    wxString cs_Numbers[128];

	LMAL_MainSetAutoDownload(false);
	wxString item;
//	cmbTxVGA1->Clear();
/*	for(int i=-35; i<=-4; i++)
	{
        cs_Numbers[i+35] = wxString::Format("%i", i);
	}
    cmbTxVGA1->Append( 32, cs_Numbers);
	cmbTxVGA1->SetSelection(18);   // -14 dB */

	for(int i=0; i<=25; i++)
	{
        cs_Numbers[i] = wxString::Format("%i", i);
	}
//	cmbTxVGA2->Append( 25, cs_Numbers);
//	cmbTxVGA2->SetSelection(0);

	for(int i=0; i<=30; i+=3)
	{
        cs_Numbers[i/3] = wxString::Format("%i", i);
	}
	cmbRxVGA2->Append( 11, cs_Numbers);
	cmbRxVGA2->SetSelection(m_RxVGA2Sel);

	//char ctemp[32];

	for(int i=0; i<=120; i++)
	    cs_Numbers[i] = wxString::Format("%.2f", 20*log10((float)127/(127-i)));
	cmbRxFEVGA1->Append(121, cs_Numbers);
	cmbRxFEVGA1->SetSelection(m_RxVGA1Sel);
	LMAL_MainSetAutoDownload(true);
}

/**
	@brief Generates frequency values for FFT graph
	@param samplingFreq sampling frequency in Hz
*/
void pnlSpectrum::generateFFTxaxis(float samplingFreq)
{
	int FFTsamples = m_FFTsamplesCount;
	if( m_fftxaxisValues != NULL)
		delete []m_fftxaxisValues;

	m_fftxaxisValues = new float[FFTsamples];
    changeSamplingFrequency(samplingFreq);

	if(samplesXaxis)
        delete []samplesXaxis;
    samplesXaxis = new float[FFTsamples];
	for(int i=0; i<FFTsamples; ++i)
		samplesXaxis[i] = i;

    if(PwrcountXaxis != NULL)
        delete []PwrcountXaxis;
    PwrcountXaxis = new float[g_MaxPwrSpanSec];
//    PwrcountXaxis = new float[g_MaxDispFrames];
 //   for(int i = 0; i < g_MaxDispFrames; i++){
    for(int i = 0; i < g_MaxPwrSpanSec; i++){
        PwrcountXaxis[i] = i;}

}


/**
    @brief Changes FFT amplitudes graph x axis values depending on sampling frequency
    @param samplingFrequency sampling frequency in Hz
*/
void pnlSpectrum::changeSamplingFrequency(float samplingFrequency)
{
    if(m_fftxaxisValues)
    {
        // NB: this is the only place we need to test for a sampling
        //     frequency change which determines if the frequency plan
        //     changes.  Clear g_FFTfileIsDefined or g_OverwriteFFTfile if so
        if( m_samplingFrequency != (unsigned long)samplingFrequency ) {
            g_FFTfileIsDefined = false;     // require re-entry into FFT Output control
            // or
            //g_OverwriteFFTfile = false;   // will cause the next record to not append, but require a new file
            //OverwriteChk->SetValue(false);
#if _DEBUG
            cout << "Disabling FFT file definition because sampling frequency changed" << endl;
#endif // _DEBUG
        }

        //negative frequencies
        for (int f = 0; f < m_FFTsamplesCount / 2 - 1; f++)
        {
            m_fftxaxisValues[f] = (-1) * (m_FFTsamplesCount / 2 - 1 - f) *
                (samplingFrequency / m_FFTsamplesCount);
        }
        // possitive frequencies
        for (int f = 0; f < m_FFTsamplesCount / 2; f++)
        {
            m_fftxaxisValues[f + m_FFTsamplesCount / 2 - 1] =
                (f) * (samplingFrequency / m_FFTsamplesCount);
        }
        m_samplingFrequency = samplingFrequency;
    }
}

/*void pnlSpectrum::OncmbTxFilterSelected(wxCommandEvent& event)
{
    LMLL_TxLPFSetLpfBw(cmbTxFilter->GetSelection()+4); // +4 because this combobox has not all items
} */

void pnlSpectrum::OncmbRxFilterSelected(wxCommandEvent& event)
{
    Apply_btn->Enable(true);
}

/*void pnlSpectrum::OncmbTxVGA1Selected(wxCommandEvent& event)
{
    LMLL_TxRfSetVga1G_u(cmbTxVGA1->GetSelection());
} */

/*void pnlSpectrum::OncmbTxVGA2Selected(wxCommandEvent& event)
{
    LMLL_TxRfSetVga2G_u(cmbTxVGA2->GetSelection());
} */

void pnlSpectrum::OncmbRxFEVGA1Selected(wxCommandEvent& event)
{
    Apply_btn->Enable(true);
}

void pnlSpectrum::OncmbRxVGA2Selected(wxCommandEvent& event)
{
    Apply_btn->Enable(true);
}

void pnlSpectrum::OncmbLNAGainModeSelected(wxCommandEvent& event)
{
    Apply_btn->Enable(true);
}

/**
    @brief Configures receiver frequency
*/
void pnlSpectrum::OnbtnSetRxFreqClick(wxCommandEvent& event)
{
   Apply_btn->Enable(true);
   /* double freq;
    txtRxFrequencyMHz->GetValue().ToDouble(&freq);
	m_RxFreq = freq;
	if( m_RxFreq > 0.2 && m_RxFreq < 5)
		LMAL_RxPLL_SetFrequency(m_RxFreq);
	else
	{
		m_RxFreq = 0.3;
		txtRxFrequencyMHz->SetValue( wxString::Format("%f", 0.3));
	} */
}
/**
    @brief Sends configuration from spectrum panel controls
*/
void pnlSpectrum::SendSettings()
{
    LMLL_TopResetOn();
	LMLL_TopResetOff();

	LMAL_MainSetAutoDownload(false);

	LMAL_EnableAllSPIClocks();


//	LMLL_TxLPFSetLpfBw(cmbTxFilter->GetSelection()+4);
	LMLL_RxLPFSetLpfBw(cmbRxFilter->GetSelection()+4);

//	LMLL_Testing_SetRxDataSource(rgrDataSource->GetSelection());
//	LMLL_TopSetPwrSoftTx(true);
	LMLL_TopSetPwrSoftRx(true);
	//LMLL_Testing_SetTxDataSource(rgrTxDataSource->GetSelection());

	LMLL_RxFESetRFB_TIA_RXFE(cmbRxFEVGA1->GetSelection());
	LMLL_RxVGA2SetVga2G_u(cmbRxVGA2->GetSelection());
	LMAL_RxPLL_SetFrequency(m_RxFreq);
	LMAL_CalibrateRx();

/*	LMLL_TxRfSetVga1G_u(cmbTxVGA1->GetSelection());
	LMLL_TxRfSetVga2G_u(cmbTxVGA2->GetSelection());
	LMAL_TxPLL_SetFrequency(m_TxFreq);
	LMAL_CalibrateTx();
*/
	LMAL_MainSetAutoDownload(true);
	LMAL_MainDownload();
}

/**
    @brief Updates panel controls values
*/
void pnlSpectrum::ReadSettings()
{
	LMAL_MainSetAutoDownload(false);
	LMAL_MainReadSettingsFromChip();

//	cmbTxFilter->SetSelection(LMLL_TxLPFGetLpfBw()-4);
	cmbRxFilter->SetSelection(LMLL_RxLPFGetLpfBw()-4);
//	rgrRxOUTSW->SetSelection(LMLL_TopGetRXOUTSW());
	//cmbPA->SetSelection(LMLL_TxRfGetPA());
   	//cmbLNA->SetSelection(LMLL_RxFEGetLNASEL_RXFE());
//	cmbTxVGA1->SetSelection(LMLL_TxRfGetVga1G_u());
//	cmbTxVGA2->SetSelection(LMLL_TxRfGetVga2G_u());
	cmbRxFEVGA1->SetSelection(LMLL_RxFEGetRFB_TIA_RXFE());
	cmbRxVGA2->SetSelection(LMLL_RxVGA2GetVga2G_u());
	//cmbRefGainAdj->SetSelection(LMLL_ADDCGetRefGainAdj());

	float freq;
	// = LMLL_TxPLLGetFrequency();
//	m_TxFreq = freq;
	char ctemp[80];
//	sprintf(ctemp, "%2.3f", freq);
//	txtTxFrequencyGHz->SetValue(ctemp);

	freq = LMLL_RxPLLGetFrequency();
	m_RxFreq = freq;
	sprintf(ctemp, "%.0f", freq*1000);
	txtRxFrequencyMHz->SetValue(ctemp);

	LMAL_MainSetAutoDownload(true);
	//LMAL_MainDownload();
}

void pnlSpectrum::OnSpinButton1ChangeUp(wxSpinEvent& event)
{
    Apply_btn->Enable(true);
/*	double freq;
	txtTxFrequencyGHz->GetValue().ToDouble(&freq);
	freq += m_frequencyStep;
	m_TxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtTxFrequencyGHz->SetValue(ctemp);*/
}

void pnlSpectrum::OnSpinButton1ChangeDown(wxSpinEvent& event)
{
    Apply_btn->Enable(true);
/*    double freq;
	txtTxFrequencyGHz->GetValue().ToDouble(&freq);
	freq -= m_frequencyStep;
	m_TxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtTxFrequencyGHz->SetValue(ctemp);*/
}

void pnlSpectrum::OnSpinButton2ChangeUp(wxSpinEvent& event)
{
    Apply_btn->Enable(true);
  /*  double freq;
	txtRxFrequencyMHz->GetValue().ToDouble(&freq);
	freq += m_frequencyStep;
	m_RxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtRxFrequencyMHz->SetValue(ctemp);*/
}

void pnlSpectrum::OnSpinButton2ChangeDown(wxSpinEvent& event)
{
 /*   double freq;
	txtRxFrequencyMHz->GetValue().ToDouble(&freq);
	freq -= m_frequencyStep;
	m_RxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);*/
	Apply_btn->Enable(true);
//	txtRxFrequencyMHz->SetValue(ctemp);
}

/**
    @brief Initiates data samples capturing
*/
void pnlSpectrum::StartCapturing()
{
//    changeSamplingFrequency((1e6*spinSamplingFreq->GetValue()));
    changeSamplingFrequency((spinSamplingFreq->GetValue()));
 //   LMLL_TopSetPwrSoftTx(true);
	LMLL_TopSetPwrSoftRx(true);
    LMLL_Testing_StartSdramRead();
    g_capturingData = true;
    PwrSpan->Enable(false);
    if(g_FFTfileIsDefined) EnableFFTRecord(true);
    if(g_PWRfileIsDefined) EnablePWRRecord(true);

    if(spinAvgCount->GetValue() < m_buffersCount)
        m_buffersCountMask = spinAvgCount->GetValue();
    else
    {
        spinAvgCount->SetValue(m_buffersCount);
        m_buffersCountMask = m_buffersCount;
    }

    int interval = 15; // mSec
 //   int interval = 1; // mSec Test
    m_updateTimer->Start(interval);
	btnStartCapture->Enable(false);
	btnStopCapture->Enable(true);
	PwrRef->Enable(true);

	spinFFTsamples->Enable(false);
	//spinSamplingFreq->Enable(false);

    if(m_firststart) {
            oglPWRChart->ZoomX(g_MaxPwrSpanSec/2,g_MaxPwrSpanSec); //Initial Span
//            m_curPwrX_ctr = g_MaxPwrSpanSec/2;
//            m_curPwrX_span = g_MaxPwrSpanSec;
//            m_curPwrX_min = 0;
//            m_CurPwrX_Max = g_MaxPwrSpanSec;
            m_firststart = false;}
    else
            oglPWRChart->ZoomX(g_PwrSpanSec/2,g_PwrSpanSec);

}

/**
    @brief stop data samples capturing
*/
void pnlSpectrum::StopCapturing()
{
//    cout << "Before Timer Stop" << endl;
    //stop graphs update thread
    m_updateTimer->Stop();
//    cout << "After Timer Stop" << endl;
    LMLL_Testing_StopSdramRead();
//    cout << "After StopSdramRead" << endl;
    btnStartCapture->Enable(true);
	btnStopCapture->Enable(false);
	PwrRef->Enable(false);
	spinFFTsamples->Enable(true);
	spinSamplingFreq->Enable(true);
	g_capturingData = false;
    EnableFFTRecord(false);
    EnablePWRRecord(false);
    PwrSpan->Enable(true);
    if(g_PWRfileRecording) g_PWRfileRecording = false;
}

void pnlSpectrum::OnbtnRemoveMarkerClick(wxCommandEvent& event)
{
    ogl_FFTline->RemoveMarker();
}

/**
    @brief Enables to add markers
*/
void pnlSpectrum::OnbtnAddMarkerClick(wxCommandEvent& event)
{
    m_addingMarkers = true;
}

/**
    @brief Adds data marker in FFT graph on clicked point
*/
void pnlSpectrum::Onogl_FFTlineLeftDown(wxMouseEvent& event)
{
    if(m_addingMarkers)
        ogl_FFTline->AddMarker(event.GetX(), event.GetY());
    else
        ogl_FFTline->leftClick(event);
    m_addingMarkers = false;
}

void pnlSpectrum::OnchkIchannelEnabledClick1(wxCommandEvent& event)
{
    ogl_IQline->series[0]->visible = chkIchannelEnabled->GetValue();
}

void pnlSpectrum::OnchkQchannelEnabledClick1(wxCommandEvent& event)
{
    ogl_IQline->series[1]->visible = chkQchannelEnabled->GetValue();
}

void pnlSpectrum::OnspinCenterFreqChange(wxSpinEvent& event)
{
    ogl_FFTline->ZoomX((m_FFTChartCenter = spinCenterFreq->GetValue()/1e3),
                       (m_FFTChartSpan = spinSpanFreq->GetValue()/1e3));
}

void pnlSpectrum::OnspinSpanFreqChange(wxSpinEvent& event)
{
    ogl_FFTline->ZoomX((m_FFTChartCenter = spinCenterFreq->GetValue()/1e3),
                       (m_FFTChartSpan = spinSpanFreq->GetValue()/1e3));

    cout << "Center Zoom =  " << m_FFTChartCenter << endl;
    cout << "Span Zoom = " << m_FFTChartSpan << endl;
}

/**
    @brief Changes FFT samples count used for calculations
    @todo  May require a stop capture, start capture cycle...
*/
void pnlSpectrum::OnspinFFTsamplesChange(wxSpinEvent& event)
{
    int power = spinFFTsamples->GetValue();

    // NB: this is the only place we need to check for changes to
    //     the FFT samples/frame, for the purpose of cancelling
    //     the g_FFTfileIsDefined or xxx in order to prevent
    //     appending the wrong frequency plan to the same file.
    if( twotoN(power) != m_FFTsamplesCount) {
        g_FFTfileIsDefined = false;     // require re-entry into FFT Output control
        // or
        //g_OverwriteFFTfile = false;   // will cause the next record to not append, but require a new file
        //OverwriteChk->SetValue(false);
#if _DEBUG
        cout << "Disabling FFT file definition because FFT samples changed" << endl;
#endif // _DEBUG
    }
    m_FFTsamplesCount = twotoN(power);
    if(ogl_IQline) ogl_IQline->SetDisplayArea(0, m_FFTsamplesCount, -2048, 2048);
    txtFFTsamples->SetValue( wxString::Format("%i", m_FFTsamplesCount));
    if(LMLL_Testing_SetFFTSamplesCount(m_FFTsamplesCount))
    {
        allocateMemory(m_FFTsamplesCount);
        generateFFTxaxis((unsigned long)m_samplingFrequency);
    }
}

/**
    @brief Calculates FFT and redraws graphs
*/
void pnlSpectrum::UpdateGraphs(wxTimerEvent &event)
{
    if(!g_capturingData) return; // break loop for close

    if(m_updating)
        return;
 //10/9   if(g_FFTfileSetup) return; // Break Loop for file open
    if(g_FFTfileSetup || g_PWRfileSetup) return; // Break Loop for file open
    m_updating = true;
    char outbuf[80];
    wxCommandEvent dummy;
	int fftsLeft = 0; // FFT results left in queue

	bool averageFFT = chkAverage->GetValue();
	bool calculated = false;
	wxDateTime dt;
	if(averageFFT != true)
	{
        if(chkUpdateGraphs->GetValue() == true)
        {
            //calculate FFT
            calculated = LMLL_Testing_CalculateFFT();
            //if FFT has been calculated
            if(calculated)
            {
                //not averaging, take only one result
                LMLL_Testing_GetFFTData(  m_IchannelData,
                                          m_QchannelData,
                                          m_IQdataSize,
                                          m_FFTamplitudes,
                                          m_FFTdataSize,
                                          fftsLeft );

#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
                if( m_PwrRefIsSet && not m_backgroundSubtract) {
                    float min = 1.0 * (1<<12);  // 12-bit ADC max value
                    float max = 0.0;
                    float sum = 0.0;
                    float ref = -370.0;         // reference level selected in dB
                    const char *tag = "NONE";

                    // not subtracting, but set power reference just set
                    m_backgroundSubtract = true;
                    // smoothing background spectrogram
                    memcpy(m_FFTbackgroundAvg,m_FFTamplitudes,m_FFTdataSize*sizeof(float));
                    for(int i=3; i<m_FFTdataSize-3;i++)
                        // apply 7pt smoothing function on background
                        // TODO: make parametric
                        m_FFTbackgroundAvg[i] = (
                                                 m_FFTbackgroundAvg[i-3] +
                                                 m_FFTbackgroundAvg[i-2] +
                                                 m_FFTbackgroundAvg[i-1] +
                                                 m_FFTbackgroundAvg[i]   +
                                                 m_FFTbackgroundAvg[i+1] +
                                                 m_FFTbackgroundAvg[i+2] +
                                                 m_FFTbackgroundAvg[i+3] +
                                                 0.0) / 7.0;
                    // computing statistics on background spectrogram
                    for(int i=0; i<m_FFTdataSize; i++) {
                        m_FFTMaxAmplitudes[i] = -370.0;
                        if( m_FFTbackgroundAvg[i] < min ) min = m_FFTbackgroundAvg[i];
                        if( m_FFTbackgroundAvg[i] > max ) max = m_FFTbackgroundAvg[i];
                                                         sum += m_FFTbackgroundAvg[i];
                    }
                    if( g_backgroundDebugCfg & BACKGROUND_REFERENCE_MEDIAN )
                    {
                        float scratch[m_FFTdataSize];
                        extern float quick_select(float arr[], int n);
                        memcpy(scratch,m_FFTbackgroundAvg,m_FFTdataSize*sizeof(float));
                        g_Statistics_g_FFTbackgroundReferenceLevel = quick_select(scratch, m_FFTdataSize);
                        tag = "MEDIAN";
                    }
                    else if( g_backgroundDebugCfg & BACKGROUND_REFERENCE_HISTO )
                    {
                        extern float histogram_select(float arr[], int n);
                        ref = histogram_select(m_FFTbackgroundDb,m_FFTdataSize);
                        g_Statistics_g_FFTbackgroundReferenceLevel = pow(10.0,ref/10.0);
                        tag = "HISTOGRAM";
                    }
                    else if( g_backgroundDebugCfg & BACKGROUND_REFERENCE_MEAN )
                    {
                        g_Statistics_g_FFTbackgroundReferenceLevel = sum / (float)m_FFTdataSize;
                        tag = "MEAN";
                    }
                    else
                        g_Statistics_g_FFTbackgroundReferenceLevel = 0.0;
                    if( g_backgroundDebugCfg & BACKGROUND_SUBTRACT)
                    {
                        if( g_backgroundDebugCfg & BACKGROUND_VECTOR )
                        {
                            memcpy(m_FFTbackground,m_FFTbackgroundAvg,m_FFTdataSize*sizeof(float));
                        } else {
                            for(int i=0; i<m_FFTdataSize; i++) m_FFTbackground[i] = g_Statistics_g_FFTbackgroundReferenceLevel;
                        }
                    }
                    for(int i=0; i<m_FFTdataSize; i++) m_FFTbackgroundDb[i] = 10 * log10( m_FFTbackground[i] );
#ifdef _DEBUG
                    // convert statistics to dB for logging
                    min = (min <= 0.0) ? -370.0 : 10 * log10( min );
                    max = (max <= 0.0) ? -370.0 : 10 * log10( max );
                    sum = sum / (float)m_FFTdataSize;
                    sum = (sum <= 0.0) ? -370.0 : 10 * log10( sum );
                    ref = g_Statistics_g_FFTbackgroundReferenceLevel;
                    ref = (ref <= 0.0) ? -370.0 : 10 * log10( ref );
                    wxSprintf(outbuf,"%s (Reference %s%s %0.3f dB) statistics(min/max/mean in dB):%0.3f/%0.3f/%0.3f",
                        g_backgroundDebugCfg & BACKGROUND_SUBTRACT ? "Enabled" : "Display Reference Only",
                        tag,
                        g_backgroundDebugCfg & BACKGROUND_ABOVE_REFERENCE ? " Applied" : " Calculated Only",
                        ref, min, max, sum);
                    cout << "Background Subtraction " << outbuf << endl;
#endif  // _DEBUG
                } else if( not m_PwrRefIsSet && m_backgroundSubtract) {
                    // subtracting, but set power reference just cleared
                    m_backgroundSubtract = false;
                    g_Statistics_g_FFTbackgroundReferenceLevel = 0.0;
                    for(int i=0; i<m_FFTdataSize; i++) m_FFTbackground[i] = 0.0;
                    cout << "Background Subtraction Disabled" << endl;
                }
#endif  // BACKGROUND_DEBUG
                // Write Time Stamp to file
                if(g_FFTfileRecording && m_FFTCounter == 0) {
                    int ms = dt.UNow().GetMillisecond();
                    wxSprintf(outbuf,".%03d",ms);
                    if(g_FFTFileType == 0) {
                            if(g_FFT_TimeStandard == 0) {
                                    m_FFTFileClassPtr->Write(dt.Now().FormatTime().c_str());
                                    m_FFTFileClassPtr->Write(outbuf);}
                            else {
 // Bug fix 5/24                                   m_FileClassPtr->Write(dt.Now().ToUTC().FormatTime().c_str());
                                    m_FFTFileClassPtr->Write(dt.UNow().ToUTC().FormatISOCombined().c_str());
                                    wxSprintf(outbuf,".%03d",ms);
                                    m_FFTFileClassPtr->Write(outbuf);
                                    m_FFTFileClassPtr->Write("Z");
                                    }
                    }
                    else {
                            if(g_FFT_TimeStandard == 0){
                                m_FFTFileClassPtr->Write(dt.Now().FormatISOCombined().c_str());
                                wxSprintf(outbuf,".%03d",ms);
                                m_FFTFileClassPtr->Write(outbuf);}
                            else{
                                m_FFTFileClassPtr->Write(dt.Now().ToUTC().FormatISOCombined().c_str());
                                wxSprintf(outbuf,".%03d",ms);
                                m_FFTFileClassPtr->Write(outbuf);
                                m_FFTFileClassPtr->Write("Z"); }
                            }
                    m_FFTFileClassPtr->Write(",");
                }
                //convert FFT results to dB
                for(int i=0; i<m_FFTdataSize; i++)
                {
                    float value;
#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
                    m_FFTamplitudes[i] -= m_FFTbackground[i];
                    m_FFTamplitudes[i] *= g_integrationGain;
                    if( g_backgroundDebugCfg & BACKGROUND_ABOVE_REFERENCE )
                    {
                        if( m_FFTamplitudes[i] <= g_Statistics_g_FFTbackgroundReferenceLevel )  // NB: may be 0.0
                            // render the difference between the reference level and the subtracted signal
                            m_FFTamplitudes[i] = (2.0 * g_Statistics_g_FFTbackgroundReferenceLevel) - m_FFTamplitudes[i];
                        else if( g_backgroundDebugCfg & BACKGROUND_ABOVE_REFERENCE )
                            // render the difference above the reference level
                            m_FFTamplitudes[i] += g_Statistics_g_FFTbackgroundReferenceLevel;
                    }
                    // otherwise, just render pure background subtracted
#endif  // BACKGROUND_DEBUG
                    if( m_FFTamplitudes[i] <= 0.0) {
                        m_FFTamplitudes[i] = -370.0;
                    } else {
                        m_FFTamplitudes[i] = 10 * log10( m_FFTamplitudes[i] );
                    }
// BUG: RASDRviewer 1.2.2.1 would skip this point if the amplitude was too low
                    if(m_FFTamplitudes[i] >= m_FFTMaxAmplitudes[i])
                        m_FFTMaxAmplitudes[i] = m_FFTamplitudes[i];
                    value = m_MaxHold ? m_FFTMaxAmplitudes[i] : m_FFTamplitudes[i];
                    if(g_FFTfileRecording && m_FFTCounter >= g_FFTframeSkip){
                        if(g_FFTDataSource == 0) {
                            sprintf(outbuf,"%.4f,\0",value);
                            m_FFTFileClassPtr->Write(outbuf); }
                        if(g_FFTDataSource == 1
                        &&(m_fftxaxisValues[i] >= m_FFTChartCenter - (m_FFTChartSpan/2))
                        &&(m_fftxaxisValues[i] <= m_FFTChartCenter + (m_FFTChartSpan/2))) {
                            sprintf(outbuf,"%.4f,\0",value);
                            m_FFTFileClassPtr->Write(outbuf); }
                    }
                }
                if(g_FFTfileRecording && m_FFTFileClassPtr != NULL && m_FFTCounter >= g_FFTframeSkip) {
                    m_FFTFileClassPtr->Write("\r\n",2);
                    m_FFTCounter = 0;
                    m_FFTsRecorded++;
                    sprintf(outbuf,"%d",m_FFTsRecorded);
                    FFTsREC->SetValue(outbuf);
                    if(m_FFTsRecorded >= g_FFTframesOut)
                        OnRecordFFTClick(dummy);
                }
                else if(g_FFTfileRecording) m_FFTCounter++;
            }
        }
	}
	else //  averaging
	{
        if(chkUpdateGraphs->GetValue() == true)
        {
            calculated = LMLL_Testing_CalculateFFT();
            if(calculated)
            {
                float oneOverBuffersCountMask = 1.0/(float)m_buffersCountMask;

                //takes one FFT results and add it to averaging buffer
                LMLL_Testing_GetFFTData(m_IchannelData, m_QchannelData, m_IQdataSize, m_FFTamplitudesBuffer[bufferPos], m_FFTdataSize, fftsLeft);

                // update acquisition buffer position index
                bufferPos = (bufferPos + 1) % m_buffersCountMask;

                memset(m_FFTamplitudesBuffer[m_buffersCount], 0, sizeof(float)*m_FFTsamplesCount);

#if 0   // new averaging method...
#else
                // calculate average by keeping a circular buffer and *re-calculating* at each iteration
                for(int i=0; i<m_buffersCountMask; ++i)
                {
                    for(int j=0; j<m_FFTsamplesCount; ++j)
                        m_FFTamplitudesBuffer[m_buffersCount][j] += m_FFTamplitudesBuffer[bufferPos][j];
                    bufferPos = (bufferPos + 1) % m_buffersCountMask;
                }
                for(int j=0; j<m_FFTsamplesCount; ++j)
                    m_FFTamplitudesBuffer[m_buffersCount][j] = m_FFTamplitudesBuffer[m_buffersCount][j] * oneOverBuffersCountMask;
#endif // 0

#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
                if( m_PwrRefIsSet && not m_backgroundSubtract) {
                    float min = 1.0 * (1<<12);  // 12-bit ADC max value
                    float max = 0.0;
                    float sum = 0.0;
                    float ref = -370.0;         // reference level selected in dB
                    const char *tag = "NONE";

                    // not subtracting, but set power reference just set
                    m_backgroundSubtract = true;
                    // smoothing background spectrogram
                    memcpy(m_FFTbackgroundAvg,m_FFTamplitudesBuffer[m_buffersCount],m_FFTdataSize*sizeof(float));
                    for(int i=3; i<m_FFTdataSize-3;i++)
                        // apply 7pt smoothing function on background
                        // TODO: make parametric
                        m_FFTbackgroundAvg[i] = (
                                                 m_FFTbackgroundAvg[i-3] +
                                                 m_FFTbackgroundAvg[i-2] +
                                                 m_FFTbackgroundAvg[i-1] +
                                                 m_FFTbackgroundAvg[i]   +
                                                 m_FFTbackgroundAvg[i+1] +
                                                 m_FFTbackgroundAvg[i+2] +
                                                 m_FFTbackgroundAvg[i+3] +
                                                 0.0) / 7.0;
                    // computing statistics on background spectrogram
                    for(int i=0; i<m_FFTdataSize; i++) {
                        m_FFTMaxAmplitudes[i] = -370.0;
                        if( m_FFTbackgroundAvg[i] < min ) min = m_FFTbackgroundAvg[i];
                        if( m_FFTbackgroundAvg[i] > max ) max = m_FFTbackgroundAvg[i];
                                                         sum += m_FFTbackgroundAvg[i];
                    }
                    if( g_backgroundDebugCfg & BACKGROUND_REFERENCE_MEDIAN)
                    {
                        float scratch[m_FFTdataSize];
                        extern float quick_select(float arr[], int n);
                        memcpy(scratch,m_FFTbackgroundAvg,m_FFTdataSize*sizeof(float));
                        g_Statistics_g_FFTbackgroundReferenceLevel = quick_select(scratch, m_FFTdataSize);
                        tag = "MEDIAN";
                    }
                    else if( g_backgroundDebugCfg & BACKGROUND_REFERENCE_HISTO )
                    {
                        extern float histogram_select(float arr[], int n);
                        ref = histogram_select(m_FFTbackgroundDb,m_FFTdataSize);
                        g_Statistics_g_FFTbackgroundReferenceLevel = pow(10.0,ref/10.0);
                        tag = "HISTOGRAM";
                    }
                    else if( g_backgroundDebugCfg & BACKGROUND_REFERENCE_MEAN)
                    {
                        g_Statistics_g_FFTbackgroundReferenceLevel = sum / (float)m_FFTdataSize;
                        tag = "MEAN";
                    }
                    else
                        g_Statistics_g_FFTbackgroundReferenceLevel = 0.0;
                    if( g_backgroundDebugCfg & BACKGROUND_SUBTRACT)
                    {
                        if( g_backgroundDebugCfg & BACKGROUND_VECTOR )
                        {
                            memcpy(m_FFTbackground,m_FFTbackgroundAvg,m_FFTdataSize*sizeof(float));
                        } else {
                            for(int i=0; i<m_FFTdataSize; i++) m_FFTbackground[i] = g_Statistics_g_FFTbackgroundReferenceLevel;
                        }
                    }
                    for(int i=0; i<m_FFTdataSize; i++) m_FFTbackgroundDb[i] = 10 * log10( m_FFTbackground[i] );
#ifdef _DEBUG
                    // convert statistics do dB for logging
                    min = (min <= 0.0) ? -370.0 : 10 * log10( min );
                    max = (max <= 0.0) ? -370.0 : 10 * log10( max );
                    sum = sum / (float)m_FFTdataSize;
                    sum = (sum <= 0.0) ? -370.0 : 10 * log10( sum );
                    ref = g_Statistics_g_FFTbackgroundReferenceLevel;
                    ref = (ref <= 0.0) ? -370.0 : 10 * log10( ref );
                    wxSprintf(outbuf,"%s (Frame Averaged, Reference %s%s %0.3f dB) statistics(min/max/mean in dB):%0.3f/%0.3f/%0.3f",
                        g_backgroundDebugCfg & BACKGROUND_SUBTRACT ? "Enabled" : "Display Reference Only",
                        tag,
                        g_backgroundDebugCfg & BACKGROUND_ABOVE_REFERENCE ? " Applied" : " Calculated Only",
                        ref, min, max, sum);
                    cout << "Background Subtraction Enabled" << outbuf << endl;
#endif  // _DEBUG
                } else if( not m_PwrRefIsSet && m_backgroundSubtract) {
                    // subtracting, but set power reference just cleared
                    m_backgroundSubtract = false;
                    g_Statistics_g_FFTbackgroundReferenceLevel = 0.0;
                    for(int i=0; i<m_FFTdataSize; i++) m_FFTbackground[i] = 0.0;
                    cout << "Background Subtraction Disabled" << endl;
                }
#endif  // BACKGROUND_DEBUG
                // Write Time Stamp to file
                if(g_FFTfileRecording && m_FFTCounter == 0) {
                    int ms = dt.UNow().GetMillisecond();
                    wxSprintf(outbuf,".%03d",ms);
                    if(g_FFT_TimeStandard == 0 && g_FFTFileType == 0){
                        m_FFTFileClassPtr->Write(dt.Now().FormatTime().c_str());
                        m_FFTFileClassPtr->Write(outbuf); }
                    if(g_FFT_TimeStandard == 0 && g_FFTFileType == 1) {
                        m_FFTFileClassPtr->Write(dt.Now().FormatTime().c_str());
                        m_FFTFileClassPtr->Write(outbuf);}
                    if(g_FFT_TimeStandard == 1 && g_FFTFileType == 0) {
                        m_FFTFileClassPtr->Write(dt.UNow().ToUTC().FormatISOCombined().c_str());
                        wxSprintf(outbuf,".%03d",ms);
                        m_FFTFileClassPtr->Write(outbuf);
                        m_FFTFileClassPtr->Write("Z"); }
                    if(g_FFT_TimeStandard == 1 && g_FFTFileType == 1) {
                        m_FFTFileClassPtr->Write(dt.Now().ToUTC().FormatISOCombined().c_str());
                        wxSprintf(outbuf,".%03d",ms);
                        m_FFTFileClassPtr->Write(outbuf);
                        m_FFTFileClassPtr->Write("Z"); }
                    m_FFTFileClassPtr->Write(",");
                }
                //convert to dB
                for(int i=0; i<m_FFTdataSize; i++)
                {
                    float value;
                    m_FFTamplitudes[i]  = m_FFTamplitudesBuffer[m_buffersCount][i];
#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
                    m_FFTamplitudes[i] -= m_FFTbackground[i];
                    m_FFTamplitudes[i] *= g_integrationGain;
                    if( g_backgroundDebugCfg & BACKGROUND_ABOVE_REFERENCE )
                    {
                        m_FFTamplitudes[i] += g_Statistics_g_FFTbackgroundReferenceLevel;
                    }
                    // otherwise, just render pure background subtracted
#endif  // BACKGROUND_DEBUG
                    if( m_FFTamplitudes[i] <= 0.0) {
                        m_FFTamplitudes[i] = -370.0;
                    } else {
                        m_FFTamplitudes[i] = 10 * log10( m_FFTamplitudes[i] );
                    }
// BUG: RASDRviewer 1.2.2.1 would skip this point if the amplitude was too low
                    if(m_FFTamplitudes[i] >= m_FFTMaxAmplitudes[i])
                        m_FFTMaxAmplitudes[i] = m_FFTamplitudes[i];
                    value = m_MaxHold ? m_FFTMaxAmplitudes[i] : m_FFTamplitudes[i];
                    if(g_FFTfileRecording && m_FFTCounter >= g_FFTframeSkip){
                        if(g_FFTDataSource == 0) {
                            sprintf(outbuf,"%.4f,\0",value);
                            m_FFTFileClassPtr->Write(outbuf); }
                        if(g_FFTDataSource == 1
                        &&(m_fftxaxisValues[i] >= m_FFTChartCenter - (m_FFTChartSpan/2))
                        &&(m_fftxaxisValues[i] <= m_FFTChartCenter + (m_FFTChartSpan/2))) {
                            sprintf(outbuf,"%.4f,\0",value);
                            m_FFTFileClassPtr->Write(outbuf); }
                    }
                }
                if(g_FFTfileRecording && m_FFTFileClassPtr != NULL && m_FFTCounter >= g_FFTframeSkip) {
                    m_FFTFileClassPtr->Write("\r\n",2);
                    m_FFTCounter = 0;
                    m_FFTsRecorded++;
                    sprintf(outbuf,"%d",m_FFTsRecorded);
                    FFTsREC->SetValue(outbuf);
                    if(m_FFTsRecorded >= g_FFTframesOut)
                        OnRecordFFTClick(dummy);
                }
                else if(g_FFTfileRecording) m_FFTCounter++;
            }
        }
	}

    unsigned long rate = 1;
	unsigned long dataRateBps = 0;
	unsigned int failures = 0;

	//get data rate and failure count
	LMLL_Testing_GetStatusInfo(dataRateBps, failures);
	rate = dataRateBps;
	lblDataRate->SetLabel( wxString::Format(wxT("%i"), rate));

	if(chkUpdateGraphs->GetValue() == true)
	{
        ogl_IQline->series[0]->AssignValues(samplesXaxis, m_IchannelData, m_IQdataSize);
        ogl_IQline->series[1]->AssignValues(samplesXaxis, m_QchannelData, m_IQdataSize);
		ogl_IQscatter->series[0]->AssignValues(m_IchannelData, m_QchannelData, m_IQdataSize);
		if(!m_MaxHold)
            ogl_FFTline->series[0]->AssignValues(m_fftxaxisValues, m_FFTamplitudes, m_FFTdataSize);
        else
            ogl_FFTline->series[0]->AssignValues(m_fftxaxisValues, m_FFTMaxAmplitudes, m_FFTdataSize);
#if defined(BACKGROUND_DEBUG) && BACKGROUND_DEBUG
        if(m_backgroundSubtract) {
            ogl_FFTline->series[1]->color = 0x00FF0000; // green+no alpha
            ogl_FFTline->series[1]->AssignValues(m_fftxaxisValues, m_FFTbackgroundDb, m_FFTdataSize);
        } else {
            ogl_FFTline->series[1]->color = 0xF0F0F0FF; // background
            // keep existing series as is (which just changes their color)
        }
#endif  // BACKGROUND_SUBTRACE
		ogl_FFTline->Refresh();
		ogl_IQscatter->Refresh();
		ogl_IQline->Refresh();
//		oglPWRChart->Refresh();
	}
	++m_frames;
	m_time = GetTickCount()-m_lastUpdate;
	if(m_time >= 1000 * m_PwrIntTime)
//	if(m_time >= 1000)
    {
        lblFPS->SetLabel( wxString::Format("%i", m_frames));
        UpdatePwrGraph();
        m_frames = 0;
        m_time = 0;
        m_lastUpdate = GetTickCount();
    }
    else CalculatePwrAve();
//	m_lastUpdate = GetTickCount();
    m_updating = false;
}
void pnlSpectrum::SetPwrRange() {

m_PwrMax = 0;
m_PwrMin = 999;
for(int i = m_Index; i > m_Index - g_PwrSpanSec; i--){
    if(i < 0) break;
    if(m_PWRvalues[i] > m_PwrMax)  m_PwrMax = 1.1 * m_PWRvalues[i];
    if(m_PWRvalues[i] < m_PwrMin) m_PwrMin = 0.9 * m_PWRvalues[i];

    }

float span = m_PwrMax - m_PwrMin;
float center = m_PwrMin + (span/2);
    if(oglPWRChart) {
        oglPWRChart->ZoomY(center,span);

    }
}
void pnlSpectrum::UpdatePwrGraph()
{
    if(!g_capturingData) return; // Break loop for close
    // Calculate the average power and clear accumulator
        m_PwrAccum = m_PwrAccum + g_framepwr;
        m_PwrAveCount++;
        m_PwrAve = m_PwrAccum / m_PwrAveCount;
#if defined(CSV_DEBUG)
    // Coherent output with timestamp
    {
        static bool once = true;
        wxDateTime dt;
        wxDateTime ts = dt.UNow();
        int ms = ts.GetMillisecond();
        long updateCount = InterlockedExchange(&g_Statistics_updateCount,0);
        char outbuf[1024];

        if(once)
        {
            wxString timecode = ts.Format("%Y-%m-%dT%H%M");
            if(m_CSVFileClassPtr == NULL) m_CSVFileClassPtr = new wxFile();
            wxSprintf(outbuf,CSV_DEBUG,timecode.c_str());  // create unique filenames
            cout << "Using " << outbuf << " as log file..." << endl;
            m_CSVFileClassPtr->Create(outbuf,FALSE,wxS_DEFAULT);
            wxSprintf(outbuf,"Timestamp,Rate (KB/s),UpdateCode,Failures,Packets,FFTs,Samples FIFO Level,FFT FIFO Level,Polarity,I/Q Shift,ReferenceLevel,avgI,avgQ,Pwr (mW),Avg Pwr (mW)\r\n");
            once = false;
        } else {
            wxSprintf(outbuf,"%s.%03dZ,%u,%ld,%d,%ld,%ld,%d,%d,%s,%s,%f,%f,%f,%f,%f\r\n",
                ts.ToUTC().FormatISOCombined().c_str(), ts.GetMillisecond(),
                g_Statistics_m_bytesPerSecond,
                updateCount,
                g_Statistics_ulFailures,
                g_Statistics_packetReceived,
                g_Statistics_countFFT,
                g_Statistics_m_SamplesFIFOLength,
                g_Statistics_m_fftFIFOLength,
                (g_Statistics_m_frameStart ? "QI" : "IQ"),
                (g_Statistics_needToAlignData ? "true" : "false"),
                g_Statistics_g_FFTbackgroundReferenceLevel,
                g_avgI, g_avgQ,
                g_framepwr,
                m_PwrAve );
        }
        if( m_CSVFileClassPtr && m_CSVFileClassPtr->IsOpened()) {
            m_CSVFileClassPtr->Write(outbuf);
            cout << outbuf;
        }
    }
#elif defined(_DEBUG)
        cout << "Pwr = " << g_framepwr;
        cout << " Ave Pwr = " << m_PwrAve << endl;
#endif // defined
        //Reset /accumulator and count
        m_PwrAccum = 0;
        m_PwrAveCount = 0;

     // Update the graph
		m_PWRvalues[m_Index] = m_PwrAve - m_PwrRefOffset; // Transfer Global power for frame
        if(g_PWRfileRecording){  // Output data to file
            if(g_PwrRecordRate == 1){
                RecordPwrLine(m_Index,m_PWRvalues[m_Index]);
            }
            else {
                m_PWRRecordCount++;
                m_PWRRecordAccum = m_PWRRecordAccum + m_PWRvalues[m_Index];
                if(m_PWRRecordCount >= g_PwrRecordRate) {
                    RecordPwrLine(m_Index,m_PWRRecordAccum/m_PWRRecordCount);
                    m_PWRRecordCount = 0;
                    m_PWRRecordAccum = 0;
                }
            }
        }
//		PwrcountXaxis[m_Index] = m_PwrCount; //Set X value to Power Count
		m_PwrCount++;
		m_Index++;
		// Prevent Memory Overflow      todo add popup message
		if(m_Index == g_MaxPwrSpanSec) { //Prevent Memory Overflow
            cout << "MaxPwrSpanSec Exceeded" << endl;
            StopCapturing();
            // BUG: this is Paul's original code.  It freezes all data capturing at 86400 sec (about 24hrs).
            //btnStartCapture->Enable(false);
            // FIX: starting a new capture re-allocates buffers
            // TODO: it may stop file data output so this needs to be checked
            StartCapturing();
		}

            if(m_Index == 1) {
 //                   m_curPwrX_ctr = g_PwrSpanSec/2;
 //                   m_curPwrX_span = ;
                    oglPWRChart->ZoomX(g_PwrSpanSec/2,g_PwrSpanSec);
                    m_MinCurPwrIndex = 0; }
       /*     if(m_Index == m_CurPwrX_Max) { // Roll the chart
                m_curPwrX_ctr++;
                oglPWRChart->ZoomX(m_curPwrX_ctr,m_curPwrX_span);
                m_CurPwrX_Max++;
                m_curPwrX_min++;
            } */

            if(m_Index == g_PwrSpanSec + m_MinCurPwrIndex){
                oglPWRChart ->ZoomX(m_Index +1 -g_PwrSpanSec/2,g_PwrSpanSec);
                m_MinCurPwrIndex = m_Index +1 - g_PwrSpanSec;
                oglPWRChart->Refresh();
                }
            if(m_PWRSpanSecChanged) {
                m_PWRSpanSecChanged = false;
                if(m_Index > g_PwrSpanSec){ //Handles Change in spansec
                    oglPWRChart ->ZoomX(m_Index,g_PwrSpanSec);
                    m_MinCurPwrIndex = m_Index - g_PwrSpanSec /2;
                    }
            }
    if(m_PwrRefOffset > 0) {
		if(m_PwrAve -m_PwrRefOffset < 0.25 * m_YSPan[m_curYstep] && m_curYstep > 0) {
            m_curYstep--;
            oglPWRChart->ZoomY(m_YCent[m_curYstep],m_YSPan[m_curYstep]);}
        if(m_PwrAve - m_PwrRefOffset > 0.75 * m_YSPan[m_curYstep] && m_curYstep < 6) {
            m_curYstep++;
            oglPWRChart->ZoomY(m_YCent[m_curYstep],m_YSPan[m_curYstep]);}
        }

    oglPWRChart->series[0]->AssignValues(PwrcountXaxis, m_PWRvalues, g_DisplayFrames);
    oglPWRChart->Refresh();

    if(g_framepwr > 0.9 * m_PwrMax || g_framepwr < 0.9 * m_PwrMin)
        SetPwrRange();

    if(g_framepwr < MIN_THRESH || g_framepwr > MAX_THRESH)
        oglPWRChart->series[0]->color = 0xFF0000FF; //Red
    else oglPWRChart->series[0]->color = 0x00FF00FF; // Green
//        cout << g_framepwr << endl;
}
void pnlSpectrum::RecordPwrLine(int index, double value)
{
    char outbuf[80];
	wxDateTime dt;

    if(!m_PWRFileClassPtr || !m_PWRFileClassPtr->IsOpened()) return; // File not Opened

        int ms = dt.UNow().GetMillisecond();
        wxSprintf(outbuf,".%03d",ms);
        if(g_PWRTimeStandard == 0 && g_PWRFileType == 0){
            m_PWRFileClassPtr->Write(dt.Now().FormatTime().c_str());
            m_PWRFileClassPtr->Write(outbuf); }
        if(g_PWRTimeStandard == 0 && g_PWRFileType == 1) {
            m_PWRFileClassPtr->Write(dt.Now().FormatTime().c_str());
            m_PWRFileClassPtr->Write(outbuf);}
        if(g_PWRTimeStandard == 1 && g_PWRFileType == 0) {
            m_PWRFileClassPtr->Write(dt.UNow().ToUTC().FormatISOCombined().c_str());
            wxSprintf(outbuf,".%03d",ms);
            m_PWRFileClassPtr->Write(outbuf);
            m_PWRFileClassPtr->Write("Z"); }
        if(g_PWRTimeStandard == 1 && g_PWRFileType == 1) {
            m_PWRFileClassPtr->Write(dt.Now().ToUTC().FormatISOCombined().c_str());
            wxSprintf(outbuf,".%03d",ms);
            m_PWRFileClassPtr->Write(outbuf);
            m_PWRFileClassPtr->Write("Z"); }

        sprintf(outbuf,",%0.3f\r\n",value);
        m_PWRFileClassPtr->Write(outbuf);

}
void pnlSpectrum::CalculatePwrAve()
{
        m_PwrAccum = m_PwrAccum + g_framepwr;
        m_PwrAveCount++;
}
bool pnlSpectrum::IsCapturingData()
{
    return g_capturingData;
}

void pnlSpectrum::OnspinAvgCountChange(wxSpinEvent& event)
{
    if( g_UnlimitedAveraging )
    {
        m_buffersCountMask = 1;
    } else {
        m_buffersCountMask = spinAvgCount->GetValue();
        if(m_buffersCountMask > m_buffersCount)
        {
            m_buffersCountMask = m_buffersCount;
            spinAvgCount->SetValue(m_buffersCount);
        }
    }
}

void pnlSpectrum::OnGLCanvas1Paint1(wxPaintEvent& event)
{
}

void pnlSpectrum::OnGLCanvas1Paint2(wxPaintEvent& event)
{
}

void pnlSpectrum::Onogl_FFTlinePaint(wxPaintEvent& event)
{
}

void pnlSpectrum::OnspinSamplingFreqChange(wxSpinEvent& event)
{
    Apply_btn->Enable(true);
}

void pnlSpectrum::OnspinSamplingFreqChange1(wxSpinEvent& event)
{
    Apply_btn->Enable(true);
}

void pnlSpectrum::OnPanel2Paint(wxPaintEvent& event)
{
}

void pnlSpectrum::OnPanel2Paint1(wxPaintEvent& event)
{
}

void pnlSpectrum::OnspinSamplingFreqChange2(wxSpinEvent& event)
{
}

void pnlSpectrum::OntxtRxFrequencyGHzTextEnter(wxCommandEvent& event)
{
    Apply_btn->Enable(true);
}

void pnlSpectrum::Onogl_IQlinePaint(wxPaintEvent& event)
{
}

void pnlSpectrum::Onogl_FFTlinePaint1(wxPaintEvent& event)
{
}

void pnlSpectrum::Onogl_FFTlinePaint2(wxPaintEvent& event)
{
}

void pnlSpectrum::OnPanel1Paint(wxPaintEvent& event)
{
}

void pnlSpectrum::OnoglPWRChartPaint(wxPaintEvent& event)
{
}

void pnlSpectrum::OnoglPWRChartPaint1(wxPaintEvent& event)
{
}

void pnlSpectrum::OnoglPWRChartLeftDown(wxMouseEvent& event)
{
    oglPWRChart->leftClick(event);
}

void pnlSpectrum::OnButton2Click(wxCommandEvent& event)
{
}

void pnlSpectrum::OnRecordFFTClick(wxCommandEvent& event)
{
    FFTRec_btn->Enable(false); // Avoid Key Bounce
    if(!g_FFTfileRecording) {
        bool success = OpenFFTfile();
        if( success ) {
            char outbuf[80];
            FFTRec_btn->SetLabel("Stop FFT Rec");
            cout << "FFT File recording" << endl;
            m_FFTsRecorded = 0; //Reset
            sprintf(outbuf,"%d",m_FFTsRecorded);
            FFTsREC->SetValue(outbuf);
            // NB: moved headers and frequency tags to OpenFFTfile()
            g_FFTfileRecording = true;  // only *AFTER* the header has been written...
        }
    } else {
        g_FFTfileRecording = false;
        FFTRec_btn->SetLabel("FFT Record");
        if(g_NumbFFTFiles == 2) { // Multiple Files
            wxCommandEvent dummy;
            m_FFTFileClassPtr->Flush();
            m_FFTFileClassPtr->Close();
            SuffixFFTFileName();    // rotates the filename for next time
            //if(g_capturingData) {
            //        g_PendingRestartCapture = true;
            //        OnbtnStopCaptureClick(dummy);
            //}
            //OpenFFTfile();
            // file remains closed
        } else {
            m_FFTFileClassPtr->Flush();
            m_FFTFileClassPtr->Close();
            // file remains closed
        }
    }
    FFTRec_btn->Enable(true); // Restore operation from Key Bounce
}


void pnlSpectrum::OnStopFFTRecClick(wxCommandEvent& event)
{ /*

    g_FFTfileRecording = false;
    cout << "FFT Recording Stoped" << endl;
    StopFFTRec->Enable(false);
    if(g_NumbFFTFiles == 2) { // Multiple Files
            wxCommandEvent dummy;
            m_FFTFileClassPtr->Flush();
            m_FFTFileClassPtr->Close();
 //           wrong: m_FileClassPtr->~wxFile(); // Desroy
 //           right: if(m_FileClassPtr != NULL) delete m_FileClassPtr;
 //           m_FileClassPtr = NULL;
            g_FFTfileIsOpen = false;
            SuffixFFTFileName();
            cout << g_FFTfileName << endl;
            if(g_capturingData) {
                    g_PendingRestartCapture = true;
                    OnbtnStopCaptureClick(dummy);
            }
            OpenFFTfile();
    }
    if(g_FFTfileIsOpen && g_capturingData )FFTRec_btn->Enable(true);
        */
}

// TODO: make the default .csv extension a para
static wxString _append_hash_before_ext( wxString s, wxString e = wxT(".csv") )
{
    int p1 = s.Find('#',true);
    int p2 = s.Find('.',true);
    wxString t;
    long v;

    if( p1 == wxNOT_FOUND )     // no # character
    {
        if( p2 == wxNOT_FOUND ) return s+"#1"+e;// s="Example", return="Example#1.csv"
        if( p2 == 0) return "#1"+s;             // s=".csv", return="#1.csv"
        return s.Mid(0,p2)+"#1"+s.Mid(p2);      // s="Example.csv", return="Example#1.csv"
    }
    if( p2 == wxNOT_FOUND )     // no extension
    {
        if( s.Mid(p1+1).ToLong(&v) )
        {
            t.Printf(wxT("%ld"), v+1);
            if( p1 == 0 ) return "#"+t+e;       // s="#1", return="#2.csv"
            return s.Mid(0,p1+1)+t+e;           // s="Example#1", return="Example#2.csv"
        }
        if( p1 == 0 ) return "#1"+e;            // s="#", return="#1.csv"
        return s.Mid(0,p1)+"#1"+e;              // s="Example#garbage", return="Example#1.csv"
    }
    if( p2 == 0 ) return "#1"+s;                // s=".csv", return="#1.csv"
    if( p2 == p1+1 )
    {
        if( p1 == 0 ) return "#1"+e;            // s="#.csv", return="#1.csv"
        return s.Mid(0,p1)+"1"+s.Mid(p2);       // s="Example#.csv", return="Example#1.csv"
    }
    if( s.Mid(p1+1,p2-p1-1).ToLong(&v) )
    {
        t.Printf(wxT("%ld"), v+1);
        return s.Mid(0,p1+1)+t+s.Mid(p2);       // s="Example#1.csv", return="Example#2.csv"
    }
    return s.Mid(0,p1)+"#1"+s.Mid(p2);          // s="Example#garbage.csv", return="Example#1.csv"
}

// add #N in front of .xxx

void pnlSpectrum:: SuffixFFTFileName() {
    wxString s = _append_hash_before_ext( wxString(g_FFTfileName) );
    cout << "SuffixFFTFileName()=" << s << endl;
    wxSnprintf(g_FFTfileName,sizeof(g_FFTfileName)-1,"%s",s);
    g_FFTfileName[sizeof(g_FFTfileName)-1] = 0;
}
void pnlSpectrum:: SuffixPWRFileName() {
    wxString s = _append_hash_before_ext( wxString(g_PWRfileName) );
    cout << "SuffixPWRFileName()=" << s << endl;
    wxSnprintf(g_PWRfileName,sizeof(g_PWRfileName)-1,"%s",s);
    g_PWRfileName[sizeof(g_PWRfileName)-1] = 0;
}

/* NOTE: these didnt work right if you had . and other things in the string
   and this led to invalid filenames that wouldnt open and silently fail...  :(

void pnlSpectrum:: SuffixFFTFileName() {

    char fileName[1024];
    char numstr[80];
    char newnumstr[80];
    int dashnum;
    bool founddot = false;
    bool foundnum = false;
    int j = 0;
    int l = 0;

    wxStrncpy(fileName,g_FFTfileName,1023);
    for(int i = 0; i < 1024 ; i++) {
        if(fileName[i] == '#' && !foundnum) {
            foundnum = true;
            g_FFTfileName[j] = fileName[i];
            j++;
            i++;
            for(int k = i; k < 80 ; k++) {
                if(g_FFTfileName[k] == '.' || g_FFTfileName[k] == 0X00) {
                        numstr[l + 1] = 0X00;
                        i++;
                        break;}
                numstr[l] = g_FFTfileName[k];
                l++;
                i++;
            }
        dashnum = atoi(numstr) + 1; //Increment Suffix
        sprintf(newnumstr,"%d\0",dashnum);
        for(int m = 0; m < 80; m++) {
            if(newnumstr[m] == 0X00)  {
                    g_FFTfileName[j] = '.';
                    j++;
                    break; }
            g_FFTfileName[j] = newnumstr[m];
            j++;
            }
        }
        if(fileName[i] == '.'&& !founddot) {
            founddot = true;
            if(!foundnum) {
                g_FFTfileName[j] = '#';
                g_FFTfileName[j+1] = '2';
                j++;}
            j++;
            }

        if(fileName[i] == 0X00) {
                if(!founddot && !foundnum) { // No file extension or dash
                    g_FFTfileName[j] = '#' ;
                    j++;
                    g_FFTfileName[j] = '2';
                    j++;
                }
                g_FFTfileName[j] = fileName[i];
                break; }// end of string
        g_FFTfileName[j] = fileName[i];
        j++;
    }
    cout << "New File = " << g_FFTfileName << endl;
}

void pnlSpectrum:: SuffixPWRFileName() {

    char fileName[1024];
    char numstr[80];
    char newnumstr[80];
    int dashnum;
    bool founddot = false;
    bool foundnum = false;
    int j = 0;
    int l = 0;
    wxStrncpy(fileName,g_PWRfileName,1023);
    for(int i = 0; i < 1024 ; i++) {
        if(fileName[i] == '#' && !foundnum) {
            foundnum = true;
            g_PWRfileName[j] = fileName[i];
            j++;
            i++;
            for(int k = i; k < 80 ; k++) {
                if(g_PWRfileName[k] == '.' || g_PWRfileName[k] == 0X00) {
                        numstr[l + 1] = 0X00;
                        i++;
                        break;}
                numstr[l] = g_PWRfileName[k];
                l++;
                i++;
            }
        dashnum = atoi(numstr) + 1; //Increment Suffix
        sprintf(newnumstr,"%d\0",dashnum);
        for(int m = 0; m < 80; m++) {
            if(newnumstr[m] == 0X00)  {
                    g_PWRfileName[j] = '.';
                    j++;
                    break; }
            g_PWRfileName[j] = newnumstr[m];
            j++;
            }
        }
        if(fileName[i] == '.'&& !founddot) {
            founddot = true;
            if(!foundnum) {
                g_PWRfileName[j] = '#';
                g_PWRfileName[j+1] = '2';
                j++;}
            j++;
            }

        if(fileName[i] == 0X00) {
                if(!founddot && !foundnum) { // No file extension or dash
                    g_PWRfileName[j] = '#' ;
                    j++;
                    g_PWRfileName[j] = '2';
                    j++;
                }
                g_PWRfileName[j] = fileName[i];
                break; }// end of string
        g_PWRfileName[j] = fileName[i];
        j++;
    }
    cout << "New File = " << g_PWRfileName << endl;

}
*/

void pnlSpectrum::EnableFFTRecord(bool Enabled)
{
    if(Enabled && g_capturingData) FFTRec_btn->Enable(true);
    else FFTRec_btn->Enable(false);
}
void pnlSpectrum::EnablePWRRecord(bool Enabled)
{
    if(Enabled && g_capturingData) RecordPWR->Enable(true);
//    if(Enabled) RecordPWR->Enable(true);
    else RecordPWR->Enable(false);
}
/*
void pnlSpectrum::OnFFTfileYESbtnClick(wxCommandEvent& event)
{
    cout<<"FFTfileOKbtnClick"<<endl;
}
*/
bool pnlSpectrum::OpenFFTfile()
{
    char outbuf[80];
    wxDateTime dt;

    if(g_FFTfileIsDefined) {
        if(m_FFTFileClassPtr == NULL) m_FFTFileClassPtr = new wxFile();
        if(g_OverwriteFFTfile && m_FFTFileClassPtr->Exists(g_FFTfileName)) {
            // support for append mode
            // NB: changes to frequency settings will disable g_FFTfileIsDefined
            //     if necessary, it could be possible to read the file and compare
            //     with the active frequency settings, but that is more work for
            //     a dubious amount of gain.  By disabling g_FFTfileIsDefined,
            //     the GUI will require the user to re-assign the FFT Output file
            m_FFTFileClassPtr->Open(g_FFTfileName,wxFile::write_append,wxS_DEFAULT);
            if(m_FFTFileClassPtr->IsOpened()) return true;
        } else {
            m_FFTFileClassPtr->Create(g_FFTfileName,g_OverwriteFFTfile,wxS_DEFAULT);
            if(m_FFTFileClassPtr->IsOpened()) {
#ifdef _DEBUG
                sprintf(outbuf,"To Record %d Frames Every %d-th Frame\0",g_FFTframesOut, g_FFTframeSkip);
                cout << outbuf << endl;
#endif
                if(g_FFTFileType == 0 && m_FFTsamplesCount > 128){ //Set Max Samps/FRame for Excel
                    int fftsamples = 128;
                    txtFFTsamples->SetValue( wxString::Format("%i", fftsamples));
                    spinFFTsamples->SetValue(7);
                    if(LMLL_Testing_SetFFTSamplesCount(fftsamples))
                    {
                        m_FFTsamplesCount = fftsamples;
 //                       generateFFTxaxis((unsigned long)m_samplingFrequency);
                        generateFFTxaxis(m_samplingFrequency / 1e6);
                        allocateMemory(m_FFTsamplesCount);
                    }
                }
                //if(g_PendingRestartCapture) { //Toggle to Place in effect
                //        btnStartCapture->Enable(true);
                //        OnbtnStartCaptureClick(dummy);
                //        g_PendingRestartCapture = false;
                //        }
                m_FFTFileClassPtr->Write(g_FFTfileName ,wxStrlen((g_FFTfileName)));
                m_FFTFileClassPtr->Write(",,,Created,");
                if(g_FFT_TimeStandard == 0) m_FFTFileClassPtr->Write(dt.Now().FormatDate().c_str()); //Local Time
                else m_FFTFileClassPtr->Write(dt.Now().ToUTC().FormatDate().c_str()); //UT
                m_FFTFileClassPtr->Write(",");
                int offsethour = dt.Now().GetHour() - dt.Now().ToUTC().GetHour();
                if(g_FFT_TimeStandard == 0) wxSprintf(outbuf,"Time Zn,UT%d",offsethour);
                else wxSprintf(outbuf,"Time Zn,UT");
                m_FFTFileClassPtr->Write(outbuf);
                m_FFTFileClassPtr->Write(",\r\n");
                // NB: the frequency plan is written out here
                sprintf(outbuf,"***BEGIN DATA COLLECTION***\r\nKHz\r\n\0");
                m_FFTFileClassPtr->Write(outbuf);
                for(int f = 0; f < m_FFTsamplesCount-1; f++) {
                    if((g_FFTDataSource == 1)
                            && (m_fftxaxisValues[f] >= m_FFTChartCenter - (m_FFTChartSpan/2))
                            && (m_fftxaxisValues[f] <= m_FFTChartCenter + (m_FFTChartSpan/2))) {
                        sprintf(outbuf,",%0.5f\0",m_fftxaxisValues[f]*1e3);
                        m_FFTFileClassPtr->Write(outbuf);
                    } else if(g_FFTDataSource == 0) {
                        sprintf(outbuf,",%0.5f\0",m_fftxaxisValues[f]*1e3);
                        m_FFTFileClassPtr->Write(outbuf);
                    }
                }
                sprintf(outbuf,"\r\n\0");
                m_FFTFileClassPtr->Write(outbuf);
                return true;
            } else {
                cout << "FFT file open Failed" << endl;
            }
        }
    }
    else cout << "FFT filename is not defined" << endl;
    return false;
}

bool pnlSpectrum::OpenPWRfile()
{
    char outbuf[80];
    wxDateTime dt;

    if(g_PWRfileIsDefined) {
        if(m_PWRFileClassPtr == NULL) m_PWRFileClassPtr = new wxFile();
        if(g_OverwritePWRfile && m_PWRFileClassPtr->Exists(g_PWRfileName)) {
            // support for append mode
            m_PWRFileClassPtr->Open(g_PWRfileName,wxFile::write_append,wxS_DEFAULT);
            if(m_PWRFileClassPtr->IsOpened()) return true;
        } else {
            m_PWRFileClassPtr->Create(g_PWRfileName,g_OverwritePWRfile,wxS_DEFAULT);
            if(m_PWRFileClassPtr->IsOpened()) {
                m_PWRFileClassPtr->Write(g_PWRfileName ,wxStrlen((g_PWRfileName)));
                m_PWRFileClassPtr->Write(",,,Created,");
                if(g_PWRTimeStandard == 0) m_PWRFileClassPtr->Write(dt.Now().FormatDate().c_str()); //Local Time
                else m_PWRFileClassPtr->Write(dt.Now().ToUTC().FormatDate().c_str()); //UT
                m_PWRFileClassPtr->Write(",");
                int offsethour = dt.Now().GetHour() - dt.Now().ToUTC().GetHour();
                if(g_PWRTimeStandard == 0) wxSprintf(outbuf,"Time Zn,UT%d",offsethour);
                else wxSprintf(outbuf,"Time Zn,UT");
                m_PWRFileClassPtr->Write(outbuf);
                m_PWRFileClassPtr->Write(",\r\n");
                // Insert Column header line.
                m_PWRFileClassPtr->Write("TIME,ADC PWR (uW),\r\n");
                return true;
            } else {
                cout << "PWR file open Failed" << endl;
            }
        }
    }
    else cout << "PWR filename is not defined" << endl;
    return false;
}

void pnlSpectrum::OnchkUpdateGraphsClick(wxCommandEvent& event)
{
}

void pnlSpectrum::OnoglPWRChartPaint2(wxPaintEvent& event)
{
}

void pnlSpectrum::OnPaint(wxPaintEvent& event)
{
}

void pnlSpectrum::OnPwrRefClick(wxCommandEvent& event)
{
    if(m_PwrRefIsSet) {
        m_PwrRefIsSet = false;
        m_PwrRefOffset = 0;
        m_PwrAccum = 0; //Remove any unused values
        PwrRef->SetLabel("SetPWRRef");
    }
    else {
        m_PwrRefIsSet = true;
        m_PwrRefOffset = g_framepwr;
        PwrRef->SetLabel("ResetPWRRef");
    }
}

void pnlSpectrum::OnPanel5Paint(wxPaintEvent& event)
{
}

void pnlSpectrum::OnPwrSpanChange(wxSpinEvent& event)
{

    char outbuf[80];
    g_PwrSpanSec = 60 * PwrSpan->GetValue();
    m_PWRSpanSecChanged = true;

}

// NOTE: the "quirky" handling of g_PendingRestartCapture
//       and the need to keep the file open after recording
//       has been setup appears to have to do with the desire
//       to not 'glitch' the recording when pressing 'start' recording
//       I think it is misguided.  It would be a heck of a lot simpler
//       to just open the file when you press start and close it when
//       you stop or the recording ends.
void pnlSpectrum::OnPwrRecordClick(wxCommandEvent& event)
{
    RecordPWR->Enable(false); // Avoid Key Bounce
    if(!g_PWRfileRecording) {
        g_PWRfileRecording = OpenPWRfile();
        if(g_PWRfileRecording) RecordPWR->SetLabel("StopPwrRec");
    }
    else {
        g_PWRfileRecording = false;
        RecordPWR->SetLabel("RecordPWR");
        if(g_NumbPWRFiles == 2) { // Multiple Files
            wxCommandEvent dummy;
            m_PWRFileClassPtr->Flush();
            m_PWRFileClassPtr->Close();
            SuffixPWRFileName();    // rotates the filename for next time
            //if(g_capturingData) {
            //    g_PendingRestartCapture = true; // needed by OpenPWRfile() to restart
            //    // OpenPWRfile() does this: OnbtnStopCaptureClick(dummy);
            //}
            //OpenPWRfile();
            // file remains closed
        } else {
            m_PWRFileClassPtr->Flush();
            m_PWRFileClassPtr->Close();
            // file remains closed
        }
    }
    RecordPWR->Enable(true); // Restore operation from Key Bounce
}


void pnlSpectrum::OntxtRxFrequencyMHzText(wxCommandEvent& event)
{
    Apply_btn->Enable(true);
}



void pnlSpectrum::OnIntegration_TimeSelect(wxCommandEvent& event)
{
    int sel;
    sel = Integration_Time->GetSelection();
    if(sel == 0) m_PwrIntTime = 1;
    if(sel == 1) m_PwrIntTime = 5;
    if(sel == 2) m_PwrIntTime = 10;

    }

void pnlSpectrum::OnMaxHoldClick(wxCommandEvent& event)
{
    if(!m_MaxHold) {
        m_MaxHold = true;
        MaxHold->SetLabel("MaxHoldOff");
    }
    else {
        m_MaxHold = false;
        ResetMaxHold();
        MaxHold->SetLabel("MaxHoldFFT");
    }
}
void pnlSpectrum :: ResetMaxHold()
{
    cout<<"REsetMaxHold()" << endl;

    if(m_FFTMaxAmplitudes)
        for( int i = 0;i < m_FFTsamplesCount; i++)
            m_FFTMaxAmplitudes[i] = -1;

}

void pnlSpectrum::OnMaxHoldClick1(wxCommandEvent& event)
{
}
