#ifndef DLGFREQVSCAP_H
#define DLGFREQVSCAP_H

//(*Headers(dlgFreqVsCap)
#include <wx/dialog.h>
class wxPanel;
class wxGrid;
class wxSpinEvent;
class wxFlexGridSizer;
class wxBoxSizer;
class wxSpinCtrl;
class wxButton;
class wxGridEvent;
//*)

#include "CommonFile.h"

class dlgFreqVsCap: public wxDialog
{
	public:

		dlgFreqVsCap(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgFreqVsCap();

		sVcoVsCap sVco1;
        sVcoVsCap sVco2;
        sVcoVsCap sVco3;
        sVcoVsCap sVco4;
        void Initialize(wxString Name);
        int ShowModal();

		//(*Declarations(dlgFreqVsCap)
		wxButton* btnSetVCO2_RFCnt;
		wxButton* OKBtn;
		wxButton* btnSave;
		wxButton* btnViewGrphVCO1;
		wxPanel* Panel4;
		wxButton* btnSetVCO3_RFCnt;
		wxSpinCtrl* txtVCO1Pts;
		wxPanel* Panel1;
		wxSpinCtrl* txtVCO3Pts;
		wxButton* btnSetVCO4_RFCnt;
		wxGrid* grdVco3;
		wxPanel* Panel3;
		wxGrid* grdVco4;
		wxButton* btnViewGrphVCO2;
		wxButton* btnLoad;
		wxButton* CancelBtn;
		wxSpinCtrl* txtVCO2Pts;
		wxButton* btnViewGrphVCO4;
		wxButton* btnSetVCO1_RFCnt;
		wxButton* btnViewGrphVCO3;
		wxGrid* grdVco1;
		wxPanel* Panel2;
		wxGrid* grdVco2;
		wxSpinCtrl* txtVCO4Pts;
		//*)

	protected:

		//(*Identifiers(dlgFreqVsCap)
		static const long ID_SPINCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_GRID1;
		static const long ID_PANEL1;
		static const long ID_SPINCTRL2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_GRID2;
		static const long ID_PANEL2;
		static const long ID_SPINCTRL3;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_GRID3;
		static const long ID_PANEL3;
		static const long ID_SPINCTRL4;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_GRID4;
		static const long ID_PANEL4;
		static const long ID_BUTTON9;
		static const long ID_BUTTON10;
		static const long ID_BUTTON11;
		static const long ID_BUTTON12;
		//*)

        void SetTblRws(int Cnt, wxGrid *grd);
        bool CheckValues(wxGrid *grd);
        void ConstructValues(sVcoVsCap &Vco, wxGrid *grdVco, wxSpinCtrl *VCOPts);
        void DestroyValues(sVcoVsCap &Vco);
        void SavePathToReg(wxString Path);
        wxString ReadPathFromReg();
        void LoadValuesFromFile(wxString FName);
        void ShowVCOValues(sVcoVsCap *Vco, wxGrid *grdVco, wxSpinCtrl *VCOPts);

        wxString m_sName;
        wxString m_sLastUsedVCOFile;


	private:

		//(*Handlers(dlgFreqVsCap)
		void btnSaveClick(wxCommandEvent& event);
		void btnLoadClick(wxCommandEvent& event);
		void OKBtnClick(wxCommandEvent& event);
		void FormDestroy(wxCommandEvent& event);
		void FormShow(wxCommandEvent& event);
		void OnbtnSetVCO1_RFCntClick(wxCommandEvent& event);
		void OnbtnSetVCO2_RFCntClick(wxCommandEvent& event);
		void OnbtnSetVCO3_RFCntClick(wxCommandEvent& event);
		void OnbtnSetVCO4_RFCntClick(wxCommandEvent& event);
		void OnbtnViewGrphVCO1Click(wxCommandEvent& event);
		void OnbtnViewGrphVCO2Click(wxCommandEvent& event);
		void OnbtnViewGrphVCO3Click(wxCommandEvent& event);
		void OnbtnViewGrphVCO4Click(wxCommandEvent& event);
		void OnCancelBtnClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
