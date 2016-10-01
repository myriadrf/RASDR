// -----------------------------------------------------------------------------
// FILE:        "PopTuning.cpp"
// DESCRIPTION: "Source Code File"
// DATE:        "06/26/2016 00:00 AM "
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
#include "PopTuning.h"
#include "globals.h"

//(*InternalHeaders(PopTuning)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "FFTviewerMain.h"
//(*IdInit(PopTuning)
const long PopTuning::ID_TEXTCTRL3 = wxNewId();
const long PopTuning::ID_BUTTON3 = wxNewId();
const long PopTuning::ID_STATICTEXT2 = wxNewId();
const long PopTuning::ID_STATICTEXT4 = wxNewId();
const long PopTuning::ID_BUTTON2 = wxNewId();
const long PopTuning::ID_TEXTCTRL1 = wxNewId();
const long PopTuning::ID_TEXTCTRL2 = wxNewId();
const long PopTuning::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PopTuning,wxDialog)
	//(*EventTable(PopTuning)
	//*)
END_EVENT_TABLE()

PopTuning::PopTuning(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(PopTuning)
	wxGridSizer* GridSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(parent, wxID_ANY, _("Tuning Adjustments"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	txtNotice = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	txtNotice->Disable();
	txtNotice->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	txtNotice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	BoxSizer1->Add(txtNotice, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("DC Offset Correction"));
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	ZEROButton = new wxButton(this, ID_BUTTON3, _("Zero"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	GridSizer1->Add(ZEROButton, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Offset for I samples"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizer1->Add(StaticText2, 1, wxTOP|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Offset for Q samples"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	GridSizer1->Add(StaticText4, 1, wxTOP|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	CALButton = new wxButton(this, ID_BUTTON2, _("Use Current Averages"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	GridSizer1->Add(CALButton, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextDCOffsetI = new wxTextCtrl(this, ID_TEXTCTRL1, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	GridSizer1->Add(TextDCOffsetI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextDCOffsetQ = new wxTextCtrl(this, ID_TEXTCTRL2, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	GridSizer1->Add(TextDCOffsetQ, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	OKButton = new wxButton(this, ID_BUTTON1, _("Accept values and close dialog"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(OKButton, 0, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnZEROButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnCALButtonClick);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PopTuning::OnTextDCOffsetITextEnter);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PopTuning::OnTextDCOffsetQTextEnter);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnOKButtonClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&PopTuning::OnInit);
	//*)
}

PopTuning::~PopTuning()
{
//    cout << "~PopTuning()" << endl;
	//(*Destroy(PopTuning)
	//*)
}

void PopTuning::OnInit(wxInitDialogEvent& event)
{
    TextDCOffsetI->SetValue( wxString::Format("%.3f", g_DcOffsetI) );
    TextDCOffsetQ->SetValue( wxString::Format("%.3f", g_DcOffsetQ) );
    TextDCOffsetI->Enable(g_AutoDCOffset ? false : true);
    TextDCOffsetQ->Enable(g_AutoDCOffset ? false : true);
    ZEROButton->Enable(g_AutoDCOffset ? false : true);
    if( g_AutoDCOffset ) txtNotice->SetValue( wxString::Format("When Auto DC Offset is set, editing offsets are disabled.  Use Current reads values.") );
    else txtNotice->SetValue( wxString::Format("Changes made to offsets take effect immediately.") );
}

void PopTuning::OnCALButtonClick(wxCommandEvent& event)
{
	g_DcOffsetI = g_avgI;
	g_DcOffsetQ = g_avgQ;
	TextDCOffsetI->SetValue( wxString::Format("%.3f", g_DcOffsetI) );
	TextDCOffsetQ->SetValue( wxString::Format("%.3f", g_DcOffsetQ) );
}

void PopTuning::OnOKButtonClick(wxCommandEvent& event)
{
    double v;
    if (TextDCOffsetI->GetValue().ToDouble(&v)) g_DcOffsetI = (float)v;
    if (TextDCOffsetQ->GetValue().ToDouble(&v)) g_DcOffsetQ = (float)v;
    //cout << "g_DcOffsetI=" << g_DcOffsetI << endl;
    //cout << "g_DcOffsetQ=" << g_DcOffsetQ << endl;
    Destroy();
}

void PopTuning::OnZEROButtonClick(wxCommandEvent& event)
{
    TextDCOffsetI->SetValue( wxString::Format("%.3f", 0.0) );
    TextDCOffsetQ->SetValue( wxString::Format("%.3f", 0.0) );
    g_DcOffsetI = (float)0.0;
    g_DcOffsetQ = (float)0.0;
}

void PopTuning::OnTextDCOffsetITextEnter(wxCommandEvent& event)
{
    double v;
    if (TextDCOffsetI->GetValue().ToDouble(&v)) g_DcOffsetI = (float)v;
}

void PopTuning::OnTextDCOffsetQTextEnter(wxCommandEvent& event)
{
    double v;
    if (TextDCOffsetQ->GetValue().ToDouble(&v)) g_DcOffsetQ = (float)v;
}
