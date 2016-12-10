#ifndef FRAMEADCGRAPH_H
#define FRAMEADCGRAPH_H

#include <wx/event.h>

class frameADCGraph : public wxFrame
{
    public:
        frameADCGraph(const wxString& title );
        virtual ~frameADCGraph();
    protected:
    private:
            void OnHello(wxCommandEvent& event);
            void OnExit(wxCommandEvent& event);
            void OnAbout(wxCommandEvent& event);
   wxDECLARE_EVENT_TABLE();
};

#endif // FRAMEADCGRAPH_H
