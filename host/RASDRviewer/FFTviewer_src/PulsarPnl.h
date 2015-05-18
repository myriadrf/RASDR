// -----------------------------------------------------------------------------
// FILE:        "PulsarPnl.h"
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
#ifndef PULSARPNL_H
#define PULSARPNL_H

#include "OpenGLGraph.h"
//(*Headers(PulsarPnl)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/glcanvas.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/gauge.h>
//*)

class PulsarPnl: public wxPanel
{
	public:

		PulsarPnl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PulsarPnl();

        void StartSim();
        void SetSimClock();
        void StartPulseCapture();
        void StopSim();
        void StopPulseCapture();
        void EnableChanges();
        void DisableChanges();
        int m_mode;
        bool m_SimClockSet;

		//(*Declarations(PulsarPnl)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxPanel* Panel5;
		OpenGLGraph* ogl_DM_Display;
		OpenGLGraph* ogl_Pulse_Period;
		wxComboBox* Period_Inc;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxButton* Start_Pulse_Search;
		wxGauge* Phase_Lock_Guage;
		wxComboBox* Max_Period;
		wxStaticText* StaticText6;
		wxPanel* Panel9;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxGauge* Period_Guage;
		wxPanel* Panel8;
		wxButton* SropRecDM;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* StopRecPeriod;
		wxGauge* DM_Guage;
		wxPanel* Panel6;
		wxPanel* Panel3;
		wxComboBox* Max_DM;
		wxComboBox* Min_DM;
		wxComboBox* Int_Margin;
		wxComboBox* DM_Inc;
		wxGrid* Current_Test_Values;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxPanel* Panel7;
		wxComboBox* Min_Period;
		wxButton* RecordPeriod;
		wxRadioBox* Pulsar_Mode;
		wxStaticText* StaticText12;
		wxPanel* Panel2;
		wxGrid* Spect_Inputs;
		wxButton* Record_DM;
		wxStaticText* StaticText4;
		//*)

		PulsarPnl(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style = 0, wxString str = "");

		protected:

		//(*Identifiers(PulsarPnl)
		static const long ID_GLCANVAS1;
		static const long ID_PANEL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_PANEL2;
		static const long ID_GLCANVAS2;
		static const long ID_PANEL3;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_PANEL4;
		static const long ID_STATICTEXT1;
		static const long ID_GRID1;
		static const long ID_PANEL6;
		static const long ID_RADIOBOX1;
		static const long ID_PANEL9;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT6;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX3;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX5;
		static const long ID_BUTTON5;
		static const long ID_PANEL7;
		static const long ID_STATICTEXT2;
		static const long ID_GRID2;
		static const long ID_PANEL8;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT3;
		static const long ID_GAUGE1;
		static const long ID_STATICTEXT9;
		static const long ID_GAUGE2;
		static const long ID_STATICTEXT10;
		static const long ID_GAUGE3;
		static const long ID_PANEL5;
		//*)

	private:

		//(*Handlers(PulsarPnl)
		void Onogl_Pulse_PeriodPaint(wxPaintEvent& event);
		void OnStopRecPeriodClick(wxCommandEvent& event);
		void OnGrid2CellLeftClick(wxGridEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnSpinCtrl4Change(wxSpinEvent& event);
		void OnRadioBox1Select(wxCommandEvent& event);
		void OnPanel7Paint(wxPaintEvent& event);
		void OnComboBox1Selected(wxCommandEvent& event);
		void OnComboBox5Selected(wxCommandEvent& event);
		void OnSpect_InputsCellLeftClick(wxGridEvent& event);
		void OnStart_Pulse_SearchClick(wxCommandEvent& event);
		void OnPulsar_ModeSelect(wxCommandEvent& event);
		void OnMin_DMSelected(wxCommandEvent& event);
		void OnMax_DMSelected(wxCommandEvent& event);
		void OnInt_MarginSelected(wxCommandEvent& event);
		void OnMin_PeriodSelected(wxCommandEvent& event);
		void OnMax_PeriodSelected(wxCommandEvent& event);
		void OnDM_IncSelected(wxCommandEvent& event);
		void OnPeriod_IncSelected(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
