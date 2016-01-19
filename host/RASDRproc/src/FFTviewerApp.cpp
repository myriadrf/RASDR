// -----------------------------------------------------------------------------
// FILE:        "FFTviewerApp.cpp"
// DESCRIPTION: "Source Code File"
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
 * Name:      FFTviewerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Lime Microsystems ()
 * Created:   2013-05-08
 * Copyright: Lime Microsystems ()
 * License:
 **************************************************************/
#include "FFTviewerApp.h"
#include <wx/splash.h>
#include <wx/mstream.h>
#include <wx/icon.h>
//(*AppHeaders
#include "FFTviewerMain.h"
#include <wx/image.h>
//*)

//DEFINE_EVENT_TYPE(wxEVT_COMMAND_EXIT_CALL)
//IMPLEMENT_DYNAMIC_CLASS(wxExitEvent,wxNotifyEvent)



IMPLEMENT_APP(FFTviewerApp);
/*
BEGIN_EVENT_TABLE(FFTviewerApp, wxApp)
EventTable(FFTviewerApp)
wxEVT_COMMAND_EXIT_CALL   (wxID_ANY, FFTviewerApp::CloseApp)
END_EVENT_TABLE()
*/

#ifdef WIN32
 wxBitmap* GetBitmapFromMemory(const char* t_data, const DWORD t_size)
  {
     wxMemoryInputStream a_is(t_data, t_size);
     return new wxBitmap(wxImage(a_is, wxBITMAP_TYPE_PNG, -1), -1);
  }

bool LoadDataFromResource(char*& t_data, DWORD& t_dataSize, const wxString& t_name)
  {
     bool     r_result    = false;
     HGLOBAL  a_resHandle = 0;
     HRSRC    a_resource;

     a_resource = FindResource(0, t_name.wchar_str(), RT_RCDATA);

     if(0 != a_resource)
     {
        a_resHandle = LoadResource(NULL, a_resource);
        if (0 != a_resHandle)
        {
           t_data = (char*)LockResource(a_resHandle);
           t_dataSize = SizeofResource(NULL, a_resource);
           r_result = true;
        }
     }

     return r_result;
  }

wxBitmap* CreateBitmapFromPngResource(const wxString& t_name)
{
 wxBitmap*   r_bitmapPtr = 0;

 char*       a_data      = 0;
 DWORD       a_dataSize  = 0;

 if(LoadDataFromResource(a_data, a_dataSize, t_name))
 {
    r_bitmapPtr = GetBitmapFromMemory(a_data, a_dataSize);
 }

 return r_bitmapPtr;
}

#endif

bool FFTviewerApp::OnInit()
{
    #ifdef WIN32
    wxInitAllImageHandlers();
    wxDisableAsserts();
    wxBitmap *splashImage = CreateBitmapFromPngResource("splashImage");
    wxSplashScreen* splash = new wxSplashScreen( *splashImage,
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          6000, NULL, -1, wxDefaultPosition, wxDefaultSize,
          wxSIMPLE_BORDER|wxSTAY_ON_TOP);
//cout << "After Splash started" << endl;
    wxYield();
    #endif
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	FFTviewerFrame* Frame = new FFTviewerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
 //   this->Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,
 //                 wxCommandEventHandler(FFTviewerApp::CloseApp));
    return wxsOK;

}

//Connect(wxID_ANY,wxEVT_EXIT_CALL,(wxObjectEventFunction)&FFTviewerApp::CloseApp);
/*
void FFTviewerApp::CloseApp(wxCommandEvent& event)
{
    Exit();
} */

/*
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
*/
