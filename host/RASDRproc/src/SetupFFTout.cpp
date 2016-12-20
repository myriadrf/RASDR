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
const long SetupFFTout::ID_RADIOBOX4 = wxNewId();
const long SetupFFTout::ID_RADIOBOX3 = wxNewId();
const long SetupFFTout::ID_RADIOBOX2 = wxNewId();
const long SetupFFTout::ID_RADIOBUTTON2 = wxNewId();
const long SetupFFTout::ID_RADIOBUTTON1 = wxNewId();
const long SetupFFTout::ID_FILEPICKERCTRL1 = wxNewId();
const long SetupFFTout::ID_CHECKBOX1 = wxNewId();
const long SetupFFTout::ID_SPINCTRL1 = wxNewId();
const long SetupFFTout::ID_STATICTEXT4 = wxNewId();
const long SetupFFTout::ID_SPINCTRL2 = wxNewId();
const long SetupFFTout::ID_STATICTEXT1 = wxNewId();
const long SetupFFTout::ID_COMBOBOX1 = wxNewId();
const long SetupFFTout::ID_STATICTEXT2 = wxNewId();
const long SetupFFTout::ID_BUTTON1 = wxNewId();
const long SetupFFTout::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SetupFFTout,wxDialog)
	//(*EventTable(SetupFFTout)
	//*)
END_EVENT_TABLE()
double dbTrigger;

SetupFFTout::SetupFFTout(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    dbTrigger = -999.0;  // negative value <= -900 means off
    wxString marker1DbStr = wxString::Format(wxT("Marker 1 amplitude %.1f"),marker1Db);
	//(*Initialize(SetupFFTout)
	wxFlexGridSizer* FlexGridSizer4;
	wxGridBagSizer* GridBagSizer1;
	wxFlexGridSizer* FlexGridSizer3;
	wxGridBagSizer* GridBagSizer2;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Setup FFT Output"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(514,775));
	SetFocus();
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Excel (Limited Bins)"),
		_("General Comma Delimited")
	};
	FileType = new wxRadioBox(this, ID_RADIOBOX1, _("File Type"), wxDefaultPosition, wxSize(249,95), 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	wxFont FileTypeFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	FileType->SetFont(FileTypeFont);
	GridBagSizer1->Add(FileType, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("ALL FFT Bins"),
		_("ZOOM FFT Range Bins")
	};
	DataSource = new wxRadioBox(this, ID_RADIOBOX4, _("Data Source"), wxDefaultPosition, wxSize(247,96), 2, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX4"));
	wxFont DataSourceFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	DataSource->SetFont(DataSourceFont);
	GridBagSizer1->Add(DataSource, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("Local Time (i.e. EST)"),
		_("Universal Time (UT)")
	};
	TimeStandard = new wxRadioBox(this, ID_RADIOBOX3, _("Time Standard"), wxDefaultPosition, wxSize(248,91), 2, __wxRadioBoxChoices_3, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX3"));
	wxFont TimeStandardFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	TimeStandard->SetFont(TimeStandardFont);
	GridBagSizer1->Add(TimeStandard, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_("Single"),
		_("Multiple (Suffix File Name)")
	};
	NumbFiles = new wxRadioBox(this, ID_RADIOBOX2, _("Number of Files"), wxDefaultPosition, wxSize(249,90), 2, __wxRadioBoxChoices_4, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX2"));
	wxFont NumbFilesFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	NumbFiles->SetFont(NumbFilesFont);
	GridBagSizer1->Add(NumbFiles, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	RadioButton2 = new wxRadioButton(this, ID_RADIOBUTTON2, _("Trigger on Amplitude Change"), wxDefaultPosition, wxSize(241,28), 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	wxFont RadioButton2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	RadioButton2->SetFont(RadioButton2Font);
	FlexGridSizer3->Add(RadioButton2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, _("Trigger on Record Button"), wxDefaultPosition, wxSize(235,23), 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	RadioButton1->SetValue(true);
	wxFont RadioButton1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	RadioButton1->SetFont(RadioButton1Font);
	FlexGridSizer3->Add(RadioButton1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(FlexGridSizer3, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("File Output"));
	OutputFile = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, wxEmptyString, wxEmptyString, _T("*.csv"), wxDefaultPosition, wxSize(259,57), wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	wxFont OutputFileFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	OutputFile->SetFont(OutputFileFont);
	StaticBoxSizer1->Add(OutputFile, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	OverwriteChk = new wxCheckBox(this, ID_CHECKBOX1, _("Overwrite\?"), wxDefaultPosition, wxSize(248,26), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	OverwriteChk->SetValue(false);
	wxFont OverwriteChkFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	OverwriteChk->SetFont(OverwriteChkFont);
	StaticBoxSizer1->Add(OverwriteChk, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	GridBagSizer1->Add(StaticBoxSizer1, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer2 = new wxGridBagSizer(0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FFTsToRec = new wxSpinCtrl(this, ID_SPINCTRL1, _T("9999"), wxDefaultPosition, wxSize(82,21), 0, 1, 10000, 9999, _T("ID_SPINCTRL1"));
	FFTsToRec->SetValue(_T("9999"));
	wxFont FFTsToRecFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	FFTsToRec->SetFont(FFTsToRecFont);
	FlexGridSizer2->Add(FFTsToRec, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("TOTAL FFTs"), wxDefaultPosition, wxSize(114,24), wxALIGN_LEFT, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer2->Add(FlexGridSizer2, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	SpinCtrl1 = new wxSpinCtrl(this, ID_SPINCTRL2, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 1, _T("ID_SPINCTRL2"));
	SpinCtrl1->SetValue(_T("1"));
	wxFont SpinCtrl1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	SpinCtrl1->SetFont(SpinCtrl1Font);
	FlexGridSizer5->Add(SpinCtrl1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Skip frames"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer2->Add(FlexGridSizer5, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	ComboBox1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(77,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	ComboBox1->Append(_("+1 dB"));
	ComboBox1->Append(_("+2 dB"));
	ComboBox1->SetSelection( ComboBox1->Append(_("+3 dB")) );
	ComboBox1->Append(_("+6 dB"));
	wxFont ComboBox1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	ComboBox1->SetFont(ComboBox1Font);
	FlexGridSizer6->Add(ComboBox1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, marker1DbStr, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	FlexGridSizer6->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	GridBagSizer2->Add(FlexGridSizer6, wxGBPosition(2, 0), wxDefaultSpan, wxALIGN_LEFT|wxALIGN_TOP, 0);
	GridBagSizer1->Add(GridBagSizer2, wxGBPosition(7, 0), wxDefaultSpan, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	Button1 = new wxButton(this, ID_BUTTON1, _("OK | Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont Button1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	Button1->SetFont(Button1Font);
	FlexGridSizer4->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxFont Button2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	Button2->SetFont(Button2Font);
	FlexGridSizer4->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(FlexGridSizer4, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer1->Add(GridBagSizer1, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();
	Center();

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnFileTypeSelect);
	Connect(ID_RADIOBOX4,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnDataSourceSelect);
	Connect(ID_RADIOBOX3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnTimeStandardSelect);
	Connect(ID_RADIOBOX2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnNumbFilesSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&SetupFFTout::OnRadioButton2Select1);
	Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SetupFFTout::OnOutputFileFileChanged);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnOverwriteChkClick);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SetupFFTout::OnFFTsToRecChange);
	//*)
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnFFTfileOKbtnClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnCancelClick);
//	FFTfileOKbtn = new wxButton(this,wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, wxDefaultValidator, _T("ID_BUTTON2"));
//	FFTfileOKbtn = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FFTOKBUTTON"));
    NumbFiles->SetSelection(g_NumbFFTFiles-1);
    FileType->SetSelection(g_FFTFileType);
    TimeStandard->SetSelection(g_FFT_TimeStandard);
    //FrameSkip->SetValue(g_FFTframeSkip);
    FFTsToRec->SetValue(g_FFTframesOut);
    DataSource->SetSelection(g_FFTDataSource);
//    OutputFile->SetPath(g_FFTfileName);
}


/* DO NOT ERASE THESE COMMENT CODE LINES.  Every time wxSmith pens SetupFFTout.wxs, they are lost in the init code above. argh.
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnFFTfileOKbtnClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SetupFFTout::OnCancelClick);
*/

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
    Button1->Enable(false); // Avoid Double Click

    g_NumbFFTFiles = NumbFiles -> GetSelection() + 1;
    g_FFTFileType = FileType -> GetSelection();
    g_FFT_TimeStandard = TimeStandard->GetSelection();
    g_FFTDataSource = DataSource->GetSelection();
    if(g_capturingData) g_PendingRestartCapture = true;
    g_FFTfileSetup = true;

    /* db trigger mode? */
    if (RadioButton2->GetValue()) {
        /* ComboBox1 is the dB trigger value */
        int selection = ComboBox1->GetCurrentSelection();
        switch (selection) {  //0 indexed, TO DO:  use enumeration instead of magic numbers so can synch with widget definition
            case 0:
                dbTrigger = 1.0;
                break;
            case 1:
                dbTrigger = 2.0;
                break;
            case 2:
                dbTrigger = 3.0;
                break;
            case 3:
                dbTrigger = 6.0;
                break;
        }
        g_dbTrigger = dbTrigger;
    }
    printf("dbTrigger %.1f \n",dbTrigger);
    printf("g_FFTfileNAme %s \n",g_FFTfileName);
    if (g_FFTfileIsDefined) {
        printf("g_FFTfileisDefined ** \n");
    }
    Destroy();
}

void SetupFFTout::OnOutputFileFileChanged(wxFileDirPickerEvent& event)
{
    strncpy(g_FFTfileName,OutputFile->GetPath(),1023);
    g_FFTfileIsDefined = true;
}


void SetupFFTout::OnOverwriteChkClick(wxCommandEvent& event)
{
    if(OverwriteChk->IsChecked()) g_OverwriteFFTfile = true;
    else g_OverwriteFFTfile = false;
}

void SetupFFTout::OnFrameSkipChange(wxSpinEvent& event)
{
    //g_FFTframeSkip = FrameSkip->GetValue();//FFTsToRec = new wxSpinCtrl(this, ID_SPINCTRL1, _T("64"), wxDefaultPosition, wxSize(82,21), 0, 1, 10000, 64, _T("ID_SPINCTRL1"));
	//FFTsToRec->SetValue(_T("64"));//FrameSkip->GetValue();
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

void SetupFFTout::OnRadioButton2Select(wxCommandEvent& event)
{
}

void SetupFFTout::OnRadioButton2Select1(wxCommandEvent& event)
{
}

void SetupFFTout::OnRadioButton3Select(wxCommandEvent& event)
{
}

void SetupFFTout::SetMarker1DbLevel(float db) {
    marker1Db = db;
    wxString marker1DbStr;
    marker1DbStr = wxString::Format(wxT("Marker 1 amplitude %.1f dB"),marker1Db);
    if (db > 900) { //if marker 1 not set yet, so disable trigger on amplitude option
        RadioButton2->Disable();
        marker1DbStr = wxString("Marker 1 not yet set");
    }
    StaticText2->SetLabel(marker1DbStr);
}
