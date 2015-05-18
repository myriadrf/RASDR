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

IMPLEMENT_APP(FFTviewerApp);

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
    return wxsOK;

}
