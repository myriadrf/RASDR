// -----------------------------------------------------------------------------
// FILE:        "SetupDMOut.cpp"
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
#include "SetupDMOut.h"

//(*InternalHeaders(SetupDMOut)
#include <wx/font.h>
#include <wx/string.h>
//*)

//(*IdInit(SetupDMOut)
const long SetupDMOut::ID_RADIOBOX1 = wxNewId();
const long SetupDMOut::ID_RADIOBOX2 = wxNewId();
const long SetupDMOut::ID_RADIOBOX3 = wxNewId();
const long SetupDMOut::ID_STATICTEXT1 = wxNewId();
const long SetupDMOut::ID_FILEPICKERCTRL1 = wxNewId();
const long SetupDMOut::ID_CHECKBOX1 = wxNewId();
const long SetupDMOut::ID_BUTTON1 = wxNewId();
const long SetupDMOut::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SetupDMOut,wxDialog)
	//(*EventTable(SetupDMOut)
	//*)
END_EVENT_TABLE()

SetupDMOut::SetupDMOut(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SetupDMOut)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_T("Excel(limited Size .csv)"),
		_T("General (.csv)")
	};
	File_Type = new wxRadioBox(this, ID_RADIOBOX1, _T("File Type"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	wxFont File_TypeFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	File_Type->SetFont(File_TypeFont);
	FlexGridSizer1->Add(File_Type, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_T("Single (Append)"),
		_T("Multiple (Suffix Name)")
	};
	Numb_Files = new wxRadioBox(this, ID_RADIOBOX2, _T("Number of Files"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX2"));
	wxFont Numb_FilesFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	Numb_Files->SetFont(Numb_FilesFont);
	FlexGridSizer1->Add(Numb_Files, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_T("Local Time Zone"),
		_T("Universal Time")
	};
	TimeStd = new wxRadioBox(this, ID_RADIOBOX3, _T("Tme Standard"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX3"));
	wxFont TimeStdFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	TimeStd->SetFont(TimeStdFont);
	FlexGridSizer1->Add(TimeStd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("ENTER FLE NAME: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	DMFileName = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, _T("DMOut.csv"), wxEmptyString, _T("*.csv"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	wxFont DMFileNameFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	DMFileName->SetFont(DMFileNameFont);
	FlexGridSizer1->Add(DMFileName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	AppendDMFile = new wxCheckBox(this, ID_CHECKBOX1, _T("APPEND"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	AppendDMFile->SetValue(false);
	wxFont AppendDMFileFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	AppendDMFile->SetFont(AppendDMFileFont);
	FlexGridSizer1->Add(AppendDMFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	OK = new wxButton(this, ID_BUTTON1, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont OKFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	OK->SetFont(OKFont);
	FlexGridSizer1->Add(OK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Cancel = new wxButton(this, ID_BUTTON2, _T("CANCEL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont CancelFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	Cancel->SetFont(CancelFont);
	FlexGridSizer1->Add(Cancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupDMOut::OnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupDMOut::OnCancelClick);
	//*)
}

SetupDMOut::~SetupDMOut()
{
	//(*Destroy(SetupDMOut)
	//*)
}


void SetupDMOut::OnOKClick(wxCommandEvent& event)
{
    OK->Enable(false); // Avoid Double Click
}

void SetupDMOut::OnCancelClick(wxCommandEvent& event)
{
    Destroy();
}
