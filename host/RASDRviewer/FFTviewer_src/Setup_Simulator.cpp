// -----------------------------------------------------------------------------
// FILE:        "Setup_Simulator.cpp"
// DESCRIPTION: "Source Code File"
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
#include "Setup_Simulator.h"
#include "globals.h"

//(*InternalHeaders(Setup_Simulator)
#include <wx/font.h>
#include <wx/string.h>
//*)

//(*IdInit(Setup_Simulator)
const long Setup_Simulator::ID_STATICTEXT4 = wxNewId();
const long Setup_Simulator::ID_STATICTEXT1 = wxNewId();
const long Setup_Simulator::ID_COMBOBOX1 = wxNewId();
const long Setup_Simulator::ID_STATICTEXT2 = wxNewId();
const long Setup_Simulator::ID_COMBOBOX2 = wxNewId();
const long Setup_Simulator::ID_STATICBOX1 = wxNewId();
const long Setup_Simulator::ID_COMBOBOX3 = wxNewId();
const long Setup_Simulator::ID_STATICTEXT3 = wxNewId();
const long Setup_Simulator::ID_COMBOBOX4 = wxNewId();
const long Setup_Simulator::ID_BUTTON1 = wxNewId();
const long Setup_Simulator::ID_BUTTON2 = wxNewId();
const long Setup_Simulator::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Setup_Simulator,wxDialog)
	//(*EventTable(Setup_Simulator)
	//*)
END_EVENT_TABLE()

Setup_Simulator::Setup_Simulator(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(Setup_Simulator)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _T("SetupSimulation"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(184,160), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _T("PULSAR SIMULATION FACTORS"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(12,wxSWISS,wxFONTSTYLE_ITALIC,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _T("Dispersion Measure : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DM_Box = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	DM_Box->Append(_T("2.65"));
	DM_Box->SetSelection( DM_Box->Append(_T("26.8")) );
	DM_Box->Append(_T("50.4"));
	DM_Box->Append(_T("56.8"));
	DM_Box->Append(_T("68.0"));
	FlexGridSizer1->Add(DM_Box, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _T("Pulse Period (mS) : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Period_Box = new wxComboBox(Panel1, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	Period_Box->Append(_T("5.75"));
	Period_Box->Append(_T("33.08"));
	Period_Box->Append(_T("89.3"));
	Period_Box->SetSelection( Period_Box->Append(_T("714.5")) );
	FlexGridSizer1->Add(Period_Box, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBox1 = new wxStaticBox(Panel1, ID_STATICBOX1, _T("Duty Cycle (% On) : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBOX1"));
	wxFont StaticBox1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticBox1->SetFont(StaticBox1Font);
	FlexGridSizer1->Add(StaticBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Duty_Box = new wxComboBox(Panel1, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	Duty_Box->Append(_T("5.0"));
	Duty_Box->Append(_T("10.0"));
	Duty_Box->Append(_T("15.0"));
	Duty_Box->Append(_T("20.0"));
	Duty_Box->SetSelection( Duty_Box->Append(_T("25.0")) );
	Duty_Box->Append(_T("30.0"));
	Duty_Box->Append(_T("35.0"));
	Duty_Box->Append(_T("40.0"));
	Duty_Box->Append(_T("45.0"));
	Duty_Box->Append(_T("50.0"));
	FlexGridSizer1->Add(Duty_Box, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _T("Pulse Level Factor : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Factor_Box = new wxComboBox(Panel1, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	Factor_Box->Append(_T("0.95"));
	Factor_Box->Append(_T("0.96"));
	Factor_Box->Append(_T("0.97"));
	Factor_Box->Append(_T("0.98"));
	Factor_Box->Append(_T("0.99"));
	Factor_Box->Append(_T("1.0"));
	Factor_Box->SetSelection( Factor_Box->Append(_T("1.0001")) );
	Factor_Box->Append(_T("1.1"));
	Factor_Box->Append(_T("1.2"));
	Factor_Box->Append(_T("1.3"));
	Factor_Box->Append(_T("1.4"));
	Factor_Box->Append(_T("1.5"));
	Factor_Box->Append(_T("2.0"));
	FlexGridSizer1->Add(Factor_Box, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	OKbtn = new wxButton(Panel1, ID_BUTTON1, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont OKbtnFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	OKbtn->SetFont(OKbtnFont);
	FlexGridSizer1->Add(OKbtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Cancel_Btn = new wxButton(Panel1, ID_BUTTON2, _T("CANCEL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Cancel_BtnFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	Cancel_Btn->SetFont(Cancel_BtnFont);
	FlexGridSizer1->Add(Cancel_Btn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Setup_Simulator::OnOKbtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Setup_Simulator::OnCancel_BtnClick);
	//*)
}

Setup_Simulator::~Setup_Simulator()
{
	//(*Destroy(Setup_Simulator)
	//*)
}


void Setup_Simulator::OnOKbtnClick(wxCommandEvent& event)
{
    g_Sim_DM = atof(DM_Box->GetValue());
    g_Sim_Period = atof(Period_Box->GetValue());
    g_Sim_Duty = atof(Duty_Box->GetValue());
    g_Sim_Factor = atof(Factor_Box->GetValue());
    Destroy();
}

void Setup_Simulator::OnCancel_BtnClick(wxCommandEvent& event)
{
    Destroy();
}
