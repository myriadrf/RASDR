/***************************************************************
 * Name:      FFTviewerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2013-05-08
 * Copyright: Lime Microsystems ()
 * License:
 **************************************************************/

#ifndef FFTVIEWERMAIN_H
#define FFTVIEWERMAIN_H

//(*Headers(FFTviewerFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "GUI/frControlPanel.h"
#include "GUI/pnlSpectrum.h"
#include "GUI/pnlSamplesGenerator.h"

class FFTviewerFrame: public wxFrame
{
    public:

        FFTviewerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FFTviewerFrame();

        static void UpdateInterface(int code, char *param);
        void ShowChipVerRevMask(char ver, char rev, char mask);
        void PrintStatus(const char *msg);

    private:

        frControlPanel *m_ControlPanel;
        static const long ID_CONTROL_PANEL;
        //(*Handlers(FFTviewerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnMenuItem7Selected(wxCommandEvent& event);
        void OnMenuReadSettingsSelected(wxCommandEvent& event);
        void OnMenuSendSettingsSelected(wxCommandEvent& event);
        void OnMenuStartCaptureSelected(wxCommandEvent& event);
        void OnMenuStopCaptureSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(FFTviewerFrame)
        static const long ID_PANEL1;
        static const long ID_PANEL2;
        static const long ID_NOTEBOOK1;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM4;
        static const long ID_MENUITEM5;
        static const long ID_MENUITEM6;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(FFTviewerFrame)
        wxMenuItem* MenuItem7;
        wxNotebook* Notebook1;
        wxMenuItem* MenuItem5;
        wxStatusBar* mStatusBar;
        pnlSpectrum* mSpectrum;
        wxMenu* Menu3;
        wxMenuItem* MenuItem4;
        pnlSamplesGenerator* mTransmitter;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem6;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FFTVIEWERMAIN_H
