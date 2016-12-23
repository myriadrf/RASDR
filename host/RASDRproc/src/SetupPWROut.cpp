// -----------------------------------------------------------------------------
// FILE:        "SetupPWROut.cpp"
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
#include "SetupPWROut.h"
#include "globals.h"
#include <wx/filepicker.h>
#include <wx/filedlg.h>
#include <wx/choice.h>
#include <stdio.h>

//(*InternalHeaders(SetupPWROut)
#include <wx/font.h>
#include <wx/string.h>
//*)

//(*IdInit(SetupPWROut)
const long SetupPWROut::ID_RADIOBOX1 = wxNewId();
const long SetupPWROut::ID_RADIOBOX2 = wxNewId();
const long SetupPWROut::ID_RADIOBOX3 = wxNewId();
const long SetupPWROut::ID_STATICBOX1 = wxNewId();
const long SetupPWROut::ID_FILEPICKERCTRL1 = wxNewId();
const long SetupPWROut::ID_CHECKBOX1 = wxNewId();
const long SetupPWROut::ID_STATICTEXT1 = wxNewId();
const long SetupPWROut::ID_CHOICE1 = wxNewId();
const long SetupPWROut::ID_BUTTON1 = wxNewId();
const long SetupPWROut::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SetupPWROut,wxDialog)
	//(*EventTable(SetupPWROut)
	//*)
END_EVENT_TABLE()

SetupPWROut::SetupPWROut(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SetupPWROut)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_T("Excel (Limited Size) (.csv)"),
		_T("General (.csv)")
	};
	FileType = new wxRadioBox(this, ID_RADIOBOX1, _T("FileType"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	wxFont FileTypeFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	FileType->SetFont(FileTypeFont);
	FlexGridSizer1->Add(FileType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_T("Single"),
		_T("Multiple (Suffix File Name)")
	};
	NumbFiles = new wxRadioBox(this, ID_RADIOBOX2, _T("Number of Files"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX2"));
	wxFont NumbFilesFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	NumbFiles->SetFont(NumbFilesFont);
	FlexGridSizer1->Add(NumbFiles, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_T("Local Time (i.e. EST)"),
		_T("Universal Time (UT)")
	};
	TimeStd = new wxRadioBox(this, ID_RADIOBOX3, _T("Time Standard"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX3"));
	wxFont TimeStdFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	TimeStd->SetFont(TimeStdFont);
	FlexGridSizer1->Add(TimeStd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _T("Enter File Name: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBOX1"));
	wxFont StaticBox1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticBox1->SetFont(StaticBox1Font);
	FlexGridSizer1->Add(StaticBox1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
// BUG: this prevented the user's entry from persisting in a session
// BEWARE: If you open the .wxs file, it will *REWRITE* this session with the setup of the .wxs file...
//	OutputFile = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, g_PWRfileName, wxEmptyString, _T("*.csv"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	OutputFile = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, g_PWRfileName, wxEmptyString, _T("*.csv"), wxDefaultPosition, wxDefaultSize, wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	wxFont OutputFileFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	OutputFile->SetFont(OutputFileFont);
	FlexGridSizer1->Add(OutputFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	OverwriteFile = new wxCheckBox(this, ID_CHECKBOX1, _T("Append/Overwrite File\?"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	OverwriteFile->SetValue(false);
	wxFont OverwriteFileFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	OverwriteFile->SetFont(OverwriteFileFont);
	FlexGridSizer1->Add(OverwriteFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Select The Recording Rate:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RecordRate = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxSize(150,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	RecordRate->Append(_T("Every integration"));
	RecordRate->Append(_T("Every 10 integrations"));
	RecordRate->SetSelection( RecordRate->Append(_T("Every 30 integrations")) );
	RecordRate->Append(_T("Every 60 integrations"));
	wxFont RecordRateFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	RecordRate->SetFont(RecordRateFont);
	FlexGridSizer1->Add(RecordRate, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	OK = new wxButton(this, ID_BUTTON1, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont OKFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	OK->SetFont(OKFont);
	FlexGridSizer2->Add(OK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CANCEL = new wxButton(this, ID_BUTTON2, _T("CANCEL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont CANCELFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	CANCEL->SetFont(CANCELFont);
	FlexGridSizer2->Add(CANCEL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupPWROut::OnFileTypeSelect);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupPWROut::OnNumbFilesSelect);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupPWROut::OnTimeStdSelect);
	Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SetupPWROut::OnFilePickerCtrl1FileChanged);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SetupPWROut::OnOverwriteFileClick);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SetupPWROut::OnReordRateSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupPWROut::OnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupPWROut::OnCANCELClick);
	//*)
	// Load previous configuration
	NumbFiles->SetSelection(g_NumbPWRFiles -1);
	FileType->SetSelection(g_PWRFileType);
	TimeStd->SetSelection(g_PWRTimeStandard);
	if(g_PwrRecordRate == 1) RecordRate->SetSelection(0);
	if(g_PwrRecordRate == 10) RecordRate->SetSelection(1);
	if(g_PwrRecordRate == 30) RecordRate->SetSelection(2);
	if(g_PwrRecordRate == 60) RecordRate->SetSelection(3);
}

SetupPWROut::~SetupPWROut()
{
	//(*Destroy(SetupPWROut)
	//*)
}


void SetupPWROut::OnFileTypeSelect(wxCommandEvent& event)
{
}

void SetupPWROut::OnNumbFilesSelect(wxCommandEvent& event)
{
}

void SetupPWROut::OnTimeStdSelect(wxCommandEvent& event)
{
}

void SetupPWROut::OnFilePickerCtrl1FileChanged(wxFileDirPickerEvent& event)
{
    strncpy(g_PWRfileName,OutputFile->GetPath(),1023);
}

void SetupPWROut::OnOKClick(wxCommandEvent& event)
{
    OK->Enable(false); // Disable to avoid double click

    g_NumbPWRFiles = NumbFiles -> GetSelection() + 1;
    g_PWRFileType = FileType -> GetSelection();
    g_PWRTimeStandard = TimeStd->GetSelection();
// dubious:    if(g_capturingData) g_PendingRestartCapture = true;
// NOTE: wierd.  the 'g_PWRfileSetup' appears to be used to prevent
//       the pnlSpectrum::UpdateGraphs() from making an update if set...
//       the boolean is cleared when we return from the modal dialog.
    g_PWRfileSetup = true;
    int rate = RecordRate->GetSelection();
    if(rate == 0) g_PwrRecordRate = 1;
    if(rate == 1) g_PwrRecordRate = 10;
    if(rate == 2) g_PwrRecordRate = 30;
    if(rate == 3) g_PwrRecordRate = 60;
    Destroy();
}

void SetupPWROut::OnCANCELClick(wxCommandEvent& event)
{
    Destroy();
}

void SetupPWROut::OnOverwriteFileClick(wxCommandEvent& event)
{
    g_OverwritePWRfile = true;
}

void SetupPWROut::OnReordRateSelect(wxCommandEvent& event)
{
}
