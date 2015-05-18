// -----------------------------------------------------------------------------
// FILE:        "dlgFreqVsCap.cpp"
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
#include "dlgFreqVsCap.h"

//(*InternalHeaders(dlgFreqVsCap)
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

#include "ctr_6002dr2_LogicDLL.h"
#include "GUIUtils.h"
#include "dlgVcoGrph.h"

//(*IdInit(dlgFreqVsCap)
const long dlgFreqVsCap::ID_SPINCTRL1 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON1 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON2 = wxNewId();
const long dlgFreqVsCap::ID_GRID1 = wxNewId();
const long dlgFreqVsCap::ID_PANEL1 = wxNewId();
const long dlgFreqVsCap::ID_SPINCTRL2 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON3 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON4 = wxNewId();
const long dlgFreqVsCap::ID_GRID2 = wxNewId();
const long dlgFreqVsCap::ID_PANEL2 = wxNewId();
const long dlgFreqVsCap::ID_SPINCTRL3 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON5 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON6 = wxNewId();
const long dlgFreqVsCap::ID_GRID3 = wxNewId();
const long dlgFreqVsCap::ID_PANEL3 = wxNewId();
const long dlgFreqVsCap::ID_SPINCTRL4 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON7 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON8 = wxNewId();
const long dlgFreqVsCap::ID_GRID4 = wxNewId();
const long dlgFreqVsCap::ID_PANEL4 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON9 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON10 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON11 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON12 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgFreqVsCap,wxDialog)
	//(*EventTable(dlgFreqVsCap)
	//*)
END_EVENT_TABLE()

dlgFreqVsCap::dlgFreqVsCap(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgFreqVsCap::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgFreqVsCap)
	wxFlexGridSizer* FlexGridSizer4;
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

	Create(parent, id, _("Frequency vs Capacitance"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO1Pts = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL1"));
	txtVCO1Pts->SetValue(_T("3"));
	FlexGridSizer3->Add(txtVCO1Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO1_RFCnt = new wxButton(Panel1, ID_BUTTON1, _("Set VCO1 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnSetVCO1_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO1 = new wxButton(Panel1, ID_BUTTON2, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnViewGrphVCO1->Disable();
	FlexGridSizer3->Add(btnViewGrphVCO1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco1 = new wxGrid(Panel1, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	grdVco1->CreateGrid(3,2);
	grdVco1->EnableEditing(true);
	grdVco1->EnableGridLines(true);
	grdVco1->SetRowLabelSize(48);
	grdVco1->SetDefaultColSize(100, true);
	grdVco1->SetColLabelValue(0, _("Vco1 Freq. GHz"));
	grdVco1->SetColLabelValue(1, _("Vco1 Cap "));
	grdVco1->SetDefaultCellFont( grdVco1->GetFont() );
	grdVco1->SetDefaultCellTextColour( grdVco1->GetForegroundColour() );
	FlexGridSizer2->Add(grdVco1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel1);
	FlexGridSizer2->SetSizeHints(Panel1);
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO2Pts = new wxSpinCtrl(Panel2, ID_SPINCTRL2, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL2"));
	txtVCO2Pts->SetValue(_T("3"));
	FlexGridSizer5->Add(txtVCO2Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO2_RFCnt = new wxButton(Panel2, ID_BUTTON3, _("Set VCO2 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer5->Add(btnSetVCO2_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO2 = new wxButton(Panel2, ID_BUTTON4, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	btnViewGrphVCO2->Disable();
	FlexGridSizer5->Add(btnViewGrphVCO2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco2 = new wxGrid(Panel2, ID_GRID2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID2"));
	grdVco2->CreateGrid(3,2);
	grdVco2->EnableEditing(true);
	grdVco2->EnableGridLines(true);
	grdVco2->SetRowLabelSize(48);
	grdVco2->SetDefaultColSize(100, true);
	grdVco2->SetColLabelValue(0, _("Vco2 Freq. GHz"));
	grdVco2->SetColLabelValue(1, _("Vco2 Cap "));
	grdVco2->SetDefaultCellFont( grdVco2->GetFont() );
	grdVco2->SetDefaultCellTextColour( grdVco2->GetForegroundColour() );
	FlexGridSizer4->Add(grdVco2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(FlexGridSizer4);
	FlexGridSizer4->Fit(Panel2);
	FlexGridSizer4->SetSizeHints(Panel2);
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO3Pts = new wxSpinCtrl(Panel3, ID_SPINCTRL3, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL3"));
	txtVCO3Pts->SetValue(_T("3"));
	FlexGridSizer7->Add(txtVCO3Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO3_RFCnt = new wxButton(Panel3, ID_BUTTON5, _("Set VCO3 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer7->Add(btnSetVCO3_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO3 = new wxButton(Panel3, ID_BUTTON6, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	btnViewGrphVCO3->Disable();
	FlexGridSizer7->Add(btnViewGrphVCO3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco3 = new wxGrid(Panel3, ID_GRID3, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID3"));
	grdVco3->CreateGrid(3,2);
	grdVco3->EnableEditing(true);
	grdVco3->EnableGridLines(true);
	grdVco3->SetRowLabelSize(48);
	grdVco3->SetDefaultColSize(100, true);
	grdVco3->SetColLabelValue(0, _("Vco3 Freq. GHz"));
	grdVco3->SetColLabelValue(1, _("Vco3 Cap "));
	grdVco3->SetDefaultCellFont( grdVco3->GetFont() );
	grdVco3->SetDefaultCellTextColour( grdVco3->GetForegroundColour() );
	FlexGridSizer6->Add(grdVco3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(Panel3);
	FlexGridSizer6->SetSizeHints(Panel3);
	FlexGridSizer1->Add(Panel3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO4Pts = new wxSpinCtrl(Panel4, ID_SPINCTRL4, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL4"));
	txtVCO4Pts->SetValue(_T("3"));
	FlexGridSizer9->Add(txtVCO4Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO4_RFCnt = new wxButton(Panel4, ID_BUTTON7, _("Set VCO4 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	FlexGridSizer9->Add(btnSetVCO4_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO4 = new wxButton(Panel4, ID_BUTTON8, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	btnViewGrphVCO4->Disable();
	FlexGridSizer9->Add(btnViewGrphVCO4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco4 = new wxGrid(Panel4, ID_GRID4, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID4"));
	grdVco4->CreateGrid(3,2);
	grdVco4->EnableEditing(true);
	grdVco4->EnableGridLines(true);
	grdVco4->SetRowLabelSize(48);
	grdVco4->SetDefaultColSize(100, true);
	grdVco4->SetColLabelValue(0, _("Vco4 Freq. GHz"));
	grdVco4->SetColLabelValue(1, _("Vco4 Cap "));
	grdVco4->SetDefaultCellFont( grdVco4->GetFont() );
	grdVco4->SetDefaultCellTextColour( grdVco4->GetForegroundColour() );
	FlexGridSizer8->Add(grdVco4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4->SetSizer(FlexGridSizer8);
	FlexGridSizer8->Fit(Panel4);
	FlexGridSizer8->SetSizeHints(Panel4);
	FlexGridSizer1->Add(Panel4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	OKBtn = new wxButton(this, ID_BUTTON9, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
	BoxSizer1->Add(OKBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CancelBtn = new wxButton(this, ID_BUTTON10, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	BoxSizer1->Add(CancelBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	btnLoad = new wxButton(this, ID_BUTTON11, _("Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
	btnLoad->Disable();
	BoxSizer2->Add(btnLoad, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSave = new wxButton(this, ID_BUTTON12, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
	btnSave->Disable();
	BoxSizer2->Add(btnSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO1_RFCntClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnViewGrphVCO1Click);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO2_RFCntClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO3_RFCntClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO4_RFCntClick);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OKBtnClick);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnCancelBtnClick);
	//*)

	sVco1.iRef = 0;
	sVco1.dFreq = NULL;
	sVco1.iCap = NULL;
	sVco2.iRef = 0;
	sVco2.dFreq = NULL;
	sVco2.iCap = NULL;
	sVco3.iRef = 0;
	sVco3.dFreq = NULL;
	sVco3.iCap = NULL;
	sVco4.iRef = 0;
	sVco4.dFreq = NULL;
	sVco4.iCap = NULL;
	m_sLastUsedVCOFile = "";
}

dlgFreqVsCap::~dlgFreqVsCap()
{
	//(*Destroy(dlgFreqVsCap)
	//*)
}

void dlgFreqVsCap::SetTblRws(int Cnt, wxGrid *grd)
{
	if (Cnt > grd->GetRows())
	{
		for (int i = grd->GetRows(); i < Cnt; i++)
		{
		    grd->AppendRows(1);
			grd->SetCellValue(0, i, "");
            grd->SetCellValue(1, i, "");
		}
	}
	else
	{
        for (int i = grd->GetRows(); i >= Cnt; i--)
		{
		    grd->DeleteRows(i);
		}
	}
};

bool dlgFreqVsCap::CheckValues(wxGrid *grd)
{
	double dtry;
	char *ends;
	for (int i = 0; i < grdVco1->GetRows(); i++)
	{
		dtry = strtod(toCString(grd->GetCellValue(0, i)), &ends);
		if (*ends != NULL)
		{
			// ShowMessage("Allowed Input: +-1234567890.");
			return false;
		};

		dtry = strtod(toCString(grd->GetCellValue(1, i)), &ends);
		if (*ends != NULL)
		{
			// ShowMessage("Allowed Input: +-1234567890.");
			return false;
		};
	};
	return true;
};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::btnSaveClick(wxCommandEvent& event)
{
// TODO (userk1#1#): rewrite with streams

    /*
    wxFileDialog saveFileDialog(this, _("Save XYZ file"), "", "", "Project-Files (*.prj)|*.prj", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

	if (saveFileDialog.ShowModal() == wxID_OK)
	{
		// Check values
		if (!CheckValues(grdVco1))
		{
			ShowMessage(
				"Allowed Input in Table for VCO1: +-1234567890.\nValues are not Saved To the File!");
			return;
		};
		if (!CheckValues(grdVco2))
		{
			ShowMessage(
				"Allowed Input in Table for VCO2: +-1234567890.\nValues are not Saved To the File!");
			return;
		};
		if (!CheckValues(grdVco3))
		{
			ShowMessage(
				"Allowed Input in Table for VCO3: +-1234567890.\nValues are not Saved To the File!");
			return;
		};
		if (!CheckValues(grdVco4))
		{
			ShowMessage(
				"Allowed Input in Table for VCO4: +-1234567890.\nValues are not Saved To the File!");
			return;
		};

		pfItems = CreateFile(toCString(dlgSave->FileName), // name of the file
			GENERIC_WRITE, // desired access
			FILE_SHARE_READ, // share mode
			NULL, // security attributes
			CREATE_ALWAYS, // creation disposition
			FILE_ATTRIBUTE_NORMAL,
			// | FILE_FLAG_WRITE_THROUGH , //flags and attr
			NULL); // template file

		if (pfItems == INVALID_HANDLE_VALUE)
		{
			ShowMessage(
				"Can not Create File.\nValues are not Saved To the File!");
			return;
		};

		// VCO1 Values
		iCnt = txtVCO1Pts->Text.ToInt();
		WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt),
			(LPDWORD)&writen, NULL);
		for (int i = 1; i <= iCnt; i++)
		{
			dTmp = grdVco1->Cells[1][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
			dTmp = grdVco1->Cells[2][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
		};

		// VCO2 Values
		iCnt = txtVCO2Pts->Text.ToInt();
		WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt),
			(LPDWORD)&writen, NULL);
		for (int i = 1; i <= iCnt; i++)
		{
			dTmp = grdVco2->Cells[1][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
			dTmp = grdVco2->Cells[2][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
		};

		// VCO3 Values
		iCnt = txtVCO3Pts->Text.ToInt();
		WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt),
			(LPDWORD)&writen, NULL);
		for (int i = 1; i <= iCnt; i++)
		{
			dTmp = grdVco3->Cells[1][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
			dTmp = grdVco3->Cells[2][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
		};

		// VCO4 Values
		iCnt = txtVCO4Pts->Text.ToInt();
		WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt),
			(LPDWORD)&writen, NULL);
		for (int i = 1; i <= iCnt; i++)
		{
			dTmp = grdVco4->Cells[1][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
			dTmp = grdVco4->Cells[2][i].ToDouble();
			WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp),
				(LPDWORD)&writen, NULL);
		};

		CloseHandle(pfItems);
	};
	*/
}

// ---------------------------------------------------------------------------
void dlgFreqVsCap::btnLoadClick(wxCommandEvent& event)
{
	wxFileDialog *openFileDialog = new wxFileDialog(this, _("Open file"), "", "", "VCO Values (*.vco)|*.vco", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog->ShowModal() == wxID_CANCEL)
        return;
    LoadValuesFromFile(openFileDialog->GetPath());
}
// ---------------------------------------------------------------------------

void dlgFreqVsCap::ConstructValues(sVcoVsCap &Vco, wxGrid *grdVco,
	wxSpinCtrl *VCOPts)
{
	DestroyValues(Vco);
	// Vco.iRef = VCOPts->Text.ToInt();
	Vco.iRef = VCOPts->GetValue();
	Vco.dFreq = new double[Vco.iRef];
	Vco.iCap = new double[Vco.iRef];
	for (int i = 0; i < Vco.iRef; i++)
	{
		Vco.dFreq[i] = atof(toCString(grdVco->GetCellValue(i, 0)));
		Vco.iCap[i] = atof(toCString(grdVco->GetCellValue(i, 1)));
	};
};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::FormDestroy(wxCommandEvent& event)
{
	DestroyValues(sVco1);
	DestroyValues(sVco2);
	DestroyValues(sVco3);
	DestroyValues(sVco4);
}

// ---------------------------------------------------------------------------
void dlgFreqVsCap::DestroyValues(sVcoVsCap &Vco)
{
	if (Vco.iRef)
	{
		Vco.iRef = 0;
		delete[]Vco.dFreq;
		Vco.dFreq = NULL;
		delete[]Vco.iCap;
		Vco.iCap = NULL;
	};
};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::OKBtnClick(wxCommandEvent& event)
{
	// Check values
	if (!CheckValues(grdVco1))
	{
		ShowMessage(
			"Allowed Input in Table for VCO1: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco1, grdVco1, txtVCO1Pts);
	LMLL_FreqVsCapSetVco(&sVco1, 1, true);

	// Check values
	if (!CheckValues(grdVco2))
	{
		ShowMessage(
			"Allowed Input in Table for VCO2: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco2, grdVco2, txtVCO2Pts);
	LMLL_FreqVsCapSetVco(&sVco2, 2, true);

	// Check values
	if (!CheckValues(grdVco3))
	{
		ShowMessage(
			"Allowed Input in Table for VCO3: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco3, grdVco3, txtVCO3Pts);
	LMLL_FreqVsCapSetVco(&sVco3, 3, true);

	// Check values
	if (!CheckValues(grdVco4))
	{
		ShowMessage(
			"Allowed Input in Table for VCO4: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco4, grdVco4, txtVCO4Pts);
	LMLL_FreqVsCapSetVco(&sVco4, 4, true);

	if (m_sLastUsedVCOFile != "")
		SavePathToReg(m_sLastUsedVCOFile);
    EndModal(wxID_OK);
}

// ---------------------------------------------------------------------------
void dlgFreqVsCap::Initialize(wxString Name)
{
	wxString FName;
	wxString Str;
	m_sName = Name;

	// Load VCO calibration values from last used file
	FName = ReadPathFromReg();

	if (!FileExists(FName))
	{
		if (m_sName == "TxVCOFile")
		{
			//FName = ChangeFileExt(Application->ExeName, ".tco");
		}
		else
		{
			//FName = ChangeFileExt(Application->ExeName, ".rco");
		};
	};

	if (FileExists(FName))
	{
		LoadValuesFromFile(toCString(FName));
	}
	else
	{
		Str = "Can't find VCO calibration values file for" + Name;
		Str = Str + "\nDefault values are used.";
		// Uncoment this line for displaying the message.
		// ShowMessage(Str);
	};

	ShowVCOValues(LMLL_FreqVsCapGetVco(1, true), grdVco1, txtVCO1Pts);
	ShowVCOValues(LMLL_FreqVsCapGetVco(2, true), grdVco2, txtVCO1Pts);
	ShowVCOValues(LMLL_FreqVsCapGetVco(3, true), grdVco3, txtVCO1Pts);
	ShowVCOValues(LMLL_FreqVsCapGetVco(4, true), grdVco4, txtVCO1Pts);
	ConstructValues(sVco1, grdVco1, txtVCO1Pts);
	ConstructValues(sVco2, grdVco2, txtVCO2Pts);
	ConstructValues(sVco3, grdVco3, txtVCO3Pts);
	ConstructValues(sVco4, grdVco4, txtVCO4Pts);

};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::SavePathToReg(wxString Path)
{
    /*
	TRegistry* reg = new TRegistry;
	// reg->OpenKey("Software\\ctr_6002d\\Settings", true);
	reg->OpenKey(RegistrywxString, true);
	reg->WritewxString(m_sName, Path);
	// reg->WritewxString("LastDirectory", "C:\\");
	// reg->WriteInteger("Data", 1);
	delete reg;
	*/
};

// ---------------------------------------------------------------------------
wxString dlgFreqVsCap::ReadPathFromReg()
{
    /*
	wxString FileName;
	TRegistry* reg = new TRegistry;
	// reg->OpenKey("Software\\ctr_6002d\\Settings", true);
	reg->OpenKey(RegistrywxString, true);
	FileName = reg->ReadwxString(m_sName);
	delete reg;
	return FileName;
	*/
	return wxString("");
};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::FormShow(wxCommandEvent& event)
{
	ShowVCOValues(LMLL_FreqVsCapGetVco(1, true), grdVco1, txtVCO1Pts);
	ShowVCOValues(LMLL_FreqVsCapGetVco(2, true), grdVco2, txtVCO2Pts);
	ShowVCOValues(LMLL_FreqVsCapGetVco(3, true), grdVco3, txtVCO3Pts);
	ShowVCOValues(LMLL_FreqVsCapGetVco(4, true), grdVco4, txtVCO4Pts);
}
// ---------------------------------------------------------------------------

void dlgFreqVsCap::ShowVCOValues(sVcoVsCap *Vco, wxGrid *grdVco, wxSpinCtrl *VCOPts)
{
	char buffer[50];
	int precision = 5;

	VCOPts->SetValue(Vco->iRef);
	SetTblRws(Vco->iRef, grdVco);
	for (int i = 0; i < Vco->iRef; i++)
	{
		gcvt(Vco->dFreq[i], precision, buffer);
		grdVco->SetCellValue(i, 0, buffer);
		//gcvt(Vco->iCap[i], 1, buffer);
		grdVco->SetCellValue(i, 1, wxString::Format("%.0f", Vco->iCap[i]));
	};
};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::LoadValuesFromFile(wxString FName)
{
    /*
	HANDLE pfItems;
	DWORD dwBytesRead;
	int iCnt;
	double dTmp;
	sVcoVsCap VcoVsCap;

	pfItems = CreateFile(toCString(FName), // name of the file
		GENERIC_READ, // desired access
		FILE_SHARE_READ, // share mode
		NULL, // security attributes
		OPEN_EXISTING, // creation disposition
		FILE_ATTRIBUTE_NORMAL, // | FILE_FLAG_WRITE_THROUGH , //flags and attr
		NULL); // template file
	if (pfItems == INVALID_HANDLE_VALUE)
	{
		ShowMessage("Can not Open the File!");
		return;
	};

	// --===== Save path to registry. BEGIN =====--
	// SavePathToReg(FName);
	m_sLastUsedVCOFile = FName;
	// --=====  Save path to registry. END  =====--

	// VCO1 Values
	ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.dFreq[i - 1] = dTmp;
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	ShowVCOValues(&VcoVsCap, grdVco1, txtVCO1Pts);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	// VCO2 Values
	ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.dFreq[i - 1] = dTmp;
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	ShowVCOValues(&VcoVsCap, grdVco2, txtVCO2Pts);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	// VCO3 Values
	ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.dFreq[i - 1] = dTmp;
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	ShowVCOValues(&VcoVsCap, grdVco3, txtVCO3Pts);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	// VCO4 Values
	ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.dFreq[i - 1] = dTmp;
		ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	ShowVCOValues(&VcoVsCap, grdVco4, txtVCO4Pts);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	CloseHandle(pfItems);
	*/
};



void dlgFreqVsCap::OnbtnSetVCO1_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO1Pts->GetValue(), grdVco1);
}

void dlgFreqVsCap::OnbtnSetVCO2_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO2Pts->GetValue(), grdVco2);
}

void dlgFreqVsCap::OnbtnSetVCO3_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO3Pts->GetValue(), grdVco3);
}

void dlgFreqVsCap::OnbtnSetVCO4_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO4Pts->GetValue(), grdVco4);
}

void dlgFreqVsCap::OnbtnViewGrphVCO1Click(wxCommandEvent& event)
{
    dlgVcoGrph *graph = new dlgVcoGrph(this);
	// Check values
	if (!CheckValues(grdVco1))
	{
		ShowMessage(
			"Allowed Input in Table for VCO4: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco1, grdVco1, txtVCO1Pts);
	// TODO (userk1#1#): draw graph
	//graph->SetValues(sVco1.iRef, sVco1.dFreq, sVco1.iCap);
	graph->ShowModal();
	delete graph;
}

void dlgFreqVsCap::OnbtnViewGrphVCO2Click(wxCommandEvent& event)
{
    dlgVcoGrph *graph = new dlgVcoGrph(this);
	// Check values
	if (!CheckValues(grdVco1))
	{
		ShowMessage(
			"Allowed Input in Table for VCO4: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco2, grdVco2, txtVCO2Pts);
	// TODO (userk1#1#): draw graph
	//graph->SetValues(sVco1.iRef, sVco1.dFreq, sVco1.iCap);
	graph->ShowModal();
	delete graph;
}

void dlgFreqVsCap::OnbtnViewGrphVCO3Click(wxCommandEvent& event)
{
    dlgVcoGrph *graph = new dlgVcoGrph(this);
	// Check values
	if (!CheckValues(grdVco1))
	{
		ShowMessage(
			"Allowed Input in Table for VCO4: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco3, grdVco3, txtVCO3Pts);
// TODO (userk1#1#): draw graph
	//graph->SetValues(sVco1.iRef, sVco1.dFreq, sVco1.iCap);
	graph->ShowModal();
	delete graph;
}

void dlgFreqVsCap::OnbtnViewGrphVCO4Click(wxCommandEvent& event)
{
    dlgVcoGrph *graph = new dlgVcoGrph(this);
	// Check values
	if (!CheckValues(grdVco1))
	{
		ShowMessage(
			"Allowed Input in Table for VCO4: +-1234567890.\nCan not Draw Values!");
		return;
	};
	ConstructValues(sVco4, grdVco4, txtVCO4Pts);
	// TODO (userk1#1#): draw graph
	//graph->SetValues(sVco1.iRef, sVco1.dFreq, sVco1.iCap);
	graph->ShowModal();
	delete graph;
}

int dlgFreqVsCap::ShowModal()
{
    wxCommandEvent evt;
    FormShow(evt);
    return wxDialog::ShowModal();
}

void dlgFreqVsCap::OnCancelBtnClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
