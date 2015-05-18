#include "dlgVcoGrph.h"

//(*InternalHeaders(dlgVcoGrph)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgVcoGrph)
const long dlgVcoGrph::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgVcoGrph,wxDialog)
	//(*EventTable(dlgVcoGrph)
	//*)
END_EVENT_TABLE()

dlgVcoGrph::dlgVcoGrph(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgVcoGrph::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgVcoGrph)
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(719,464));
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(500,400), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer1->Add(Panel1, 1, wxALL|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	SetSizer(BoxSizer1);
	Layout();
	//*)
}

dlgVcoGrph::~dlgVcoGrph()
{
	//(*Destroy(dlgVcoGrph)
	//*)
}

