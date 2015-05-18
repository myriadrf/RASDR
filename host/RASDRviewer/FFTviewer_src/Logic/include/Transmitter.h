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
