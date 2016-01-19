// -----------------------------------------------------------------------------
// FILE:        "dlgRefClk.cpp"
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
#include "dlgRefClk.h"

#include "ctr_6002dr2_LogicDLL.h"

//(*InternalHeaders(dlgRefClk)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgRefClk)
const long dlgRefClk::ID_BUTTON1 = wxNewId();
const long dlgRefClk::ID_BUTTON2 = wxNewId();
const long dlgRefClk::ID_STATICTEXT1 = wxNewId();
const long dlgRefClk::ID_TEXTCTRL1 = wxNewId();
const long dlgRefClk::ID_BUTTON3 = wxNewId();
const long dlgRefClk::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgRefClk,wxDialog)
	//(*EventTable(dlgRefClk)
	//*)
END_EVENT_TABLE()

dlgRefClk::dlgRefClk(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgRefClk::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgRefClk)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(4, 1, 0, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	btnS01 = new wxButton(this, ID_BUTTON1, _("Set to 40 MHz"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(btnS01, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	btnS02 = new wxButton(this, ID_BUTTON2, _("Set to 32.72 MHz"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(btnS02, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Reference Frequency (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txtRefClk = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxSize(184,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(txtRefClk, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	btnOK = new wxButton(this, ID_BUTTON3, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer2->Add(btnOK, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	btnCancel = new wxButton(this, ID_BUTTON4, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer2->Add(btnCancel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRefClk::OnbtnS01Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRefClk::OnbtnS02Click);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRefClk::OnbtnOKClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRefClk::OnbtnCancelClick);
	//*)
}

dlgRefClk::~dlgRefClk()
{
	//(*Destroy(dlgRefClk)
	//*)
}


void dlgRefClk::OnbtnOKClick(wxCommandEvent& event)
{
    this->EndDialog(wxOK);
}

void dlgRefClk::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndDialog(wxCANCEL);
}

void dlgRefClk::OnbtnS01Click(wxCommandEvent& event)
{
    txtRefClk->SetValue("40");
}

void dlgRefClk::OnbtnS02Click(wxCommandEvent& event)
{
    txtRefClk->SetValue("30.72");
}

void dlgRefClk::OnbtnS01Click1(wxCommandEvent& event)
{
}

void dlgRefClk::OnInit(wxInitDialogEvent& event)
{

}
