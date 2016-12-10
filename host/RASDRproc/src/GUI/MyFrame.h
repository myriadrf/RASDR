#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyFrame: public wxFrame

{

 public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnHello(wxCommandEvent& event);
  wxPanel* GetPanel();
};
