// -----------------------------------------------------------------------------
// FILE:        "pnlCustomer.cpp"
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
#include "pnlCustomer.h"
#include "ctr_6002dr2_LogicDLL.h"
#include <vector>
using namespace std;
//(*InternalHeaders(pnlCustomer)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlCustomer)
const long pnlCustomer::ID_STATICTEXT1 = wxNewId();
const long pnlCustomer::ID_COMBOBOX3 = wxNewId();
const long pnlCustomer::ID_BUTTON4 = wxNewId();
const long pnlCustomer::ID_BUTTON5 = wxNewId();
const long pnlCustomer::ID_BUTTON6 = wxNewId();
const long pnlCustomer::ID_STATICTEXT6 = wxNewId();
const long pnlCustomer::ID_STATICTEXT7 = wxNewId();
const long pnlCustomer::ID_STATICTEXT8 = wxNewId();
const long pnlCustomer::ID_COMBOBOX4 = wxNewId();
const long pnlCustomer::ID_COMBOBOX5 = wxNewId();
const long pnlCustomer::ID_COMBOBOX6 = wxNewId();
const long pnlCustomer::ID_STATICTEXT9 = wxNewId();
const long pnlCustomer::ID_STATICTEXT10 = wxNewId();
const long pnlCustomer::ID_STATICTEXT11 = wxNewId();
const long pnlCustomer::ID_STATICTEXT12 = wxNewId();
const long pnlCustomer::ID_COMBOBOX7 = wxNewId();
const long pnlCustomer::ID_COMBOBOX8 = wxNewId();
const long pnlCustomer::ID_BUTTON7 = wxNewId();
const long pnlCustomer::ID_BUTTON8 = wxNewId();
const long pnlCustomer::ID_BUTTON9 = wxNewId();
const long pnlCustomer::ID_TEXTCTRL2 = wxNewId();
const long pnlCustomer::ID_STATICTEXT2 = wxNewId();
const long pnlCustomer::ID_STATICTEXT3 = wxNewId();
const long pnlCustomer::ID_STATICTEXT4 = wxNewId();
const long pnlCustomer::ID_STATICTEXT5 = wxNewId();
const long pnlCustomer::ID_COMBOBOX1 = wxNewId();
const long pnlCustomer::ID_COMBOBOX2 = wxNewId();
const long pnlCustomer::ID_BUTTON1 = wxNewId();
const long pnlCustomer::ID_BUTTON2 = wxNewId();
const long pnlCustomer::ID_BUTTON3 = wxNewId();
const long pnlCustomer::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlCustomer,wxPanel)
	//(*EventTable(pnlCustomer)
	//*)
END_EVENT_TABLE()

pnlCustomer::pnlCustomer(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString nmb)
{
	BuildContent(parent,id,pos,size);
}

void pnlCustomer::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlCustomer)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("LNA Control"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT1, _("Active LNA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticBoxSizer2->Add(StaticText5, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbLNASEL_Cust = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(76,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	StaticBoxSizer2->Add(cmbLNASEL_Cust, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Automatic Calibration"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
	btnClbrTx = new wxButton(this, ID_BUTTON4, _("Transmitter"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer2->Add(btnClbrTx, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnClbrRx = new wxButton(this, ID_BUTTON5, _("Receiver"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer2->Add(btnClbrRx, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCalLPFCore = new wxButton(this, ID_BUTTON6, _("LPF Core"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer2->Add(btnCalLPFCore, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Bypass Congiurations"));
	FlexGridSizer3 = new wxFlexGridSizer(2, 3, 0, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Rx Bypass Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer3->Add(StaticText6, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Tx Bypass Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer3->Add(StaticText7, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("RF / BB Loopback Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer3->Add(StaticText8, 1, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbBypass = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	cmbBypass->Append(_("Normal Operation"));
	cmbBypass->Append(_("Bypass RxLPF"));
	cmbBypass->Append(_("Bypass RxLPF, RxVGA2"));
	FlexGridSizer3->Add(cmbBypass, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbTxBypass = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	cmbTxBypass->Append(_("Normal Operation"));
	cmbTxBypass->Append(_("Bypass TxLPF"));
	FlexGridSizer3->Add(cmbTxBypass, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbLoopback = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	cmbLoopback->Append(_("Normal Operation"));
	cmbLoopback->Append(_("BB loopback to RxLPF Input"));
	cmbLoopback->Append(_("BB loopback to RxVGA2 Input"));
	cmbLoopback->Append(_("BB loopback to Output Pins"));
	cmbLoopback->Append(_("RF loopback LNA1"));
	cmbLoopback->Append(_("RF loopback LNA2"));
	cmbLoopback->Append(_("RF loopback LNA3"));
	FlexGridSizer3->Add(cmbLoopback, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Downlink (Tx) Frequency Band and Channel"));
	FlexGridSizer4 = new wxFlexGridSizer(2, 4, 0, 0);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Band:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer4->Add(StaticText9, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer4->Add(StaticText10, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Fast Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer4->Add(StaticText11, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Frequency, MHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer4->Add(StaticText12, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbDLTXBands = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(51,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	FlexGridSizer4->Add(cmbDLTXBands, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDLTXChan = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(64,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	FlexGridSizer4->Add(cmbDLTXChan, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	btnDLTXFChan_B = new wxButton(this, ID_BUTTON7, _("B"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	BoxSizer2->Add(btnDLTXFChan_B, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDLTXFChan_M = new wxButton(this, ID_BUTTON8, _("M"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	BoxSizer2->Add(btnDLTXFChan_M, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDLTXFChan_T = new wxButton(this, ID_BUTTON9, _("T"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	BoxSizer2->Add(btnDLTXFChan_T, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(BoxSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDLTXFreq = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(82,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer4->Add(txtDLTXFreq, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Uplink (Rx) Frequency Band and Channel"));
	FlexGridSizer1 = new wxFlexGridSizer(2, 4, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Band:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText1, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText2, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Fast Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText3, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Frequency, MHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(StaticText4, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbULRXBands = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(51,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	FlexGridSizer1->Add(cmbULRXBands, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbULRXChan = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(64,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer1->Add(cmbULRXChan, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	btnULRXFChan_B = new wxButton(this, ID_BUTTON1, _("B"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(btnULRXFChan_B, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnULRXFChan_M = new wxButton(this, ID_BUTTON2, _("M"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(btnULRXFChan_M, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnULRXFChan_T = new wxButton(this, ID_BUTTON3, _("T"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer1->Add(btnULRXFChan_T, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtULRXFreq = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(82,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(txtULRXFreq, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer5);
	FlexGridSizer5->Fit(this);
	FlexGridSizer5->SetSizeHints(this);

	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbLNASEL_CustChange);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnClbrTxClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnClbrRxClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::Button1Click);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbBypassChange);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbTxBypassChange);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbLoopbackChange);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbDLTXBandsChange);
	Connect(ID_COMBOBOX8,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbDLTXChanChange);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnDLTXFChan_BClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnDLTXFChan_MClick);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnDLTXFChan_TClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbULRXBandsChange);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCustomer::cmbULRXChanChange);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnULRXFChan_BClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnULRXFChan_MClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCustomer::btnULRXFChan_TClick);
	//*)
}

pnlCustomer::~pnlCustomer()
{
	//(*Destroy(pnlCustomer)
	//*)
}

// ---------------------------------------------------------------------------
void pnlCustomer::SetGuiDecode()
{
};

// ---------------------------------------------------------------------------

void pnlCustomer::cmbLNASEL_CustChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_SelectActiveLNA(cmbLNASEL_Cust->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlCustomer::cmbBypassChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_SetRxBypass(cmbBypass->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlCustomer::cmbTxBypassChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_SetTxBypass(cmbTxBypass->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlCustomer::cmbLoopbackChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_SetLoopback(cmbLoopback->GetSelection());
}
// ---------------------------------------------------------------------------

void pnlCustomer::btnClbrTxClick(wxCommandEvent& event)
{
	LMAL_CalibrateTx();
}
// ---------------------------------------------------------------------------

void pnlCustomer::btnClbrRxClick(wxCommandEvent& event)
{
	LMAL_CalibrateRx();
}
// ---------------------------------------------------------------------------

void pnlCustomer::Button1Click(wxCommandEvent& event)
{
	LMAL_CalibrateLPFCore();
}
// ---------------------------------------------------------------------------

void pnlCustomer::btnCalRxTIAClick(wxCommandEvent& event)
{
//	LMAL_CalibrateRxTIA();
}
// ---------------------------------------------------------------------------

void pnlCustomer::cmbDLTXBandsChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_MainSetDLTXBand(cmbDLTXBands->GetSelection());
	setupChannels(false);
	updateFrequency(false);
//	setFastChanAllUp(false);
	// m_frmCustomer->setFastChannelsAllUp(false);
}
// ---------------------------------------------------------------------------

void pnlCustomer::cmbULRXBandsChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_MainSetULRXBand(cmbULRXBands->GetSelection());
	setupChannels(true);
	updateFrequency(true);
//	setFastChanAllUp(true);
}
// ---------------------------------------------------------------------------

void pnlCustomer::cmbDLTXChanChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_MainSetDLTXChannel(cmbDLTXChan->GetSelection());
	updateFrequency(false);
//	setFastChanAllUp(false);
	// m_frmCustomer->setFastChannelsAllUp(false);
}
// ---------------------------------------------------------------------------

void pnlCustomer::cmbULRXChanChange(wxCommandEvent& event)
{
	if(sendChanges) LMAL_MainSetULRXChannel(cmbULRXChan->GetSelection());
	updateFrequency(true);
//	setFastChanAllUp(true);
	// m_frmCustomer->setFastChannelsAllUp(true);
}
// ---------------------------------------------------------------------------

void pnlCustomer::btnDLTXFChan_BClick(wxCommandEvent& event)
{
//	setFastChan(false);
  cmbDLTXChan->SetSelection(0);
	if(sendChanges) LMAL_MainSetDLTXChannel(cmbDLTXChan->GetSelection());
	updateFrequency(false);
}
// ---------------------------------------------------------------------------
void pnlCustomer::btnULRXFChan_BClick(wxCommandEvent& event)
{
//	setFastChan(true);
  cmbULRXChan->SetSelection(0);
	if(sendChanges) LMAL_MainSetULRXChannel(cmbULRXChan->GetSelection());
	updateFrequency(true);

}
//---------------------------------------------------------------------------

void pnlCustomer::btnDLTXFChan_MClick(wxCommandEvent& event)
{
  cmbDLTXChan->SetSelection(cmbDLTXChan->GetCount()/2);
	if(sendChanges) LMAL_MainSetDLTXChannel(cmbDLTXChan->GetSelection());
	updateFrequency(false);
}

void pnlCustomer::btnDLTXFChan_TClick(wxCommandEvent& event)
{
  cmbDLTXChan->SetSelection(cmbDLTXChan->GetCount()-1);
	if(sendChanges) LMAL_MainSetDLTXChannel(cmbDLTXChan->GetSelection());
	updateFrequency(false);
}

void pnlCustomer::btnULRXFChan_MClick(wxCommandEvent& event)
{
  cmbULRXChan->SetSelection(cmbULRXChan->GetCount()/2);
	if(sendChanges) LMAL_MainSetULRXChannel(cmbULRXChan->GetSelection());
	updateFrequency(true);
}

void pnlCustomer::btnULRXFChan_TClick(wxCommandEvent& event)
{
  cmbULRXChan->SetSelection(cmbULRXChan->GetCount()-1);
	if(sendChanges) LMAL_MainSetULRXChannel(cmbULRXChan->GetSelection());
	updateFrequency(true);

}


// ---------------------------------------------------------------------------
void pnlCustomer::SetGuiDefaults()
{
    Freeze();
	int itmp;
	sendChanges = false;

	// LNASEL_RXFE[1:0]
	wxString cs_LNASEL[4] = {"Disabled", "LNA 1", "LNA 2", "LNA 3"};
	cmbLNASEL_Cust->Clear();
	cmbLNASEL_Cust->Append(4, cs_LNASEL);
	cmbLNASEL_Cust->SetSelection(1);

	cmbBypass->SetSelection(0);
	cmbTxBypass->SetSelection(0);
	cmbLoopback->SetSelection(0);

	SetGuiDecode();

	cmbDLTXBands->SetSelection(0);
	cmbULRXBands->SetSelection(0);
	cmbDLTXChan->SetSelection(0);
	cmbULRXChan->SetSelection(0);

	sendChanges = true;
	Thaw();
};

void pnlCustomer::Initialize()
{
	setupBands(false);
	setupBands(true);
	setupChannels(false);
	setupChannels(true);
	SetGuiDefaults();
};

void pnlCustomer::setupBands(bool ULRX)
{
	wxComboBox *cmbBands;
	wxTextCtrl *txtFreq;
	int numOfBands = 15;
	char **bands;
	bands = new char*[numOfBands];
	for(int i=0; i<numOfBands; i++)
		bands[i] = new char[100];

	int count = 0;

	if (ULRX)
	{
		cmbBands = cmbULRXBands;
		txtFreq = txtULRXFreq;
		LMAL_MainGetULRXBands(bands, count);
	}
	else
	{
		cmbBands = cmbDLTXBands;
		txtFreq = txtDLTXFreq;
		LMAL_MainGetDLTXBands(bands, count);
	}

	cmbBands->Clear();
	vector<wxString> vBands;
	for (int i = 0; i < count; i++)
	{
		vBands.push_back(bands[i]);
	}
	cmbBands->Append(count, &vBands[0]);
	for(int i=0; i<numOfBands; i++)
		delete []bands[i];
	delete []bands;
}

void pnlCustomer::setupChannels(bool ULRX)
{
	wxComboBox *cmbChannels;
	wxTextCtrl *txtFreq;

	int numOfChan = 1000;
	char **channels;
	channels = new char*[numOfChan];
	for(int i=0; i<numOfChan; i++)
		channels[i] = new char[100];
	int count = 0;

	if (ULRX)
	{
		cmbChannels = cmbULRXChan;
		txtFreq = txtULRXFreq;
		LMAL_MainGetULRXChannels(channels, count);
	}
	else
	{
		cmbChannels = cmbDLTXChan;
		txtFreq = txtDLTXFreq;
		LMAL_MainGetDLTXChannels(channels, count);
	}

	cmbChannels->Clear();
	vector<wxString> vChannels;
	for (int i = 0; i < count; i++)
	{
		vChannels.push_back(channels[i]);
	}
	cmbChannels->Append( count, &vChannels[0]);
	for(int i=0; i<numOfChan; i++)
		delete []channels[i];
	delete []channels;

	cmbChannels->SetSelection( 0);
	updateFrequency(ULRX);
}

void pnlCustomer::updateFrequency(bool ULRX)
{
	if (ULRX)
	{
		txtULRXFreq->SetValue( wxString::Format( "%g",LMAL_MainGetULRXFreq()));
	}
	else
	{
		txtDLTXFreq->SetValue( wxString::Format( "%g",LMAL_MainGetDLTXFreq()));
	}
}



