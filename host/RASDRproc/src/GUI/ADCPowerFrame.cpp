#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class ADCPowerFrame: public wxFrame

{

 public:
  ADCPowerFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnHello(wxCommandEvent& event);
  wxPanel* GetPanel();
  wxSizer* GetSizer();
 private:
    wxPanel *panel;
    wxSizer *sizer;
};


enum
{
    ID_Hello = 1
};
ADCPowerFrame::ADCPowerFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    panel = new wxPanel(this,  wxID_ANY);
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    //SetStatusText( "Welcome to wxWidgets!" );

    //sizer = new wxBoxSizer(wxVERTICAL);
    //panel->SetSizer(sizer);
    //sizer->SetSizeHints(this);
}

wxSizer* ADCPowerFrame::GetSizer() {
    return sizer;
}

wxPanel* ADCPowerFrame::GetPanel() {
    return panel;
}
void ADCPowerFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
    Destroy();
}
void ADCPowerFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void ADCPowerFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
