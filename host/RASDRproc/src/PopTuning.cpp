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
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "FFTviewerMain.h"
//(*IdInit(PopTuning)
const long PopTuning::ID_BUTTON1 = wxNewId();
const long PopTuning::ID_STATICTEXT1 = wxNewId();
const long PopTuning::ID_STATICTEXT2 = wxNewId();
const long PopTuning::ID_BUTTON2 = wxNewId();
const long PopTuning::ID_TEXTCTRL1 = wxNewId();
const long PopTuning::ID_TEXTCTRL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PopTuning,wxDialog)
	//(*EventTable(PopTuning)
	//*)
END_EVENT_TABLE()

PopTuning::PopTuning(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(PopTuning)
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, _("Tuning Adjustments"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	OKButton = new wxButton(this, ID_BUTTON1, _("OK Accept Values"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	GridSizer1->Add(OKButton, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("DC Offset for I samples"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("DC Offset for Q samples"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CALButton = new wxButton(this, ID_BUTTON2, _("Use Current Averages"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	GridSizer1->Add(CALButton, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	GridSizer1->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	GridSizer1->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnOKButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnCALButtonClick);
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
	TextCtrl1->SetValue( wxString::Format("%.3f", g_DcOffsetI) );
	TextCtrl2->SetValue( wxString::Format("%.3f", g_DcOffsetQ) );
}

void PopTuning::OnCALButtonClick(wxCommandEvent& event)
{
	TextCtrl1->SetValue( wxString::Format("%.3f", g_avgI) );
	TextCtrl2->SetValue( wxString::Format("%.3f", g_avgQ) );
}

void PopTuning::OnOKButtonClick(wxCommandEvent& event)
{
    double v;
    if (TextCtrl1->GetValue().ToDouble(&v)) g_DcOffsetI = (float)v;
    if (TextCtrl2->GetValue().ToDouble(&v)) g_DcOffsetQ = (float)v;
    cout << "g_DcOffsetI=" << g_DcOffsetI << endl;
    cout << "g_DcOffsetQ=" << g_DcOffsetQ << endl;
    Destroy();
}
