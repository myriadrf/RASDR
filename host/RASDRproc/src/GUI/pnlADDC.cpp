// -----------------------------------------------------------------------------
// FILE:        "pnlADDC.cpp"
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
#include "pnlADDC.h"
#include "ctr_6002dr2_LogicDLL.h"

//(*InternalHeaders(pnlADDC)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlADDC)
const long pnlADDC::ID_RADIOBOX1 = wxNewId();
const long pnlADDC::ID_CHECKBOX1 = wxNewId();
const long pnlADDC::ID_CHECKBOX3 = wxNewId();
const long pnlADDC::ID_CHECKBOX2 = wxNewId();
const long pnlADDC::ID_CHECKBOX4 = wxNewId();
const long pnlADDC::ID_CHECKBOX5 = wxNewId();
const long pnlADDC::ID_CHECKBOX6 = wxNewId();
const long pnlADDC::ID_RADIOBOX10 = wxNewId();
const long pnlADDC::ID_RADIOBOX11 = wxNewId();
const long pnlADDC::ID_RADIOBOX12 = wxNewId();
const long pnlADDC::ID_RADIOBOX13 = wxNewId();
const long pnlADDC::ID_RADIOBOX14 = wxNewId();
const long pnlADDC::ID_STATICTEXT1 = wxNewId();
const long pnlADDC::ID_STATICTEXT2 = wxNewId();
const long pnlADDC::ID_STATICTEXT3 = wxNewId();
const long pnlADDC::ID_STATICTEXT4 = wxNewId();
const long pnlADDC::ID_STATICTEXT5 = wxNewId();
const long pnlADDC::ID_COMBOBOX1 = wxNewId();
const long pnlADDC::ID_COMBOBOX2 = wxNewId();
const long pnlADDC::ID_COMBOBOX3 = wxNewId();
const long pnlADDC::ID_COMBOBOX4 = wxNewId();
const long pnlADDC::ID_COMBOBOX5 = wxNewId();
const long pnlADDC::ID_STATICTEXT15 = wxNewId();
const long pnlADDC::ID_COMBOBOX15 = wxNewId();
const long pnlADDC::ID_RADIOBOX2 = wxNewId();
const long pnlADDC::ID_STATICTEXT16 = wxNewId();
const long pnlADDC::ID_COMBOBOX16 = wxNewId();
const long pnlADDC::ID_CHECKBOX7 = wxNewId();
const long pnlADDC::ID_STATICTEXT7 = wxNewId();
const long pnlADDC::ID_STATICTEXT6 = wxNewId();
const long pnlADDC::ID_STATICTEXT8 = wxNewId();
const long pnlADDC::ID_STATICTEXT9 = wxNewId();
const long pnlADDC::ID_STATICTEXT10 = wxNewId();
const long pnlADDC::ID_STATICTEXT11 = wxNewId();
const long pnlADDC::ID_COMBOBOX6 = wxNewId();
const long pnlADDC::ID_COMBOBOX7 = wxNewId();
const long pnlADDC::ID_COMBOBOX8 = wxNewId();
const long pnlADDC::ID_COMBOBOX9 = wxNewId();
const long pnlADDC::ID_COMBOBOX10 = wxNewId();
const long pnlADDC::ID_COMBOBOX11 = wxNewId();
const long pnlADDC::ID_STATICTEXT12 = wxNewId();
const long pnlADDC::ID_STATICTEXT13 = wxNewId();
const long pnlADDC::ID_STATICTEXT14 = wxNewId();
const long pnlADDC::ID_COMBOBOX12 = wxNewId();
const long pnlADDC::ID_COMBOBOX13 = wxNewId();
const long pnlADDC::ID_COMBOBOX14 = wxNewId();
const long pnlADDC::ID_RADIOBOX9 = wxNewId();
const long pnlADDC::ID_RADIOBOX3 = wxNewId();
const long pnlADDC::ID_RADIOBOX4 = wxNewId();
const long pnlADDC::ID_RADIOBOX5 = wxNewId();
const long pnlADDC::ID_RADIOBOX6 = wxNewId();
const long pnlADDC::ID_RADIOBOX7 = wxNewId();
const long pnlADDC::ID_RADIOBOX8 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlADDC,wxPanel)
	//(*EventTable(pnlADDC)
	//*)
END_EVENT_TABLE()

pnlADDC::pnlADDC(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
	BuildContent(parent,id,pos,size);
}

// ---------------------------------------------------------------------------
void pnlADDC::Initialize()
{
	sendChanges = false;
	FillComboBoxes();
	SetGuiDefaults();
	sendChanges = true;
};

// ---------------------------------------------------------------------------
void pnlADDC::SetGuiDefaults()
{
    Freeze();
	// EN_ADC_DAC
	chbEN_ADC_DAC->SetValue(true);

	// Decode
	rgrDecode->SetSelection(0);

	// ============== ENABLE CONTROL REGISTERS ==========

	// Rx Fsync Polarity, frame start
	rgrRX_FSYNC_P->SetSelection(0);

	// Rx Interleave Mode
	rgrRX_INTER->SetSelection(0);

	// Dac Clk Edge Polarity
	rgrDAC_CLK_P->SetSelection(1);

	// Tx Fsync Polarity, frame start
	rgrTX_FSYNC_P->SetSelection(0);

	// Tx Interleave Mode
	rgrTX_INTER->SetSelection(0);

	// Enable DAC
	chkEN_DAC->SetValue(true);

	// Enable ADC1 (I Channel)
	chkEN_ADC_I->SetValue(true);

	// Enable ADC2 (Q Channel)
	chkEN_ADC_Q->SetValue(true);

	// Enable ADC reference
	chkEN_ADC_REF->SetValue(true);

	// Enable master reference
	chkEN_M_REF->SetValue(true);

	// ============== REFERENECE CONTROL REGISTERS 0 ==========
	// Bandgap Temperature Coefficient Control
	cmbBandgapTemp->SetSelection( 8);

	// Bandgap Gain Control
	cmbBandgapGain->SetSelection(8);

	// ============== REFERENECE CONTROL REGISTERS 1 ==========
	// Reference Amps bias adjust
	cmbRefAmpsBiasAdj->SetSelection(0);

	// Reference Amps bias UP
	cmbRefAmpsBiasUp->SetSelection(0);

	// Reference Amps bias DOWN
	cmbRefAmpsBiasDn->SetSelection(0);

	// ============== ADC CONTROL REGISTERS 1 ==========
	// Reference bias resistor adjust
	cmbRefResistorBiasAdj->SetSelection(0);

	// Reference bias UP
	cmbRefBiasUp->SetSelection(0);

	// Reference bias DN
	cmbRefBiasDn->SetSelection(0);

	// ============== ADC CONTROL REGISTERS 2 ==========
	// Reference Gain Adjust
	cmbRefGainAdj->SetSelection(0);

	// Common Mode Adjust
	cmbCoomonModeAdj->SetSelection(0);

	// Reference Buffer Boost
	cmbRefBufferBoost->SetSelection(0);

	// Input Buffer Disable
	chkInputBufferDisable->SetValue(true);

	// ============== ADC CONTROL REGISTERS 3 ==========
	// ADC Sampling Phase Select
	cmbADCSamplingPhase->SetSelection(0);

	// Clock Non-Overlap Adjust
	cmbClockNonOverlapAdjust->SetSelection(0);

	// ============== ADC CONTROL REGISTERS 4 ==========
	// ADC bias resistor adjust
	rgrADCBiasResistorAdjust->SetSelection(0);

	// Main bias DOWN
	cmbMainBiasDN->SetSelection(0);

	// ADC Amp1 stage1 bias UP
	rgrADCAmp1Stage1BasUp->SetSelection(0);

	// ADC Amp2-4 stage1 bias UP
	rgrADCAmp24Stage1BasUp->SetSelection(0);

	// ============== ADC CONTROL REGISTERS 5 ==========
	// ADC Amp1 stage2 bias UP
	rgrADCAmp1Stage2BasUp->SetSelection(0);

	// ADC Amp2-4 stage2 bias UP
	rgrADCAmp24Stage2BasUp->SetSelection(0);

	// Quantizer  bias UP
	rgrQuantizerBiasUp->SetSelection(0);

	// Input Buffer bias UP
	rgrInputBufferBiasUp->SetSelection(0);

	// ============== DAC CONTROL REGISTERS 1 ==========
	// DAC Internal Output Load Resistor Control Bits
	cmbDACInternalOutputLoadResistor->SetSelection( 2);

	// DAC Reference Current Resistor
	rgrDACReferenceCurrentResistor->SetSelection(1);

	// DAC Full Scale Output Current Control (single-ended)
	cmbDACFullScaleOutputCurrent->SetSelection(0);

	SetGuiDecode();
	Thaw();
};

// ---------------------------------------------------------------------------
void pnlADDC::SetGuiDecode()
{
	if (rgrDecode->GetSelection() == 0)
	{
		// Decode
		chbEN_ADC_DAC->Enable(true);

		chkEN_ADC_I->Enable(false);
		chkEN_ADC_Q->Enable(false);
		chkEN_ADC_REF->Enable(false);
		chkEN_DAC->Enable(false);
		chkEN_M_REF->Enable(false);
	}
	else
	{
		// Direct control
		chbEN_ADC_DAC->Enable(false);

		chkEN_ADC_I->Enable(true);
		chkEN_ADC_Q->Enable(true);
		chkEN_ADC_REF->Enable(true);
		chkEN_DAC->Enable(true);
		chkEN_M_REF->Enable(true);
	};
};

void pnlADDC::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlADDC)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer14;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer10 = new wxFlexGridSizer(3, 1, 0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_RADIOBOX1, _("Decoding"), wxPoint(0,8), wxSize(220,56), 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	FlexGridSizer10->Add(rgrDecode, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC/DAC Enable Control"));
	FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
	chbEN_ADC_DAC = new wxCheckBox(this, ID_CHECKBOX1, _("ADDC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chbEN_ADC_DAC->SetValue(false);
	FlexGridSizer1->Add(chbEN_ADC_DAC, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_ADC_REF = new wxCheckBox(this, ID_CHECKBOX3, _("ADC Ref Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkEN_ADC_REF->SetValue(false);
	FlexGridSizer1->Add(chkEN_ADC_REF, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_ADC_I = new wxCheckBox(this, ID_CHECKBOX2, _("ADC1 (I) Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkEN_ADC_I->SetValue(false);
	FlexGridSizer1->Add(chkEN_ADC_I, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_DAC = new wxCheckBox(this, ID_CHECKBOX4, _("DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkEN_DAC->SetValue(false);
	FlexGridSizer1->Add(chkEN_DAC, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_ADC_Q = new wxCheckBox(this, ID_CHECKBOX5, _("ADC2 (Q) Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkEN_ADC_Q->SetValue(false);
	FlexGridSizer1->Add(chkEN_ADC_Q, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_M_REF = new wxCheckBox(this, ID_CHECKBOX6, _("Master Ref Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkEN_M_REF->SetValue(false);
	FlexGridSizer1->Add(chkEN_M_REF, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer10->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC/DAC Miscellaneous Control"));
	FlexGridSizer8 = new wxFlexGridSizer(3, 2, 0, 0);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("0"),
		_("1")
	};
	rgrRX_FSYNC_P = new wxRadioBox(this, ID_RADIOBOX10, _("Rx Fsync Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX10"));
	FlexGridSizer8->Add(rgrRX_FSYNC_P, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("0"),
		_("1")
	};
	rgrTX_FSYNC_P = new wxRadioBox(this, ID_RADIOBOX11, _("Tx Fsync Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX11"));
	FlexGridSizer8->Add(rgrTX_FSYNC_P, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_("I,Q"),
		_("Q,I")
	};
	rgrRX_INTER = new wxRadioBox(this, ID_RADIOBOX12, _("Rx Interleave"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX12"));
	FlexGridSizer8->Add(rgrRX_INTER, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[2] =
	{
		_("I,Q"),
		_("Q,I")
	};
	rgrTX_INTER = new wxRadioBox(this, ID_RADIOBOX13, _("Tx Interleave"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_5, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX13"));
	FlexGridSizer8->Add(rgrTX_INTER, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_6[2] =
	{
		_("Pos"),
		_("Neg")
	};
	rgrDAC_CLK_P = new wxRadioBox(this, ID_RADIOBOX14, _("DAC Edge"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_6, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX14"));
	FlexGridSizer8->Add(rgrDAC_CLK_P, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer10->Add(StaticBoxSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer11 = new wxFlexGridSizer(3, 1, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC_DAC Reference Control"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 5, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Bandgap Temp Coeff:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Bandgap Gain:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Ref Amps Bias Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Ref Amps Bias UP:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer2->Add(StaticText4, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Ref Amps Bias DN:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer2->Add(StaticText5, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbBandgapTemp = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	FlexGridSizer2->Add(cmbBandgapTemp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbBandgapGain = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer2->Add(cmbBandgapGain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefAmpsBiasAdj = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(90,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	FlexGridSizer2->Add(cmbRefAmpsBiasAdj, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefAmpsBiasUp = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(90,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	FlexGridSizer2->Add(cmbRefAmpsBiasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefAmpsBiasDn = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(95,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer2->Add(cmbRefAmpsBiasDn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC Control"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("DAC Internal Output Load Resistor:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer6->Add(StaticText15, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDACInternalOutputLoadResistor = new wxComboBox(this, ID_COMBOBOX15, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX15"));
	FlexGridSizer6->Add(cmbDACInternalOutputLoadResistor, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_7[2] =
	{
		_("Internal"),
		_("External")
	};
	rgrDACReferenceCurrentResistor = new wxRadioBox(this, ID_RADIOBOX2, _("DAC Reference Current Resistor"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_7, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	FlexGridSizer5->Add(rgrDACReferenceCurrentResistor, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("DAC Full Scale Output Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer7->Add(StaticText16, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDACFullScaleOutputCurrent = new wxComboBox(this, ID_COMBOBOX16, wxEmptyString, wxDefaultPosition, wxSize(163,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX16"));
	FlexGridSizer7->Add(cmbDACFullScaleOutputCurrent, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer4, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC Control"));
	FlexGridSizer12 = new wxFlexGridSizer(5, 1, 0, 0);
	chkInputBufferDisable = new wxCheckBox(this, ID_CHECKBOX7, _("Input Buffer Disabled"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkInputBufferDisable->SetValue(false);
	FlexGridSizer12->Add(chkInputBufferDisable, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(2, 6, 0, 0);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Ref Bias Res Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer3->Add(StaticText7, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Ref Bias UP:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer3->Add(StaticText6, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Ref Bias DN:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer3->Add(StaticText8, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Ref Buff Boost:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer3->Add(StaticText9, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Common Mode Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer3->Add(StaticText10, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Ref Gain Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer3->Add(StaticText11, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefResistorBiasAdj = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	FlexGridSizer3->Add(cmbRefResistorBiasAdj, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefBiasUp = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	FlexGridSizer3->Add(cmbRefBiasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefBiasDn = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	FlexGridSizer3->Add(cmbRefBiasDn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefBufferBoost = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
	FlexGridSizer3->Add(cmbRefBufferBoost, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbCoomonModeAdj = new wxComboBox(this, ID_COMBOBOX10, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX10"));
	FlexGridSizer3->Add(cmbCoomonModeAdj, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefGainAdj = new wxComboBox(this, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX11"));
	FlexGridSizer3->Add(cmbRefGainAdj, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer3, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer13->AddGrowableCol(0);
	FlexGridSizer4 = new wxFlexGridSizer(2, 3, 0, 0);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Main Bias DN:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer4->Add(StaticText12, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Clock Non-Overlap Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer4->Add(StaticText13, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("ADC Sampling Phase:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer4->Add(StaticText14, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbMainBiasDN = new wxComboBox(this, ID_COMBOBOX12, wxEmptyString, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX12"));
	FlexGridSizer4->Add(cmbMainBiasDN, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbClockNonOverlapAdjust = new wxComboBox(this, ID_COMBOBOX13, wxEmptyString, wxDefaultPosition, wxSize(120,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX13"));
	FlexGridSizer4->Add(cmbClockNonOverlapAdjust, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbADCSamplingPhase = new wxComboBox(this, ID_COMBOBOX14, wxEmptyString, wxDefaultPosition, wxSize(116,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX14"));
	FlexGridSizer4->Add(cmbADCSamplingPhase, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_8[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCBiasResistorAdjust = new wxRadioBox(this, ID_RADIOBOX9, _("ADC Bias Resistor Adjust, uA"), wxPoint(352,80), wxDefaultSize, 4, __wxRadioBoxChoices_8, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX9"));
	FlexGridSizer13->Add(rgrADCBiasResistorAdjust, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer13, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer14 = new wxFlexGridSizer(2, 3, 0, 0);
	FlexGridSizer14->AddGrowableCol(0);
	FlexGridSizer14->AddGrowableCol(1);
	FlexGridSizer14->AddGrowableCol(2);
	wxString __wxRadioBoxChoices_9[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp1Stage1BasUp = new wxRadioBox(this, ID_RADIOBOX3, _("ADC Amp1 Stage1 Bias Up, uA"), wxPoint(0,128), wxDefaultSize, 4, __wxRadioBoxChoices_9, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX3"));
	FlexGridSizer14->Add(rgrADCAmp1Stage1BasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_10[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp24Stage1BasUp = new wxRadioBox(this, ID_RADIOBOX4, _("ADC Amp2-4 Stage1 Bias Up, uA"), wxPoint(168,128), wxDefaultSize, 4, __wxRadioBoxChoices_10, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX4"));
	FlexGridSizer14->Add(rgrADCAmp24Stage1BasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_11[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrQuantizerBiasUp = new wxRadioBox(this, ID_RADIOBOX5, _("Quantizer Bias Up, uA"), wxPoint(352,128), wxSize(160,44), 4, __wxRadioBoxChoices_11, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX5"));
	FlexGridSizer14->Add(rgrQuantizerBiasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_12[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp1Stage2BasUp = new wxRadioBox(this, ID_RADIOBOX6, _("ADC Amp1 Stage2 Bias Up, uA"), wxPoint(0,184), wxDefaultSize, 4, __wxRadioBoxChoices_12, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX6"));
	FlexGridSizer14->Add(rgrADCAmp1Stage2BasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_13[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp24Stage2BasUp = new wxRadioBox(this, ID_RADIOBOX7, _("ADC Amp2-4 Stage2 Bias Up, uA"), wxPoint(168,184), wxDefaultSize, 4, __wxRadioBoxChoices_13, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX7"));
	FlexGridSizer14->Add(rgrADCAmp24Stage2BasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_14[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrInputBufferBiasUp = new wxRadioBox(this, ID_RADIOBOX8, _("Input Buffer Bias Up, uA"), wxPoint(352,184), wxSize(160,44), 4, __wxRadioBoxChoices_14, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX8"));
	FlexGridSizer14->Add(rgrInputBufferBiasUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer12, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer3, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(FlexGridSizer11, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer9);
	FlexGridSizer9->Fit(this);
	FlexGridSizer9->SetSizeHints(this);

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrDecodeClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::chkEN_ADC_REFClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::chkEN_ADC_REFClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::chkEN_ADC_IClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::chkEN_DACClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::chkEN_ADC_QClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::chkEN_M_REFClick);
	Connect(ID_RADIOBOX10,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrRX_FSYNC_PClick);
	Connect(ID_RADIOBOX11,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrTX_FSYNC_PClick);
	Connect(ID_RADIOBOX12,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrRX_INTERClick);
	Connect(ID_RADIOBOX13,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrTX_INTERClick);
	Connect(ID_RADIOBOX14,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrDAC_CLK_PClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbBandgapTempChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbBandgapGainChange);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefAmpsBiasAdjChange);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefAmpsBiasUpChange);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefAmpsBiasDnChange);
	Connect(ID_COMBOBOX15,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbDACInternalOutputLoadResistorChange);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrDACReferenceCurrentResistorClick);
	Connect(ID_COMBOBOX16,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbDACFullScaleOutputCurrentChange);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::chkInputBufferDisableClick);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefResistorBiasAdjChange);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefBiasUpChange);
	Connect(ID_COMBOBOX8,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefBiasDnChange);
	Connect(ID_COMBOBOX9,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefBufferBoostChange);
	Connect(ID_COMBOBOX10,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbCoomonModeAdjChange);
	Connect(ID_COMBOBOX11,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbRefGainAdjChange);
	Connect(ID_COMBOBOX12,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbMainBiasDNChange);
	Connect(ID_COMBOBOX13,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbClockNonOverlapAdjustChange);
	Connect(ID_COMBOBOX14,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::cmbADCSamplingPhaseChange);
	Connect(ID_RADIOBOX9,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrADCBiasResistorAdjustClick);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrADCAmp1Stage1BasUpClick);
	Connect(ID_RADIOBOX4,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrADCAmp24Stage1BasUpClick);
	Connect(ID_RADIOBOX5,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrQuantizerBiasUpClick);
	Connect(ID_RADIOBOX6,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrADCAmp1Stage2BasUpClick);
	Connect(ID_RADIOBOX7,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrADCAmp24Stage2BasUpClick);
	Connect(ID_RADIOBOX8,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::rgrInputBufferBiasUpClick);
	//*)
}

pnlADDC::~pnlADDC()
{
	//(*Destroy(pnlADDC)
	//*)
}

// ---------------------------------------------------------------------------
void pnlADDC::rgrRX_FSYNC_PClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRX_FSYNC_P(rgrRX_FSYNC_P->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrRX_INTERClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRX_INTER(rgrRX_INTER->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrDAC_CLK_PClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetDAC_CLK_P(rgrDAC_CLK_P->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrTX_FSYNC_PClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetTX_FSYNC_P(rgrTX_FSYNC_P->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrTX_INTERClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetTX_INTER(rgrTX_INTER->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::chkEN_DACClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetEN_DAC(chkEN_DAC->GetValue());
}
// ---------------------------------------------------------------------------

void pnlADDC::chkEN_ADC_IClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetEN_ADC_I(chkEN_ADC_I->GetValue());
}
// ---------------------------------------------------------------------------

void pnlADDC::chkEN_ADC_QClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetEN_ADC_Q(chkEN_ADC_Q->GetValue());
}
// ---------------------------------------------------------------------------

void pnlADDC::chkEN_ADC_REFClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetEN_ADC_REF(chkEN_ADC_REF->GetValue());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrDecodeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetDecode(rgrDecode->GetSelection());
	SetGuiDecode();
}
// ---------------------------------------------------------------------------

void pnlADDC::chkEN_M_REFClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetEN_M_REF(chkEN_M_REF->GetValue());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbBandgapTempChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetBandgapTemp(cmbBandgapTemp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbBandgapGainChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetBandgapGain(cmbBandgapGain->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefAmpsBiasAdjChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefAmpsBiasAdj(cmbRefAmpsBiasAdj->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefAmpsBiasUpChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefAmpsBiasUp(cmbRefAmpsBiasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefAmpsBiasDnChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefAmpsBiasDn(cmbRefAmpsBiasDn->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefResistorBiasAdjChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefResistorBiasAdj(cmbRefResistorBiasAdj->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefBiasUpChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefBiasUp(cmbRefBiasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefBiasDnChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefBiasDn(cmbRefBiasDn->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefGainAdjChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefGainAdj(cmbRefGainAdj->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbCoomonModeAdjChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetCoomonModeAdj(cmbCoomonModeAdj->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbRefBufferBoostChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetRefBufferBoost(cmbRefBufferBoost->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::chkInputBufferDisableClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetInputBufferDisable(chkInputBufferDisable->GetValue());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbADCSamplingPhaseChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetADCSamplingPhase(cmbADCSamplingPhase->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbClockNonOverlapAdjustChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetClockNonOverlapAdjust(cmbClockNonOverlapAdjust->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrADCBiasResistorAdjustClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetADCBiasResistorAdjust(rgrADCBiasResistorAdjust->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbMainBiasDNChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetMainBiasDN(cmbMainBiasDN->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrADCAmp1Stage1BasUpClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetADCAmp1Stage1BiasUp(rgrADCAmp1Stage1BasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrADCAmp24Stage1BasUpClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetADCAmp24Stage1BiasUp(rgrADCAmp24Stage1BasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrADCAmp1Stage2BasUpClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetADCAmp1Stage2BiasUp(rgrADCAmp1Stage2BasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrADCAmp24Stage2BasUpClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetADCAmp24Stage2BiasUp(rgrADCAmp24Stage2BasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrQuantizerBiasUpClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetQuantizerBiasUp(rgrQuantizerBiasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrInputBufferBiasUpClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetInputBufferBiasUp(rgrInputBufferBiasUp->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbDACInternalOutputLoadResistorChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetDACInternalOutputLoadResistor(cmbDACInternalOutputLoadResistor->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::rgrDACReferenceCurrentResistorClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetDACReferenceCurrentResistor(rgrDACReferenceCurrentResistor->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlADDC::cmbDACFullScaleOutputCurrentChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_ADDCSetDACFullScaleOutputCurrent(cmbDACFullScaleOutputCurrent->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlADDC::SetGuiDecode(int Decode)
{

};

// ---------------------------------------------------------------------------
//	updates GUI data values
// ---------------------------------------------------------------------------
bool pnlADDC::UpdateGUI()
{
	int itmp;

	// EN
	chbEN_ADC_DAC->SetValue(LMLL_ADDCGetEN_ADC_DAC());

	// DECODE
	rgrDecode->SetSelection( LMLL_ADDCGetDecode());

	// TX_CTRL1[6:4]
	cmbDACInternalOutputLoadResistor->SetSelection(LMLL_ADDCGetDACInternalOutputLoadResistor());

	// TX_CTRL1[3]
	rgrDACReferenceCurrentResistor->SetSelection(LMLL_ADDCGetDACReferenceCurrentResistor());

	// TX_CTRL1[1:0]
	cmbDACFullScaleOutputCurrent->SetSelection(	LMLL_ADDCGetDACFullScaleOutputCurrent());

	// RX_CTRL1[7:6]
	cmbRefResistorBiasAdj->SetSelection( LMLL_ADDCGetRefResistorBiasAdj());

	// RX_CTRL1[5:4]
	cmbRefBiasUp->SetSelection( LMLL_ADDCGetRefBiasUp());

	// RX_CTRL1[3:0]
	cmbRefBiasDn->SetSelection( LMLL_ADDCGetRefBiasDn());

	// RX_CTRL2[7:6]
	cmbRefGainAdj->SetSelection( LMLL_ADDCGetRefGainAdj());

	// RX_CTRL2[5:4]
	cmbCoomonModeAdj->SetSelection( LMLL_ADDCGetCoomonModeAdj());

	// RX_CTRL2[3:2]
	cmbRefBufferBoost->SetSelection( LMLL_ADDCGetRefBufferBoost());

	// RX_CTRL2[0]
	chkInputBufferDisable->SetValue(LMLL_ADDCGetInputBufferDisable());

	// MISC_CTRL[9]
	rgrRX_FSYNC_P->SetSelection( LMLL_ADDCGetRX_FSYNC_P());

	// MISC_CTRL[8]
	rgrRX_INTER->SetSelection( LMLL_ADDCGetRX_INTER());

	// MISC_CTRL[7]
	rgrDAC_CLK_P->SetSelection( LMLL_ADDCGetDAC_CLK_P());

	// MISC_CTRL[6]
	rgrTX_FSYNC_P->SetSelection( LMLL_ADDCGetTX_FSYNC_P());

	// MISC_CTRL[5]
	rgrTX_INTER->SetSelection( LMLL_ADDCGetTX_INTER());

	// RX_CTRL3[7]
	cmbADCSamplingPhase->SetSelection( LMLL_ADDCGetADCSamplingPhase());

	// RX_CTRL3[1:0]
	cmbClockNonOverlapAdjust->SetSelection(LMLL_ADDCGetClockNonOverlapAdjust());

	// RX_CTRL4[7:6]
	rgrADCBiasResistorAdjust->SetSelection(	LMLL_ADDCGetADCBiasResistorAdjust());

	// RX_CTRL4[5:4]
	cmbMainBiasDN->SetSelection( LMLL_ADDCGetMainBiasDN());

	// RX_CTRL4[3:2]
	rgrADCAmp1Stage1BasUp->SetSelection( LMLL_ADDCGetADCAmp1Stage1BiasUp());

	// RX_CTRL4[1:0]
	rgrADCAmp24Stage1BasUp->SetSelection( LMLL_ADDCGetADCAmp24Stage1BiasUp());

	// RX_CTRL5[7:6]
	rgrADCAmp1Stage2BasUp->SetSelection( LMLL_ADDCGetADCAmp1Stage2BiasUp());

	// RX_CTRL5[5:4]
	rgrADCAmp24Stage2BasUp->SetSelection( LMLL_ADDCGetADCAmp24Stage2BiasUp());

	// RX_CTRL5[3:2]
	rgrQuantizerBiasUp->SetSelection( LMLL_ADDCGetQuantizerBiasUp());

	// RX_CTRL5[1:0]
	rgrInputBufferBiasUp->SetSelection( LMLL_ADDCGetInputBufferBiasUp());

	// REF_CTRL0[7:4]
	cmbBandgapTemp->SetSelection( LMLL_ADDCGetBandgapTemp());

	// REF_CTRL0[3:0]
	cmbBandgapGain->SetSelection( LMLL_ADDCGetBandgapGain());

	// REF_CTRL1[7:6]
	cmbRefAmpsBiasAdj->SetSelection( LMLL_ADDCGetRefAmpsBiasAdj());

	// REF_CTRL1[5:4]
	cmbRefAmpsBiasUp->SetSelection( LMLL_ADDCGetRefAmpsBiasUp());

	// REF_CTRL1[3:0]
	cmbRefAmpsBiasDn->SetSelection( LMLL_ADDCGetRefAmpsBiasDn());

	// MISC_CTRL[4]
	chkEN_DAC->SetValue(LMLL_ADDCGetEN_DAC());

	// EN_ADC_I
	chkEN_ADC_I->SetValue(LMLL_ADDCGetEN_ADC_I());

	// EN_ADC_Q
	chkEN_ADC_Q->SetValue(LMLL_ADDCGetEN_ADC_Q());

	// EN_ADC_REF
	chkEN_ADC_REF->SetValue(LMLL_ADDCGetEN_ADC_REF());

	// EN_M_REF
	chkEN_M_REF->SetValue(LMLL_ADDCGetEN_M_REF());

    SetGuiDecode();

	return true;
};

void pnlADDC::OnEraseBackground(wxEraseEvent& event)
{
}

void pnlADDC::FillComboBoxes()
{
    Freeze();
	// Bandgap Temperature Coefficient Control
	wxString cs_Bandgap[16];
	cs_Bandgap[0] = ("-8 (Min)");
	cs_Bandgap[1] = ("-7");
	cs_Bandgap[2] = ("-6");
	cs_Bandgap[3] = ("-5");
	cs_Bandgap[4] = ("-4");
	cs_Bandgap[5] = ("-3");
	cs_Bandgap[6] = ("-2");
	cs_Bandgap[7] = ("-1");
	cs_Bandgap[8] = (" 0 (Nom)");
	cs_Bandgap[9] = (" 1");
	cs_Bandgap[10] = (" 2");
	cs_Bandgap[11] = (" 3");
	cs_Bandgap[12] = (" 4");
	cs_Bandgap[13] = (" 5");
	cs_Bandgap[14] = (" 6");
	cs_Bandgap[15] = (" 7 (Max)");

	cmbBandgapTemp->Clear();
	cmbBandgapTemp->Append(16, cs_Bandgap);
	cmbBandgapTemp->SetSelection( 8);

	// Bandgap Gain Control
	cmbBandgapGain->Clear();
	cmbBandgapGain->Append(16, cs_Bandgap);
	cmbBandgapGain->SetSelection(8);

	// ============== REFERENECE CONTROL REGISTERS 1 ==========
	// Reference Amps bias adjust
	wxString cs_Amps[4] = {"20uA","40uA","10uA","15uA"};
	cmbRefAmpsBiasAdj->Clear();
	cmbRefAmpsBiasAdj->Append(4, cs_Amps);
	cmbRefAmpsBiasAdj->SetSelection(0);

	// Reference Amps bias UP
	wxString cs_Bias[4] = {"1.0X" , "1.5X", "2.0X", "2.5X"};
	cmbRefAmpsBiasUp->Clear();
	cmbRefAmpsBiasUp->Append(4, cs_Bias);
	cmbRefAmpsBiasUp->SetSelection(0);

	// Reference Amps bias DOWN
	cmbRefAmpsBiasDn->Clear();
	wxString cs_Numbers[16];
	for (int i = 0; i < 16; i++)
		cs_Numbers[i] = wxString::Format("%i", i);
	cmbRefAmpsBiasDn->Append( 16, cs_Numbers);
	cmbRefAmpsBiasDn->SetSelection(0);

	// ============== ADC CONTROL REGISTERS 1 ==========
	// Reference bias resistor adjust
	cmbRefResistorBiasAdj->Clear();
	cmbRefResistorBiasAdj->Append(4, cs_Amps);
	cmbRefResistorBiasAdj->SetSelection(0);

	// Reference bias UP
	cmbRefBiasUp->Clear();
	cmbRefBiasUp->Append(4, cs_Bias);
	cmbRefBiasUp->SetSelection(0);

	// Reference bias DN
	cmbRefBiasDn->Clear();
	cmbRefBiasDn->Append( 16, cs_Numbers);
	cmbRefBiasDn->SetSelection(0);

	// ============== ADC CONTROL REGISTERS 2 ==========
	// Reference Gain Adjust
	cmbRefGainAdj->Clear();
	wxString cs_RefGain[4] = { "1.50V", "1.75V","1.00V","1.25V"};
	cmbRefGainAdj->Append(4, cs_RefGain);
	cmbRefGainAdj->SetSelection(0);

	// Common Mode Adjust
	cmbCoomonModeAdj->Clear();
	wxString cs_Coomon[4] = {"875mV","960mV","700mV","790mV"};
	cmbCoomonModeAdj->Append(4, cs_Coomon);
	cmbCoomonModeAdj->SetSelection(0);

	// Reference Buffer Boost
	cmbRefBufferBoost->Clear();
	cmbRefBufferBoost->Append(4, cs_Bias);
	cmbRefBufferBoost->SetSelection(0);

	// ============== ADC CONTROL REGISTERS 3 ==========
	// ADC Sampling Phase Select
	cmbADCSamplingPhase->Clear();
	cmbADCSamplingPhase->Append("Rising Edge");
	cmbADCSamplingPhase->Append("Falling Edge");
	cmbADCSamplingPhase->SetSelection(0);

	// Clock Non-Overlap Adjust
	cmbClockNonOverlapAdjust->Clear();
	cmbClockNonOverlapAdjust->Append("Nominal");
	cmbClockNonOverlapAdjust->Append("+450ps");
	cmbClockNonOverlapAdjust->Append("+150ps");
	cmbClockNonOverlapAdjust->Append("+300ps");
	cmbClockNonOverlapAdjust->SetSelection(0);

	// Main bias DOWN
	cmbMainBiasDN->Clear();
	cmbMainBiasDN->Append("0 (Nom)");
	cmbMainBiasDN->Append("1");
	cmbMainBiasDN->Append("2");
	cmbMainBiasDN->Append("3 (Min)");
	cmbMainBiasDN->SetSelection(0);

	cmbDACInternalOutputLoadResistor->Clear();
	wxString cs_DAC[8] = {"Open Circuit","100 Ohms","200 Ohms"," 66 Ohms","200 Ohms"," 66 Ohms","100 Ohms"," 50 Ohms"};

	cmbDACInternalOutputLoadResistor->Append(8, cs_DAC);
	cmbDACInternalOutputLoadResistor->SetSelection( 2);

	// DAC Full Scale Output Current Control (single-ended)
	cmbDACFullScaleOutputCurrent->Clear();
	cmbDACFullScaleOutputCurrent->Append("  5 mA");
	cmbDACFullScaleOutputCurrent->Append(" 10 mA");
	cmbDACFullScaleOutputCurrent->Append("2.5 mA");
	cmbDACFullScaleOutputCurrent->Append("  5 mA");
	cmbDACFullScaleOutputCurrent->SetSelection(0);

	Thaw();
}
