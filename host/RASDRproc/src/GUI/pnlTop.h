// -----------------------------------------------------------------------------
// FILE:        "pnlTop.h"
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
#ifndef PNLTOP_H
#define PNLTOP_H

//(*Headers(pnlTop)
#include <wx/panel.h>
class wxStaticBox;
class wxCheckBox;
class wxComboBox;
class wxStaticLine;
class wxRadioBox;
class wxStaticText;
class wxToggleButton;
class wxFlexGridSizer;
class wxBoxSizer;
class wxButton;
class wxStaticBoxSizer;
class wxCheckListBox;
//*)

class pnlTop: public wxPanel
{
	public:

		pnlTop(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles = 0, wxString idname="");
		virtual ~pnlTop();

        void FillComboBoxes();
        void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();

        bool UpdateGUI();
        void DownloadAllDCCalValues();

        /*int GetCalVal(int Addr);
        void SetCalVal(int Addr, int Val);
        void SetCalAddr(int Addr);*/
        void StartCalibration(int Addr);
        char GetCalStatus();
        void SetCalDefaults();

		//(*Declarations(pnlTop)
		wxCheckBox* chkLpfCalEn;
		wxRadioBox* rgrCLKSEL_LPFCAL;
		wxStaticText* StaticText9;
		wxCheckBox* chbPwrSoftTx;
		wxRadioBox* rgrDecode;
		wxStaticText* lblRCCAL_LPFCAL;
		wxButton* btnReadRCCALVal;
		wxRadioBox* rgrRFLB;
		wxCheckBox* chkLpfCalEnEnf;
		wxButton* btnDCStartClbr;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxComboBox* cmbDCCalAddr;
		wxCheckBox* chbPDXCOBUF;
		wxStaticText* StaticText8;
		wxCheckBox* chbPwrRfLbsw;
		wxStaticText* StaticText1;
		wxCheckBox* chbSLFBXCOBUF;
		wxStaticText* StaticText3;
		wxRadioBox* rgrBBLB;
		wxRadioBox* rgrRXOUTSW;
		wxCheckBox* chbPwrLpfCal;
		wxRadioBox* rgrDsmRst;
		wxCheckBox* chkLpfCalRst;
		wxStaticBox* StaticBox2;
		wxCheckBox* chbPwrTopMods;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxPanel* Panel7;
		wxButton* btnDCRstClbr;
		wxStaticLine* StaticLine1;
		wxCheckBox* chbBYPXCOBUF;
		wxComboBox* cmbLpfCalBw;
		wxStaticText* lblDC_LOCK;
		wxComboBox* cmbLpfCalCode;
		wxCheckBox* chbPD_CLKLPFCAL;
		wxRadioBox* rgrSpiMode;
		wxButton* btnDCLoadVal;
		wxToggleButton* swReset;
		wxCheckListBox* chbSpiClkBuf;
		wxComboBox* cmbCalVal;
		wxButton* btnDCReadVal;
		wxStaticText* lblDC_CLBR_DONE;
		wxStaticText* lbDC_REGVAL;
		wxStaticText* StaticText4;
		wxRadioBox* rgrTDDMOD;
		wxCheckBox* chbRxTestModeEn;
		wxStaticText* lblDC_UD;
		wxRadioBox* rgrFDDTDD;
		wxCheckBox* chbPwrSoftRx;
		//*)

	protected:

		//(*Identifiers(pnlTop)
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
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX4;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_RADIOBOX5;
		static const long ID_RADIOBOX6;
		static const long ID_RADIOBOX7;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKLISTBOX1;
		static const long ID_RADIOBOX8;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_STATICBOX2;
		static const long ID_STATICTEXT11;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX3;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT14;
		static const long ID_PANEL7;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_CHECKBOX9;
		static const long ID_RADIOBOX9;
		static const long ID_TOGGLEBUTTON1;
		//*)

	private:

		//(*Handlers(pnlTop)
		void rgrDecodeClick(wxCommandEvent& event);
		void rgrSpiModeClick(wxCommandEvent& event);
		void rgrDsmRstClick(wxCommandEvent& event);
		void chbRxTestModeEnClick(wxCommandEvent& event);
		void chbSpiClkBufClick(wxCommandEvent& event);
		void rgrRFLBClick(wxCommandEvent& event);
		void chkLpfCalRstClick(wxCommandEvent& event);
		void chkLpfCalEnClick(wxCommandEvent& event);
		void chkLpfCalEnEnfClick(wxCommandEvent& event);
		void cmbLpfCalCodeChange(wxCommandEvent& event);
		void cmbLpfCalBwChange(wxCommandEvent& event);
		void chbPwrTopModsClick(wxCommandEvent& event);
		void chbPwrSoftTxClick(wxCommandEvent& event);
		void chbPwrSoftRxClick(wxCommandEvent& event);
		void chbPwrLpfCalClick(wxCommandEvent& event);
		void chbPwrRfLbswClick(wxCommandEvent& event);
		void cmbDCCalAddrChange(wxCommandEvent& event);
		void cmbCalValChange(wxCommandEvent& event);
		void btnDCRstClbrClick(wxCommandEvent& event);
		void btnDCLoadValClick(wxCommandEvent& event);
		void btnDCStartClbrClick(wxCommandEvent& event);
		void btnDCReadValClick(wxCommandEvent& event);
		void rgrBBLBClick(wxCommandEvent& event);
		void rgrCLKSEL_LPFCALClick(wxCommandEvent& event);
		void chbPD_CLKLPFCALClick(wxCommandEvent& event);
		void rgrRXOUTSWClick(wxCommandEvent& event);
		void rgrFDDTDDClick(wxCommandEvent& event);
		void rgrTDDMODClick(wxCommandEvent& event);
		void chbPDXCOBUFClick(wxCommandEvent& event);
		void chbSLFBXCOBUFClick(wxCommandEvent& event);
		void chbBYPXCOBUFClick(wxCommandEvent& event);
		void btnReadRCCALValClick(wxCommandEvent& event);
		void swResetClick(wxCommandEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		void OnPaint(wxPaintEvent& event);
		//*)

        bool sendChanges;

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
