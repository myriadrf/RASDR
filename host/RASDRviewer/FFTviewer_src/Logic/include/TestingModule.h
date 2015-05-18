// -----------------------------------------------------------------------------
// FILE: 		TestingModule.h
// DESCRIPTION:	Header for TestingModule.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef TESTING_MODULE_H
#define TESTING_MODULE_H

#include "fftw3.h"
#include <vector>
#include <string.h>
#include <sstream>

#include <FIFO.h>
#include "Packets.h"

#define DIGIGREEN_SPLIT_PACKET_SIZE 10880 //number of I and Q pairs in split packet
#define DIGIRED_SPLIT_PACKET_SIZE 16384 //number of I and Q pairs in split packet

using namespace std;

class Main_Module;
class ConnectionManager;

class TestingModule
{
public:
    TestingModule(Main_Module *pMainModule);
	~TestingModule();

	void USBFIFOReset();
	void FPGAResetOn();
	void FPGAResetOff();
	void SelectRxSource(bool ADC);
	void SelectTxSource(bool ADC);
	void EnableFPGA(bool Rx, bool Tx);

	void StartSdramRead();
	void StopSdramRead();

    static void *ReadDataThread(void *ptrTestingModule);
	void ReadData();
	void ReadData_DigiRed();
	unsigned long readDataThreadID;

	bool externalCalculateFFT();

	unsigned long calcFFTThreadID;

	void UpdateInterface(int code, char *param);
	void (*updateInterfaceCallback)(int ,char *);

    void SetConnectionManager( ConnectionManager *mng);
    ConnectionManager* GetConnectionManager();

	void ShowMessage(char *str);
	void ShowMessage(string str);

	void printHex(char *src, int size);

	int FFTsamples;

	void writeLog(string msg, int importance = 10);

	void turnOnDCcorrection();
	void turnOffDCcorrection();

    bool setFFTSamplesCount(unsigned int samplesCount);

	unsigned int m_bytesPerSecond;
	int m_ulFailures;

	blockingFIFO<SplitPacket> *m_SamplesFIFO;
	blockingFIFO<FFTPacket> *m_fftFIFO;
	fftwf_complex* m_fftCalcIn;
	fftwf_complex* m_fftCalcOut;
	fftwf_plan m_fftCalcPlan;

	bool m_hwDigiRed;
	int m_frameStart;
	bool m_swapIQ;

private:
    void initializeFIFO(int samplesSize, int fftSize);
    void initializeFFTplan(int samplesCount);

    ConnectionManager *device;
	int m_DCcorrectionOnOff;

	long countFFT;
	long countSplits;
	long countBuffers;
	unsigned long m_bufferFailures;

	bool readingData;

	Main_Module *pMain;
	double samplingFrequency;

	bool m_FPGA_Rx_enabled;
	bool m_FPGA_Tx_enabled;
	bool m_FPGA_RXSRC_ADC;
	bool m_FPGA_TXSRC_ADC;
};


#endif
