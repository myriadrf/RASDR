// -----------------------------------------------------------------------------
// FILE:        "pnlTxLPF.h"
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
#ifndef PNLTXLPF_H
#define PNLTXLPF_H

//(*Headers(pnlTxLPF)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxStaticLine;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxBoxSizer;
class wxButton;
class wxStaticBoxSizer;
//*)
class pnlADDC;

class pnlTxLPF: public wxPanel
{
	public:

		pnlTxLPF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles = 0, wxString idname="");
		virtual ~pnlTxLPF();

        void FillComboBoxes();
        void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize(pnlADDC *ADDC);
        bool UpdateGUI();
        void UpdateVerRevMask(char Ver, char Rev, char Mask);

		//(*Declarations(pnlTxLPF)
		wxCheckBox* chbPwrDCDac;
		wxRadioBox* rgrDecode;
		wxButton* btnDCStartClbr;
		wxStaticText* StaticText2;
		wxCheckBox* chbPwrDCRef;
		wxStaticText* StaticText6;
		wxComboBox* cmbDCCalAddr;
		wxStaticText* StaticText8;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxRadioBox* rgrLpfByp;
		wxComboBox* cmbLpfBw;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* btnDCRstClbr;
		wxStaticLine* StaticLine1;
		wxComboBox* cmbDCOffset;
		wxStaticText* lblDC_LOCK;
		wxButton* btnDCLoadVal;
		wxCheckBox* chbPwrLpfMods;
		wxComboBox* cmbCalVal;
		wxButton* btnDCReadVal;
		wxStaticText* lblDC_CLBR_DONE;
		wxStaticText* lbDC_REGVAL;
		wxCheckBox* chbPwrDCCmpr;
		wxStaticText* StaticText4;
		wxComboBox* cmbRcCal;
		wxStaticText* lblDC_UD;
		wxCheckBox* chbTX_DACBUF_EN;
		wxCheckBox* chbPwrLpf;
		//*)

	protected:

		//(*Identifiers(pnlTxLPF)
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
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_COMBOBOX3;
		static const long ID_RADIOBOX1;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_RADIOBOX2;
		//*)

	private:

		//(*Handlers(pnlTxLPF)
		void rgrDecodeClick(wxCommandEvent& event);
		void cmbLpfBwChange(wxCommandEvent& event);
		void cmbDCOffsetChange(wxCommandEvent& event);
		void cmbRcCalChange(wxCommandEvent& event);
		void chbPwrLpfClick(wxCommandEvent& event);
		void chbPwrDCDacClick(wxCommandEvent& event);
		void chbPwrDCRefClick(wxCommandEvent& event);
		void chbPwrDCCmprClick(wxCommandEvent& event);
		void cmbDCCalAddrChange(wxCommandEvent& event);
		void cmbCalValChange(wxCommandEvent& event);
		void btnDCRstClbrClick(wxCommandEvent& event);
		void btnDCLoadValClick(wxCommandEvent& event);
		void btnDCStartClbrClick(wxCommandEvent& event);
		void chbPwrLpfModsClick(wxCommandEvent& event);
		void rgrLpfBypClick(wxCommandEvent& event);
		void btnDCReadValClick(wxCommandEvent& event);
		void chbTX_DACBUF_ENClick(wxCommandEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

	protected:
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
		char m_cMAddr;
        pnlADDC *m_frmADDC;
        char m_cVer;
        char m_cRev;
        char m_cMask;
        bool sendChanges;

		DECLARE_EVENT_TABLE()
};

#endif
