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
class wxRadioBox;
class wxGLCanvas;
class wxStaticText;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxBoxSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

#include "OpenGLGraph.h"

class pnlSpectrum: public wxPanel
{
    friend class GraphUpdateThread;
	public:
        const static int GRAPH_UPDATE_MESSAGE_ID;
		pnlSpectrum(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString str="");
		virtual ~pnlSpectrum();

		void onChipConnect();
        void onChipDisconnect();
        void PrintStatus(const char *msg);
        void Initialize();
        void RedrawGraphs();

        void SendSettings();
        void ReadSettings();

        void StartCapturing();
        void StopCapturing();

        bool IsCapturingData();

		//(*Declarations(pnlSpectrum)
		wxStaticText* StaticText10;
		wxRadioBox* rgrTxDataSource;
		wxStaticText* StaticText9;
		wxSpinButton* spinFFTsamples;
		wxComboBox* cmbTxVGA1;
		wxCheckBox* chkUpdateGraphs;
		wxComboBox* cmbLNAGainMode;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxCheckBox* chkQchannelEnabled;
		wxPanel* Panel4;
		wxStaticText* StaticText14;
		wxStaticText* StaticText6;
		wxComboBox* cmbTxVGA2;
		wxSplitterWindow* SplitterWindow2;
		wxSpinCtrl* spinCenterFreq;
		wxPanel* Panel9;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxPanel* Panel8;
		wxPanel* Panel1;
		wxStaticText* lblDataRate;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxTextCtrl* txtFFTsamples;
		wxTextCtrl* txtTxFrequencyGHz;
		wxComboBox* cmbRxFEVGA1;
		wxButton* btnSetRxFreq;
		wxPanel* Panel6;
		wxPanel* Panel3;
		wxButton* btnStartCapture;
		wxComboBox* cmbRxVGA2;
		wxSpinButton* SpinButton1;
		wxCheckBox* chkDCcorrection;
		wxRadioBox* rgrDataSource;
		wxSpinCtrl* spinAvgCount;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* btnStopCapture;
		wxPanel* Panel7;
		wxSpinButton* SpinButton2;
		wxButton* btnAddMarker;
		wxComboBox* cmbTxFilter;
		wxButton* btnRemoveMarker;
		OpenGLGraph* ogl_FFTline;
		wxButton* btnSetTxFreq;
		wxStaticText* lblFPS;
		wxComboBox* cmbRxFilter;
		wxSpinCtrl* spinSpanFreq;
		wxStaticText* StaticText12;
		wxTextCtrl* txtRxFrequencyGHz;
		wxPanel* Panel2;
		OpenGLGraph* ogl_IQscatter;
		wxSplitterWindow* SplitterWindow1;
		wxCheckBox* chkIchannelEnabled;
		wxStaticText* StaticText4;
		wxCheckBox* chkAverage;
		OpenGLGraph* ogl_IQline;
		wxSpinCtrl* spinSamplingFreq;
		//*)

	protected:

		//(*Identifiers(pnlSpectrum)
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
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_STATICTEXT12;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT13;
		static const long ID_SPINCTRL2;
		static const long ID_PANEL4;
		static const long ID_PANEL3;
		static const long ID_SPLITTERWINDOW1;
		static const long ID_PANEL9;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_CHECKBOX1;
		static const long ID_SPINCTRL4;
		static const long ID_STATICTEXT14;
		static const long ID_TEXTCTRL3;
		static const long ID_SPINBUTTON3;
		static const long ID_STATICTEXT15;
		static const long ID_SPINCTRL3;
		static const long ID_CHECKBOX2;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL1;
		static const long ID_SPINBUTTON1;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT4;
		static const long ID_COMBOBOX3;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL2;
		static const long ID_SPINBUTTON2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_PANEL10;
		static const long ID_PANEL2;
		//*)

	private:
	    wxTimer* m_updateTimer;

	    void initializeGraphs();
		void generateFFTxaxis(unsigned long samplingFrequency);
		void changeSamplingFrequency(long samplingFrequency);
        float *m_fftxaxisValues;
        void disableDCComparators();
        void initializeInterfaceValues();
		void allocateMemory(unsigned int samples);
        void freeMemory();

        int m_IQdataSize;
        int m_FFTdataSize;
        float *m_IchannelData;
        float *m_QchannelData;
        float *m_FFTfrequencies;
        float *m_FFTamplitudes;

        float *samplesXaxis;
        float m_frequencyStep;  //value for incrementing or decrementing frequency

        float m_TxFreq;
        float m_RxFreq;

        bool m_addingMarkers;

        int m_FFTsamplesCount;
        unsigned long m_samplingFrequency;


        float **m_FFTamplitudesBuffer;
        const int m_buffersCount;
        int m_buffersCountMask;
        int bufferPos;

        bool m_capturingData;
        bool m_updating;
        long m_time;
        long m_lastUpdate;
        int m_frames;

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
		//*)

		void UpdateGraphs(wxTimerEvent &event);

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
