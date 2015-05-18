// -----------------------------------------------------------------------------
// FILE:        "pnlSamplesGenerator.cpp"
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
#include "pnlSamplesGenerator.h"
#include "ctr_6002dr2_LogicDLL.h"

#include <sstream>
using namespace std;

//(*InternalHeaders(pnlSamplesGenerator)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlSamplesGenerator)
//*)

BEGIN_EVENT_TABLE(pnlSamplesGenerator,wxPanel)
	//(*EventTable(pnlSamplesGenerator)
	//*)
END_EVENT_TABLE()

pnlSamplesGenerator::pnlSamplesGenerator(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString str)
{
    m_isamples = NULL;
    m_qsamples = NULL;
    m_xaxis = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlSamplesGenerator::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlSamplesGenerator)
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(913,263), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	//*)

	glSignalGraph->settings.useVBO = false;
    glSignalGraph->AddSeries();
    glSignalGraph->AddSeries();
    glSignalGraph->SetInitialDisplayArea(0, 128, -2048, 2048);
    glSignalGraph->settings.marginLeft = 80;
    glSignalGraph->settings.marginBottom = 35;
    glSignalGraph->settings.title = "IQ samples";
    glSignalGraph->series[0]->color = 0xFF0000FF;
    glSignalGraph->series[1]->color = 0x0000FFFF;
}

pnlSamplesGenerator::~pnlSamplesGenerator()
{
	//(*Destroy(pnlSamplesGenerator)
	//*)
}

void pnlSamplesGenerator::OnrgrDataSourceSelect(wxCommandEvent& event)
{
    switch( rgrDataSource->GetSelection() )
    {
    case 0:
        btnOpenFile->SetLabel("Generate");
        break;
    case 1:
        btnOpenFile->SetLabel("Open file");
        break;
    case 2:
        btnOpenFile->SetLabel("Open file");
        break;
    case 3:
        btnOpenFile->SetLabel("Generate");
        break;
    }
}



void pnlSamplesGenerator::OnbtnStartGeneratingClick(wxCommandEvent& event)
{
    if( rgrDataSource->GetSelection() == 4)
    {
        vector<unsigned char> pattern;
        unsigned int sample = 0;
        stringstream ss;
        ss.str( txtHexInput->GetValue().ToStdString() );
        while(!ss.eof())
        {
            ss >> hex >> sample;
            pattern.push_back(sample&0xFF);
        }
        LMLL_Transmitter_LoadSamplesFromArray(&pattern[0], pattern.size());
    }
    LMLL_Transmitter_StartSendingSamples();
}

void pnlSamplesGenerator::OnbtnStopGeneratingClick(wxCommandEvent& event)
{
    LMLL_Transmitter_StopSendingSamples();
}

void pnlSamplesGenerator::OnbtnOpenFileClick(wxCommandEvent& event)
{
    if( rgrDataSource->GetSelection() == 0)
    {
        double freq = 0;
        txtFreq->GetValue().wxString::ToDouble(&freq);
        double amp = 0;
        amp = spinAmplitude->GetValue();
        double samplingRate = 0;
        samplingRate = spinSamplingRate->GetValue();
        LMLL_Transmitter_GenerateSamples( freq, amp, samplingRate);
    }
    else if( rgrDataSource->GetSelection() == 3)
    {
        LMLL_Transmitter_GenerateSamples( 4, 2048, 16);
    }
    else
    {
        wxFileDialog *openFileDialog = new wxFileDialog(this, _("Open samples file"), "", "", "txt (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        if (openFileDialog->ShowModal() == wxID_CANCEL)
            return;

        if(rgrDataSource->GetSelection() == 1)
            LMLL_Transmitter_LoadSamplesFromFile( (char*)openFileDialog->GetPath().ToStdString().c_str(), false);
        else if(rgrDataSource->GetSelection() == 2)
            LMLL_Transmitter_LoadSamplesFromFile( (char*)openFileDialog->GetPath().ToStdString().c_str(), true);
    }
    if(m_isamples)
        delete m_isamples;
    if(m_qsamples)
        delete m_qsamples;
    if(m_xaxis)
        delete m_xaxis;

    int samplesCount = 0;
    LMLL_Transmitter_GetSamples(NULL, NULL, samplesCount);
    m_isamples = new float[samplesCount];
    m_qsamples = new float[samplesCount];
    m_xaxis = new float[samplesCount];
    for(int i=0; i<samplesCount; i++)
        m_xaxis[i] = i;
    LMLL_Transmitter_GetSamples(m_isamples, m_qsamples, samplesCount);
    glSignalGraph->series[0]->AssignValues(m_xaxis, m_isamples, samplesCount);
    glSignalGraph->series[1]->AssignValues(m_xaxis, m_qsamples, samplesCount);
    glSignalGraph->Draw();
}

void pnlSamplesGenerator::OnPanel3Paint(wxPaintEvent& event)
{
}

void pnlSamplesGenerator::OnPaint(wxPaintEvent& event)
{
}
