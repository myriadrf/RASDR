#ifndef PNLADDC_H
#define PNLADDC_H

//(*Headers(pnlADDC)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxStaticBoxSizer;
//*)

class pnlADDC: public wxPanel
{
	public:

		pnlADDC(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize,int styles = 0, wxString idname="");
		virtual ~pnlADDC();

		bool sendChanges;
		void FillComboBoxes();
        void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();
        void SetGuiDecode(int Decode);

        bool UpdateGUI();

		//(*Declarations(pnlADDC)
		wxStaticText* StaticText10;
		wxRadioBox* rgrADCAmp24Stage1BasUp;
		wxStaticText* StaticText9;
		wxRadioBox* rgrRX_FSYNC_P;
		wxRadioBox* rgrDACReferenceCurrentResistor;
		wxRadioBox* rgrDecode;
		wxComboBox* cmbRefAmpsBiasUp;
		wxComboBox* cmbBandgapGain;
		wxStaticText* StaticText13;
		wxComboBox* cmbDACFullScaleOutputCurrent;
		wxStaticText* StaticText2;
		wxRadioBox* rgrTX_FSYNC_P;
		wxCheckBox* chkEN_DAC;
		wxStaticText* StaticText14;
		wxComboBox* cmbRefResistorBiasAdj;
		wxCheckBox* chkEN_ADC_REF;
		wxStaticText* StaticText6;
		wxComboBox* cmbClockNonOverlapAdjust;
		wxComboBox* cmbRefBiasDn;
		wxComboBox* cmbRefBufferBoost;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxCheckBox* chbEN_ADC_DAC;
		wxCheckBox* chkEN_ADC_Q;
		wxRadioBox* rgrADCAmp1Stage1BasUp;
		wxRadioBox* rgrDAC_CLK_P;
		wxCheckBox* chkEN_M_REF;
		wxComboBox* cmbCoomonModeAdj;
		wxComboBox* cmbRefAmpsBiasAdj;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxComboBox* cmbBandgapTemp;
		wxComboBox* cmbMainBiasDN;
		wxComboBox* cmbDACInternalOutputLoadResistor;
		wxCheckBox* chkInputBufferDisable;
		wxRadioBox* rgrADCBiasResistorAdjust;
		wxRadioBox* rgrADCAmp24Stage2BasUp;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxCheckBox* chkEN_ADC_I;
		wxRadioBox* rgrADCAmp1Stage2BasUp;
		wxRadioBox* rgrTX_INTER;
		wxRadioBox* rgrRX_INTER;
		wxRadioBox* rgrQuantizerBiasUp;
		wxComboBox* cmbRefBiasUp;
		wxStaticText* StaticText4;
		wxComboBox* cmbRefAmpsBiasDn;
		wxComboBox* cmbRefGainAdj;
		wxComboBox* cmbADCSamplingPhase;
		wxStaticText* StaticText16;
		wxRadioBox* rgrInputBufferBiasUp;
		//*)

	protected:

		//(*Identifiers(pnlADDC)
		static const long ID_RADIOBOX1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_RADIOBOX10;
		static const long ID_RADIOBOX11;
		static const long ID_RADIOBOX12;
		static const long ID_RADIOBOX13;
		static const long ID_RADIOBOX14;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_COMBOBOX3;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT15;
		static const long ID_COMBOBOX15;
		static const long ID_RADIOBOX2;
		static const long ID_STATICTEXT16;
		static const long ID_COMBOBOX16;
		static const long ID_CHECKBOX7;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_COMBOBOX8;
		static const long ID_COMBOBOX9;
		static const long ID_COMBOBOX10;
		static const long ID_COMBOBOX11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_COMBOBOX12;
		static const long ID_COMBOBOX13;
		static const long ID_COMBOBOX14;
		static const long ID_RADIOBOX9;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX4;
		static const long ID_RADIOBOX5;
		static const long ID_RADIOBOX6;
		static const long ID_RADIOBOX7;
		static const long ID_RADIOBOX8;
		//*)

	private:

		//(*Handlers(pnlADDC)
		void rgrRX_FSYNC_PClick(wxCommandEvent& event);
		void rgrRX_INTERClick(wxCommandEvent& event);
		void rgrDAC_CLK_PClick(wxCommandEvent& event);
		void rgrTX_FSYNC_PClick(wxCommandEvent& event);
		void rgrTX_INTERClick(wxCommandEvent& event);
		void chkEN_DACClick(wxCommandEvent& event);
		void chkEN_ADC_IClick(wxCommandEvent& event);
		void chkEN_ADC_QClick(wxCommandEvent& event);
		void chkEN_ADC_REFClick(wxCommandEvent& event);
		void chkEN_M_REFClick(wxCommandEvent& event);
		void cmbBandgapTempChange(wxCommandEvent& event);
		void cmbBandgapGainChange(wxCommandEvent& event);
		void cmbRefAmpsBiasAdjChange(wxCommandEvent& event);
		void cmbRefAmpsBiasUpChange(wxCommandEvent& event);
		void cmbRefAmpsBiasDnChange(wxCommandEvent& event);
		void cmbRefResistorBiasAdjChange(wxCommandEvent& event);
		void cmbRefBiasUpChange(wxCommandEvent& event);
		void cmbRefBiasDnChange(wxCommandEvent& event);
		void cmbRefGainAdjChange(wxCommandEvent& event);
		void cmbCoomonModeAdjChange(wxCommandEvent& event);
		void cmbRefBufferBoostChange(wxCommandEvent& event);
		void chkInputBufferDisableClick(wxCommandEvent& event);
		void cmbADCSamplingPhaseChange(wxCommandEvent& event);
		void cmbClockNonOverlapAdjustChange(wxCommandEvent& event);
		void rgrADCBiasResistorAdjustClick(wxCommandEvent& event);
		void cmbMainBiasDNChange(wxCommandEvent& event);
		void rgrADCAmp1Stage1BasUpClick(wxCommandEvent& event);
		void rgrADCAmp24Stage1BasUpClick(wxCommandEvent& event);
		void rgrADCAmp1Stage2BasUpClick(wxCommandEvent& event);
		void rgrADCAmp24Stage2BasUpClick(wxCommandEvent& event);
		void rgrQuantizerBiasUpClick(wxCommandEvent& event);
		void rgrInputBufferBiasUpClick(wxCommandEvent& event);
		void cmbDACInternalOutputLoadResistorChange(wxCommandEvent& event);
		void rgrDACReferenceCurrentResistorClick(wxCommandEvent& event);
		void cmbDACFullScaleOutputCurrentChange(wxCommandEvent& event);
		void rgrDecodeClick(wxCommandEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
