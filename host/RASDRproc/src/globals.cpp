// -----------------------------------------------------------------------------
// FILE:        "globals.cpp"
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
//Globals.cpp The place for globals declarations

//#include "pnlSpectrum.h"
int g_frame_delay = 1000;

int g_closedelay  = 0;// This is used in debug mode on closing by slowing process
// Set to 0 for normal operation Higher values delay the steps in closing
double g_framepwr; // Used to return the frame power from the testing module
//float g_DisplayTimeSpan = 30;
//int g_DisplayFrames = 3600;
bool g_PwrRefIsSet = false;
double g_PwrRefOffset = 0.0;
double g_PwrAccum = 0.0;
int g_PwrSpanSec = 900; // Default (15 Min)X Span being Displayed on Power Chart
int g_MaxPwrSpanSec = 86400; // Max X Span & Storage Size
float g_framesPerMin = 1260; // Estimated
// BUGS: these were all arrays of pointers
char g_FFTfileName[1024] = { "FFTOut.csv" };
char g_PWRfileName[1024] = { "PowerOut.csv" };
char g_CfgFileName[80]   = { "RASDR.cfg" };
bool g_CfgChanged = false;
int g_FFTfileAction = 0;
bool g_FFTfileSetup = false;
bool g_FFTfileRecording = false;
bool g_OverwriteFFTfile = false;
bool g_FFTfileIsDefined = false;
int g_PWRfileAction = 0;
bool g_PWRfileSetup = false;
bool g_PWRfileRecording = false;
bool g_OverwritePWRfile = false;
bool g_PWRfileIsDefined = false;
int g_FFTframeSkip = 5;
int g_FFTframesOut = 64;
int g_FFTFileType = 1; // 0 = .csv for excel 1 = General
int g_PWRFileType = 0; // 0 = .csv for excel 1 = General
int g_NumbFFTFiles = 2; // 1 = single 2 = multiple suffixed
int g_NumbPWRFiles = 1; // 1 = single 2 = multiple suffixed
int g_FFT_TimeStandard = 1; // 0 = Local Time 1 = UT
int g_PWRTimeStandard = 0; // 0 = Local Time 1 = UT
bool g_PendingRestartCapture = false;
bool g_capturingData = false;
int g_PwrRecordRate = 30; // Default
float g_dbTrigger = -999; // < -900 = no trigger
//long ID_FFTOKBUTTON = wxID_OK;
int g_MaxFFTbins = 16384;   // TODO: coordinate with pnlSpectrum.cpp, Packets.h, TestingModule.h/.cpp, globals.cpp and pnlSpectrum.wxs
int g_FFTDataSource = 0;
bool g_Pulsar_Sim_Running = false;
bool g_Pulsar_Capture_Running = false;
float g_Min_DM_Range = 100;
float g_Max_DM_Range = 300;
float g_DM_Inc = 0.2;
float g_Min_Period_Range = 70;
float g_Max_Period_Range = 120;
float g_Period_Inc = 0.2;
float g_Margin = 0.1;
float g_Sim_DM = 26.8;
float g_Sim_Duty = 25.0;
float g_Sim_Period = 714.5;
float g_Sim_Factor = 1.0001;

// background subtraction
volatile int g_backgroundDebugCfg = 0x27;    // see globals.h for code
float g_integrationGain = 1.0;
float g_DcOffsetI = 0.0;
float g_DcOffsetQ = 0.0;
float g_avgI = 0.0;
float g_avgQ = 0.0;
bool g_AutoDCOffset = false;        // NB: not sure if we want this in the config file...
volatile float g_DcErrorI = 0.0;
volatile float g_DcErrorQ = 0.0;
volatile int g_UnlimitedAveraging = 0;
float g_MaxADC = (float)((1<<(12-1))-1);    // LMS6002D (signed 12-bit ADC) maximum positive value

// Radio Sky Spectrograph integration
char g_RSS_IP[1024] = { "127.0.0.1" };
unsigned short g_RSS_Port = 8888;
int  g_RSS_Channels = 100;
bool g_RSS_Enable = false;
float g_RSS_FrequencyOffset = 0.0;
volatile bool g_RSS_MustDisconnect = false;
bool g_RSS_Extension = false;
float g_RSS_Offset = 0.0;
float g_RSS_Gain = 1.0;
float g_RSS_Bias = 0.0;
float g_RSS_MinValue = (float)(0<<12);
float g_RSS_MaxValue = (float)(1<<12)-1.0;

// statistics gathering/reporting
volatile long g_Statistics_updateCount = 0;
volatile unsigned int g_Statistics_m_bytesPerSecond = 0;
volatile int g_Statistics_ulFailures = 0;
volatile long g_Statistics_packetReceived = 0;
volatile long g_Statistics_countFFT = 0;
volatile int g_Statistics_m_SamplesFIFOLength = 0;
volatile int g_Statistics_m_fftFIFOLength = 0;
volatile int g_Statistics_m_frameStart = 0;
volatile bool g_Statistics_needToAlignData = false;
volatile float g_Statistics_g_FFTbackgroundReferenceLevel = 0.0;
volatile float g_Statistics_g_framepwr = 0.0;
volatile float g_Statistics_m_PwrAve = 0.0;
