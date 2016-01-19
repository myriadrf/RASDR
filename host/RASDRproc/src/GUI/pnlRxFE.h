// -----------------------------------------------------------------------------
// FILE:        "pnlRxFE.h"
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
#ifndef PNLRXFE_H
#define PNLRXFE_H

//(*Headers(pnlRxFE)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxStaticBoxSizer;
//*)

class pnlRxFE: public wxPanel
{
	public:

		pnlRxFE(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles=0, wxString idname="");
		virtual ~pnlRxFE();

        void FillComboBoxes();
		void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();
        bool UpdateGUI();

		//(*Declarations(pnlRxFE)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxComboBox* cmbRFB_TIA_RXFE;
		wxComboBox* cmbRDLINT_LNA_RXFE;
		wxComboBox* cmbICT_TIA_RXFE;
		wxRadioBox* rgrDecode;
		wxComboBox* cmbG_FINE_LNA3_RXFE;
		wxStaticText* StaticText13;
		wxComboBox* cmbLNASEL_RXFE;
		wxStaticText* StaticText2;
		wxStaticText* StaticText14;
		wxComboBox* cmbICT_MIX_RXFE;
		wxComboBox* cmbICT_LNA_RXFE;
		wxStaticText* StaticText6;
		wxComboBox* cmbCBE_LNA_RXFE;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxCheckBox* chkINLOAD_LNA_RXFE;
		wxStaticText* StaticText3;
		wxComboBox* cmbIN1SEL_MIX_RXFE;
		wxCheckBox* chkPD_MXLOB_RXFE;
		wxComboBox* cmbDCOFF_I_RXFE;
		wxStaticText* StaticText5;
		wxComboBox* cmbLOBN_MIX_RXFE;
		wxStaticText* StaticText7;
		wxCheckBox* chkRINEN_MIX_RXFE;
		wxComboBox* cmbIP2TRIM_Q_RXFE;
		wxComboBox* cmbG_LNA_RXFE;
		wxComboBox* cmbRDLEXT_LNA_RXFE;
		wxCheckBox* chkXLOAD_LNA_RXFE;
		wxCheckBox* chkPD_LNA_RXFE;
		wxStaticText* StaticText15;
		wxComboBox* cmbCFB_TIA_RXFE;
		wxComboBox* cmbDCOFF_Q_RXFE;
		wxStaticText* StaticText12;
		wxCheckBox* chbPwrRxFeMods;
		wxCheckBox* chkPD_MIX_RXFE;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxComboBox* cmbIP2TRIM_I_RXFE;
		wxCheckBox* chkPD_TIA_RXFE;
		wxStaticText* StaticText16;
		wxComboBox* cmbICT_MXLOB_RXFE;
		//*)

	protected:

		//(*Identifiers(pnlRxFE)
		static const long ID_RADIOBOX2;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_STATICTEXT1;
		static const long ID_CHECKBOX8;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX2;
		static const long ID_COMBOBOX3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX9;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX10;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX12;
		static const long ID_COMBOBOX13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_COMBOBOX14;
		static const long ID_COMBOBOX15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX16;
		static const long ID_COMBOBOX17;
		static const long ID_COMBOBOX18;
		//*)

	private:

		//(*Handlers(pnlRxFE)
        void rgrDecodeClick(wxCommandEvent& event);
        void chbPwrRxFeModsClick(wxCommandEvent& event);
        void cmbIN1SEL_MIX_RXFEChange(wxCommandEvent& event);
        void cmbDCOFF_I_RXFEChange(wxCommandEvent& event);
        void chkINLOAD_LNA_RXFEClick(wxCommandEvent& event);
        void cmbDCOFF_Q_RXFEChange(wxCommandEvent& event);
        void chkXLOAD_LNA_RXFEClick(wxCommandEvent& event);
        void cmbIP2TRIM_I_RXFEChange(wxCommandEvent& event);
        void cmbIP2TRIM_Q_RXFEChange(wxCommandEvent& event);
        void cmbG_LNA_RXFEChange(wxCommandEvent& event);
        void cmbLNASEL_RXFEChange(wxCommandEvent& event);
        void cmbCBE_LNA_RXFEChange(wxCommandEvent& event);
        void cmbRFB_TIA_RXFEChange(wxCommandEvent& event);
        void cmbCFB_TIA_RXFEChange(wxCommandEvent& event);
        void cmbRDLEXT_LNA_RXFEChange(wxCommandEvent& event);
        void cmbRDLINT_LNA_RXFEChange(wxCommandEvent& event);
        void cmbICT_MIX_RXFEChange(wxCommandEvent& event);
        void cmbICT_LNA_RXFEChange(wxCommandEvent& event);
        void cmbICT_TIA_RXFEChange(wxCommandEvent& event);
        void cmbICT_MXLOB_RXFEChange(wxCommandEvent& event);
        void cmbLOBN_MIX_RXFEChange(wxCommandEvent& event);
        void chkPD_TIA_RXFEClick(wxCommandEvent& event);
        void chkPD_MXLOB_RXFEClick(wxCommandEvent& event);
        void chkPD_MIX_RXFEClick(wxCommandEvent& event);
        void chkPD_LNA_RXFEClick(wxCommandEvent& event);
        void chkRINEN_MIX_RXFEClick(wxCommandEvent& event);
        void cmbG_FINE_LNA3_RXFEChange(wxCommandEvent& event);
		//*)

	protected:
        char m_cMAddr;
        bool sendChanges;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
