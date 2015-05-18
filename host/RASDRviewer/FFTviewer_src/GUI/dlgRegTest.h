#ifndef DLGREGTEST_H
#define DLGREGTEST_H

//(*Headers(dlgRegTest)
#include <wx/dialog.h>
class wxRichTextCtrl;
class wxFlexGridSizer;
class wxButton;
//*)

class dlgRegTest: public wxDialog
{
	public:

		dlgRegTest(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgRegTest();

        void AddLine(wxString Line);

		//(*Declarations(dlgRegTest)
		wxRichTextCtrl* reInfo;
		wxButton* btnClose;
		//*)

	protected:

		//(*Identifiers(dlgRegTest)
		static const long ID_RICHTEXTCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(dlgRegTest)
		void OnbtnCloseClick(wxCommandEvent& event);
		void OnbtnCloseClick1(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
