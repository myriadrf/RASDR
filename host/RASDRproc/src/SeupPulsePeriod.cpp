// -----------------------------------------------------------------------------
// FILE:        "SeupPulsePeriod.cpp"
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
#include "SeupPulsePeriod.h"

//(*InternalHeaders(SeupPulsePeriod)
#include <wx/font.h>
#include <wx/string.h>
//*)

//(*IdInit(SeupPulsePeriod)
const long SeupPulsePeriod::ID_RADIOBOX1 = wxNewId();
const long SeupPulsePeriod::ID_RADIOBOX2 = wxNewId();
const long SeupPulsePeriod::ID_RADIOBOX3 = wxNewId();
const long SeupPulsePeriod::ID_STATICTEXT1 = wxNewId();
const long SeupPulsePeriod::ID_FILEPICKERCTRL1 = wxNewId();
const long SeupPulsePeriod::ID_CHECKBOX1 = wxNewId();
const long SeupPulsePeriod::ID_BUTTON1 = wxNewId();
const long SeupPulsePeriod::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SeupPulsePeriod,wxDialog)
	//(*EventTable(SeupPulsePeriod)
	//*)
END_EVENT_TABLE()

SeupPulsePeriod::SeupPulsePeriod(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SeupPulsePeriod)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_T("Excel (Limitid Size) (.csv)"),
		_T("Geenral (.csv)")
	};
	FileType = new wxRadioBox(this, ID_RADIOBOX1, _T("File Type"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	wxFont FileTypeFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	FileType->SetFont(FileTypeFont);
	FlexGridSizer1->Add(FileType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_T("Single (Append)"),
		_T("Multiple (Suffix Name)")
	};
	NumberofFiles = new wxRadioBox(this, ID_RADIOBOX2, _T("Number of Files"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX2"));
	wxFont NumberofFilesFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	NumberofFiles->SetFont(NumberofFilesFont);
	FlexGridSizer1->Add(NumberofFiles, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_T("Local Time (i.e. EST)"),
		_T("Universal Time (UT)")
	};
	TimeStandard = new wxRadioBox(this, ID_RADIOBOX3, _T("Time Standard"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX3"));
	wxFont TimeStandardFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	TimeStandard->SetFont(TimeStandardFont);
	FlexGridSizer1->Add(TimeStandard, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Enter File Name : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	PulseFile = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, _T("/PulseOut.csv"), wxEmptyString, _T("*.csv\""), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	wxFont PulseFileFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	PulseFile->SetFont(PulseFileFont);
	FlexGridSizer1->Add(PulseFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Overwrite = new wxCheckBox(this, ID_CHECKBOX1, _T("OVERWRITE\?"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	Overwrite->SetValue(false);
	wxFont OverwriteFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	Overwrite->SetFont(OverwriteFont);
	FlexGridSizer1->Add(Overwrite, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	OK = new wxButton(this, ID_BUTTON1, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont OKFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	OK->SetFont(OKFont);
	FlexGridSizer2->Add(OK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Cancel = new wxButton(this, ID_BUTTON2, _T("CANCEL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont CancelFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	Cancel->SetFont(CancelFont);
	FlexGridSizer2->Add(Cancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SeupPulsePeriod::OnFileTypeSelect);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SeupPulsePeriod::OnNumberofFilesSelect);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SeupPulsePeriod::OnTimeStandardSelect);
	Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SeupPulsePeriod::OnPulsePeriodFileFileChanged);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SeupPulsePeriod::OnOverwriteClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SeupPulsePeriod::OnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SeupPulsePeriod::OnCancelClick);
	//*)
}

SeupPulsePeriod::~SeupPulsePeriod()
{
	//(*Destroy(SeupPulsePeriod)
	//*)
}


void SeupPulsePeriod::OnFileTypeSelect(wxCommandEvent& event)
{
}

void SeupPulsePeriod::OnNumberofFilesSelect(wxCommandEvent& event)
{
}

void SeupPulsePeriod::OnTimeStandardSelect(wxCommandEvent& event)
{
}

void SeupPulsePeriod::OnPulsePeriodFileFileChanged(wxFileDirPickerEvent& event)
{
}

void SeupPulsePeriod::OnOverwriteClick(wxCommandEvent& event)
{
}

void SeupPulsePeriod::OnOKClick(wxCommandEvent& event)
{
    OK->Enable(false); // Avoid Double Click
}

void SeupPulsePeriod::OnCancelClick(wxCommandEvent& event)
{
    Destroy();
}
