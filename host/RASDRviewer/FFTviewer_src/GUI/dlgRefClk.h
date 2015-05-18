#ifndef DLGREFCLK_H
#define DLGREFCLK_H

//(*Headers(dlgRefClk)
#include <wx/dialog.h>
class wxTextCtrl;
class wxStaticText;
class wxFlexGridSizer;
class wxBoxSizer;
class wxButton;
//*)

class dlgRefClk: public wxDialog
{
	public:

		dlgRefClk(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgRefClk();

		//(*Declarations(dlgRefClk)
		wxButton* btnS02;
		wxButton* btnS01;
		wxButton* btnCancel;
		wxTextCtrl* txtRefClk;
		wxStaticText* StaticText1;
		wxButton* btnOK;
		//*)

	protected:

		//(*Identifiers(dlgRefClk)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		//*)

	private:

		//(*Handlers(dlgRefClk)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnS01Click(wxCommandEvent& event);
		void OnbtnS02Click(wxCommandEvent& event);
		void OnbtnS01Click1(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
