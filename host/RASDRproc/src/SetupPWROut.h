// -----------------------------------------------------------------------------
// FILE:        "SetupPWROut.h"
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
#ifndef SETUPPWROUT_H
#define SETUPPWROUT_H

//(*Headers(SetupPWROut)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class SetupPWROut: public wxDialog
{
	public:

		SetupPWROut(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SetupPWROut();

		//(*Declarations(SetupPWROut)
		wxRadioBox* NumbFiles;
		wxFilePickerCtrl* OutputFile;
		wxButton* OK;
		wxRadioBox* TimeStd;
		wxChoice* RecordRate;
		wxStaticText* StaticText1;
		wxStaticBox* StaticBox1;
		wxRadioBox* FileType;
		wxButton* CANCEL;
		wxCheckBox* OverwriteFile;
		//*)

	protected:

		//(*Identifiers(SetupPWROut)
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_RADIOBOX3;
		static const long ID_STATICBOX1;
		static const long ID_FILEPICKERCTRL1;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(SetupPWROut)
		void OnFileTypeSelect(wxCommandEvent& event);
		void OnNumbFilesSelect(wxCommandEvent& event);
		void OnTimeStdSelect(wxCommandEvent& event);
		void OnFilePickerCtrl1FileChanged(wxFileDirPickerEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnOKClick(wxCommandEvent& event);
		void OnCANCELClick(wxCommandEvent& event);
		void OnOverwriteFileClick(wxCommandEvent& event);
		void OnReordRateSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
