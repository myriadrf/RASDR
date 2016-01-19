// -----------------------------------------------------------------------------
// FILE:        "PulsarPnl.cpp"
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
#include "PulsarPnl.h"
#include "globals.h"
#include <wx/button.h>

//(*InternalHeaders(PulsarPnl)
#include <wx/font.h>
#include <wx/string.h>
//*)

//(*IdInit(PulsarPnl)
const long PulsarPnl::ID_GLCANVAS1 = wxNewId();
const long PulsarPnl::ID_PANEL1 = wxNewId();
const long PulsarPnl::ID_BUTTON1 = wxNewId();
const long PulsarPnl::ID_BUTTON2 = wxNewId();
const long PulsarPnl::ID_PANEL2 = wxNewId();
const long PulsarPnl::ID_GLCANVAS2 = wxNewId();
const long PulsarPnl::ID_PANEL3 = wxNewId();
const long PulsarPnl::ID_BUTTON3 = wxNewId();
const long PulsarPnl::ID_BUTTON4 = wxNewId();
const long PulsarPnl::ID_PANEL4 = wxNewId();
const long PulsarPnl::ID_STATICTEXT1 = wxNewId();
const long PulsarPnl::ID_GRID1 = wxNewId();
const long PulsarPnl::ID_PANEL6 = wxNewId();
const long PulsarPnl::ID_RADIOBOX1 = wxNewId();
const long PulsarPnl::ID_PANEL9 = wxNewId();
const long PulsarPnl::ID_STATICTEXT4 = wxNewId();
const long PulsarPnl::ID_STATICTEXT11 = wxNewId();
const long PulsarPnl::ID_STATICTEXT12 = wxNewId();
const long PulsarPnl::ID_STATICTEXT13 = wxNewId();
const long PulsarPnl::ID_STATICTEXT6 = wxNewId();
const long PulsarPnl::ID_COMBOBOX1 = wxNewId();
const long PulsarPnl::ID_COMBOBOX2 = wxNewId();
const long PulsarPnl::ID_COMBOBOX6 = wxNewId();
const long PulsarPnl::ID_STATICTEXT7 = wxNewId();
const long PulsarPnl::ID_COMBOBOX3 = wxNewId();
const long PulsarPnl::ID_COMBOBOX4 = wxNewId();
const long PulsarPnl::ID_COMBOBOX7 = wxNewId();
const long PulsarPnl::ID_STATICTEXT8 = wxNewId();
const long PulsarPnl::ID_COMBOBOX5 = wxNewId();
const long PulsarPnl::ID_BUTTON5 = wxNewId();
const long PulsarPnl::ID_PANEL7 = wxNewId();
const long PulsarPnl::ID_STATICTEXT2 = wxNewId();
const long PulsarPnl::ID_GRID2 = wxNewId();
const long PulsarPnl::ID_PANEL8 = wxNewId();
const long PulsarPnl::ID_STATICTEXT5 = wxNewId();
const long PulsarPnl::ID_STATICTEXT3 = wxNewId();
const long PulsarPnl::ID_GAUGE1 = wxNewId();
const long PulsarPnl::ID_STATICTEXT9 = wxNewId();
const long PulsarPnl::ID_GAUGE2 = wxNewId();
const long PulsarPnl::ID_STATICTEXT10 = wxNewId();
const long PulsarPnl::ID_GAUGE3 = wxNewId();
const long PulsarPnl::ID_PANEL5 = wxNewId();
//*)



BEGIN_EVENT_TABLE(PulsarPnl,wxPanel)
	//(*EventTable(PulsarPnl)
	//*)
END_EVENT_TABLE()

PulsarPnl::PulsarPnl(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString str)
{
	//(*Initialize(PulsarPnl)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetMinSize(wxSize(250,250));
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	int GLCanvasAttributes_1[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE,      16,
		WX_GL_STENCIL_SIZE,    0,
		0, 0 };
	ogl_DM_Display = new OpenGLGraph(Panel1, ID_GLCANVAS1, wxDefaultPosition, wxSize(1400,700), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
	FlexGridSizer2->Add(ogl_DM_Display, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel1);
	FlexGridSizer2->SetSizeHints(Panel1);
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Record_DM = new wxButton(Panel2, ID_BUTTON1, _T("RECORD DM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Record_DM->Disable();
	BoxSizer1->Add(Record_DM, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SropRecDM = new wxButton(Panel2, ID_BUTTON2, _T("Stop Recording"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	SropRecDM->Disable();
	BoxSizer1->Add(SropRecDM, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	Panel2->SetSizer(BoxSizer1);
	BoxSizer1->Fit(Panel2);
	BoxSizer1->SetSizeHints(Panel2);
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	int GLCanvasAttributes_2[] = {
		WX_GL_RGBA,
		WX_GL_DOUBLEBUFFER,
		WX_GL_DEPTH_SIZE,      16,
		WX_GL_STENCIL_SIZE,    0,
		0, 0 };
	ogl_Pulse_Period = new OpenGLGraph(Panel3, ID_GLCANVAS2, wxDefaultPosition, wxSize(1400,700), 0, _T("ID_GLCANVAS2"), GLCanvasAttributes_2);
	FlexGridSizer3->Add(ogl_Pulse_Period, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(Panel3);
	FlexGridSizer3->SetSizeHints(Panel3);
	FlexGridSizer1->Add(Panel3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	RecordPeriod = new wxButton(Panel4, ID_BUTTON3, _T("RECORD PERIOD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	RecordPeriod->Disable();
	BoxSizer2->Add(RecordPeriod, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StopRecPeriod = new wxButton(Panel4, ID_BUTTON4, _T("Stop Recording"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StopRecPeriod->Disable();
	BoxSizer2->Add(StopRecPeriod, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	Panel4->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel4);
	BoxSizer2->SetSizeHints(Panel4);
	FlexGridSizer1->Add(Panel4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel5 = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	FlexGridSizer4 = new wxFlexGridSizer(1, 5, 0, 0);
	Panel6 = new wxPanel(Panel5, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	FlexGridSizer5 = new wxFlexGridSizer(6, 1, 0, 0);
	StaticText1 = new wxStaticText(Panel6, ID_STATICTEXT1, _T("INPUT from SPECTRUM"), wxPoint(0,0), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText1->SetMinSize(wxSize(170,20));
	wxFont StaticText1Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Spect_Inputs = new wxGrid(Panel6, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	Spect_Inputs->CreateGrid(5,1);
	Spect_Inputs->Disable();
	Spect_Inputs->EnableEditing(true);
	Spect_Inputs->EnableGridLines(true);
	Spect_Inputs->SetColLabelSize(15);
	Spect_Inputs->SetRowLabelSize(100);
	Spect_Inputs->SetDefaultRowSize(16, true);
	Spect_Inputs->SetDefaultColSize(50, true);
	Spect_Inputs->SetColLabelValue(0, _T("Value"));
	Spect_Inputs->SetRowLabelValue(0, _T("Samps/Second"));
	Spect_Inputs->SetRowLabelValue(1, _T("Samps/Frame"));
	Spect_Inputs->SetRowLabelValue(2, _T("Bandwidth"));
	Spect_Inputs->SetRowLabelValue(3, _T("Gain"));
	Spect_Inputs->SetRowLabelValue(4, _T("Center Freq"));
	Spect_Inputs->SetCellValue(0, 0, _T("1"));
	Spect_Inputs->SetCellValue(1, 0, _T("2"));
	Spect_Inputs->SetCellValue(2, 0, _T("3"));
	Spect_Inputs->SetCellValue(3, 0, _T("4"));
	Spect_Inputs->SetCellValue(4, 0, _T("5"));
	Spect_Inputs->SetDefaultCellFont( Spect_Inputs->GetFont() );
	Spect_Inputs->SetDefaultCellTextColour( Spect_Inputs->GetForegroundColour() );
	FlexGridSizer5->Add(Spect_Inputs, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6->SetSizer(FlexGridSizer5);
	FlexGridSizer5->Fit(Panel6);
	FlexGridSizer5->SetSizeHints(Panel6);
	FlexGridSizer4->Add(Panel6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel9 = new wxPanel(Panel5, ID_PANEL9, wxPoint(100,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
	FlexGridSizer7 = new wxFlexGridSizer(6, 1, 0, 0);
	wxString __wxRadioBoxChoices_1[3] =
	{
		_T("Spectrum"),
		_T("Pulsar"),
		_T("Simulator")
	};
	Pulsar_Mode = new wxRadioBox(Panel9, ID_RADIOBOX1, _T("MODE"), wxDefaultPosition, wxSize(98,113), 3, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	Pulsar_Mode->SetSelection(0);
	wxFont Pulsar_ModeFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	Pulsar_Mode->SetFont(Pulsar_ModeFont);
	FlexGridSizer7->Add(Pulsar_Mode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel9->SetSizer(FlexGridSizer7);
	FlexGridSizer7->Fit(Panel9);
	FlexGridSizer7->SetSizeHints(Panel9);
	FlexGridSizer4->Add(Panel9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7 = new wxPanel(Panel5, ID_PANEL7, wxPoint(200,-1), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	FlexGridSizer10 = new wxFlexGridSizer(4, 4, 0, 0);
	StaticText4 = new wxStaticText(Panel7, ID_STATICTEXT4, _T("USER INPUT"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	FlexGridSizer10->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(Panel7, ID_STATICTEXT11, _T("MIN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	wxFont StaticText11Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText11->SetFont(StaticText11Font);
	FlexGridSizer10->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(Panel7, ID_STATICTEXT12, _T("MAX"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	wxFont StaticText12Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText12->SetFont(StaticText12Font);
	FlexGridSizer10->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(Panel7, ID_STATICTEXT13, _T("INCREMENT"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	wxFont StaticText13Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText13->SetFont(StaticText13Font);
	FlexGridSizer10->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(Panel7, ID_STATICTEXT6, _T("DM "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	wxFont StaticText6Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText6->SetFont(StaticText6Font);
	FlexGridSizer10->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Min_DM = new wxComboBox(Panel7, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	Min_DM->Append(_T("40"));
	Min_DM->Append(_T("50"));
	Min_DM->SetSelection( Min_DM->Append(_T("100")) );
	Min_DM->Append(_T("200"));
	Min_DM->Append(_T("500"));
	Min_DM->Append(_T("1000"));
	Min_DM->Disable();
	FlexGridSizer10->Add(Min_DM, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Max_DM = new wxComboBox(Panel7, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	Max_DM->Append(_T("100"));
	Max_DM->Append(_T("200"));
	Max_DM->SetSelection( Max_DM->Append(_T("300")) );
	Max_DM->Append(_T("400"));
	Max_DM->Append(_T("1200"));
	Max_DM->Append(_T("1400"));
	Max_DM->Disable();
	FlexGridSizer10->Add(Max_DM, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DM_Inc = new wxComboBox(Panel7, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	DM_Inc->Append(_T("0.1"));
	DM_Inc->SetSelection( DM_Inc->Append(_T("0.2")) );
	DM_Inc->Append(_T("0.3"));
	DM_Inc->Append(_T("0.4"));
	DM_Inc->Append(_T("0.5"));
	DM_Inc->Append(_T("1.0"));
	DM_Inc->Append(_T("2.0"));
	DM_Inc->Append(_T("10.0"));
	DM_Inc->Disable();
	FlexGridSizer10->Add(DM_Inc, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(Panel7, ID_STATICTEXT7, _T("PERIOD (mS)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	wxFont StaticText7Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText7->SetFont(StaticText7Font);
	FlexGridSizer10->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Min_Period = new wxComboBox(Panel7, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	Min_Period->Append(_T("25"));
	Min_Period->Append(_T("50"));
	Min_Period->SetSelection( Min_Period->Append(_T("70")) );
	Min_Period->Append(_T("100"));
	Min_Period->Append(_T("500"));
	Min_Period->Append(_T("1000"));
	Min_Period->Append(_T("2000"));
	Min_Period->Append(_T("5000"));
	Min_Period->Disable();
	FlexGridSizer10->Add(Min_Period, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Max_Period = new wxComboBox(Panel7, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	Max_Period->Append(_T("80"));
	Max_Period->Append(_T("100"));
	Max_Period->SetSelection( Max_Period->Append(_T("120")) );
	Max_Period->Append(_T("300"));
	Max_Period->Append(_T("500"));
	Max_Period->Append(_T("1200"));
	Max_Period->Append(_T("2000"));
	Max_Period->Append(_T("3000"));
	Max_Period->Append(_T("6000"));
	Max_Period->Disable();
	FlexGridSizer10->Add(Max_Period, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Period_Inc = new wxComboBox(Panel7, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	Period_Inc->Append(_T("0.1"));
	Period_Inc->SetSelection( Period_Inc->Append(_T("0.2")) );
	Period_Inc->Append(_T("0.3"));
	Period_Inc->Append(_T("0.5"));
	Period_Inc->Append(_T("1.0"));
	Period_Inc->Append(_T("5.0"));
	Period_Inc->Append(_T("10.0"));
	Period_Inc->Append(_T("20.0"));
	Period_Inc->Disable();
	FlexGridSizer10->Add(Period_Inc, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(Panel7, ID_STATICTEXT8, _T("MARGIN (dB)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	wxFont StaticText8Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText8->SetFont(StaticText8Font);
	FlexGridSizer10->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Int_Margin = new wxComboBox(Panel7, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	Int_Margin->Append(_T("0.01"));
	Int_Margin->Append(_T("0.05"));
	Int_Margin->SetSelection( Int_Margin->Append(_T("0.1")) );
	Int_Margin->Append(_T("0.2"));
	Int_Margin->Append(_T("0.3"));
	Int_Margin->Append(_T("0.4"));
	Int_Margin->Append(_T("0.5"));
	Int_Margin->Append(_T("1.0"));
	Int_Margin->Disable();
	FlexGridSizer10->Add(Int_Margin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Start_Pulse_Search = new wxButton(Panel7, ID_BUTTON5, _T("START Search"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	Start_Pulse_Search->Disable();
	wxFont Start_Pulse_SearchFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	Start_Pulse_Search->SetFont(Start_Pulse_SearchFont);
	FlexGridSizer10->Add(Start_Pulse_Search, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(FlexGridSizer10);
	FlexGridSizer10->Fit(Panel7);
	FlexGridSizer10->SetSizeHints(Panel7);
	FlexGridSizer4->Add(Panel7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel8 = new wxPanel(Panel5, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
	FlexGridSizer6 = new wxFlexGridSizer(6, 1, 0, 0);
	StaticText2 = new wxStaticText(Panel8, ID_STATICTEXT2, _T("Current TEST"), wxPoint(202,-1), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText2->SetMinSize(wxSize(-1,20));
	wxFont StaticText2Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	FlexGridSizer6->Add(StaticText2, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Current_Test_Values = new wxGrid(Panel8, ID_GRID2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID2"));
	Current_Test_Values->CreateGrid(3,1);
	Current_Test_Values->Disable();
	Current_Test_Values->EnableEditing(true);
	Current_Test_Values->EnableGridLines(true);
	Current_Test_Values->SetColLabelSize(15);
	Current_Test_Values->SetRowLabelSize(100);
	Current_Test_Values->SetDefaultRowSize(16, true);
	Current_Test_Values->SetDefaultColSize(50, true);
	Current_Test_Values->SetColLabelValue(0, _T("Value"));
	Current_Test_Values->SetRowLabelValue(0, _T("DM"));
	Current_Test_Values->SetRowLabelValue(1, _T("PERIOD"));
	Current_Test_Values->SetRowLabelValue(2, _T("Phase"));
	Current_Test_Values->SetDefaultCellFont( Current_Test_Values->GetFont() );
	Current_Test_Values->SetDefaultCellTextColour( Current_Test_Values->GetForegroundColour() );
	FlexGridSizer6->Add(Current_Test_Values, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel8->SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(Panel8);
	FlexGridSizer6->SetSizeHints(Panel8);
	FlexGridSizer4->Add(Panel8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(6, 2, 0, 0);
	StaticText5 = new wxStaticText(Panel5, ID_STATICTEXT5, _T("PROGRESS"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	wxFont StaticText5Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText5->SetFont(StaticText5Font);
	FlexGridSizer8->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel5, ID_STATICTEXT3, _T("DISPERSION"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	FlexGridSizer8->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DM_Guage = new wxGauge(Panel5, ID_GAUGE1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE1"));
	DM_Guage->SetValue(100);
	FlexGridSizer8->Add(DM_Guage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(Panel5, ID_STATICTEXT9, _T("PERIOD"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxFont StaticText9Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText9->SetFont(StaticText9Font);
	FlexGridSizer8->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Period_Guage = new wxGauge(Panel5, ID_GAUGE2, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE2"));
	Period_Guage->SetValue(50);
	FlexGridSizer8->Add(Period_Guage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(Panel5, ID_STATICTEXT10, _T("Phase LOCK"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxFont StaticText10Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText10->SetFont(StaticText10Font);
	FlexGridSizer8->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Phase_Lock_Guage = new wxGauge(Panel5, ID_GAUGE3, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE3"));
	FlexGridSizer8->Add(Phase_Lock_Guage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(FlexGridSizer8, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer4->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel5->SetSizer(FlexGridSizer4);
	FlexGridSizer4->Fit(Panel5);
	FlexGridSizer4->SetSizeHints(Panel5);
	FlexGridSizer1->Add(Panel5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	ogl_Pulse_Period->Connect(wxEVT_PAINT,(wxObjectEventFunction)&PulsarPnl::Onogl_Pulse_PeriodPaint,0,this);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PulsarPnl::OnStopRecPeriodClick);
	Connect(ID_GRID1,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&PulsarPnl::OnSpect_InputsCellLeftClick);
	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnPulsar_ModeSelect);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnMin_DMSelected);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PulsarPnl::OnMin_DMSelected);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnMax_DMSelected);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PulsarPnl::OnMax_DMSelected);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnDM_IncSelected);
	Connect(ID_COMBOBOX6,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PulsarPnl::OnDM_IncSelected);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnMin_PeriodSelected);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PulsarPnl::OnMin_PeriodSelected);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnMax_PeriodSelected);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PulsarPnl::OnMax_PeriodSelected);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnPeriod_IncSelected);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PulsarPnl::OnPeriod_IncSelected);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&PulsarPnl::OnInt_MarginSelected);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PulsarPnl::OnInt_MarginSelected);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PulsarPnl::OnStart_Pulse_SearchClick);
	Panel7->Connect(wxEVT_PAINT,(wxObjectEventFunction)&PulsarPnl::OnPanel7Paint,0,this);
	Connect(ID_GRID2,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&PulsarPnl::OnGrid2CellLeftClick);
	//*)
	m_mode = 0; // Default
	m_SimClockSet = false;
}

PulsarPnl::~PulsarPnl()
{
	//(*Destroy(PulsarPnl)
	//*)
}
void PulsarPnl::SetSimClock() {

    m_SimClockSet = true;
    cout << "m_SimClockSet" << endl;
}

void PulsarPnl::StartSim() {
    DisableChanges();
    if(!m_SimClockSet) SetSimClock();
    g_Pulsar_Sim_Running = true;
    cout << "Sim Started" << endl;

}
void PulsarPnl::StopSim() {
    EnableChanges();
    g_Pulsar_Sim_Running = false;
    cout << "Sim Stopped" << endl;
}
void PulsarPnl:: StartPulseCapture() {

    DisableChanges();
    g_Pulsar_Capture_Running = true;

}

void PulsarPnl::StopPulseCapture() {

    EnableChanges();
    g_Pulsar_Capture_Running = false;

}
void PulsarPnl::EnableChanges(){
    Min_DM->Enable(true);
    Max_DM->Enable(true);
    DM_Inc->Enable(true);
    Min_Period->Enable(true);
    Max_Period->Enable(true);
    Period_Inc->Enable(true);
    Int_Margin->Enable(true);
//    cout << "Changes Enabled" << endl;
}
void PulsarPnl::DisableChanges(){
    Min_DM->Enable(false);
    Max_DM->Enable(false);
    DM_Inc->Enable(false);
    Min_Period->Enable(false);
    Max_Period->Enable(false);
    Period_Inc->Enable(false);
    Int_Margin->Enable(false);

//    cout << "Changes Disabled" << endl;
}
void PulsarPnl::Onogl_Pulse_PeriodPaint(wxPaintEvent& event)
{
}

void PulsarPnl::OnStopRecPeriodClick(wxCommandEvent& event)
{
}

void PulsarPnl::OnGrid2CellLeftClick(wxGridEvent& event)
{
}

void PulsarPnl::OnCheckBox1Click(wxCommandEvent& event)
{
}

void PulsarPnl::OnSpinCtrl4Change(wxSpinEvent& event)
{
}

void PulsarPnl::OnRadioBox1Select(wxCommandEvent& event)
{
}

void PulsarPnl::OnPanel7Paint(wxPaintEvent& event)
{
}

void PulsarPnl::OnComboBox1Selected(wxCommandEvent& event)
{
}

void PulsarPnl::OnComboBox5Selected(wxCommandEvent& event)
{
}

void PulsarPnl::OnSpect_InputsCellLeftClick(wxGridEvent& event)
{
}

void PulsarPnl::OnStart_Pulse_SearchClick(wxCommandEvent& event)
{
    if(m_mode == 0) return;//Invalid Mode fdor search

    if(!g_Pulsar_Capture_Running && !g_Pulsar_Sim_Running) {
        Start_Pulse_Search -> SetLabel("STOP Reset");
        if(m_mode == 1) StartPulseCapture();
        if(m_mode == 2) StartSim();
        Pulsar_Mode -> Enable(false);
    }

    else {
        Start_Pulse_Search -> SetLabel("START Search");
        if(m_mode == 1) StopPulseCapture();
        if(m_mode == 2) StopSim();
        Pulsar_Mode -> Enable(true);
    }

}

void PulsarPnl::OnPulsar_ModeSelect(wxCommandEvent& event)
{
    m_mode = Pulsar_Mode ->GetSelection();
    if(m_mode > 0) {
            Start_Pulse_Search->Enable(true);
            EnableChanges(); }
    else {
            Start_Pulse_Search->Enable(false);
            DisableChanges(); }
    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }

}

void PulsarPnl::OnMin_DMSelected(wxCommandEvent& event)
{ //Todo add edits

    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }
    g_Min_DM_Range = atof(Min_DM -> GetValue());

}
void PulsarPnl::OnMax_DMSelected(wxCommandEvent& event)
{
    float old = g_Max_DM_Range;

    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }
    g_Max_DM_Range = atof(Max_DM -> GetValue());

    if(g_Max_DM_Range < g_Min_DM_Range) {
        g_Max_DM_Range = old;
        Max_DM -> Undo();
    }
}

void PulsarPnl::OnInt_MarginSelected(wxCommandEvent& event)
{
    float oldmargin = g_Margin;

    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }
    g_Margin = atof(Int_Margin -> GetValue());

    if(g_Margin < 0){ //Invalid

        g_Margin = oldmargin;
        Int_Margin -> Undo();

    }
}

void PulsarPnl::OnMin_PeriodSelected(wxCommandEvent& event)
{
    float old = g_Min_Period_Range;

    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }
    g_Min_Period_Range = atof(Min_Period->GetValue());

    //Todo add edits
}

void PulsarPnl::OnMax_PeriodSelected(wxCommandEvent& event)
{
    float old = g_Max_Period_Range;

    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }
    g_Max_Period_Range = atof(Max_Period->GetValue());

    if(g_Max_Period_Range < g_Min_Period_Range){
        g_Max_Period_Range = old;
        Max_Period->Undo();
    }

}

void PulsarPnl::OnDM_IncSelected(wxCommandEvent& event)
{
    float old = g_DM_Inc;

    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }
    // Todo Add Edits
    g_DM_Inc = atof(DM_Inc->GetValue());
    if(g_DM_Inc < 0) {
        g_DM_Inc = old;
        DM_Inc->Undo();
    }
}

void PulsarPnl::OnPeriod_IncSelected(wxCommandEvent& event)
{
    float old = g_Period_Inc;

    if(m_SimClockSet) {
        m_SimClockSet = false;
        cout << "m_Sim Clock Not Set" << endl;
    }
    //Todo Add Edits
    g_Period_Inc = atof(Period_Inc->GetValue());
    if(g_Period_Inc < 0) {
        g_Period_Inc = old;
        Period_Inc -> Undo();
    }
}
