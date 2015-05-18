#ifndef DLGVCOGRPH_H
#define DLGVCOGRPH_H

//(*Headers(dlgVcoGrph)
#include <wx/dialog.h>
class wxPanel;
class wxBoxSizer;
//*)

class dlgVcoGrph: public wxDialog
{
	public:

		dlgVcoGrph(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgVcoGrph();

		//(*Declarations(dlgVcoGrph)
		wxPanel* Panel1;
		//*)

	protected:

		//(*Identifiers(dlgVcoGrph)
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(dlgVcoGrph)
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
