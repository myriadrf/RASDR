// -----------------------------------------------------------------------------
// FILE:        "dlgRegTest.h"
// DESCRIPTION: "Header File"
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
#ifndef DLGREGTEST_H
#define DLGREGTEST_H

//(*Headers(dlgRegTest)
#include <wx/dialog.h>
class wxRichTextCtrl;
class wxFlexGridSizer;
class wxButton;
//*)

class dlgRegTest: public wxDialog
{
	public:

		dlgRegTest(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgRegTest();

        void AddLine(wxString Line);

		//(*Declarations(dlgRegTest)
		wxRichTextCtrl* reInfo;
		wxButton* btnClose;
		//*)

	protected:

		//(*Identifiers(dlgRegTest)
		static const long ID_RICHTEXTCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(dlgRegTest)
		void OnbtnCloseClick(wxCommandEvent& event);
		void OnbtnCloseClick1(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
