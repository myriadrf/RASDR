// -----------------------------------------------------------------------------
// FILE:        "dlgVcoCapLog.cpp"
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
#include "dlgVcoCapLog.h"

//(*InternalHeaders(dlgVcoCapLog)
#include <wx/richtext/richtextctrl.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgVcoCapLog)
const long dlgVcoCapLog::ID_RICHTEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgVcoCapLog,wxDialog)
	//(*EventTable(dlgVcoCapLog)
	//*)
END_EVENT_TABLE()

dlgVcoCapLog::dlgVcoCapLog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgVcoCapLog::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgVcoCapLog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(427,256));
	Move(wxDefaultPosition);
	memLogText = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, _("Text"), wxDefaultPosition, wxSize(424,256), wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
		wxRichTextAttr rchtxtAttr_1;
	//*)
}

dlgVcoCapLog::~dlgVcoCapLog()
{
	//(*Destroy(dlgVcoCapLog)
	//*)
}

void dlgVcoCapLog::AddLine(wxString Line)
{
	memLogText->AppendText(Line);
	memLogText->AppendText("\n");
};
