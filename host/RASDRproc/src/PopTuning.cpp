// -----------------------------------------------------------------------------
// FILE:        "PopTuning.cpp"
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
#include "PopTuning.h"
#include "globals.h"

//(*InternalHeaders(PopTuning)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "FFTviewerMain.h"
//(*IdInit(PopTuning)
const long PopTuning::ID_TEXTCTRL3 = wxNewId();
const long PopTuning::ID_BUTTON3 = wxNewId();
const long PopTuning::ID_STATICTEXT2 = wxNewId();
const long PopTuning::ID_STATICTEXT4 = wxNewId();
const long PopTuning::ID_BUTTON2 = wxNewId();
const long PopTuning::ID_TEXTCTRL1 = wxNewId();
const long PopTuning::ID_TEXTCTRL2 = wxNewId();
const long PopTuning::ID_CHECKBOX5 = wxNewId();
const long PopTuning::ID_CHECKBOX3 = wxNewId();
const long PopTuning::ID_CHECKBOX1 = wxNewId();
const long PopTuning::ID_CHECKBOX2 = wxNewId();
const long PopTuning::ID_STATICTEXT1 = wxNewId();
const long PopTuning::ID_CHOICE1 = wxNewId();
const long PopTuning::ID_STATICTEXT3 = wxNewId();
const long PopTuning::ID_TEXTCTRL4 = wxNewId();
const long PopTuning::ID_BUTTON4 = wxNewId();
const long PopTuning::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PopTuning,wxDialog)
	//(*EventTable(PopTuning)
	//*)
END_EVENT_TABLE()

PopTuning::PopTuning(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(PopTuning)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxGridSizer* GridSizer4;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxGridSizer* GridSizer2;

	Create(parent, wxID_ANY, _("Tuning Adjustments"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	txtNotice = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	txtNotice->Disable();
	txtNotice->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	txtNotice->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	BoxSizer1->Add(txtNotice, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("DC Offset Correction"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	ZEROButton = new wxButton(this, ID_BUTTON3, _("Zero"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer1->Add(ZEROButton, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Offset for I samples"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Offset for Q samples"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	CALButton = new wxButton(this, ID_BUTTON2, _("Use Current Averages"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer1->Add(CALButton, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextDCOffsetI = new wxTextCtrl(this, ID_TEXTCTRL1, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(TextDCOffsetI, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextDCOffsetQ = new wxTextCtrl(this, ID_TEXTCTRL2, _("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer1->Add(TextDCOffsetQ, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Spectral Averaging"));
	GridSizer4 = new wxGridSizer(0, 2, 0, 0);
	chkUnlimited = new wxCheckBox(this, ID_CHECKBOX5, _("Unlimited Averaging"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkUnlimited->SetValue(false);
	chkUnlimited->Disable();
	chkUnlimited->SetToolTip(_("Choose whether to enable the *EXPERIMENTAL* unlimited averaging code.  This code uses an autoregressive (running) average to perform the spectral averaging and this allow an unlimited amount of spectral integration.\n\nThe trade off is that with unlimited averaging, the response of the spectral output is a function of the amount of averaging, and so it can be hard to understand what is happening at the receiver."));
	GridSizer4->Add(chkUnlimited, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDBFS = new wxCheckBox(this, ID_CHECKBOX3, _("Reference to ADC Full Scale"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkDBFS->SetValue(false);
	chkDBFS->Disable();
	chkDBFS->SetToolTip(_("Render spectral data relative to the ADC full scale value.  Essentially this amounts to subtracting a constant offset from each frequency point.  The value is given by:\n\n20 * log10( sqrt(2)*maxADC )\n\nWhere maxADC is (1<<(12-1))-1, or 2047 for a 12-bit signed ADC."));
	GridSizer4->Add(chkDBFS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(GridSizer4, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer3, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Spectral Background Subtraction"));
	GridSizer2 = new wxGridSizer(0, 4, 0, 0);
	chkEnable = new wxCheckBox(this, ID_CHECKBOX1, _("Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkEnable->SetValue(false);
	chkEnable->SetToolTip(_("Enable normalization of power spectrum output.  When this is enabled, a snapshot of the spectrum is taken when the \'SetPWRRef\' button is set on the main GUI.  From that point onward, all spectra to be averaged are first subtracted from this spectrum."));
	GridSizer2->Add(chkEnable, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDisplay = new wxCheckBox(this, ID_CHECKBOX2, _("Display"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkDisplay->SetValue(false);
	chkDisplay->SetToolTip(_("Choose whether to display the waveform of the background spectrum overlaid with the active spectrum or not."));
	GridSizer2->Add(chkDisplay, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(GridSizer2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 4, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Method:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	choiceMethod = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	choiceMethod->Append(_("Mean"));
	choiceMethod->Append(_("Median"));
	choiceMethod->Append(_("Histogram"));
	choiceMethod->Append(_("Vector"));
	choiceMethod->SetToolTip(_("This controls the method used to compute the background level (scalar or vector).  The following choices are implemented:\n\nMean:  Compute the mean value across all frequency bins (scalar).\nMedian: Compute the median value and use that (scalar).\nHistogram:  Compute a histogram of values and select the most common value (scalar).\nVector: Use the integrated spectrum as the background level directly (vector)."));
	FlexGridSizer2->Add(choiceMethod, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Integration Gain:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextIntegrationGain = new wxTextCtrl(this, ID_TEXTCTRL4, _("1.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	TextIntegrationGain->SetToolTip(_("Apply an amount of gain to each frequency value prior to accumulating."));
	FlexGridSizer2->Add(TextIntegrationGain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	btnReference = new wxButton(this, ID_BUTTON4, _("Reset Reference"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticBoxSizer2->Add(btnReference, 0, wxALL|wxFIXED_MINSIZE|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	OKButton = new wxButton(this, ID_BUTTON1, _("Accept values and close dialog"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(OKButton, 0, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnZEROButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnCALButtonClick);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PopTuning::OnTextDCOffsetITextEnter);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PopTuning::OnTextDCOffsetQTextEnter);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PopTuning::OnBackgroundChkButtonClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PopTuning::OnBackgroundChkButtonClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PopTuning::OnBackgroundChkButtonClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PopTuning::OnBackgroundChkButtonClick);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&PopTuning::OnchoiceMethodSelect);
	Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PopTuning::OnTextIntegrationGainEnter);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnbtnReferenceClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PopTuning::OnOKButtonClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&PopTuning::OnInit);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PopTuning::OnClose);
	//*)
}

void PopTuning::OnInit(wxInitDialogEvent& event)
{
    // DC offset correction
    TextDCOffsetI->SetValue( wxString::Format("%.3f", g_DcOffsetI) );
    TextDCOffsetQ->SetValue( wxString::Format("%.3f", g_DcOffsetQ) );
    TextDCOffsetI->Enable(g_AutoDCOffset ? false : true);
    TextDCOffsetQ->Enable(g_AutoDCOffset ? false : true);
    ZEROButton->Enable(g_AutoDCOffset ? false : true);
    if( g_AutoDCOffset ) txtNotice->SetValue( wxString::Format("When Auto DC Offset is set, editing offsets are disabled.  Use Current reads values.") );
    else txtNotice->SetValue( wxString::Format("Changes made to offsets take effect immediately.") );

    // background subtraction
    chkEnable->SetValue( g_backgroundDebugCfg & BACKGROUND_SUBTRACT ? true : false );
    chkDisplay->SetValue( g_backgroundDebugCfg & BACKGROUND_DISPLAY ? true : false );
    chkUnlimited->SetValue( g_UnlimitedAveraging ? true : false );
    TextIntegrationGain->SetValue( wxString::Format("%.3f", g_integrationGain) );
    switch( g_backgroundDebugCfg & 0xF0 ) { // MEAN|MEDIAN|HISTO (see globals.h)
    default:                                // 0|1|2 (see PopTuning.wxs)
    case BACKGROUND_REFERENCE_MEAN: choiceMethod->SetSelection(0); break;
    case BACKGROUND_REFERENCE_MEDIAN: choiceMethod->SetSelection(1); break;
    case BACKGROUND_REFERENCE_HISTO: choiceMethod->SetSelection(2); break;
    case BACKGROUND_REFERENCE_VECTOR: choiceMethod->SetSelection(3); break;
    }
    btnReference->SetLabel( g_PwrRefIsSet ? "Reset Reference" : "Set Reference" );
    old_PwrRefIsSet = g_PwrRefIsSet;
    chkDisplay->Enable( g_PwrRefIsSet ? false : true );
}

void PopTuning::OnCALButtonClick(wxCommandEvent& event)
{
	g_DcOffsetI = g_avgI;
	g_DcOffsetQ = g_avgQ;
	TextDCOffsetI->SetValue( wxString::Format("%.3f", g_DcOffsetI) );
	TextDCOffsetQ->SetValue( wxString::Format("%.3f", g_DcOffsetQ) );
}

void PopTuning::OnOKButtonClick(wxCommandEvent& event)
{
    double v;
    if (TextDCOffsetI->GetValue().ToDouble(&v)) g_DcOffsetI = (float)v;
    if (TextDCOffsetQ->GetValue().ToDouble(&v)) g_DcOffsetQ = (float)v;
    //cout << "g_DcOffsetI=" << g_DcOffsetI << endl;
    //cout << "g_DcOffsetQ=" << g_DcOffsetQ << endl;
    if( old_PwrRefIsSet != g_PwrRefIsSet )
    {
        if( g_PwrRefIsSet ) // was OFF, is now ON, so turn it OFF
        {
            g_PwrRefIsSet = false;
            g_PwrRefOffset = 0.0;
            g_PwrAccum = 0.0;
        }
        else                // was ON, is now OFF, so turn it back ON...
        {
            g_PwrRefIsSet = true;
            g_PwrRefOffset = g_framepwr;
        }
    }
    Destroy();
}

void PopTuning::OnZEROButtonClick(wxCommandEvent& event)
{
    TextDCOffsetI->SetValue( wxString::Format("%.3f", 0.0) );
    TextDCOffsetQ->SetValue( wxString::Format("%.3f", 0.0) );
    g_DcOffsetI = (float)0.0;
    g_DcOffsetQ = (float)0.0;
}

void PopTuning::OnTextDCOffsetITextEnter(wxCommandEvent& event)
{
    double v;
    if (TextDCOffsetI->GetValue().ToDouble(&v)) g_DcOffsetI = (float)v;
}

void PopTuning::OnTextDCOffsetQTextEnter(wxCommandEvent& event)
{
    double v;
    if (TextDCOffsetQ->GetValue().ToDouble(&v)) g_DcOffsetQ = (float)v;
}

void PopTuning::OnBackgroundChkButtonClick(wxCommandEvent& event)
{
    int code = g_backgroundDebugCfg & 0xFC;     // clear SUBTRACT|DISPLAY (see globals.h)
    if ( chkEnable->IsChecked() )   code |= BACKGROUND_SUBTRACT;
    if ( chkDisplay->IsChecked() )  code |= BACKGROUND_DISPLAY;
    g_backgroundDebugCfg = code;
    g_UnlimitedAveraging = (int)chkUnlimited->IsChecked()?1:0;
}

void PopTuning::OnTextIntegrationGainEnter(wxCommandEvent& event)
{
    double v;
    if (TextIntegrationGain->GetValue().ToDouble(&v)) g_integrationGain = (float)v;
}

void PopTuning::OnchoiceMethodSelect(wxCommandEvent& event)
{
    int code = g_backgroundDebugCfg & 0x0F;     // clear MEAN|MEDIAN|HISTO|VECTOR (see globals.h)
    switch( choiceMethod->GetSelection() ) {    // 0|1|2 (see PopTuning.wxs)
    case 0: code |= BACKGROUND_REFERENCE_MEAN; break;
    case 1: code |= BACKGROUND_REFERENCE_MEDIAN; break;
    case 2: code |= BACKGROUND_REFERENCE_HISTO; break;
    case 3: code |= BACKGROUND_REFERENCE_VECTOR; break;
    default:
        code = g_backgroundDebugCfg;            // change nothing
        break;
    }
    g_backgroundDebugCfg = code;
}

void PopTuning::OnbtnReferenceClick(wxCommandEvent& event)
{
    if(g_PwrRefIsSet) {
        g_PwrRefIsSet = false;
        g_PwrRefOffset = 0.0;
        g_PwrAccum = 0.0;
        btnReference->SetLabel("Set Reference");
    } else {
        g_PwrRefIsSet = true;
        g_PwrRefOffset = g_framepwr;
        btnReference->SetLabel("Reset Reference");
    }
    chkDisplay->Enable( g_PwrRefIsSet ? false : true );
}

void PopTuning::OnClose(wxCloseEvent& event)
{
    if( old_PwrRefIsSet != g_PwrRefIsSet )
    {
        if( g_PwrRefIsSet ) // was OFF, is now ON, so turn it OFF
        {
            g_PwrRefIsSet = false;
            g_PwrRefOffset = 0.0;
            g_PwrAccum = 0.0;
        }
        else                // was ON, is now OFF, so turn it back ON...
        {
            g_PwrRefIsSet = true;
            g_PwrRefOffset = g_framepwr;
        }
    }
    Destroy();
}
