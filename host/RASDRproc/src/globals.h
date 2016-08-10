// -----------------------------------------------------------------------------
// FILE:        "globals.h"
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
//Globals.h - Place for Global variables
#ifndef GLOBAL_H
#define GLOBAL_H
#define CLOSE_DEBUG true

#define BACKGROUND_SUBTRACT         0x01    // subtract background
#define BACKGROUND_DISPLAY          0x02    // display background on overlay screen
#define BACKGROUND_ABOVE_REFERENCE  0x04    // render signal above/below reference signal
#define BACKGROUND_VECTOR           0x08    // treat the background subtraction as a vector (on) or a scalar (off)
#define BACKGROUND_REFERENCE_MEAN   0x10    // background reference is mean value
#define BACKGROUND_REFERENCE_MEDIAN 0x20    // background reference is median value
#define BACKGROUND_REFERENCE_HISTO  0x40    // background reference by peak histogram value
#define BACKGROUND_DEBUG            0x27    // default value if no configuration file present (non-zero enables system)
extern int g_backgroundDebugCfg;
extern float g_integrationGain;
extern float g_DcOffsetI;
extern float g_DcOffsetQ;
extern float g_avgI;
extern float g_avgQ;
extern bool g_AutoDCOffset;
extern volatile float g_DcErrorI;
extern volatile float g_DcErrorQ;
extern int g_UnlimitedAveraging;

#define CSV_DEBUG   "RASDRproc-%s.csv"      // filename template to produce .csv output

////include <wx/string.h>
extern int g_frame_delay;
extern int g_closedelay;
extern double g_framepwr;
//extern float g_DisplayTimeSpan;
//extern int g_DisplayFrames;
extern int g_PwrSpanSec;
extern int g_MaxPwrSpanSec;
extern float g_framesPerMin;
extern char g_FFTfileName[1024];
extern char g_PWRfileName[1024];
extern char g_CfgFileName[80];
extern bool g_CfgChanged;
extern int g_FFTfileAction;
extern bool g_FFTfileSetup;
extern bool g_FFTfileRecording;
extern bool g_OverwriteFFTfile;
extern bool g_FFTfileIsDefined;
extern int g_PWRfileAction;
extern bool g_PWRfileSetup;
extern bool g_PWRfileRecording;
extern bool g_OverwritePWRfile;
extern bool g_PWRfileIsDefined;
extern int g_FFTframeSkip;
extern int g_FFTframesOut;
extern int g_FFTFileType;
extern int g_PWRFileType;
extern int g_NumbFFTFiles;
extern int g_NumbPWRFiles;
extern int g_FFT_TimeStandard;
extern int g_PWRTimeStandard;
extern bool g_PendingRestartCapture;
extern bool g_capturingData;
extern int g_PwrRecordRate;
extern int g_MaxFFTbins;
extern int g_FFTDataSource;
extern bool g_Pulsar_Sim_Running;
extern bool g_Pulsar_Capture_Running;
extern float g_Min_DM_Range;
extern float g_Max_DM_Range;
extern float g_DM_Inc;
extern float g_Min_Period_Range;
extern float g_Max_Period_Range;
extern float g_Period_Inc;
extern float g_Margin;
extern float g_Sim_DM;
extern float g_Sim_Period;
extern float g_Sim_Duty;
extern float g_Sim_Factor;

// Radio Sky Spectrograph integration
extern char g_RSS_IP[1024];
extern unsigned short g_RSS_Port;
extern int  g_RSS_Channels;
extern bool g_RSS_Enable;
extern float g_RSS_FrequencyOffset;
extern volatile bool g_RSS_MustDisconnect;
extern bool g_RSS_Extension;
extern float g_RSS_Offset;
extern float g_RSS_Gain;
extern float g_RSS_Bias;
extern float g_RSS_MinValue;
extern float g_RSS_MaxValue;

//extern long ID_FFTOKBUTTON;
//typedef struct statistics {
    extern volatile long g_Statistics_updateCount;
    extern volatile unsigned int g_Statistics_m_bytesPerSecond;
    extern volatile int g_Statistics_ulFailures;
    extern volatile long g_Statistics_packetReceived;
    extern volatile long g_Statistics_countFFT;
    extern volatile int g_Statistics_m_SamplesFIFOLength;
    extern volatile int g_Statistics_m_fftFIFOLength;
    extern volatile int g_Statistics_m_frameStart;
    extern volatile bool g_Statistics_needToAlignData;
    extern volatile float g_Statistics_g_FFTbackgroundReferenceLevel;
    extern volatile float g_Statistics_g_framepwr;
    extern volatile float g_Statistics_m_PwrAve;
//} statistics_t;
//extern statistics_t g_Statistics;
#endif
