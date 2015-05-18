#include "dlgRegTest.h"

//(*InternalHeaders(dlgRegTest)
#include <wx/sizer.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgRegTest)
const long dlgRegTest::ID_RICHTEXTCTRL1 = wxNewId();
const long dlgRegTest::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgRegTest,wxDialog)
	//(*EventTable(dlgRegTest)
	//*)
END_EVENT_TABLE()

dlgRegTest::dlgRegTest(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgRegTest::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgRegTest)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Registers test"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(409,436));
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	reInfo = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(392,384), wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
		wxRichTextAttr rchtxtAttr_1;
	FlexGridSizer1->Add(reInfo, 0, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnClose = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRegTest::OnbtnCloseClick);
	//*)
	reInfo->Clear();
}

dlgRegTest::~dlgRegTest()
{
	//(*Destroy(dlgRegTest)
	//*)
}

void dlgRegTest::AddLine(wxString Line)
{
	reInfo->AppendText(Line);
	reInfo->AppendText("\n");
};

void dlgRegTest::OnbtnCloseClick(wxCommandEvent& event)
{
    this->EndDialog(wxOK);
}

void dlgRegTest::OnbtnCloseClick1(wxCommandEvent& event)
{
    this->EndDialog(wxOK);
}
