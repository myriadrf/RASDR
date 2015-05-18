// -----------------------------------------------------------------------------
// FILE:        "GUIUtils.cpp"
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
