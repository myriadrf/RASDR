// -----------------------------------------------------------------------------
// FILE:        "pnlSpectrum.h"
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
#ifndef PNLSPECTRUM_H
#define PNLSPECTRUM_H

//(*Headers(pnlSpectrum)
#include <wx/panel.h>
class wxSpinEvent;
class wxSplitterWindow;
class wxSpinButton;
class wxCheckBox;
class wxTextCtrl;
class wxSplitterEvent;
class wxComboBox;
class wxGLCanvas;
class wxStaticText;
class wxToggleButton;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxBoxSizer;
class wxButton;
class wxChoice;
//*)
#include <wx/textfile.h>
class wxFile;

#include "OpenGLGraph.h"
//#include <wx/file.h>
class pnlSpectrum: public wxPanel
{
    friend class GraphUpdateThread;
	public:
        const static int GRAPH_UPDATE_MESSAGE_ID;

        const static int FFT_FILE_OK_BTN_MESSAGE_ID;

		pnlSpectrum(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString str="");
		virtual ~pnlSpectrum();

		void onChipConnect();
        void onChipDisconnect();
        void PrintStatus(const char *msg);
        void Initialize();
        void RedrawGraphs();
        void UpdatePwrGraph();
        void CalculatePwrAve();

        void SendSettings();
        void ReadSettings();
        void GetConfiguration();

        void StartCapturing();
        void StopCapturing();
        bool OpenFFTfile();
        wxFile *FFTfilePtr;
        wxFile *m_FFTFileClassPtr;
// NB: use of the define would require include of ..\globals.h
//#ifdef CSV_DEBUG
        wxFile *m_CSVFileClassPtr;
//#endif
        bool m_MaxHold;
        bool OpenPWRfile();
        wxFile *m_PWRFileClassPtr;
        double m_RxFreq;
        float m_frequencyStep;  //value for incrementing or decrementing frequency
        int m_RxVGA1Sel;
        int m_RxVGA2Sel;
        wxTextFile *m_CFG_File;

        bool IsCapturingData();
        bool m_capturingData;
        bool m_backgroundCalculated;
        double m_PwrRefScale;
        const char *m_PwrRefScaleUnits;
        double m_MseAccum;
        double m_PwrAve;
        int m_PwrAveCount;

	    wxTimer* m_updateTimer;
	    void shutdown();
	    void EnableFFTRecord(bool enabled);
	    void EnablePWRRecord(bool enabled);
        void SuffixFFTFileName();
        void SuffixPWRFileName();
//	    void OnFFTfileOKbtnClick(wxCommandEvent& event);
        void OnFFTfileYESbtnClick(wxCommandEvent& event);
        int m_PwrIntTime;
        void ResetMaxHold();
		//(*Declarations(pnlSpectrum)
		wxStaticText* StaticText10;
		wxStaticText* txtOkToChange;
		wxStaticText* StaticText9;
		wxSpinButton* spinFFTsamples;
		wxFlexGridSizer* FlexGridSizer4;
		wxPanel* Panel5;
		wxToggleButton* PwrRef;
		OpenGLGraph* oglPWRChart;
		wxCheckBox* chkAutoscalePwrX;
		wxComboBox* cmbRFInputSelection;
		wxButton*  RecordPWR;
		wxCheckBox* chkAutoscalePwrY;
		wxCheckBox* chkUpdateGraphs;
		wxComboBox* cmbLNAGainMode;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxCheckBox* chkQchannelEnabled;
		wxButton* FFTRec_btn;
		wxStaticText* StaticText14;
		wxChoice* Integration_Time;
		wxStaticText* StaticText6;
		wxSplitterWindow* SplitterWindow2;
		wxSpinCtrl* spinCenterFreq;
		wxTextCtrl* DCOffsetSkew;
		wxPanel* Panel9;
		wxStaticText* StaticText8;
		wxButton* Apply_btn;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		wxPanel* Panel8;
		wxPanel* Panel1;
		wxStaticText* lblDataRate;
		wxCheckBox* AutoDCCorrection;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxTextCtrl* txtFFTsamples;
		wxComboBox* cmbRxFEVGA1;
		wxButton* DCOffsetCorrection;
		wxPanel* Panel6;
		wxPanel* Panel3;
		wxButton* btnStartCapture;
		wxComboBox* cmbRxVGA2;
		wxSpinCtrl* spinAvgCount;
		wxTextCtrl* FFTsREC;
		wxStaticText* StaticText5;
		wxSpinCtrl* PwrSpan;
		wxStaticText* StaticText7;
		wxCheckBox* chkAutoRestart;
		wxButton* btnStopCapture;
		wxPanel* Panel7;
		wxButton* btnAddMarker;
		wxButton* btnRemoveMarker;
		OpenGLGraph* ogl_FFTline;
		wxComboBox* cmbLNASelection;
		wxButton* MaxHold;
		wxStaticText* lblFPS;
		wxComboBox* cmbRxFilter;
		wxTextCtrl* txtRxFrequencyMHz;
		wxStaticText* StaticText15;
		wxSpinCtrl* spinSpanFreq;
		wxStaticText* StaticText12;
		wxPanel* Panel2;
		OpenGLGraph* ogl_IQscatter;
		wxBoxSizer* BoxSizer3;
		wxSplitterWindow* SplitterWindow1;
		wxCheckBox* chkIchannelEnabled;
		wxStaticText* StaticText4;
		wxStaticText* StaticText17;
		wxCheckBox* chkAverage;
		wxStaticText* DCOffsetSkewLabel;
		wxStaticText* StaticText16;
		OpenGLGraph* ogl_IQline;
		wxSpinCtrl* spinSamplingFreq;
		//*)

	protected:

		//(*Identifiers(pnlSpectrum)
		static const long ID_CHECKBOX3B;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT16;
		static const long ID_PANEL1;
		static const long ID_GLCANVAS1;
		static const long ID_PANEL6;
		static const long ID_GLCANVAS2;
		static const long ID_PANEL7;
		static const long ID_SPLITTERWINDOW2;
		static const long ID_GLCANVAS3;
		static const long ID_STATICTEXT12;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT13;
		static const long ID_SPINCTRL2;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON4;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT17;
		static const long ID_BUTTON7;
		static const long ID_PANEL8;
		static const long ID_PANEL3;
		static const long ID_SPLITTERWINDOW1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_CHECKBOX1;
		static const long ID_SPINCTRL4;
		static const long ID_STATICTEXT14;
		static const long ID_TEXTCTRL3;
		static const long ID_SPINBUTTON3;
		static const long ID_STATICTEXT15;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT21;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT6;
		static const long ID_COMBOBOX2;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_TOGGLEBUTTON1;
		static const long ID_BUTTON10;
		static const long ID_BUTTON8;
		static const long ID_CHECKBOX2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL4;
		static const long ID_GLCANVAS4;
		static const long ID_CHECKBOX1B;
		static const long ID_CHECKBOX1C;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL5;
		static const long ID_STATICTEXT4;
		static const long ID_CHOICE1;
		static const long ID_PANEL5;
		static const long ID_PANEL10;
		static const long ID_PANEL2;
		static const long ID_DB_TRIGGER;
		//*)

	private:

	    void initializeGraphs();
		void generateFFTxaxis(float samplingFrequency);
		void changeSamplingFrequency(float samplingFrequency);
        float *m_fftxaxisValues;
        void disableDCComparators();
        void initializeInterfaceValues();
		bool allocateMemory(int samples);
        void freeMemory();
//        void SuffixFFTFileName();
//        void SuffixPWRFileName();
        void RecordPwrLine(int index,double value);
        int twotoN(int N);
        void SetPwrRangeX();
        void SetPwrRescaleX();
        void SetPwrRangeY();
        void SetPwrRescaleY();

        int m_IQdataSize;
        int m_FFTdataSize;
        int m_PWRdataSize;
        float *m_IchannelData;
        float *m_QchannelData;
        float *m_FFTfrequencies;
        float *m_FFTamplitudes;
        float *m_FFTbackground;
        float *m_FFTbackgroundAvg;
        float *m_FFTbackgroundDb;
        float *m_FFTMaxAmplitudes;
        float *m_PWRvalues;
        float m_PwrMax;
        float m_PwrMin;

        float *samplesXaxis;
        float *PwrcountXaxis;
        int m_PwrCount;
        int m_Index;
        int m_CurPwrX_Max;
        int m_curPwrX_min;
        int m_curPwrX_span;
        int m_curPwrX_ctr;
//        int m_curYstep;
//        float *m_YSPan;
//        float *m_YCent;
        bool m_PlottingLow;
        bool m_ADFInitialized;

        float m_TxFreq;

        bool m_addingMarkers;

        int m_FFTsamplesCount;
        int m_FFTCounter;
        int m_FFTsRecorded;
        unsigned long m_samplingFrequency;


        float **m_FFTamplitudesBuffer;
        const int m_buffersCount;
        int m_buffersCountMask;
        int bufferPos;

        bool m_updating;
        bool m_restarting;
        wxDateTime m_dtLastRestart;
        int m_restart_step;
        long m_time;
        long m_lastUpdate;
        int m_frames;
        bool m_firststart;
        int m_CurPwrSpan;
        int m_PWRRecordCount;
        double m_PWRRecordAccum;
        float m_FFTChartCenter;
        float m_FFTChartSpan;

		//(*Handlers(pnlSpectrum)
		void OnGLCanvas1Paint(wxPaintEvent& event);
		void OnbtnStartCaptureClick(wxCommandEvent& event);
		void OnbtnStopCaptureClick(wxCommandEvent& event);
		void OnchkIchannelEnabledClick(wxCommandEvent& event);
		void OnchkQchannelEnabledClick(wxCommandEvent& event);
		void OnchkDCcorrectionClick(wxCommandEvent& event);
		void OnrgrDataSourceSelect(wxCommandEvent& event);
		void OnrgrTxDataSourceSelect(wxCommandEvent& event);
		void OnComboBox1Selected(wxCommandEvent& event);
		void OncmbTxFilterSelected(wxCommandEvent& event);
		void OncmbRxFilterSelected(wxCommandEvent& event);
		void OncmbTxVGA1Selected(wxCommandEvent& event);
		void OncmbTxVGA2Selected(wxCommandEvent& event);
		void OncmbRxFEVGA1Selected(wxCommandEvent& event);
		void OncmbRxVGA2Selected(wxCommandEvent& event);
		void OncmbLNAGainModeSelected(wxCommandEvent& event);
		void OnbtnSetRxFreqClick(wxCommandEvent& event);
		void OnbtnSetTxFreqClick(wxCommandEvent& event);
		void OnSpinButton1Change(wxSpinEvent& event);
		void OnSpinButton1ChangeUp(wxSpinEvent& event);
		void OnSpinButton1ChangeDown(wxSpinEvent& event);
		void OnSpinButton2ChangeUp(wxSpinEvent& event);
		void OnSpinButton2ChangeDown(wxSpinEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		void OnbtnRemoveMarkerClick(wxCommandEvent& event);
		void OnbtnAddMarkerClick(wxCommandEvent& event);
		void Onogl_FFTlineLeftDown(wxMouseEvent& event);
		void OnchkIchannelEnabledClick1(wxCommandEvent& event);
		void OnchkQchannelEnabledClick1(wxCommandEvent& event);
		void OnspinCenterFreqChange(wxSpinEvent& event);
		void OnspinSpanFreqChange(wxSpinEvent& event);
		void OnspinFFTsamplesChange(wxSpinEvent& event);
		void OnspinAvgCountChange(wxSpinEvent& event);
		void OnGLCanvas1Paint1(wxPaintEvent& event);
		void OnGLCanvas1Paint2(wxPaintEvent& event);
		void Onogl_FFTlinePaint(wxPaintEvent& event);
		void OnspinSamplingFreqChange(wxSpinEvent& event);
		void OnspinSamplingFreqChange1(wxSpinEvent& event);
		void OnPanel2Paint(wxPaintEvent& event);
		void OnPanel2Paint1(wxPaintEvent& event);
		void OnApplyClick(wxCommandEvent& event);
		void OnApply_btnClick(wxCommandEvent& event);
		void OntxtRxFrequencyGHzTextEnter(wxCommandEvent& event);
		void OnspinSamplingFreqChange2(wxSpinEvent& event);
		void OntxtRxFrequencyGHzTextEnter1(wxCommandEvent& event);
		void Onogl_IQlinePaint(wxPaintEvent& event);
		void Onogl_FFTlinePaint1(wxPaintEvent& event);
		void Onogl_FFTlinePaint2(wxPaintEvent& event);
		void OnPanel1Paint(wxPaintEvent& event);
		void Onogl_PWR_canvasPaint(wxPaintEvent& event);
		void OnoglPWRChartPaint(wxPaintEvent& event);
		void OnoglPWRChartPaint1(wxPaintEvent& event);
		void OnoglPWRChartLeftDown(wxMouseEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnRecordFFTClick(wxCommandEvent& event);
		void OnStopFFTRecClick(wxCommandEvent& event);
		void OnchkUpdateGraphsClick(wxCommandEvent& event);
		void OnoglPWRChartPaint2(wxPaintEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnPwrRefClick(wxCommandEvent& event);
		void OnPanel5Paint(wxPaintEvent& event);
		void OnPwrSpanChange(wxSpinEvent& event);
		void OnPwrSpanChange1(wxSpinEvent& event);
		void OnPwrRecordClick(wxCommandEvent& event);
		void OntxtRxFrequencyMHzText(wxCommandEvent& event);
		void OnIntegration_TimeSelect(wxCommandEvent& event);
		void OntxtFFTsamplesText(wxCommandEvent& event);
		void OnMaxHoldClick(wxCommandEvent& event);
		void OnMaxHoldClick1(wxCommandEvent& event);
		void OnDCOffsetCorrectionClick(wxCommandEvent& event);
		void OncmbLNASelectionSelected(wxCommandEvent& event);
		void OncmbRFInputSelectionSelected(wxCommandEvent& event);
		//*)

		void UpdateGraphs(wxTimerEvent &event);

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
