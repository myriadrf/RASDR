// -----------------------------------------------------------------------------
// FILE:        "Transmitter.h"
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
// -----------------------------------------------------------------------------
// FILE: 		Transmitter.h
// DESCRIPTION:	Header for Transmitter.cpp
// DATE:		2013-08-12
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <vector>
#include <pthread.h>
#include <string>
using namespace std;

class Main_Module;
class ConnectionManager;

class Transmitter
{
    public:
        Transmitter(Main_Module *pMainModule);
        ~Transmitter();

        void StartSendingSamples();
        void StopSendingSamples();

        void LoadSamplesFromFile(string filename, bool binary = false);
        void GenerateSamples(double freq, double amplitude, double samplingRate);
        void GetSamples(float *Ichannel, float *Qchannel, int &samplesCount);
        void SetPlaybackPattern(unsigned char* array, long length);
    private:
        unsigned long m_bytesXferred;
        unsigned long m_transmitErrors;
        unsigned long m_packetsSent;
        ConnectionManager *device;
        void Transmit();
        static void* transmitThreadEntry(void *pTransmitter);
        pthread_t m_transmitThreadID;

        Main_Module *p_main;
        bool working;
        vector<int> m_Isamples;
        vector<int> m_Qsamples;
        bool transmittingPattern;
        vector<unsigned char> pattern;
};


#endif // TRANSMITTER_H
