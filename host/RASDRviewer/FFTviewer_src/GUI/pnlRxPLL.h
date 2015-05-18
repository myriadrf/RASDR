// -----------------------------------------------------------------------------
// FILE:        "pnlRxPLL.h"
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
#ifndef PNLRxPLL_H
#define PNLRxPLL_H

//(*Headers(pnlRxPLL)
#include <wx/panel.h>
class wxSpinEvent;
class wxSpinButton;
class wxCheckBox;
class wxTextCtrl;
class wxNotebookEvent;
class wxComboBox;
class wxRadioBox;
class wxNotebook;
class wxStaticText;
class wxFlexGridSizer;
class wxBoxSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

#include <fstream>
#include <ostream>
using namespace std;

class pnlRxPLL: public wxPanel
{
	public:

		pnlRxPLL(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles = 0, wxString idname="");
		virtual ~pnlRxPLL();

        void FillComboBoxes();
		void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();

        bool ChipVsGui(ofstream &out, wxString Caption, bool bWrAll);
        bool UpdateGUI();

        void SetRefClk(double RefClk);
        double GetRefClk();

        void BIST_ShowState(bool State);
        void BIST_ShowSignature();

		//(*Declarations(pnlRxPLL)
		wxStaticText* StaticText10;
		wxRadioBox* rgrBCLKSEL;
		wxStaticText* StaticText9;
		wxCheckBox* chbPwrPllMods;
		wxCheckBox* chbFSTVCOBG;
		wxStaticText* StaticText20;
		wxComboBox* cmbVCOCAP;
		wxCheckBox* chbAUTOBYP;
		wxRadioBox* rgrDecode;
		wxRadioBox* rgrBINSEL;
		wxCheckBox* chkCapLog;
		wxStaticText* lblAutoTuneSatatus;
		wxComboBox* cmbBCODE;
		wxStaticText* lblDiv;
		wxNotebook* Notebook1;
		wxComboBox* cmbSELOUT;
		wxCheckBox* chkENFEEDDIV;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxCheckBox* chkOEN_TSTD_SX;
		wxStaticText* StaticText14;
		wxComboBox* cmbACODE;
		wxButton* Button1;
		wxSpinButton* CSpinButton1;
		wxStaticText* StaticText6;
		wxCheckBox* chbEN_PFD_UP;
		wxRadioBox* rgrFRANGE;
		wxStaticText* lblVTUNE_H;
		wxButton* btnClbr;
		wxStaticText* StaticText19;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxButton* btnTune;
		wxStaticText* StaticText18;
		wxButton* btnReadBISTState;
		wxButton* btnCalc;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* lblVTUNE_L;
		wxPanel* Panel6;
		wxStaticText* StaticText21;
		wxPanel* Panel3;
		wxStaticText* lblFvco8Int;
		wxStaticText* StaticText23;
		wxComboBox* cmbICHP;
		wxCheckBox* chkPOL;
		wxStaticText* lblVcoF;
		wxCheckBox* chkDITHEN;
		wxCheckBox* chkENLAMP;
		wxCheckBox* chkENLOBUF;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxRadioBox* rgrSELVCO;
		wxButton* btnReadVtune;
		wxPanel* Panel7;
		wxStaticText* lblN;
		wxStaticText* lblFvco4Int;
		wxStaticText* lblFvco16Int;
		wxPanel* Panel15;
		wxStaticText* lblFvcoInt;
		wxStaticText* lblNfrac;
		wxCheckBox* chkTRI;
		wxCheckBox* chkPD_VCOCOMP_SX;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxButton* btnChoose;
		wxPanel* Panel2;
		wxCheckBox* chbPDVCOREG;
		wxCheckBox* chbBYPVCOREG;
		wxCheckBox* chkPFDCLKP;
		wxCheckBox* chkPFDPD;
		wxRadioBox* rgrMODE;
		wxComboBox* cmbOFFDOWN;
		wxComboBox* cmbVOVCOREG;
		wxStaticText* lblBSIG;
		wxStaticText* lblFvco2Int;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxComboBox* cmbOFFUP;
		wxStaticText* lblBSTATE;
		wxStaticText* lblNint;
		wxStaticText* lblROutF;
		wxCheckBox* chkPASSEN_TSTOD_SD;
		wxComboBox* cmbDITHN;
		wxStaticText* StaticText16;
		wxTextCtrl* txtDesFreq;
		//*)

	protected:

		//(*Identifiers(pnlRxPLL)
		static const long ID_RADIOBOX1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON3;
		static const long ID_CHECKBOX3;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT3;
		static const long ID_PANEL2;
		static const long ID_STATICTEXT4;
		static const long ID_COMBOBOX2;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_PANEL3;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_CHECKBOX15;
		static const long ID_CHECKBOX16;
		static const long ID_CHECKBOX17;
		static const long ID_PANEL6;
		static const long ID_STATICTEXT33;
		static const long ID_STATICTEXT35;
		static const long ID_STATICTEXT34;
		static const long ID_COMBOBOX5;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_COMBOBOX8;
		static const long ID_CHECKBOX18;
		static const long ID_COMBOBOX9;
		static const long ID_STATICTEXT36;
		static const long ID_PANEL15;
		static const long ID_RADIOBOX2;
		static const long ID_TEXTCTRL1;
		static const long ID_SPINBUTTON1;
		static const long ID_BUTTON5;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT20;
		static const long ID_RADIOBOX3;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX3;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT24;
		static const long ID_STATICTEXT25;
		static const long ID_STATICTEXT26;
		static const long ID_STATICTEXT27;
		static const long ID_STATICTEXT28;
		static const long ID_STATICTEXT29;
		static const long ID_STATICTEXT30;
		static const long ID_STATICTEXT31;
		static const long ID_STATICTEXT32;
		static const long ID_RADIOBOX4;
		static const long ID_PANEL4;
		static const long ID_STATICTEXT37;
		static const long ID_BUTTON6;
		static const long ID_STATICTEXT38;
		static const long ID_BUTTON7;
		static const long ID_RADIOBOX5;
		static const long ID_RADIOBOX6;
		static const long ID_PANEL7;
		static const long ID_NOTEBOOK1;
		//*)

	private:

		//(*Handlers(pnlRxPLL)
		void btnCalcClick(wxCommandEvent& event);
		void chkDITHENClick(wxCommandEvent& event);
		void cmbDITHNChange(wxCommandEvent& event);
		void chbPwrPllModsClick(wxCommandEvent& event);
		void rgrDecodeClick(wxCommandEvent& event);
		void rgrMODEClick(wxCommandEvent& event);
		void rgrSELVCOClick(wxCommandEvent& event);
		void rgrFRANGEClick(wxCommandEvent& event);
		void cmbSELOUTChange(wxCommandEvent& event);
		void cmbICHPChange(wxCommandEvent& event);
		void cmbOFFUPChange(wxCommandEvent& event);
		void cmbOFFDOWNChange(wxCommandEvent& event);
		void cmbVCOCAPChange(wxCommandEvent& event);
		void cmbBCODEChange(wxCommandEvent& event);
		void cmbACODEChange(wxCommandEvent& event);
		void chkENLOBUFClick(wxCommandEvent& event);
		void chkENLAMPClick(wxCommandEvent& event);
		void chkPFDPDClick(wxCommandEvent& event);
		void chkENFEEDDIVClick(wxCommandEvent& event);
		void btnClbrClick(wxCommandEvent& event);
		void btnChooseClick(wxCommandEvent& event);
		void chkPD_VCOCOMP_SXClick(wxCommandEvent& event);
		void chkOEN_TSTD_SXClick(wxCommandEvent& event);
		void chkPASSEN_TSTOD_SDClick(wxCommandEvent& event);
		void btnReadVtuneClick(wxCommandEvent& event);
		void btnTuneClick(wxCommandEvent& event);
		void chkPFDCLKPClick(wxCommandEvent& event);
		void chkTRIClick(wxCommandEvent& event);
		void chkPOLClick(wxCommandEvent& event);
		void chbAUTOBYPClick(wxCommandEvent& event);
		void chbEN_PFD_UPClick(wxCommandEvent& event);
		void chbBYPVCOREGClick(wxCommandEvent& event);
		void chbPDVCOREGClick(wxCommandEvent& event);
		void chbFSTVCOBGClick(wxCommandEvent& event);
		void cmbVOVCOREGChange(wxCommandEvent& event);
		void rgrBCLKSELClick(wxCommandEvent& event);
		void rgrBINSELClick(wxCommandEvent& event);
		void btnReadBISTStateClick(wxCommandEvent& event);
		void Button1Click(wxCommandEvent& event);
		void btnBSTARTClick(wxCommandEvent& event);
		void txtDesFreqChange(wxCommandEvent& event);
		void CSpinButton1DownClick(wxCommandEvent& event);
		void CSpinButton1UpClick(wxCommandEvent& event);
		void OnCSpinButton1ChangeUp(wxSpinEvent& event);
		void OnCSpinButton1ChangeDown(wxSpinEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

	protected:
        char m_cMAddr;
        //TdlgFreqVsCap *dlgFreqVsCap;
        bool sendChanges;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
