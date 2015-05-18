#ifndef DLGVCOCAPLOG_H
#define DLGVCOCAPLOG_H

//(*Headers(dlgVcoCapLog)
#include <wx/dialog.h>
class wxRichTextCtrl;
//*)

class dlgVcoCapLog: public wxDialog
{
	public:

		dlgVcoCapLog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgVcoCapLog();
		void AddLine(wxString Line);

		//(*Declarations(dlgVcoCapLog)
		wxRichTextCtrl* memLogText;
		//*)

	protected:

		//(*Identifiers(dlgVcoCapLog)
		static const long ID_RICHTEXTCTRL1;
		//*)

	private:

		//(*Handlers(dlgVcoCapLog)
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
