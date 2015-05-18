// -----------------------------------------------------------------------------
// FILE:        "dlgRegTest.cpp"
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
#include "dlgRegTest.h"

//(*InternalHeaders(dlgRegTest)
#include <wx/sizer.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgRegTest)
const long dlgRegTest::ID_RICHTEXTCTRL1 = wxNewId();
const long dlgRegTest::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgRegTest,wxDialog)
	//(*EventTable(dlgRegTest)
	//*)
END_EVENT_TABLE()

dlgRegTest::dlgRegTest(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgRegTest::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgRegTest)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Registers test"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(409,436));
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	reInfo = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(392,384), wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
		wxRichTextAttr rchtxtAttr_1;
	FlexGridSizer1->Add(reInfo, 0, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnClose = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRegTest::OnbtnCloseClick);
	//*)
	reInfo->Clear();
}

dlgRegTest::~dlgRegTest()
{
	//(*Destroy(dlgRegTest)
	//*)
}

void dlgRegTest::AddLine(wxString Line)
{
	reInfo->AppendText(Line);
	reInfo->AppendText("\n");
};

void dlgRegTest::OnbtnCloseClick(wxCommandEvent& event)
{
    this->EndDialog(wxOK);
}

void dlgRegTest::OnbtnCloseClick1(wxCommandEvent& event)
{
    this->EndDialog(wxOK);
}
