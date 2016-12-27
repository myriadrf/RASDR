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
const long PopSetupRSS::ID_STATICTEXT10 = wxNewId();
const long PopSetupRSS::ID_CHECKBOX2 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT1 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT2 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL1 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL2 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT3 = wxNewId();
const long PopSetupRSS::ID_SPINCTRL1 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT9 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL8 = wxNewId();
const long PopSetupRSS::ID_BUTTON2 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT11 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT4 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL3 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT5 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL4 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT6 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL5 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT7 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL6 = wxNewId();
const long PopSetupRSS::ID_STATICTEXT8 = wxNewId();
const long PopSetupRSS::ID_TEXTCTRL7 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PopSetupRSS,wxDialog)
	//(*EventTable(PopSetupRSS)
	//*)
END_EVENT_TABLE()

PopSetupRSS::PopSetupRSS(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(PopSetupRSS)
	wxButton* ApplyButton;
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;
	wxGridSizer* GridSizer2;

	Create(parent, wxID_ANY, _("Setup RSS Output"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	GridSizer1 = new wxGridSizer(0, 2, 0, 0);
	OKButton = new wxButton(this, ID_BUTTON1, _("Ok/Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	OKButton->SetDefault();
	OKButton->SetToolTip(_("Apply settings and restart the RSS socket server if enabled.\nNOTE: will cause a disconnect on the client."));
	GridSizer1->Add(OKButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Enable = new wxCheckBox(this, ID_CHECKBOX1, _("Enable\?"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	Enable->SetValue(false);
	Enable->SetToolTip(_("Enable or Disable the RSS socket server with the below parameters"));
	GridSizer1->Add(Enable, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("<spacer>"), wxDefaultPosition, wxDLG_UNIT(this,wxSize(-1,-1)), 0, _T("ID_STATICTEXT10"));
	StaticText10->SetMaxSize(wxDLG_UNIT(this,wxSize(-1,1)));
	StaticText10->Hide();
	GridSizer1->Add(StaticText10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Extension = new wxCheckBox(this, ID_CHECKBOX2, _("Extentions Enable\?"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	Extension->SetValue(false);
	GridSizer1->Add(Extension, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Server IP"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	IP = new wxTextCtrl(this, ID_TEXTCTRL1, _("127.0.0.1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	GridSizer1->Add(IP, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 9);
	Port = new wxTextCtrl(this, ID_TEXTCTRL2, _("8888"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	GridSizer1->Add(Port, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 9);
	ChannelsLabel = new wxStaticText(this, ID_STATICTEXT3, _("Channels (100-512)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	GridSizer1->Add(ChannelsLabel, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Channels = new wxSpinCtrl(this, ID_SPINCTRL1, _T("100"), wxDefaultPosition, wxDefaultSize, 0, 100, 512, 100, _T("ID_SPINCTRL1"));
	Channels->SetValue(_T("100"));
	GridSizer1->Add(Channels, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Frequency Offset (GHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	GridSizer1->Add(StaticText9, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FrequencyOffset = new wxTextCtrl(this, ID_TEXTCTRL8, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	GridSizer1->Add(FrequencyOffset, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Adjustments"));
	GridSizer2 = new wxGridSizer(0, 2, 0, 0);
	ApplyButton = new wxButton(this, ID_BUTTON2, _("Accept"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	ApplyButton->SetToolTip(_("Apply changes to the settings in this box only.\nNOTE: will *not* cause a disconnect on the client, just update of the values."));
	GridSizer2->Add(ApplyButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("<spacer>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticText11->Hide();
	GridSizer2->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Channel Offset"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	GridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Offset = new wxTextCtrl(this, ID_TEXTCTRL3, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	GridSizer2->Add(Offset, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Channel Gain"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	GridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Gain = new wxTextCtrl(this, ID_TEXTCTRL4, _("1.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	GridSizer2->Add(Gain, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Channel Bias"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	GridSizer2->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	Bias = new wxTextCtrl(this, ID_TEXTCTRL5, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	GridSizer2->Add(Bias, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Minimum Value (clip)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	GridSizer2->Add(StaticText7, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	MinValue = new wxTextCtrl(this, ID_TEXTCTRL6, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	GridSizer2->Add(MinValue, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Maximum Value (clip)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	GridSizer2->Add(StaticText8, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	MaxValue = new wxTextCtrl(this, ID_TEXTCTRL7, _("4095.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	GridSizer2->Add(MaxValue, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(GridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopSetupRSS::OnOKButtonClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PopSetupRSS::OnExtensionClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopSetupRSS::OnApplyButtonClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&PopSetupRSS::OnInit);
	//*)
}

#if 0 /*
PopSetupRSS::~PopSetupRSS()
{
//    cout << "~PopSetupRSS()" << endl;
	//(*Destroy(PopTuning)
	//*)
}
*/
#endif

void PopSetupRSS::OnInit(wxInitDialogEvent& event)
{
//    cout << "PopSetupRSS::OnInit()" << endl;
	IP->SetValue( wxString::Format("%s", g_RSS_IP) );
	Port->SetValue( wxString::Format("%hu", g_RSS_Port) );
	Enable->SetValue(g_RSS_Enable);
	Offset->SetValue( wxString::Format("%.6f", g_RSS_Offset) );
	Gain->SetValue( wxString::Format("%.6f", g_RSS_Gain) );
	Bias->SetValue( wxString::Format("%.6f", g_RSS_Bias) );
	MinValue->SetValue( wxString::Format("%.6f", g_RSS_MinValue) );
	MaxValue->SetValue( wxString::Format("%.6f", g_RSS_MaxValue) );
	FrequencyOffset->SetValue( wxString::Format("%.6f", g_RSS_FrequencyOffset) );
	Extension->SetValue(g_RSS_Extension);
    //OnExtensionClick();    // update labels/range for channels
    if( g_RSS_Extension ) {
        ChannelsLabel->SetLabel("Channels          ");
        Channels->SetMin(1);
        Channels->SetMax(1<<14);    // TODO: coordinate with pnlSpectrum.cpp, Packets.h, TestingModule.h/.cpp, globals.cpp and pnlSpectrum.wxs
    } else {
        ChannelsLabel->SetLabel("Channels (100-512)");
        Channels->SetMin(100);
        Channels->SetMax(512);
    }
	Channels->SetValue( g_RSS_Channels );
}

// settings that require a disconnect if changed
void PopSetupRSS::OnOKButtonClick(wxCommandEvent& event)
{
    // TODO: if the widget was a float widget, we wouldnt have to validate it
    float v;
    v = (float)atof(FrequencyOffset->GetValue());
    if( v < 0.0 )
    {
        cout << "PopSetupRSS::OnOKButtonClick minimum FrequencyOffset is 0" << endl;
        FrequencyOffset->SetValue( wxString::Format("0.0") );
        return; // do not destroy the form
    }
    g_RSS_FrequencyOffset = v;
    strncpy(g_RSS_IP,IP->GetValue(),sizeof(g_RSS_IP)-1); g_RSS_IP[sizeof(g_RSS_IP)-1] = '\0';
    g_RSS_Port = (unsigned short)atoi(Port->GetValue());
    g_RSS_Channels = Channels->GetValue();
    g_RSS_Enable = Enable->GetValue();
    g_RSS_Extension = Extension->GetValue();
    g_RSS_Offset = (float)atof(Offset->GetValue());
    g_RSS_Gain = (float)atof(Gain->GetValue());
    g_RSS_Bias = (float)atof(Bias->GetValue());
    g_RSS_MinValue = (float)atof(MinValue->GetValue());
    g_RSS_MaxValue = (float)atof(MaxValue->GetValue());
    cout << (g_RSS_Extension?"RSSx ":"RSS ") << g_RSS_Enable
         << ", CHAN " << g_RSS_Channels
         << ", FO " << g_RSS_FrequencyOffset
         << ", SERVER " << g_RSS_IP << ":" << g_RSS_Port
         << ", ChOffset " << g_RSS_Offset << ", ChGain " << g_RSS_Gain << ", ChBias " << g_RSS_Bias
         << ", ChMinValue " << g_RSS_MinValue << ", ChMaxValue " << g_RSS_MaxValue
         << endl;
    g_RSS_MustDisconnect = true;
    Destroy();
}

// settings that can change without disconnect
void PopSetupRSS::OnApplyButtonClick(wxCommandEvent& event)
{
    g_RSS_Offset = (float)atof(Offset->GetValue());
    g_RSS_Gain = (float)atof(Gain->GetValue());
    g_RSS_Bias = (float)atof(Bias->GetValue());
    g_RSS_MinValue = (float)atof(MinValue->GetValue());
    g_RSS_MaxValue = (float)atof(MaxValue->GetValue());
    cout << (g_RSS_Extension?"RSSx ":"RSS ") << g_RSS_Enable
         << ", ChOffset " << g_RSS_Offset << ", ChGain " << g_RSS_Gain << ", ChBias " << g_RSS_Bias
         << ", ChMinValue " << g_RSS_MinValue << ", ChMaxValue " << g_RSS_MaxValue
         << endl;
}

void PopSetupRSS::OnExtensionClick(wxCommandEvent& event)
{
    if( Extension->GetValue() ) {
        ChannelsLabel->SetLabel("Channels          ");
        Channels->SetMin(1);
        Channels->SetMax(1<<14);    // TODO: coordinate with pnlSpectrum.cpp, Packets.h, TestingModule.h/.cpp, globals.cpp and pnlSpectrum.wxs
    } else {
        ChannelsLabel->SetLabel("Channels (100-512)");
        Channels->SetMin(100);
        Channels->SetMax(512);
    }
}
