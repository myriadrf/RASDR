// -----------------------------------------------------------------------------
// FILE:        "pnlRxFE.cpp"
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
#include "pnlRxFE.h"
#include "ctr_6002dr2_LogicDLL.h"
//(*InternalHeaders(pnlRxFE)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlRxFE)
const long pnlRxFE::ID_RADIOBOX2 = wxNewId();
const long pnlRxFE::ID_CHECKBOX1 = wxNewId();
const long pnlRxFE::ID_CHECKBOX2 = wxNewId();
const long pnlRxFE::ID_CHECKBOX3 = wxNewId();
const long pnlRxFE::ID_CHECKBOX4 = wxNewId();
const long pnlRxFE::ID_CHECKBOX5 = wxNewId();
const long pnlRxFE::ID_CHECKBOX6 = wxNewId();
const long pnlRxFE::ID_CHECKBOX7 = wxNewId();
const long pnlRxFE::ID_STATICTEXT1 = wxNewId();
const long pnlRxFE::ID_CHECKBOX8 = wxNewId();
const long pnlRxFE::ID_COMBOBOX1 = wxNewId();
const long pnlRxFE::ID_STATICTEXT2 = wxNewId();
const long pnlRxFE::ID_STATICTEXT3 = wxNewId();
const long pnlRxFE::ID_COMBOBOX2 = wxNewId();
const long pnlRxFE::ID_COMBOBOX3 = wxNewId();
const long pnlRxFE::ID_STATICTEXT4 = wxNewId();
const long pnlRxFE::ID_STATICTEXT5 = wxNewId();
const long pnlRxFE::ID_COMBOBOX4 = wxNewId();
const long pnlRxFE::ID_COMBOBOX5 = wxNewId();
const long pnlRxFE::ID_STATICTEXT6 = wxNewId();
const long pnlRxFE::ID_STATICTEXT7 = wxNewId();
const long pnlRxFE::ID_COMBOBOX6 = wxNewId();
const long pnlRxFE::ID_COMBOBOX7 = wxNewId();
const long pnlRxFE::ID_STATICTEXT8 = wxNewId();
const long pnlRxFE::ID_COMBOBOX8 = wxNewId();
const long pnlRxFE::ID_STATICTEXT9 = wxNewId();
const long pnlRxFE::ID_COMBOBOX9 = wxNewId();
const long pnlRxFE::ID_STATICTEXT10 = wxNewId();
const long pnlRxFE::ID_COMBOBOX10 = wxNewId();
const long pnlRxFE::ID_STATICTEXT11 = wxNewId();
const long pnlRxFE::ID_COMBOBOX11 = wxNewId();
const long pnlRxFE::ID_STATICTEXT12 = wxNewId();
const long pnlRxFE::ID_STATICTEXT13 = wxNewId();
const long pnlRxFE::ID_COMBOBOX12 = wxNewId();
const long pnlRxFE::ID_COMBOBOX13 = wxNewId();
const long pnlRxFE::ID_STATICTEXT14 = wxNewId();
const long pnlRxFE::ID_STATICTEXT15 = wxNewId();
const long pnlRxFE::ID_COMBOBOX14 = wxNewId();
const long pnlRxFE::ID_COMBOBOX15 = wxNewId();
const long pnlRxFE::ID_STATICTEXT16 = wxNewId();
const long pnlRxFE::ID_STATICTEXT17 = wxNewId();
const long pnlRxFE::ID_STATICTEXT18 = wxNewId();
const long pnlRxFE::ID_COMBOBOX16 = wxNewId();
const long pnlRxFE::ID_COMBOBOX17 = wxNewId();
const long pnlRxFE::ID_COMBOBOX18 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlRxFE,wxPanel)
	//(*EventTable(pnlRxFE)
	//*)
END_EVENT_TABLE()

pnlRxFE::pnlRxFE(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
	BuildContent(parent,id,pos,size);
}

void pnlRxFE::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlRxFE)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxSize(880,526), wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer6 = new wxFlexGridSizer(1, 4, 0, 0);
	FlexGridSizer7 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer7->AddGrowableRow(1);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_RADIOBOX2, _("Decoding"), wxPoint(16,8), wxSize(144,63), 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrDecode->SetSelection(0);
	FlexGridSizer7->Add(rgrDecode, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrRxFeMods = new wxCheckBox(this, ID_CHECKBOX1, _("RxFE Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chbPwrRxFeMods->SetValue(false);
	StaticBoxSizer1->Add(chbPwrRxFeMods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_TIA_RXFE = new wxCheckBox(this, ID_CHECKBOX2, _("TIA Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkPD_TIA_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_TIA_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_MXLOB_RXFE = new wxCheckBox(this, ID_CHECKBOX3, _("MXLOB Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkPD_MXLOB_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_MXLOB_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_MIX_RXFE = new wxCheckBox(this, ID_CHECKBOX4, _("MIX Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkPD_MIX_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_MIX_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_LNA_RXFE = new wxCheckBox(this, ID_CHECKBOX5, _("LNA Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkPD_LNA_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_LNA_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkRINEN_MIX_RXFE = new wxCheckBox(this, ID_CHECKBOX6, _("MIX Term Resistor Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkRINEN_MIX_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkRINEN_MIX_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("LNA Control"));
	FlexGridSizer1 = new wxFlexGridSizer(8, 2, 0, 0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer1->AddGrowableRow(1);
	FlexGridSizer1->AddGrowableRow(2);
	FlexGridSizer1->AddGrowableRow(3);
	FlexGridSizer1->AddGrowableRow(4);
	FlexGridSizer1->AddGrowableRow(5);
	FlexGridSizer1->AddGrowableRow(6);
	FlexGridSizer1->AddGrowableRow(7);
	chkINLOAD_LNA_RXFE = new wxCheckBox(this, ID_CHECKBOX7, _("Internal LNA Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkINLOAD_LNA_RXFE->SetValue(false);
	FlexGridSizer1->Add(chkINLOAD_LNA_RXFE, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Capacitance to BE:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkXLOAD_LNA_RXFE = new wxCheckBox(this, ID_CHECKBOX8, _("External LNA Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkXLOAD_LNA_RXFE->SetValue(false);
	FlexGridSizer1->Add(chkXLOAD_LNA_RXFE, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCBE_LNA_RXFE = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	FlexGridSizer1->Add(cmbCBE_LNA_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("LNA Gain Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("LNA3 Fine Gain:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbG_LNA_RXFE = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer1->Add(cmbG_LNA_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbG_FINE_LNA3_RXFE = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	FlexGridSizer1->Add(cmbG_FINE_LNA3_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Active LNA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("LNA Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(StaticText5, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbLNASEL_RXFE = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	FlexGridSizer1->Add(cmbLNASEL_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_LNA_RXFE = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer1->Add(cmbICT_LNA_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("LNA Load Resistor,\n External Load (Gain):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("LNA Load Resistor,\n Internal Load(Gain):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer1->Add(StaticText7, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRDLEXT_LNA_RXFE = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	FlexGridSizer1->Add(cmbRDLEXT_LNA_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRDLINT_LNA_RXFE = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	FlexGridSizer1->Add(cmbRDLINT_LNA_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("MIX Control"));
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("MIX Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticBoxSizer3->Add(StaticText8, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_MIX_RXFE = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	StaticBoxSizer3->Add(cmbICT_MIX_RXFE, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("MIX Input:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticBoxSizer3->Add(StaticText9, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbIN1SEL_MIX_RXFE = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
	StaticBoxSizer3->Add(cmbIN1SEL_MIX_RXFE, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("MXLOB Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticBoxSizer3->Add(StaticText10, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_MXLOB_RXFE = new wxComboBox(this, ID_COMBOBOX10, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX10"));
	StaticBoxSizer3->Add(cmbICT_MXLOB_RXFE, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("LO Bias Of The Mix:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticBoxSizer3->Add(StaticText11, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbLOBN_MIX_RXFE = new wxComboBox(this, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX11"));
	StaticBoxSizer3->Add(cmbLOBN_MIX_RXFE, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("IP2 Cancellation"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Channel I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer2->Add(StaticText12, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Channel Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer2->Add(StaticText13, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbIP2TRIM_I_RXFE = new wxComboBox(this, ID_COMBOBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX12"));
	FlexGridSizer2->Add(cmbIP2TRIM_I_RXFE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbIP2TRIM_Q_RXFE = new wxComboBox(this, ID_COMBOBOX13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX13"));
	FlexGridSizer2->Add(cmbIP2TRIM_Q_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("DC Offset Cancellation"));
	FlexGridSizer3 = new wxFlexGridSizer(2, 2, 0, 0);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Channel I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer3->Add(StaticText14, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Channel Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer3->Add(StaticText15, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCOFF_I_RXFE = new wxComboBox(this, ID_COMBOBOX14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX14"));
	FlexGridSizer3->Add(cmbDCOFF_I_RXFE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCOFF_Q_RXFE = new wxComboBox(this, ID_COMBOBOX15, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX15"));
	FlexGridSizer3->Add(cmbDCOFF_Q_RXFE, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VGA1 Control"));
	FlexGridSizer4 = new wxFlexGridSizer(2, 3, 0, 0);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Feedback Resistor (Gain):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer4->Add(StaticText16, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Feedback Capacitor (BW):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer4->Add(StaticText17, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer4->Add(StaticText18, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRFB_TIA_RXFE = new wxComboBox(this, ID_COMBOBOX16, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX16"));
	FlexGridSizer4->Add(cmbRFB_TIA_RXFE, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbCFB_TIA_RXFE = new wxComboBox(this, ID_COMBOBOX17, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX17"));
	FlexGridSizer4->Add(cmbCFB_TIA_RXFE, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TIA_RXFE = new wxComboBox(this, ID_COMBOBOX18, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX18"));
	FlexGridSizer4->Add(cmbICT_TIA_RXFE, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(FlexGridSizer4, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(StaticBoxSizer6, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer5);
	SetSizer(FlexGridSizer5);
	Layout();

	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::rgrDecodeClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chbPwrRxFeModsClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chkPD_TIA_RXFEClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chkPD_MXLOB_RXFEClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chkPD_MIX_RXFEClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chkPD_LNA_RXFEClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chkRINEN_MIX_RXFEClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chkINLOAD_LNA_RXFEClick);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::chkXLOAD_LNA_RXFEClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbCBE_LNA_RXFEChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbG_LNA_RXFEChange);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbG_FINE_LNA3_RXFEChange);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbLNASEL_RXFEChange);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbICT_LNA_RXFEChange);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbRDLEXT_LNA_RXFEChange);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbRDLINT_LNA_RXFEChange);
	Connect(ID_COMBOBOX8,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbICT_MIX_RXFEChange);
	Connect(ID_COMBOBOX9,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbIN1SEL_MIX_RXFEChange);
	Connect(ID_COMBOBOX10,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbICT_MXLOB_RXFEChange);
	Connect(ID_COMBOBOX11,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbLOBN_MIX_RXFEChange);
	Connect(ID_COMBOBOX12,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbIP2TRIM_I_RXFEChange);
	Connect(ID_COMBOBOX13,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbIP2TRIM_Q_RXFEChange);
	Connect(ID_COMBOBOX14,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbDCOFF_I_RXFEChange);
	Connect(ID_COMBOBOX15,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbDCOFF_Q_RXFEChange);
	Connect(ID_COMBOBOX16,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbRFB_TIA_RXFEChange);
	Connect(ID_COMBOBOX17,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbCFB_TIA_RXFEChange);
	Connect(ID_COMBOBOX18,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::cmbICT_TIA_RXFEChange);
	//*)
}

pnlRxFE::~pnlRxFE()
{
	//(*Destroy(pnlRxFE)
	//*)
}

void pnlRxFE::rgrDecodeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetDecode(rgrDecode->GetSelection());
	SetGuiDecode();
}

// ---------------------------------------------------------------------------
void pnlRxFE::chbPwrRxFeModsClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetPwrRxFeMods(chbPwrRxFeMods->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbIN1SEL_MIX_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetIN1SEL_MIX_RXFE(cmbIN1SEL_MIX_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbDCOFF_I_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetDCOFF_I_RXFE(cmbDCOFF_I_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::chkINLOAD_LNA_RXFEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetINLOAD_LNA_RXFE(chkINLOAD_LNA_RXFE->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbDCOFF_Q_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetDCOFF_Q_RXFE(cmbDCOFF_Q_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::chkXLOAD_LNA_RXFEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetXLOAD_LNA_RXFE(chkXLOAD_LNA_RXFE->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbIP2TRIM_I_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetIP2TRIM_I_RXFE(cmbIP2TRIM_I_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbIP2TRIM_Q_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetIP2TRIM_Q_RXFE(cmbIP2TRIM_Q_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbG_LNA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetG_LNA_RXFE(cmbG_LNA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbLNASEL_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetLNASEL_RXFE(cmbLNASEL_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbCBE_LNA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetCBE_LNA_RXFE(cmbCBE_LNA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbRFB_TIA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetRFB_TIA_RXFE(cmbRFB_TIA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbCFB_TIA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetCFB_TIA_RXFE(cmbCFB_TIA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbRDLEXT_LNA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetRDLEXT_LNA_RXFE(cmbRDLEXT_LNA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbRDLINT_LNA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetRDLINT_LNA_RXFE(cmbRDLINT_LNA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbICT_MIX_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetICT_MIX_RXFE(cmbICT_MIX_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbICT_LNA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetICT_LNA_RXFE(cmbICT_LNA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbICT_TIA_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetICT_TIA_RXFE(cmbICT_TIA_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbICT_MXLOB_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetICT_MXLOB_RXFE(cmbICT_MXLOB_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbLOBN_MIX_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetLOBN_MIX_RXFE(cmbLOBN_MIX_RXFE->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlRxFE::chkPD_TIA_RXFEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetPD_TIA_RXFE(chkPD_TIA_RXFE->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxFE::chkPD_MXLOB_RXFEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetPD_MXLOB_RXFE(chkPD_MXLOB_RXFE->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxFE::chkPD_MIX_RXFEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetPD_MIX_RXFE(chkPD_MIX_RXFE->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxFE::chkPD_LNA_RXFEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetPD_LNA_RXFE(chkPD_LNA_RXFE->GetValue());
}

// ---------------------------------------------------------------------------
void pnlRxFE::cmbG_FINE_LNA3_RXFEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetG_FINE_LNA3_RXFE(cmbG_FINE_LNA3_RXFE->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlRxFE::chkRINEN_MIX_RXFEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_RxFESetRINEN_MIX_RXFE(chkRINEN_MIX_RXFE->GetValue());
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// updates GUI data values
// ---------------------------------------------------------------------------
bool pnlRxFE::UpdateGUI()
{
	int itmp;
	bool bRez = true;

	// DECODE
	rgrDecode->SetSelection(LMLL_RxFEGetDecode());

	// EN
	chbPwrRxFeMods->SetValue(LMLL_RxFEGetPwrRxFeMods());

	// IN1SEL_MIX_RXFE
	cmbIN1SEL_MIX_RXFE->SetSelection(LMLL_RxFEGetIN1SEL_MIX_RXFE());

	// DCOFF_I_RXFE[6:0]
	cmbDCOFF_I_RXFE->SetSelection(LMLL_RxFEGetDCOFF_I_RXFE());

	// INLOAD_LNA_RXFE
	chkINLOAD_LNA_RXFE->SetValue(LMLL_RxFEGetINLOAD_LNA_RXFE());

	// DCOFF_Q_RXFE[6:0]
	cmbDCOFF_Q_RXFE->SetSelection(LMLL_RxFEGetDCOFF_Q_RXFE());

	// XLOAD_LNA_RXFE
	chkXLOAD_LNA_RXFE->SetValue(LMLL_RxFEGetXLOAD_LNA_RXFE());

	// IP2TRIM_I_RXFE[6:0]
	cmbIP2TRIM_I_RXFE->SetSelection(LMLL_RxFEGetIP2TRIM_I_RXFE());

	// IP2TRIM_Q_RXFE[6:0]
	cmbIP2TRIM_Q_RXFE->SetSelection(LMLL_RxFEGetIP2TRIM_Q_RXFE());

	// G_LNA_RXFE[1:0]
	cmbG_LNA_RXFE->SetSelection(LMLL_RxFEGetG_LNA_RXFE());

	// LNASEL_RXFE[1:0]
	cmbLNASEL_RXFE->SetSelection(LMLL_RxFEGetLNASEL_RXFE());

	// CBE_LNA_RXFE[3:0]
	cmbCBE_LNA_RXFE->SetSelection(LMLL_RxFEGetCBE_LNA_RXFE());

	// RFB_TIA_RXFE[6:0]
	cmbRFB_TIA_RXFE->SetSelection(LMLL_RxFEGetRFB_TIA_RXFE());

	// CFB_TIA_RXFE[6:0]
	cmbCFB_TIA_RXFE->SetSelection(LMLL_RxFEGetCFB_TIA_RXFE());

	// RDLEXT_LNA_RXFE[5:0]
	cmbRDLEXT_LNA_RXFE->SetSelection(LMLL_RxFEGetRDLEXT_LNA_RXFE());

	// RDLINT_LNA_RXFE[5:0]
	cmbRDLINT_LNA_RXFE->SetSelection(LMLL_RxFEGetRDLINT_LNA_RXFE());

	// ICT_MIX_RXFE[3:0]
	cmbICT_MIX_RXFE->SetSelection(LMLL_RxFEGetICT_MIX_RXFE());

	// ICT_LNA_RXFE[3:0]
	cmbICT_LNA_RXFE->SetSelection(LMLL_RxFEGetICT_LNA_RXFE());

	// ICT_TIA_RXFE[3:0]
	cmbICT_TIA_RXFE->SetSelection(LMLL_RxFEGetICT_TIA_RXFE());

	// ICT_MXLOB_RXFE[3:0]
	cmbICT_MXLOB_RXFE->SetSelection(LMLL_RxFEGetICT_MXLOB_RXFE());

	// LOBN_MIX_RXFE[3:0]
	cmbLOBN_MIX_RXFE->SetSelection(LMLL_RxFEGetLOBN_MIX_RXFE());

	// RINEN_MIX_RXFE
	chkRINEN_MIX_RXFE->SetValue(LMLL_RxFEGetRINEN_MIX_RXFE());

	// G_FINE_LNA3_RXFE[1:0]
	cmbG_FINE_LNA3_RXFE->SetSelection(LMLL_RxFEGetG_FINE_LNA3_RXFE());

	// PD_TIA_RXFE
	chkPD_TIA_RXFE->SetValue(LMLL_RxFEGetPD_TIA_RXFE());

	// PD_MXLOB_RXFE
	chkPD_MXLOB_RXFE->SetValue(LMLL_RxFEGetPD_MXLOB_RXFE());

	// PD_MIX_RXFE
	chkPD_MIX_RXFE->SetValue(LMLL_RxFEGetPD_MIX_RXFE());

	// PD_LNA_RXFE
	chkPD_LNA_RXFE->SetValue(LMLL_RxFEGetPD_LNA_RXFE());

	SetGuiDecode();

	return bRez;
};

// ---------------------------------------------------------------------------
void pnlRxFE::Initialize()
{
	sendChanges = false;
	m_cMAddr = LMLL_RxFEGetAddr();
	FillComboBoxes();
	SetGuiDefaults();
	sendChanges = true;
};

// ---------------------------------------------------------------------------
void pnlRxFE::SetGuiDefaults()
{
    Freeze();
	int itmp;

	// DECODE
	rgrDecode->SetSelection(0);
	// EN
	chbPwrRxFeMods->SetValue(true);

	// IN1SEL_MIX_RXFE
	cmbIN1SEL_MIX_RXFE->SetSelection(1);

	// DCOFF_I_RXFE[6:0]
	// DCOFF_Q_RXFE[6:0]
	cmbDCOFF_I_RXFE->SetSelection(63);
	cmbDCOFF_Q_RXFE->SetSelection(63);

	// INLOAD_LNA_RXFE
	chkINLOAD_LNA_RXFE->SetValue(true);

	// XLOAD_LNA_RXFE
	chkXLOAD_LNA_RXFE->SetValue(false);

	// IP2TRIM_I_RXFE[6:0]
	// IP2TRIM_Q_RXFE[6:0]
	cmbIP2TRIM_I_RXFE->SetSelection(63);
	cmbIP2TRIM_Q_RXFE->SetSelection(63);

	// G_LNA_RXFE[1:0]
	cmbG_LNA_RXFE->SetSelection(2);

	// LNASEL_RXFE[1:0]
	cmbLNASEL_RXFE->SetSelection(1);

	// CBE_LNA_RXFE[3:0]
	cmbCBE_LNA_RXFE->SetSelection(0);

	// RFB_TIA_RXFE[6:0]
	cmbRFB_TIA_RXFE->SetSelection(120);

	// CFB_TIA_RXFE[6:0]
	cmbCFB_TIA_RXFE->SetSelection(0);

	// RDLEXT_LNA_RXFE[6:0]
	// RDLINT_LNA_RXFE[6:0]
	cmbRDLEXT_LNA_RXFE->SetSelection(28);
	cmbRDLINT_LNA_RXFE->SetSelection(28);

	// ICT_MIX_RXFE[3:0]
	cmbICT_MIX_RXFE->SetSelection(7);
	// ICT_LNA_RXFE[3:0]
	cmbICT_LNA_RXFE->SetSelection(7);

	// ICT_TIA_RXFE[3:0]
	cmbICT_TIA_RXFE->SetSelection(7);
	// ICT_MXLOB_RXFE[3:0]
	cmbICT_MXLOB_RXFE->SetSelection(7);

	// LOBN_MIX_RXFE[3:0]
	cmbLOBN_MIX_RXFE->SetSelection(3);
	// RINEN_MIX_RXFE
	chkRINEN_MIX_RXFE->SetValue(false);
	// G_FINE_LNA3_RXFE[1:0]
	cmbG_FINE_LNA3_RXFE->SetSelection(0);

	// PD_TIA_RXFE
	chkPD_TIA_RXFE->SetValue(true);
	// PD_MXLOB_RXFE
	chkPD_MXLOB_RXFE->SetValue(true);
	// PD_MIX_RXFE
	chkPD_MIX_RXFE->SetValue(true);
	// PD_LNA_RXFE
	chkPD_LNA_RXFE->SetValue(true);

	SetGuiDecode();
	Thaw();
};

// ---------------------------------------------------------------------------
void pnlRxFE::SetGuiDecode()
{
	if (rgrDecode->GetSelection() == 0)
	{
		// Decode
		chbPwrRxFeMods->Enable(true);

		chkPD_TIA_RXFE->Enable(false);
		chkPD_MXLOB_RXFE->Enable(false);
		chkPD_MIX_RXFE->Enable(false);
		chkPD_LNA_RXFE->Enable(false);
	}
	else
	{
		// Direct control
		chbPwrRxFeMods->Enable(false);

		chkPD_TIA_RXFE->Enable(true);
		chkPD_MXLOB_RXFE->Enable(true);
		chkPD_MIX_RXFE->Enable(true);
		chkPD_LNA_RXFE->Enable(true);
	};
};

void pnlRxFE::FillComboBoxes()
{
    Freeze();
	int itmp;
	wxString *cs_Numbers = new wxString[128];

	// IN1SEL_MIX_RXFE
	wxString cs_IN1SEL[2] = {"To Pads", "To LNA Out"};
	cmbIN1SEL_MIX_RXFE->Clear();
	cmbIN1SEL_MIX_RXFE->Append(2, cs_IN1SEL);
	cmbIN1SEL_MIX_RXFE->SetSelection(1);

	// DCOFF_I_RXFE[6:0]
	// DCOFF_Q_RXFE[6:0]
	cmbDCOFF_I_RXFE->Clear();
	cmbDCOFF_Q_RXFE->Clear();

    for (int i = 0; i < 127; i++)
		cs_Numbers[i] = wxString::Format("%i", i - 63);
	cmbDCOFF_I_RXFE->Append( 127, cs_Numbers );
    cmbDCOFF_Q_RXFE->Append( 127, cs_Numbers );
	cmbDCOFF_I_RXFE->SetSelection(63);
	cmbDCOFF_Q_RXFE->SetSelection(63);

	// IP2TRIM_I_RXFE[6:0]
	// IP2TRIM_Q_RXFE[6:0]
	cmbIP2TRIM_I_RXFE->Clear();
	cmbIP2TRIM_Q_RXFE->Clear();
	cmbIP2TRIM_I_RXFE->Append( 127, cs_Numbers);
	cmbIP2TRIM_Q_RXFE->Append( 127, cs_Numbers);
	cmbIP2TRIM_I_RXFE->SetSelection(63);
	cmbIP2TRIM_Q_RXFE->SetSelection(63);

	// G_LNA_RXFE[1:0]
	cmbG_LNA_RXFE->Clear();
	// cmbG_LNA_RXFE->Append("TBC");
	wxString cs_G_LNA[3] = {"Bypass", "Mid Gain", "Max Gain"};
	cmbG_LNA_RXFE->Append(3, cs_G_LNA);
	cmbG_LNA_RXFE->SetSelection(2);

	// LNASEL_RXFE[1:0]
	cmbLNASEL_RXFE->Clear();
	wxString cs_LNASEL[4] = {"Disabled", "LNA 1", "LNA 2", "LNA 3"};
	cmbLNASEL_RXFE->Append(4, cs_LNASEL);
	cmbLNASEL_RXFE->SetSelection(1);

	// CBE_LNA_RXFE[3:0]
	cmbCBE_LNA_RXFE->Clear();
	for (int i = 0; i < 128; i++)
		cs_Numbers[i] = wxString::Format("%i", i);
    cmbCBE_LNA_RXFE->Append( 16, cs_Numbers);
	cmbCBE_LNA_RXFE->SetSelection(0);

	// RFB_TIA_RXFE[6:0]
	cmbRFB_TIA_RXFE->Clear();
    cmbRFB_TIA_RXFE->Append(128, cs_Numbers);
	cmbRFB_TIA_RXFE->SetSelection(120);

	// CFB_TIA_RXFE[6:0]
	cmbCFB_TIA_RXFE->Clear();
    cmbCFB_TIA_RXFE->Append(128, cs_Numbers);
	cmbCFB_TIA_RXFE->SetSelection(0);

	// RDLEXT_LNA_RXFE[6:0]
	// RDLINT_LNA_RXFE[6:0]
	cmbRDLEXT_LNA_RXFE->Clear();
	cmbRDLINT_LNA_RXFE->Clear();
    cmbRDLEXT_LNA_RXFE->Append( 64, cs_Numbers);
	cmbRDLINT_LNA_RXFE->Append( 64, cs_Numbers);
	cmbRDLEXT_LNA_RXFE->SetSelection(28);
	cmbRDLINT_LNA_RXFE->SetSelection(28);

	// ICT_MIX_RXFE[3:0]
	cmbICT_MIX_RXFE->Clear();
    cmbICT_MIX_RXFE->Append(16, cs_Numbers);
	cmbICT_MIX_RXFE->SetSelection(7);
	// ICT_LNA_RXFE[3:0]
	cmbICT_LNA_RXFE->Clear();
    cmbICT_LNA_RXFE->Append(16, cs_Numbers);
	cmbICT_LNA_RXFE->SetSelection(7);

	// ICT_TIA_RXFE[3:0]
	cmbICT_TIA_RXFE->Clear();
	cmbICT_TIA_RXFE->Append(16, cs_Numbers);
	cmbICT_TIA_RXFE->SetSelection(7);
	// ICT_MXLOB_RXFE[3:0]
	cmbICT_MXLOB_RXFE->Clear();
	cmbICT_MXLOB_RXFE->Append(16, cs_Numbers);
	cmbICT_MXLOB_RXFE->SetSelection(7);

	// LOBN_MIX_RXFE[3:0]
	cmbLOBN_MIX_RXFE->Clear();
	cmbLOBN_MIX_RXFE->Append(16, cs_Numbers);
	cmbLOBN_MIX_RXFE->SetSelection(3);

	// G_FINE_LNA3_RXFE[1:0]
	cmbG_FINE_LNA3_RXFE->Clear();
	wxString cs_G_FINE_LNA[4] = {"+0 dB", "+1 dB", "+2 dB", "+3 dB"};
	cmbG_FINE_LNA3_RXFE->Append(4, cs_G_FINE_LNA);
	cmbG_FINE_LNA3_RXFE->SetSelection(0);

	Thaw();
}
