#include "pnlBoard.h"
#include "ctr_6002dr2_LogicDLL.h"


//(*InternalHeaders(pnlBoard)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

#include <wx/filedlg.h>

//(*IdInit(pnlBoard)
const long pnlBoard::ID_BUTTON3 = wxNewId();
const long pnlBoard::ID_BUTTON4 = wxNewId();
const long pnlBoard::ID_RADIOBOX5 = wxNewId();
const long pnlBoard::ID_RADIOBOX6 = wxNewId();
const long pnlBoard::ID_STATICTEXT2 = wxNewId();
const long pnlBoard::ID_TEXTCTRL2 = wxNewId();
const long pnlBoard::ID_CHECKBOX4 = wxNewId();
const long pnlBoard::ID_STATICLINE1 = wxNewId();
const long pnlBoard::ID_STATICTEXT4 = wxNewId();
const long pnlBoard::ID_TEXTCTRL4 = wxNewId();
const long pnlBoard::ID_CHECKBOX2 = wxNewId();
const long pnlBoard::ID_CHECKBOX3 = wxNewId();
const long pnlBoard::ID_RADIOBOX1 = wxNewId();
const long pnlBoard::ID_PANEL2 = wxNewId();
const long pnlBoard::ID_CHECKBOX5 = wxNewId();
const long pnlBoard::ID_STATICLINE2 = wxNewId();
const long pnlBoard::ID_STATICTEXT1 = wxNewId();
const long pnlBoard::ID_TEXTCTRL1 = wxNewId();
const long pnlBoard::ID_CHECKBOX1 = wxNewId();
const long pnlBoard::ID_CHECKBOX6 = wxNewId();
const long pnlBoard::ID_RADIOBOX2 = wxNewId();
const long pnlBoard::ID_PANEL5 = wxNewId();
const long pnlBoard::ID_CHECKBOX7 = wxNewId();
const long pnlBoard::ID_STATICLINE3 = wxNewId();
const long pnlBoard::ID_STATICTEXT3 = wxNewId();
const long pnlBoard::ID_TEXTCTRL3 = wxNewId();
const long pnlBoard::ID_CHECKBOX9 = wxNewId();
const long pnlBoard::ID_CHECKBOX10 = wxNewId();
const long pnlBoard::ID_RADIOBOX3 = wxNewId();
const long pnlBoard::ID_PANEL6 = wxNewId();
const long pnlBoard::ID_CHECKBOX8 = wxNewId();
const long pnlBoard::ID_STATICLINE4 = wxNewId();
const long pnlBoard::ID_STATICTEXT5 = wxNewId();
const long pnlBoard::ID_TEXTCTRL5 = wxNewId();
const long pnlBoard::ID_CHECKBOX13 = wxNewId();
const long pnlBoard::ID_CHECKBOX14 = wxNewId();
const long pnlBoard::ID_RADIOBOX4 = wxNewId();
const long pnlBoard::ID_PANEL7 = wxNewId();
const long pnlBoard::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlBoard,wxPanel)
	//(*EventTable(pnlBoard)
	//*)
END_EVENT_TABLE()

pnlBoard::pnlBoard(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
	BuildContent(parent,id,pos,size);
}

void pnlBoard::Initialize()
{
}

void pnlBoard::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlBoard)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxSize(824,195), wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Si5356A"));
	btnConfigureSi5356A = new wxButton(this, ID_BUTTON3, _("Upload register map to Si5356A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	StaticBoxSizer2->Add(btnConfigureSi5356A, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnLoadFile = new wxButton(this, ID_BUTTON4, _("Load register map from file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticBoxSizer2->Add(btnLoadFile, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Crystal"),
		_("CLKIN")
	};
	rgrRefClkSelect = new wxRadioBox(this, ID_RADIOBOX5, _("Reference Clock"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX5"));
	rgrRefClkSelect->SetSelection(1);
	FlexGridSizer7->Add(rgrRefClkSelect, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8 = new wxFlexGridSizer(1, 2, 0, 0);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("27 MHz"),
		_("25 MHz")
	};
	rgrCrystalFreq = new wxRadioBox(this, ID_RADIOBOX6, _("Crystal Frequency"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX6"));
	rgrCrystalFreq->SetSelection(0);
	FlexGridSizer8->Add(rgrCrystalFreq, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("CLKIN (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer9->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	txtRefClk = new wxTextCtrl(this, ID_TEXTCTRL2, _("30.72"), wxDefaultPosition, wxSize(72,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer9->Add(txtRefClk, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer8->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
	Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(240,50), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("Clock 0/1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVAen = new wxCheckBox(Panel2, ID_CHECKBOX4, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkDRVAen->SetValue(true);
	FlexGridSizer1->Add(chkDRVAen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(Panel2, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(Panel2, ID_STATICTEXT4, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVAfreq = new wxTextCtrl(Panel2, ID_TEXTCTRL4, _("20"), wxDefaultPosition, wxSize(82,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer1->Add(txtDRVAfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVAInvertEven = new wxCheckBox(Panel2, ID_CHECKBOX2, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkDRVAInvertEven->SetValue(false);
	FlexGridSizer1->Add(chkDRVAInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVAInvertOdd = new wxCheckBox(Panel2, ID_CHECKBOX3, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkDRVAInvertOdd->SetValue(false);
	FlexGridSizer1->Add(chkDRVAInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVAoutput = new wxRadioBox(Panel2, ID_RADIOBOX1, _("Output Signal"), wxDefaultPosition, wxSize(197,40), 3, __wxRadioBoxChoices_3, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrDRVAoutput->SetSelection(2);
	StaticBoxSizer1->Add(rgrDRVAoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(StaticBoxSizer1);
	StaticBoxSizer1->Fit(Panel2);
	StaticBoxSizer1->SetSizeHints(Panel2);
	FlexGridSizer2->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel5 = new wxPanel(this, ID_PANEL5, wxPoint(240,50), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel5, _("DAC Clock"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVBen = new wxCheckBox(Panel5, ID_CHECKBOX5, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkDRVBen->SetValue(true);
	FlexGridSizer3->Add(chkDRVBen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine2 = new wxStaticLine(Panel5, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	FlexGridSizer3->Add(StaticLine2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(Panel5, ID_STATICTEXT1, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVBfreq = new wxTextCtrl(Panel5, ID_TEXTCTRL1, _("20"), wxDefaultPosition, wxSize(82,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(txtDRVBfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVBInvertEven = new wxCheckBox(Panel5, ID_CHECKBOX1, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkDRVBInvertEven->SetValue(false);
	FlexGridSizer3->Add(chkDRVBInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVBInvertOdd = new wxCheckBox(Panel5, ID_CHECKBOX6, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkDRVBInvertOdd->SetValue(false);
	FlexGridSizer3->Add(chkDRVBInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVBoutput = new wxRadioBox(Panel5, ID_RADIOBOX2, _("Output Signal"), wxDefaultPosition, wxSize(197,40), 3, __wxRadioBoxChoices_4, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrDRVBoutput->SetSelection(2);
	StaticBoxSizer3->Add(rgrDRVBoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel5->SetSizer(StaticBoxSizer3);
	StaticBoxSizer3->Fit(Panel5);
	StaticBoxSizer3->SetSizeHints(Panel5);
	FlexGridSizer2->Add(Panel5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6 = new wxPanel(this, ID_PANEL6, wxPoint(240,50), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, Panel6, _("ADC Clock"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVCen = new wxCheckBox(Panel6, ID_CHECKBOX7, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkDRVCen->SetValue(true);
	FlexGridSizer4->Add(chkDRVCen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine3 = new wxStaticLine(Panel6, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
	FlexGridSizer4->Add(StaticLine3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel6, ID_STATICTEXT3, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer4->Add(StaticText3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVCfreq = new wxTextCtrl(Panel6, ID_TEXTCTRL3, _("20"), wxDefaultPosition, wxSize(82,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer4->Add(txtDRVCfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVCInvertEven = new wxCheckBox(Panel6, ID_CHECKBOX9, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkDRVCInvertEven->SetValue(false);
	FlexGridSizer4->Add(chkDRVCInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVCInvertOdd = new wxCheckBox(Panel6, ID_CHECKBOX10, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkDRVCInvertOdd->SetValue(false);
	FlexGridSizer4->Add(chkDRVCInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVCoutput = new wxRadioBox(Panel6, ID_RADIOBOX3, _("Output Signal"), wxDefaultPosition, wxSize(197,40), 3, __wxRadioBoxChoices_5, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX3"));
	rgrDRVCoutput->SetSelection(2);
	StaticBoxSizer4->Add(rgrDRVCoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6->SetSizer(StaticBoxSizer4);
	StaticBoxSizer4->Fit(Panel6);
	StaticBoxSizer4->SetSizeHints(Panel6);
	FlexGridSizer2->Add(Panel6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7 = new wxPanel(this, ID_PANEL7, wxPoint(240,50), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, Panel7, _("Clock 6/7"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVDen = new wxCheckBox(Panel7, ID_CHECKBOX8, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkDRVDen->SetValue(true);
	FlexGridSizer5->Add(chkDRVDen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine4 = new wxStaticLine(Panel7, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
	FlexGridSizer5->Add(StaticLine4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(Panel7, ID_STATICTEXT5, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer5->Add(StaticText5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVDfreq = new wxTextCtrl(Panel7, ID_TEXTCTRL5, _("20"), wxDefaultPosition, wxSize(82,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer5->Add(txtDRVDfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVDInvertEven = new wxCheckBox(Panel7, ID_CHECKBOX13, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkDRVDInvertEven->SetValue(false);
	FlexGridSizer5->Add(chkDRVDInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVDInvertOdd = new wxCheckBox(Panel7, ID_CHECKBOX14, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chkDRVDInvertOdd->SetValue(false);
	FlexGridSizer5->Add(chkDRVDInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_6[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVDoutput = new wxRadioBox(Panel7, ID_RADIOBOX4, _("Output Signal"), wxDefaultPosition, wxSize(197,40), 3, __wxRadioBoxChoices_6, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX4"));
	rgrDRVDoutput->SetSelection(2);
	StaticBoxSizer5->Add(rgrDRVDoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(StaticBoxSizer5);
	StaticBoxSizer5->Fit(Panel7);
	StaticBoxSizer5->SetSizeHints(Panel7);
	FlexGridSizer2->Add(Panel7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnConfigureClock = new wxButton(this, ID_BUTTON5, _("Configure Clocks"), wxPoint(152,400), wxSize(160,32), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer6->Add(btnConfigureClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer6);
	SetSizer(FlexGridSizer6);
	Layout();

	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnConfigureSi5356AClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnLoadFileClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnConfigureClockClick);
	//*)
}

pnlBoard::~pnlBoard()
{
	//(*Destroy(pnlBoard)
	//*)
}


void pnlBoard::OnbtnConfigureSi5356AClick(wxCommandEvent& event)
{
    LMLL_BoardConfigureSi5356A();
}

void pnlBoard::OnbtnLoadFileClick(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open project file"), "", "", "Register Files (*.h)|*.h|Text files (*.txt)|*.TXT", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LMLL_BoardLoadRegValuesFromFile( (char*)openFileDialog.GetPath().ToStdString().c_str() );
}

void pnlBoard::OnbtnConfigureClockClick(wxCommandEvent& event)
{
    double refFreq;
    double freq;

    txtRefClk->GetValue().ToDouble(&refFreq);

    LMLL_BoardEnableClock(0, chkDRVAen->GetValue());
    LMLL_BoardEnableClock(1, chkDRVBen->GetValue());
    LMLL_BoardEnableClock(2, chkDRVCen->GetValue());
    LMLL_BoardEnableClock(3, chkDRVDen->GetValue());

    txtDRVAfreq->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(0, refFreq, freq);
    txtDRVBfreq->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(1, refFreq, freq);
    txtDRVCfreq->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(2, refFreq, freq);
    txtDRVDfreq->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(3, refFreq, freq);

    unsigned int inv = 0;
    inv = chkDRVAInvertEven->GetValue();
    inv |= chkDRVAInvertOdd->GetValue() << 2;
    LMLL_BoardSetClockInversion(0, inv);

    inv = chkDRVBInvertEven->GetValue();
    inv |= chkDRVBInvertOdd->GetValue() << 2;
    LMLL_BoardSetClockInversion(1, inv);

    inv = chkDRVCInvertEven->GetValue();
    inv |= chkDRVCInvertOdd->GetValue() << 2;
    LMLL_BoardSetClockInversion(2, inv);

    inv = chkDRVDInvertEven->GetValue();
    inv |= chkDRVDInvertOdd->GetValue() << 2;
    LMLL_BoardSetClockInversion(3, inv);

    LMLL_BoardSetClockOutputFormat(0, rgrDRVAoutput->GetSelection() + 1);
    LMLL_BoardSetClockOutputFormat(1, rgrDRVBoutput->GetSelection() + 1);
    LMLL_BoardSetClockOutputFormat(2, rgrDRVCoutput->GetSelection() + 1);
    LMLL_BoardSetClockOutputFormat(3, rgrDRVDoutput->GetSelection() + 1);
    LMLL_BoardConfigureSi5356A();
}
