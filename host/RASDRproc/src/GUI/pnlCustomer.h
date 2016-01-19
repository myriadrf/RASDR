// -----------------------------------------------------------------------------
// FILE:        "pnlCustomer.h"
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
#ifndef PNLCUSTOMER_H
#define PNLCUSTOMER_H

//(*Headers(pnlCustomer)
#include <wx/panel.h>
class wxTextCtrl;
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
class wxBoxSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

class pnlCustomer: public wxPanel
{
	public:

		pnlCustomer(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString nmb = "");
		virtual ~pnlCustomer();

        void Initialize();
        void setupBands(bool ULRX);
        void setupChannels(bool ULRX);
        void updateFrequency(bool ULRX);

		//(*Declarations(pnlCustomer)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxButton* btnULRXFChan_M;
		wxButton* btnDLTXFChan_T;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxComboBox* cmbLoopback;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxButton* btnDLTXFChan_B;
		wxStaticText* StaticText1;
		wxButton* btnULRXFChan_B;
		wxStaticText* StaticText3;
		wxComboBox* cmbDLTXChan;
		wxComboBox* cmbLNASEL_Cust;
		wxButton* btnULRXFChan_T;
		wxButton* btnDLTXFChan_M;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxComboBox* cmbDLTXBands;
		wxComboBox* cmbULRXChan;
		wxComboBox* cmbTxBypass;
		wxButton* btnClbrRx;
		wxStaticText* StaticText12;
		wxTextCtrl* txtULRXFreq;
		wxButton* btnCalLPFCore;
		wxComboBox* cmbBypass;
		wxStaticText* StaticText4;
		wxTextCtrl* txtDLTXFreq;
		wxButton* btnClbrTx;
		wxComboBox* cmbULRXBands;
		//*)

	protected:

		//(*Identifiers(pnlCustomer)
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_COMBOBOX7;
		static const long ID_COMBOBOX8;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_TEXTCTRL1;
		//*)

	private:

		//(*Handlers(pnlCustomer)
		    void cmbLNASEL_CustChange(wxCommandEvent& event);
		    void cmbBypassChange(wxCommandEvent& event);
		    void cmbTxBypassChange(wxCommandEvent& event);
		    void cmbLoopbackChange(wxCommandEvent& event);
		    void btnClbrTxClick(wxCommandEvent& event);
		    void btnClbrRxClick(wxCommandEvent& event);
		    void Button1Click(wxCommandEvent& event);
		    void btnCalRxTIAClick(wxCommandEvent& event);
		    void cmbDLTXBandsChange(wxCommandEvent& event);
		    void cmbULRXBandsChange(wxCommandEvent& event);
		    void cmbDLTXChanChange(wxCommandEvent& event);
		    void cmbULRXChanChange(wxCommandEvent& event);
		    void btnDLTXFChan_BClick(wxCommandEvent& event);
		    void btnULRXFChan_BClick(wxCommandEvent& event);
		void btnDLTXFChan_MClick(wxCommandEvent& event);
		void btnDLTXFChan_TClick(wxCommandEvent& event);
		void btnULRXFChan_MClick(wxCommandEvent& event);
		void btnULRXFChan_TClick(wxCommandEvent& event);
		//*)

	protected:
        void SetGuiDefaults();
        void SetGuiDecode();
        bool sendChanges;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
