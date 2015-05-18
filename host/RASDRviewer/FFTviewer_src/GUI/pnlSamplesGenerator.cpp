#include "pnlSamplesGenerator.h"
#include "ctr_6002dr2_LogicDLL.h"

#include <sstream>
using namespace std;

//(*InternalHeaders(pnlSamplesGenerator)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/glcanvas.h>
#include <wx/spinctrl.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlSamplesGenerator)
const long pnlSamplesGenerator::ID_RADIOBOX1 = wxNewId();
const long pnlSamplesGenerator::ID_BUTTON1 = wxNewId();
const long pnlSamplesGenerator::ID_BUTTON2 = wxNewId();
const long pnlSamplesGenerator::ID_BUTTON3 = wxNewId();
const long pnlSamplesGenerator::ID_STATICTEXT1 = wxNewId();
const long pnlSamplesGenerator::ID_TEXTCTRL1 = wxNewId();
const long pnlSamplesGenerator::ID_STATICTEXT2 = wxNewId();
const long pnlSamplesGenerator::ID_SPINCTRL1 = wxNewId();
const long pnlSamplesGenerator::ID_STATICTEXT3 = wxNewId();
const long pnlSamplesGenerator::ID_SPINCTRL2 = wxNewId();
const long pnlSamplesGenerator::ID_PANEL1 = wxNewId();
const long pnlSamplesGenerator::ID_GLCANVAS1 = wxNewId();
const long pnlSamplesGenerator::ID_PANEL2 = wxNewId();
const long pnlSamplesGenerator::ID_STATICTEXT4 = wxNewId();
const long pnlSamplesGenerator::ID_STATICTEXT5 = wxNewId();
const long pnlSamplesGenerator::ID_TEXTCTRL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSamplesGenerator,wxPanel)
	//(*EventTable(pnlSamplesGenerator)
	//*)
END_EVENT_TABLE()

pnlSamplesGenerator::pnlSamplesGenerator(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString str)
{
    m_isamples = NULL;
    m_qsamples = NULL;
    m_xaxis = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlSamplesGenerator::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlSamplesGenerator)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxSize(779,400), wxTAB_TRAVERSAL, _T("id"));
	wxString __wxRadioBoxChoices_1[5] =
	{
		_("Signal generator"),
		_("Text File"),
		_("Binary File"),
		_("Square"),
		_("Hex input")
	};
	rgrDataSource = new wxRadioBox(this, ID_RADIOBOX1, _("Data Source:"), wxPoint(8,8), wxDefaultSize, 5, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrDataSource->SetSelection(4);
	btnStartGenerating = new wxButton(this, ID_BUTTON1, _("Start Transmitting Samples"), wxPoint(128,16), wxSize(144,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnStopGenerating = new wxButton(this, ID_BUTTON2, _("Stop Transmitting Samples"), wxPoint(128,56), wxSize(144,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnOpenFile = new wxButton(this, ID_BUTTON3, _("Generate"), wxPoint(8,160), wxSize(112,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(8,190), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Frequency:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("2.5"), wxDefaultPosition, wxSize(52,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(txtFreq, 1, wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Amplitude:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	spinAmplitude = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("1024"), wxDefaultPosition, wxSize(63,21), 0, 0, 2048, 1024, _T("ID_SPINCTRL1"));
	spinAmplitude->SetValue(_T("1024"));
	FlexGridSizer1->Add(spinAmplitude, 1, wxTOP|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("SamplingRate:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	spinSamplingRate = new wxSpinCtrl(Panel1, ID_SPINCTRL2, _T("100"), wxDefaultPosition, wxDefaultSize, 0, 0, 10000000, 100, _T("ID_SPINCTRL2"));
	spinSamplingRate->SetValue(_T("100"));
	FlexGridSizer1->Add(spinSamplingRate, 1, wxTOP|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);
	Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(280,16), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	int GLCanvasAttributes_1[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE,      16,
		WX_GL_STENCIL_SIZE,    0,
		0, 0 };
	glSignalGraph = new OpenGLGraph(Panel2, ID_GLCANVAS1, wxDefaultPosition, wxSize(430,156), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
	glSignalGraph->SetMinSize(wxSize(400,150));
	FlexGridSizer2->Add(glSignalGraph, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel2);
	FlexGridSizer2->SetSizeHints(Panel2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("CURRENTLY NOT TESTED!"), wxPoint(288,192), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Hex input:"), wxPoint(224,240), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	txtHexInput = new wxTextCtrl(this, ID_TEXTCTRL2, _("FF FF 00 00"), wxPoint(280,238), wxSize(408,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlSamplesGenerator::OnrgrDataSourceSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSamplesGenerator::OnbtnStartGeneratingClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSamplesGenerator::OnbtnStopGeneratingClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSamplesGenerator::OnbtnOpenFileClick);
	//*)

	glSignalGraph->settings.useVBO = false;
    glSignalGraph->AddSeries();
    glSignalGraph->AddSeries();
    glSignalGraph->SetInitialDisplayArea(0, 128, -2048, 2048);
    glSignalGraph->settings.marginLeft = 80;
    glSignalGraph->settings.marginBottom = 35;
    glSignalGraph->settings.title = "IQ samples";
    glSignalGraph->series[0]->color = 0xFF0000FF;
    glSignalGraph->series[1]->color = 0x0000FFFF;
}

pnlSamplesGenerator::~pnlSamplesGenerator()
{
	//(*Destroy(pnlSamplesGenerator)
	//*)
}

void pnlSamplesGenerator::OnrgrDataSourceSelect(wxCommandEvent& event)
{
    switch( rgrDataSource->GetSelection() )
    {
    case 0:
        btnOpenFile->SetLabel("Generate");
        break;
    case 1:
        btnOpenFile->SetLabel("Open file");
        break;
    case 2:
        btnOpenFile->SetLabel("Open file");
        break;
    case 3:
        btnOpenFile->SetLabel("Generate");
        break;
    }
}



void pnlSamplesGenerator::OnbtnStartGeneratingClick(wxCommandEvent& event)
{
    if( rgrDataSource->GetSelection() == 4)
    {
        vector<unsigned char> pattern;
        unsigned int sample = 0;
        stringstream ss;
        ss.str( txtHexInput->GetValue().ToStdString() );
        while(!ss.eof())
        {
            ss >> hex >> sample;
            pattern.push_back(sample&0xFF);
        }
        LMLL_Transmitter_LoadSamplesFromArray(&pattern[0], pattern.size());
    }
    LMLL_Transmitter_StartSendingSamples();
}

void pnlSamplesGenerator::OnbtnStopGeneratingClick(wxCommandEvent& event)
{
    LMLL_Transmitter_StopSendingSamples();
}

void pnlSamplesGenerator::OnbtnOpenFileClick(wxCommandEvent& event)
{
    if( rgrDataSource->GetSelection() == 0)
    {
        double freq = 0;
        txtFreq->GetValue().wxString::ToDouble(&freq);
        double amp = 0;
        amp = spinAmplitude->GetValue();
        double samplingRate = 0;
        samplingRate = spinSamplingRate->GetValue();
        LMLL_Transmitter_GenerateSamples( freq, amp, samplingRate);
    }
    else if( rgrDataSource->GetSelection() == 3)
    {
        LMLL_Transmitter_GenerateSamples( 4, 2048, 16);
    }
    else
    {
        wxFileDialog *openFileDialog = new wxFileDialog(this, _("Open samples file"), "", "", "txt (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        if (openFileDialog->ShowModal() == wxID_CANCEL)
            return;

        if(rgrDataSource->GetSelection() == 1)
            LMLL_Transmitter_LoadSamplesFromFile( (char*)openFileDialog->GetPath().ToStdString().c_str(), false);
        else if(rgrDataSource->GetSelection() == 2)
            LMLL_Transmitter_LoadSamplesFromFile( (char*)openFileDialog->GetPath().ToStdString().c_str(), true);
    }
    if(m_isamples)
        delete m_isamples;
    if(m_qsamples)
        delete m_qsamples;
    if(m_xaxis)
        delete m_xaxis;

    int samplesCount = 0;
    LMLL_Transmitter_GetSamples(NULL, NULL, samplesCount);
    m_isamples = new float[samplesCount];
    m_qsamples = new float[samplesCount];
    m_xaxis = new float[samplesCount];
    for(int i=0; i<samplesCount; i++)
        m_xaxis[i] = i;
    LMLL_Transmitter_GetSamples(m_isamples, m_qsamples, samplesCount);
    glSignalGraph->series[0]->AssignValues(m_xaxis, m_isamples, samplesCount);
    glSignalGraph->series[1]->AssignValues(m_xaxis, m_qsamples, samplesCount);
    glSignalGraph->Draw();
}
