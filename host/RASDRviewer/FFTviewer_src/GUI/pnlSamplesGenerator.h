#ifndef PNLSAMPLESGENERATOR_H
#define PNLSAMPLESGENERATOR_H

//(*Headers(pnlSamplesGenerator)
#include <wx/panel.h>
class wxSpinEvent;
class wxTextCtrl;
class wxRadioBox;
class wxGLCanvas;
class wxStaticText;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxButton;
//*)
#include "OpenGLGraph.h"

class pnlSamplesGenerator: public wxPanel
{
	public:

		pnlSamplesGenerator(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style = 0, wxString str = "");
		virtual ~pnlSamplesGenerator();

		//(*Declarations(pnlSamplesGenerator)
		wxStaticText* StaticText2;
		wxSpinCtrl* spinSamplingRate;
		wxTextCtrl* txtFreq;
		wxPanel* Panel1;
		wxButton* btnStopGenerating;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* btnStartGenerating;
		wxRadioBox* rgrDataSource;
		wxStaticText* StaticText5;
		wxSpinCtrl* spinAmplitude;
		OpenGLGraph* glSignalGraph;
		wxPanel* Panel2;
		wxStaticText* StaticText4;
		wxTextCtrl* txtHexInput;
		wxButton* btnOpenFile;
		//*)

	protected:

		//(*Identifiers(pnlSamplesGenerator)
		static const long ID_RADIOBOX1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL2;
		static const long ID_PANEL1;
		static const long ID_GLCANVAS1;
		static const long ID_PANEL2;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL2;
		//*)

	private:
        float *m_isamples;
        float *m_qsamples;
        float *m_xaxis;
		//(*Handlers(pnlSamplesGenerator)
		void OnrgrDataSourceSelect(wxCommandEvent& event);
		void OnbtnStartGeneratingClick(wxCommandEvent& event);
		void OnbtnStopGeneratingClick(wxCommandEvent& event);
		void OnbtnOpenFileClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
