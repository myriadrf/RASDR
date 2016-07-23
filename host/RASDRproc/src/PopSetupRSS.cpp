// -----------------------------------------------------------------------------
// FILE:        "PopSetupRSS.cpp"
// DESCRIPTION: "Source Code File"
// DATE:        "06/26/2016 00:00 AM "
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
#include "PopSetupRSS.h"
#include "globals.h"

//(*InternalHeaders(PopSetupRSS)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "FFTviewerMain.h"
//(*IdInit(PopSetupRSS)
const long PopSetupRSS::ID_BUTTON1 = wxNewId();
const long PopSetupRSS::ID_CHECKBOX1 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT1 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL1 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT2 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL2 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT3 = wxNewId();
const long PopSetupRSS::ID_SPINCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PopSetupRSS,wxDialog)
	//(*EventTable(PopSetupRSS)
	//*)
END_EVENT_TABLE()

PopSetupRSS::PopSetupRSS(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(PopSetupRSS)
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, _("Setup RSS Output"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	GridSizer1 = new wxGridSizer(0, 2, 0, 0);
	// row 1
	OKButton = new wxButton(this, ID_BUTTON1, _("OK Accept Values"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	GridSizer1->Add(OKButton, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Enable = new wxCheckBox(this, ID_CHECKBOX1, _("Enable\?"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	Enable->SetValue(g_RSS_Enable);
	GridSizer1->Add(Enable, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    // row 2
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Server IP"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_BOTTOM, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_BOTTOM, 5);
    // row 3
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("127.0.0.1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	GridSizer1->Add(TextCtrl1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP, 5);
	TextCtrl1->SetValue( wxString::Format("%s", g_RSS_IP) );
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("8888"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	GridSizer1->Add(TextCtrl2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP, 5);
	TextCtrl2->SetValue( wxString::Format("%hu", g_RSS_Port) );
    // row 4
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Channels (100-500)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	GridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Channels = new wxSpinCtrl(this, ID_SPINCTRL1, _("100"), wxDefaultPosition, wxDefaultSize, 0, 100, 500, 100, _T("ID_SPINCTRL1"));
	Channels->SetValue(g_RSS_Channels);
	GridSizer1->Add(Channels, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    // end
	BoxSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopSetupRSS::OnOKButtonClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&PopSetupRSS::OnInit);
	//*)
}

PopSetupRSS::~PopSetupRSS()
{
    cout << "~PopSetupRSS()" << endl;
	//(*Destroy(PopTuning)
	//*)
}

void PopSetupRSS::OnInit(wxInitDialogEvent& event)
{
    cout << "PopSetupRSS::OnInit()" << endl;
	TextCtrl1->SetValue( wxString::Format("%s", g_RSS_IP) );
	TextCtrl2->SetValue( wxString::Format("%hu", g_RSS_Port) );
	Channels->SetValue( g_RSS_Channels );
	Enable->SetValue(g_RSS_Enable);
}

void PopSetupRSS::OnOKButtonClick(wxCommandEvent& event)
{
    strncpy(g_RSS_IP,TextCtrl1->GetValue(),sizeof(g_RSS_IP)-1); g_RSS_IP[sizeof(g_RSS_IP)-1] = '\0';
    g_RSS_Port = (unsigned short)atoi(TextCtrl2->GetValue());
    g_RSS_Channels = Channels->GetValue();
    g_RSS_Enable = Enable->GetValue();
    cout << "RSS " << g_RSS_Enable << ", CHAN " << g_RSS_Channels << ", SERVER " << g_RSS_IP << ":" << g_RSS_Port << endl;
    Destroy();
}
