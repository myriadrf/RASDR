// -----------------------------------------------------------------------------
// FILE:        "PopList.cpp"
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
#include "PopList.h"
#include "globals.h"

//(*InternalHeaders(PopList)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "FFTviewerMain.h"
//(*IdInit(PopList)
const long PopList::ID_BUTTON1 = wxNewId();
const long PopList::ID_STATICTEXT1 = wxNewId();
const long PopList::ID_SPINCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PopList,wxDialog)
	//(*EventTable(PopList)
	//*)
END_EVENT_TABLE()

PopList::PopList(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(PopList)
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, _("FRAME DELAY"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	OKButton = new wxButton(this, ID_BUTTON1, _("OK Accept Value"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	GridSizer1->Add(OKButton, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Frame Delay (mS)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("1000"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 1000, _T("ID_SPINCTRL1"));
	SpinCtrl1->SetValue(_T("1000"));
	GridSizer1->Add(SpinCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopList::OnOKButtonClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&PopList::OnInit);
	//*)
}

PopList::~PopList()
{
    cout << "~PopList()" << endl;
	//(*Destroy(PopList)
	//*)
}

FFTviewerFrame *parent;

void PopList::OnInit(wxInitDialogEvent& event)
{
    SpinCtrl1->SetValue(g_frame_delay);
}

void PopList::OnOKButtonClick(wxCommandEvent& event)
{
    g_frame_delay = SpinCtrl1->GetValue();
    cout << g_frame_delay << endl;
    Destroy();
}
