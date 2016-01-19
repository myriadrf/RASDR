// -----------------------------------------------------------------------------
// FILE:        "FFTviewerApp.h"
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
 * Name:      FFTviewerApp.h
 * Purpose:   Defines Application Class
 * Author:    Lime Microsystems ()
 * Created:   2013-05-08
 * Copyright: Lime Microsystems ()
 * License:
 **************************************************************/

#ifndef FFTVIEWERAPP_H
#define FFTVIEWERAPP_H
#include <wx/app.h>

class FFTviewerApp : public wxApp
{
    public:
        virtual bool OnInit();
        void CloseApp(wxCommandEvent& event);

 //       DECLARE_EVENT_TABLE()
};

class wxExitEvent : public wxNotifyEvent
{
    public:
    wxExitEvent(wxEventType commandType = wxEVT_NULL,
                int id =0 ) : wxNotifyEvent(commandType,id)
                {}
    wxExitEvent(const wxExitEvent& event) : wxNotifyEvent(event)
            {}
            virtual wxEvent *Clone() const
            {  return new wxExitEvent(*this); }
DECLARE_DYNAMIC_CLASS(wxExitEvent);
};

typedef void (wxEvtHandler :: *wxExitEventFunction)
    (wxExitEvent&);
BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_COMMAND_EXIT_CALL,801)
END_DECLARE_EVENT_TYPES()

#define EVT_COMMAND_EXIT_CALL(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_EXIT_CALL, id, -1, (wxObjectEventFunction)(wxEventFunction) (wxExitCtrlEventFunction) & fn, (wxObject *) NULL ) ,

#endif // FFTVIEWERAPP_H
