#include "pnlSpectrum.h"
#include "GUIUtils.h"
#include "ctr_6002dr2_LogicDLL.h"


//(*InternalHeaders(pnlSpectrum)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/spinctrl.h>
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
const long pnlSpectrum::ID_PANEL4 = wxNewId();
const long pnlSpectrum::ID_PANEL3 = wxNewId();
const long pnlSpectrum::ID_SPLITTERWINDOW1 = wxNewId();
const long pnlSpectrum::ID_PANEL9 = wxNewId();
const long pnlSpectrum::ID_BUTTON1 = wxNewId();
const long pnlSpectrum::ID_BUTTON2 = wxNewId();
const long pnlSpectrum::ID_CHECKBOX1 = wxNewId();
const long pnlSpectrum::ID_SPINCTRL4 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT14 = wxNewId();
const long pnlSpectrum::ID_TEXTCTRL3 = wxNewId();
const long pnlSpectrum::ID_SPINBUTTON3 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT15 = wxNewId();
const long pnlSpectrum::ID_SPINCTRL3 = wxNewId();
const long pnlSpectrum::ID_CHECKBOX2 = wxNewId();
const long pnlSpectrum::ID_RADIOBOX1 = wxNewId();
const long pnlSpectrum::ID_RADIOBOX2 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT1 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX1 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT2 = wxNewId();
const long pnlSpectrum::ID_TEXTCTRL1 = wxNewId();
const long pnlSpectrum::ID_SPINBUTTON1 = wxNewId();
const long pnlSpectrum::ID_BUTTON3 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT3 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX2 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT4 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX3 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT5 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX4 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT6 = wxNewId();
const long pnlSpectrum::ID_TEXTCTRL2 = wxNewId();
const long pnlSpectrum::ID_SPINBUTTON2 = wxNewId();
const long pnlSpectrum::ID_BUTTON4 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT7 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX5 = wxNewId();
const long pnlSpectrum::ID_STATICTEXT8 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX6 = wxNewId();
const long pnlSpectrum::ID_COMBOBOX7 = wxNewId();
const long pnlSpectrum::ID_PANEL10 = wxNewId();
const long pnlSpectrum::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSpectrum,wxPanel)
	//(*EventTable(pnlSpectrum)
	//*)
	EVT_TIMER(GRAPH_UPDATE_MESSAGE_ID, pnlSpectrum::UpdateGraphs)
END_EVENT_TABLE()

const int pnlSpectrum::GRAPH_UPDATE_MESSAGE_ID = 100000;

pnlSpectrum::pnlSpectrum(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString str) : m_buffersCount(64)
{
    m_lastUpdate = 0;
    m_capturingData = false;
    m_updating = false;
    m_time = 0;
    m_frames = 0;

    m_addingMarkers = false;
	m_fftxaxisValues = NULL;
	m_TxFreq = 2.200;
	m_RxFreq = 2.199;
	m_frequencyStep = 0.1; //MHz
	m_IchannelData = NULL;
	m_QchannelData = NULL;
	m_FFTfrequencies = NULL;
	m_FFTamplitudes = NULL;
	samplesXaxis = NULL;

    BuildContent(parent,id,pos,size);
    m_FFTsamplesCount = pow(2, spinFFTsamples->GetValue());
    m_samplingFrequency = 1;

    //parameters for FFT results averaging
	m_buffersCountMask = m_buffersCount;
	m_FFTamplitudesBuffer = NULL;

	allocateMemory(m_FFTsamplesCount);
    generateFFTxaxis(spinSamplingFreq->GetValue());

    m_updateTimer = new wxTimer(this, GRAPH_UPDATE_MESSAGE_ID);
}

void pnlSpectrum::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlSpectrum)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(900,600), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMinSize(wxSize(900,500));
	FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetMinSize(wxSize(800,32));
	chkUpdateGraphs = new wxCheckBox(Panel1, ID_CHECKBOX3, _("Update graphs"), wxPoint(32,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkUpdateGraphs->SetValue(true);
	chkIchannelEnabled = new wxCheckBox(Panel1, ID_CHECKBOX4, _("I channel"), wxPoint(144,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkIchannelEnabled->SetValue(true);
	chkQchannelEnabled = new wxCheckBox(Panel1, ID_CHECKBOX5, _("Q channel"), wxPoint(224,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkQchannelEnabled->SetValue(true);
	StaticText9 = new wxStaticText(Panel1, ID_STATICTEXT9, _("Data rate KB/s:"), wxPoint(360,8), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	lblDataRate = new wxStaticText(Panel1, ID_STATICTEXT10, _("0"), wxPoint(440,8), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	lblFPS = new wxStaticText(Panel1, ID_STATICTEXT11, _("30"), wxPoint(720,8), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticText14 = new wxStaticText(Panel1, ID_STATICTEXT16, _("Updates per second:"), wxPoint(608,8), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
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
	ogl_FFTline->SetMinSize(wxSize(-1,150));
	FlexGridSizer2->Add(ogl_FFTline, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(Panel3, ID_PANEL4, wxDefaultPosition, wxSize(800,24), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	Panel4->SetMinSize(wxSize(800,24));
	btnAddMarker = new wxButton(Panel4, ID_BUTTON5, _("Add marker"), wxPoint(416,0), wxSize(139,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	btnRemoveMarker = new wxButton(Panel4, ID_BUTTON6, _("Remove marker"), wxPoint(568,0), wxSize(152,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	StaticText10 = new wxStaticText(Panel4, ID_STATICTEXT12, _("Center Frequency(Hz):"), wxPoint(16,4), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	spinCenterFreq = new wxSpinCtrl(Panel4, ID_SPINCTRL1, _T("0"), wxPoint(128,0), wxSize(72,21), 0, -5000000, 5000000, 0, _T("ID_SPINCTRL1"));
	spinCenterFreq->SetValue(_T("0"));
	StaticText11 = new wxStaticText(Panel4, ID_STATICTEXT13, _("Span(Hz):"), wxPoint(208,4), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	spinSpanFreq = new wxSpinCtrl(Panel4, ID_SPINCTRL2, _T("10000000"), wxPoint(264,0), wxSize(88,21), 0, 10, 10000000, 10000000, _T("ID_SPINCTRL2"));
	spinSpanFreq->SetValue(_T("10000000"));
	FlexGridSizer2->Add(Panel4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel3);
	FlexGridSizer2->SetSizeHints(Panel3);
	SplitterWindow1->SplitHorizontally(SplitterWindow2, Panel3);
	FlexGridSizer1->Add(SplitterWindow1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(500,10), wxSize(800,178), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel8 = new wxPanel(Panel2, ID_PANEL9, wxPoint(752,8), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
	Panel9 = new wxPanel(Panel2, ID_PANEL10, wxPoint(8,8), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
	FlexGridSizer7 = new wxFlexGridSizer(1, 5, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(7, 1, 0, 0);
	btnStartCapture = new wxButton(Panel9, ID_BUTTON1, _("Start capturing samples"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer8->Add(btnStartCapture, 0, wxTOP|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnStopCapture = new wxButton(Panel9, ID_BUTTON2, _("Stop capturing samples"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer8->Add(btnStopCapture, 1, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
	chkAverage = new wxCheckBox(Panel9, ID_CHECKBOX1, _("Average FFT"), wxDefaultPosition, wxSize(88,24), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkAverage->SetValue(false);
	FlexGridSizer12->Add(chkAverage, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	spinAvgCount = new wxSpinCtrl(Panel9, ID_SPINCTRL4, _T("4"), wxDefaultPosition, wxSize(50,21), 0, 1, 128, 4, _T("ID_SPINCTRL4"));
	spinAvgCount->SetValue(_T("4"));
	spinAvgCount->SetToolTip(_("Number of FFT for averaging"));
	FlexGridSizer12->Add(spinAvgCount, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText12 = new wxStaticText(Panel9, ID_STATICTEXT14, _("FFT samples:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer8->Add(StaticText12, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	txtFFTsamples = new wxTextCtrl(Panel9, ID_TEXTCTRL3, _("16384"), wxDefaultPosition, wxSize(56,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer9->Add(txtFFTsamples, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	spinFFTsamples = new wxSpinButton(Panel9, ID_SPINBUTTON3, wxDefaultPosition, wxSize(17,22), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON3"));
	spinFFTsamples->SetValue(14);
	spinFFTsamples->SetRange(2, 16);
	FlexGridSizer9->Add(spinFFTsamples, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer8->Add(FlexGridSizer9, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(Panel9, ID_STATICTEXT15, _("Sampling Frequency(Hz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer8->Add(StaticText13, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	spinSamplingFreq = new wxSpinCtrl(Panel9, ID_SPINCTRL3, _T("10000000"), wxDefaultPosition, wxDefaultSize, 0, 1, 100000000, 10000000, _T("ID_SPINCTRL3"));
	spinSamplingFreq->SetValue(_T("10000000"));
	FlexGridSizer8->Add(spinSamplingFreq, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10 = new wxFlexGridSizer(3, 1, 0, 0);
	chkDCcorrection = new wxCheckBox(Panel9, ID_CHECKBOX2, _("DC correction"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkDCcorrection->SetValue(true);
	FlexGridSizer10->Add(chkDCcorrection, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("NCO"),
		_("ADC")
	};
	rgrDataSource = new wxRadioBox(Panel9, ID_RADIOBOX1, _("Rx Data Source"), wxPoint(144,48), wxDefaultSize, 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrDataSource->SetSelection(1);
	FlexGridSizer10->Add(rgrDataSource, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Off"),
		_("On")
	};
	rgrTxDataSource = new wxRadioBox(Panel9, ID_RADIOBOX2, _("FPGA Transmitter"), wxPoint(144,96), wxSize(104,40), 2, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrTxDataSource->SetSelection(1);
	FlexGridSizer10->Add(rgrTxDataSource, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer10, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel9, _("Tx"));
	FlexGridSizer3 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticText1 = new wxStaticText(Panel9, ID_STATICTEXT1, _("Filter (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbTxFilter = new wxComboBox(Panel9, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbTxFilter->SetSelection( cmbTxFilter->Append(_("5")) );
	cmbTxFilter->Append(_("4.375"));
	cmbTxFilter->Append(_("3.5"));
	cmbTxFilter->Append(_("3"));
	cmbTxFilter->Append(_("2.75"));
	cmbTxFilter->Append(_("2.5"));
	cmbTxFilter->Append(_("1.92"));
	cmbTxFilter->Append(_("1.5"));
	cmbTxFilter->Append(_("1.375"));
	cmbTxFilter->Append(_("1.25"));
	cmbTxFilter->Append(_("0.875"));
	cmbTxFilter->Append(_("0.75"));
	FlexGridSizer3->Add(cmbTxFilter, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel9, ID_STATICTEXT2, _("Frequency (GHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer4->AddGrowableCol(0);
	txtTxFrequencyGHz = new wxTextCtrl(Panel9, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxSize(68,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer4->Add(txtTxFrequencyGHz, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinButton1 = new wxSpinButton(Panel9, ID_SPINBUTTON1, wxDefaultPosition, wxSize(17,24), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON1"));
	SpinButton1->SetRange(0, 100);
	FlexGridSizer4->Add(SpinButton1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetTxFreq = new wxButton(Panel9, ID_BUTTON3, _("Set"), wxDefaultPosition, wxSize(41,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer4->Add(btnSetTxFreq, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel9, ID_STATICTEXT3, _("VGA1 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbTxVGA1 = new wxComboBox(Panel9, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer3->Add(cmbTxVGA1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(Panel9, ID_STATICTEXT4, _("VGA2 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbTxVGA2 = new wxComboBox(Panel9, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	FlexGridSizer3->Add(cmbTxVGA2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer1, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel9, _("Rx"));
	FlexGridSizer5 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticText5 = new wxStaticText(Panel9, ID_STATICTEXT5, _("Filter (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer5->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRxFilter = new wxComboBox(Panel9, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	cmbRxFilter->SetSelection( cmbRxFilter->Append(_("5")) );
	cmbRxFilter->Append(_("4.375"));
	cmbRxFilter->Append(_("3.5"));
	cmbRxFilter->Append(_("3"));
	cmbRxFilter->Append(_("2.75"));
	cmbRxFilter->Append(_("2.5"));
	cmbRxFilter->Append(_("1.92"));
	cmbRxFilter->Append(_("1.5"));
	cmbRxFilter->Append(_("1.375"));
	cmbRxFilter->Append(_("1.25"));
	cmbRxFilter->Append(_("0.875"));
	cmbRxFilter->Append(_("0.75"));
	FlexGridSizer5->Add(cmbRxFilter, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(Panel9, ID_STATICTEXT6, _("Frequency (GHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer5->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	txtRxFrequencyGHz = new wxTextCtrl(Panel9, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(68,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer6->Add(txtRxFrequencyGHz, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinButton2 = new wxSpinButton(Panel9, ID_SPINBUTTON2, wxDefaultPosition, wxSize(17,24), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON2"));
	SpinButton2->SetRange(0, 100);
	FlexGridSizer6->Add(SpinButton2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetRxFreq = new wxButton(Panel9, ID_BUTTON4, _("Set"), wxDefaultPosition, wxSize(41,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer6->Add(btnSetRxFreq, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(Panel9, ID_STATICTEXT7, _("VGA1 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer5->Add(StaticText7, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRxFEVGA1 = new wxComboBox(Panel9, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer5->Add(cmbRxFEVGA1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(Panel9, ID_STATICTEXT8, _("VGA2 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer5->Add(StaticText8, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRxVGA2 = new wxComboBox(Panel9, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	FlexGridSizer5->Add(cmbRxVGA2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer2, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer11 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel9, _("LNA Gain Mode"));
	cmbLNAGainMode = new wxComboBox(Panel9, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	cmbLNAGainMode->Append(_("Bypass"));
	cmbLNAGainMode->Append(_("-6 dB"));
	cmbLNAGainMode->SetSelection( cmbLNAGainMode->Append(_("Max gain")) );
	StaticBoxSizer3->Add(cmbLNAGainMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer11, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
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
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnStartCaptureClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnStopCaptureClick);
	Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlSpectrum::OnspinAvgCountChange);
	Connect(ID_SPINBUTTON3,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&pnlSpectrum::OnspinFFTsamplesChange);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnchkDCcorrectionClick);
	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OnrgrDataSourceSelect);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OnrgrTxDataSourceSelect);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbTxFilterSelected);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&pnlSpectrum::OnSpinButton1ChangeUp);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&pnlSpectrum::OnSpinButton1ChangeDown);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnSetTxFreqClick);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbTxVGA1Selected);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbTxVGA2Selected);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbRxFilterSelected);
	Connect(ID_SPINBUTTON2,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&pnlSpectrum::OnSpinButton2ChangeUp);
	Connect(ID_SPINBUTTON2,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&pnlSpectrum::OnSpinButton2ChangeDown);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSpectrum::OnbtnSetRxFreqClick);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbRxFEVGA1Selected);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbRxVGA2Selected);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSpectrum::OncmbLNAGainModeSelected);
	//*)
	Initialize();
}

pnlSpectrum::~pnlSpectrum()
{
	//free all used memory
    freeMemory();
	if( m_fftxaxisValues)
		delete []m_fftxaxisValues;

	//(*Destroy(pnlSpectrum)
	//*)
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
        ogl_IQline->SetInitialDisplayArea(0, 16384, -2048, 2048);
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


    if(ogl_FFTline)
    {
        ogl_FFTline->settings.useVBO = true;
        ogl_FFTline->AddSeries();
        ogl_FFTline->SetDrawingMode(GLG_LINE);
        ogl_FFTline->settings.gridXlines = 15;
        ogl_FFTline->SetInitialDisplayArea(-5000000, 5000000, -70, 70);

        ogl_FFTline->settings.title = "FFT";
        ogl_FFTline->settings.marginLeft = 75;
        ogl_FFTline->settings.marginBottom = 35;
        ogl_FFTline->settings.titleXaxis = "Frequency";
        ogl_FFTline->settings.titleYaxis = "Amplitude";
        ogl_FFTline->settings.xUnits = " Hz";
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

	m_FFTamplitudesBuffer = new float*[m_buffersCount+1];
	for(int i=0; i<m_buffersCount+1; i++)
		m_FFTamplitudesBuffer[i] = new float[m_FFTsamplesCount];
	bufferPos = 0;
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

    if(m_FFTamplitudesBuffer)
    {
        for(int i=0; i<m_buffersCount; ++i)
            delete []m_FFTamplitudesBuffer[i];
        delete []m_FFTamplitudes;
    }
    m_FFTamplitudesBuffer = NULL;
}

/**
	@brief Initializes GUI elements
*/
void pnlSpectrum::Initialize()
{
    initializeInterfaceValues();
	char ctemp[80];
	sprintf(ctemp, "%2.3f", m_TxFreq);
	txtTxFrequencyGHz->SetValue(ctemp);
	sprintf(ctemp, "%2.3f", m_RxFreq);
	txtRxFrequencyGHz->SetValue(ctemp);

	m_buffersCountMask = spinAvgCount->GetValue();

	initializeGraphs();
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
	LMLL_TxRfSetPA(1);
	LMAL_SelectActiveLNA(1);
	LMLL_TopSetRXOUTSW(0);

	SendSettings();
	LMLL_Testing_SetRxDataSource(rgrDataSource->GetSelection());
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
    StartCapturing();
}

/**
	@brief Stops samples capturing
*/
void pnlSpectrum::OnbtnStopCaptureClick(wxCommandEvent& event)
{
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
    LMLL_Testing_SetDCCorrection(chkDCcorrection->GetValue());
}

void pnlSpectrum::OnrgrDataSourceSelect(wxCommandEvent& event)
{
    int selection = rgrDataSource->GetSelection();
    LMLL_Testing_SetRxDataSource(selection);
}

void pnlSpectrum::OnrgrTxDataSourceSelect(wxCommandEvent& event)
{
    LMLL_Testing_SetTxDataSource(rgrTxDataSource->GetSelection());
}

void pnlSpectrum::OnComboBox1Selected(wxCommandEvent& event)
{
    LMLL_RxFESetG_LNA_RXFE(cmbLNAGainMode->GetSelection());
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
	cmbTxVGA1->Clear();
	for(int i=-35; i<=-4; i++)
	{
        cs_Numbers[i+35] = wxString::Format("%i", i);
	}
    cmbTxVGA1->Append( 32, cs_Numbers);
	cmbTxVGA1->SetSelection(18);   // -14 dB

	for(int i=0; i<=25; i++)
	{
        cs_Numbers[i] = wxString::Format("%i", i);
	}
	cmbTxVGA2->Append( 25, cs_Numbers);
	cmbTxVGA2->SetSelection(0);

	for(int i=0; i<=30; i+=3)
	{
        cs_Numbers[i/3] = wxString::Format("%i", i);
	}
	cmbRxVGA2->Append( 11, cs_Numbers);
	cmbRxVGA2->SetSelection(1);

	char ctemp[32];

	for(int i=0; i<=120; i++)
	    cs_Numbers[i] = wxString::Format("%.2f", 20*log10((float)127/(127-i)));
	cmbRxFEVGA1->Append(121, cs_Numbers);
	cmbRxFEVGA1->SetSelection(120);
	LMAL_MainSetAutoDownload(true);
}

/**
	@brief Generates frequency values for FFT graph
	@param samplingFreq sampling frequency in Hz
*/
void pnlSpectrum::generateFFTxaxis(unsigned long samplingFreq)
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
}

/**
    @brief Changes FFT amplitudes graph x axis values depending on sampling frequency
    @param samplingFrequency sampling frequency in Hz
*/
void pnlSpectrum::changeSamplingFrequency(long samplingFrequency)
{
    if(m_fftxaxisValues)
    {
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

void pnlSpectrum::OncmbTxFilterSelected(wxCommandEvent& event)
{
    LMLL_TxLPFSetLpfBw(cmbTxFilter->GetSelection()+4); // +4 because this combobox has not all items
}

void pnlSpectrum::OncmbRxFilterSelected(wxCommandEvent& event)
{
    LMLL_RxLPFSetLpfBw(cmbRxFilter->GetSelection()+4); // +4 because this combobox has not all items
}

void pnlSpectrum::OncmbTxVGA1Selected(wxCommandEvent& event)
{
    LMLL_TxRfSetVga1G_u(cmbTxVGA1->GetSelection());
}

void pnlSpectrum::OncmbTxVGA2Selected(wxCommandEvent& event)
{
    LMLL_TxRfSetVga2G_u(cmbTxVGA2->GetSelection());
}

void pnlSpectrum::OncmbRxFEVGA1Selected(wxCommandEvent& event)
{
    LMLL_RxFESetRFB_TIA_RXFE(cmbRxFEVGA1->GetSelection());
}

void pnlSpectrum::OncmbRxVGA2Selected(wxCommandEvent& event)
{
    LMLL_RxVGA2SetVga2G_u(cmbRxVGA2->GetSelection());
}

void pnlSpectrum::OncmbLNAGainModeSelected(wxCommandEvent& event)
{
    LMLL_RxFESetG_LNA_RXFE(cmbLNAGainMode->GetSelection());
}

/**
    @brief Configures receiver frequency
*/
void pnlSpectrum::OnbtnSetRxFreqClick(wxCommandEvent& event)
{
    double freq;
    txtRxFrequencyGHz->GetValue().ToDouble(&freq);
	m_RxFreq = freq;
	if( m_RxFreq > 0.2 && m_RxFreq < 5)
		LMAL_RxPLL_SetFrequency(m_RxFreq);
	else
	{
		m_RxFreq = 0.3;
		txtRxFrequencyGHz->SetValue( wxString::Format("%f", 0.3));
	}
}

/**
    @brief Configures transmitter frequency
*/
void pnlSpectrum::OnbtnSetTxFreqClick(wxCommandEvent& event)
{
    double freq;
    txtTxFrequencyGHz->GetValue().ToDouble(&freq);
	m_TxFreq = freq;
	if( m_TxFreq > 0.2 && m_TxFreq < 5)
		LMAL_TxPLL_SetFrequency(m_TxFreq);
	else
	{
		m_TxFreq = 0.3;
		txtTxFrequencyGHz->SetValue( wxString::Format("%f", 0.3));
	}
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


	LMLL_TxLPFSetLpfBw(cmbTxFilter->GetSelection()+4);
	LMLL_RxLPFSetLpfBw(cmbRxFilter->GetSelection()+4);

	LMLL_Testing_SetRxDataSource(rgrDataSource->GetSelection());
	LMLL_TopSetPwrSoftTx(true);
	LMLL_TopSetPwrSoftRx(true);
	LMLL_Testing_SetTxDataSource(rgrTxDataSource->GetSelection());

	LMLL_RxFESetRFB_TIA_RXFE(cmbRxFEVGA1->GetSelection());
	LMLL_RxVGA2SetVga2G_u(cmbRxVGA2->GetSelection());
	LMAL_RxPLL_SetFrequency(m_RxFreq);
	LMAL_CalibrateRx();

	LMLL_TxRfSetVga1G_u(cmbTxVGA1->GetSelection());
	LMLL_TxRfSetVga2G_u(cmbTxVGA2->GetSelection());
	LMAL_TxPLL_SetFrequency(m_TxFreq);
	LMAL_CalibrateTx();

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

	cmbTxFilter->SetSelection(LMLL_TxLPFGetLpfBw()-4);
	cmbRxFilter->SetSelection(LMLL_RxLPFGetLpfBw()-4);
	//rgrRxOUTSW->SetSelection(LMLL_TopGetRXOUTSW());
	//cmbPA->SetSelection(LMLL_TxRfGetPA());
   	//cmbLNA->SetSelection(LMLL_RxFEGetLNASEL_RXFE());
	cmbTxVGA1->SetSelection(LMLL_TxRfGetVga1G_u());
	cmbTxVGA2->SetSelection(LMLL_TxRfGetVga2G_u());
	cmbRxFEVGA1->SetSelection(LMLL_RxFEGetRFB_TIA_RXFE());
	cmbRxVGA2->SetSelection(LMLL_RxVGA2GetVga2G_u());
	//cmbRefGainAdj->SetSelection(LMLL_ADDCGetRefGainAdj());

	float freq = LMLL_TxPLLGetFrequency();
	m_TxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtTxFrequencyGHz->SetValue(ctemp);

	freq = LMLL_RxPLLGetFrequency();
	m_RxFreq = freq;
	sprintf(ctemp, "%2.3f", freq);
	txtRxFrequencyGHz->SetValue(ctemp);

	LMAL_MainSetAutoDownload(true);
	//LMAL_MainDownload();
}

void pnlSpectrum::OnSpinButton1ChangeUp(wxSpinEvent& event)
{
	double freq;
	txtTxFrequencyGHz->GetValue().ToDouble(&freq);
	freq += m_frequencyStep;
	m_TxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtTxFrequencyGHz->SetValue(ctemp);
}

void pnlSpectrum::OnSpinButton1ChangeDown(wxSpinEvent& event)
{
    double freq;
	txtTxFrequencyGHz->GetValue().ToDouble(&freq);
	freq -= m_frequencyStep;
	m_TxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtTxFrequencyGHz->SetValue(ctemp);
}

void pnlSpectrum::OnSpinButton2ChangeUp(wxSpinEvent& event)
{
    double freq;
	txtRxFrequencyGHz->GetValue().ToDouble(&freq);
	freq += m_frequencyStep;
	m_RxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtRxFrequencyGHz->SetValue(ctemp);
}

void pnlSpectrum::OnSpinButton2ChangeDown(wxSpinEvent& event)
{
    double freq;
	txtRxFrequencyGHz->GetValue().ToDouble(&freq);
	freq -= m_frequencyStep;
	m_RxFreq = freq;
	char ctemp[80];
	sprintf(ctemp, "%2.3f", freq);
	txtRxFrequencyGHz->SetValue(ctemp);
}

/**
    @brief Initiates data samples capturing
*/
void pnlSpectrum::StartCapturing()
{
    changeSamplingFrequency(spinSamplingFreq->GetValue());
    LMLL_TopSetPwrSoftTx(true);
	LMLL_TopSetPwrSoftRx(true);
    LMLL_Testing_StartSdramRead();
    m_capturingData = true;

    if(spinAvgCount->GetValue() < m_buffersCount)
        m_buffersCountMask = spinAvgCount->GetValue();
    else
    {
        spinAvgCount->SetValue(m_buffersCount);
        m_buffersCountMask = m_buffersCount;
    }

    int interval = 15;
    m_updateTimer->Start(interval);
	btnStartCapture->Enable(false);
	btnStopCapture->Enable(true);
	spinFFTsamples->Enable(false);
	spinSamplingFreq->Enable(false);
}

/**
    @brief Stops data samples capturing
*/
void pnlSpectrum::StopCapturing()
{
    //stop graphs update thread
    m_updateTimer->Stop();

    LMLL_Testing_StopSdramRead();
    btnStartCapture->Enable(true);
	btnStopCapture->Enable(false);
	spinFFTsamples->Enable(true);
	spinSamplingFreq->Enable(true);
	m_capturingData = false;
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
    ogl_FFTline->ZoomX(spinCenterFreq->GetValue(), spinSpanFreq->GetValue());
}

void pnlSpectrum::OnspinSpanFreqChange(wxSpinEvent& event)
{
    ogl_FFTline->ZoomX(spinCenterFreq->GetValue(), spinSpanFreq->GetValue());
}

/**
    @brief Changes FFT samples count used for calculations
*/
void pnlSpectrum::OnspinFFTsamplesChange(wxSpinEvent& event)
{
    int power = spinFFTsamples->GetValue();
    int fftsamples = pow(2, power);
    txtFFTsamples->SetValue( wxString::Format("%i", fftsamples));
    if(LMLL_Testing_SetFFTSamplesCount(fftsamples))
    {
        m_FFTsamplesCount = fftsamples;
        generateFFTxaxis(m_samplingFrequency);
        allocateMemory(m_FFTsamplesCount);
    }
}

/**
    @brief Calculates FFT and redraws graphs
*/
void pnlSpectrum::UpdateGraphs(wxTimerEvent &event)
{
    if(m_updating)
        return;
    m_updating = true;


	int fftsLeft = 0; // FFT results left in queue

	bool averageFFT = chkAverage->GetValue();
	bool calculated = false;

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
                LMLL_Testing_GetFFTData(m_IchannelData,
                                          m_QchannelData,
                                          m_IQdataSize,
                                          m_FFTamplitudes,
                                          m_FFTdataSize,
                                          fftsLeft);

                //convert FFT results to dB
                for(int i=0; i<m_FFTdataSize; i++)
                {
                    if( m_FFTamplitudes[i] <= 0)
                        m_FFTamplitudes[i] = -370;
                    else
                        m_FFTamplitudes[i] = 10 * log10( m_FFTamplitudes[i] );
                }
            }
        }
	}
	else
	{
        if(chkUpdateGraphs->GetValue() == true)
        {
            calculated = LMLL_Testing_CalculateFFT();
            if(calculated)
            {
                //takes one FFT results and add it to averaging buffer
                LMLL_Testing_GetFFTData(m_IchannelData, m_QchannelData, m_IQdataSize, m_FFTamplitudesBuffer[bufferPos], m_FFTdataSize, fftsLeft);
                bufferPos = (bufferPos + 1) % m_buffersCountMask;

                memset(m_FFTamplitudesBuffer[m_buffersCount], 0, sizeof(float)*m_FFTsamplesCount);
                //calculate average
                for(int i=0; i<m_buffersCountMask; ++i)
                {
                    for(int j=0; j<m_FFTsamplesCount; ++j)
                        m_FFTamplitudesBuffer[m_buffersCount][j] += m_FFTamplitudesBuffer[bufferPos][j];
                    bufferPos = (bufferPos + 1) % m_buffersCountMask;
                }
                for(int j=0; j<m_FFTsamplesCount; ++j)
                    m_FFTamplitudesBuffer[m_buffersCount][j] = m_FFTamplitudesBuffer[m_buffersCount][j]/m_buffersCountMask;

                //convert to dB
                for(int i=0; i<m_FFTdataSize; i++)
                {
                    if( m_FFTamplitudesBuffer[m_buffersCount][i] <= 0)
                        m_FFTamplitudes[i] = -370;
                    else
                        m_FFTamplitudes[i] = 10 * log10( m_FFTamplitudesBuffer[m_buffersCount][i] );
                }
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
		ogl_FFTline->series[0]->AssignValues(m_fftxaxisValues, m_FFTamplitudes, m_FFTdataSize);
		ogl_FFTline->Refresh();
		ogl_IQscatter->Refresh();
		ogl_IQline->Refresh();
	}
	++m_frames;
	m_time += GetTickCount()-m_lastUpdate;
	if(m_time >= 1000)
    {
        lblFPS->SetLabel( wxString::Format("%i", m_frames));
        m_frames = 0;
        m_time = 0;
    }
	m_lastUpdate = GetTickCount();
    m_updating = false;
}

bool pnlSpectrum::IsCapturingData()
{
    return m_capturingData;
}

void pnlSpectrum::OnspinAvgCountChange(wxSpinEvent& event)
{
    if(spinAvgCount->GetValue() < m_buffersCount)
        m_buffersCountMask = spinAvgCount->GetValue();
    else
    {
        spinAvgCount->SetValue(m_buffersCount);
        m_buffersCountMask = m_buffersCount;
    }
}
