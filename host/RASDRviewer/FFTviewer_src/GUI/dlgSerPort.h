#ifndef DLGSERPORT_H
#define DLGSERPORT_H

//(*Headers(dlgSerPort)
#include <wx/dialog.h>
class wxComboBox;
class wxStaticLine;
class wxRadioBox;
class wxFlexGridSizer;
class wxButton;
//*)

class dlgSerPort: public wxDialog
{
	public:

		dlgSerPort(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgSerPort();

		//(*Declarations(dlgSerPort)
		wxButton* btnClose;
		wxButton* btnCancel;
		wxComboBox* cmbComPorts;
		wxRadioBox* rgrBaud;
		wxComboBox* cmbUSBDevices;
		wxRadioBox* rgrPortSelection;
		wxStaticLine* StaticLine1;
		//*)

	protected:

		//(*Identifiers(dlgSerPort)
		static const long ID_RADIOBOX1;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_RADIOBOX2;
		static const long ID_STATICLINE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:
	    void FormShow();
        wxString m_sComName;
        int m_iBaud;
        int connectionType;

        int Code2Baud(int Code);
        int Baud2Code(int baudrate);
        void LoadFromIni();
        void SaveToIni();
        void GetConnectionInfo();
		//(*Handlers(dlgSerPort)
		void OnbtnCloseClick(wxCommandEvent& event);
		void OnrgrPortSelectionSelect(wxCommandEvent& event);
		void OnrgrBaudSelect(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
