// -----------------------------------------------------------------------------
// FILE:        "pnlRxLPF.cpp"
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
#include "pnlRxLPF.h"
#include "ctr_6002dr2_LogicDLL.h"
#include "CommonFile.h"

#include "pnlADDC.h"

//(*InternalHeaders(pnlRxLPF)
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

//(*IdInit(pnlRxLPF)
const long pnlRxLPF::ID_BUTTON1 = wxNewId();
const long pnlRxLPF::ID_BUTTON2 = wxNewId();
const long pnlRxLPF::ID_BUTTON4 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT1 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT2 = wxNewId();
const long pnlRxLPF::ID_STATICLINE1 = wxNewId();
const long pnlRxLPF::ID_COMBOBOX1 = wxNewId();
const long pnlRxLPF::ID_COMBOBOX2 = wxNewId();
const long pnlRxLPF::ID_BUTTON5 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT3 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT7 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT4 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT8 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT5 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT9 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT6 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT10 = wxNewId();
const long pnlRxLPF::ID_CHECKBOX2 = wxNewId();
const long pnlRxLPF::ID_CHECKBOX1 = wxNewId();
const long pnlRxLPF::ID_CHECKBOX3 = wxNewId();
const long pnlRxLPF::ID_CHECKBOX4 = wxNewId();
const long pnlRxLPF::ID_CHECKBOX5 = wxNewId();
const long pnlRxLPF::ID_CHECKBOX6 = wxNewId();
const long pnlRxLPF::ID_COMBOBOX3 = wxNewId();
const long pnlRxLPF::ID_RADIOBOX1 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT11 = wxNewId();
const long pnlRxLPF::ID_STATICTEXT12 = wxNewId();
const long pnlRxLPF::ID_COMBOBOX4 = wxNewId();
const long pnlRxLPF::ID_COMBOBOX5 = wxNewId();
const long pnlRxLPF::ID_RADIOBOX2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlRxLPF,wxPanel)
	//(*EventTable(pnlRxLPF)
	//*)
END_EVENT_TABLE()

pnlRxLPF::pnlRxLPF(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
    m_frmADDC = NULL;
	m_cVer = 2;
	m_cRev = 2;
	m_cMask = 0;
	BuildContent(parent,id,pos,size);
}

void pnlRxLPF::Initialize(pnlADDC *ADDC)
{
	sendChanges = false;
	m_cMAddr = LMLL_RxLPFGetAddr();
	m_frmADDC = ADDC;
    FillComboBoxes();
	SetGuiDefaults();
	sendChanges = true;
};

void pnlRxLPF::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlRxLPF)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxSize(350,253), wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
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
	FlexGridSizer6->Add(lbDC_REGVAL, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Lock Pattern:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_LOCK = new wxStaticText(this, ID_STATICTEXT8, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer6->Add(lblDC_LOCK, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Calibration Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_CLBR_DONE = new wxStaticText(this, ID_STATICTEXT9, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer6->Add(lblDC_CLBR_DONE, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Comparator Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer6->Add(StaticText6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_UD = new wxStaticText(this, ID_STATICTEXT10, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer6->Add(lblDC_UD, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrLpfMods = new wxCheckBox(this, ID_CHECKBOX2, _("LPF Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chbPwrLpfMods->SetValue(false);
	StaticBoxSizer2->Add(chbPwrLpfMods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrLpf = new wxCheckBox(this, ID_CHECKBOX1, _("LPF Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chbPwrLpf->SetValue(false);
	StaticBoxSizer2->Add(chbPwrLpf, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCDac = new wxCheckBox(this, ID_CHECKBOX3, _("DC Offset DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chbPwrDCDac->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCDac, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCRef = new wxCheckBox(this, ID_CHECKBOX4, _("dc_ref_con3 Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chbPwrDCRef->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCRef, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCmpr = new wxCheckBox(this, ID_CHECKBOX5, _("DC Offset Comparator Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chbPwrDCCmpr->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCmpr, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbTX_DACBUF_EN = new wxCheckBox(this, ID_CHECKBOX6, _("DAC Buffer Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chbTX_DACBUF_EN->SetValue(false);
	StaticBoxSizer2->Add(chbTX_DACBUF_EN, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("LPF Bandwidth"));
	cmbLpfBw = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(75,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	StaticBoxSizer3->Add(cmbLpfBw, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Normal Operation"),
		_("Bypass LPF")
	};
	rgrLpfByp = new wxRadioBox(this, ID_RADIOBOX1, _("Test"), wxPoint(344,120), wxSize(128,63), 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	BoxSizer1->Add(rgrLpfByp, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(BoxSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Process Calibration Values"));
	FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT11, _("DC Offset Resistor:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer1->Add(StaticText7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT12, _("From TRX_LPF_CAL:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer1->Add(StaticText8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCOffset = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	FlexGridSizer1->Add(cmbDCOffset, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRcCal = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer1->Add(cmbRcCal, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_RADIOBOX2, _("Decoding"), wxPoint(720,8), wxSize(136,69), 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	FlexGridSizer2->Add(rgrDecode, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer2);
	SetSizer(FlexGridSizer2);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxLPF::btnDCRstClbrClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxLPF::btnDCLoadValClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxLPF::btnDCStartClbrClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxLPF::cmbDCCalAddrChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxLPF::cmbCalValChange);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxLPF::btnDCReadValClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxLPF::chbPwrLpfModsClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxLPF::chbPwrLpfClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxLPF::chbPwrDCDacClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxLPF::chbPwrDCRefClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxLPF::chbPwrDCCmprClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxLPF::chbTX_DACBUF_ENClick);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxLPF::cmbLpfBwChange);
	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxLPF::rgrLpfBypClick);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxLPF::cmbDCOffsetChange);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxLPF::cmbRcCalChange);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxLPF::rgrDecodeClick);
	//*)
}

pnlRxLPF::~pnlRxLPF()
{
	//(*Destroy(pnlRxLPF)
	//*)
}

void pnlRxLPF::SetGuiDefaults()
{
    Freeze();
   	cmbLpfBw->SetSelection(0);
	// EN
	chbPwrLpfMods->SetValue(true);
	// DECODE
	rgrDecode->SetSelection(0);

	// BYP_EN_LPF
	rgrLpfByp->SetSelection(0);
	// DCO_DACCAL_LPF[5:0]
	cmbDCOffset->SetSelection(0x0C);

	// TX_DACBUF_EN
	if (m_cMAddr == TxLpfAddr)
	{
		chbTX_DACBUF_EN->Enable(true);
		chbTX_DACBUF_EN->SetValue(true);
		chbTX_DACBUF_EN->Show(true);
	}
	else
	{
		chbTX_DACBUF_EN->Enable(false);
		chbTX_DACBUF_EN->Show(false);
	};
	// RCCAL_LPF[2:0]
	cmbRcCal->SetSelection(3);
	// PD_DCOCMP_LPF
	chbPwrDCCmpr->SetValue(true);
	// PD_DCODAC_LPF
	chbPwrDCDac->SetValue(true);
	// PD_DCOREF_LPF
	chbPwrDCRef->SetValue(true);
	// PD_FIL_LPF
	chbPwrLpf->SetValue(true);

	// DC_ADDR[3:0]
	cmbDCCalAddr->SetSelection(0);

	// DC_CNTVAL[5:0]
	cmbCalVal->SetSelection(31);

	SetGuiDecode();
	Thaw();
};

void pnlRxLPF::SetGuiDecode()
{
	if (rgrDecode->GetSelection() == 0)
	{
		// Decode
		chbPwrLpfMods->Enable(true);

		chbPwrLpf->Enable(false);
		chbPwrDCDac->Enable(false);
		chbPwrDCRef->Enable(false);
		if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
		{
			chbPwrDCCmpr->Enable(true);
		}
		else
		{
			chbPwrDCCmpr->Enable(false);
		};
		chbTX_DACBUF_EN->Enable(false);
	}
	else
	{
		// Direct control
		chbPwrLpfMods->Enable(false);

		chbPwrLpf->Enable(true);
		chbPwrDCDac->Enable(true);
		chbPwrDCRef->Enable(true);
		chbPwrDCCmpr->Enable(true);
		chbTX_DACBUF_EN->Enable(true);
	};

	if(m_frmADDC)
		m_frmADDC->SetGuiDecode(rgrDecode->GetSelection());
};

// ---------------------------------------------------------------------------
// updates GUI data values
// ---------------------------------------------------------------------------
bool pnlRxLPF::UpdateGUI()
{
	int itmp;
	bool bRez = true;

	int iDC_REGVAL;
	int iDC_LOCK;
	int iDC_CLBR_DONE;
	int iDC_UD;

	LMLL_RxLPFGetDCCalibrationData(iDC_REGVAL, iDC_LOCK, iDC_CLBR_DONE, iDC_UD);
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
	//cmbCalVal->SetSelection( LMLL_RxLPFGetCalVal();
	cmbCalVal->SetSelection( iDC_REGVAL);

	// DC_START_CLBR
	// itmp = DC_START_CLBR_r03_b55();

	// DC_LOAD
	// itmp = DC_LOAD_r03_b44();

	// DC_SRESET
	// itmp = DC_SRESET_r03_b33();

	// DC_ADDR[2:0]
	// itmp = DC_ADDR_r03_b20();
	// if(itmp > 4) {itmp = 4; bRez = false;}
	cmbDCCalAddr->SetSelection( LMLL_RxLPFGetDCCalAddr());

	// BWC_LPF[3:0]
	cmbLpfBw->SetSelection( LMLL_RxLPFGetLpfBw());

	// EN
	chbPwrLpfMods->SetValue(LMLL_RxLPFGetPwrLpfMods());

	// DECODE
	rgrDecode->SetSelection( LMLL_RxLPFGetDecode());

	// BYP_EN_LPF
	rgrLpfByp->SetSelection( LMLL_RxLPFGetLpfByp());

	// DCO_DACCAL_LPF[5:0]
	cmbDCOffset->SetSelection( LMLL_RxLPFGetDCOffset());

    /*
	// TX_DACBUF_EN
	if (m_cMAddr == TxLpfAddr)
	{
		chbTX_DACBUF_EN->SetValue(LMLL_RxLPFGetTX_DACBUF_EN());
		// chbTX_DACBUF_EN->SetValue(!chbTX_DACBUF_EN->Checked);
	};
	*/

	// RCCAL_LPF[2:0]
	cmbRcCal->SetSelection( LMLL_RxLPFGetRcCal());

	// PD_DCOCMP_LPF
	chbPwrDCCmpr->SetValue(LMLL_RxLPFGetPwrDCCmpr());
	// chbPwrDCCmpr->SetValue(!chbPwrDCCmpr->Checked);

	// PD_DCODAC_LPF
	chbPwrDCDac->SetValue(LMLL_RxLPFGetPwrDCDac());
	// chbPwrDCDac->SetValue(!chbPwrDCDac->Checked);

	// PD_DCOREF_LPF
	chbPwrDCRef->SetValue(LMLL_RxLPFGetPwrDCRef());
	// chbPwrDCRef->SetValue(!chbPwrDCRef->Checked);

	// PD_FIL_LPF
	chbPwrLpf->SetValue(LMLL_RxLPFGetPwrLpf());
	// chbPwrLpf->SetValue(!chbPwrLpf->Checked);

	if (m_frmADDC)
		m_frmADDC->UpdateGUI();

	SetGuiDecode();

	return bRez;
};

// ---------------------------------------------------------------------------
void pnlRxLPF::cmbLpfBwChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetLpfBw(cmbLpfBw->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::chbPwrLpfModsClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetPwrLpfMods(chbPwrLpfMods->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::rgrDecodeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetDecode(rgrDecode->GetSelection());
	SetGuiDecode();
}

// ---------------------------------------------------------------------------
void pnlRxLPF::rgrLpfBypClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetLpfByp(rgrLpfByp->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::cmbDCOffsetChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetDCOffset(cmbDCOffset->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::cmbRcCalChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetRcCal(cmbRcCal->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::chbPwrLpfClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetPwrLpf(chbPwrLpf->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::chbPwrDCDacClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetPwrDCDac(chbPwrDCDac->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::chbPwrDCRefClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetPwrDCRef(chbPwrDCRef->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::chbPwrDCCmprClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetPwrDCCmpr(chbPwrDCCmpr->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::chbTX_DACBUF_ENClick(wxCommandEvent& event)
{
	//if(sendChanges) LMLL_RxLPFSetTX_DACBUF_EN(chbTX_DACBUF_EN->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::cmbDCCalAddrChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxLPFSetDCCalAddr(cmbDCCalAddr->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::cmbCalValChange(wxCommandEvent& event)
{
	//if(sendChanges) LMLL_RxLPFSetCalVal(cmbCalVal->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxLPF::btnDCRstClbrClick(wxCommandEvent& event)
{
	LMLL_RxLPFDCResetCalibration();
}

// ---------------------------------------------------------------------------
void pnlRxLPF::btnDCLoadValClick(wxCommandEvent& event)
{
	LMLL_RxLPFDCLoadValues(cmbCalVal->GetSelection());
}

void pnlRxLPF::btnDCReadValClick(wxCommandEvent& event)
{
	int DC_regVal;
	int DC_lock;
	int DC_clbr;
	int DC_ud;
	LMLL_RxLPFGetDCCalibrationData(DC_regVal, DC_lock, DC_clbr, DC_ud);
	// DC_REGVAL[5:0]
	lbDC_REGVAL->SetLabel( wxString::Format("%i", DC_regVal ));
	// DC_LOCK[2:0]
	lblDC_LOCK->SetLabel(wxString::Format("%i", DC_lock ));
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
void pnlRxLPF::btnDCStartClbrClick(wxCommandEvent& event)
{
	LMLL_RxLPFDCStartCalibration();
}

void pnlRxLPF::FillComboBoxes()
{
    Freeze();
    wxString cs_Numbers[64];
    for(int i=0; i<64; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
	// BWC_LPF[3:0]
	cmbLpfBw->Clear();
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
	cmbLpfBw->Append(16, cs_Bw);
	cmbLpfBw->SetSelection(0);

	cmbDCOffset->Clear();
    cmbDCOffset->Append( 64, cs_Numbers);
	cmbDCOffset->SetSelection(0x0C);

	// RCCAL_LPF[2:0]
	cmbRcCal->Clear();
    cmbRcCal->Append( 8, cs_Numbers);
	cmbRcCal->SetSelection(3);

	// DC_ADDR[3:0]
	cmbDCCalAddr->Clear();
	cmbDCCalAddr->Append( 5, cs_Numbers);
	cmbDCCalAddr->SetSelection(0);

	// DC_CNTVAL[5:0]
	cmbCalVal->Clear();
    cmbCalVal->Append( 64, cs_Numbers);
	cmbCalVal->SetSelection(31);

	Thaw();
}
