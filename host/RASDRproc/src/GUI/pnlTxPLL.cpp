// -----------------------------------------------------------------------------
// FILE:        "pnlTxPLL.cpp"
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
#include "pnlTxPLL.h"
#include "ctr_6002dr2_LogicDLL.h"
//(*InternalHeaders(pnlTxPLL)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/spinbutt.h>
#include <wx/combobox.h>
//*)

#include "CommonFile.h"
#include "dlgFreqVsCap.h"
#include "dlgVcoCapLog.h"

//(*IdInit(pnlTxPLL)
const long pnlTxPLL::ID_RADIOBOX1 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX1 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX2 = wxNewId();
const long pnlTxPLL::ID_BUTTON1 = wxNewId();
const long pnlTxPLL::ID_BUTTON2 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT1 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT2 = wxNewId();
const long pnlTxPLL::ID_BUTTON3 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX3 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX1 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT3 = wxNewId();
const long pnlTxPLL::ID_PANEL2 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT4 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX2 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX4 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX5 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX6 = wxNewId();
const long pnlTxPLL::ID_BUTTON4 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT5 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT6 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT7 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT8 = wxNewId();
const long pnlTxPLL::ID_PANEL3 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX7 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX8 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX9 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX10 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX11 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX12 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX13 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX14 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX15 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX16 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX17 = wxNewId();
const long pnlTxPLL::ID_PANEL6 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT33 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT35 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT34 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX5 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX6 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX7 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX8 = wxNewId();
const long pnlTxPLL::ID_CHECKBOX18 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX9 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT36 = wxNewId();
const long pnlTxPLL::ID_PANEL15 = wxNewId();
const long pnlTxPLL::ID_RADIOBOX2 = wxNewId();
const long pnlTxPLL::ID_TEXTCTRL1 = wxNewId();
const long pnlTxPLL::ID_SPINBUTTON1 = wxNewId();
const long pnlTxPLL::ID_BUTTON5 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT11 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT12 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT13 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT14 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT15 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT16 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT17 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT19 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT18 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT20 = wxNewId();
const long pnlTxPLL::ID_RADIOBOX3 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT9 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX3 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT10 = wxNewId();
const long pnlTxPLL::ID_COMBOBOX4 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT21 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT22 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT23 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT24 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT25 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT26 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT27 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT28 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT29 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT30 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT31 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT32 = wxNewId();
const long pnlTxPLL::ID_RADIOBOX4 = wxNewId();
const long pnlTxPLL::ID_PANEL4 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT37 = wxNewId();
const long pnlTxPLL::ID_BUTTON6 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT38 = wxNewId();
const long pnlTxPLL::ID_BUTTON7 = wxNewId();
const long pnlTxPLL::ID_RADIOBOX5 = wxNewId();
const long pnlTxPLL::ID_RADIOBOX6 = wxNewId();
const long pnlTxPLL::ID_PANEL7 = wxNewId();
const long pnlTxPLL::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTxPLL,wxPanel)
	//(*EventTable(pnlTxPLL)
	//*)
END_EVENT_TABLE()

pnlTxPLL::pnlTxPLL(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
	BuildContent(parent,id,pos,size);
}

void pnlTxPLL::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTxPLL)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer12;
	wxStaticBoxSizer* StaticBoxSizer15;
	wxStaticBoxSizer* StaticBoxSizer14;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer9;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer13;
	wxStaticBoxSizer* StaticBoxSizer10;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer8;
	wxStaticBoxSizer* StaticBoxSizer11;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(839,534), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer1 = new wxFlexGridSizer(0, 6, 0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_RADIOBOX1, _("Decoding"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	FlexGridSizer1->Add(rgrDecode, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Test Signals"));
	chkOEN_TSTD_SX = new wxCheckBox(this, ID_CHECKBOX1, _("Buffer Enalbed"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkOEN_TSTD_SX->SetValue(false);
	StaticBoxSizer1->Add(chkOEN_TSTD_SX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkPASSEN_TSTOD_SD = new wxCheckBox(this, ID_CHECKBOX2, _("Pass Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkPASSEN_TSTOD_SD->SetValue(false);
	StaticBoxSizer1->Add(chkPASSEN_TSTOD_SD, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VCO Capacitance"));
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	btnChoose = new wxButton(Panel2, ID_BUTTON1, _("Select"), wxPoint(216,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnClbr = new wxButton(Panel2, ID_BUTTON2, _("Calibration"), wxPoint(216,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Status:"), wxPoint(0,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	lblAutoTuneSatatus = new wxStaticText(Panel2, ID_STATICTEXT2, _("NA"), wxPoint(48,8), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	btnTune = new wxButton(Panel2, ID_BUTTON3, _("Tune"), wxPoint(0,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	chkCapLog = new wxCheckBox(Panel2, ID_CHECKBOX3, _("Log"), wxPoint(88,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkCapLog->SetValue(false);
	cmbVCOCAP = new wxComboBox(Panel2, ID_COMBOBOX1, wxEmptyString, wxPoint(152,32), wxSize(64,24), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT3, _("Value:"), wxPoint(160,16), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticBoxSizer2->Add(Panel2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("VCO Output"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Voltage, V:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticBoxSizer3->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVOVCOREG = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(81,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	StaticBoxSizer3->Add(cmbVOVCOREG, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("Various VCO Controls"));
	chbBYPVCOREG = new wxCheckBox(this, ID_CHECKBOX4, _("VCO Reg. Bypass"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chbBYPVCOREG->SetValue(false);
	StaticBoxSizer4->Add(chbBYPVCOREG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	chbPDVCOREG = new wxCheckBox(this, ID_CHECKBOX5, _("VCO Reg. PD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chbPDVCOREG->SetValue(false);
	StaticBoxSizer4->Add(chbPDVCOREG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	chbFSTVCOBG = new wxCheckBox(this, ID_CHECKBOX6, _("BG Res. Shorted"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chbFSTVCOBG->SetValue(false);
	StaticBoxSizer4->Add(chbFSTVCOBG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer1->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VCO Comparators"));
	Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	btnReadVtune = new wxButton(Panel3, ID_BUTTON4, _("Read"), wxPoint(8,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticText4 = new wxStaticText(Panel3, ID_STATICTEXT5, _("High:"), wxPoint(0,8), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	lblVTUNE_H = new wxStaticText(Panel3, ID_STATICTEXT6, _("0"), wxPoint(32,8), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	StaticText5 = new wxStaticText(Panel3, ID_STATICTEXT7, _("Low:"), wxPoint(56,8), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	lblVTUNE_L = new wxStaticText(Panel3, ID_STATICTEXT8, _("0"), wxPoint(88,8), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticBoxSizer5->Add(Panel3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(3, 1, 0, 0);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power Control"));
	Panel6 = new wxPanel(this, ID_PANEL6, wxDefaultPosition, wxSize(267,109), wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	chbPwrPllMods = new wxCheckBox(Panel6, ID_CHECKBOX7, _("PLL Modules Enable"), wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chbPwrPllMods->SetValue(true);
	chkENLOBUF = new wxCheckBox(Panel6, ID_CHECKBOX8, _("LO Buffer Enable"), wxPoint(0,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkENLOBUF->SetValue(true);
	chkENLAMP = new wxCheckBox(Panel6, ID_CHECKBOX9, _("Input limiter Amp. En."), wxPoint(0,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkENLAMP->SetValue(true);
	chkENFEEDDIV = new wxCheckBox(Panel6, ID_CHECKBOX10, _("Feedback Divider En."), wxPoint(0,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkENFEEDDIV->SetValue(true);
	chkPFDPD = new wxCheckBox(Panel6, ID_CHECKBOX11, _("PFD/CP En."), wxPoint(160,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chkPFDPD->SetValue(true);
	chkPD_VCOCOMP_SX = new wxCheckBox(Panel6, ID_CHECKBOX12, _("VCO COMP En."), wxPoint(160,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	chkPD_VCOCOMP_SX->SetValue(false);
	chbAUTOBYP = new wxCheckBox(Panel6, ID_CHECKBOX13, _("DSMN Auto Byp."), wxPoint(160,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chbAUTOBYP->SetValue(false);
	chbEN_PFD_UP = new wxCheckBox(Panel6, ID_CHECKBOX14, _("PFD Up Pulses"), wxPoint(160,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chbEN_PFD_UP->SetValue(false);
	chkPFDCLKP = new wxCheckBox(Panel6, ID_CHECKBOX15, _("PFD Clk Inverted (Unchecked-in Phase)"), wxPoint(0,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	chkPFDCLKP->SetValue(false);
	chkTRI = new wxCheckBox(Panel6, ID_CHECKBOX16, _("CP Out Mode: Tri-state (Unchecked-Normal)"), wxPoint(0,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	chkTRI->SetValue(false);
	chkPOL = new wxCheckBox(Panel6, ID_CHECKBOX17, _("CP Out Inverted (Unchecked-Normal)"), wxPoint(0,96), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
	chkPOL->SetValue(false);
	StaticBoxSizer6->Add(Panel6, 1, wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer11 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("CP Current and Offset"));
	FlexGridSizer4 = new wxFlexGridSizer(2, 3, 0, 0);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT33, _("Current, uA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	FlexGridSizer4->Add(StaticText11, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT35, _("Up Offset, uA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
	FlexGridSizer4->Add(StaticText18, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT34, _("Dn Offset, uA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	FlexGridSizer4->Add(StaticText16, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbICHP = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(78,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer4->Add(cmbICHP, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbOFFUP = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(83,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	FlexGridSizer4->Add(cmbOFFUP, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbOFFDOWN = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(75,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	FlexGridSizer4->Add(cmbOFFDOWN, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer11->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer11, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer12 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Output Buffer"));
	cmbSELOUT = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(81,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	cmbSELOUT->Append(_("Disabled"));
	cmbSELOUT->Append(_("First"));
	cmbSELOUT->Append(_("Second"));
	cmbSELOUT->Append(_("Third"));
	StaticBoxSizer12->Add(cmbSELOUT, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer12, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer13 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Dithering Control"));
	Panel15 = new wxPanel(this, ID_PANEL15, wxDefaultPosition, wxSize(142,46), wxTAB_TRAVERSAL, _T("ID_PANEL15"));
	Panel15->SetMinSize(wxSize(142,46));
	chkDITHEN = new wxCheckBox(Panel15, ID_CHECKBOX18, _("Use"), wxPoint(8,12), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX18"));
	chkDITHEN->SetValue(false);
	cmbDITHN = new wxComboBox(Panel15, ID_COMBOBOX9, wxEmptyString, wxPoint(64,16), wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
	StaticText20 = new wxStaticText(Panel15, ID_STATICTEXT36, _("Bits Dither:"), wxPoint(72,0), wxDefaultSize, 0, _T("ID_STATICTEXT36"));
	StaticBoxSizer13->Add(Panel15, 1, wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer13, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(296,112), wxDefaultSize, wxNO_BORDER, _T("ID_NOTEBOOK1"));
	Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	FlexGridSizer9 = new wxFlexGridSizer(2, 3, 0, 0);
	FlexGridSizer10 = new wxFlexGridSizer(2, 1, 0, 0);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Fractional"),
		_("Integer")
	};
	rgrMODE = new wxRadioBox(Panel4, ID_RADIOBOX2, _("PLL Mode"), wxPoint(8,8), wxSize(153,40), 2, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrMODE->SetSelection(0);
	FlexGridSizer10->Add(rgrMODE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxVERTICAL, Panel4, _("Output Frequency, GHz"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer5->AddGrowableCol(0);
	txtDesFreq = new wxTextCtrl(Panel4, ID_TEXTCTRL1, _("2.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer5->Add(txtDesFreq, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CSpinButton1 = new wxSpinButton(Panel4, ID_SPINBUTTON1, wxDefaultPosition, wxSize(17,21), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON1"));
	CSpinButton1->SetRange(0, 100);
	FlexGridSizer5->Add(CSpinButton1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCalc = new wxButton(Panel4, ID_BUTTON5, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	StaticBoxSizer7->Add(btnCalc, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer10->Add(StaticBoxSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(FlexGridSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, Panel4, _("Calculated Values for Fractional Mode"));
	FlexGridSizer2 = new wxFlexGridSizer(5, 2, 5, 0);
	StaticText8 = new wxStaticText(Panel4, ID_STATICTEXT11, _("N Integer:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer2->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblNint = new wxStaticText(Panel4, ID_STATICTEXT12, _("130"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer2->Add(lblNint, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(Panel4, ID_STATICTEXT13, _("N Fractional:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer2->Add(StaticText10, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblNfrac = new wxStaticText(Panel4, ID_STATICTEXT14, _("2097152"), wxDefaultPosition, wxSize(64,13), 0, _T("ID_STATICTEXT14"));
	FlexGridSizer2->Add(lblNfrac, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(Panel4, ID_STATICTEXT15, _("Divider:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer2->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblDiv = new wxStaticText(Panel4, ID_STATICTEXT16, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer2->Add(lblDiv, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(Panel4, ID_STATICTEXT17, _("Real Output Freq, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer2->Add(StaticText14, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblROutF = new wxStaticText(Panel4, ID_STATICTEXT19, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	FlexGridSizer2->Add(lblROutF, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(Panel4, ID_STATICTEXT18, _("VCO Freq, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer2->Add(StaticText15, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblVcoF = new wxStaticText(Panel4, ID_STATICTEXT20, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer2->Add(lblVcoF, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(StaticBoxSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[5] =
	{
		_("All Powered Down"),
		_("Low Frequency"),
		_("Mid Low Frequency"),
		_("Mid High Frequency"),
		_("High Frequency")
	};
	rgrSELVCO = new wxRadioBox(Panel4, ID_RADIOBOX3, _("Current VCO"), wxPoint(368,8), wxSize(128,120), 5, __wxRadioBoxChoices_3, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX3"));
	rgrSELVCO->SetSelection(2);
	FlexGridSizer9->Add(rgrSELVCO, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, Panel4, _("A and B Counter Values"));
	StaticText6 = new wxStaticText(Panel4, ID_STATICTEXT9, _("Counter A Value:"), wxDefaultPosition, wxSize(82,14), 0, _T("ID_STATICTEXT9"));
	StaticBoxSizer8->Add(StaticText6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbACODE = new wxComboBox(Panel4, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	StaticBoxSizer8->Add(cmbACODE, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText7 = new wxStaticText(Panel4, ID_STATICTEXT10, _("Counter B Value:"), wxDefaultPosition, wxSize(81,12), 0, _T("ID_STATICTEXT10"));
	StaticBoxSizer8->Add(StaticText7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbBCODE = new wxComboBox(Panel4, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	StaticBoxSizer8->Add(cmbBCODE, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer9->Add(StaticBoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer10 = new wxStaticBoxSizer(wxHORIZONTAL, Panel4, _("Calculated Values for Integer Mode"));
	FlexGridSizer3 = new wxFlexGridSizer(6, 2, 2, 0);
	StaticText9 = new wxStaticText(Panel4, ID_STATICTEXT21, _("Divider N:"), wxDefaultPosition, wxSize(112,13), 0, _T("ID_STATICTEXT21"));
	FlexGridSizer3->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblN = new wxStaticText(Panel4, ID_STATICTEXT22, _("130"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	FlexGridSizer3->Add(lblN, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(Panel4, ID_STATICTEXT23, _("Fvco, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	FlexGridSizer3->Add(StaticText13, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvcoInt = new wxStaticText(Panel4, ID_STATICTEXT24, _("2097152"), wxDefaultPosition, wxSize(64,13), 0, _T("ID_STATICTEXT24"));
	FlexGridSizer3->Add(lblFvcoInt, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(Panel4, ID_STATICTEXT25, _("Fvco/2, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	FlexGridSizer3->Add(StaticText17, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco2Int = new wxStaticText(Panel4, ID_STATICTEXT26, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	FlexGridSizer3->Add(lblFvco2Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText19 = new wxStaticText(Panel4, ID_STATICTEXT27, _("Fvco/4, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	FlexGridSizer3->Add(StaticText19, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco4Int = new wxStaticText(Panel4, ID_STATICTEXT28, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	FlexGridSizer3->Add(lblFvco4Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText21 = new wxStaticText(Panel4, ID_STATICTEXT29, _("Fvco/8, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	FlexGridSizer3->Add(StaticText21, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco8Int = new wxStaticText(Panel4, ID_STATICTEXT30, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	FlexGridSizer3->Add(lblFvco8Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText23 = new wxStaticText(Panel4, ID_STATICTEXT31, _("Fvco/16, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	FlexGridSizer3->Add(StaticText23, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco16Int = new wxStaticText(Panel4, ID_STATICTEXT32, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	FlexGridSizer3->Add(lblFvco16Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer10->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(StaticBoxSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[5] =
	{
		_("All Powered Down"),
		_("Fvco/2"),
		_("Fvco/4"),
		_("Fvco/8"),
		_("Fvco/16")
	};
	rgrFRANGE = new wxRadioBox(Panel4, ID_RADIOBOX4, _("MUX/DIV Selection"), wxPoint(368,128), wxSize(128,120), 5, __wxRadioBoxChoices_4, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX4"));
	rgrFRANGE->SetSelection(1);
	FlexGridSizer9->Add(rgrFRANGE, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4->SetSizer(FlexGridSizer9);
	FlexGridSizer9->Fit(Panel4);
	FlexGridSizer9->SetSizeHints(Panel4);
	Panel7 = new wxPanel(Notebook1, ID_PANEL7, wxPoint(295,67), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	FlexGridSizer11 = new wxFlexGridSizer(0, 4, 0, 0);
	StaticBoxSizer14 = new wxStaticBoxSizer(wxVERTICAL, Panel7, _("BIST State"));
	lblBSTATE = new wxStaticText(Panel7, ID_STATICTEXT37, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
	StaticBoxSizer14->Add(lblBSTATE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnReadBISTState = new wxButton(Panel7, ID_BUTTON6, _("Read BIST State"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	StaticBoxSizer14->Add(btnReadBISTState, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer11->Add(StaticBoxSizer14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer15 = new wxStaticBoxSizer(wxVERTICAL, Panel7, _("BIST Signature"));
	lblBSIG = new wxStaticText(Panel7, ID_STATICTEXT38, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT38"));
	StaticBoxSizer15->Add(lblBSIG, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(Panel7, ID_BUTTON7, _("Read Signature"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	StaticBoxSizer15->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer11->Add(StaticBoxSizer15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[3] =
	{
		_("Clock Disabled"),
		_("Ref Clk for BIST"),
		_("Feedback Div Out")
	};
	rgrBCLKSEL = new wxRadioBox(Panel7, ID_RADIOBOX5, _("DSMN/BIST Clock"), wxPoint(236,8), wxDefaultSize, 3, __wxRadioBoxChoices_5, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX5"));
	FlexGridSizer11->Add(rgrBCLKSEL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_6[2] =
	{
		_("NINT/NFRAC"),
		_("LFSR")
	};
	rgrBINSEL = new wxRadioBox(Panel7, ID_RADIOBOX6, _("DSMN/BIST Input"), wxPoint(356,8), wxSize(103,80), 2, __wxRadioBoxChoices_6, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX6"));
	FlexGridSizer11->Add(rgrBINSEL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(FlexGridSizer11);
	FlexGridSizer11->Fit(Panel7);
	FlexGridSizer11->SetSizeHints(Panel7);
	Notebook1->AddPage(Panel4, _("Frequency Control"), false);
	Notebook1->AddPage(Panel7, _("BIST Control"), false);
	FlexGridSizer7->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer6);
	SetSizer(FlexGridSizer6);
	Layout();

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::rgrDecodeClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkOEN_TSTD_SXClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkPASSEN_TSTOD_SDClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::btnChooseClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::btnClbrClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::btnTuneClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbVCOCAPChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbVOVCOREGChange);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chbBYPVCOREGClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chbPDVCOREGClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chbFSTVCOBGClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::btnReadVtuneClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chbPwrPllModsClick);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkENLOBUFClick);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkENLAMPClick);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkENFEEDDIVClick);
	Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkPFDPDClick);
	Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkPD_VCOCOMP_SXClick);
	Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chbAUTOBYPClick);
	Connect(ID_CHECKBOX14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chbEN_PFD_UPClick);
	Connect(ID_CHECKBOX15,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkPFDCLKPClick);
	Connect(ID_CHECKBOX16,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkTRIClick);
	Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkPOLClick);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbICHPChange);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbOFFUPChange);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbOFFDOWNChange);
	Connect(ID_COMBOBOX8,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbSELOUTChange);
	Connect(ID_CHECKBOX18,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::chkDITHENClick);
	Connect(ID_COMBOBOX9,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbDITHNChange);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::rgrMODEClick);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&pnlTxPLL::OnCSpinButton1ChangeUp);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&pnlTxPLL::OnCSpinButton1ChangeDown);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::btnCalcClick);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::rgrSELVCOClick);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbACODEChange);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::cmbBCODEChange);
	Connect(ID_RADIOBOX4,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::rgrFRANGEClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::btnReadBISTStateClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::Button1Click);
	Connect(ID_RADIOBOX5,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::rgrBCLKSELClick);
	Connect(ID_RADIOBOX6,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::rgrBINSELClick);
	//*)
}

pnlTxPLL::~pnlTxPLL()
{
	//(*Destroy(pnlTxPLL)
	//*)
}

void pnlTxPLL::Initialize()
{
	sendChanges = false;
	m_cMAddr = LMLL_TxPLLGetAddr();

	if (m_cMAddr == TxPllAddr)
	{
		cmbSELOUT->Enable(false);
		// dlgFreqVsCap->Initialize("TxVCOFile", m_TxPLLModule->m_FreqVsCap);
	}
	else
	{
		// dlgFreqVsCap->Initialize("RxVCOFile", m_TxPLLModule->m_FreqVsCap);
	};
	FillComboBoxes();
	SetGuiDefaults();
	sendChanges = true;
};

// ---------------------------------------------------------------------------
void pnlTxPLL::SetGuiDefaults()
{
    Freeze();
	int itmp;
	double dtmp;

	// ==== 0x04 ==========================
	// DITHEN
	chkDITHEN->SetValue(true);
	// DITHN[2:0]
	cmbDITHN->SetSelection(0);
	// EN
	chbPwrPllMods->SetValue(true);
	// AUTOBYP
	chbAUTOBYP->SetValue(false);
	// DECODE
	rgrDecode->SetSelection(0);
	// MODE
	rgrMODE->SetSelection(0);

	// ==== 0x05 ==========================
	// SELVCO[2:0]
	rgrSELVCO->SetSelection(2);
	// FRANGE[2:0]
	rgrFRANGE->SetSelection(1);
	// SELOUT[1:0]
	cmbSELOUT->SetSelection(1);
	// ==== 0x06 ==========================
	// EN_PFD_UP
	chbEN_PFD_UP->SetValue(true);
	// OEN_TSTD_SX
	chkOEN_TSTD_SX->SetValue(false);
	// PASSEN_TSTOD_SD
	chkPASSEN_TSTOD_SD->SetValue(false);
	// ICHP[4:0]
	cmbICHP->SetSelection(12);
	// ==== 0x07 ==========================
	// BYPVCOREG
	chbBYPVCOREG->SetValue(true);
	// PDVCOREG
	chbPDVCOREG->SetValue(true);
	// FSTVCOBG
	chbFSTVCOBG->SetValue(true);
	// OFFUP[4:0]
	cmbOFFUP->SetSelection(0);
	// ==== 0x08 ==========================
	// VOVCOREG
	cmbVOVCOREG->SetSelection(5);
	// OFFDOWN[4:0]
	cmbOFFDOWN->SetSelection(0);
	// ==== 0x09 ==========================
	// VCOCAP[5:0]
	cmbVCOCAP->SetSelection(20);
	// ==== 0x0A ==========================
	// BCODE[5:0]
	cmbBCODE->SetSelection(5);
	// ==== 0x0B ==========================
	// ACODE[3:0]
	cmbACODE->SetSelection(0);
	// PD_VCOCOMP_SX
	chkPD_VCOCOMP_SX->SetValue(true);
	// ENLOBUF
	chkENLOBUF->SetValue(true);
	// ENLAMP
	chkENLAMP->SetValue(true);
	// TRI
	chkTRI->SetValue(false);
	// ==== 0x0C ==========================
	// POL
	chkPOL->SetValue(false);
	// PFDPD
	chkPFDPD->SetValue(true);
	// ENFEEDDIV
	chkENFEEDDIV->SetValue(true);
	// PFDCLKP
	chkPFDCLKP->SetValue(true);
	// BCLKSEL
	rgrBCLKSEL->SetSelection(2);
	// BINSEL
	rgrBINSEL->SetSelection(0);

	// Set frequency
	if (m_cMAddr == RxPllAddr)
	{
		txtDesFreq->SetValue( wxString::Format("%f", 1.950));
	}
	else
	{
		txtDesFreq->SetValue( wxString::Format("%f", 2.140));
	};

	lblBSTATE->SetLabel("Not Running");
	lblBSIG->SetLabel("0x000000");

	SetGuiDecode();
    Thaw();
};

// ---------------------------------------------------------------------------
void pnlTxPLL::SetGuiDecode()
{
	if (rgrDecode->GetSelection() == 0)
	{
		// Decode
		chbPwrPllMods->Enable(true);

		chkENLOBUF->Enable(false);
		chkENLAMP->Enable(false);
		// rgrTRI->Enable(false);
		chkTRI->Enable(false);
		// rgrPOL->Enable(false);
		chkPOL->Enable(false);
		chkPFDPD->Enable(false);
		chkENFEEDDIV->Enable(false);
		// rgrPFDCLKP->Enable(false);
		chkPFDCLKP->Enable(false);
		chkPD_VCOCOMP_SX->Enable(false);
	}
	else
	{
		// Direct control
		chbPwrPllMods->Enable(false);

		chkENLOBUF->Enable(true);
		chkENLAMP->Enable(true);
		// rgrTRI->Enable(true);
		chkTRI->Enable(true);
		// rgrPOL->Enable(true);
		chkPOL->Enable(true);
		chkPFDPD->Enable(true);
		chkENFEEDDIV->Enable(true);
		// rgrPFDCLKP->Enable(true);
		chkPFDCLKP->Enable(true);
		chkPD_VCOCOMP_SX->Enable(true);
	};
};

// ---------------------------------------------------------------------------
void pnlTxPLL::btnCalcClick(wxCommandEvent& event)
{
	double dDesFreq;
	txtDesFreq->GetValue().ToDouble(&dDesFreq);
	if ((dDesFreq < 0.2) || (dDesFreq > 4.5))
	{
		//ShowMessage("Incorrect Frequency Value.\nShould be between 0.2 and 4.5GHz.");
		return;
	}
	else
	{
	    txtDesFreq->GetValue().ToDouble(&dDesFreq);
		LMAL_TxPLL_SetFrequency(dDesFreq);
	}
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chkDITHENClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetDITHEN(chkDITHEN->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbDITHNChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetDITHN(cmbDITHN->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chbPwrPllModsClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetPwrPllMods(chbPwrPllMods->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::rgrDecodeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetDecode(rgrDecode->GetSelection());
	SetGuiDecode();
}
// ---------------------------------------------------------------------------

void pnlTxPLL::rgrMODEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetMODE(rgrMODE->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::rgrSELVCOClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetSELVCO(rgrSELVCO->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::rgrFRANGEClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetFRANGE(rgrFRANGE->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbSELOUTChange(wxCommandEvent& event)
{
	//if(sendChanges) LMLL_TxPLLSetSELOUT(cmbSELOUT->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbICHPChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetICHP(cmbICHP->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbOFFUPChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetOFFUP(cmbOFFUP->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbOFFDOWNChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetOFFDOWN(cmbOFFDOWN->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbVCOCAPChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetVCOCAP(cmbVCOCAP->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbBCODEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetBCODE(cmbBCODE->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::cmbACODEChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetACODE(cmbACODE->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chkENLOBUFClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetENLOBUF(chkENLOBUF->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chkENLAMPClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetENLAMP(chkENLAMP->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chkTRIClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetTRI(chkTRI->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chkPOLClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetPOL(chkPOL->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chkPFDPDClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetPFDPD(chkPFDPD->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chkENFEEDDIVClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetENFEEDDIV(chkENFEEDDIV->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chkPFDCLKPClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetPFDCLKP(chkPFDCLKP->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chkPD_VCOCOMP_SXClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetPD_VCOCOMP_SX(chkPD_VCOCOMP_SX->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chkOEN_TSTD_SXClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetOEN_TSTD_SX(chkOEN_TSTD_SX->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chkPASSEN_TSTOD_SDClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetPASSEN_TSTOD_SD(chkPASSEN_TSTOD_SD->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chbAUTOBYPClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetAUTOBYP(chbAUTOBYP->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chbEN_PFD_UPClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetEN_PFD_UP(chbEN_PFD_UP->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::chbBYPVCOREGClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetBYPVCOREG(chbBYPVCOREG->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chbPDVCOREGClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetPDVCOREG(chbPDVCOREG->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::chbFSTVCOBGClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetFSTVCOBG(chbFSTVCOBG->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::cmbVOVCOREGChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetVOVCOREG(cmbVOVCOREG->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::rgrBCLKSELClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetBCLKSEL(rgrBCLKSEL->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxPLL::rgrBINSELClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxPLLSetBINSEL(rgrBINSEL->GetSelection());
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// updates GUI data values
// ---------------------------------------------------------------------------
bool pnlTxPLL::UpdateGUI()
{
	int itmp;
	bool bRez = true;
	int iNint;
	int iFrac;
	double dFreq;

	//---------------------
	double ddiv, dROutf, Vcof;

	LMLL_TxPLLGetValuesForFractionalMode(iNint, iFrac, ddiv, dROutf, Vcof);
	lblNint->SetLabel( wxString::Format("%i", iNint));
	lblNfrac->SetLabel(wxString::Format("%i", iFrac));
	lblDiv->SetLabel(wxString::Format("%f", ddiv));
	lblROutF->SetLabel(wxString::Format("%f", dROutf));
	lblVcoF->SetLabel(wxString::Format("%f", Vcof));
	//---------------------
	int iN;
	double Fvco;
	double Fvco2;
	double Fvco4;
	double Fvco8;
	double Fvco16;
	LMLL_TxPLLGetValuesForIntegerMode(iN, Fvco, Fvco2, Fvco4, Fvco8, Fvco16);

	lblN->SetLabel( wxString::Format("%i", iN));
	lblFvcoInt->SetLabel( wxString::Format("%f", Fvco));
	lblFvco2Int->SetLabel( wxString::Format("%f", Fvco2));
	lblFvco4Int->SetLabel( wxString::Format("%f", Fvco4));
	lblFvco8Int->SetLabel( wxString::Format("%f", Fvco8));
	lblFvco16Int->SetLabel( wxString::Format("%f", Fvco16));
	//---------------------

	// DITHEN
	chkDITHEN->SetValue(LMLL_TxPLLGetDITHEN());

	// DITHN[2:0]
	cmbDITHN->SetSelection(LMLL_TxPLLGetDITHN());

	// EN
	chbPwrPllMods->SetValue(LMLL_TxPLLGetPwrPllMods());

	// AUTOBYP
	chbAUTOBYP->SetValue(LMLL_TxPLLGetAUTOBYP());

	// DECODE
	rgrDecode->SetSelection(LMLL_TxPLLGetDecode());

	// MODE
	rgrMODE->SetSelection(LMLL_TxPLLGetMODE());

	// SELVCO[2:0]
	rgrSELVCO->SetSelection(LMLL_TxPLLGetSELVCO());

	// FRANGE[2:0]
	rgrFRANGE->SetSelection(LMLL_TxPLLGetFRANGE());

	txtDesFreq->SetValue( wxString::Format("%f", LMLL_TxPLLGetFrequency()));

	// SELOUT[1:0]
	// not used in TxPLL
	//cmbSELOUT->SetSelection(LMLL_TxPLLGetSELOUT();

	// EN_PFD_UP
	chbEN_PFD_UP->SetValue(LMLL_TxPLLGetEN_PFD_UP());

	// OEN_TSTD_SX
	chkOEN_TSTD_SX->SetValue(LMLL_TxPLLGetOEN_TSTD_SX());

	// PASSEN_TSTOD_SD
	chkPASSEN_TSTOD_SD->SetValue(LMLL_TxPLLGetPASSEN_TSTOD_SD());

	// ICHP[4:0]
	cmbICHP->SetSelection(LMLL_TxPLLGetICHP());

	// BYPVCOREG
	chbBYPVCOREG->SetValue(LMLL_TxPLLGetBYPVCOREG());

	// PDVCOREG
	chbPDVCOREG->SetValue(LMLL_TxPLLGetPDVCOREG());

	// FSTVCOBG
	chbFSTVCOBG->SetValue(LMLL_TxPLLGetFSTVCOBG());

	// OFFUP[4:0]
	cmbOFFUP->SetSelection(LMLL_TxPLLGetOFFUP());

	// VOVCOREG[3:0]
	cmbVOVCOREG->SetSelection(LMLL_TxPLLGetVOVCOREG());

	// OFFDOWN[4:0]
	cmbOFFDOWN->SetSelection(LMLL_TxPLLGetOFFDOWN());

	// VCOCAP[5:0]
	cmbVCOCAP->SetSelection(LMLL_TxPLLGetVCOCAP());

	// BCODE[5:0]
	cmbBCODE->SetSelection(LMLL_TxPLLGetBCODE());

	// ACODE[3:0]
	cmbACODE->SetSelection(LMLL_TxPLLGetACODE());

	// PD_VCOCOMP_SX
	chkPD_VCOCOMP_SX->SetValue(LMLL_TxPLLGetPD_VCOCOMP_SX());

	// ENLOBUF
	chkENLOBUF->SetValue(LMLL_TxPLLGetENLOBUF());

	// ENLAMP
	chkENLAMP->SetValue(LMLL_TxPLLGetENLAMP());

	// TRI
	chkTRI->SetValue(LMLL_TxPLLGetTRI());

	// POL
	chkPOL->SetValue(LMLL_TxPLLGetPOL());

	// PFDPD
	chkPFDPD->SetValue(LMLL_TxPLLGetPFDPD());

	// ENFEEDDIV
	chkENFEEDDIV->SetValue(LMLL_TxPLLGetENFEEDDIV());

	// PFDCLKP
	chkPFDCLKP->SetValue(LMLL_TxPLLGetPFDCLKP());

	// BCLKSEL
	rgrBCLKSEL->SetSelection(LMLL_TxPLLGetBCLKSEL());

	// BINSEL
	rgrBINSEL->SetSelection(LMLL_TxPLLGetBINSEL());

	// BSTART
	// itmp = BSTART_r0C_b00();

	// BSTATE
	// BIST_ShowState(BSTATE_r0D_b77());

	// BSIG
	BIST_ShowSignature();
	SetGuiDecode();

	return bRez;
};

// ---------------------------------------------------------------------------
void pnlTxPLL::btnClbrClick(wxCommandEvent& event)
{
    dlgFreqVsCap *dlg;
    dlg = new dlgFreqVsCap(this);
	dlg->ShowModal();
	delete dlg;
}
// ---------------------------------------------------------------------------

void pnlTxPLL::btnChooseClick(wxCommandEvent& event)
{
	LMLL_TxPLLChooseVcoCap();
}
// ---------------------------------------------------------------------------

void pnlTxPLL::SetRefClk(double RefClk)
{
	if(sendChanges) LMLL_TxPLLSetRefClk(RefClk);
};

// ---------------------------------------------------------------------------
double pnlTxPLL::GetRefClk()
{
	return LMLL_TxPLLGetRefClk();
};

// ---------------------------------------------------------------------------
void pnlTxPLL::btnReadVtuneClick(wxCommandEvent& event)
{
	int State = LMLL_TxPLLGetVTuneState();
	switch (State)
	{
	case 0x00:
		lblVTUNE_H->SetLabel("0");
		lblVTUNE_L->SetLabel("0");
		break;

	case 0x01:
		lblVTUNE_H->SetLabel("0");
		lblVTUNE_L->SetLabel("1");
		break;

	case 0x02:
		lblVTUNE_H->SetLabel("1");
		lblVTUNE_L->SetLabel("0");
		break;

	default:
		lblVTUNE_H->SetLabel("1");
		lblVTUNE_L->SetLabel("1");
	};
}

// ---------------------------------------------------------------------------
// VTUNE_H, VTUNE_L, Returns
// 0        0        0x00
// 0        1        0x01
// 1        0        0x02
// 1        1        0x03 (ERROR)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
void pnlTxPLL::btnTuneClick(wxCommandEvent& event)
{
	LMLL_TxPLLTune();

	dlgVcoCapLog *VcoCapLog = NULL;
	VcoCapLog = new dlgVcoCapLog(this, wxNewId());

	if (chkCapLog->GetValue() == true)
	{
		unsigned int bufLen = LMLL_TxPLLGetVcoCapLogLength();
		char *tempBuf = new char [bufLen];
		LMLL_TxPLLGetVcoCapLogMessages(tempBuf);
		VcoCapLog->AddLine(tempBuf);
		VcoCapLog->ShowModal();
		delete []tempBuf;
	}
	if (VcoCapLog)
		VcoCapLog->Destroy();
}

// ---------------------------------------------------------------------------
void pnlTxPLL::BIST_ShowState(bool State)
{
	if (State)
		lblBSTATE->SetLabel("In Progress");
	else
		lblBSTATE->SetLabel("Not Running");
};

// ---------------------------------------------------------------------------
void pnlTxPLL::btnReadBISTStateClick(wxCommandEvent& event)
{
	BIST_ShowState(LMLL_TxPLLBIST_GetState());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::BIST_ShowSignature()
{
	lblBSIG->SetLabel(Int2Hex(LMLL_TxPLLBIST_GetSignature(), 6).c_str());
};

// ---------------------------------------------------------------------------
void pnlTxPLL::Button1Click(wxCommandEvent& event)
{
	lblBSIG->SetLabel(Int2Hex(LMLL_TxPLLBIST_GetSignature(), 6).c_str());
}

// ---------------------------------------------------------------------------
void pnlTxPLL::btnBSTARTClick(wxCommandEvent& event)
{
	LMLL_TxPLLBIST_Start();
}

// ---------------------------------------------------------------------------
void pnlTxPLL::txtDesFreqChange(wxCommandEvent& event)
{
	/*if(txtDesFreq->Text.Length() > 0)
		LMLL_TxPLLCustSet_LoadFrequency(txtDesFreq->Text.ToDouble());*/
}

//---------------------------------------------------------------------------
// decrements txtDesFreq value
//---------------------------------------------------------------------------
void pnlTxPLL::OnCSpinButton1ChangeDown(wxSpinEvent& event)
{
    double temp;
	txtDesFreq->GetValue().ToDouble(&temp);
	temp -= 0.1;
    txtDesFreq->SetValue( wxString::Format( "%f", temp));
}

//---------------------------------------------------------------------------
// increments txtDesFreq value
//---------------------------------------------------------------------------
void pnlTxPLL::OnCSpinButton1ChangeUp(wxSpinEvent& event)
{
    double temp;
	txtDesFreq->GetValue().ToDouble(&temp);
	temp += 0.1;
	txtDesFreq->SetValue( wxString::Format( "%f", temp));
}

void pnlTxPLL::OnEraseBackground(wxEraseEvent& event)
{
}

void pnlTxPLL::FillComboBoxes()
{
    Freeze();
    wxString cs_Numbers[64];
    for(int i=0; i<64; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
	int itmp;
	double dtmp;

	cmbDITHN->Clear();
	for(int i=0; i<8; i++)
        cs_Numbers[i] = wxString::Format("%i", i+1);
    cmbDITHN->Append( 8, cs_Numbers);
	cmbDITHN->SetSelection(0);

	cmbICHP->Clear();
	itmp = 0;
	for(int i=0; i<25; i++)
    {
        cs_Numbers[i] = wxString::Format("%i", itmp);
        itmp += 100;
    }
	cmbICHP->Append( 25, cs_Numbers);
	cmbICHP->SetSelection(12);

	cmbOFFUP->Clear();
	itmp = 0;
	for (int i = 0; i < 25; i++)
	{
		cs_Numbers[i] = wxString::Format("%i", itmp);
		itmp += 10;
	};
	cmbOFFUP->Append( 25, cs_Numbers);
	cmbOFFUP->SetSelection(0);
	// ==== 0x08 ==========================
	// VOVCOREG
	cmbVOVCOREG->Clear();
	dtmp = 1.4;
	for (int i = 0; i < 13; i++)
	{
		cs_Numbers[i] = wxString::Format("%.2f", dtmp);
		dtmp += 0.1;
	};
	cmbVOVCOREG->Append( 13, cs_Numbers);
	cmbVOVCOREG->SetSelection(5);
	// OFFDOWN[4:0]
	cmbOFFDOWN->Clear();
	itmp = 0;
	for (int i = 0; i < 25; i++)
	{
		cs_Numbers[i] = wxString::Format("%i", itmp);
		itmp += 10;
	};
	cmbOFFDOWN->Append( 25, cs_Numbers);
	cmbOFFDOWN->SetSelection(0);
	// ==== 0x09 ==========================
	// VCOCAP[5:0]
	cmbVCOCAP->Clear();
	for (int i = 0; i < 64; i++)
		cs_Numbers[i] = wxString::Format("%i", i);
	cmbVCOCAP->Append( 64, cs_Numbers);
	cmbVCOCAP->SetSelection(20);
	// ==== 0x0A ==========================
	// BCODE[5:0]
	cmbBCODE->Clear();
	for (int i = 7; i < 36; i++)
	{
		cs_Numbers[i-7] = wxString::Format("%i", i);
	};
	cmbBCODE->Append( 29, cs_Numbers);
	cmbBCODE->SetSelection(5);
	// ==== 0x0B ==========================
	// ACODE[3:0]
	cmbACODE->Clear();
	cmbACODE->Append( 8, cs_Numbers);
	cmbACODE->SetSelection(0);
	// PD_VCOCOMP_SX
    Thaw();
}
