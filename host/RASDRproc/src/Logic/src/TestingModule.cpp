// -----------------------------------------------------------------------------
// FILE: 		TestingModule.h
// DESCRIPTION:	Module designed for reading data samples from board
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "TestingModule.h"
#include "..\globals.h"
#ifdef WIN32


#include "windows.h"
#else
#include <unistd.h>
#include <libusb-1.0/libusb.h>
#include "TimeCounter.h"
#endif

#include <cmath>
#include <string>
#include <string.h>
#include <iostream>
#include <iomanip>
#include "Main_Module.h"
#include "ConnectionManager.h"
#include "fftw3.h"
#include "CallbackCodes.h"
#include <stdio.h>
#include <pthread.h>
//#include "globals.h"
#include "socket.h"     // for sockets code
#include <float.h>      // for FLT_MIN, FLT_MAX

pthread_t readThreadID;
pthread_t calculateThreadID;    // huh... not used.. it could be...
pthread_t transmitThreadID;


using namespace std;

// Comands
// I2C FPGA
#define CFG_ADDR 0xAA
#define CMD_CFG_I2C_WR 0x14
#define CMD_CFG_I2C_RD 0x15

// LMS6002D
#define CMD_LMS_WR 0x16
#define CMD_LMS_RD 0x17

// I2C Si5356A
#define FSN_ADDR 0xE0
#define CMD_FSN_I2C_WR 0x24
#define CMD_FSN_I2C_RD 0x25


#define SI5338_DELAY 12 //12ms
#define LOCK_MASK 0x19
#define LOS_MASK 0x08


/**
	@brief Allocates memory needed for I,Q channel samples and FFT data
 */

 extern int g_frame_delay; //Global variable

TestingModule::TestingModule(Main_Module *pMainModule)
{
    m_swapIQ = false;
    m_frameStart = 0;
    m_hwDigiRed = false;
    m_SamplesFIFO = NULL;
    m_fftFIFO = NULL;
    m_fftAvgFIFO = NULL;
    m_fftCalcIn = NULL;
    m_fftCalcOut = NULL;
    //fftwf_import_wisdom_from_filename("fftw_wisdom.bin");

	pMain = pMainModule;
	updateInterfaceCallback = NULL;

	m_FPGA_Rx_enabled = true;
	m_FPGA_Tx_enabled = true;
	m_FPGA_RXSRC_ADC = false;
	m_FPGA_TXSRC_ADC = true;

	readingData = false;
	transmitActive = false;
	m_bytesPerSecond = 0;
	m_ulFailures = 0;
	m_bufferFailures = 0;

    countFFT = 0;
	FFTsamples = 0;
	samplingFrequency = 10000000; // Hz

	m_DCcorrectionOnOff = 1;
	device = NULL;

    initializeFFTplan(16384);       // TODO: coordinate with pnlSpectrum.cpp, Packets.h, TestingModule.h/.cpp, globals.cpp and pnlSpectrum.wxs
    initializeFIFO(DIGIGREEN_SPLIT_PACKET_SIZE, FFTsamples);

    // Support for RSS Integration
    socket_init();
}

/**
    @brief Initializes buffers for samples data and fft calculations data
    @param samplesSize size of samples packet
    @param fftSize size of fft packet
*/
void TestingModule::initializeFIFO(int samplesSize, int fftSize)
{
    if(m_SamplesFIFO)
    {
        if(m_SamplesFIFO->m_packetSize != samplesSize)
        {
            delete m_SamplesFIFO;
            m_SamplesFIFO = new blockingFIFO<SplitPacket>(32, samplesSize);
        }
    }
    else
        m_SamplesFIFO = new blockingFIFO<SplitPacket>(32, samplesSize);

    if(m_fftFIFO)
    {
        if(m_fftFIFO->m_packetSize != fftSize)
        {
            delete m_fftFIFO;
            m_fftFIFO = new blockingFIFO<FFTPacket>(32, fftSize);
        }
    }
    else
        m_fftFIFO = new blockingFIFO<FFTPacket>(32, fftSize);

    if(m_fftAvgFIFO)
    {
        if(m_fftAvgFIFO->m_packetSize != fftSize)
        {
            delete m_fftAvgFIFO;
            m_fftAvgFIFO = new blockingFIFO<FFTAvgPacket>(32, fftSize);
        }
    }
    else
        m_fftAvgFIFO = new blockingFIFO<FFTAvgPacket>(32, fftSize);
}

/**
    @brief Initializes FFT plan and data buffers for given samples count
    @param samplesCount number of samples used in FFT
*/
void TestingModule::initializeFFTplan(int samplesCount)
{
    if(samplesCount != FFTsamples)
    {
        if(m_fftCalcIn)
            fftwf_free(m_fftCalcIn);
        m_fftCalcIn = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * samplesCount);
        if(m_fftCalcOut)
            fftwf_free(m_fftCalcOut);
        m_fftCalcOut = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * samplesCount);

        m_fftCalcPlan = fftwf_plan_dft_1d(samplesCount, m_fftCalcIn, m_fftCalcOut,
            FFTW_FORWARD, FFTW_MEASURE);

        FFTsamples = samplesCount;
    }
}

/**
	@brief Dealocates used memory.
 */
TestingModule::~TestingModule()
{
    // Support for RSS Integration
    socket_fini();

	delete m_SamplesFIFO;
	delete m_fftFIFO;
	delete m_fftAvgFIFO;
}

/**
	@brief Initiates realtime data reading and calculating.
 */
void TestingModule::StartSdramRead()
{
	// if reading is not in progress reset all counters
	if (!readingData)
	{
		// allocate needed memory
		bool DigiRed = false;
        char val = 0;
        device->GetCustomParameter("HW_DigiRed", &val);
        DigiRed = val;
        if(DigiRed)
        {
            m_hwDigiRed = true;
            int maxPacketSize = 0;
            device->GetCustomParameter("MaxPacketSize", &maxPacketSize);

            if(maxPacketSize == 512)
                initializeFIFO(DIGIRED_SPLIT_PACKET_SIZE/2, FFTsamples);
            else
                initializeFIFO(DIGIRED_SPLIT_PACKET_SIZE*4, FFTsamples);
            initializeFFTplan(FFTsamples);
        }
        else
        {
            m_hwDigiRed = false;
            initializeFIFO(DIGIGREEN_SPLIT_PACKET_SIZE, FFTsamples);
            initializeFFTplan(FFTsamples);
        }

		SelectRxSource(m_FPGA_RXSRC_ADC);
		EnableFPGA(false, m_FPGA_Tx_enabled);
		FPGAResetOn();
		USBFIFOReset();
		FPGAResetOff();
		EnableFPGA(true, m_FPGA_Tx_enabled);

		readingData = true;
        transmitActive = false; // this will tell us if we have to join the TransmitSpectraThread
		pthread_create(&readThreadID, NULL, ReadDataThread, this);
		if( g_RSS_Enable )
		{
		    transmitActive = true;
		    m_svr = -1;
            pthread_create(&transmitThreadID, NULL, TransmitSpectraThread, this);
		}
	}
}

/**
	@brief Stops realtime data receiving and calculating.
 */
void TestingModule::StopSdramRead()
{
	// disable data receiving and wait for other thread to exit
	if(readingData)
    {
        void *status = NULL;
        int r;

        readingData = false;    // this is supposed to signal the threads to exit...

        //need to unblock fifo in case other thread was waiting for data
        m_SamplesFIFO->unblock();
        m_fftFIFO->unblock();
        m_fftAvgFIFO->unblock();

        // http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_join.html
        r = pthread_join(readThreadID, &status);
        if(r) printf("::StopSdramRead pthread_join(readThreadID,status=%p)=%d (%s)\n", status, r, strerror(r));
        if(transmitActive)
        {
            if (m_svr > 0) socket_close(m_svr); // if thread is in accept()
            r = pthread_join(transmitThreadID, &status);
            if(r) printf("::StopSdramRead pthread_join(transmitThreadID,status=%p)=%d (%s)\n", status, r, strerror(r));
        }
    // FIXME: not sure if this is needed in the else:
    } else {
        //need to unblock fifo in case other thread was waiting for data
        m_SamplesFIFO->unblock();
        m_fftFIFO->unblock();
        m_fftAvgFIFO->unblock();
    }
}

/**
	@brief Thread starts data reading procedure.
	@param ptrTestingModule pointer to testing module.
 */
void* TestingModule::ReadDataThread(void *ptrTestingModule)
{
	TestingModule *module = reinterpret_cast<TestingModule*>(ptrTestingModule);
	if (module == NULL || !module->readingData)
		pthread_exit(module);
	else
    {
        char digiRed = 0;
        module->device->GetCustomParameter("HW_DigiRed", &digiRed);
        if( digiRed )
            module->ReadData_DigiRed();
        else
            module->ReadData();
    }
	return NULL;
}

/**
	@brief Reads data stream from board.
 */
void TestingModule::ReadData()
{
	//clear all data from buffers
	m_SamplesFIFO->reset();
	SplitPacket splitPkt(DIGIGREEN_SPLIT_PACKET_SIZE);

	int QueueSize = 16; // must be power of 2
	unsigned int iQueueSizeMask = QueueSize-1;
	int Timeout = 1500;

	if (!device->IsOpen())
	{
		writeLog("Error: no USB device found.", 1);
		readingData = false;
		return;
	}

	m_ulFailures = 0;
	m_bufferFailures = 0;
	long len = 32768; //size of received buffers

	int* contexts = new int[QueueSize];
	unsigned char** m_Buffers = new unsigned char*[QueueSize];
    for (int i = 0; i < QueueSize; i++)
		m_Buffers[i] = new unsigned char[len];
	// Queue-up the first batch of transfer requests
	for (int i = 0; i < QueueSize; i++)
		contexts[i] = device->BeginDataReading(m_Buffers[i], len);

	long m_BytesXferred = 0;
	long t1, t2, deltaT, t1_info, t2_info;
	t1 = GetTickCount();
	t2 = t1;

	unsigned int i = 0;
	long rLen = len;

	long packetReceived = 0;

	unsigned int pos = 0; //position within received buffer
	unsigned int currentSample = 0;
	int tempInt; //used to store sample value during splitting

	t1_info = GetTickCount();
	while (readingData)
	{
		// Reset this each time through because FinishDataReading may modify it
		rLen = len;
		if(!device->WaitForReading(contexts[i], 1000))
		{
			//device->AbortReading();
			m_bufferFailures++;
		}
		// Must always call FinishDataXfer to release memory of contexts[i]
		if (device->FinishDataReading(m_Buffers[i], rLen, contexts[i]))
  		{
			packetReceived++;
			t2 = GetTickCount();
			m_BytesXferred += rLen;
		}
		else
		{
			m_bufferFailures++;
		}

		if (rLen >= len) //start splitting buffer into IQ samples
		{
			rLen = len;
			pos = 0;
			currentSample = 0;

            while (currentSample < splitPkt.size) //10880 samples in one received buffer
            {
                if ((pos & 511) == 510)
                    pos += 2;
                // I channel
                tempInt = (m_Buffers[i][pos + 1] & 0x0F) << 8;
                tempInt |= m_Buffers[i][pos];
                tempInt = tempInt << 20;
                splitPkt.Idata[currentSample] = tempInt >> 20;

                // Q channel
                tempInt = m_Buffers[i][pos + 2] << 4;
                tempInt |= (m_Buffers[i][pos + 1] >> 4);
                tempInt = tempInt << 20;
                splitPkt.Qdata[currentSample] = tempInt >> 20;


                //advance to next sample
                pos += 3;
                ++currentSample;
            }
			//push received samples to FIFO
			splitPkt.used = false;
			m_SamplesFIFO->push(&splitPkt);
		}
		// Re-submit this request to keep the queue full
        contexts[i] = device->BeginDataReading(m_Buffers[i], len);

		t2_info = GetTickCount();
//		if (t2_info - t1_info > 10000)
		if ((t2_info - t1_info) > g_frame_delay) // each delay period display info and update data rate
		//This uses a global variable that changes with the frame delay pop-up on the menu
		//g_frame_delay is in mS of delay between frames
		{
			t1_info = t2_info;
			deltaT = (t2 - t1);
			if (deltaT <= 0)
			{
				deltaT = 1;
				m_BytesXferred = 0;
			}
			t1 = GetTickCount();

			m_ulFailures = m_bufferFailures;
			m_bytesPerSecond = (m_BytesXferred/1024) / (deltaT/1000.0); // / 1000;
			m_BytesXferred = 0;

			cout << "Rate: " << m_bytesPerSecond << "  KB/s  " << endl;
			cout << "Failures: " << m_ulFailures << endl;

			cout << " streaming packet received: " << packetReceived << endl;
			cout << " ffts calculated: " << countFFT << endl << endl;

			cout << " samples FIFO len: " << m_SamplesFIFO->length() << endl;
			cout << " FFT FIFO len: " << m_fftFIFO->length() << endl << endl;
			cout << " FFT AVG FIFO len: " << m_fftAvgFIFO->length() << endl << endl;

			cout << " Frame Power: " << g_framepwr << endl;

			packetReceived = 0;
			countFFT = 0;
		}
		i = (i + 1) & iQueueSizeMask;
		countBuffers++;
	}
	device->AbortReading(); // aborts all pending operations

	// Wait for all the queued requests to be canceled
	for(int j=0; j<QueueSize; j++)
	{
		rLen = len;
		device->WaitForReading(contexts[i], 20);
		device->FinishDataReading(m_Buffers[i], rLen, contexts[i]);
		delete[] m_Buffers[i];
		i = (i + 1) & iQueueSizeMask;
	}
	delete[] m_Buffers;
	delete[] contexts;
}

/**
	@brief Reads data stream from board.
 */
void TestingModule::ReadData_DigiRed()
{
    bool usb3connection = false;
    int maxPacketSize = 0;
    device->GetCustomParameter("MaxPacketSize", &maxPacketSize);
    if(maxPacketSize == 512)
        usb3connection = false;
    else if(maxPacketSize > 512)
        usb3connection = true;
	//clear all data from buffers
	m_SamplesFIFO->reset();

	SplitPacket *splitPkt;

    long len;
	if(m_hwDigiRed)
    {
        if(maxPacketSize == 512)
        {
            splitPkt = new SplitPacket(DIGIRED_SPLIT_PACKET_SIZE/2);
            len = 32768;
        }
        else
        {
            splitPkt = new SplitPacket(DIGIRED_SPLIT_PACKET_SIZE*4);
            len = 4096*64;
        }
    }
    else
    {
        splitPkt = new SplitPacket(DIGIGREEN_SPLIT_PACKET_SIZE);
        len = 32768;
    }

	int QueueSize = 16; // must be power of 2
	unsigned int iQueueSizeMask = QueueSize-1;
	int Timeout = 1000;

	if (!device->IsOpen())
	{
		writeLog("Error: no USB device found.", 1);
		readingData = false;
		return;
	}

	m_ulFailures = 0;
	m_bufferFailures = 0;

    bool iq_select = true;
    bool iq_select_secondary = true;

	int* contexts = new int[QueueSize];
	unsigned char** m_Buffers = new unsigned char*[QueueSize];
    for (int i = 0; i < QueueSize; i++)
		m_Buffers[i] = new unsigned char[len];
	// Queue-up the first batch of transfer requests
	for (int i = 0; i < QueueSize; i++)
		contexts[i] = device->BeginDataReading(m_Buffers[i], len);

	long m_BytesXferred = 0;
	long t1, t2, deltaT, t1_info, t2_info;
	t1 = GetTickCount();
	t2 = t1;

	unsigned int i = 0;
	long rLen = len;

	long packetReceived = 0;

	unsigned int currentSample = 0;
	int tempInt; //used to store sample value during splitting

	t1_info = GetTickCount();

	bool needToAlignData = false;

    long iq_select_errors = 0;
    long iq_select_errors_secondary = 0;
	while (readingData)
	{
		// Reset this each time through because FinishDataReading may modify it
		rLen = len;
		if(!device->WaitForReading(contexts[i], 100))
		{
			//device->AbortReading();
			m_bufferFailures++;
		}
		// Must always call FinishDataXfer to release memory of contexts[i]
		if (device->FinishDataReading(m_Buffers[i], rLen, contexts[i]))
  		{
			packetReceived++;
			t2 = GetTickCount();
			m_BytesXferred += rLen;

			/*if(dumpBuffer)
            {
                fstream fout;
                fout.open("bufferDump.txt", ios::out|ios::binary);
                fout.write((const char*)m_Buffers[i], rLen);
                fout.close();
                dumpBuffer = false;
            }*/
		}
		else
		{
			m_bufferFailures++;
		}

		if (rLen >= len) //start splitting buffer into IQ samples
		{
			rLen = len;
            if( (((m_Buffers[i][1]) & 0x10) >> 4) == !m_frameStart)
            {
                needToAlignData = false;
            }
            else
                needToAlignData = true;

            if(needToAlignData)
            {
                for(int b=0; b<len; b+=4)
                {
                    // Q channel
                    tempInt = (m_Buffers[i][b+1]) << 8;
                    tempInt |= m_Buffers[i][b];
                    tempInt = tempInt << 20;
                    splitPkt->Qdata[currentSample] = tempInt >> 20;
                    ++currentSample;
                    if(currentSample >= splitPkt->size)
                    {
                        splitPkt->used = false;
                        m_SamplesFIFO->push(splitPkt);
                        currentSample = 0;
                    }
                    // I channel
                    tempInt = (m_Buffers[i][b + 3]) << 8;
                    tempInt |= m_Buffers[i][b + 2];
                    tempInt = tempInt << 20;
                    splitPkt->Idata[currentSample] = tempInt >> 20;
                    //advance to next sample
                }
            }
            else
            {
                for(int b=0; b<len; b+=4)
                {
                    // I channel
                    tempInt = (m_Buffers[i][b+1]) << 8;
                    tempInt |= m_Buffers[i][b];
                    tempInt = tempInt << 20;
                    splitPkt->Idata[currentSample] = tempInt >> 20;

                    // Q channel
                    tempInt = (m_Buffers[i][b + 3]) << 8;
                    tempInt |= m_Buffers[i][b + 2];
                    tempInt = tempInt << 20;
                    splitPkt->Qdata[currentSample] = tempInt >> 20;

                    //advance to next sample
                    ++currentSample;
                    if(currentSample >= splitPkt->size)
                    {
                        splitPkt->used = false;
                        m_SamplesFIFO->push(splitPkt);
                        currentSample = 0;
                    }
                }
            }
		}
		// Re-submit this request to keep the queue full
        contexts[i] = device->BeginDataReading(m_Buffers[i], len);
        i = (i + 1) & iQueueSizeMask;
		countBuffers++;

		t2_info = GetTickCount();
		if (t2_info - t1_info > 1000) // each second display info and update data rate
		{
			t1_info = t2_info;
			deltaT = (t2 - t1);
			if (deltaT <= 0)
			{
				deltaT = 1;
				m_BytesXferred = 0;
			}
			t1 = GetTickCount();

			m_ulFailures = m_bufferFailures;
			m_bytesPerSecond = (m_BytesXferred/1024) / (deltaT/1000.0); // / 1000;
			m_BytesXferred = 0;

#if defined(CSV_DEBUG)
            // NB: reporting/file management is performed in GUI\pnlSpectrum.cpp ::UpdatePwrGraph()
            InterlockedIncrement(&g_Statistics_updateCount);    // odd values indicate statistics update in progress
            g_Statistics_m_bytesPerSecond = m_bytesPerSecond;
            g_Statistics_ulFailures = m_ulFailures;
            g_Statistics_packetReceived = packetReceived;
            g_Statistics_countFFT = countFFT;
            g_Statistics_m_SamplesFIFOLength = m_SamplesFIFO->length();
            g_Statistics_m_fftFIFOLength = m_fftFIFO->length();
            g_Statistics_m_frameStart = m_frameStart;
            g_Statistics_needToAlignData = needToAlignData;
            InterlockedIncrement(&g_Statistics_updateCount);    // non-zero even values indicate no torn data...
#elif defined(_DEBUG)
			cout << "Rate: " << m_bytesPerSecond << "  KB/s  " << endl;
			cout << "Failures: " << m_ulFailures << endl;

//			cout << "Frame Power: " << g_framepwr << " mW @ ADC" << endl << endl;

			cout << " streaming packets received: " << packetReceived << endl;
			cout << " ffts calculated: " << countFFT << endl << endl;

			cout << " samples FIFO len: " << m_SamplesFIFO->length() << endl;
			cout << " FFT FIFO len: " << m_fftFIFO->length() << endl << endl;
			cout << " FFT AVG FIFO len: " << m_fftAvgFIFO->length() << endl << endl;

			cout << "frame start : " << !m_frameStart << endl;
			cout << "need to shift : " << (needToAlignData ? "true" : "false") << endl;
#endif // defined
			iq_select_errors = 0;
			iq_select_errors_secondary = 0;

			packetReceived = 0;
			countFFT = 0;
		}
	}
    device->AbortReading(); // aborts all pending operations

	// Wait for all the queued requests to be canceled
	for(int j=0; j<QueueSize; ++j)
	{
		rLen = len;
		device->WaitForReading(contexts[i], 20);
		device->FinishDataReading(m_Buffers[i], rLen, contexts[i]);
		delete[] m_Buffers[i];
		i = (i + 1) & iQueueSizeMask;
	}
	delete[] m_Buffers;
	delete[] contexts;
	delete splitPkt;
}

/**
    Takes data samples from Samples FIFO and calculates FFT. Calculation results are copied to FFT FIFO
*/
bool TestingModule::externalCalculateFFT()
{
    FFTPacket fftPkt(FFTsamples);
    SplitPacket *splitPkt;

    int maxPacketSize = 0;
    device->GetCustomParameter("MaxPacketSize", &maxPacketSize);
//cout << "Max Packet Size = " << maxPacketSize << endl;
	if(m_hwDigiRed && maxPacketSize == 512)
    {
        splitPkt = new SplitPacket(DIGIRED_SPLIT_PACKET_SIZE/2);
    }
    else if(m_hwDigiRed && maxPacketSize > 512)
    {
        splitPkt = new SplitPacket(DIGIRED_SPLIT_PACKET_SIZE*4);
    }
    else
    {
        splitPkt = new SplitPacket(DIGIGREEN_SPLIT_PACKET_SIZE);
    }

	memset(fftPkt.amplitudes, 0, fftPkt.size*sizeof(float));
	long timeout = 300;

	int tempInt = 0;
	float sumI = 0;
	float sumQ = 0;
    float avgI = 0;
	float avgQ = 0;
	double SumVsq = 0;
	//double scalefactor = 2.145767; //nW Qstep * Qstep / Impedance at ADC
//	double scalefactor = 1.3732910156e-4; //nW Qstep * Qstep / Impedance at ADC (mW)
    double scalefactor = 4*6.70552E-05; // Imperical microwatts

	unsigned int samplesUsed = splitPkt->size; //number of samples used from packet
	unsigned int samplesReceived = 0; //number of samples received

    if(m_SamplesFIFO->length() < 1+FFTsamples/splitPkt->size)
    {
        delete splitPkt;
        return false;
    }

    m_SamplesFIFO->freeze();
    for(int i=0; i<1+FFTsamples/splitPkt->size; ++i)
	{
		if (samplesUsed >= splitPkt->size) //if packet used up, pop another one
		{
			m_SamplesFIFO->pop(splitPkt); // popping from FIFO is blocked if no packets are left
			samplesUsed = 0;
		}
		//calculate averages for I and Q to perform DC correction
		if(m_swapIQ)
        {
            while (samplesReceived < FFTsamples && samplesUsed < splitPkt->size)
            {
                sumI += (m_fftCalcIn[samplesReceived][0] = splitPkt->Qdata[samplesUsed]);
                sumQ += (m_fftCalcIn[samplesReceived][1] = splitPkt->Idata[samplesUsed]);
                //SumVsq += (splitPkt->Idata[samplesUsed] * splitPkt-> Idata[samplesUsed]) +
                //           (splitPkt->Qdata[samplesUsed] * splitPkt-> Qdata[samplesUsed]);
                ++samplesReceived;
                ++samplesUsed;
            }
        }
        else
        {
            while (samplesReceived < FFTsamples && samplesUsed < splitPkt->size)
            {
                sumI += (m_fftCalcIn[samplesReceived][0] = splitPkt->Idata[samplesUsed]);
                sumQ += (m_fftCalcIn[samplesReceived][1] = splitPkt->Qdata[samplesUsed]);
                //SumVsq += (splitPkt->Idata[samplesUsed] * splitPkt-> Idata[samplesUsed]) +
                //           (splitPkt->Qdata[samplesUsed] * splitPkt-> Qdata[samplesUsed]);
                ++samplesReceived;
                ++samplesUsed;
            }
        }
		//enough samples received for FFT, start calculating
		if (samplesReceived >= FFTsamples)
		{
			float oneOverN = 1.0/(float)FFTsamples;
			samplesReceived = 0;

			avgI = sumI * oneOverN;
			avgQ = sumQ * oneOverN;
			//g_framepwr = SumVsq * scalefactor * oneOverN ;
			sumI = 0;
			sumQ = 0;
			SumVsq = 0;
			//do DC correction
			if (m_DCcorrectionOnOff)
			{
				for (int i = 0; i < FFTsamples; ++i)
				{
					m_fftCalcIn[i][0] -= g_DcOffsetI;
					m_fftCalcIn[i][1] -= g_DcOffsetQ;
                    SumVsq += (m_fftCalcIn[i][0] * m_fftCalcIn[i][0]) +
                              (m_fftCalcIn[i][1] * m_fftCalcIn[i][1]);
				}
			} else {
				for (int i = 0; i < FFTsamples; ++i)
				{
                    SumVsq += (m_fftCalcIn[i][0] * m_fftCalcIn[i][0]) +
                              (m_fftCalcIn[i][1] * m_fftCalcIn[i][1]);
                }
            }
			g_avgI = avgI;
			g_avgQ = avgQ;
			g_framepwr = SumVsq * scalefactor * oneOverN ;

//			cout << "Start FFT Calc Ticks : " <<GetTickCount();

			fftwf_execute(m_fftCalcPlan);

//			cout << " After FFT Calc Tcks : " << GetTickCount() << endl;

			// normalize FFT results
			for (int i = 0; i < FFTsamples; ++i)
			{
				m_fftCalcOut[i][0] *= oneOverN;
				m_fftCalcOut[i][1] *= oneOverN;
			}

			// negative frequencies
			int lim = FFTsamples / 2 - 1;
			int itmp = 0;
			for (int f = 0; f < lim; f++)
			{
                double ifreq2 = m_fftCalcOut[itmp][0] * m_fftCalcOut[itmp][0];
                double qfreq2 = m_fftCalcOut[itmp][1] * m_fftCalcOut[itmp][1];
				itmp = FFTsamples / 2 + f;
				fftPkt.amplitudes[f] = (ifreq2 + qfreq2) * g_integrationGain;
			}

			// positive frequencies
			lim = FFTsamples / 2;
			for (int f = 0; f < lim; f++)
			{
                double ifreq2 = m_fftCalcOut[f][0] * m_fftCalcOut[f][0];
                double qfreq2 = m_fftCalcOut[f][1] * m_fftCalcOut[f][1];
				fftPkt.amplitudes[f + lim - 1] = (ifreq2 + qfreq2) * g_integrationGain;
			}

			//samples used for current FFT
			for (int i = 0; i < FFTsamples; ++i)
			{
				fftPkt.isamples[i] = m_fftCalcIn[i][0];
				fftPkt.qsamples[i] = m_fftCalcIn[i][1];
			}
			//push FFT results to FIFO
			fftPkt.used = false;
			m_fftFIFO->push(&fftPkt);
			++countFFT;
			m_SamplesFIFO->unfreeze();
			break;
        }
	}
	delete splitPkt;
	return true;
}

/**
	@brief Thread handles spectrum output service.
	@param ptrTestingModule pointer to testing module.
 */
void* TestingModule::TransmitSpectraThread(void *ptrTestingModule)
{
	TestingModule *module = reinterpret_cast<TestingModule*>(ptrTestingModule);
	if (module == NULL || !module->readingData)
		pthread_exit(module);
	else if(g_RSS_Extension) module->TransmitSpectra_RSSx();
	else                     module->TransmitSpectra_RSS();
	return NULL;
}

/**
	@brief Reads data stream from board.
 */
void TestingModule::TransmitSpectra_RSS()
{
    FFTAvgPacket avgPkt(FFTsamples);
    int flag;
	//const char *options = "ipv4";   // TODO: may need to provide options
    int s, n, l;

    // NB: socket_init() was called once in the TestingModule constructor

    flag = SOCKET_VERBOSE;
    //if( strstr(options,"ipv6") ) flag |= SOCKET_IPV6;
    //if( strstr(options,"bsd") ) flag |= SOCKET_BSD;

    // setup socket server
    // accept connection

    m_svr = socket_open_bind_and_listen(g_RSS_IP,g_RSS_Port,1,flag);
    if (m_svr>0) do
    {
        cout << "::TransmitSpectra_RSS accepting connection..." << endl;

        s = socket_accept(m_svr,flag);
        if (s>0)
        {
            unsigned int imin, imax, imid, channel;
            float fmin, fmax, fmid, fcenter, foffset;

            // obtain first buffer
            m_fftAvgFIFO->pop(&avgPkt);     // NB: blocks until first buffer is received
            if( !readingData ) continue;    // stop before 1st average is computed
            else {
                char buffer[1024];
                unsigned int bandwidth;
                float fbin = fabs(avgPkt.offset_frequencies[1] - avgPkt.offset_frequencies[0])*1e6;

                // construct configuration string
                fcenter = avgPkt.fcenter*1e9;
                foffset = avgPkt.foffset*1e9;
                channel = avgPkt.size;
                imin = 0;
                imid = channel / 2;
                imax = avgPkt.size - 1;
                fmin = avgPkt.offset_frequencies[imin]*1e6 + fcenter;  // FIXME: normalize to Ghz
                fmid = avgPkt.offset_frequencies[imid]*1e6 + fcenter;
                fmax = avgPkt.offset_frequencies[imax]*1e6 + fcenter;
                bandwidth = (unsigned int)fabs(fmax - fmin);

                if ( g_RSS_Channels > channel )         // invalid channels
                {
                    cout << "::TransmitSpectra_RSS channels (" << g_RSS_Channels
                         << ") > actual (" << channel << ") - STOP"
                         << endl;
                    break;
                }
                if ( g_RSS_Channels < channel )         // need to pick a subset to send to RSS
                {
                    channel = (unsigned int)g_RSS_Channels;
                    imin = imid - channel / 2;
                    //imid stays where it is (at the fcenter)
                    imax = imid + channel / 2 - 1;
                    fmin = avgPkt.offset_frequencies[imin]*1e6 + fcenter;
                    fmid = avgPkt.offset_frequencies[imid]*1e6 + fcenter;
                    fmax = avgPkt.offset_frequencies[imax]*1e6 + fcenter;

                    // FIXME: offset_frequencies[-2,-1] appear to be incorrect
                    // so compute from the bin size
                    if (imax >= avgPkt.size-2)
                    {
                        float _fmax = fmax;
                        fmax = fmin + channel * fbin;

                        cout << "::TransmitSpectra_RSS BUG adjust"
                             << " fmax " << _fmax*1e-6 << " MHz -> " << fmax*1e-6 << " MHz"
                             << endl;
                    }

                    bandwidth = (unsigned int)fabs(fmax - fmin);
                }
                else
                {
                    // FIXME: offset_frequencies[-2,-1] appear to be incorrect
                    // so compute from the bin size
                    float _fmax = fmax;
                    fmax = fmin + channel * fbin;

                    cout << "::TransmitSpectra_RSS BUG adjust"
                         << " fmax " << _fmax*1e-6 << " MHz -> " << fmax*1e-6 << " MHz"
                         << endl;

                    bandwidth = (unsigned int)fabs(fmax - fmin);

                }
                // if its the same, then imin/imax/fmin/fmax are already set correctly
                g_RSS_MustDisconnect = false;

                cout << "::TransmitSpectra_RSS"
                     << " fcenter=" << fcenter*1e-6 << " MHz"
                     << ",channel=" << channel
                     << ",fmin=" << fmin*1e-6 << " MHz"
                     << ",fmid=" << fmid*1e-6 << " MHz"
                     << ",fmax=" << fmax*1e-6 << " MHz"
                     << ",bandwidth=" << bandwidth
                     << endl;

                // send configuration string
                // see http://cygnusa.blogspot.com/2015/07/how-to-talk-to-radio-sky-spectrograph.html
                // TODO: does RSS need/care about the trailing '|' and CRLF?
                n = snprintf(buffer,sizeof(buffer),"F %u|S %u|O %u|C %u|\r\n",
                    (unsigned int)fmid, bandwidth, (unsigned int)foffset, channel );
                buffer[sizeof(buffer)-1] = '\0';    // force NUL

                cout << "::TransmitSpectra_RSS send (" << n << ") " << buffer
                     << endl
                     << "::TransmitSpectra_RSS "
                     << fmin*1e-6 << " MHz" << " to " << fmax*1e-6 << " MHz"
                     << ",[" << imin << "," << imid << "," << imax << "]"
                     << endl
                     << "::TransmitSpectra_RSS offset "
                     << avgPkt.offset_frequencies[imin]*1e3 << " KHz"
                     << "," << avgPkt.offset_frequencies[imid]*1e3 << " KHz"
                     << "," << avgPkt.offset_frequencies[imax]*1e3 << " KHz"
                     << endl;

                // DEBUG
                /*
                if (0)
                {
                    float last = 0.0;
                    cout << "::TransmitSpectra_RSS frequencies: " << endl;
                    for(int i=0;i<avgPkt.size;i++)
                    {
                        float f = avgPkt.offset_frequencies[i]*1e6 + fcenter;
                        const char *mark = (f<last)?"**":"  ";  // HIGHLIGHT non-increasing values
                        if( i >= imin && i <= imax )
                            cout << mark << "[" << i << "]=" << f << endl;
                        else
                            cout << mark << "(" << i << ")=" << f << endl;
                        last = f;
                    }
                }
                */

                l=socket_send(s,buffer,n,0);
                if( l!=n ) break;
            }

            // get next buffer
            while( readingData )
            {
                short buffer[channel+1];
                char *p = (char *)&buffer[0];
                size_t todo = sizeof(buffer);

                m_fftAvgFIFO->pop(&avgPkt);     // NB: blocks until first buffer is received
                if( !readingData || g_RSS_MustDisconnect ) break;
                if( avgPkt.size < channel ) break;  // safety

                // format the protocol buffer to match RSS requirement (high->low frequency)
                for(unsigned int i=0,u=imax;i<channel;i++,u--)
                {
                    float v = ((avgPkt.amplitudes[u] + g_RSS_Offset) * g_RSS_Gain) + g_RSS_Bias;
                    // see protocol spec
                    if (v < g_RSS_MinValue) buffer[i] = (short)g_RSS_MinValue;
                    else if (v > g_RSS_MaxValue) buffer[i] = (short)g_RSS_MaxValue;
                    else buffer[i] = (short)roundf(v);
                }
                buffer[channel] = 0xFEFE;    // see protocol spec

#if 0
                // DEBUGGING - send ASCII over telnet for diagnostic w/o RSS
                char cbuf[1024];
                short _amin = SHRT_MAX, _amax = SHRT_MIN;
                float _aminf = FLT_MAX, _amaxf = FLT_MIN;
                for(unsigned int i=0,u=imin;u<imax;i++,u++)
                {
                    float v = avgPkt.amplitudes[channel - u - 1];
                    if (v < _aminf) _aminf = v;
                    if (v > _amaxf) _amaxf = v;
                    if (buffer[i] < _amin) _amin = buffer[i];
                    if (buffer[i] > _amax) _amax = buffer[i];
                }
                n = snprintf(cbuf,sizeof(cbuf),"f[%.0f,%.0f] @%.0f min/max=[%g(%hd),%g(%hd)]\r\n",
                    _fmin, _fmax, _fcenter, _aminf, _amin, _amaxf, _amax );
                cbuf[sizeof(cbuf)-1] = '\0';    // force NUL
                p = &cbuf[0];
                todo = n;
#endif

                l = socket_send(s,p,todo,0);
                if ( l != todo ) break;
            }

            cout << "::TransmitSpectra_RSS close" << endl;

            socket_close(s);
        }
    } while( readingData );     // client disconnected, but we are still capturing...

    cout << "::TransmitSpectra_RSS exit" << endl;
}

/**
	@brief Reads data stream from board.
 */
void TestingModule::TransmitSpectra_RSSx()
{
    cout << "::TransmitSpectra_RSSx not implemented at the moment..." << endl;
}

/**
 @brief Prints out given byte array in hexadecimal format.
 @param src pointer to byte array
 @param size number of bytes to print
 */
void TestingModule::printHex(char *src, int size)
{
	char tempBuf[10];
	memset(tempBuf, 0, 10);
	for (int i = 0; i < size; i++)
	{
		sprintf(tempBuf, "%.8x", src[i]);
		cout << "0x" << tempBuf[6] << tempBuf[7] << ' ';
	}
}

/**
	@brief Calls interface update callback function with given code and additional parameters.
 */
void TestingModule::UpdateInterface(int code, char *param)
{
	if (updateInterfaceCallback)
		updateInterfaceCallback(code, param);
}

/**
	@brief Assigns connection manager for data transfering.
	@param mng pointer to connection manager
 */
void TestingModule::SetConnectionManager(ConnectionManager *mng)
{
	device = mng;
}

/**
	@brief Returns pointer to currently used connection manager.
 */
ConnectionManager* TestingModule::GetConnectionManager()
{
	return device;
}

/**
	@brief Prints given character string.
	@param str pointer to null terminated char array
 */
void TestingModule::ShowMessage(char *str)
{
	cout << str << endl;
}
/**
	@brief Prints given string.
	@param str string to print
 */
void TestingModule::ShowMessage(string str)
{
	cout << str << endl;
}

void TestingModule::writeLog(string msg, int importance)
{
	if (importance < 5)
		UpdateInterface(SHOW_TESTING_LOG_MESSAGE, (char*)msg.c_str());
}
/**
	@brief Enables DC correction
*/
void TestingModule::turnOnDCcorrection()
{
	m_DCcorrectionOnOff = 1;
}

/**
	@brief Disables DC correction
*/
void TestingModule::turnOffDCcorrection()
{
	m_DCcorrectionOnOff = 0;
}

/**
	@brief Clears usb fifo buffer.
 */
void TestingModule::USBFIFOReset()
{
    long length = 64;
	unsigned char *out = new unsigned char[length];

	if (!device)
		return;

	memset(out, 0x00, length);
	out[0] = 0x40;
	out[1] = 0x10;
	out[2] = 1;

	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(out, length);
	delete []out;
}

/**
	@brief Enables FPGA reset signal.
 */
void TestingModule::FPGAResetOn()
{
    long length = 64;
	unsigned char *out = new unsigned char[length];

	if (!device)
		return;

	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = CFG_ADDR;
	out[2] = 1;

	out[4] = 0x03;
	out[5] = 0x00;

	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(out, length);
	delete []out;
}

/**
	@brief Disables FPGA reset signal.
 */
void TestingModule::FPGAResetOff()
{
    long length = 64;
	unsigned char *out = new unsigned char[length];

	if (!device)
		return;

	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = CFG_ADDR;
	out[2] = 1;

	out[4] = 0x03;
	out[5] = 0x01;

	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(out, length);
	delete []out;
}

/**
	@brief Selects which source will be used for data stream, NCO or ADC.
 */
void TestingModule::SelectRxSource(bool ADC)
{
	m_FPGA_RXSRC_ADC = ADC;
	// send reset command
    long length = 64;
	unsigned char *out = new unsigned char[length];

	if (!device)
		return;

	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = CFG_ADDR;
	out[2] = 1;

	out[4] = 0x02;
	out[5] = m_FPGA_RXSRC_ADC; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | m_FPGA_Tx_enabled; // TXDEN
	out[5] = (out[5] << 1) | m_FPGA_Rx_enabled; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(out, length);
	delete []out;
}

void TestingModule::SelectTxSource(bool ADC)
{
	m_FPGA_Tx_enabled = ADC;
	// send reset command
    long length = 64;
	unsigned char *out = new unsigned char[length];

	if (!device)
		return;

	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = CFG_ADDR;
	out[2] = 1;

	out[4] = 0x02;
	out[5] = m_FPGA_RXSRC_ADC; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | m_FPGA_Tx_enabled; // TXDEN
	out[5] = (out[5] << 1) | m_FPGA_Rx_enabled; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(out, length);
	delete []out;
}

/**
	@brief Enables or disables data streaming.
 */
void TestingModule::EnableFPGA(bool Rx, bool Tx)
{
	m_FPGA_Rx_enabled = Rx;
	m_FPGA_Tx_enabled = Tx;

	long length = 64;
	unsigned char out[length];
	if (!device)
		return;

	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = CFG_ADDR;
	out[2] = 1;

	out[4] = 0x02;
	out[5] = m_FPGA_RXSRC_ADC; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | m_FPGA_Tx_enabled; // TXDEN
	out[5] = (out[5] << 1) | m_FPGA_Rx_enabled; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(out, length);
}

/**
    @brief Sets samples count used in FFT calculations
    @param samplesCount new samples count
    @return true if samples count changed
*/
bool TestingModule::setFFTSamplesCount(unsigned int samplesCount)
{
    if(!readingData)
    {
        initializeFFTplan(samplesCount);
        return true;
    }
    return false;
}
