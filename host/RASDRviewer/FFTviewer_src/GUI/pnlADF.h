// -----------------------------------------------------------------------------
// FILE:        "pnlADF.h"
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
#ifndef PNLADF_H
#define PNLADF_H

//(*Headers(pnlADF)
#include <wx/panel.h>
class wxSpinEvent;
class wxTextCtrl;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxButton;
class wxStaticBoxSizer;
//*)

class pnlADF: public wxPanel
{
	public:

		pnlADF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles=0, wxString idname="");
		virtual ~pnlADF();

		void SetGuiDefaults();

		//(*Declarations(pnlADF)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxComboBox* cmbTC_f;
		wxRadioBox* rgrPDP_i;
		wxComboBox* cmbCS2_i;
		wxComboBox* cmbMOC_i;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxSpinCtrl* spinNCnt;
		wxStaticText* StaticText14;
		wxComboBox* cmbCS2_f;
		wxStaticText* StaticText6;
		wxComboBox* cmbLDP;
		wxStaticText* StaticText19;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		wxRadioBox* rgrPD1_f;
		wxButton* btnCalcSend;
		wxStaticText* StaticText1;
		wxRadioBox* rgrCPS_f;
		wxStaticText* StaticText3;
		wxComboBox* cmbFL_i;
		wxTextCtrl* txtFref;
		wxComboBox* cmbCS1_i;
		wxRadioBox* rgrPDP_f;
		wxSpinCtrl* spinRCnt;
		wxRadioBox* rgrCPS_i;
		wxComboBox* cmbCPG;
		wxComboBox* cmbMOC_f;
		wxRadioBox* rgrPD2_f;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxComboBox* cmbCS1_f;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxRadioBox* rgrPD1_i;
		wxStaticText* lblFcomp;
		wxComboBox* cmbTC_i;
		wxRadioBox* rgrCR_f;
		wxTextCtrl* txtFvco;
		wxStaticText* StaticText17;
		wxComboBox* cmbFL_f;
		wxStaticText* StaticText4;
		wxComboBox* cmbABW;
		wxRadioBox* rgrCR_i;
		wxStaticText* lblFvco;
		wxStaticText* StaticText16;
		wxRadioBox* rgrPD2_i;
		//*)

	protected:

		//(*Identifiers(pnlADF)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX3;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX8;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX4;
		static const long ID_RADIOBOX5;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX9;
		static const long ID_COMBOBOX10;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_COMBOBOX11;
		static const long ID_COMBOBOX12;
		static const long ID_STATICTEXT21;
		static const long ID_COMBOBOX13;
		static const long ID_RADIOBOX6;
		static const long ID_RADIOBOX7;
		static const long ID_RADIOBOX8;
		static const long ID_RADIOBOX9;
		static const long ID_RADIOBOX10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(pnlADF)
		void OnbtnCalcSendClick(wxCommandEvent& event);
		void OncmbABWSelected(wxCommandEvent& event);
		void OncmbCS1_fSelected(wxCommandEvent& event);
		void OncmbTC_fSelected(wxCommandEvent& event);
		void OnrgrCR_iSelect(wxCommandEvent& event);
		void OnrgrPD2_fSelect(wxCommandEvent& event);
		void OnrgrPD1_iSelect(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
