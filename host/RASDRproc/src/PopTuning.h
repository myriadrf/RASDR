// -----------------------------------------------------------------------------
// FILE:        "PopTuning.h"
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
#ifndef POPTUNING_H
#define POPTUNING_H

//(*Headers(PopTuning)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class PopTuning: public wxDialog
{
	public:

		PopTuning(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~PopTuning();

		//(*Declarations(PopTuning)
		wxTextCtrl* TextDCOffsetQ;
		wxButton* OKButton;
		wxStaticText* StaticText2;
		wxButton* CALButton;
		wxBoxSizer* BoxSizer1;
		wxTextCtrl* TextDCOffsetI;
		wxStaticText* StaticText4;
		wxButton* ZEROButton;
		wxTextCtrl* txtNotice;
		//*)

	protected:

		//(*Identifiers(PopTuning)
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT4;
		static const long ID_BUTTON2;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(PopTuning)
		void OnInit(wxInitDialogEvent& event);
		void OnCALButtonClick(wxCommandEvent& event);
		void OnOKButtonClick(wxCommandEvent& event);
		void OnZEROButtonClick(wxCommandEvent& event);
		void OnTextDCOffsetITextEnter(wxCommandEvent& event);
		void OnTextDCOffsetQTextEnter(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
