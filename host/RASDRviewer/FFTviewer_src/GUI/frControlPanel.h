// -----------------------------------------------------------------------------
// FILE:        "frControlPanel.h"
// DESCRIPTION: "Header File"
// DATE:        "05/09/2015 06:44 AM "
// AUTHOR(s):   Lime Microsystems, Paul L. Oxley
// Copyright:   Society of Amateur Radio Astronomers (2014-2015)
//
// Based on original work from Zydrunas Tamosevicius (Lime Microsystems, Ltd.)
// and distributed under the Apache License 2.0 at:
// https://github.com/myriadrf/myriadrf-utils
//
// The RASDRviewer version has been specifically modified for Radio Astronomy
// by Paul L. Oxley for the Society of Amateur Radio Astronomers.  These
// modifications are provided to you under the Gnu Public License version 2.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// REVISIONS:   as appropriate
// -----------------------------------------------------------------------------
#ifndef FRCONTROLPANEL_H
#define FRCONTROLPANEL_H

#include "pnlTop.h"
#include "pnlTxPLL.h"
#include "pnlTxRF.h"
#include "pnlTxLPF.h"
#include "pnlRxLPF.h"
#include "pnlRxVGA2.h"
#include "pnlADDC.h"
#include "pnlBoard.h"
#include "pnlRxFE.h"
#include "pnlRxPLL.h"
#include "pnlCustomer.h"
#include "pnlADF.h"
#include <wx/toolbar.h>
#include "dlgSerPort.h"

//(*Headers(frControlPanel)
#include <wx/frame.h>
class wxPanel;
class wxFileDialog;
class wxStatusBar;
class wxNotebookEvent;
class wxMenuBar;
class wxRichTextCtrl;
class wxNotebook;
class wxMenu;
class wxFlexGridSizer;
class wxToolBar;
//*)

class frControlPanel: public wxFrame
{
	public:

		frControlPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~frControlPanel();

		void FileNew1Execute(wxCommandEvent& event);
        void FileOpen1Execute(wxCommandEvent& event);
        void Save(wxCommandEvent& event);
        void FileExit1Execute(wxCommandEvent& event);
        void HelpAbout1Execute(wxCommandEvent& event);
        void FormCreate(wxCommandEvent& event);
        void mnuAutoDwnldClick(wxCommandEvent& event);
        void mnuReadConfigurationClick(wxCommandEvent& event);
        void tbtnDownloadClick(wxCommandEvent& event);
        void FileSaveAsItemClick(wxCommandEvent& event);
        void mnuRefClkClick(wxCommandEvent& event);

        void ChipGUI1Click(wxCommandEvent& event);
        void mnuSaveRegistersClick(wxCommandEvent& event);
        void ChipGUI2Click(wxCommandEvent& event);
        void CommunicationSettings1Click(wxCommandEvent& event);
        void RegisterTest1Click(wxCommandEvent& event);
        void mnuRegTestLongClick(wxCommandEvent& event);
        void mnuReadRVFClick(wxCommandEvent& event);
        void mnuReadRVF_hexClick(wxCommandEvent& event);
        void mnuReadRVF_rfifClick(wxCommandEvent& event);

        void slLogMesg(char *msg);
        void slLogMesg(int num);
        static void UpdateInterface(int code, char *opt_Msg);
        static int UpdateMessageLog();
        static void ReceivePopUpMessage(char *msg);
        static void ReceiveLogMessage(char *msg);

		//(*Declarations(frControlPanel)
		wxToolBar* ToolBar1;
		pnlCustomer* m_Customer;
		wxToolBarToolBase* ToolBarItem3;
		wxRichTextCtrl* lbMsgs;
		pnlADDC* m_ADDC;
		wxStatusBar* sbMain;
		wxMenuItem* mnuRefClk;
		wxMenuItem* mnuChipToGUI;
		pnlRxFE* m_RxFE;
		wxMenu* Menu3;
		wxMenuItem* mnuSaveAs;
		pnlRxPLL* m_RxPLL;
		pnlTxLPF* m_TxLPF;
		wxToolBarToolBase* tbtnDownload;
		wxFileDialog* dlgOpen;
		pnlTxRF* m_TxRF;
		pnlRxVGA2* m_RxVGA2;
		wxMenu* Menu1;
		wxMenuItem* mnuOpen;
		wxMenuItem* mnuReadRVF_rfif;
		wxToolBarToolBase* ToolBarItem1;
		wxMenuItem* mnuAutoDwnld;
		wxMenuItem* mnuNew;
		pnlADF* m_ADF;
		wxMenuItem* RegisterTest1;
		wxNotebook* pcSPIS;
		pnlTop* m_top;
		pnlTxPLL* m_TxPLL;
		pnlRxLPF* m_RxLPF;
		wxMenuBar* MenuBar1;
		wxMenuItem* CommunicationSettings1;
		pnlBoard* m_Board;
		wxMenu* Menu2;
		wxToolBarToolBase* ToolBarItem2;
		wxMenuItem* mnuSave;
		//*)

	protected:

		//(*Identifiers(frControlPanel)
		static const long ID_PANEL2;
		static const long ID_PANEL3;
		static const long ID_PANEL4;
		static const long ID_PANEL5;
		static const long ID_PANEL6;
		static const long ID_PANEL7;
		static const long ID_PANEL8;
		static const long ID_PANEL9;
		static const long ID_PANEL10;
		static const long ID_PANEL11;
		static const long ID_PANEL13;
		static const long ID_PANEL1;
		static const long ID_NOTEBOOK1;
		static const long ID_RICHTEXTCTRL1;
		static const long ID_MENUITEM1;
		static const long ID_MENUITEM2;
		static const long ID_MENUITEM3;
		static const long ID_MENUITEM4;
		static const long ID_MENUITEM9;
		static const long ID_MENUITEM10;
		static const long ID_MENUITEM5;
		static const long ID_MENUITEM6;
		static const long ID_MENUITEM7;
		static const long ID_MENUITEM8;
		static const long ID_TOOLBARITEM1;
		static const long ID_TOOLBARITEM2;
		static const long ID_TOOLBARITEM3;
		static const long ID_TOOLBARITEM4;
		static const long ID_TOOLBAR1;
		static const long ID_STATUSBAR1;
		//*)

	private:

		//(*Handlers(frControlPanel)
		void OnmnuNewSelected(wxCommandEvent& event);
		void OnmnuOpenSelected(wxCommandEvent& event);
		void OnmnuSaveSelected(wxCommandEvent& event);
		void OnmnuSaveAsSelected(wxCommandEvent& event);
		void OnmnuAutoDwnldSelected(wxCommandEvent& event);
		void OnCommunicationSettings1Selected(wxCommandEvent& event);
		void OnRegisterTest1Selected(wxCommandEvent& event);
		void OnmnuAboutSelected(wxCommandEvent& event);
		void OntbtnDownloadClicked(wxCommandEvent& event);
		void OnmnuAutoDwnldSelected1(wxCommandEvent& event);
		void OnCommunicationSettings1Selected1(wxCommandEvent& event);
		void OnmnuRefClkSelected1(wxCommandEvent& event);
		void OnmnuChipToGUISelected(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnpcSPISPageChanging(wxNotebookEvent& event);
		void OnmnuReadRVFSelected(wxCommandEvent& event);
		void OnmnuReadRVF_hexSelected(wxCommandEvent& event);
		void OnmnuReadRVF_rfifSelected(wxCommandEvent& event);
		void OnmnuSaveRegistersSelected(wxCommandEvent& event);
		void Onm_CustomerPaint(wxPaintEvent& event);
		//*)

		dlgSerPort *dSerPort;

        bool sendChanges;
        wxString m_sFileName;

        void setCurrentFileName(wxString fileName);
        void EnableAllSPIClocks();
        void EnableSPIClockByMask(int Mask);
        void RestoreAllSPIClocks();
        void SetLnaChain(int iChain);
        void SetBypassLoopback();
        bool TestRegisters();
        bool TestRegistersTrial();
        void CalLPFCore();

        bool FileIsNotEmpty(wxString filename);
        void LoadConfiguration(wxString sIniName);

        void ShowReferenceClk(double Val);
        void SaveRefClkToReg(double Freq);
        double ReadRefClkFromReg(void);

        void LoadAdditionalSettings();
        void UpdateVerRevMask();
        void DevicesChanged();

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
