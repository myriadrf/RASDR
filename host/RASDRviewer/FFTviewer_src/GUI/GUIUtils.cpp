#include "GUIUtils.h"

#include <wx/msgdlg.h>
#include <fstream>
using namespace std;
void ShowMessage(wxString msg)
{
    wxMessageDialog *dlg;
    dlg = new wxMessageDialog(NULL, msg, "Message", wxOK);
    dlg->ShowModal();
    delete dlg;
}

bool FileExists(wxString filename)
{
    fstream fin;
    fin.open(filename, ios::in);
    fin.peek();
    if(fin.good())
        return true;
    else
        return false;
}

void milSleep(long miliseconds)
{
#ifdef WIN32
    Sleep(miliseconds);
#else
    usleep(miliseconds*1000);
#endif // WIN32
}
