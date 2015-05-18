#ifndef PNLBOARD_H
#define PNLBOARD_H

//(*Headers(pnlBoard)
#include <wx/panel.h>
class wxCheckBox;
class wxTextCtrl;
class wxStaticLine;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

class pnlBoard: public wxPanel
{
	public:

		pnlBoard(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles=0, wxString idname="");
		virtual ~pnlBoard();
		void Initialize();

		//(*Declarations(pnlBoard)
		wxTextCtrl* txtDRVAfreq;
		wxRadioBox* rgrDRVCoutput;
		wxTextCtrl* txtDRVDfreq;
		wxPanel* Panel5;
		wxStaticText* StaticText2;
		wxButton* btnLoadFile;
		wxRadioBox* rgrRefClkSelect;
		wxTextCtrl* txtRefClk;
		wxTextCtrl* txtDRVCfreq;
		wxStaticText* StaticText1;
		wxCheckBox* chkDRVAInvertEven;
		wxStaticText* StaticText3;
		wxCheckBox* chkDRVCInvertOdd;
		wxRadioBox* rgrDRVAoutput;
		wxCheckBox* chkDRVDen;
		wxTextCtrl* txtDRVBfreq;
		wxPanel* Panel6;
		wxStaticLine* StaticLine4;
		wxStaticLine* StaticLine2;
		wxCheckBox* chkDRVBen;
		wxCheckBox* chkDRVAen;
		wxRadioBox* rgrCrystalFreq;
		wxCheckBox* chkDRVDInvertEven;
		wxStaticText* StaticText5;
		wxCheckBox* chkDRVBInvertEven;
		wxCheckBox* chkDRVCen;
		wxPanel* Panel7;
		wxStaticLine* StaticLine3;
		wxStaticLine* StaticLine1;
		wxButton* btnConfigureClock;
		wxCheckBox* chkDRVDInvertOdd;
		wxPanel* Panel2;
		wxStaticText* StaticText4;
		wxCheckBox* chkDRVBInvertOdd;
		wxRadioBox* rgrDRVDoutput;
		wxButton* btnConfigureSi5356A;
		wxRadioBox* rgrDRVBoutput;
		wxCheckBox* chkDRVAInvertOdd;
		wxCheckBox* chkDRVCInvertEven;
		//*)

	protected:

		//(*Identifiers(pnlBoard)
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_RADIOBOX5;
		static const long ID_RADIOBOX6;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_CHECKBOX4;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_RADIOBOX1;
		static const long ID_PANEL2;
		static const long ID_CHECKBOX5;
		static const long ID_STATICLINE2;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX6;
		static const long ID_RADIOBOX2;
		static const long ID_PANEL5;
		static const long ID_CHECKBOX7;
		static const long ID_STATICLINE3;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_RADIOBOX3;
		static const long ID_PANEL6;
		static const long ID_CHECKBOX8;
		static const long ID_STATICLINE4;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL5;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_RADIOBOX4;
		static const long ID_PANEL7;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(pnlBoard)
		void OnbtnConfigureSi5356AClick(wxCommandEvent& event);
		void OnbtnLoadFileClick(wxCommandEvent& event);
		void OnbtnConfigureClockClick(wxCommandEvent& event);
		//*)

	protected:
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
