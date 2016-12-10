// -----------------------------------------------------------------------------
// FILE:        "SetupFFTout.h"
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
#ifndef SETUPFFTOUT_H
#define SETUPFFTOUT_H

//(*Headers(SetupFFTout)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/spinctrl.h>
#include <wx/radiobut.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

class SetupFFTout: public wxDialog
{
	public:

		SetupFFTout(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SetupFFTout();

		//(*Declarations(SetupFFTout)
		wxRadioBox* NumbFiles;
		wxRadioButton* RadioButton1;
		wxRadioBox* DataSource;
		wxFilePickerCtrl* OutputFile;
		wxSpinCtrl* SpinCtrl1;
		wxStaticText* StaticText2;
		wxRadioButton* RadioButton2;
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		wxRadioBox* TimeStandard;
		wxRadioBox* FileType;
		wxSpinCtrl* FFTsToRec;
		wxComboBox* ComboBox1;
		wxStaticText* StaticText4;
		wxCheckBox* OverwriteChk;
		//*)

	protected:

		//(*Identifiers(SetupFFTout)
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX4;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX2;
		static const long ID_RADIOBUTTON2;
		static const long ID_RADIOBUTTON1;
		static const long ID_FILEPICKERCTRL1;
		static const long ID_CHECKBOX1;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(SetupFFTout)
		void OnFileSelected(wxFileDirPickerEvent& event);
		void OnPwrTrigdBSelected(wxCommandEvent& event);
		void OnCancelClick(wxCommandEvent& event);
		void OnOKbtnClick(wxCommandEvent& event);
		void OnFFTfileOKbtnClick(wxCommandEvent& event);
		//		void OnFFTfileYESbtnClick1(wxCommandEvent& event);
		void OnOutputFileFileChanged(wxFileDirPickerEvent& event);
		void OnOverwriteChkClick(wxCommandEvent& event);
		void OnFrameSkipChange(wxSpinEvent& event);
		void OnFFTsToRecChange(wxSpinEvent& event);
		void OnRadioBox1Select(wxCommandEvent& event);
		void OnFileTypeSelect(wxCommandEvent& event);
		void OnNumbFilesSelect(wxCommandEvent& event);
		void OnTimeStandardSelect(wxCommandEvent& event);
		void OnDataSourceSelect(wxCommandEvent& event);
		void OnRadioButton2Select(wxCommandEvent& event);
		void OnRadioButton2Select1(wxCommandEvent& event);
		void OnRadioButton3Select(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
