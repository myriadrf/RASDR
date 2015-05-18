// -----------------------------------------------------------------------------
// FILE:        "TestingModule.h"
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
