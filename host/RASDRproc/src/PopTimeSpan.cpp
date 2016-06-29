// -----------------------------------------------------------------------------
// FILE:        "PopTimeSpan.cpp"
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
#include "PopTimeSpan.h"
#include "globals.h"

//(*InternalHeaders(PopTimeSpan)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PopTimeSpan)
const long PopTimeSpan::ID_BUTTON1 = wxNewId();
const long PopTimeSpan::ID_STATICTEXT1 = wxNewId();
const long PopTimeSpan::ID_SPINCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PopTimeSpan,wxDialog)
	//(*EventTable(PopTimeSpan)
	//*)
END_EVENT_TABLE()

PopTimeSpan::PopTimeSpan(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PopTimeSpan)
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, _("Tme Span"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	OKButton = new wxButton(this, ID_BUTTON1, _("OK Accept Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	GridSizer1->Add(OKButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Time Span (Min)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("30"), wxDefaultPosition, wxDefaultSize, 0, 2, 90, 30, _T("ID_SPINCTRL1"));
	SpinCtrl1->SetValue(_T("30"));
	GridSizer1->Add(SpinCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTimeSpan::OnOKButtonClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&PopTimeSpan::OnInit);
	//*)
}

PopTimeSpan::~PopTimeSpan()
{
	//(*Destroy(PopTimeSpan)
	//*)
}


void PopTimeSpan::OnInit(wxInitDialogEvent& event)
{
//    SpinCtrl1->SetValue(g_DisplayTimeSpan);
}

void PopTimeSpan::OnOKButtonClick(wxCommandEvent& event)
{
//    g_DisplayTimeSpan = SpinCtrl1->GetValue();
//    g_DisplayFrames = g_DisplayTimeSpan * g_framesPerMin;
    Destroy();
}
