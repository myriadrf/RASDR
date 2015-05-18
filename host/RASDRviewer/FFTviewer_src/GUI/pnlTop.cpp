#include "pnlTop.h"
#include "ctr_6002dr2_LogicDLL.h"

//(*InternalHeaders(pnlTop)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/tglbtn.h>
#include <wx/statline.h>
#include <wx/statbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlTop)
const long pnlTop::ID_BUTTON1 = wxNewId();
const long pnlTop::ID_BUTTON2 = wxNewId();
const long pnlTop::ID_BUTTON4 = wxNewId();
const long pnlTop::ID_STATICTEXT1 = wxNewId();
const long pnlTop::ID_STATICTEXT2 = wxNewId();
const long pnlTop::ID_STATICLINE1 = wxNewId();
const long pnlTop::ID_COMBOBOX1 = wxNewId();
const long pnlTop::ID_COMBOBOX2 = wxNewId();
const long pnlTop::ID_BUTTON5 = wxNewId();
const long pnlTop::ID_STATICTEXT3 = wxNewId();
const long pnlTop::ID_STATICTEXT7 = wxNewId();
const long pnlTop::ID_STATICTEXT4 = wxNewId();
const long pnlTop::ID_STATICTEXT8 = wxNewId();
const long pnlTop::ID_STATICTEXT5 = wxNewId();
const long pnlTop::ID_STATICTEXT9 = wxNewId();
const long pnlTop::ID_STATICTEXT6 = wxNewId();
const long pnlTop::ID_STATICTEXT10 = wxNewId();
const long pnlTop::ID_RADIOBOX3 = wxNewId();
const long pnlTop::ID_RADIOBOX4 = wxNewId();
const long pnlTop::ID_CHECKBOX1 = wxNewId();
const long pnlTop::ID_CHECKBOX2 = wxNewId();
const long pnlTop::ID_CHECKBOX3 = wxNewId();
const long pnlTop::ID_CHECKBOX4 = wxNewId();
const long pnlTop::ID_CHECKBOX5 = wxNewId();
const long pnlTop::ID_RADIOBOX5 = wxNewId();
const long pnlTop::ID_RADIOBOX6 = wxNewId();
const long pnlTop::ID_RADIOBOX7 = wxNewId();
const long pnlTop::ID_CHECKBOX6 = wxNewId();
const long pnlTop::ID_CHECKBOX7 = wxNewId();
const long pnlTop::ID_CHECKBOX8 = wxNewId();
const long pnlTop::ID_CHECKLISTBOX1 = wxNewId();
const long pnlTop::ID_RADIOBOX8 = wxNewId();
const long pnlTop::ID_CHECKBOX10 = wxNewId();
const long pnlTop::ID_CHECKBOX11 = wxNewId();
const long pnlTop::ID_CHECKBOX12 = wxNewId();
const long pnlTop::ID_CHECKBOX13 = wxNewId();
const long pnlTop::ID_STATICBOX2 = wxNewId();
const long pnlTop::ID_STATICTEXT11 = wxNewId();
const long pnlTop::ID_BUTTON3 = wxNewId();
const long pnlTop::ID_STATICTEXT12 = wxNewId();
const long pnlTop::ID_STATICTEXT13 = wxNewId();
const long pnlTop::ID_COMBOBOX3 = wxNewId();
const long pnlTop::ID_COMBOBOX4 = wxNewId();
const long pnlTop::ID_STATICTEXT14 = wxNewId();
const long pnlTop::ID_PANEL7 = wxNewId();
const long pnlTop::ID_RADIOBOX1 = wxNewId();
const long pnlTop::ID_RADIOBOX2 = wxNewId();
const long pnlTop::ID_CHECKBOX9 = wxNewId();
const long pnlTop::ID_RADIOBOX9 = wxNewId();
const long pnlTop::ID_TOGGLEBUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTop,wxPanel)
	//(*EventTable(pnlTop)
	//*)
END_EVENT_TABLE()

pnlTop::pnlTop(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size,int styles, wxString idname)
{
    sendChanges = true;
	BuildContent(parent,id,pos,size);
}

void pnlTop::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTop)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxBoxSizer* BoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(782,524), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("DC Calibration"));
	FlexGridSizer4 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer5 = new wxFlexGridSizer(3, 3, 0, 0);
	btnDCRstClbr = new wxButton(this, ID_BUTTON1, _("Reset Calibration"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer5->Add(btnDCRstClbr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCLoadVal = new wxButton(this, ID_BUTTON2, _("Load Cnt Value"), wxPoint(136,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer5->Add(btnDCLoadVal, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCStartClbr = new wxButton(this, ID_BUTTON4, _("Start Calibration"), wxPoint(256,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer5->Add(btnDCStartClbr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("CAL ModuleAddress:"), wxPoint(8,40), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Calibration Value:"), wxPoint(136,40), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer5->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	StaticLine1->Hide();
	FlexGridSizer5->Add(StaticLine1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCCalAddr = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(8,56), wxSize(120,24), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	FlexGridSizer5->Add(cmbDCCalAddr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbCalVal = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(136,56), wxSize(104,24), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer5->Add(cmbCalVal, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCReadVal = new wxButton(this, ID_BUTTON5, _("Read Values"), wxDefaultPosition, wxSize(96,24), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer5->Add(btnDCReadVal, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Calibration Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer6->Add(StaticText3, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lbDC_REGVAL = new wxStaticText(this, ID_STATICTEXT7, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer6->Add(lbDC_REGVAL, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Lock Pattern:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_LOCK = new wxStaticText(this, ID_STATICTEXT8, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer6->Add(lblDC_LOCK, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Calibration Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_CLBR_DONE = new wxStaticText(this, ID_STATICTEXT9, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer6->Add(lblDC_CLBR_DONE, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Comparator Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer6->Add(StaticText6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_UD = new wxStaticText(this, ID_STATICTEXT10, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer6->Add(lblDC_UD, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer11 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(2, 2, 0, 0);
	wxString __wxRadioBoxChoices_1[4] =
	{
		_("Disabled"),
		_("TxMIX to LNA1 Path"),
		_("TxMIX to LNA2 Path"),
		_("TxMIX to LNA3 (GSM) Path")
	};
	rgrRFLB = new wxRadioBox(this, ID_RADIOBOX3, _("RF Loopback Control"), wxPoint(8,120), wxDefaultSize, 4, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX3"));
	FlexGridSizer8->Add(rgrRFLB, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[4] =
	{
		_("Disabled"),
		_("loopb to LPF input"),
		_("loopb to VGA2 input"),
		_("loopb to Rx Out Pins")
	};
	rgrBBLB = new wxRadioBox(this, ID_RADIOBOX4, _("BB Loopback"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX4"));
	FlexGridSizer8->Add(rgrBBLB, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power Control"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	chbPwrTopMods = new wxCheckBox(this, ID_CHECKBOX1, _("Top Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chbPwrTopMods->SetValue(true);
	BoxSizer1->Add(chbPwrTopMods, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrSoftTx = new wxCheckBox(this, ID_CHECKBOX2, _("Soft Tx Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chbPwrSoftTx->SetValue(false);
	BoxSizer1->Add(chbPwrSoftTx, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrSoftRx = new wxCheckBox(this, ID_CHECKBOX3, _("Soft Rx Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chbPwrSoftRx->SetValue(false);
	BoxSizer1->Add(chbPwrSoftRx, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrLpfCal = new wxCheckBox(this, ID_CHECKBOX4, _("DCOREG LPFCAL Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chbPwrLpfCal->SetValue(false);
	BoxSizer1->Add(chbPwrLpfCal, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrRfLbsw = new wxCheckBox(this, ID_CHECKBOX5, _("RF LBSW Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chbPwrRfLbsw->SetValue(false);
	BoxSizer1->Add(chbPwrRfLbsw, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("Open (off)"),
		_("Closed (on)")
	};
	rgrRXOUTSW = new wxRadioBox(this, ID_RADIOBOX5, _("RX Out/ADC In Switch"), wxPoint(208,248), wxDefaultSize, 2, __wxRadioBoxChoices_3, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX5"));
	rgrRXOUTSW->SetSelection(1);
	BoxSizer3->Add(rgrRXOUTSW, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_("Transmit"),
		_("Receive")
	};
	rgrTDDMOD = new wxRadioBox(this, ID_RADIOBOX6, _("TDD Mode Selection"), wxPoint(208,296), wxDefaultSize, 2, __wxRadioBoxChoices_4, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX6"));
	rgrTDDMOD->SetSelection(1);
	BoxSizer3->Add(rgrTDDMOD, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[2] =
	{
		_("FDD"),
		_("TDD")
	};
	rgrFDDTDD = new wxRadioBox(this, ID_RADIOBOX7, _("FDD/TDD Selection"), wxPoint(208,344), wxDefaultSize, 2, __wxRadioBoxChoices_5, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX7"));
	rgrFDDTDD->SetSelection(1);
	BoxSizer3->Add(rgrFDDTDD, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(FlexGridSizer8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("XCO Buffer"));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	chbPDXCOBUF = new wxCheckBox(this, ID_CHECKBOX6, _("Power Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chbPDXCOBUF->SetValue(false);
	BoxSizer2->Add(chbPDXCOBUF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chbSLFBXCOBUF = new wxCheckBox(this, ID_CHECKBOX7, _("Self Biasing"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chbSLFBXCOBUF->SetValue(true);
	BoxSizer2->Add(chbSLFBXCOBUF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chbBYPXCOBUF = new wxCheckBox(this, ID_CHECKBOX8, _("Bypass"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chbBYPXCOBUF->SetValue(false);
	BoxSizer2->Add(chbBYPXCOBUF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(BoxSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer3, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer11, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Clock Buffers"));
	chbSpiClkBuf = new wxCheckListBox(this, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(293,79), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	chbSpiClkBuf->Append(_("Tx DSM SPI"));
	chbSpiClkBuf->Append(_("Tx LPF"));
	chbSpiClkBuf->Append(_("Rx DSM SPI"));
	chbSpiClkBuf->Append(_("Rx LPF"));
	chbSpiClkBuf->Append(_("Rx VGA2"));
	chbSpiClkBuf->Append(_("LPF CALCORE"));
	chbSpiClkBuf->Append(_("PLLCLKOUT"));
	StaticBoxSizer6->Add(chbSpiClkBuf, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer10->Add(StaticBoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("TRX LPF Calibration"));
	Panel7 = new wxPanel(this, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	wxString __wxRadioBoxChoices_6[2] =
	{
		_("From TxPLL"),
		_("PLL Reference")
	};
	rgrCLKSEL_LPFCAL = new wxRadioBox(Panel7, ID_RADIOBOX8, _("LPF Tuning Clock"), wxPoint(0,140), wxSize(296,42), 2, __wxRadioBoxChoices_6, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX8"));
	rgrCLKSEL_LPFCAL->SetSelection(1);
	chbPD_CLKLPFCAL = new wxCheckBox(Panel7, ID_CHECKBOX10, _("DIV8 for LPD Tuning CLock PD"), wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chbPD_CLKLPFCAL->SetValue(false);
	chkLpfCalEnEnf = new wxCheckBox(Panel7, ID_CHECKBOX11, _("Enalbe Enforce Mode"), wxPoint(0,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chkLpfCalEnEnf->SetValue(false);
	chkLpfCalEn = new wxCheckBox(Panel7, ID_CHECKBOX12, _("Enalbe LPFCAL"), wxPoint(0,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	chkLpfCalEn->SetValue(false);
	chkLpfCalRst = new wxCheckBox(Panel7, ID_CHECKBOX13, _("Reset LPFCAL"), wxPoint(184,16), wxSize(112,24), 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkLpfCalRst->SetValue(false);
	StaticBox2 = new wxStaticBox(Panel7, ID_STATICBOX2, _("RCCAL LPFCAL Value"), wxPoint(0,56), wxSize(144,80), 0, _T("ID_STATICBOX2"));
	StaticText7 = new wxStaticText(Panel7, ID_STATICTEXT11, _("RCCAL_LPFCAL:"), wxPoint(8,80), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	btnReadRCCALVal = new wxButton(Panel7, ID_BUTTON3, _("Read Value"), wxPoint(8,104), wxSize(128,28), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	lblRCCAL_LPFCAL = new wxStaticText(Panel7, ID_STATICTEXT12, _("\?\?\?\?"), wxPoint(104,80), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	StaticText8 = new wxStaticText(Panel7, ID_STATICTEXT13, _("LPFCAL Code:"), wxPoint(160,40), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	cmbLpfCalCode = new wxComboBox(Panel7, ID_COMBOBOX3, wxEmptyString, wxPoint(152,56), wxSize(144,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	cmbLpfCalCode->Append(_("000"));
	cmbLpfCalCode->Append(_("001"));
	cmbLpfCalCode->Append(_("010"));
	cmbLpfCalCode->Append(_("011"));
	cmbLpfCalCode->Append(_("100"));
	cmbLpfCalCode->Append(_("101"));
	cmbLpfCalCode->Append(_("110"));
	cmbLpfCalCode->Append(_("111"));
	cmbLpfCalBw = new wxComboBox(Panel7, ID_COMBOBOX4, wxEmptyString, wxPoint(152,104), wxSize(144,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	StaticText9 = new wxStaticText(Panel7, ID_STATICTEXT14, _("LPF Bandwidth:"), wxPoint(160,88), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	StaticBoxSizer4->Add(Panel7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer10->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer10, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(5, 1, 0, 0);
	wxString __wxRadioBoxChoices_7[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_RADIOBOX1, _("Decoding"), wxPoint(720,8), wxSize(136,69), 2, __wxRadioBoxChoices_7, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	FlexGridSizer3->Add(rgrDecode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_8[2] =
	{
		_("3 Wire"),
		_("4 Wire")
	};
	rgrSpiMode = new wxRadioBox(this, ID_RADIOBOX2, _("SPI Port Mode"), wxPoint(720,80), wxSize(136,69), 2, __wxRadioBoxChoices_8, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrSpiMode->SetSelection(1);
	FlexGridSizer3->Add(rgrSpiMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Rx Bypass Mode"));
	chbRxTestModeEn = new wxCheckBox(this, ID_CHECKBOX9, _("TIA Shorted\nTo Output Pins"), wxDefaultPosition, wxSize(129,32), 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chbRxTestModeEn->SetValue(false);
	StaticBoxSizer5->Add(chbRxTestModeEn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_9[2] =
	{
		_("Reset State"),
		_("Inactive")
	};
	rgrDsmRst = new wxRadioBox(this, ID_RADIOBOX9, _("DSM Soft Reset"), wxPoint(720,224), wxSize(140,69), 2, __wxRadioBoxChoices_9, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX9"));
	rgrDsmRst->SetSelection(1);
	FlexGridSizer3->Add(rgrDsmRst, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Global Reset"));
	swReset = new wxToggleButton(this, ID_TOGGLEBUTTON1, _("Reset is OFF"), wxPoint(16,16), wxSize(112,104), 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
	StaticBoxSizer7->Add(swReset, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::btnDCRstClbrClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::btnDCLoadValClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::btnDCStartClbrClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::cmbDCCalAddrChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::cmbCalValChange);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::btnDCReadValClick);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrRFLBClick);
	Connect(ID_RADIOBOX4,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrBBLBClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbPwrTopModsClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbPwrSoftTxClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbPwrSoftRxClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbPwrLpfCalClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbPwrRfLbswClick);
	Connect(ID_RADIOBOX5,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrRXOUTSWClick);
	Connect(ID_RADIOBOX6,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrTDDMODClick);
	Connect(ID_RADIOBOX7,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrFDDTDDClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbPDXCOBUFClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbSLFBXCOBUFClick);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbBYPXCOBUFClick);
	Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&pnlTop::chbSpiClkBufClick);
	Connect(ID_RADIOBOX8,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrCLKSEL_LPFCALClick);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbPD_CLKLPFCALClick);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chkLpfCalEnEnfClick);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chkLpfCalEnClick);
	Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chkLpfCalRstClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::btnReadRCCALValClick);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::cmbLpfCalCodeChange);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::cmbLpfCalBwChange);
	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrDecodeClick);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrSpiModeClick);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::chbRxTestModeEnClick);
	Connect(ID_RADIOBOX9,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::rgrDsmRstClick);
	Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::swResetClick);
	//*)
}

pnlTop::~pnlTop()
{
	//(*Destroy(pnlTop)
	//*)
}


// ---------------------------------------------------------------------------
void pnlTop::Initialize()
{
	sendChanges = false;
	FillComboBoxes();
	SetGuiDefaults();
	sendChanges = true;
};

// ---------------------------------------------------------------------------
void pnlTop::SetGuiDefaults()
{
    Freeze();
	// DECODE
	rgrDecode->SetSelection( 0);
	// SRESET
	rgrDsmRst->SetSelection( 1);
	// EN
	chbPwrTopMods->SetValue(true);
	// STXEN
	chbPwrSoftTx->SetValue(false);
	// SRXEN
	chbPwrSoftRx->SetValue(false);
	// TFWMODE
	rgrSpiMode->SetSelection( 1);

	// CLKSEL_LPFCAL
	rgrCLKSEL_LPFCAL->SetSelection( 1);
	// PD_CLKLPFCAL
	chbPD_CLKLPFCAL->SetValue(true);
	// ENF_EN_CAL_LPFCAL
	chkLpfCalEnEnf->SetValue(false);
	// RST_CAL_LPFCAL
	chkLpfCalRst->SetValue(true);

	// EN_CAL_LPFCAL
	chkLpfCalEn->SetValue(false);
	// FORCE_CODE_CAL_LPFCAL[2:0]
	cmbLpfCalCode->SetSelection( 0);
	// BWC_LPFCAL[3:0]
	cmbLpfCalBw->SetSelection( 0);

	// BBBYP_RX
	chbRxTestModeEn->SetValue(false);
	// Control changed to radiobuttons instead of checkboxes,
	// while only one should be active at a time:
	// LBEN_LPFIN_RX
	// LBEN_VGA2IN_RX
	// LBEN_OPIN_RX
	rgrBBLB->SetSelection( 0);
	// LBRFEN_RXFE[3:0]
	rgrRFLB->SetSelection( 0);

	// RXOUTSW
	rgrRXOUTSW->SetSelection( 0);
	// CLK_EN[6:0]
	for (int i = 0; i < 6; i++)
	{
		chbSpiClkBuf->Check(i, false);
	};
	chbSpiClkBuf->Check(6, true);

	// FDDTDD
	rgrFDDTDD->SetSelection( 0);
	// TDDMOD
	rgrTDDMOD->SetSelection( 0);

	// PDXCOBUF
	chbPDXCOBUF->SetValue(false);
	// SLFBXCOBUF
	chbSLFBXCOBUF->SetValue(true);
	// BYPXCOBUF
	chbBYPXCOBUF->SetValue(false);
	// PD_DCOREF_LPFCAL
	chbPwrLpfCal->SetValue(true);
	// RFLBSW_EN
	chbPwrRfLbsw->SetValue(false);

	// DC_ADDR[3:0]
	cmbDCCalAddr->SetSelection( 0);

	// DC_CNTVAL[5:0]
    cmbCalVal->SetSelection( 31);

	SetGuiDecode();
	Thaw();
};

// ---------------------------------------------------------------------------
void pnlTop::SetGuiDecode()
{
	if (rgrDecode->GetSelection() == 0)
	{
		// Decode
		chbPwrTopMods->Enable(true);

		chbPwrLpfCal->Enable(false);
		chbPwrRfLbsw->Enable(false);
	}
	else
	{
		// Direct control
		chbPwrTopMods->Enable(false);

		chbPwrLpfCal->Enable(true);
		chbPwrRfLbsw->Enable(true);
	};
};

// ---------------------------------------------------------------------------
// updates GUI data values
// ---------------------------------------------------------------------------
bool pnlTop::UpdateGUI()
{
	int itmp;
	bool bRez = true;

	int DC_regVal;
	int DC_lock;
	int DC_clbr;
	int DC_ud;
	LMLL_TopGetDCCalibrationData(DC_regVal, DC_lock, DC_clbr, DC_ud);
	// DC_REGVAL[5:0]
	lbDC_REGVAL->SetLabel( wxString::Format("%i", DC_regVal));

	// DC_LOCK[2:0]
	lblDC_LOCK->SetLabel( wxString::Format("%i", DC_lock));

	// DC_CLBR_DONE
	if(DC_clbr)
		lblDC_CLBR_DONE->SetLabel("In progress");
	else
		lblDC_CLBR_DONE->SetLabel("Done");

	// DC_UD
	if(DC_ud)
		lblDC_UD->SetLabel("Up");
	else
		lblDC_UD->SetLabel("Down");

	// RCCAL_LPFCAL[2:0]
	lblRCCAL_LPFCAL->SetLabel(wxString::Format("%i", LMLL_TopGetRCCAL_LPFCAL()));

	// DC_CNTVAL[5:0]
	//cmbCalVal->SetSelection( LMLL_TopGetCalVal();
	cmbCalVal->SetSelection( DC_regVal);
	/*
	 //DC_START_CLBR
	 itmp = DC_START_CLBR_r03_b55();

	 //DC_LOAD
	 itmp = DC_LOAD_r03_b44();

	 //DC_SRESET
	 itmp = DC_SRESET_r03_b33();
	 */

	// DC_ADDR[2:0]
	cmbDCCalAddr->SetSelection( LMLL_TopGetDCCalAddr());

	/*
	 //VER[3:0]
	 itmp = VER_r04_b74();

	 //REV[3:0]
	 itmp = REV_r04_b30();
	 */

	// DECODE
	rgrDecode->SetSelection( LMLL_TopGetDecode());

	// SRESET
	rgrDsmRst->SetSelection( LMLL_TopGetDsmRst());

	// EN
	chbPwrTopMods->SetValue(LMLL_TopGetPwrTopMods());

	// STXEN
	chbPwrSoftTx->SetValue(LMLL_TopGetPwrSoftTx());

	// SRXEN
	chbPwrSoftRx->SetValue(LMLL_TopGetPwrSoftRx()) ;

	// TFWMODEA
	rgrSpiMode->SetSelection( LMLL_TopGetSpiMode());

	// CLKSEL_LPFCAL
	rgrCLKSEL_LPFCAL->SetSelection( LMLL_TopGetCLKSEL_LPFCAL());

	// PD_CLKLPFCAL
	chbPD_CLKLPFCAL->SetValue(LMLL_TopGetPD_CLKLPFCAL());

	// ENF_EN_CAL_LPFCAL
	chkLpfCalEnEnf->SetValue(LMLL_TopGetLpfCalEnEnf());

	// RST_CAL_LPFCAL
	chkLpfCalRst->SetValue(LMLL_TopGetLpfCalRst());
	// chkLpfCalRst->SetValue(!chkLpfCalRst->Checked;

	// EN_CAL_LPFCAL
	chkLpfCalEn->SetValue(LMLL_TopGetLpfCalEn());

	// FORCE_CODE_CAL_LPFCAL[2:0]
	cmbLpfCalCode->SetSelection( LMLL_TopGetLpfCalCode());

	// BWC_LPFCAL[3:0]
	cmbLpfCalBw->SetSelection( LMLL_TopGetLpfCalBw());

	// BBBYP_RX
	chbRxTestModeEn->SetValue(LMLL_TopGetRxTestModeEn());

	// LBEN_LPFIN_RX
	// LBEN_VGA2IN_RX
	// LBEN_OPIN_RX

	rgrBBLB->SetSelection( LMLL_TopGetBBLB());

	// LBRFEN[3:0]
	rgrRFLB->SetSelection( LMLL_TopGetRFLB());

	// RXOUTSW
	rgrRXOUTSW->SetSelection( LMLL_TopGetRXOUTSW());

	// SPI_CLK_EN [6]
	chbSpiClkBuf->Check(6, LMLL_TopGetSpiClkBuf(6));

	// SPI_CLK_EN [5]
	chbSpiClkBuf->Check(5, LMLL_TopGetSpiClkBuf(5));

	// SPI_CLK_EN [4]
	chbSpiClkBuf->Check(4, LMLL_TopGetSpiClkBuf(4));

	// SPI_CLK_EN [3]
	chbSpiClkBuf->Check(3, LMLL_TopGetSpiClkBuf(3));

	// SPI_CLK_EN [2]
	chbSpiClkBuf->Check(2, LMLL_TopGetSpiClkBuf(2));

	// SPI_CLK_EN [1]
	chbSpiClkBuf->Check(1, LMLL_TopGetSpiClkBuf(1));

	// SPI_CLK_EN [0]
	chbSpiClkBuf->Check(0, LMLL_TopGetSpiClkBuf(0));

	// FDDTDD
	rgrFDDTDD->SetSelection( LMLL_TopGetFDDTDD());

	// TDDMOD
	rgrTDDMOD->SetSelection( LMLL_TopGetTDDMOD());

	// PDXCOBUF
	chbPDXCOBUF->SetValue(LMLL_TopGetPDXCOBUF());

	// SLFBXCOBUF
	chbSLFBXCOBUF->SetValue(LMLL_TopGetSLFBXCOBUF());

	// BYPXCOBUF
	chbBYPXCOBUF->SetValue(LMLL_TopGetBYPXCOBUF());

	// PD[1]
	chbPwrLpfCal->SetValue(LMLL_TopGetPwrLpfCal());
	// chbPwrLpfCal->SetValue(!chbPwrLpfCal->Checked;

	// PD[0]
	chbPwrRfLbsw->SetValue(LMLL_TopGetPwrRfLbsw());

	return bRez;
};

// ---------------------------------------------------------------------------
void pnlTop::rgrDecodeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetDecode(rgrDecode->GetSelection());
	SetGuiDecode();
}

// ---------------------------------------------------------------------------
void pnlTop::rgrDsmRstClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetDsmRst(rgrDsmRst->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::chbPwrTopModsClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetPwrTopMods(chbPwrTopMods->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::chbPwrSoftTxClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetPwrSoftTx(chbPwrSoftTx->GetValue());
	// 1.a. When Soft Tx is Enabled it automatically enables Tx DSM SPI.
	chbSpiClkBuf->Check(0, chbPwrSoftTx->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::chbPwrSoftRxClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetPwrSoftRx(chbPwrSoftRx->GetValue());
	// 1.b. When Soft Rx is Enabled it automatically enables Rx DSM SPI.
	chbSpiClkBuf->Check(2, chbPwrSoftRx->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::rgrSpiModeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetSpiMode(rgrSpiMode->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::chkLpfCalEnEnfClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetLpfCalEnEnf(chkLpfCalEnEnf->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::chkLpfCalRstClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetLpfCalRst(chkLpfCalRst->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::chbRxTestModeEnClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetRxTestModeEn(chbRxTestModeEn->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::rgrBBLBClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetBBLB(rgrBBLB->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::rgrRFLBClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetRFLB(rgrRFLB->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::chkLpfCalEnClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetLpfCalEn(chkLpfCalEn->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::cmbLpfCalCodeChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetLpfCalCode(cmbLpfCalCode->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::cmbLpfCalBwChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetLpfCalBw(cmbLpfCalBw->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::chbSpiClkBufClick(wxCommandEvent& event)
{
	for (int i = 0; i < 7; i++)
		if(sendChanges) LMLL_TopSetSpiClkBuf(i, chbSpiClkBuf->IsChecked(i));
}

// ---------------------------------------------------------------------------
void pnlTop::chbPwrLpfCalClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetPwrLpfCal(chbPwrLpfCal->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::chbPwrRfLbswClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetPwrRfLbsw(chbPwrRfLbsw->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTop::cmbDCCalAddrChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetDCCalAddr(cmbDCCalAddr->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::cmbCalValChange(wxCommandEvent& event)
{
	//if(sendChanges) LMLL_TopSetCalVal(cmbCalVal->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTop::rgrCLKSEL_LPFCALClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetCLKSEL_LPFCAL(rgrCLKSEL_LPFCAL->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTop::chbPD_CLKLPFCALClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetPD_CLKLPFCAL(chbPD_CLKLPFCAL->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTop::rgrRXOUTSWClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetRXOUTSW(rgrRXOUTSW->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTop::rgrFDDTDDClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetFDDTDD(rgrFDDTDD->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTop::rgrTDDMODClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetTDDMOD(rgrTDDMOD->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTop::chbPDXCOBUFClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetPDXCOBUF(chbPDXCOBUF->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTop::chbSLFBXCOBUFClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetSLFBXCOBUF(chbSLFBXCOBUF->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTop::chbBYPXCOBUFClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TopSetBYPXCOBUF(chbBYPXCOBUF->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTop::btnDCRstClbrClick(wxCommandEvent& event)
{
	LMLL_TopDCResetCalibration();
}
// ---------------------------------------------------------------------------

void pnlTop::btnDCLoadValClick(wxCommandEvent& event)
{
	LMLL_TopDCLoadValues(cmbCalVal->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTop::btnDCStartClbrClick(wxCommandEvent& event)
{
	LMAL_TopDCStartCalibration();
}

// ---------------------------------------------------------------------------
void pnlTop::btnDCReadValClick(wxCommandEvent& event)
{
	/*
	int calibVal = 0;
	int lockPattern = 0;
	int calibStatus = 0;
	int compValue = 0;
	LMLL_TopDCReadValues(calibVal, lockPattern, calibStatus, compValue);
	lbDC_REGVAL->SetLabel(calibVal;
	lblDC_LOCK->SetLabel(lockPattern;
	lblDC_CLBR_DONE->SetLabel(calibStatus;
	lblDC_UD->SetLabel(compValue;
	*/
	int DC_regVal;
	int DC_lock;
	int DC_clbr;
	int DC_ud;
	LMLL_TopGetDCCalibrationData(DC_regVal, DC_lock, DC_clbr, DC_ud);
	// DC_REGVAL[5:0]
	lbDC_REGVAL->SetLabel( wxString::Format("%i", DC_regVal));
	// DC_LOCK[2:0]
	lblDC_LOCK->SetLabel( wxString::Format("%i", DC_lock));
	if(DC_clbr)
		lblDC_CLBR_DONE->SetLabel("In progress");
	else
		lblDC_CLBR_DONE->SetLabel("Done");

	// DC_UD
	if(DC_ud)
		lblDC_UD->SetLabel("Up");
	else
		lblDC_UD->SetLabel("Down");
}

// ---------------------------------------------------------------------------
void pnlTop::btnReadRCCALValClick(wxCommandEvent& event)
{
	lblRCCAL_LPFCAL->SetLabel( wxString::Format("%i", LMLL_TopGetRCCAL_LPFCAL()));
}

void pnlTop::swResetClick(wxCommandEvent& event)
{
	if (swReset->GetValue())
    {
        swReset->SetLabel("Reset is ON");
        LMLL_TopResetOn();
    }
	else
    {
        swReset->SetLabel("Reset is OFF");
        LMLL_TopResetOff();
    }
}
// ---------------------------------------------------------------------------

void pnlTop::OnEraseBackground(wxEraseEvent& event)
{
}

void pnlTop::FillComboBoxes()
{
    Freeze();
    wxString cs_Numbers[64];
	// DECODE
	cmbLpfCalCode->Clear();
	for (int i = 0; i < 8; i++)
		cs_Numbers[i] = wxString::Format("%i", i);
	cmbLpfCalCode->Append( 8, cs_Numbers);
	cmbLpfCalCode->SetSelection( 0);
	// BWC_LPFCAL[3:0]
	cmbLpfCalBw->Clear();
	wxString cs_Bw[16] = {"14 MHz",
	"10 MHz",
	"7 MHz",
	"6 MHz",
	"5 MHz",
	"4.375 MHz",
	"3.5 MHz",
	"3 MHz",
	"2.75 MHz",
	"2.5 MHz",
	"1.92 MHz",
	"1.5 MHz",
	"1.375 MHz",
	"1.25 MHz",
	"0.875 MHz",
	"0.75 MHz"};

	cmbLpfCalBw->Append(16, cs_Bw);
	cmbLpfCalBw->SetSelection( 0);

	// DC_ADDR[3:0]
	cmbDCCalAddr->Clear();
	for (int i = 0; i < 5; i++)
		cs_Numbers[i] = wxString::Format("%i", i);
    cmbDCCalAddr->Append( 5, cs_Numbers);
	cmbDCCalAddr->SetSelection( 0);

	// DC_CNTVAL[5:0]
	cmbCalVal->Clear();
	for(int i=0; i<64; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
	cmbCalVal->Append( 64, cs_Numbers);
    cmbCalVal->SetSelection( 31);
	Thaw();
}

void pnlTop::OnPaint(wxPaintEvent& event)
{
}
