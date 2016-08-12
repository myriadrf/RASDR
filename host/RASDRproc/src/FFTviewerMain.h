// -----------------------------------------------------------------------------
// FILE:        "FFTviewerMain.h"
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
#include "FFToutSetup.h"
#include "PulsarPnl.h"
//#include "GUI/pnlSamplesGenerator.h"
//#include <errno.h>

//wxInt32 frame_delay; //Default Value - Global Variable

class FFTviewerFrame: public wxFrame
{
   public:

        FFTviewerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FFTviewerFrame();

        static void UpdateInterface(int code, char *param);
        void ShowChipVerRevMask(char ver, char rev, char mask);
        void PrintStatus(const char *msg);
        string DelayStr;
        void term_error(int num);
        bool SaveConfiguration();
        void shutdown();
        void OnFFTfileOKbtnClick(wxCommandEvent& event);
        FFToutSetup *m_fftoutsetup;
        wxFile *m_CFG_FileClassPtr;

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
        void OnFrameDelaySelected(wxCommandEvent& event);
        void OnTuningParametersSelected(wxCommandEvent& event);
        void OnmSpectrumPaint(wxPaintEvent& event);
        void OnMenuItemSaveConfigSelected(wxCommandEvent& event);
//        void OnDispTimeSelected(wxCommandEvent& event);
        void OnFFTCaptureSelected(wxCommandEvent& event);
        void OnRSSParametersSelected(wxCommandEvent& event);
        void OnSetupFFTOut5Selected(wxCommandEvent& event);
        void OnSSetupFFTOutelected(wxCommandEvent& event);
        void OnSetupFFTOutSelected(wxCommandEvent& event);
        void OnSetupPWROut9Selected(wxCommandEvent& event);
        void OnSetupPWROutSelected(wxCommandEvent& event);
        void OnSetupPulsePeriodOutSelected(wxCommandEvent& event);
        void OnSetupPulseTimeDomainOutSelected(wxCommandEvent& event);
        void OnMenuItem12Selected(wxCommandEvent& event);
        void OnSetupDMOutSelected(wxCommandEvent& event);
        void OnSetup_SimSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(FFTviewerFrame)
        static const long ID_PANEL1;
        static const long ID_NOTEBOOK1;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM5;
        static const long ID_MENUITEM6;
        static const long idFrameDelay;
        static const long idTuningParameters;
        static const long ID_MENUITEM4;
        static const long ID_MENUITEM7;
        static const long idRssParameters;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(FFTviewerFrame)
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem7;
        wxNotebook* Notebook1;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem8B;
        wxStatusBar* mStatusBar;
        pnlSpectrum* mSpectrum;
        wxMenu* Menu3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem9;
        wxMenu* Menu5;
        wxMenu* Menu4;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FFTVIEWERMAIN_H
