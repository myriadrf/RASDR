// -----------------------------------------------------------------------------
// FILE:        "PopSetupRSS.h"
// DESCRIPTION: "Header File"
// DATE:        "06/26/2016 00:00 AM "
// AUTHOR(s):   Lime Microsystems, Paul L. Oxley
// Copyright:   Society of Amateur Radio Astronomers (2014-2016)
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
#ifndef POPSETUPRSS_H
#define POPSETUPRSS_H

//(*Headers(PopSetupRSS)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
//*)

class PopSetupRSS: public wxDialog
{
	public:

		PopSetupRSS(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~PopSetupRSS();

		//(*Declarations(PopSetupRSS)
		wxButton* OKButton;
		wxCheckBox* Enable;
		wxStaticText* StaticText1;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText2;
		wxTextCtrl* TextCtrl2;
		wxStaticText* StaticText3;
		wxSpinCtrl* Channels;
		//*)

	protected:

		//(*Identifiers(PopSetupRSS)
		static const long ID_BUTTON1;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL1;
		//*)

	private:

		//(*Handlers(PopSetupRSS)
		void OnInit(wxInitDialogEvent& event);
		void OnOKButtonClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
