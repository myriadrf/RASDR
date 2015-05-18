#ifndef PNLTXRF_H
#define PNLTXRF_H

//(*Headers(pnlTxRF)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxStaticBoxSizer;
//*)

class pnlTxRF: public wxPanel
{
	public:

		pnlTxRF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles = 0, wxString idname="");
		virtual ~pnlTxRF();

        void FillComboBoxes();
		void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();
        bool UpdateGUI();

		//(*Declarations(pnlTxRF)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxComboBox* cmbICT_TXLOBUF;
		wxCheckBox* chbPD_DRVAUX;
		wxRadioBox* rgrDecode;
		wxCheckBox* chbPwrVga1_I;
		wxCheckBox* chbPD_TXDRV;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxComboBox* cmbPKDBW;
		wxComboBox* cmbVga2G_t;
		wxStaticText* StaticText6;
		wxCheckBox* chbPD_TXLOBUF;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxCheckBox* chbFST_PKDET;
		wxComboBox* cmbENVD;
		wxComboBox* cmbVBCAS_TXDRV;
		wxComboBox* cmbVga1DcI;
		wxRadioBox* rgrPA;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxCheckBox* chbFST_TXHFBIAS;
		wxComboBox* cmbICT_TXDRV;
		wxCheckBox* chbPwrVga2;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxComboBox* cmbVga1G_t;
		wxComboBox* cmbVga1G_u;
		wxComboBox* cmbVga1DcQ;
		wxComboBox* cmbVga2G_u;
		wxComboBox* cmbICT_TXMIX;
		wxCheckBox* chbPD_PKDET;
		wxCheckBox* chbPwrTxRfMods;
		wxStaticText* StaticText12;
		wxRadioBox* rgrLOOPBBEN;
		wxCheckBox* chbPwrVga1_Q;
		wxComboBox* cmbENVD2;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(pnlTxRF)
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT6;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX7;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX9;
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT4;
		static const long ID_COMBOBOX3;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX8;
		static const long ID_COMBOBOX9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX10;
		static const long ID_COMBOBOX11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX12;
		static const long ID_COMBOBOX13;
		//*)

	private:

		//(*Handlers(pnlTxRF)
        void chbPwrTxRfModsClick(wxCommandEvent& event);
        void rgrDecodeClick(wxCommandEvent& event);
        void cmbVga1G_uChange(wxCommandEvent& event);
        void cmbVga1DcIChange(wxCommandEvent& event);
        void cmbVga1DcQChange(wxCommandEvent& event);
        void rgrPAClick(wxCommandEvent& event);
        void cmbVga2G_uChange(wxCommandEvent& event);
        void chbPwrVga1_IClick(wxCommandEvent& event);
        void chbPwrVga2Click(wxCommandEvent& event);
        void cmbVga1G_tChange(wxCommandEvent& event);
        void cmbVga2G_tChange(wxCommandEvent& event);
        void chbPwrVga1_QClick(wxCommandEvent& event);
        void rgrLOOPBBENClick(wxCommandEvent& event);
        void chbPD_DRVAUXClick(wxCommandEvent& event);
        void chbPD_PKDETClick(wxCommandEvent& event);
        void cmbENVDChange(wxCommandEvent& event);
        void cmbENVD2Change(wxCommandEvent& event);
        void cmbPKDBWChange(wxCommandEvent& event);
        void chbFST_PKDETClick(wxCommandEvent& event);
        void chbFST_TXHFBIASClick(wxCommandEvent& event);
        void cmbICT_TXLOBUFChange(wxCommandEvent& event);
        void cmbVBCAS_TXDRVChange(wxCommandEvent& event);
        void cmbICT_TXMIXChange(wxCommandEvent& event);
        void cmbICT_TXDRVChange(wxCommandEvent& event);
        void chbPD_TXLOBUFClick(wxCommandEvent& event);
        void chbPD_TXDRVClick(wxCommandEvent& event);
		//*)

	protected:
        int m_cMAddr;
        int m_cVer;
        int m_cRev;
        int m_cMask;

        bool sendChanges;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
