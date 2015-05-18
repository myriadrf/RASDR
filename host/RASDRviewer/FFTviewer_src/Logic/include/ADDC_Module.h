// -----------------------------------------------------------------------------
// FILE: 		ADDC_Module.h
// DESCRIPTION:	Header for ADDC_Module.cpp
// DATE:
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef ADDC_Module_H
#define ADDC_Module_H
//---------------------------------------------------------------------------

#include "common.h"
#include <iostream>
#include "iniParser.h"
#include "Main_Module.h"

typedef INI <string, string, string> ini_t;
//---------------------------------------------------------------------------
class ADDC_Module
{
public:
	ADDC_Module();
	~ADDC_Module();
	void Initialize(Main_Module *pMain, char MAddr);
	char getAddr();
	void SetDefaults();
	void SaveConf(ini_t *pini);
	void ReadConf(ini_t *pini);
	bool ChipVsGui(sPrData &m_psD, ofstream &out, string Caption, bool bWrAll);
	void MakeRVFFile(sPrData &m_psD, ofstream &out);        //Writes Register - Value format to the file.
	void MakeRFIFFile(sPrData &m_psD, ofstream &out, const char *FRIF_SPI_A);        //Writes RFIF register format to the file.
	bool SetGUIUnderReadback(sPrData &m_psD);
	void MakeRegisterFile(sPrData &m_psD, ofstream &out);

	void CustSet_cmbCoomonModeAdj(int Ind);

	void setRX_FSYNC_P(int index);
	int getRX_FSYNC_P();

	void setRX_INTER(int index);
	int getRX_INTER();

	void setDAC_CLK_P(int index);
	int getDAC_CLK_P();

	void setTX_FSYNC_P(int index);
	int getTX_FSYNC_P();

	void setTX_INTER(int index);
	int getTX_INTER();

	void setEN_DAC(bool state);
	bool getEN_DAC();

	void setEN_ADC_DAC(bool state);
	bool getEN_ADC_DAC();

	void setEN_ADC_I(bool state);
	bool getEN_ADC_I();

	void setEN_ADC_Q(bool state);
	bool getEN_ADC_Q();

	void setEN_ADC_REF(bool state);
	bool getEN_ADC_REF();

	void setEN_M_REF(bool state);
	bool getEN_M_REF();

	void setBandgapTemp(int index);
	int getBandgapTemp();

	void setBandgapGain(int index);
	int getBandgapGain();

	void setRefAmpsBiasAdj(int index);
	int getRefAmpsBiasAdj();

	void setRefAmpsBiasUp(int index);
	int getRefAmpsBiasUp();

	void setRefAmpsBiasDn(int index);
	int getRefAmpsBiasDn();

	void setRefResistorBiasAdj(int index);
	int getRefResistorBiasAdj();

	void setRefBiasUp(int index);
	int getRefBiasUp();

	void setRefBiasDn(int index);
	int getRefBiasDn();

	void setRefGainAdj(int index);
	int getRefGainAdj();

	void setCoomonModeAdj(int index);
	int getCoomonModeAdj();

	void setRefBufferBoost(int index);
	int getRefBufferBoost();

	void setInputBufferDisable(bool state);
	bool getInputBufferDisable();

	void setADCSamplingPhase(int index);
	int getADCSamplingPhase();

	void setClockNonOverlapAdjust(int index);
	int getClockNonOverlapAdjust();

	void setADCBiasResistorAdjust(int index);
	int getADCBiasResistorAdjust();

	void setMainBiasDN(int index);
	int getMainBiasDN();

	void setADCAmp1Stage1BiasUp(int index);
	int getADCAmp1Stage1BiasUp();

	void setADCAmp24Stage1BiasUp(int index);
	int getADCAmp24Stage1BiasUp();

	void setADCAmp1Stage2BiasUp(int index);
	int getADCAmp1Stage2BiasUp();

	void setADCAmp24Stage2BiasUp(int index);
	int getADCAmp24Stage2BiasUp();

	void setQuantizerBiasUp(int index);
	int getQuantizerBiasUp();

	void setInputBufferBiasUp(int index);
	int getInputBufferBiasUp();

	void setDACInternalOutputLoadResistor(int index);
	int getDACInternalOutputLoadResistor();

	void setDACReferenceCurrentResistor(int index);
	int getDACReferenceCurrentResistor();

	void setDACFullScaleOutputCurrent(int index);
	int getDACFullScaleOutputCurrent();

	void setDecode(int index);
	int getDecode();

protected:
	char m_cMAddr;
	sPrData m_psD;
	bool m_bAllowSend;

private:
	Main_Module *m_MainModule;

	SelectionContainer rgrRX_FSYNC_P;
	SelectionContainer rgrRX_INTER;
	SelectionContainer rgrDAC_CLK_P;
	SelectionContainer rgrTX_FSYNC_P;
	SelectionContainer rgrTX_INTER;
	SelectionContainer cmbBandgapTemp;
	SelectionContainer cmbBandgapGain;
	SelectionContainer cmbRefAmpsBiasAdj;
	SelectionContainer cmbRefAmpsBiasUp;
	SelectionContainer cmbRefAmpsBiasDn;
	SelectionContainer cmbCoomonModeAdj;
	SelectionContainer cmbRefGainAdj;
	SelectionContainer cmbRefResistorBiasAdj;
	SelectionContainer cmbRefBiasUp;
	SelectionContainer cmbRefBiasDn;
	SelectionContainer cmbRefBufferBoost;
	SelectionContainer rgrADCAmp1Stage2BasUp;
	SelectionContainer rgrADCAmp24Stage2BasUp;
	SelectionContainer rgrQuantizerBiasUp;
	SelectionContainer rgrInputBufferBiasUp;
	SelectionContainer rgrADCAmp1Stage1BasUp;
	SelectionContainer rgrADCAmp24Stage1BasUp;
	SelectionContainer rgrADCBiasResistorAdjust;
	SelectionContainer rgrDACReferenceCurrentResistor;
	SelectionContainer cmbDACInternalOutputLoadResistor;
	SelectionContainer cmbDACFullScaleOutputCurrent;
	SelectionContainer cmbMainBiasDN;
	SelectionContainer cmbClockNonOverlapAdjust;
	SelectionContainer cmbADCSamplingPhase;
	BoolCheckBox chkInputBufferDisable;
	BoolCheckBox chkEN_ADC_I;
	BoolCheckBox chkEN_ADC_Q;
	BoolCheckBox chkEN_ADC_REF;
	BoolCheckBox chkEN_DAC;
	BoolCheckBox chkEN_M_REF;
	BoolCheckBox chbEN_ADC_DAC;
	SelectionContainer rgrDecode;
};

#endif  // ADDC_Module_H


