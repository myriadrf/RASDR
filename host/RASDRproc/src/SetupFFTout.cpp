// -----------------------------------------------------------------------------
// FILE:        "SetupFFTout.cpp"
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
#include "SetupFFTout.h"
#include "globals.h"
#include <wx/filepicker.h>
#include <wx/filedlg.h>
#include <stdio.h>
//(*InternalHeaders(SetupFFTout)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(SetupFFTout)
const long SetupFFTout::ID_RADIOBOX1 = wxNewId();
const long SetupFFTout::ID_RADIOBOX2 = wxNewId();
const long SetupFFTout::ID_RADIOBOX3 = wxNewId();
const long SetupFFTout::ID_RADIOBOX4 = wxNewId();
const long SetupFFTout::ID_STATICTEXT1 = wxNewId();
const long SetupFFTout::ID_FILEPICKERCTRL1 = wxNewId();
const long SetupFFTout::ID_CHECKBOX1 = wxNewId();
const long SetupFFTout::ID_RADIOBUTTON1 = wxNewId();
const long SetupFFTout::ID_RADIOBUTTON2 = wxNewId();
const long SetupFFTout::ID_RADIOBUTTON3 = wxNewId();
const long SetupFFTout::ID_STATICTEXT2 = wxNewId();
const long SetupFFTout::ID_COMBOBOX1 = wxNewId();
const long SetupFFTout::ID_COMBOBOX2 = wxNewId();
const long SetupFFTout::ID_STATICTEXT3 = wxNewId();
const long SetupFFTout::ID_SPINCTRL1 = wxNewId();
const long SetupFFTout::ID_STATICTEXT4 = wxNewId();
const long SetupFFTout::ID_STATICTEXT5 = wxNewId();
const long SetupFFTout::ID_SPINCTRL2 = wxNewId();
const long SetupFFTout::ID_STATICTEXT6 = wxNewId();
const long SetupFFTout::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SetupFFTout,wxDialog)
	//(*EventTable(SetupFFTout)
	//*)
END_EVENT_TABLE()

SetupFFTout::SetupFFTout(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SetupFFTout)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Setup FFT Output"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetFocus();
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Excel (Limited Bins)"),
		_("General Comma Delimited")
	};
	FileType = new wxRadioBox(this, ID_RADIOBOX1, _("File Type"), wxDefaultPosition, wxSize(289,95), 2, __wxRadioBoxChoices_1, 1, wxRA_HORIZONTAL|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_RADIOBOX1"));
	wxFont FileTypeFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	FileType->SetFont(FileTypeFont);
	FlexGridSizer1->Add(FileType, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Single (Appended)"),
		_("Multiple (Suffix File Name)")
	};
	NumbFiles = new wxRadioBox(this, ID_RADIOBOX2, _("Number of Files"), wxDefaultPosition, wxSize(278,90), 2, __wxRadioBoxChoices_2, 1, wxRA_HORIZONTAL|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_RADIOBOX2"));
	wxFont NumbFilesFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	NumbFiles->SetFont(NumbFilesFont);
	FlexGridSizer1->Add(NumbFiles, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("Local Time (i.e. EST)"),
		_("Universal Time (UT)")
	};
	TimeStandard = new wxRadioBox(this, ID_RADIOBOX3, _("Time Standard"), wxDefaultPosition, wxSize(259,91), 2, __wxRadioBoxChoices_3, 1, wxRA_HORIZONTAL|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_RADIOBOX3"));
	wxFont TimeStandardFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	TimeStandard->SetFont(TimeStandardFont);
	FlexGridSizer1->Add(TimeStandard, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_("ALL FFT Bins"),
		_("ZOOM FFT Range Bins")
	};
	DataSource = new wxRadioBox(this, ID_RADIOBOX4, _("Data Sourcew"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 1, wxRA_HORIZONTAL|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_RADIOBOX4"));
	wxFont DataSourceFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	DataSource->SetFont(DataSourceFont);
	FlexGridSizer1->Add(DataSource, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("ENTER File Name"), wxDefaultPosition, wxSize(329,22), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
//	OutputFile = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, _T("FFTout.csv"), wxEmptyString, _T("*.csv"), wxDefaultPosition, wxDefaultSize, wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	OutputFile = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, g_FFTfileName, wxEmptyString, _T("*.csv"), wxDefaultPosition, wxDefaultSize, wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	wxFont OutputFileFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	OutputFile->SetFont(OutputFileFont);
	FlexGridSizer1->Add(OutputFile, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	OverwriteChk = new wxCheckBox(this, ID_CHECKBOX1, _("Overwrite File\?"), wxDefaultPosition, wxSize(199,26), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	OverwriteChk->SetValue(false);
	wxFont OverwriteChkFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	OverwriteChk->SetFont(OverwriteChkFont);
	FlexGridSizer1->Add(OverwriteChk, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, _("Trigger with Record Button"), wxDefaultPosition, wxSize(254,23), 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	RadioButton1->SetValue(true);
	RadioButton1->Disable();
	wxFont RadioButton1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	RadioButton1->SetFont(RadioButton1Font);
	FlexGridSizer1->Add(RadioButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButton2 = new wxRadioButton(this, ID_RADIOBUTTON2, _("Trigger Power (FUTURE)"), wxDefaultPosition, wxSize(217,28), 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	RadioButton2->Disable();
	wxFont RadioButton2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	RadioButton2->SetFont(RadioButton2Font);
	FlexGridSizer1->Add(RadioButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButton3 = new wxRadioButton(this, ID_RADIOBUTTON3, _("Trigger Time (FUTURE)"), wxDefaultPosition, wxSize(207,24), 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
	RadioButton3->Disable();
	wxFont RadioButton3Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	RadioButton3->SetFont(RadioButton3Font);
	FlexGridSizer1->Add(RadioButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Tigger On at"), wxDefaultPosition, wxSize(333,21), wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ComboBox1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	ComboBox1->Append(_("+1 dB"));
	ComboBox1->Append(_("+2 dB"));
	ComboBox1->SetSelection( ComboBox1->Append(_("+3 dB")) );
	ComboBox1->Append(_("+6 dB"));
	ComboBox1->Disable();
	wxFont ComboBox1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	ComboBox1->SetFont(ComboBox1Font);
	FlexGridSizer1->Add(ComboBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ComboBox2 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	ComboBox2->Append(_("+5 Min"));
	ComboBox2->Append(_("+10 Min"));
	ComboBox2->Append(_("+15 Min"));
	ComboBox2->SetSelection( ComboBox2->Append(_("+30 Min")) );
	ComboBox2->Append(_("+45 Min"));
	ComboBox2->Append(_("+1 Hr"));
	ComboBox2->Append(_("+2 Hr"));
	ComboBox2->Append(_("+3 Hr"));
	ComboBox2->Disable();
	wxFont ComboBox2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	ComboBox2->SetFont(ComboBox2Font);
	FlexGridSizer1->Add(ComboBox2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Record"), wxDefaultPosition, wxSize(348,29), wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FFTsToRec = new wxSpinCtrl(this, ID_SPINCTRL1, _T("64"), wxDefaultPosition, wxSize(82,21), 0, 1, 10000, 64, _T("ID_SPINCTRL1"));
	FFTsToRec->SetValue(_T("64"));
	wxFont FFTsToRecFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	FFTsToRec->SetFont(FFTsToRecFont);
	FlexGridSizer1->Add(FFTsToRec, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("TOTAL FFTs"), wxDefaultPosition, wxSize(259,24), wxALIGN_LEFT, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Every"), wxDefaultPosition, wxSize(353,25), wxALIGN_RIGHT, _T("ID_STATICTEXT5"));
	wxFont StaticText5Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText5->SetFont(StaticText5Font);
	FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FrameSkip = new wxSpinCtrl(this, ID_SPINCTRL2, _T("5"), wxDefaultPosition, wxSize(90,21), 0, 1, 1000, 5, _T("ID_SPINCTRL2"));
	FrameSkip->SetValue(_T("5"));
	wxFont FrameSkipFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	FrameSkip->SetFont(FrameSkipFont);
	FlexGridSizer1->Add(FrameSkip, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("th Frame"), wxDefaultPosition, wxSize(284,22), wxALIGN_LEFT, _T("ID_STATICTEXT6"));
	wxFont StaticText6Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText6->SetFont(StaticText6Font);
	FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FFTfileOKbtn = new wxButton(this, wxID_YES, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_YES"));
	wxFont FFTfileOKbtnFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	FFTfileOKbtn->SetFont(FFTfileOKbtnFont);
	FlexGridSizer2->Add(FFTfileOKbtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Cancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont CancelFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	Cancel->SetFont(CancelFont);
	FlexGridSizer2->Add(Cancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnFileTypeSelect);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnNumbFilesSelect);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnTimeStandardSelect);
	Connect(ID_RADIOBOX4,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnDataSourceSelect);
	Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SetupFFTout::OnOutputFileFileChanged);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnOverwriteChkClick);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SetupFFTout::OnFFTsToRecChange);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SetupFFTout::OnFrameSkipChange);
	Connect(wxID_YES,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnFFTfileOKbtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnCancelClick);
	//*)
//	FFTfileOKbtn = new wxButton(this,wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, wxDefaultValidator, _T("ID_BUTTON2"));
//	FFTfileOKbtn = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FFTOKBUTTON"));
    NumbFiles->SetSelection(g_NumbFFTFiles-1);
    FileType->SetSelection(g_FFTFileType);
    TimeStandard->SetSelection(g_FFT_TimeStandard);
    FrameSkip->SetValue(g_FFTframeSkip);
    FFTsToRec->SetValue(g_FFTframesOut);
    DataSource->SetSelection(g_FFTDataSource);
//    OutputFile->SetPath(g_FFTfileName);
}

SetupFFTout::~SetupFFTout()
{
	//(*Destroy(SetupFFTout)
	//*)
}

void SetupFFTout::OnFileSelected(wxFileDirPickerEvent& event)
{
}

void SetupFFTout::OnPwrTrigdBSelected(wxCommandEvent& event)
{
}

void SetupFFTout::OnCancelClick(wxCommandEvent& event)
{
    Destroy();
}


void SetupFFTout::OnFFTfileOKbtnClick(wxCommandEvent& event)
{
//    cout<<"event.SkipCall"<<endl;
 //   event.Skip();
    FFTfileOKbtn->Enable(false); // Avoid Double Click

    g_NumbFFTFiles = NumbFiles -> GetSelection() + 1;
    g_FFTFileType = FileType -> GetSelection();
    g_FFT_TimeStandard = TimeStandard->GetSelection();
    g_FFTDataSource = DataSource->GetSelection();
    if(g_capturingData) g_PendingRestartCapture = true;
    g_FFTfileSetup = true;
    Destroy();
}

void SetupFFTout::OnOutputFileFileChanged(wxFileDirPickerEvent& event)
{
    strncpy(g_FFTfileName,OutputFile->GetPath(),1023);
}


void SetupFFTout::OnOverwriteChkClick(wxCommandEvent& event)
{
    if(OverwriteChk->IsChecked()) g_OverwriteFFTfile = true;
    else g_OverwriteFFTfile = false;
}

void SetupFFTout::OnFrameSkipChange(wxSpinEvent& event)
{
    g_FFTframeSkip = FrameSkip->GetValue();
}

void SetupFFTout::OnFFTsToRecChange(wxSpinEvent& event)
{
    g_FFTframesOut = FFTsToRec->GetValue();
}

void SetupFFTout::OnRadioBox1Select(wxCommandEvent& event)
{
}

void SetupFFTout::OnFileTypeSelect(wxCommandEvent& event)
{
}

void SetupFFTout::OnNumbFilesSelect(wxCommandEvent& event)
{
}

void SetupFFTout::OnTimeStandardSelect(wxCommandEvent& event)
{
}

void SetupFFTout::OnDataSourceSelect(wxCommandEvent& event)
{
}
