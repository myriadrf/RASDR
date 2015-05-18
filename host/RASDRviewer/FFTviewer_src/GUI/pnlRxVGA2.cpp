// -----------------------------------------------------------------------------
// FILE:        "pnlRxVGA2.cpp"
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
#include "pnlRxVGA2.h"
#include "ctr_6002dr2_LogicDLL.h"

//(*InternalHeaders(pnlRxVGA2)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlRxVGA2)
const long pnlRxVGA2::ID_BUTTON1 = wxNewId();
const long pnlRxVGA2::ID_BUTTON2 = wxNewId();
const long pnlRxVGA2::ID_BUTTON4 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT1 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT2 = wxNewId();
const long pnlRxVGA2::ID_STATICLINE1 = wxNewId();
const long pnlRxVGA2::ID_COMBOBOX1 = wxNewId();
const long pnlRxVGA2::ID_COMBOBOX2 = wxNewId();
const long pnlRxVGA2::ID_BUTTON5 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT3 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT7 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT4 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT8 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT5 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT9 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT6 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT10 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX1 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX2 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX3 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX4 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX5 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX6 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX7 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX8 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX9 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX10 = wxNewId();
const long pnlRxVGA2::ID_CHECKBOX11 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT11 = wxNewId();
const long pnlRxVGA2::ID_COMBOBOX3 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT12 = wxNewId();
const long pnlRxVGA2::ID_COMBOBOX4 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT13 = wxNewId();
const long pnlRxVGA2::ID_COMBOBOX5 = wxNewId();
const long pnlRxVGA2::ID_COMBOBOX6 = wxNewId();
const long pnlRxVGA2::ID_RADIOBOX2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlRxVGA2,wxPanel)
	//(*EventTable(pnlRxVGA2)
	//*)
END_EVENT_TABLE()

pnlRxVGA2::pnlRxVGA2(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
    m_cVer = 2;
	m_cRev = 2;
	m_cMask = 0;
	BuildContent(parent,id,pos,size);
}

void pnlRxVGA2::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlRxVGA2)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxSize(555,304), wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
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
	lbDC_REGVAL = new wxStaticText(this, ID_STATICTEXT7, _("\?\?\?"), wxDefaultPosition, wxSize(78,13), 0, _T("ID_STATICTEXT7"));
	FlexGridSizer6->Add(lbDC_REGVAL, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Lock Pattern:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_LOCK = new wxStaticText(this, ID_STATICTEXT8, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer6->Add(lblDC_LOCK, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Calibration Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_CLBR_DONE = new wxStaticText(this, ID_STATICTEXT9, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer6->Add(lblDC_CLBR_DONE, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Comparator Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer6->Add(StaticText6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_UD = new wxStaticText(this, ID_STATICTEXT10, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer6->Add(lblDC_UD, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(1, 3, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrVGA2Mods = new wxCheckBox(this, ID_CHECKBOX1, _("RxVGA2 Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chbPwrVGA2Mods->SetValue(false);
	StaticBoxSizer2->Add(chbPwrVGA2Mods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCurrR = new wxCheckBox(this, ID_CHECKBOX2, _("DC Current Regulator Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chbPwrDCCurrR->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCurrR, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCDACB = new wxCheckBox(this, ID_CHECKBOX3, _("VGA2B DC Cal. DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chbPwrDCDACB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCDACB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCmpB = new wxCheckBox(this, ID_CHECKBOX4, _("VGA2B DC Cal. Comp. Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chbPwrDCCmpB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCmpB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCDACA = new wxCheckBox(this, ID_CHECKBOX5, _("VGA2A DC Cal. DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chbPwrDCDACA->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCDACA, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCmpA = new wxCheckBox(this, ID_CHECKBOX6, _("VGA2A DC Cal. Comp. Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chbPwrDCCmpA->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCmpA, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBG = new wxCheckBox(this, ID_CHECKBOX7, _("Band Gap Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chbPwrBG->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBypAB = new wxCheckBox(this, ID_CHECKBOX8, _("Out Buff. in Both VGAs Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chbPwrBypAB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBypAB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBypB = new wxCheckBox(this, ID_CHECKBOX9, _("VGA2B Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chbPwrBypB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBypB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBypA = new wxCheckBox(this, ID_CHECKBOX10, _("VGA2A Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chbPwrBypA->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBypA, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrCurrRef = new wxCheckBox(this, ID_CHECKBOX11, _("Current Reference Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chbPwrCurrRef->SetValue(false);
	StaticBoxSizer2->Add(chbPwrCurrRef, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("VGA2 Control"));
	StaticText7 = new wxStaticText(this, ID_STATICTEXT11, _("VGA2 Gain, dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticBoxSizer3->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2G_u = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	StaticBoxSizer3->Add(cmbVga2G_u, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT12, _("VGA2B Gain (Test), dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	StaticBoxSizer3->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2GB_t = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	StaticBoxSizer3->Add(cmbVga2GB_t, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT13, _("VGA2A Gain (Test), dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	StaticBoxSizer3->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2GA_t = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	StaticBoxSizer3->Add(cmbVga2GA_t, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VGA2 CM Voltage"));
	cmbVCM = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	StaticBoxSizer4->Add(cmbVCM, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_RADIOBOX2, _("Decoding"), wxPoint(720,8), wxSize(136,69), 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	FlexGridSizer1->Add(rgrDecode, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::btnDCRstClbrClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::btnDCLoadValClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::btnDCStartClbrClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::cmbDCCalAddrChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::cmbCalValChange);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::btnDCReadValClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrVGA2ModsClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrDCCurrRClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrDCDACBClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrDCCmpBClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrDCDACAClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrDCCmpAClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrBGClick);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrBypABClick);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrBypBClick);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrBypAClick);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::chbPwrCurrRefClick);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::cmbVga2G_uChange);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::cmbVga2GB_tChange);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::cmbVga2GA_tChange);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::cmbVCMChange);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::rgrDecodeClick);
	//*)
}

pnlRxVGA2::~pnlRxVGA2()
{
	//(*Destroy(pnlRxVGA2)
	//*)
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::Initialize()
{
	sendChanges = false;
	m_cMAddr = LMLL_RxVGA2GetAddr();
	FillComboBoxes();
	SetGuiDefaults();
	sendChanges = true;
};

// ---------------------------------------------------------------------------
void pnlRxVGA2::SetGuiDefaults()
{
    Freeze();
	cmbVCM->SetSelection(7);

	// EN
	chbPwrVGA2Mods->SetValue(true);
	// DECODE
	rgrDecode->SetSelection(0);

	// VGA2GAIN[4:0]
	cmbVga2G_u->SetSelection(1);

	//
	chbPwrDCCurrR->SetValue(true);
	chbPwrDCDACB->SetValue(true);
	chbPwrDCCmpB->SetValue(true);
	chbPwrDCDACA->SetValue(true);
	chbPwrDCCmpA->SetValue(true);
	chbPwrBG->SetValue(true);
	//
	chbPwrBypAB->SetValue(true);
	chbPwrBypB->SetValue(true);
	chbPwrBypA->SetValue(true);
	chbPwrCurrRef->SetValue(true);

	// VGA2GAINB[3:0]
	cmbVga2GB_t->SetSelection(0);

	// VGA2GAINA[3:0]
	cmbVga2GA_t->SetSelection(1);

	// DC_ADDR[3:0]
    cmbDCCalAddr->SetSelection(0);

	// DC_CNTVAL[5:0]
	cmbCalVal->SetSelection(31);

	SetGuiDecode();
	Thaw();
};

// ---------------------------------------------------------------------------
void pnlRxVGA2::SetGuiDecode()
{
	if (rgrDecode->GetSelection() == 0)
	{
		// Decode
		chbPwrVGA2Mods->Enable(true);
		cmbVga2G_u->Enable(true);

		chbPwrDCCurrR->Enable(false);
		chbPwrDCDACB->Enable(false);
		chbPwrDCDACA->Enable(false);

		// To resolove Ver=2 Rev=2 Mask=1 version
		if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
		{
			chbPwrDCCmpB->Enable(true);
			chbPwrDCCmpA->Enable(true);
		}
		else
		{
			chbPwrDCCmpB->Enable(false);
			chbPwrDCCmpA->Enable(false);
		};

		chbPwrBG->Enable(false);
		chbPwrBypAB->Enable(false);
		chbPwrBypB->Enable(false);
		chbPwrBypA->Enable(false);
		chbPwrCurrRef->Enable(false);
		cmbVga2GB_t->Enable(false);
		cmbVga2GA_t->Enable(false);
	}
	else
	{
		// Direct control
		chbPwrVGA2Mods->Enable(false);
		cmbVga2G_u->Enable(false);

		chbPwrDCCurrR->Enable(true);
		chbPwrDCDACB->Enable(true);
		chbPwrDCCmpB->Enable(true);
		chbPwrDCDACA->Enable(true);
		chbPwrDCCmpA->Enable(true);
		chbPwrBG->Enable(true);
		chbPwrBypAB->Enable(true);
		chbPwrBypB->Enable(true);
		chbPwrBypA->Enable(true);
		chbPwrCurrRef->Enable(true);
		cmbVga2GB_t->Enable(true);
		cmbVga2GA_t->Enable(true);
	};
};

// ----------------------------------------------------------------------------
// Set GUI according to the chip version, revision and mask
// ----------------------------------------------------------------------------
void pnlRxVGA2::UpdateVerRevMask(char Ver, char Rev, char Mask)
{
	m_cVer = Ver;
	m_cRev = Rev;
	m_cMask = Mask;

	SetGuiDecode();
};

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrVGA2ModsClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrVGA2Mods(chbPwrVGA2Mods->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::rgrDecodeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetDecode(rgrDecode->GetSelection());
	SetGuiDecode();
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::cmbVga2G_uChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetVga2G_u(cmbVga2G_u->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrDCCurrRClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrDCCurrR(chbPwrDCCurrR->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrDCDACBClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrDCDACB(chbPwrDCDACB->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrDCCmpBClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrDCCmpB(chbPwrDCCmpB->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrDCDACAClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrDCDACA(chbPwrDCDACA->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrDCCmpAClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrDCCmpA(chbPwrDCCmpA->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrBGClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrBG(chbPwrBG->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrBypABClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrBypAB(chbPwrBypAB->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrBypBClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrBypB(chbPwrBypB->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrBypAClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrBypA(chbPwrBypA->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::chbPwrCurrRefClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetPwrCurrRef(chbPwrCurrRef->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::cmbVga2GB_tChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetVga2GB_t(cmbVga2GB_t->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::cmbVga2GA_tChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetVga2GA_t(cmbVga2GA_t->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::cmbVCMChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetVCM(cmbVCM->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::cmbDCCalAddrChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxVGA2SetDCCalAddr(cmbDCCalAddr->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::cmbCalValChange(wxCommandEvent& event)
{
	//if(sendChanges) LMLL_RxVGA2SetCalVal(cmbCalVal->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::btnDCRstClbrClick(wxCommandEvent& event)
{
	LMLL_RxVGA2DCResetCalibration();
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::btnDCLoadValClick(wxCommandEvent& event)
{
	LMLL_RxVGA2DCLoadValues(cmbCalVal->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::btnDCStartClbrClick(wxCommandEvent& event)
{
	LMLL_RxVGA2DCStartCalibration();
}

// ---------------------------------------------------------------------------
void pnlRxVGA2::btnDCReadValClick(wxCommandEvent& event)
{
	int DC_regVal;
	int DC_lock;
	int DC_clbr;
	int DC_ud;
	LMLL_RxVGA2GetDCCalibrationData(DC_regVal, DC_lock, DC_clbr, DC_ud);
	// DC_REGVAL[5:0]
	lbDC_REGVAL->SetLabel( wxString::Format("%i", DC_regVal));
	// DC_LOCK[2:0]
	lblDC_LOCK->SetLabel( wxString::Format("%i", DC_lock));
	if(DC_clbr)
		lblDC_CLBR_DONE->SetLabel("In Progress");
	else
		lblDC_CLBR_DONE->SetLabel("Done");

	// DC_UD
	if(DC_ud)
		lblDC_UD->SetLabel("Up");
	else
		lblDC_UD->SetLabel("Down");
}

// ---------------------------------------------------------------------------
// updates GUI data values
// ---------------------------------------------------------------------------
bool pnlRxVGA2::UpdateGUI()
{
	int itmp;
	bool bRez = true;

	int iDC_REGVAL;
	int iDC_LOCK;
	int iDC_CLBR_DONE;
	int iDC_UD;

	LMLL_RxVGA2GetDCCalibrationData(iDC_REGVAL, iDC_LOCK, iDC_CLBR_DONE, iDC_UD);
	// DC_REGVAL[5:0]
	lbDC_REGVAL->SetLabel( wxString::Format("%i", iDC_REGVAL));

	// DC_LOCK[2:0]
	lblDC_LOCK->SetLabel( wxString::Format("%i", iDC_LOCK));

	// DC_CLBR_DONE
	if(iDC_CLBR_DONE)
		lblDC_CLBR_DONE->SetLabel("In Progress");
	else
		lblDC_CLBR_DONE->SetLabel("Done");

	// DC_UD
	if(iDC_UD)
		lblDC_UD->SetLabel("Up");
	else
		lblDC_UD->SetLabel("Down");

	// DC_CNTVAL[5:0]
	//cmbCalVal->SetSelection(LMLL_RxVGA2GetCalVal();
	cmbCalVal->SetSelection(iDC_REGVAL);

	// DC_START_CLBR
	// itmp = DC_START_CLBR_r03_b55();

	// DC_LOAD
	// itmp = DC_LOAD_r03_b44();

	// DC_SRESET
	// itmp = DC_SRESET_r03_b33();

	// DC_ADDR[2:0]
	cmbDCCalAddr->SetSelection(LMLL_RxVGA2GetDCCalAddr());

	// VCM[3:0]
	cmbVCM->SetSelection(LMLL_RxVGA2GetVCM());

	// EN
	chbPwrVGA2Mods->SetValue(LMLL_RxVGA2GetPwrVGA2Mods());

	// DECODE
	rgrDecode->SetSelection(LMLL_RxVGA2GetDecode());

	// VGA2GAIN[4:0]
	cmbVga2G_u->SetSelection(LMLL_RxVGA2GetVga2G_u());

	// PD[9]
	chbPwrDCCurrR->SetValue(LMLL_RxVGA2GetPwrDCCurrR());
	// chbPwrDCCurrR->SetValue(!chbPwrDCCurrR->Checked;

	// PD[8]
	chbPwrDCDACB->SetValue(LMLL_RxVGA2GetPwrDCDACB());
	// chbPwrDCDACB->SetValue(!chbPwrDCDACB->Checked;

	// PD[7]
	chbPwrDCCmpB->SetValue(LMLL_RxVGA2GetPwrDCCmpB());
	// chbPwrDCCmpB->SetValue(!chbPwrDCCmpB->Checked;

	// PD[6]
	chbPwrDCDACA->SetValue(LMLL_RxVGA2GetPwrDCDACA());
	// chbPwrDCDACA->SetValue(!chbPwrDCDACA->Checked);

	// PD[5]
	chbPwrDCCmpA->SetValue(LMLL_RxVGA2GetPwrDCCmpA());
	// chbPwrDCCmpA->SetValue(!chbPwrDCCmpA->Checked);

	// PD[4]
	chbPwrBG->SetValue(LMLL_RxVGA2GetPwrBG());
	// chbPwrBG->SetValue(!chbPwrBG->Checked);

	// PD[3]
	chbPwrBypAB->SetValue(LMLL_RxVGA2GetPwrBypAB());
	// chbPwrBypAB->SetValue(!chbPwrBypAB->Checked);

	// PD[2]
	chbPwrBypB->SetValue(LMLL_RxVGA2GetPwrBypB());
	// chbPwrBypB->SetValue(!chbPwrBypB->Checked);

	// PD[1]
	chbPwrBypA->SetValue(LMLL_RxVGA2GetPwrBypA());
	// chbPwrBypA->SetValue(!chbPwrBypA->Checked);

	// PD[0]
	chbPwrCurrRef->SetValue(LMLL_RxVGA2GetPwrCurrRef());
	// chbPwrCurrRef->SetValue(!chbPwrCurrRef->Checked);

	// VGA2GAINB[3:0]
	cmbVga2GB_t->SetSelection(LMLL_RxVGA2GetVga2GB_t());

	// VGA2GAINA[3:0]
	cmbVga2GA_t->SetSelection(LMLL_RxVGA2GetVga2GA_t());

	SetGuiDecode();

	return bRez;
};

void pnlRxVGA2::OnEraseBackground(wxEraseEvent& event)
{
}

void pnlRxVGA2::FillComboBoxes()
{
    Freeze();
    wxString cs_Numbers[64];
    for(int i=0; i<64; i++)
        cs_Numbers[i] = wxString::Format("%i", i);

	int itmp;
	// VCM related
	double V1 = 0.9;
	double VLSB = 0.04;
	double VCMV;

	// VCM[3:0]
	itmp = 0;
	cmbVCM->Clear();
	for (int i = 0; i <= 7; i++)
	{
		VCMV = V1 - (i - 7) * VLSB;
		cs_Numbers[itmp++] = wxString::Format("%.6g", VCMV);
	};
	for (int i = 14; i >= 8; i--)
	{
		VCMV = V1 + (i - 15) * VLSB;
		cs_Numbers[itmp++] = wxString::Format("%.6g", VCMV);
	};
	cmbVCM->Append( 15, cs_Numbers);
	cmbVCM->SetSelection(7);

	// VGA2GAIN[4:0]
	cmbVga2G_u->Clear();
	itmp = 0;
	for (int i = 0; i < 11; i++)
	{
		cs_Numbers[i] = wxString::Format("%i", itmp);
		itmp += 3;
	};
    cmbVga2G_u->Append( 11, cs_Numbers);
	cmbVga2G_u->SetSelection(1);

	// VGA2GAINB[3:0]
	cmbVga2GB_t->Clear();
	for(int i=0; i<11; i++)
        cs_Numbers[i] = wxString::Format("%i", i*3);
	cmbVga2GB_t->Append(11, cs_Numbers);
	cmbVga2GB_t->SetSelection(0);

	// VGA2GAINA[3:0]
	cmbVga2GA_t->Clear();
	cmbVga2GA_t->Append(11, cs_Numbers);
	cmbVga2GA_t->SetSelection(1);

	// DC_ADDR[3:0]
	cmbDCCalAddr->Clear();
	 for(int i=0; i<5; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
    cmbDCCalAddr->Append( 5, cs_Numbers);
    cmbDCCalAddr->SetSelection(0);

	// DC_CNTVAL[5:0]
	cmbCalVal->Clear();
	 for(int i=0; i<64; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
    cmbCalVal->Append( 64, cs_Numbers);
	cmbCalVal->SetSelection(31);

	Thaw();
}
