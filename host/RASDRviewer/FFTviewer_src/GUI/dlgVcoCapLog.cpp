#include "dlgVcoCapLog.h"

//(*InternalHeaders(dlgVcoCapLog)
#include <wx/richtext/richtextctrl.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgVcoCapLog)
const long dlgVcoCapLog::ID_RICHTEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgVcoCapLog,wxDialog)
	//(*EventTable(dlgVcoCapLog)
	//*)
END_EVENT_TABLE()

dlgVcoCapLog::dlgVcoCapLog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgVcoCapLog::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgVcoCapLog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(427,256));
	Move(wxDefaultPosition);
	memLogText = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, _("Text"), wxDefaultPosition, wxSize(424,256), wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
		wxRichTextAttr rchtxtAttr_1;
	//*)
}

dlgVcoCapLog::~dlgVcoCapLog()
{
	//(*Destroy(dlgVcoCapLog)
	//*)
}

void dlgVcoCapLog::AddLine(wxString Line)
{
	memLogText->AppendText(Line);
	memLogText->AppendText("\n");
};
