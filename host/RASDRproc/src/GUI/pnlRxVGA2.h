// -----------------------------------------------------------------------------
// FILE:        "pnlRxVGA2.h"
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
#ifndef PNLRXVGA2_H
#define PNLRXVGA2_H

//(*Headers(pnlRxVGA2)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxStaticLine;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

class pnlRxVGA2: public wxPanel
{
	public:

		pnlRxVGA2(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles= 0, wxString idname="");
		virtual ~pnlRxVGA2();

        void FillComboBoxes();
        void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();
        bool UpdateGUI();

        void UpdateVerRevMask(char Ver, char Rev, char Mask);

		//(*Declarations(pnlRxVGA2)
		wxStaticText* StaticText9;
		wxRadioBox* rgrDecode;
		wxCheckBox* chbPwrBypAB;
		wxCheckBox* chbPwrBypA;
		wxButton* btnDCStartClbr;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxCheckBox* chbPwrDCCurrR;
		wxComboBox* cmbDCCalAddr;
		wxCheckBox* chbPwrBypB;
		wxStaticText* StaticText8;
		wxCheckBox* chbPwrVGA2Mods;
		wxStaticText* StaticText1;
		wxComboBox* cmbVCM;
		wxStaticText* StaticText3;
		wxCheckBox* chbPwrCurrRef;
		wxCheckBox* chbPwrDCDACB;
		wxCheckBox* chbPwrBG;
		wxCheckBox* chbPwrDCDACA;
		wxCheckBox* chbPwrDCCmpA;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* btnDCRstClbr;
		wxCheckBox* chbPwrDCCmpB;
		wxComboBox* cmbVga2G_u;
		wxComboBox* cmbVga2GB_t;
		wxStaticLine* StaticLine1;
		wxComboBox* cmbVga2GA_t;
		wxStaticText* lblDC_LOCK;
		wxButton* btnDCLoadVal;
		wxComboBox* cmbCalVal;
		wxButton* btnDCReadVal;
		wxStaticText* lblDC_CLBR_DONE;
		wxStaticText* lbDC_REGVAL;
		wxStaticText* StaticText4;
		wxStaticText* lblDC_UD;
		//*)

	protected:

		//(*Identifiers(pnlRxVGA2)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICLINE1;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_BUTTON5;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT10;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX3;
		static const long ID_STATICTEXT12;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX5;
		static const long ID_COMBOBOX6;
		static const long ID_RADIOBOX2;
		//*)

	private:

		//(*Handlers(pnlRxVGA2)
		void chbPwrVGA2ModsClick(wxCommandEvent& event);
		void rgrDecodeClick(wxCommandEvent& event);
		void cmbVga2G_uChange(wxCommandEvent& event);
		void chbPwrDCCurrRClick(wxCommandEvent& event);
		void chbPwrDCDACBClick(wxCommandEvent& event);
		void chbPwrDCCmpBClick(wxCommandEvent& event);
		void chbPwrDCDACAClick(wxCommandEvent& event);
		void chbPwrDCCmpAClick(wxCommandEvent& event);
		void chbPwrBGClick(wxCommandEvent& event);
		void chbPwrBypABClick(wxCommandEvent& event);
		void chbPwrBypBClick(wxCommandEvent& event);
		void chbPwrBypAClick(wxCommandEvent& event);
		void chbPwrCurrRefClick(wxCommandEvent& event);
		void cmbVga2GB_tChange(wxCommandEvent& event);
		void cmbVga2GA_tChange(wxCommandEvent& event);
		void cmbDCCalAddrChange(wxCommandEvent& event);
		void cmbCalValChange(wxCommandEvent& event);
		void btnDCRstClbrClick(wxCommandEvent& event);
		void btnDCLoadValClick(wxCommandEvent& event);
		void btnDCStartClbrClick(wxCommandEvent& event);
		void btnDCReadValClick(wxCommandEvent& event);
		void cmbVCMChange(wxCommandEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

	protected:
        char m_cMAddr;
        char m_cVer;
        char m_cRev;
        char m_cMask;
        bool sendChanges;

        // VCM code to combobox index recalculation
        int VCM2CMB(int code);
        int CMB2VCM(int code);
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
