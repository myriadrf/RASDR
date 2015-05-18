// -----------------------------------------------------------------------------
// FILE: 		ADDC_Module.cpp
// DESCRIPTION:	DAC and ADC control
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ---------------------------------------------------------------------------
#include "ADDC_Module.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
// ---------------------------------------------------------------------------
// 0x7
#define            EN_ADC_DAC_r07_b77() ((m_psD.cDataR[0x07] & 0x80) >> 7)
#define        DECODE_ADC_DAC_r07_b66() ((m_psD.cDataR[0x07] & 0x40) >> 6)
#define           TX_CTRL1_64_r07_b53() ((m_psD.cDataR[0x07] & 0x38) >> 3)
#define           TX_CTRL1_33_r07_b22() ((m_psD.cDataR[0x07] & 0x04) >> 2)
#define           TX_CTRL1_10_r07_b10() ((m_psD.cDataR[0x07] & 0x03) >> 0)
// 0x8
#define            RX_CTRL1_76_r08_b76() ((m_psD.cDataR[0x08] & 0xC0) >> 6)
#define            RX_CTRL1_54_r08_b54() ((m_psD.cDataR[0x08] & 0x30) >> 4)
#define            RX_CTRL1_30_r08_b30() ((m_psD.cDataR[0x08] & 0x0F) >> 0)
// 0x9
#define            RX_CTRL2_76_r09_b65() ((m_psD.cDataR[0x09] & 0x60) >> 5)
#define            RX_CTRL2_54_r09_b43() ((m_psD.cDataR[0x09] & 0x18) >> 3)
#define            RX_CTRL2_32_r09_b21() ((m_psD.cDataR[0x09] & 0x06) >> 1)
#define            RX_CTRL2_00_r09_b00() ((m_psD.cDataR[0x09] & 0x01) >> 0)
// 0xA
#define           MISC_CTRL_99_r0A_b77() ((m_psD.cDataR[0x0A] & 0x80) >> 7)
#define           MISC_CTRL_88_r0A_b66() ((m_psD.cDataR[0x0A] & 0x40) >> 6)
#define           MISC_CTRL_77_r0A_b55() ((m_psD.cDataR[0x0A] & 0x20) >> 5)
#define           MISC_CTRL_66_r0A_b44() ((m_psD.cDataR[0x0A] & 0x10) >> 4)
#define           MISC_CTRL_55_r0A_b33() ((m_psD.cDataR[0x0A] & 0x08) >> 3)
#define            RX_CTRL3_77_r0A_b22() ((m_psD.cDataR[0x0A] & 0x04) >> 2)
#define            RX_CTRL3_10_r0A_b10() ((m_psD.cDataR[0x0A] & 0x03) >> 0)
// 0xB
#define            RX_CTRL4_76_r0B_b76() ((m_psD.cDataR[0x0B] & 0xC0) >> 6)
#define            RX_CTRL4_54_r0B_b54() ((m_psD.cDataR[0x0B] & 0x30) >> 4)
#define            RX_CTRL4_32_r0B_b32() ((m_psD.cDataR[0x0B] & 0x0C) >> 2)
#define            RX_CTRL4_10_r0B_b10() ((m_psD.cDataR[0x0B] & 0x03) >> 0)
// 0xC
#define            RX_CTRL5_76_r0C_b76() ((m_psD.cDataR[0x0C] & 0xC0) >> 6)
#define            RX_CTRL5_54_r0C_b54() ((m_psD.cDataR[0x0C] & 0x30) >> 4)
#define            RX_CTRL5_32_r0C_b32() ((m_psD.cDataR[0x0C] & 0x0C) >> 2)
#define            RX_CTRL5_10_r0C_b10() ((m_psD.cDataR[0x0C] & 0x03) >> 0)
// 0xD
#define           REF_CTRL0_74_r0D_b74() ((m_psD.cDataR[0x0D] & 0xF0) >> 4)
#define           REF_CTRL0_30_r0D_b30() ((m_psD.cDataR[0x0D] & 0x0F) >> 0)
// 0xE
#define           REF_CTRL1_76_r0E_b76() ((m_psD.cDataR[0x0E] & 0xC0) >> 6)
#define           REF_CTRL1_54_r0E_b54() ((m_psD.cDataR[0x0E] & 0x30) >> 4)
#define           REF_CTRL1_30_r0E_b30() ((m_psD.cDataR[0x0E] & 0x0F) >> 0)
// 0xF
#define           MISC_CTRL_44_r0F_b44() ((m_psD.cDataR[0x0F] & 0x10) >> 4)
#define           MISC_CTRL_33_r0F_b33() ((m_psD.cDataR[0x0F] & 0x08) >> 3)
#define           MISC_CTRL_22_r0F_b22() ((m_psD.cDataR[0x0F] & 0x04) >> 2)
#define           MISC_CTRL_11_r0F_b11() ((m_psD.cDataR[0x0F] & 0x02) >> 1)
#define           MISC_CTRL_00_r0F_b00() ((m_psD.cDataR[0x0F] & 0x01) >> 0)

#define FRIF_DIR_W "rfIf Direct=16,"
// #define FRIF_SPI_A ",20"

// ---------------------------------------------------------------------------
ADDC_Module::ADDC_Module()
{
	m_MainModule = NULL;
}

ADDC_Module::~ADDC_Module()
{
}
/**
	@return Returns ADDC module address inside chip.
*/
char ADDC_Module::getAddr()
{
	return m_cMAddr;
}

/**
	@brief Initializes module address inside chip and sets default configuration settings.
*/
void ADDC_Module::Initialize(Main_Module *pMain, char MAddr)
{
	m_MainModule = pMain;
	m_cMAddr = MAddr;

	SetDefaults();
};

/**
	@brief Sets default configuration settings.
*/
void ADDC_Module::SetDefaults()
{
	m_bAllowSend = false;

	// EN_ADC_DAC
	chbEN_ADC_DAC.checked = true;

	// Decode
	rgrDecode.itemIndex = 0;

	// ============== ENABLE CONTROL REGISTERS ==========

	// Rx Fsync Polarity, frame start
	rgrRX_FSYNC_P.itemIndex = 0;

	// Rx Interleave Mode
	rgrRX_INTER.itemIndex = 0;

	// Dac Clk Edge Polarity
	rgrDAC_CLK_P.itemIndex = 1;

	// Tx Fsync Polarity, frame start
	rgrTX_FSYNC_P.itemIndex = 0;

	// Tx Interleave Mode
	rgrTX_INTER.itemIndex = 0;

	// Enable DAC
	chkEN_DAC.checked = true;

	// Enable ADC1 (I Channel)
	chkEN_ADC_I.checked = true;

	// Enable ADC2 (Q Channel)
	chkEN_ADC_Q.checked = true;

	// Enable ADC reference
	chkEN_ADC_REF.checked = true;

	// Enable master reference
	chkEN_M_REF.checked = true;

	// ============== REFERENECE CONTROL REGISTERS 0 ==========
	// Bandgap Temperature Coefficient Control
	cmbBandgapTemp.clear();
	cmbBandgapTemp.add("-8 (Min)");
	cmbBandgapTemp.add("-7");
	cmbBandgapTemp.add("-6");
	cmbBandgapTemp.add("-5");
	cmbBandgapTemp.add("-4");
	cmbBandgapTemp.add("-3");
	cmbBandgapTemp.add("-2");
	cmbBandgapTemp.add("-1");
	cmbBandgapTemp.add(" 0 (Nom)");
	cmbBandgapTemp.add(" 1");
	cmbBandgapTemp.add(" 2");
	cmbBandgapTemp.add(" 3");
	cmbBandgapTemp.add(" 4");
	cmbBandgapTemp.add(" 5");
	cmbBandgapTemp.add(" 6");
	cmbBandgapTemp.add(" 7 (Max)");
	cmbBandgapTemp.itemIndex = 8;

	// Bandgap Gain Control
	cmbBandgapGain.clear();
	cmbBandgapGain.add("-8 (Min)");
	cmbBandgapGain.add("-7");
	cmbBandgapGain.add("-6");
	cmbBandgapGain.add("-5");
	cmbBandgapGain.add("-4");
	cmbBandgapGain.add("-3");
	cmbBandgapGain.add("-2");
	cmbBandgapGain.add("-1");
	cmbBandgapGain.add(" 0 (Nom)");
	cmbBandgapGain.add(" 1");
	cmbBandgapGain.add(" 2");
	cmbBandgapGain.add(" 3");
	cmbBandgapGain.add(" 4");
	cmbBandgapGain.add(" 5");
	cmbBandgapGain.add(" 6");
	cmbBandgapGain.add(" 7 (Max)");
	cmbBandgapGain.itemIndex = 8;

	// ============== REFERENECE CONTROL REGISTERS 1 ==========
	// Reference Amps bias adjust
	cmbRefAmpsBiasAdj.clear();
	cmbRefAmpsBiasAdj.add("20uA");
	cmbRefAmpsBiasAdj.add("40uA");
	cmbRefAmpsBiasAdj.add("10uA");
	cmbRefAmpsBiasAdj.add("15uA");
	cmbRefAmpsBiasAdj.itemIndex = 0;

	// Reference Amps bias UP
	cmbRefAmpsBiasUp.clear();
	cmbRefAmpsBiasUp.add("1.0X");
	cmbRefAmpsBiasUp.add("1.5X");
	cmbRefAmpsBiasUp.add("2.0X");
	cmbRefAmpsBiasUp.add("2.5X");
	cmbRefAmpsBiasUp.itemIndex = 0;

	// Reference Amps bias DOWN
	cmbRefAmpsBiasDn.clear();
	for (int i = 0; i < 16; i++)
	{
		cmbRefAmpsBiasDn.add(i);
	};
	cmbRefAmpsBiasDn.itemIndex = 0;

	// ============== ADC CONTROL REGISTERS 1 ==========
	// Reference bias resistor adjust
	cmbRefResistorBiasAdj.clear();
	cmbRefResistorBiasAdj.add("20uA");
	cmbRefResistorBiasAdj.add("40uA");
	cmbRefResistorBiasAdj.add("10uA");
	cmbRefResistorBiasAdj.add("15uA");
	cmbRefResistorBiasAdj.itemIndex = 0;

	// Reference bias UP
	cmbRefBiasUp.clear();
	cmbRefBiasUp.add("1.0X");
	cmbRefBiasUp.add("1.5X");
	cmbRefBiasUp.add("2.0X");
	cmbRefBiasUp.add("2.5X");
	cmbRefBiasUp.itemIndex = 0;

	// Reference bias DN
	cmbRefBiasDn.clear();
	for (int i = 0; i < 16; i++)
	{
		cmbRefBiasDn.add(i);
	};
	cmbRefBiasDn.itemIndex = 0;

	// ============== ADC CONTROL REGISTERS 2 ==========
	// Reference Gain Adjust
	cmbRefGainAdj.clear();
	cmbRefGainAdj.add("1.50V");
	cmbRefGainAdj.add("1.75V");
	cmbRefGainAdj.add("1.00V");
	cmbRefGainAdj.add("1.25V");
	cmbRefGainAdj.itemIndex = 0;

	// Common Mode Adjust
	cmbCoomonModeAdj.clear();
	cmbCoomonModeAdj.add("875mV");
	cmbCoomonModeAdj.add("960mV");
	cmbCoomonModeAdj.add("700mV");
	cmbCoomonModeAdj.add("790mV");
	cmbCoomonModeAdj.itemIndex = 0;

	// Reference Buffer Boost
	cmbRefBufferBoost.clear();
	cmbRefBufferBoost.add("1.0X");
	cmbRefBufferBoost.add("1.5X");
	cmbRefBufferBoost.add("2.0X");
	cmbRefBufferBoost.add("2.5X");
	cmbRefBufferBoost.itemIndex = 0;

	// Input Buffer Disable
	chkInputBufferDisable.checked = true;

	// ============== ADC CONTROL REGISTERS 3 ==========
	// ADC Sampling Phase Select
	cmbADCSamplingPhase.clear();
	cmbADCSamplingPhase.add("Rising Edge");
	cmbADCSamplingPhase.add("Falling Edge");
	cmbADCSamplingPhase.itemIndex = 0;

	// Clock Non-Overlap Adjust
	cmbClockNonOverlapAdjust.clear();
	cmbClockNonOverlapAdjust.add("Nominal");
	cmbClockNonOverlapAdjust.add("+450ps");
	cmbClockNonOverlapAdjust.add("+150ps");
	cmbClockNonOverlapAdjust.add("+300ps");
	cmbClockNonOverlapAdjust.itemIndex = 0;

	// ============== ADC CONTROL REGISTERS 4 ==========
	// ADC bias resistor adjust
	rgrADCBiasResistorAdjust.itemIndex = 0;

	// Main bias DOWN
	cmbMainBiasDN.clear();
	cmbMainBiasDN.add("0 (Nom)");
	cmbMainBiasDN.add("1");
	cmbMainBiasDN.add("2");
	cmbMainBiasDN.add("3 (Min)");
	cmbMainBiasDN.itemIndex = 0;

	// ADC Amp1 stage1 bias UP
	rgrADCAmp1Stage1BasUp.itemIndex = 0;

	// ADC Amp2-4 stage1 bias UP
	rgrADCAmp24Stage1BasUp.itemIndex = 0;

	// ============== ADC CONTROL REGISTERS 5 ==========
	// ADC Amp1 stage2 bias UP
	rgrADCAmp1Stage2BasUp.itemIndex = 0;

	// ADC Amp2-4 stage2 bias UP
	rgrADCAmp24Stage2BasUp.itemIndex = 0;

	// Quantizer  bias UP
	rgrQuantizerBiasUp.itemIndex = 0;

	// Input Buffer bias UP
	rgrInputBufferBiasUp.itemIndex = 0;

	// ============== DAC CONTROL REGISTERS 1 ==========
	// DAC Internal Output Load Resistor Control Bits
	cmbDACInternalOutputLoadResistor.clear();
	cmbDACInternalOutputLoadResistor.add("Open Circuit");
	cmbDACInternalOutputLoadResistor.add("100 Ohms");
	cmbDACInternalOutputLoadResistor.add("200 Ohms");
	cmbDACInternalOutputLoadResistor.add(" 66 Ohms");
	cmbDACInternalOutputLoadResistor.add("200 Ohms");
	cmbDACInternalOutputLoadResistor.add(" 66 Ohms");
	cmbDACInternalOutputLoadResistor.add("100 Ohms");
	cmbDACInternalOutputLoadResistor.add(" 50 Ohms");
	cmbDACInternalOutputLoadResistor.itemIndex = 2;

	// DAC Reference Current Resistor
	rgrDACReferenceCurrentResistor.itemIndex = 1;

	// DAC Full Scale Output Current Control (single-ended)
	cmbDACFullScaleOutputCurrent.clear();
	cmbDACFullScaleOutputCurrent.add("  5 mA");
	cmbDACFullScaleOutputCurrent.add(" 10 mA");
	cmbDACFullScaleOutputCurrent.add("2.5 mA");
	cmbDACFullScaleOutputCurrent.add("  5 mA");
	cmbDACFullScaleOutputCurrent.itemIndex = 0;

	//SetGuiDecode();

	m_bAllowSend = true;
};

// ---------------------------------------------------------------------------
void ADDC_Module::setRX_FSYNC_P(int index)
{
	rgrRX_FSYNC_P.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x50);
}

int ADDC_Module::getRX_FSYNC_P()
{
	return rgrRX_FSYNC_P.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRX_INTER(int index)
{
	rgrRX_INTER.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x51);
}

int ADDC_Module::getRX_INTER()
{
	return rgrRX_INTER.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setDAC_CLK_P(int index)
{
	rgrDAC_CLK_P.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x52);
}

int ADDC_Module::getDAC_CLK_P()
{
	return rgrDAC_CLK_P.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setTX_FSYNC_P(int index)
{
	rgrTX_FSYNC_P.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x53);
}

int ADDC_Module::getTX_FSYNC_P()
{
	return rgrTX_FSYNC_P.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setTX_INTER(int index)
{
	rgrTX_INTER.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x54);
}

int ADDC_Module::getTX_INTER()
{
	return rgrTX_INTER.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setEN_DAC(bool state)
{
	chkEN_DAC.checked = state;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x55);
}

bool ADDC_Module::getEN_DAC()
{
	return chkEN_DAC.checked;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setEN_ADC_DAC(bool state)
{
	chbEN_ADC_DAC.checked = state;
}

bool ADDC_Module::getEN_ADC_DAC()
{
	return chbEN_ADC_DAC.checked;
}

// ---------------------------------------------------------------------------
void ADDC_Module::setEN_ADC_I(bool state)
{
	chkEN_ADC_I.checked = state;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x56);
}

bool ADDC_Module::getEN_ADC_I()
{
	return chkEN_ADC_I.checked;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setEN_ADC_Q(bool state)
{
	chkEN_ADC_Q.checked = state;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x57);
}

bool ADDC_Module::getEN_ADC_Q()
{
	return chkEN_ADC_Q.checked;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setEN_ADC_REF(bool state)
{
	chkEN_ADC_REF.checked = state;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x74);
}

bool ADDC_Module::getEN_ADC_REF()
{
	return chkEN_ADC_REF.checked;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setDecode(int index)
{
	rgrDecode.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x75);
}

int ADDC_Module::getDecode()
{
	return rgrDecode.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setEN_M_REF(bool state)
{
	chkEN_M_REF.checked = state;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x59);
}

bool ADDC_Module::getEN_M_REF()
{
	return chkEN_M_REF.checked;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setBandgapTemp(int index)
{
	cmbBandgapTemp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x5A);
}

int ADDC_Module::getBandgapTemp()
{
	return cmbBandgapTemp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setBandgapGain(int index)
{
	cmbBandgapGain.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x5B);
}

int ADDC_Module::getBandgapGain()
{
	return cmbBandgapGain.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefAmpsBiasAdj(int index)
{
	cmbRefAmpsBiasAdj.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x5C);
}

int ADDC_Module::getRefAmpsBiasAdj()
{
	return cmbRefAmpsBiasAdj.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefAmpsBiasUp(int index)
{
	cmbRefAmpsBiasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x5D);
}

int ADDC_Module::getRefAmpsBiasUp()
{
	return cmbRefAmpsBiasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefAmpsBiasDn(int index)
{
	cmbRefAmpsBiasDn.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x5E);
}

int ADDC_Module::getRefAmpsBiasDn()
{
	return cmbRefAmpsBiasDn.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefResistorBiasAdj(int index)
{
	cmbRefResistorBiasAdj.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x5F);
}

int ADDC_Module::getRefResistorBiasAdj()
{
	return cmbRefResistorBiasAdj.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefBiasUp(int index)
{
	cmbRefBiasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0X60);
}

int ADDC_Module::getRefBiasUp()
{
	return cmbRefBiasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefBiasDn(int index)
{
	cmbRefBiasDn.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0X61);
}

int ADDC_Module::getRefBiasDn()
{
	return cmbRefBiasDn.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefGainAdj(int index)
{
	cmbRefGainAdj.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0X62);
}

int ADDC_Module::getRefGainAdj()
{
	return cmbRefGainAdj.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setCoomonModeAdj(int index)
{
	cmbCoomonModeAdj.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0X63);
}

int ADDC_Module::getCoomonModeAdj()
{
	return cmbCoomonModeAdj.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setRefBufferBoost(int index)
{
	cmbRefBufferBoost.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0X64);
}

int ADDC_Module::getRefBufferBoost()
{
	return cmbRefBufferBoost.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setInputBufferDisable(bool state)
{
	chkInputBufferDisable.checked = state;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0X65);
}

bool ADDC_Module::getInputBufferDisable()
{
	return chkInputBufferDisable.checked;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setADCSamplingPhase(int index)
{
	cmbADCSamplingPhase.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x66);
}

int ADDC_Module::getADCSamplingPhase()
{
	return cmbADCSamplingPhase.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setClockNonOverlapAdjust(int index)
{
	cmbClockNonOverlapAdjust.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x67);
}

int ADDC_Module::getClockNonOverlapAdjust()
{
	return cmbClockNonOverlapAdjust.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setADCBiasResistorAdjust(int index)
{
	rgrADCBiasResistorAdjust.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x68);
}

int ADDC_Module::getADCBiasResistorAdjust()
{
	return rgrADCBiasResistorAdjust.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setMainBiasDN(int index)
{
	cmbMainBiasDN.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x69);
}

int ADDC_Module::getMainBiasDN()
{
	return cmbMainBiasDN.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setADCAmp1Stage1BiasUp(int index)
{
	rgrADCAmp1Stage1BasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x6A);
}

int ADDC_Module::getADCAmp1Stage1BiasUp()
{
	return rgrADCAmp1Stage1BasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setADCAmp24Stage1BiasUp(int index)
{
	rgrADCAmp24Stage1BasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x6B);
}

int ADDC_Module::getADCAmp24Stage1BiasUp()
{
	return rgrADCAmp24Stage1BasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setADCAmp1Stage2BiasUp(int index)
{
	rgrADCAmp1Stage2BasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x6C);
}

int ADDC_Module::getADCAmp1Stage2BiasUp()
{
	return rgrADCAmp1Stage2BasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setADCAmp24Stage2BiasUp(int index)
{
	rgrADCAmp24Stage2BasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x6D);
}

int ADDC_Module::getADCAmp24Stage2BiasUp()
{
	return rgrADCAmp24Stage2BasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setQuantizerBiasUp(int index)
{
	rgrQuantizerBiasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x6E);
}

int ADDC_Module::getQuantizerBiasUp()
{
	return rgrQuantizerBiasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setInputBufferBiasUp(int index)
{
	rgrInputBufferBiasUp.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x6F);
}

int ADDC_Module::getInputBufferBiasUp()
{
	return rgrInputBufferBiasUp.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setDACInternalOutputLoadResistor(int index)
{
	cmbDACInternalOutputLoadResistor.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x70);
}

int ADDC_Module::getDACInternalOutputLoadResistor()
{
	return cmbDACInternalOutputLoadResistor.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setDACReferenceCurrentResistor(int index)
{
	rgrDACReferenceCurrentResistor.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x71);
}

int ADDC_Module::getDACReferenceCurrentResistor()
{
	return rgrDACReferenceCurrentResistor.itemIndex;
}
// ---------------------------------------------------------------------------

void ADDC_Module::setDACFullScaleOutputCurrent(int index)
{
	cmbDACFullScaleOutputCurrent.itemIndex = index;
	if (m_bAllowSend)
		m_MainModule->CMADDC2LPF(0x72);
}

int ADDC_Module::getDACFullScaleOutputCurrent()
{
	return cmbDACFullScaleOutputCurrent.itemIndex;
}
// ---------------------------------------------------------------------------
bool ADDC_Module::ChipVsGui(sPrData &m_psD, ofstream &out, string Caption, bool bWrAll)
{
	bool bRez = true;
	bool btmp;
	char str[64] = "";
	int itmp, itmpC;

	out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	out.width(32);
	out << "| Register";
	out.width(2);
	out << "|";
	out.width(50);
	out << "Value from PC";
	out.width(2);
	out << "|";
	out.width(50);
	out << "Value from Chip";
	out.width(1);
	out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------"
		<< endl;

	// EN_ADC_DAC
	if ((chbEN_ADC_DAC.checked != (bool)EN_ADC_DAC_r07_b77()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| EN";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbEN_ADC_DAC.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (EN_ADC_DAC_r07_b77())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// DECODE_ADC_DAC
	if ((rgrDecode.itemIndex != DECODE_ADC_DAC_r07_b66()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DECODE";
		out.width(2);
		out << "|";
		out.width(40);
		if (rgrDecode.itemIndex == 1)
			strcpy(str, "Test Mode");
		else
			strcpy(str, "User Mode");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (DECODE_ADC_DAC_r07_b66())
			strcpy(str, "Test Mode");
		else
			strcpy(str, "User Mode");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// TX_CTRL1[6:4]
	itmpC = TX_CTRL1_64_r07_b53();
	if ((cmbDACInternalOutputLoadResistor.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DAC Internal Out Load Resistor";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbDACInternalOutputLoadResistor.itemIndex;
		strcpy(str, cmbDACInternalOutputLoadResistor.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbDACInternalOutputLoadResistor.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// TX_CTRL1[3]
	itmpC = TX_CTRL1_33_r07_b22();
	if ((rgrDACReferenceCurrentResistor.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DAC Ref Current Resistor";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrDACReferenceCurrentResistor.itemIndex;
		strcpy(str, rgrDACReferenceCurrentResistor.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrDACReferenceCurrentResistor.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// TX_CTRL1[1:0]
	itmpC = TX_CTRL1_10_r07_b10();
	if ((cmbDACFullScaleOutputCurrent.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DAC Full Scale Output Control";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbDACFullScaleOutputCurrent.itemIndex;
		strcpy(str, cmbDACFullScaleOutputCurrent.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbDACFullScaleOutputCurrent.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL1[7:6]
	itmpC = RX_CTRL1_76_r08_b76();
	if ((cmbRefResistorBiasAdj.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Bias Resistor Adjust";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefResistorBiasAdj.itemIndex;
		strcpy(str, cmbRefResistorBiasAdj.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefResistorBiasAdj.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL1[5:4]
	itmpC = RX_CTRL1_54_r08_b54();
	if ((cmbRefBiasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Bias UP";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefBiasUp.itemIndex;
		strcpy(str, cmbRefBiasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefBiasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL1[3:0]
	itmpC = RX_CTRL1_30_r08_b30();
	if ((cmbRefBiasDn.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Bias Down";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefBiasDn.itemIndex;
		strcpy(str, cmbRefBiasDn.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefBiasDn.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL2[7:6]
	itmpC = RX_CTRL2_76_r09_b65();
	if ((cmbRefGainAdj.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Gain Adjust";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefGainAdj.itemIndex;
		strcpy(str, cmbRefGainAdj.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefGainAdj.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL2[5:4]
	itmpC = RX_CTRL2_54_r09_b43();
	if ((cmbCoomonModeAdj.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Common Mode Adjust";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbCoomonModeAdj.itemIndex;
		strcpy(str, cmbCoomonModeAdj.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbCoomonModeAdj.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL2[3:2]
	itmpC = RX_CTRL2_32_r09_b21();
	if ((cmbRefBufferBoost.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Buffer Boost";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefBufferBoost.itemIndex;
		strcpy(str, cmbRefBufferBoost.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefBufferBoost.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL2[0]
	if ((chkInputBufferDisable.checked != (bool)RX_CTRL2_00_r09_b00())
		|| bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Input Buffer Disable";
		out.width(2);
		out << "|";
		out.width(40);
		if (chkInputBufferDisable.checked)
			strcpy(str, "Disabled");
		else
			strcpy(str, "Enabled");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (RX_CTRL2_00_r09_b00())
			strcpy(str, "Disabled");
		else
			strcpy(str, "Enabled");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// MISC_CTRL[9]
	itmpC = MISC_CTRL_99_r0A_b77();
	if ((rgrRX_FSYNC_P.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Rx Fsync Polarity, frame start";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrRX_FSYNC_P.itemIndex;
		strcpy(str, rgrRX_FSYNC_P.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrRX_FSYNC_P.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// MISC_CTRL[8]
	itmpC = MISC_CTRL_88_r0A_b66();
	if ((rgrRX_INTER.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Rx Interleave Mode";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrRX_INTER.itemIndex;
		strcpy(str, rgrRX_INTER.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrRX_INTER.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// MISC_CTRL[7]
	itmpC = MISC_CTRL_77_r0A_b55();
	if ((rgrDAC_CLK_P.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DAC Clk Edge Polarity ";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrDAC_CLK_P.itemIndex;
		strcpy(str, rgrDAC_CLK_P.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrDAC_CLK_P.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// MISC_CTRL[6]
	itmpC = MISC_CTRL_66_r0A_b44();
	if ((rgrTX_FSYNC_P.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Tx Fsync Polarity, frame start";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrTX_FSYNC_P.itemIndex;
		strcpy(str, rgrTX_FSYNC_P.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrTX_FSYNC_P.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// MISC_CTRL[5]
	itmpC = MISC_CTRL_55_r0A_b33();
	if ((rgrTX_INTER.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Tx Interleave Mode";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrTX_INTER.itemIndex;
		strcpy(str, rgrTX_INTER.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrTX_INTER.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL3[7]
	itmpC = RX_CTRL3_77_r0A_b22();
	if ((cmbADCSamplingPhase.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ADC Sampling Phase";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbADCSamplingPhase.itemIndex;
		strcpy(str, cmbADCSamplingPhase.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbADCSamplingPhase.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL3[1:0]
	itmpC = RX_CTRL3_10_r0A_b10();
	if ((cmbClockNonOverlapAdjust.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Clock Non-Overlap Adjust";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbClockNonOverlapAdjust.itemIndex;
		strcpy(str, cmbClockNonOverlapAdjust.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbClockNonOverlapAdjust.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL4[7:6]
	itmpC = RX_CTRL4_76_r0B_b76();
	if ((rgrADCBiasResistorAdjust.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ADC Bias Resistor Adjust";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrADCBiasResistorAdjust.itemIndex;
		strcpy(str, rgrADCBiasResistorAdjust.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrADCBiasResistorAdjust.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL4[5:4]
	itmpC = RX_CTRL4_54_r0B_b54();
	if ((cmbMainBiasDN.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Main Bias Down";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbMainBiasDN.itemIndex;
		strcpy(str, cmbMainBiasDN.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbMainBiasDN.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL4[3:2]
	itmpC = RX_CTRL4_32_r0B_b32();
	if ((rgrADCAmp1Stage1BasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ADC Amp1 Stage1 Bias Up";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrADCAmp1Stage1BasUp.itemIndex;
		strcpy(str, rgrADCAmp1Stage1BasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrADCAmp1Stage1BasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL4[1:0]
	itmpC = RX_CTRL4_10_r0B_b10();
	if ((rgrADCAmp24Stage1BasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ADC Amp2-4 Stage1 Bias Up";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrADCAmp24Stage1BasUp.itemIndex;
		strcpy(str, rgrADCAmp24Stage1BasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrADCAmp24Stage1BasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL5[7:6]
	itmpC = RX_CTRL5_76_r0C_b76();
	if ((rgrADCAmp1Stage2BasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ADC Amp1 Stage2 Bias Up";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrADCAmp1Stage2BasUp.itemIndex;
		strcpy(str, rgrADCAmp1Stage2BasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrADCAmp1Stage2BasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL5[5:4]
	itmpC = RX_CTRL5_54_r0C_b54();
	if ((rgrADCAmp24Stage2BasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ADC Amp2-4 Stage2 Bias Up";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrADCAmp24Stage2BasUp.itemIndex;
		strcpy(str, rgrADCAmp24Stage2BasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrADCAmp24Stage2BasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL5[3:2]
	itmpC = RX_CTRL5_32_r0C_b32();
	if ((rgrQuantizerBiasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Quantizer Bias Up";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrQuantizerBiasUp.itemIndex;
		strcpy(str, rgrQuantizerBiasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrQuantizerBiasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// RX_CTRL5[1:0]
	itmpC = RX_CTRL5_10_r0C_b10();
	if ((rgrInputBufferBiasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Input Buffer Bias Up";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrInputBufferBiasUp.itemIndex;
		strcpy(str, rgrInputBufferBiasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrInputBufferBiasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// REF_CTRL0[7:4]
	itmpC = REF_CTRL0_74_r0D_b74();
	if (itmpC & 0x08)
		itmpC = itmpC & 0x07;
	else
		itmpC = itmpC + 8;
	if ((cmbBandgapTemp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Bandgap Temperature Coeff";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbBandgapTemp.itemIndex;
		strcpy(str, cmbBandgapTemp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbBandgapTemp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// REF_CTRL0[3:0]
	itmpC = REF_CTRL0_30_r0D_b30();
	if (itmpC & 0x08)
		itmpC = itmpC & 0x07;
	else
		itmpC = itmpC + 8;
	if ((cmbBandgapGain.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Bandgap Gain Control";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbBandgapGain.itemIndex;
		strcpy(str, cmbBandgapGain.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbBandgapGain.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// REF_CTRL1[7:6]
	itmpC = REF_CTRL1_76_r0E_b76();
	if ((cmbRefAmpsBiasAdj.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Amps Bias Adjust";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefAmpsBiasAdj.itemIndex;
		strcpy(str, cmbRefAmpsBiasAdj.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefAmpsBiasAdj.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// REF_CTRL1[5:4]
	itmpC = REF_CTRL1_54_r0E_b54();
	if ((cmbRefAmpsBiasUp.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Amps Bias UP";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefAmpsBiasUp.itemIndex;
		strcpy(str, cmbRefAmpsBiasUp.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefAmpsBiasUp.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// REF_CTRL1[3:0]
	itmpC = REF_CTRL1_30_r0E_b30();
	if ((cmbRefAmpsBiasDn.itemIndex != itmpC) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Reference Amps Bias Down";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRefAmpsBiasDn.itemIndex;
		strcpy(str, cmbRefAmpsBiasDn.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, cmbRefAmpsBiasDn.sItems[itmpC].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// MISC_CTRL[4]
	if ((chkEN_DAC.checked != (bool)MISC_CTRL_44_r0F_b44()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Enable DAC";
		out.width(2);
		out << "|";
		out.width(40);
		if (chkEN_DAC.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (MISC_CTRL_44_r0F_b44())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// EN_ADC_I
	if ((chkEN_ADC_I.checked != (bool)MISC_CTRL_33_r0F_b33()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Enable ADC1 (I Channel)";
		out.width(2);
		out << "|";
		out.width(40);
		if (chkEN_ADC_I.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (MISC_CTRL_33_r0F_b33())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// EN_ADC_Q
	if ((chkEN_ADC_Q.checked != (bool)MISC_CTRL_22_r0F_b22()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Enable ADC2 (Q Channel)";
		out.width(2);
		out << "|";
		out.width(40);
		if (chkEN_ADC_Q.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (MISC_CTRL_22_r0F_b22())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// EN_ADC_REF
	if ((chkEN_ADC_REF.checked != (bool)MISC_CTRL_11_r0F_b11()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Enable ADC Reference";
		out.width(2);
		out << "|";
		out.width(40);
		if (chkEN_ADC_REF.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (MISC_CTRL_11_r0F_b11())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// EN_M_REF
	if ((chkEN_M_REF.checked != (bool)MISC_CTRL_00_r0F_b00()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| Enable Master Reference";
		out.width(2);
		out << "|";
		out.width(40);
		if (chkEN_M_REF.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (MISC_CTRL_00_r0F_b00())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Powered Down");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	if (bRez && (!bWrAll))
	{
		out.width(136);
		out << "| CHIP Configuration EQUALS GUI Configuration";
		out.width(2);
		out << "|";
		out << endl;
	};
	out << "-----------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	out << "" << endl;
	out << "" << endl;

	return bRez;
};

/**
	@brief Writes Register - Value format to the file.
	@param m_psD register data
	@param out stream for output
*/
void ADDC_Module::MakeRVFFile(sPrData &m_psD, ofstream &out)
{
	int iRval;
	int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

	// 0x07
	iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
	out << iRval;
	out << endl;

	// 0x08
	iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
	out << iRval;
	out << endl;

	// 0x09
	iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x7F);
	out << iRval;
	out << endl;

	// 0x0A
	iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
	out << iRval;
	out << endl;

	// 0x0B
	iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
	out << iRval;
	out << endl;

	// 0x0C
	iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
	out << iRval;
	out << endl;

	// 0x0D - Read Only
	iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0xFF);
	out << iRval;
	out << endl;

	// 0x0E - Read Only
	iRval = (iAddr | (0x0E << 8)) | (m_psD.cDataR[0x0E] & 0xFF);
	out << iRval;
	out << endl;

	// 0x0F - Read Only
	iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0xFF);
	out << iRval;
	out << endl;
};

/**
	@brief Saves chip configuration using RFIF format
	@param sPrData registers data
	@param out stream for output
	@param FRIF_SPI_A rfif parameter
*/
void ADDC_Module::MakeRFIFFile(sPrData &m_psD, ofstream &out,
	const char *FRIF_SPI_A)
{
	int iRval;
	int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

	// 0x07
	// out << "# Register(s): EN_ADC_DAC, DECODE, TX_CTRL1[6:0]" << endl;
	iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x08
	// out << "# Register(s): RX_CTRL1[7:0]" << endl;
	iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x09
	// out << "# Register(s): RX_CTRL2[7:0]" << endl;
	iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x7F);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0A
	// out << "# Register(s): MISC_CTRL[9:5], RX_CTRL3[7], RX_CTRL3[1:0]" << endl;
	iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0B
	// out << "# Register(s): RX_CTRL4[7:0]" << endl;
	iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0C
	// out << "# Register(s): RX_CTRL5[7:0]" << endl;
	iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0D - Read Only
	// out << "# Register(s): REF_CTRL0[7:0]" << endl;
	iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0E - Read Only
	// out << "# Register(s): REF_CTRL1[7:0]" << endl;
	iRval = (iAddr | (0x0E << 8)) | (m_psD.cDataR[0x0E] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0F - Read Only
	// out << "# Register(s): MISC_CTRL[4:0]" << endl;
	iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	out << FRIF_SPI_A;
	out << endl;
};

/**
	@brief Reads all configuration settings from the chip
	@param m_psD registers data
*/
bool ADDC_Module::SetGUIUnderReadback(sPrData &m_psD)
{
	int itmp;

	m_bAllowSend = false;

	// EN
	itmp = EN_ADC_DAC_r07_b77();
	chbEN_ADC_DAC.checked = itmp;

	// DECODE
	itmp = DECODE_ADC_DAC_r07_b66();
	rgrDecode.itemIndex = itmp;

	// TX_CTRL1[6:4]
	itmp = TX_CTRL1_64_r07_b53();
	cmbDACInternalOutputLoadResistor.itemIndex = itmp;

	// TX_CTRL1[3]
	itmp = TX_CTRL1_33_r07_b22();
	rgrDACReferenceCurrentResistor.itemIndex = itmp;

	// TX_CTRL1[1:0]
	itmp = TX_CTRL1_10_r07_b10();
	cmbDACFullScaleOutputCurrent.itemIndex = itmp;

	// RX_CTRL1[7:6]
	itmp = RX_CTRL1_76_r08_b76();
	cmbRefResistorBiasAdj.itemIndex = itmp;

	// RX_CTRL1[5:4]
	itmp = RX_CTRL1_54_r08_b54();
	cmbRefBiasUp.itemIndex = itmp;

	// RX_CTRL1[3:0]
	itmp = RX_CTRL1_30_r08_b30();
	cmbRefBiasDn.itemIndex = itmp;

	// RX_CTRL2[7:6]
	itmp = RX_CTRL2_76_r09_b65();
	cmbRefGainAdj.itemIndex = itmp;

	// RX_CTRL2[5:4]
	itmp = RX_CTRL2_54_r09_b43();
	cmbCoomonModeAdj.itemIndex = itmp;

	// RX_CTRL2[3:2]
	itmp = RX_CTRL2_32_r09_b21();
	cmbRefBufferBoost.itemIndex = itmp;

	// RX_CTRL2[0]
	itmp = RX_CTRL2_00_r09_b00();
	chkInputBufferDisable.checked = itmp;

	// MISC_CTRL[9]
	itmp = MISC_CTRL_99_r0A_b77();
	rgrRX_FSYNC_P.itemIndex = itmp;

	// MISC_CTRL[8]
	itmp = MISC_CTRL_88_r0A_b66();
	rgrRX_INTER.itemIndex = itmp;

	// MISC_CTRL[7]
	itmp = MISC_CTRL_77_r0A_b55();
	rgrDAC_CLK_P.itemIndex = itmp;

	// MISC_CTRL[6]
	itmp = MISC_CTRL_66_r0A_b44();
	rgrTX_FSYNC_P.itemIndex = itmp;

	// MISC_CTRL[5]
	itmp = MISC_CTRL_55_r0A_b33();
	rgrTX_INTER.itemIndex = itmp;

	// RX_CTRL3[7]
	itmp = RX_CTRL3_77_r0A_b22();
	cmbADCSamplingPhase.itemIndex = itmp;

	// RX_CTRL3[1:0]
	itmp = RX_CTRL3_10_r0A_b10();
	cmbClockNonOverlapAdjust.itemIndex = itmp;

	// RX_CTRL4[7:6]
	itmp = RX_CTRL4_76_r0B_b76();
	rgrADCBiasResistorAdjust.itemIndex = itmp;

	// RX_CTRL4[5:4]
	itmp = RX_CTRL4_54_r0B_b54();
	cmbMainBiasDN.itemIndex = itmp;

	// RX_CTRL4[3:2]
	itmp = RX_CTRL4_32_r0B_b32();
	rgrADCAmp1Stage1BasUp.itemIndex = itmp;

	// RX_CTRL4[1:0]
	itmp = RX_CTRL4_10_r0B_b10();
	rgrADCAmp24Stage1BasUp.itemIndex = itmp;

	// RX_CTRL5[7:6]
	itmp = RX_CTRL5_76_r0C_b76();
	rgrADCAmp1Stage2BasUp.itemIndex = itmp;

	// RX_CTRL5[5:4]
	itmp = RX_CTRL5_54_r0C_b54();
	rgrADCAmp24Stage2BasUp.itemIndex = itmp;

	// RX_CTRL5[3:2]
	itmp = RX_CTRL5_32_r0C_b32();
	rgrQuantizerBiasUp.itemIndex = itmp;

	// RX_CTRL5[1:0]
	itmp = RX_CTRL5_10_r0C_b10();
	rgrInputBufferBiasUp.itemIndex = itmp;

	// REF_CTRL0[7:4]
	itmp = REF_CTRL0_74_r0D_b74();
	if (itmp & 0x08)
		itmp = itmp & 0x07;
	else
		itmp = itmp + 8;
	cmbBandgapTemp.itemIndex = itmp;

	// REF_CTRL0[3:0]
	itmp = REF_CTRL0_30_r0D_b30();
	if (itmp & 0x08)
		itmp = itmp & 0x07;
	else
		itmp = itmp + 8;
	cmbBandgapGain.itemIndex = itmp;

	// REF_CTRL1[7:6]
	itmp = REF_CTRL1_76_r0E_b76();
	cmbRefAmpsBiasAdj.itemIndex = itmp;

	// REF_CTRL1[5:4]
	itmp = REF_CTRL1_54_r0E_b54();
	cmbRefAmpsBiasUp.itemIndex = itmp;

	// REF_CTRL1[3:0]
	itmp = REF_CTRL1_30_r0E_b30();
	cmbRefAmpsBiasDn.itemIndex = itmp;

	// MISC_CTRL[4]
	itmp = MISC_CTRL_44_r0F_b44();
	chkEN_DAC.checked = itmp;

	// EN_ADC_I
	itmp = MISC_CTRL_33_r0F_b33();
	chkEN_ADC_I.checked = itmp;

	// EN_ADC_Q
	itmp = MISC_CTRL_22_r0F_b22();
	chkEN_ADC_Q.checked = itmp;

	// EN_ADC_REF
	itmp = MISC_CTRL_11_r0F_b11();
	chkEN_ADC_REF.checked = itmp;

	// EN_M_REF
	itmp = MISC_CTRL_00_r0F_b00();
	chkEN_M_REF.checked = itmp;

	m_bAllowSend = true;

	return true;
};

/**
	@brief Writes register map to the file. According to the customer wish.
	@param m_psD registers data
	@param out stream for output
*/
void ADDC_Module::MakeRegisterFile(sPrData &m_psD, ofstream &out)
{
	int itmp;

	// EN_ADC_DAC
	out.width(24);
	out << left;
	out << "REG 0x57 MASK 07 : 07  =";
	itmp = EN_ADC_DAC_r07_b77();
	out.width(6);
	out << right;
	out << itmp;
	out << "  EN_ADC_DAC";
	out << endl;

	// DECODE_ADC_DAC
	out.width(24);
	out << left;
	out << "REG 0x57 MASK 06 : 06  =";
	itmp = DECODE_ADC_DAC_r07_b66();
	out.width(6);
	out << right;
	out << itmp;
	out << "  DECODE_ADC_DAC";
	out << endl;

	// TX_CTRL1[6:4]
	out.width(24);
	out << left;
	out << "REG 0x57 MASK 05 : 03  =";
	itmp = TX_CTRL1_64_r07_b53();
	out.width(6);
	out << right;
	out << itmp;
	out << "  TX_CTRL1[6:4]";
	out << endl;

	// TX_CTRL1[3]
	out.width(24);
	out << left;
	out << "REG 0x57 MASK 02 : 02  =";
	itmp = TX_CTRL1_33_r07_b22();
	out.width(6);
	out << right;
	out << itmp;
	out << "  TX_CTRL1[3]";
	out << endl;

	// TX_CTRL1[1:0]
	out.width(24);
	out << left;
	out << "REG 0x57 MASK 01 : 00  =";
	itmp = TX_CTRL1_10_r07_b10();
	out.width(6);
	out << right;
	out << itmp;
	out << "  TX_CTRL1[1:0]";
	out << endl;

	// RX_CTRL1[7:6]
	out.width(24);
	out << left;
	out << "REG 0x58 MASK 07 : 06  =";
	itmp = RX_CTRL1_76_r08_b76();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL1[7:6]";
	out << endl;

	// RX_CTRL1[5:4]
	out.width(24);
	out << left;
	out << "REG 0x58 MASK 05 : 04  =";
	itmp = RX_CTRL1_54_r08_b54();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL1[5:4]";
	out << endl;

	// RX_CTRL1[3:0]
	out.width(24);
	out << left;
	out << "REG 0x58 MASK 03 : 00  =";
	itmp = RX_CTRL1_30_r08_b30();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL1[3:0]";
	out << endl;

	// RX_CTRL2[7:6]
	out.width(24);
	out << left;
	out << "REG 0x59 MASK 06 : 05  =";
	itmp = RX_CTRL2_76_r09_b65();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL2[7:6]";
	out << endl;

	// RX_CTRL2[5:4]
	out.width(24);
	out << left;
	out << "REG 0x59 MASK 04 : 03  =";
	itmp = RX_CTRL2_54_r09_b43();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL2[5:4]";
	out << endl;

	// RX_CTRL2[3:2]
	out.width(24);
	out << left;
	out << "REG 0x59 MASK 02 : 01  =";
	itmp = RX_CTRL2_32_r09_b21();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL2[3:2]";
	out << endl;

	// RX_CTRL2[0]
	out.width(24);
	out << left;
	out << "REG 0x59 MASK 00 : 00  =";
	itmp = RX_CTRL2_00_r09_b00();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL2[0]";
	out << endl;

	// MISC_CTRL[9]
	out.width(24);
	out << left;
	out << "REG 0x5A MASK 07 : 07  =";
	itmp = MISC_CTRL_99_r0A_b77();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[9]";
	out << endl;

	// MISC_CTRL[8]
	out.width(24);
	out << left;
	out << "REG 0x5A MASK 06 : 06  =";
	itmp = MISC_CTRL_88_r0A_b66();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[8]";
	out << endl;

	// MISC_CTRL[7]
	out.width(24);
	out << left;
	out << "REG 0x5A MASK 05 : 05  =";
	itmp = MISC_CTRL_77_r0A_b55();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[7]";
	out << endl;

	// MISC_CTRL[6]
	out.width(24);
	out << left;
	out << "REG 0x5A MASK 04 : 04  =";
	itmp = MISC_CTRL_66_r0A_b44();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[6]";
	out << endl;

	// MISC_CTRL[5]
	out.width(24);
	out << left;
	out << "REG 0x5A MASK 03 : 03  =";
	itmp = MISC_CTRL_55_r0A_b33();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[5]";
	out << endl;

	// RX_CTRL3[7]
	out.width(24);
	out << left;
	out << "REG 0x5A MASK 02 : 02  =";
	itmp = RX_CTRL3_77_r0A_b22();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL3[7]";
	out << endl;

	// RX_CTRL3[1:0]
	out.width(24);
	out << left;
	out << "REG 0x5A MASK 01 : 00  =";
	itmp = RX_CTRL3_10_r0A_b10();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL3[1:0]";
	out << endl;

	// RX_CTRL4[7:6]
	out.width(24);
	out << left;
	out << "REG 0x5B MASK 07 : 06  =";
	itmp = RX_CTRL4_76_r0B_b76();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL4[7:6]";
	out << endl;

	// RX_CTRL4[5:4]
	out.width(24);
	out << left;
	out << "REG 0x5B MASK 05 : 04  =";
	itmp = RX_CTRL4_54_r0B_b54();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL4[5:4]";
	out << endl;

	// RX_CTRL4[3:2]
	out.width(24);
	out << left;
	out << "REG 0x5B MASK 03 : 02  =";
	itmp = RX_CTRL4_32_r0B_b32();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL4[3:2]";
	out << endl;

	// RX_CTRL4[1:0]
	out.width(24);
	out << left;
	out << "REG 0x5B MASK 01 : 00  =";
	itmp = RX_CTRL4_10_r0B_b10();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL4[1:0]";
	out << endl;

	// RX_CTRL5[7:6]
	out.width(24);
	out << left;
	out << "REG 0x5C MASK 07 : 06  =";
	itmp = RX_CTRL5_76_r0C_b76();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL5[7:6]";
	out << endl;

	// RX_CTRL5[5:4]
	out.width(24);
	out << left;
	out << "REG 0x5C MASK 05 : 04  =";
	itmp = RX_CTRL5_54_r0C_b54();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL5[5:4]";
	out << endl;

	// RX_CTRL5[3:2]
	out.width(24);
	out << left;
	out << "REG 0x5C MASK 03 : 02  =";
	itmp = RX_CTRL5_32_r0C_b32();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL5[3:2]";
	out << endl;

	// RX_CTRL5[1:0]
	out.width(24);
	out << left;
	out << "REG 0x5C MASK 01 : 00  =";
	itmp = RX_CTRL5_10_r0C_b10();
	out.width(6);
	out << right;
	out << itmp;
	out << "  RX_CTRL5[1:0]";
	out << endl;

	// REF_CTRL0[7:4]
	out.width(24);
	out << left;
	out << "REG 0x5D MASK 07 : 04  =";
	itmp = REF_CTRL0_74_r0D_b74();
	out.width(6);
	out << right;
	out << itmp;
	out << "  REF_CTRL0[7:4]";
	out << endl;

	// REF_CTRL0[3:0]
	out.width(24);
	out << left;
	out << "REG 0x5D MASK 03 : 00  =";
	itmp = REF_CTRL0_30_r0D_b30();
	out.width(6);
	out << right;
	out << itmp;
	out << "  REF_CTRL0[3:0]";
	out << endl;

	// REF_CTRL1[7:6]
	out.width(24);
	out << left;
	out << "REG 0x5E MASK 07 : 06  =";
	itmp = REF_CTRL1_76_r0E_b76();
	out.width(6);
	out << right;
	out << itmp;
	out << "  REF_CTRL1[7:6]";
	out << endl;

	// REF_CTRL1[5:4]
	out.width(24);
	out << left;
	out << "REG 0x5E MASK 05 : 04  =";
	itmp = REF_CTRL1_54_r0E_b54();
	out.width(6);
	out << right;
	out << itmp;
	out << "  REF_CTRL1[5:4]";
	out << endl;

	// REF_CTRL1[3:0]
	out.width(24);
	out << left;
	out << "REG 0x5E MASK 03 : 00  =";
	itmp = REF_CTRL1_30_r0E_b30();
	out.width(6);
	out << right;
	out << itmp;
	out << "  REF_CTRL1[3:0]";
	out << endl;

	// MISC_CTRL[4]
	out.width(24);
	out << left;
	out << "REG 0x5F MASK 04 : 04  =";
	itmp = MISC_CTRL_44_r0F_b44();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[4]";
	out << endl;

	// MISC_CTRL[3]
	out.width(24);
	out << left;
	out << "REG 0x5F MASK 03 : 03  =";
	itmp = MISC_CTRL_33_r0F_b33();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[3]";
	out << endl;

	// MISC_CTRL[2]
	out.width(24);
	out << left;
	out << "REG 0x5F MASK 02 : 02  =";
	itmp = MISC_CTRL_22_r0F_b22();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[2]";
	out << endl;

	// MISC_CTRL[1]
	out.width(24);
	out << left;
	out << "REG 0x5F MASK 01 : 01  =";
	itmp = MISC_CTRL_11_r0F_b11();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[1]";
	out << endl;

	// MISC_CTRL[0]
	out.width(24);
	out << left;
	out << "REG 0x5F MASK 00 : 00  =";
	itmp = MISC_CTRL_00_r0F_b00();
	out.width(6);
	out << right;
	out << itmp;
	out << "  MISC_CTRL[0]";
	out << endl;
};

/**
	@brief Saves configuration settings to ini file.
	@param pini Pointer to ini file parser.
*/
void ADDC_Module::SaveConf(ini_t *pini)
{
	char Sect[80];
	sprintf(Sect,"%i", (int)m_cMAddr + 10);
	pini->Create(Sect);

	pini->Set("chbEN_ADC_DAC", chbEN_ADC_DAC.checked);
	pini->Set("rgrDecode", rgrDecode.itemIndex);

	pini->Set("cmbDACInternalOutputLoadResistor", cmbDACInternalOutputLoadResistor.itemIndex);
	pini->Set("rgrDACReferenceCurrentResistor", rgrDACReferenceCurrentResistor.itemIndex);
	pini->Set("cmbDACFullScaleOutputCurrent", cmbDACFullScaleOutputCurrent.itemIndex);

	pini->Set("cmbRefResistorBiasAdj", cmbRefResistorBiasAdj.itemIndex);
	pini->Set("cmbRefBiasUp", cmbRefBiasUp.itemIndex);
	pini->Set("cmbRefBiasDn", cmbRefBiasDn.itemIndex);

	pini->Set("cmbRefGainAdj", cmbRefGainAdj.itemIndex);
	pini->Set("cmbCoomonModeAdj", cmbCoomonModeAdj.itemIndex);
	pini->Set("cmbRefBufferBoost", cmbRefBufferBoost.itemIndex);
	pini->Set("chkInputBufferDisable", chkInputBufferDisable.checked);

	pini->Set("rgrRX_FSYNC_P", rgrRX_FSYNC_P.itemIndex);
	pini->Set("rgrRX_INTER", rgrRX_INTER.itemIndex);
	pini->Set("rgrDAC_CLK_P", rgrDAC_CLK_P.itemIndex);
	pini->Set("rgrTX_FSYNC_P", rgrTX_FSYNC_P.itemIndex);
	pini->Set("rgrTX_INTER", rgrTX_INTER.itemIndex);
	pini->Set("cmbADCSamplingPhase", cmbADCSamplingPhase.itemIndex);
	pini->Set("cmbClockNonOverlapAdjust", cmbClockNonOverlapAdjust.itemIndex);

	pini->Set("rgrADCBiasResistorAdjust", rgrADCBiasResistorAdjust.itemIndex);
	pini->Set("cmbMainBiasDN", cmbMainBiasDN.itemIndex);
	pini->Set("rgrADCAmp1Stage1BasUp", rgrADCAmp1Stage1BasUp.itemIndex);
	pini->Set("rgrADCAmp24Stage1BasUp", rgrADCAmp24Stage1BasUp.itemIndex);

	pini->Set("rgrADCAmp1Stage2BasUp", rgrADCAmp1Stage2BasUp.itemIndex);
	pini->Set("rgrADCAmp24Stage2BasUp", rgrADCAmp24Stage2BasUp.itemIndex);
	pini->Set("rgrQuantizerBiasUp", rgrQuantizerBiasUp.itemIndex);
	pini->Set("rgrInputBufferBiasUp", rgrInputBufferBiasUp.itemIndex);

	pini->Set("cmbBandgapTemp", cmbBandgapTemp.itemIndex);
	pini->Set("cmbBandgapGain", cmbBandgapGain.itemIndex);

	pini->Set("cmbRefAmpsBiasAdj", cmbRefAmpsBiasAdj.itemIndex);
	pini->Set("cmbRefAmpsBiasUp", cmbRefAmpsBiasUp.itemIndex);
	pini->Set("cmbRefAmpsBiasDn", cmbRefAmpsBiasDn.itemIndex);

	pini->Set("chkEN_DAC", chkEN_DAC.checked);
	pini->Set("chkEN_ADC_I", chkEN_ADC_I.checked);
	pini->Set("chkEN_ADC_Q", chkEN_ADC_Q.checked);
	pini->Set("chkEN_ADC_REF", chkEN_ADC_REF.checked);
	pini->Set("chkEN_M_REF", chkEN_M_REF.checked);

};

/**
	@brief Reads configuration settings from ini file.
	@param pini Pointer to ini file parser.
*/
void ADDC_Module::ReadConf(ini_t *pini)
{
	char Sect[80];
	sprintf(Sect,"%i", (int)m_cMAddr + 10);
	pini->Select(Sect);

	m_bAllowSend = false;

	chbEN_ADC_DAC.checked = pini->Get("chbEN_ADC_DAC", 1);
	rgrDecode.itemIndex = pini->Get("rgrDecode", 0);
	cmbDACInternalOutputLoadResistor.itemIndex = pini->Get("cmbDACInternalOutputLoadResistor", 2);
	rgrDACReferenceCurrentResistor.itemIndex = pini->Get("rgrDACReferenceCurrentResistor", 1);
	cmbDACFullScaleOutputCurrent.itemIndex = pini->Get("cmbDACFullScaleOutputCurrent", 0);

	cmbRefResistorBiasAdj.itemIndex = pini->Get("cmbRefResistorBiasAdj", 0);
	cmbRefBiasUp.itemIndex = pini->Get("cmbRefBiasUp", 0);
	cmbRefBiasDn.itemIndex = pini->Get("cmbRefBiasDn", 0);

	cmbRefGainAdj.itemIndex = pini->Get("cmbRefGainAdj", 0);
	cmbCoomonModeAdj.itemIndex = pini->Get("cmbCoomonModeAdj", 0);
	cmbRefBufferBoost.itemIndex = pini->Get("cmbRefBufferBoost", 0);
	chkInputBufferDisable.checked = pini->Get("chkInputBufferDisable", 1);

	rgrRX_FSYNC_P.itemIndex = pini->Get("rgrRX_FSYNC_P", 0);
	rgrRX_INTER.itemIndex = pini->Get("rgrRX_INTER", 0);
	rgrDAC_CLK_P.itemIndex = pini->Get("rgrDAC_CLK_P", 1);
	rgrTX_FSYNC_P.itemIndex = pini->Get("rgrTX_FSYNC_P", 0);
	rgrTX_INTER.itemIndex = pini->Get("rgrTX_INTER", 0);
	cmbADCSamplingPhase.itemIndex = pini->Get("cmbADCSamplingPhase", 0);
	cmbClockNonOverlapAdjust.itemIndex = pini->Get("cmbClockNonOverlapAdjust", 0);

	rgrADCBiasResistorAdjust.itemIndex = pini->Get("rgrADCBiasResistorAdjust", 0);
	cmbMainBiasDN.itemIndex = pini->Get("cmbMainBiasDN", 0);
	rgrADCAmp1Stage1BasUp.itemIndex = pini->Get("rgrADCAmp1Stage1BasUp", 0);
	rgrADCAmp24Stage1BasUp.itemIndex = pini->Get("rgrADCAmp24Stage1BasUp", 0);

	rgrADCAmp1Stage2BasUp.itemIndex = pini->Get("rgrADCAmp1Stage2BasUp", 0);
	rgrADCAmp24Stage2BasUp.itemIndex = pini->Get("rgrADCAmp24Stage2BasUp", 0);
	rgrQuantizerBiasUp.itemIndex = pini->Get("rgrQuantizerBiasUp", 0);
	rgrInputBufferBiasUp.itemIndex = pini->Get("rgrInputBufferBiasUp", 0);

	cmbBandgapTemp.itemIndex = pini->Get("cmbBandgapTemp", 8);
	cmbBandgapGain.itemIndex = pini->Get("cmbBandgapGain", 8);

	cmbRefAmpsBiasAdj.itemIndex = pini->Get("cmbRefAmpsBiasAdj", 0);
	cmbRefAmpsBiasUp.itemIndex = pini->Get("cmbRefAmpsBiasUp", 0);
	cmbRefAmpsBiasDn.itemIndex = pini->Get("cmbRefAmpsBiasDn", 0);

	chkEN_DAC.checked = pini->Get("chkEN_DAC", 1);
	chkEN_ADC_I.checked = pini->Get("chkEN_ADC_I", 1);
	chkEN_ADC_Q.checked = pini->Get("chkEN_ADC_Q", 1);
	chkEN_ADC_REF.checked = pini->Get("chkEN_ADC_REF", 1);
	chkEN_M_REF.checked = pini->Get("chkEN_M_REF", 1);

	m_bAllowSend = true;
};

void ADDC_Module::CustSet_cmbCoomonModeAdj(int Ind)
{
	setCoomonModeAdj(Ind);
};
