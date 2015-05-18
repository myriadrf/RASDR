// -----------------------------------------------------------------------------
// FILE:        "pnlTxRF.cpp"
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
#include "pnlTxRF.h"
#include "ctr_6002dr2_LogicDLL.h"

//(*InternalHeaders(pnlTxRF)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlTxRF)
const long pnlTxRF::ID_CHECKBOX1 = wxNewId();
const long pnlTxRF::ID_CHECKBOX2 = wxNewId();
const long pnlTxRF::ID_CHECKBOX3 = wxNewId();
const long pnlTxRF::ID_CHECKBOX4 = wxNewId();
const long pnlTxRF::ID_CHECKBOX5 = wxNewId();
const long pnlTxRF::ID_CHECKBOX6 = wxNewId();
const long pnlTxRF::ID_CHECKBOX7 = wxNewId();
const long pnlTxRF::ID_CHECKBOX8 = wxNewId();
const long pnlTxRF::ID_STATICTEXT5 = wxNewId();
const long pnlTxRF::ID_COMBOBOX5 = wxNewId();
const long pnlTxRF::ID_STATICTEXT6 = wxNewId();
const long pnlTxRF::ID_COMBOBOX6 = wxNewId();
const long pnlTxRF::ID_STATICTEXT7 = wxNewId();
const long pnlTxRF::ID_COMBOBOX7 = wxNewId();
const long pnlTxRF::ID_CHECKBOX10 = wxNewId();
const long pnlTxRF::ID_CHECKBOX9 = wxNewId();
const long pnlTxRF::ID_STATICTEXT1 = wxNewId();
const long pnlTxRF::ID_COMBOBOX1 = wxNewId();
const long pnlTxRF::ID_STATICTEXT2 = wxNewId();
const long pnlTxRF::ID_COMBOBOX4 = wxNewId();
const long pnlTxRF::ID_STATICTEXT3 = wxNewId();
const long pnlTxRF::ID_COMBOBOX2 = wxNewId();
const long pnlTxRF::ID_STATICTEXT4 = wxNewId();
const long pnlTxRF::ID_COMBOBOX3 = wxNewId();
const long pnlTxRF::ID_RADIOBOX3 = wxNewId();
const long pnlTxRF::ID_RADIOBOX1 = wxNewId();
const long pnlTxRF::ID_RADIOBOX2 = wxNewId();
const long pnlTxRF::ID_STATICTEXT8 = wxNewId();
const long pnlTxRF::ID_STATICTEXT9 = wxNewId();
const long pnlTxRF::ID_COMBOBOX8 = wxNewId();
const long pnlTxRF::ID_COMBOBOX9 = wxNewId();
const long pnlTxRF::ID_STATICTEXT10 = wxNewId();
const long pnlTxRF::ID_STATICTEXT11 = wxNewId();
const long pnlTxRF::ID_COMBOBOX10 = wxNewId();
const long pnlTxRF::ID_COMBOBOX11 = wxNewId();
const long pnlTxRF::ID_STATICTEXT12 = wxNewId();
const long pnlTxRF::ID_STATICTEXT13 = wxNewId();
const long pnlTxRF::ID_COMBOBOX12 = wxNewId();
const long pnlTxRF::ID_COMBOBOX13 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTxRF,wxPanel)
	//(*EventTable(pnlTxRF)
	//*)
END_EVENT_TABLE()

pnlTxRF::pnlTxRF(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
	BuildContent(parent,id,pos,size);
}

// ---------------------------------------------------------------------------
void pnlTxRF::Initialize()
{
	sendChanges = false;
	m_cMAddr = LMLL_TxRfGetAddr();
	LMAL_GetVerRevMask(m_cVer, m_cRev, m_cMask);
	FillComboBoxes();
	SetGuiDefaults();
	sendChanges = true;
};

// ---------------------------------------------------------------------------
void pnlTxRF::SetGuiDefaults()
{
    Freeze();
	int itmp;
	double dtmp;

	wxString cs_Numbers[512];
	for(int i=0; i<512; i++)
        cs_Numbers[i] = wxString::Format("%i", i);

	// DECODE
	rgrDecode->SetSelection( 0);
	// EN
	chbPwrTxRfMods->SetValue(true);

	// VGA1GAIN[4:0]
	// VGA1GAINT[7:0]
	cmbVga1G_u->Clear();
	cmbVga1G_t->Clear();
	itmp = -35;
	for(int i=0; i<32; i++)
        cs_Numbers[i] = wxString::Format("%i", i-35);
    cmbVga1G_u->Append( 32 , cs_Numbers );
    cmbVga1G_t->Append( 32 , cs_Numbers );

	cmbVga1G_u->SetSelection( 21);
	cmbVga1G_t->SetSelection( 21);

	// VGA1DC_Q[7:0]
	// VGA1DC_I[7:0]
	cmbVga1DcI->Clear();
	cmbVga1DcQ->Clear();
	dtmp = -16;
    for(int i=0; i<256; i++)
    {
        cs_Numbers[i] = wxString::Format("%.6g", dtmp);
        dtmp += 0.125;
    }

	cmbVga1DcI->Append( 256, cs_Numbers);
	cmbVga1DcQ->Append( 256, cs_Numbers);
	cmbVga1DcI->SetSelection( 128);
	cmbVga1DcQ->SetSelection( 128);

	// PA_EN
	rgrPA->SetSelection( 1);
	// PD_DRVAUX
	chbPD_DRVAUX->SetValue(true);
	// PD_PKDET
	chbPD_PKDET->SetValue(true);

	// MIXVGA2GAIN[4:0]
	cmbVga2G_u->Clear();
	for(int i=0; i<26; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
    cmbVga2G_u->Append( 26, cs_Numbers);
	cmbVga2G_u->SetSelection( 0);

	// MIXVGA2GAINT[8:0]
	cmbVga2G_t->Clear();
	for(int i=0; i<512; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
    cmbVga2G_t->Append( 512, cs_Numbers);
	cmbVga2G_t->SetSelection( 0);

	// ENVD[1:0]
	cmbENVD->Clear();
	wxString cs_ENVD[4] = {"AUXPA ED output", "AUXPA PD output", "PA1 ED output", "PA2 PD output"};
	cmbENVD->Append(4, cs_ENVD);
	cmbENVD->SetSelection( 0);

	// ENVD[2]
	cmbENVD2->Clear();
	wxString cs_ENVD2[2] = {"Reference DC", "Detector Average"};
	cmbENVD2->Append(2, cs_ENVD2);
	cmbENVD2->SetSelection( 0);

	// PKDBW[3:0]
	cmbPKDBW->Clear();
	cmbPKDBW->Append( 16, cs_Numbers);
	cmbPKDBW->SetSelection( 0);
	// LOOPBBEN
	rgrLOOPBBEN->SetSelection( 0);
	// FST_PKDET
	chbFST_PKDET->SetValue(false);
	// FST_TXHFBIAS
	chbFST_TXHFBIAS->SetValue(false);

	// ICT_TXLOBUF[3:0]
	cmbICT_TXLOBUF->Clear();
	cmbICT_TXLOBUF->Append( 16, cs_Numbers);
	// cmbICT_TXLOBUF->SetSelection( 6);
	cmbICT_TXLOBUF->SetSelection( 4);

	// VBCAS_TXDRV[3:0]
	cmbVBCAS_TXDRV->Clear();
	cmbVBCAS_TXDRV->Append( 16, cs_Numbers);
    cmbVBCAS_TXDRV->SetSelection( 0);

	// ICT_TXMIX[4:0]
	cmbICT_TXMIX->Clear();
    cmbICT_TXMIX->Append( 32, cs_Numbers);
	cmbICT_TXMIX->SetSelection( 12);

	// ICT_TXDRV[4:0]
	cmbICT_TXDRV->Clear();
    cmbICT_TXDRV->Append( 32, cs_Numbers);
	cmbICT_TXDRV->SetSelection( 12);

	chbPwrVga1_I->SetValue(true);
	chbPwrVga1_Q->SetValue(true);
	chbPD_TXDRV->SetValue(false);
	chbPD_TXLOBUF->SetValue(false);
	chbPwrVga2->SetValue(false);

	SetGuiDecode();
	Thaw();
};

// ---------------------------------------------------------------------------
void pnlTxRF::SetGuiDecode()
{
	if (rgrDecode->GetSelection() == 0)
	{
		// Decode
		chbPwrTxRfMods->Enable(true);
		cmbVga1G_u->Enable(true);
		cmbVga2G_u->Enable(true);

		chbPwrVga1_I->Enable(false);
		chbPwrVga1_Q->Enable(false);
		chbPwrVga2->Enable(false);
		cmbVga1G_t->Enable(false);
		cmbVga2G_t->Enable(false);
		chbPD_TXDRV->Enable(false);
		chbPD_TXLOBUF->Enable(false);

		if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
		{
			chbPD_DRVAUX->Enable(true);
			chbPD_PKDET->Enable(true);
		}
		else
		{
			chbPD_DRVAUX->Enable(false);
			chbPD_PKDET->Enable(false);
		};
	}
	else
	{
		// Direct control
		chbPwrTxRfMods->Enable(false);
		cmbVga1G_u->Enable(false);
		cmbVga2G_u->Enable(false);

		chbPwrVga1_I->Enable(true);
		chbPwrVga1_Q->Enable(true);
		chbPwrVga2->Enable(true);
		cmbVga1G_t->Enable(true);
		cmbVga2G_t->Enable(true);
		chbPD_TXDRV->Enable(true);
		chbPD_TXLOBUF->Enable(true);
		chbPD_PKDET->Enable(true);
		chbPD_DRVAUX->Enable(true);
	};
};

void pnlTxRF::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTxRF)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxSize(283,209), wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrTxRfMods = new wxCheckBox(this, ID_CHECKBOX1, _("TxRF Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chbPwrTxRfMods->SetValue(false);
	StaticBoxSizer1->Add(chbPwrTxRfMods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_DRVAUX = new wxCheckBox(this, ID_CHECKBOX2, _("Auxiliary PA Power Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chbPD_DRVAUX->SetValue(false);
	StaticBoxSizer1->Add(chbPD_DRVAUX, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_PKDET = new wxCheckBox(this, ID_CHECKBOX3, _("PDED Power Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chbPD_PKDET->SetValue(false);
	StaticBoxSizer1->Add(chbPD_PKDET, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrVga1_I = new wxCheckBox(this, ID_CHECKBOX4, _("VGA1 I Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chbPwrVga1_I->SetValue(false);
	StaticBoxSizer1->Add(chbPwrVga1_I, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrVga1_Q = new wxCheckBox(this, ID_CHECKBOX5, _("VGA1 Q Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chbPwrVga1_Q->SetValue(false);
	StaticBoxSizer1->Add(chbPwrVga1_Q, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_TXDRV = new wxCheckBox(this, ID_CHECKBOX6, _("PA1, PA2, AUXPA Disabled"), wxDefaultPosition, wxSize(167,13), 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chbPD_TXDRV->SetValue(false);
	StaticBoxSizer1->Add(chbPD_TXDRV, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_TXLOBUF = new wxCheckBox(this, ID_CHECKBOX7, _("TxLOBUF Disabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chbPD_TXLOBUF->SetValue(false);
	StaticBoxSizer1->Add(chbPD_TXLOBUF, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrVga2 = new wxCheckBox(this, ID_CHECKBOX8, _("MIX and VGA2 Disabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chbPwrVga2->SetValue(false);
	StaticBoxSizer1->Add(chbPwrVga2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("EDPD Control"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Detector Select:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticBoxSizer3->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbENVD = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	StaticBoxSizer3->Add(cmbENVD, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Signal for AC Coupling:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	StaticBoxSizer3->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbENVD2 = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	StaticBoxSizer3->Add(cmbENVD2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("PDED Bandwidth:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	StaticBoxSizer3->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbPKDBW = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	StaticBoxSizer3->Add(cmbPKDBW, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbFST_PKDET = new wxCheckBox(this, ID_CHECKBOX10, _("Short the Resistors in PDED"), wxDefaultPosition, wxSize(158,13), 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chbFST_PKDET->SetValue(false);
	StaticBoxSizer3->Add(chbFST_PKDET, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Bias Control"));
	chbFST_TXHFBIAS = new wxCheckBox(this, ID_CHECKBOX9, _("Tx HF Bias Resistors Shorted"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chbFST_TXHFBIAS->SetValue(false);
	StaticBoxSizer2->Add(chbFST_TXHFBIAS, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("LO Buffer Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticBoxSizer2->Add(StaticText1, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TXLOBUF = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	StaticBoxSizer2->Add(cmbICT_TXLOBUF, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("PA Cascode NPNs Bias:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBoxSizer2->Add(StaticText2, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVBCAS_TXDRV = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	StaticBoxSizer2->Add(cmbVBCAS_TXDRV, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("MIX Bias Current, mA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticBoxSizer2->Add(StaticText3, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TXMIX = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	StaticBoxSizer2->Add(cmbICT_TXMIX, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("PAs Bias Current, mA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticBoxSizer2->Add(StaticText4, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TXDRV = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	StaticBoxSizer2->Add(cmbICT_TXDRV, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[4] =
	{
		_("Switches Open"),
		_("TxLPF Output to BBLB"),
		_("TxVGA1 Output to BBLB"),
		_("PDED Output to BBLB")
	};
	rgrLOOPBBEN = new wxRadioBox(this, ID_RADIOBOX3, _("BB Loop Back Control"), wxPoint(192,224), wxSize(168,101), 4, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX3"));
	FlexGridSizer5->Add(rgrLOOPBBEN, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	wxString __wxRadioBoxChoices_2[3] =
	{
		_("PA1 and PA2 Off"),
		_("PA1 Selected"),
		_("PA2 Selected")
	};
	rgrPA = new wxRadioBox(this, ID_RADIOBOX1, _("PA Selection"), wxPoint(368,8), wxSize(144,82), 3, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrPA->SetSelection(0);
	FlexGridSizer7->Add(rgrPA, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_RADIOBOX2, _("Decoding"), wxPoint(520,8), wxSize(136,80), 2, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrDecode->SetSelection(0);
	FlexGridSizer7->Add(rgrDecode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VGA1 Control"));
	FlexGridSizer1 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("VGA1 Gain, dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer1->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("LO Leakage I DAC Out, mV:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer1->Add(StaticText9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga1G_u = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	FlexGridSizer1->Add(cmbVga1G_u, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga1DcI = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
	FlexGridSizer1->Add(cmbVga1DcI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("VGA1 Gain (Test), dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer1->Add(StaticText10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("LO Leakage Q DAC Out, mV:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer1->Add(StaticText11, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga1G_t = new wxComboBox(this, ID_COMBOBOX10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX10"));
	FlexGridSizer1->Add(cmbVga1G_t, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga1DcQ = new wxComboBox(this, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX11"));
	FlexGridSizer1->Add(cmbVga1DcQ, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer4, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VGA2 Control"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("VGA2 Gain, dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer2->Add(StaticText12, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("VGA2 Gain (Test):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer2->Add(StaticText13, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2G_u = new wxComboBox(this, ID_COMBOBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX12"));
	FlexGridSizer2->Add(cmbVga2G_u, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2G_t = new wxComboBox(this, ID_COMBOBOX13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX13"));
	FlexGridSizer2->Add(cmbVga2G_t, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer5, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer6, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer3);
	SetSizer(FlexGridSizer3);
	Layout();

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPwrTxRfModsClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPD_DRVAUXClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPD_PKDETClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPwrVga1_IClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPwrVga1_QClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPD_TXDRVClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPD_TXLOBUFClick);
	Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbPwrVga2Click);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbENVDChange);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbENVD2Change);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbPKDBWChange);
	Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbFST_PKDETClick);
	Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::chbFST_TXHFBIASClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbICT_TXLOBUFChange);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbVBCAS_TXDRVChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbICT_TXMIXChange);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbICT_TXDRVChange);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::rgrLOOPBBENClick);
	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::rgrPAClick);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::rgrDecodeClick);
	Connect(ID_COMBOBOX8,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbVga1G_uChange);
	Connect(ID_COMBOBOX9,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbVga1DcIChange);
	Connect(ID_COMBOBOX10,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbVga1G_tChange);
	Connect(ID_COMBOBOX11,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbVga1DcQChange);
	Connect(ID_COMBOBOX12,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbVga2G_uChange);
	Connect(ID_COMBOBOX13,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::cmbVga2G_tChange);
	//*)
}

pnlTxRF::~pnlTxRF()
{
	//(*Destroy(pnlTxRF)
	//*)
}

// ---------------------------------------------------------------------------
void pnlTxRF::chbPwrTxRfModsClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPwrTxRfMods(chbPwrTxRfMods->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxRF::rgrDecodeClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetDecode(rgrDecode->GetSelection());
	SetGuiDecode();
}

// ---------------------------------------------------------------------------
void pnlTxRF::cmbVga1G_uChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetVga1G_u(cmbVga1G_u->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxRF::cmbVga1DcIChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetVga1DcI(cmbVga1DcI->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxRF::cmbVga1DcQChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetVga1DcQ(cmbVga1DcQ->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxRF::rgrPAClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPA(rgrPA->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxRF::cmbVga2G_uChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetVga2G_u(cmbVga2G_u->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxRF::chbPwrVga1_IClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPwrVga1_I(chbPwrVga1_I->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxRF::chbPwrVga2Click(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPwrVga2(chbPwrVga2->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxRF::cmbVga1G_tChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetVga1G_t(cmbVga1G_t->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxRF::cmbVga2G_tChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetVga2G_t(cmbVga2G_t->GetSelection());
}

// ---------------------------------------------------------------------------
void pnlTxRF::chbPwrVga1_QClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPwrVga1_Q(chbPwrVga1_Q->GetValue());
}

// ---------------------------------------------------------------------------
void pnlTxRF::rgrLOOPBBENClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetLOOPBBEN(rgrLOOPBBEN->GetSelection());
}

// ---------------------------------------------------------------------------

void pnlTxRF::chbPD_DRVAUXClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPD_DRVAUX(chbPD_DRVAUX->GetValue());
}

// ---------------------------------------------------------------------------

void pnlTxRF::chbPD_PKDETClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPD_PKDET(chbPD_PKDET->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxRF::cmbENVDChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetENVD(cmbENVD->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxRF::cmbENVD2Change(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetENVD2(cmbENVD2->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxRF::cmbPKDBWChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPKDBW(cmbPKDBW->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxRF::chbFST_PKDETClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetFST_PKDET(chbFST_PKDET->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxRF::chbFST_TXHFBIASClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetFST_TXHFBIAS(chbFST_TXHFBIAS->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxRF::cmbICT_TXLOBUFChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetICT_TXLOBUF(cmbICT_TXLOBUF->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxRF::cmbVBCAS_TXDRVChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetVBCAS_TXDRV(cmbVBCAS_TXDRV->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxRF::cmbICT_TXMIXChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetICT_TXMIX(cmbICT_TXMIX->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxRF::cmbICT_TXDRVChange(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetICT_TXDRV(cmbICT_TXDRV->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlTxRF::chbPD_TXLOBUFClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPD_TXLOBUF(chbPD_TXLOBUF->GetValue());
}
// ---------------------------------------------------------------------------

void pnlTxRF::chbPD_TXDRVClick(wxCommandEvent& event)
{
	if(sendChanges) LMLL_TxRfSetPD_TXDRV(chbPD_TXDRV->GetValue());
}

// ---------------------------------------------------------------------------
// updates GUI data values
// ---------------------------------------------------------------------------
bool pnlTxRF::UpdateGUI()
{
	int itmp;
	bool bRez = true;

	// EN
	chbPwrTxRfMods->SetValue(LMLL_TxRfGetPwrTxRfMods());

	// DECODE
	rgrDecode->SetSelection(LMLL_TxRfGetDecode());

	// VGA1GAIN[4:0]
	cmbVga1G_u->SetSelection(LMLL_TxRfGetVga1G_u());

	// VGA1DC_I[7:0]
	cmbVga1DcI->SetSelection(LMLL_TxRfGetVga1DcI());

	// VGA1DC_Q[7:0]
	cmbVga1DcQ->SetSelection(LMLL_TxRfGetVga1DcQ());

	// PA_EN[2:0]
	rgrPA->SetSelection(LMLL_TxRfGetPA());

	// PD_DRVAUX
	chbPD_DRVAUX->SetValue(LMLL_TxRfGetPD_DRVAUX());

	// PD_PKDET
	chbPD_PKDET->SetValue(LMLL_TxRfGetPD_PKDET());

	// VGA2GAIN[4:0]
	cmbVga2G_u->SetSelection(LMLL_TxRfGetVga2G_u());

	// ENVD[2]
	cmbENVD2->SetSelection(LMLL_TxRfGetENVD2());

	// ENVD[1:0]
	cmbENVD->SetSelection(LMLL_TxRfGetENVD());

	// PKDBW[3:0]
	cmbPKDBW->SetSelection(LMLL_TxRfGetPKDBW());

	// LOOPBBEN[1:0]
	rgrLOOPBBEN->SetSelection(LMLL_TxRfGetLOOPBBEN());

	// FST_PKDET
	chbFST_PKDET->SetValue(LMLL_TxRfGetFST_PKDET());

	// FST_TXHFBIAS
	chbFST_TXHFBIAS->SetValue(LMLL_TxRfGetFST_TXHFBIAS());

	// ICT_TXLOBUF[3:0]
	cmbICT_TXLOBUF->SetSelection(LMLL_TxRfGetICT_TXLOBUF());

	// VBCAS_TXDRV[3:0]
	cmbVBCAS_TXDRV->SetSelection(LMLL_TxRfGetVBCAS_TXDRV());

	// ICT_TXMIX[4:0]
	cmbICT_TXMIX->SetSelection(LMLL_TxRfGetICT_TXMIX());

	// ICT_TXDRV[4:0]
	cmbICT_TXDRV->SetSelection(LMLL_TxRfGetICT_TXDRV());

	// PW_VGA1_I
	chbPwrVga1_I->SetValue(LMLL_TxRfGetPwrVga1_I());

	// PW_VGA1_Q
	chbPwrVga1_Q->SetValue(LMLL_TxRfGetPwrVga1_Q());

	// PD_TXDRV
	chbPD_TXDRV->SetValue(LMLL_TxRfGetPD_TXDRV());

	// PD_TXLOBUF
	chbPD_TXLOBUF->SetValue(LMLL_TxRfGetPD_TXLOBUF());

	// PD_TXMIX
	chbPwrVga2->SetValue(LMLL_TxRfGetPwrVga2());

	// VGA1GAINT[7:0]
	cmbVga1G_t->SetSelection(LMLL_TxRfGetVga1G_t());

	// G_TXVGA2[8:0]
	cmbVga2G_t->SetSelection(LMLL_TxRfGetVga2G_t());

    SetGuiDecode();

	return bRez;
};

void pnlTxRF::FillComboBoxes()
{
    Freeze();
	int itmp;
	double dtmp;

	wxString cs_Numbers[512];
	for(int i=0; i<512; i++)
        cs_Numbers[i] = wxString::Format("%i", i);


	// VGA1GAIN[4:0]
	// VGA1GAINT[7:0]
	cmbVga1G_u->Clear();
	cmbVga1G_t->Clear();
	itmp = -35;
	for(int i=0; i<32; i++)
        cs_Numbers[i] = wxString::Format("%i", i-35);
    cmbVga1G_u->Append( 32 , cs_Numbers );
    cmbVga1G_t->Append( 32 , cs_Numbers );

	cmbVga1G_u->SetSelection( 21);
	cmbVga1G_t->SetSelection( 21);

	// VGA1DC_Q[7:0]
	// VGA1DC_I[7:0]
	cmbVga1DcI->Clear();
	cmbVga1DcQ->Clear();
	dtmp = -16;
    for(int i=0; i<256; i++)
    {
        cs_Numbers[i] = wxString::Format("%f", dtmp);
        dtmp += 0.125;
    }

	cmbVga1DcI->Append( 256, cs_Numbers);
	cmbVga1DcQ->Append( 256, cs_Numbers);
	cmbVga1DcI->SetSelection( 128);
	cmbVga1DcQ->SetSelection( 128);

	// MIXVGA2GAIN[4:0]
	cmbVga2G_u->Clear();
	for(int i=0; i<26; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
    cmbVga2G_u->Append( 26, cs_Numbers);
	cmbVga2G_u->SetSelection( 0);

	// MIXVGA2GAINT[8:0]
	cmbVga2G_t->Clear();
	for(int i=0; i<512; i++)
        cs_Numbers[i] = wxString::Format("%i", i);
    cmbVga2G_t->Append( 512, cs_Numbers);
	cmbVga2G_t->SetSelection( 0);

	// ENVD[1:0]
	cmbENVD->Clear();
	wxString cs_ENVD[4] = {"AUXPA ED output", "AUXPA PD output", "PA1 ED output", "PA2 PD output"};
	cmbENVD->Append(4, cs_ENVD);
	cmbENVD->SetSelection( 0);

	// ENVD[2]
	cmbENVD2->Clear();
	wxString cs_ENVD2[2] = {"Reference DC", "Detector Average"};
	cmbENVD2->Append(2, cs_ENVD2);
	cmbENVD2->SetSelection( 0);

	// PKDBW[3:0]
	cmbPKDBW->Clear();
	cmbPKDBW->Append( 16, cs_Numbers);
	cmbPKDBW->SetSelection( 0);
	// LOOPBBEN
	rgrLOOPBBEN->SetSelection( 0);

	// ICT_TXLOBUF[3:0]
	cmbICT_TXLOBUF->Clear();
	cmbICT_TXLOBUF->Append( 16, cs_Numbers);
	// cmbICT_TXLOBUF->SetSelection( 6);
	cmbICT_TXLOBUF->SetSelection( 4);

	// VBCAS_TXDRV[3:0]
	cmbVBCAS_TXDRV->Clear();
	cmbVBCAS_TXDRV->Append( 16, cs_Numbers);
    cmbVBCAS_TXDRV->SetSelection( 0);

	// ICT_TXMIX[4:0]
	cmbICT_TXMIX->Clear();
    cmbICT_TXMIX->Append( 32, cs_Numbers);
	cmbICT_TXMIX->SetSelection( 12);

	// ICT_TXDRV[4:0]
	cmbICT_TXDRV->Clear();
    cmbICT_TXDRV->Append( 32, cs_Numbers);
	cmbICT_TXDRV->SetSelection( 12);

	Thaw();
}
