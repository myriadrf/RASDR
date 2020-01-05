// -----------------------------------------------------------------------------
// FILE: 		Transmitter.cpp
// DESCRIPTION:	implements samples transmitting
// DATE:		2013-07-17
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "Transmitter.h"
#include <math.h>
#include <iostream>
#include "ConnectionManager.h"
#include "Main_Module.h"
#include "TimeCounter.h"
#include "CyAPI.h"
using namespace std;

/**
    @brief Creates transmitter module
    @param pMainModule pointer to main module
*/
Transmitter::Transmitter(Main_Module* pMainModule)
{
    transmittingPattern = false;
    working = false;
    p_main = pMainModule;
    device = p_main->getSerPort();
    GenerateSamples(5, 1024, 20);
}

/**
    @brief ~Transmitter
*/
Transmitter::~Transmitter()
{

}

/**
    @brief Starts transmitting samples data
*/
void Transmitter::StartSendingSamples()
{
    if(!working)
    {
        working = true;
        pthread_create(&m_transmitThreadID, NULL, transmitThreadEntry, this);
    }
}

/**
    @brief Stops samples transmitting
*/
void Transmitter::StopSendingSamples()
{
    working = false;
    //pthread_cancel(m_transmitThreadID);
}

/**
    @brief Loads I and Q samples data from file
    @param filename file containing samples data
    @param binary set true if file is in binary format
*/
void Transmitter::LoadSamplesFromFile(string filename, bool binary)
{
    transmittingPattern = false;
    fstream fin;
    m_Isamples.clear();
    m_Qsamples.clear();
    double sample;
    if(binary)
    {
        fin.open(filename.c_str(), ios::in | ios::binary);
        while( !fin.eof() )
        {
            fin.read((char*)&sample, sizeof(double));
            m_Isamples.push_back(sample);
            fin.read((char*)&sample, sizeof(double));
            m_Qsamples.push_back(sample);
        }
    }
    else
    {
        fin.open(filename.c_str(), ios::in);
        while( !fin.eof() )
        {
            fin >> sample;
            m_Isamples.push_back(sample);
            fin >> sample;
            m_Qsamples.push_back(sample);
        }
    }

    fin.close();
}

/**
    @brief Generates sinus data samples for I and Q channels
*/
void Transmitter::GenerateSamples(double freq, double amplitude, double samplingRate)
{
    transmittingPattern = false;
    m_Isamples.clear();
    m_Qsamples.clear();
    double period = 1/freq;
    double angularFreq = (2*3.141596)/period;
    double timeStep = 1/samplingRate;

    int currSample = 0;
    //generate one period of samples
    double t=0;
    cout << endl;
    cout << "generated samples" << endl;
    for(int i=0; i<period/timeStep; i++)
    {
        currSample = (sin(angularFreq*t) * amplitude);
        m_Isamples.push_back(currSample);
        cout << currSample << endl;
        t+=timeStep;
    }
    cout << endl;
    for(int i=m_Isamples.size()/4; i<m_Isamples.size()+m_Isamples.size()/4; i++)
    {
        m_Qsamples.push_back( m_Isamples[i%m_Isamples.size()] );
    }
}

/**
    @brief Sets byte pattern to transmit
    @param array byte pattern that will be repeated
    @param length size of given array
*/
void Transmitter::SetPlaybackPattern(unsigned char* array, long length)
{
    transmittingPattern = true;
    pattern.clear();
    for(int i=0; i<length; ++i)
        pattern.push_back(array[i]);
}

/**
    @brief Transmits I and Q data samples
*/
void Transmitter::Transmit()
{
    m_bytesXferred = 0;
    m_transmitErrors = 0;
    m_packetsSent=0;

    bool iq_select = 0;

    int probePos = 0;
    int bufPos = 0;

    int QueueSize = 16;
    int QueueSizeMask = QueueSize-1;
    /*int* contexts = new int[QueueSize];*/

    CCyUSBDevice *usbdev;
    usbdev = new CCyUSBDevice(NULL);

    CCyUSBEndPoint *outEndPt;

    usbdev->Open(0);
    bool endptfound = false;
    if(usbdev->IsOpen())
    {
        for(int i=0; i<usbdev->EndPointCount(); ++i)
        {
            if( usbdev->EndPoints[i]->Address == 0x01)
            {
                outEndPt =  usbdev->EndPoints[i];
                endptfound = true;
                break;
            }
        }
    }
    if(!endptfound)
    {
        cout << "transmitter end point not found " << endl;
        return;
    }

    long t1_info, t2_info;
    t1_info = GetTickCount();

    //PUCHAR			*buffers		= new PUCHAR[QueueSize];
    //CCyIsoPktInfo	**isoPktInfos	= new CCyIsoPktInfo*[QueueSize];
    PUCHAR			*contexts		= new PUCHAR[QueueSize];
    OVERLAPPED		inOvLap[QueueSize];

    //int bufSize = 512*64;
    int bufSize = outEndPt->MaxPktSize*128;
    cout << "Max packet size = " << outEndPt->MaxPktSize << endl;
    long sendLen = bufSize;
    long len = bufSize; // Each xfer request will get PPX isoc packets
    cout << "Setting xfer size = " << len << endl;
    outEndPt->SetXferSize(len);
    unsigned char** buffers = new unsigned char*[QueueSize];
	unsigned char tempbuffer[bufSize];
	memset(tempbuffer, 0, bufSize);

    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);           // 100-nanosecond intervals since January 1, 1601 (UTC)
    //srand( time(NULL) );
    srand( ft.dwLowDateTime );

    long patternPos = 0;
    int patternSize = pattern.size();

    for (int b = 0; b < QueueSize; b++)
    {
        fstream fout;
        fout.open("OutgoingData.txt", ios::out);
		buffers[b] = new unsigned char[bufSize];
		memset(buffers[b], 0, bufSize);
		if(transmittingPattern)
            for(int j=0; j<bufSize; ++j)
            {
                buffers[b][j] = pattern[patternPos];
                patternPos = (patternPos+1) % patternSize;
            }
        else
        {
            if(transmittingPattern)
                for(int j=0; j<bufSize; ++j)
                {
                    buffers[b][j] = pattern[patternPos];
                    patternPos = (patternPos+1) % patternSize;
                }
            else
            for(int i=0; i<bufSize; i+=4)
            {
                //currsample = m_Isamples[probePos % m_Isamples.size()];
                buffers[b][i+1] = (m_Isamples[probePos % m_Isamples.size()] >> 8) & 0x0F;
                buffers[b][i+1] |= ((unsigned int)iq_select << 4);
                iq_select = !iq_select;
                buffers[b][i] = (m_Isamples[probePos % m_Isamples.size()]) & 0xFF;
                //currsample = m_Qsamples[probePos % m_Qsamples.size()];
                buffers[b][i+3] = (m_Qsamples[probePos % m_Qsamples.size()] >> 8) & 0x0F;
                buffers[b][i+3] |= ((unsigned int)iq_select << 4);
                iq_select = !iq_select;
                buffers[b][i+2] = (m_Qsamples[probePos % m_Qsamples.size()]) & 0xFF;
                probePos++;
            }
        }
        fout.write((const char*)buffers[b], sendLen);
        fout.close();

        //memcpy(tempbuffer, buffers[i], bufSize);
    }


    for (int i=0; i< QueueSize; i++)
    {
        //isoPktInfos[i]    = new CCyIsoPktInfo[64];
        inOvLap[i].hEvent = CreateEvent(NULL, false, false, NULL);
        //memset(buffers[i], 0,len);
    }

    int currsample = 0;

    sendLen = len;

    //fstream fout;
    //fout.open("DataStreamingOut.txt", ios::out | ios::binary);
    //fout.write( (const char*)buffers[0], sendLen);
    //fout.close();

    for(int i=0; i<QueueSize; ++i)
        //contexts[i] = device->BeginDataSending(buffers[i], sendLen);
        contexts[i] = outEndPt->BeginDataXfer(buffers[i], sendLen, &inOvLap[i]);

	cout << "TRANSMIT START" << endl;
	iq_select = 0;
    int b = 0;
    working = true;
    while(working)
    {
        sendLen = bufSize;
        /*if(!device->WaitForSending(contexts[b], 1000))
        {
            ++m_transmitErrors;
        }*/
        if (!outEndPt->WaitForXfer(&inOvLap[b], 1000))
        {
            //outEndPt->Abort();
            ++m_transmitErrors;
        }

        /*if (device->FinishDataSending(buffers[b], sendLen, contexts[b]))
  		{
            ++m_packetsSent;
            m_bytesXferred += sendLen;
		}
		else
            ++m_transmitErrors;
        */

        if (outEndPt->FinishDataXfer(buffers[b], sendLen, &inOvLap[b], contexts[b]))
        {
            m_bytesXferred += sendLen;
            //cout <<" packet sent: bytes = " << sendLen << endl;
            ++m_packetsSent;
        }
        else
            ++m_transmitErrors;

        sendLen = bufSize;

        /*if(transmittingPattern)
            for(int j=0; j<bufSize; ++j)
            {
                buffers[b][j] = pattern[patternPos];
                patternPos = (patternPos+1) % patternSize;
            }
        else
            for(int i=0; i<bufSize; i+=4)
            {
                //currsample = m_Isamples[probePos % m_Isamples.size()];
                buffers[b][i+1] = (m_Isamples[probePos % m_Isamples.size()] >> 8) & 0x0F;
                buffers[b][i+1] |= ((unsigned int)iq_select << 4);
                iq_select = !iq_select;
                buffers[b][i] = (m_Isamples[probePos % m_Isamples.size()]) & 0xFF;
                //currsample = m_Qsamples[probePos % m_Qsamples.size()];
                buffers[b][i+3] = (m_Qsamples[probePos % m_Qsamples.size()] >> 8) & 0x0F;
                buffers[b][i+3] |= ((unsigned int)iq_select << 4);
                iq_select = !iq_select;
                buffers[b][i+2] = (m_Qsamples[probePos % m_Qsamples.size()]) & 0xFF;
                probePos++;
            }*/
        contexts[b] = outEndPt->BeginDataXfer(buffers[b], sendLen, &inOvLap[b]);
        //contexts[b] = device->BeginDataSending(buffers[b], sendLen);

        b++;
        b = b % QueueSize;

        t2_info = GetTickCount();
		if (t2_info - t1_info > 1000) // each second display info and update data rate
		{

			long deltaT = (t2_info - t1_info);
			if (deltaT <= 0)
			{
				deltaT = 1;
				m_bytesXferred = 0;
			}
			long m_bytesPerSecond = (m_bytesXferred / 1024) / (deltaT/1000.0); // / 1000;


			cout << "\nSending Rate: " << m_bytesPerSecond << "  KB/s  " << endl;
			cout << "Failures: " << m_transmitErrors << endl;
			cout << " Packets Sent: " << m_packetsSent << endl;
            m_bytesXferred = 0;
			m_packetsSent = 0;
			m_transmitErrors = 0;
			t1_info = t2_info;
		}
    }
    //device->AbortSending();
    for(int i=0; i<QueueSize; i++)
    {
        sendLen = bufSize;
        outEndPt->WaitForXfer(&inOvLap[i], 1000);
        outEndPt->FinishDataXfer(buffers[i], sendLen, &inOvLap[i], contexts[i]);
        //device->WaitForSending(contexts[i], 100);
        //device->FinishDataSending(buffers[i], sendLen, contexts[i]);
        delete []buffers[i];
    }
	cout << "TRANSMIT STOP" << endl;
    delete []buffers;
    delete []contexts;
}

/**
    @brief Transmitting thread entry point
    @param pTransmitter pointer to transmitter module
*/
void* Transmitter::transmitThreadEntry(void *pTransmitter)
{
    if(pTransmitter != NULL)
        reinterpret_cast<Transmitter*>(pTransmitter)->Transmit();
    return NULL;
}

/**
    @brief Returns samples that are currently ready for transmitting
    @param Ichannel array for I channel data
    @param Qchannel array for Q channel data
    @param samplesCount number of samples returned for I and Q channels
*/
void Transmitter::GetSamples(float *Ichannel, float *Qchannel, int &samplesCount)
{
    if(Ichannel && Qchannel)
    {
        for(int i=0; i<m_Isamples.size(); i++)
        {
            Ichannel[i] = m_Isamples[i];
            Qchannel[i] = m_Qsamples[i];
        }
    }
    samplesCount = m_Isamples.size();
}
