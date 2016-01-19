// -----------------------------------------------------------------------------
// FILE: 		TxLPF_Module.cpp
// DESCRIPTION:	TxLPF control user interface
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ---------------------------------------------------------------------------
#include "TxLpf_Module.h"
#include "ConnectionManager.h"
#include "Main_Module.h"
#include "ADDC_Module.h"
// ---------------------------------------------------------------------------
// 0x0
#define             DC_REGVAL_r00_b50() ((m_psD.cDataR[0x00] & 0x3F) >> 0)
// 0x1
#define               DC_LOCK_r01_b42() ((m_psD.cDataR[0x01] & 0x1C) >> 2)
#define          DC_CLBR_DONE_r01_b11() ((m_psD.cDataR[0x01] & 0x02) >> 1)
#define                 DC_UD_r01_b00() ((m_psD.cDataR[0x01] & 0x01) >> 0)
// 0x2
#define             DC_CNTVAL_r02_b50() ((m_psD.cDataR[0x02] & 0x3F) >> 0)
// 0x3
#define         DC_START_CLBR_r03_b55() ((m_psD.cDataR[0x03] & 0x20) >> 5)
#define               DC_LOAD_r03_b44() ((m_psD.cDataR[0x03] & 0x10) >> 4)
#define             DC_SRESET_r03_b33() ((m_psD.cDataR[0x03] & 0x08) >> 3)
#define               DC_ADDR_r03_b20() ((m_psD.cDataR[0x03] & 0x07) >> 0)
// 0x4
#define               BWC_LPF_r04_b52() ((m_psD.cDataR[0x04] & 0x3C) >> 2)
#define                    EN_r04_b11() ((m_psD.cDataR[0x04] & 0x02) >> 1)
#define                DECODE_r04_b00() ((m_psD.cDataR[0x04] & 0x01) >> 0)
// 0x5
#define            BYP_EN_LPF_r05_b66() ((m_psD.cDataR[0x05] & 0x40) >> 6)
#define            DCO_DACCAL_r05_b50() ((m_psD.cDataR[0x05] & 0x3F) >> 0)
// 0x6
#define          TX_DACBUF_PD_r06_b77() ((m_psD.cDataR[0x06] & 0x80) >> 7)
#define          RCCAL_LPF_PD_r06_b64() ((m_psD.cDataR[0x06] & 0x70) >> 4)
// #define         PD_DCOCMP_LPF_r06_b33() ((m_psD.cDataR[0x06] & 0x08) >> 3)
#define         PD_DCOCMP_LPF_r06_b33_v0() ((m_psD.cDataR[0x06] & 0x08) >> 3) //When Ver=2, Rev=2, Mask=0
#define         PD_DCOCMP_LPF_r0F_b77_v1() ((m_psD.cDataR[0x0F] & 0x80) >> 7) //When Ver=2, Rev=2, Mask=1
#define         PD_DCODAC_LPF_r06_b22() ((m_psD.cDataR[0x06] & 0x04) >> 2)
#define         PD_DCOREF_LPF_r06_b11() ((m_psD.cDataR[0x06] & 0x02) >> 1)
#define            PD_FIL_LPF_r06_b00() ((m_psD.cDataR[0x06] & 0x01) >> 0)

#define FRIF_DIR_W "rfIf Direct=16,"
// #define FRIF_SPI_A_TX ",20"
// #define FRIF_SPI_A_RX ",20"

// ---------------------------------------------------------------------------
TxLPF_Module::TxLPF_Module()
{
	lbDC_REGVAL = -1;
	lblDC_LOCK = -1;
	lblDC_CLBR_DONE = -1;
	lblDC_UD = -1;
	m_ADDCmodule = NULL;
	m_cVer = 2;
	m_cRev = 2;
	m_cMask = 0;
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
TxLPF_Module::~TxLPF_Module(void)
{
	delete[]m_psD.cCmdW;
	delete[]m_psD.cDataW;
	delete[]m_psD.cCmdR;
	delete[]m_psD.cDataR;
	delete[]m_psD.iRInd;
	delete[]m_psD.iWInd;
	delete[]m_psD.cTestMap; // RT//
}

char TxLPF_Module::getAddr()
{
	return m_cMAddr;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::Initialize(Main_Module *pMain, char MAddr, ADDC_Module *ADDC)
{
	pMainModule = pMain;

	m_cMAddr = MAddr;
	m_ADDCmodule = ADDC;

	if (m_cMAddr == TxLpfAddr)
		m_psD.iLen = TxLpfLen;
	else
		m_psD.iLen = RxLpfLen;

	m_psD.cCmdW = new char[m_psD.iLen];
	m_psD.cDataW = new char[m_psD.iLen];
	m_psD.cCmdR = new char[m_psD.iLen];
	m_psD.cDataR = new char[m_psD.iLen];
	m_psD.iRInd = new int[m_psD.iLen];
	m_psD.iWInd = new int[m_psD.iLen];
	m_psD.cTestMap = new char[m_psD.iLen]; // RT//
	memset(m_psD.cCmdW, 0, m_psD.iLen);
	memset(m_psD.cDataW, 0, m_psD.iLen);
	memset(m_psD.cCmdR, 0, m_psD.iLen);
	memset(m_psD.cDataR, 0, m_psD.iLen);
	memset(m_psD.iRInd, 0, m_psD.iLen*sizeof(int));
	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	memset(m_psD.cTestMap, 0, m_psD.iLen); // RT//
	m_psD.iToR = m_psD.iLen;
	m_psD.iToW = 0;
	for (int i = 0; i < m_psD.iLen; i++)
	{
		// Write Command and Addresses
		m_psD.cCmdW[i] = 1;
		m_psD.cCmdW[i] = m_psD.cCmdW[i] << 3;
		m_psD.cCmdW[i] |= m_cMAddr;
		m_psD.cCmdW[i] = m_psD.cCmdW[i] << 4;
		m_psD.cCmdW[i] |= i;
		// Read Command and Addresses
		m_psD.cCmdR[i] = 0;
		m_psD.cCmdR[i] = m_psD.cCmdR[i] << 3;
		m_psD.cCmdR[i] |= m_cMAddr;
		m_psD.cCmdR[i] = m_psD.cCmdR[i] << 4;
		m_psD.cCmdR[i] |= i;

		m_psD.iRInd[i] = i;
	};

	// Register test mask //RT//
	for (int i = 0; i < m_psD.iLen; i++)
	{
		m_psD.cTestMap[i] = 0x00;
	};
	m_psD.cTestMap[0x0] = 0x00;
	m_psD.cTestMap[0x1] = 0x00;
	m_psD.cTestMap[0x2] = 0x3F;
	m_psD.cTestMap[0x3] = 0x3F;
	m_psD.cTestMap[0x4] = 0x3F;
	m_psD.cTestMap[0x5] = 0x7F;
	if (m_cMAddr == TxLpfAddr)
	{
		m_psD.cTestMap[0x6] = 0xFF;
	}
	else
	{
		m_psD.cTestMap[0x6] = 0x7F;
		m_psD.cTestMap[0x7] = 0xFF;
		m_psD.cTestMap[0x8] = 0xFF;
		m_psD.cTestMap[0x9] = 0x7F;
		m_psD.cTestMap[0xA] = 0xFF;
		m_psD.cTestMap[0xB] = 0xFF;
		m_psD.cTestMap[0xC] = 0xFF;
		m_psD.cTestMap[0xD] = 0xFF;
		m_psD.cTestMap[0xE] = 0xFF;
		m_psD.cTestMap[0xF] = 0x1F;
	};

	SetDefaults();
};

// ---------------------------------------------------------------------------
void TxLPF_Module::SetDefaults()
{
	m_bAllowSend = false;

	// BWC_LPF[3:0]
	cmbLpfBw.clear();
	cmbLpfBw.add("14 MHz");
	cmbLpfBw.add("10 MHz");
	cmbLpfBw.add("7 MHz");
	cmbLpfBw.add("6 MHz");
	cmbLpfBw.add("5 MHz");
	cmbLpfBw.add("4.375 MHz");
	cmbLpfBw.add("3.5 MHz");
	cmbLpfBw.add("3 MHz");
	cmbLpfBw.add("2.75 MHz");
	cmbLpfBw.add("2.5 MHz");
	cmbLpfBw.add("1.92 MHz");
	cmbLpfBw.add("1.5 MHz");
	cmbLpfBw.add("1.375 MHz");
	cmbLpfBw.add("1.25 MHz");
	cmbLpfBw.add("0.875 MHz");
	cmbLpfBw.add("0.75 MHz");
	cmbLpfBw.itemIndex = 0;
	// EN
	chbPwrLpfMods.checked = true;
	// DECODE
	rgrDecode.itemIndex = 0;

	// BYP_EN_LPF
	rgrLpfByp.itemIndex = 0;
	// DCO_DACCAL_LPF[5:0]
	cmbDCOffset.clear();
	for (int i = 0; i < 64; i++)
	{
		cmbDCOffset.add(i);
	};
	cmbDCOffset.itemIndex = 0x0C;

	// TX_DACBUF_EN
	if (m_cMAddr == TxLpfAddr)
	{
		chbTX_DACBUF_EN.checked = true;
	}
	// RCCAL_LPF[2:0]
	cmbRcCal.clear();
	for (int i = 0; i < 8; i++)
	{
		cmbRcCal.add(i);
	};
	cmbRcCal.itemIndex = 3;
	// PD_DCOCMP_LPF
	chbPwrDCCmpr.checked = true;
	// PD_DCODAC_LPF
	chbPwrDCDac.checked = true;
	// PD_DCOREF_LPF
	chbPwrDCRef.checked = true;
	// PD_FIL_LPF
	chbPwrLpf.checked = true;

	// DC_ADDR[3:0]
	cmbDCCalAddr.clear();
	for (int i = 0; i < 5; i++)
	{
		cmbDCCalAddr.add(i);
	};
	cmbDCCalAddr.itemIndex = 0;

	// DC_CNTVAL[5:0]
	cmbCalVal.clear();
	for (int i = 0; i < 64; i++)
	{
		cmbCalVal.add(i);
	};
	cmbCalVal.itemIndex = 31;

	m_DCClbrV[0] = 31;
	m_DCClbrV[1] = 31;
	m_DCClbrV[2] = 31;
	m_DCClbrV[3] = 31;
	m_DCClbrV[4] = 31;

	m_bAllowSend = true;
};

/**
    Set module according to the chip version, revision and mask
    @param Ver chip version
    @param Rev chip revision
    @param Mask chip mask
*/
void TxLPF_Module::UpdateVerRevMask(char Ver, char Rev, char Mask)
{
	m_cVer = Ver;
	m_cRev = Rev;
	m_cMask = Mask;

	// Edit Register Test masks
	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
	{
		m_psD.cTestMap[0xF] += 0x80;
		// DC Offset comparator address is different when Mask=1
		m_psD.cTestMap[0x6] -= 0x08;
	};
};

/**
    Make data to download
*/
void TxLPF_Module::MakeData(int rAddr)
{
	char btmp;

	// ======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;

	// ======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;

	// ======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
	btmp = (char)cmbCalVal.itemIndex;
	m_psD.cDataW[0x02] |= btmp;

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x08; // Not to reset calibration modules
	// DC_ADDR
	btmp = (char)cmbDCCalAddr.itemIndex;
	m_psD.cDataW[0x03] |= btmp;

	// ======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
	// BWC_LPF[3:0]
	btmp = cmbLpfBw.itemIndex;
	btmp = btmp << 2;
	m_psD.cDataW[0x04] |= btmp;
	// EN
	btmp = chbPwrLpfMods.checked == true ? 1 : 0;
	btmp = btmp << 1;
	m_psD.cDataW[0x04] |= btmp;
	// DECODE
	btmp = (char)rgrDecode.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x04] |= btmp;

	// ======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	// BYP_EN_LPF
	btmp = (char)rgrLpfByp.itemIndex;
	btmp = btmp << 6;
	m_psD.cDataW[0x05] |= btmp;
	// DCO_DACCAL_LPF[5:0]
	btmp = (char)cmbDCOffset.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x05] |= btmp;

	// ======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
	if (m_cMAddr == TxLpfAddr)
	{
		// TX_DACBUF_PD
		btmp = chbTX_DACBUF_EN.checked == true ? 0 : 1;
		btmp = btmp << 7;
		m_psD.cDataW[0x06] |= btmp;
	}
	// RCCAL_LPF[2:0]
	btmp = (char)cmbRcCal.itemIndex;
	btmp = btmp << 4;
	m_psD.cDataW[0x06] |= btmp;
	// PD_DCOCMP_LPF
	btmp = chbPwrDCCmpr.checked == true ? 0 : 1;
	btmp = btmp << 3;
	m_psD.cDataW[0x06] |= btmp;
	// PD_DCODAC_LPF
	btmp = chbPwrDCDac.checked == true ? 0 : 1;
	btmp = btmp << 2;
	m_psD.cDataW[0x06] |= btmp;
	// PD_DCOREF_LPF
	btmp = chbPwrDCRef.checked == true ? 0 : 1;
	btmp = btmp << 1;
	m_psD.cDataW[0x06] |= btmp;
	// PD_FIL_LPF
	btmp = chbPwrLpf.checked == true ? 0 : 1;
	btmp = btmp << 0;
	m_psD.cDataW[0x06] |= btmp;

	// ======= register addr 0x07 =======
	if (m_cMAddr == RxLpfAddr)
	{
		if (m_ADDCmodule)
		{
			// ======= register addr 0x07 =======
			m_psD.cDataW[0x07] = 0x00;
			// EN_ADC_DAC
			btmp = m_ADDCmodule->getEN_ADC_DAC() == true ? 1 : 0;
			btmp = btmp << 7;
			m_psD.cDataW[0x07] |= btmp;
			// DECODE
			btmp = (char)m_ADDCmodule->getDecode();
			btmp = btmp << 6;
			m_psD.cDataW[0x07] |= btmp;
			// TX_CTRL1[6:4]
			btmp = (char)m_ADDCmodule->getDACInternalOutputLoadResistor();
			btmp = btmp << 3;
			m_psD.cDataW[0x07] |= btmp;
			// TX_CTRL1[3]
			btmp = (char)m_ADDCmodule->getDACReferenceCurrentResistor();
			btmp = btmp << 2;
			m_psD.cDataW[0x07] |= btmp;
			// TX_CTRL1[1:0]
			btmp = (char)m_ADDCmodule->getDACFullScaleOutputCurrent();
			btmp = btmp << 0;
			m_psD.cDataW[0x07] |= btmp;

			// ======= register addr 0x08 =======
			m_psD.cDataW[0x08] = 0x00;
			// RX_CTRL1[7:6]
			btmp = (char)m_ADDCmodule->getRefResistorBiasAdj();
			btmp = btmp << 6;
			m_psD.cDataW[0x08] |= btmp;
			// RX_CTRL1[5:4]
			btmp = (char)m_ADDCmodule->getRefBiasUp();
			btmp = btmp << 4;
			m_psD.cDataW[0x08] |= btmp;
			// RX_CTRL1[3:0]
			btmp = (char)m_ADDCmodule->getRefBiasDn();
			btmp = btmp << 0;
			m_psD.cDataW[0x08] |= btmp;

			// ======= register addr 0x09 =======
			m_psD.cDataW[0x09] = 0x00;
			// RX_CTRL2[7:6]
			btmp = (char)m_ADDCmodule->getRefGainAdj();
			btmp = btmp << 5;
			m_psD.cDataW[0x09] |= btmp;
			// RX_CTRL2[5:4]
			btmp = (char)m_ADDCmodule->getCoomonModeAdj();
			btmp = btmp << 3;
			m_psD.cDataW[0x09] |= btmp;
			// RX_CTRL2[3:2]
			btmp = (char)m_ADDCmodule->getRefBufferBoost();
			btmp = btmp << 1;
			m_psD.cDataW[0x09] |= btmp;
			// RX_CTRL2[0]
			btmp = m_ADDCmodule->getInputBufferDisable() == true ? 1 : 0;
			btmp = btmp << 0;
			m_psD.cDataW[0x09] |= btmp;

			// ======= register addr 0x0A =======
			m_psD.cDataW[0x0A] = 0x00;
			// MISC_CTRL[9]
			btmp = m_ADDCmodule->getRX_FSYNC_P();
			btmp = btmp << 7;
			m_psD.cDataW[0x0A] |= btmp;
			// MISC_CTRL[8]
			btmp = m_ADDCmodule->getRX_INTER();
			btmp = btmp << 6;
			m_psD.cDataW[0x0A] |= btmp;
			// MISC_CTRL[7]
			btmp = m_ADDCmodule->getDAC_CLK_P();
			btmp = btmp << 5;
			m_psD.cDataW[0x0A] |= btmp;
			// MISC_CTRL[6]
			btmp = m_ADDCmodule->getTX_FSYNC_P();
			btmp = btmp << 4;
			m_psD.cDataW[0x0A] |= btmp;
			// MISC_CTRL[5]
			btmp = m_ADDCmodule->getTX_INTER();
			btmp = btmp << 3;
			m_psD.cDataW[0x0A] |= btmp;
			// RX_CTRL3[7]
			btmp = m_ADDCmodule->getADCSamplingPhase();
			btmp = btmp << 2;
			m_psD.cDataW[0x0A] |= btmp;
			// RX_CTRL3[1:0]
			btmp = m_ADDCmodule->getClockNonOverlapAdjust();
			btmp = btmp << 0;
			m_psD.cDataW[0x0A] |= btmp;

			// ======= register addr 0x0B =======
			m_psD.cDataW[0x0B] = 0x00;
			// RX_CTRL4[7:6]
			btmp = m_ADDCmodule->getADCBiasResistorAdjust();
			btmp = btmp << 6;
			m_psD.cDataW[0x0B] |= btmp;
			// RX_CTRL4[5:4]
			btmp = m_ADDCmodule->getMainBiasDN();
			btmp = btmp << 4;
			m_psD.cDataW[0x0B] |= btmp;
			// RX_CTRL4[3:2]
			btmp = m_ADDCmodule->getADCAmp1Stage1BiasUp();
			btmp = btmp << 2;
			m_psD.cDataW[0x0B] |= btmp;
			// RX_CTRL4[1:0]
			btmp = m_ADDCmodule->getADCAmp24Stage1BiasUp();
			btmp = btmp << 0;
			m_psD.cDataW[0x0B] |= btmp;

			// ======= register addr 0x0C =======
			m_psD.cDataW[0x0C] = 0x00;
			// RX_CTRL5[7:6]
			btmp = m_ADDCmodule->getADCAmp1Stage2BiasUp();
			btmp = btmp << 6;
			m_psD.cDataW[0x0C] |= btmp;
			// RX_CTRL5[5:4]
			btmp = m_ADDCmodule->getADCAmp24Stage2BiasUp();
			btmp = btmp << 4;
			m_psD.cDataW[0x0C] |= btmp;
			// RX_CTRL5[3:2]
			btmp = m_ADDCmodule->getQuantizerBiasUp();
			btmp = btmp << 2;
			m_psD.cDataW[0x0C] |= btmp;
			// RX_CTRL5[1:0]
			btmp = m_ADDCmodule->getInputBufferBiasUp();
			btmp = btmp << 0;
			m_psD.cDataW[0x0C] |= btmp;

			// ======= register addr 0x0D =======
			m_psD.cDataW[0x0D] = 0x00;
			// REF_CTRL0[7:4]
			btmp = m_ADDCmodule->getBandgapTemp() + 8;
			btmp = btmp & 0x0F;
			btmp = btmp << 4;
			m_psD.cDataW[0x0D] |= btmp;
			// REF_CTRL0[3:0]
			btmp = m_ADDCmodule->getBandgapGain() + 8;
			btmp = btmp & 0x0F;
			btmp = btmp << 0;
			m_psD.cDataW[0x0D] |= btmp;

			// ======= register addr 0x0E =======
			m_psD.cDataW[0x0E] = 0x00;
			// REF_CTRL1[7:6]
			btmp = m_ADDCmodule->getRefAmpsBiasAdj();
			btmp = btmp << 6;
			m_psD.cDataW[0x0E] |= btmp;
			// REF_CTRL1[5:4]
			btmp = m_ADDCmodule->getRefAmpsBiasUp();
			btmp = btmp << 4;
			m_psD.cDataW[0x0E] |= btmp;
			// REF_CTRL1[3:0]
			btmp = m_ADDCmodule->getRefAmpsBiasDn();
			btmp = btmp << 0;
			m_psD.cDataW[0x0E] |= btmp;

			// ======= register addr 0x0F =======
			m_psD.cDataW[0x0F] = 0x00;
			// MISC_CTRL[4]
			btmp = m_ADDCmodule->getEN_DAC() == true ? 1 : 0;
			btmp = btmp << 4;
			m_psD.cDataW[0x0F] |= btmp;
			// EN_ADC_I
			btmp = m_ADDCmodule->getEN_ADC_I() == true ? 1 : 0;
			btmp = btmp << 3;
			m_psD.cDataW[0x0F] |= btmp;
			// EN_ADC_Q
			btmp = m_ADDCmodule->getEN_ADC_Q() == true ? 1 : 0;
			btmp = btmp << 2;
			m_psD.cDataW[0x0F] |= btmp;
			// EN_ADC_REF
			btmp = m_ADDCmodule->getEN_ADC_REF() == true ? 1 : 0;
			btmp = btmp << 1;
			m_psD.cDataW[0x0F] |= btmp;
			// EN_M_REF
			btmp = m_ADDCmodule->getEN_M_REF() == true ? 1 : 0;
			btmp = btmp << 0;
			m_psD.cDataW[0x0F] |= btmp;
		};
	};

	// To solve Ver=2 Rev=2 Mask=1 case
	// PD_DCOCMP_LPF
	btmp = chbPwrDCCmpr.checked == true ? 0 : 1;
	btmp = btmp << 7;
	m_psD.cDataW[0x0F] |= btmp;

	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch (rAddr)
	{
		// DC Calibration
	case 0xF0:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x03;
		break;

	case 0xF1:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x02;
		break;

		// User mode
	case 0x00:
	case 0x01:
	case 0x02:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x04;
		break;

	case 0x03:
	case 0x04:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x05;
		break;

		// Test mode
	case 0x05:
	case 0x06:
	case 0x07:
	case 0x08:
	case 0x09:
	case 0x0A:
		m_psD.iToW = 2;
		m_psD.iWInd[0] = 0x04;
		m_psD.iWInd[1] = 0x06;
		break;

	case 0x091:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0F;
		break;

	case 0x74:
	case 0x70:
	case 0x71:
	case 0x72:
	case 0x75:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x07;
		break;

	case 0x5F:
	case 0x60:
	case 0x61:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x08;
		break;

	case 0x62:
	case 0x63:
	case 0x64:
	case 0x65:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x09;
		break;

	case 0x50:
	case 0x51:
	case 0x52:
	case 0x53:
	case 0x54:
	case 0x66:
	case 0x67:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0A;
		break;

	case 0x68:
	case 0x69:
	case 0x6A:
	case 0x6B:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0B;
		break;

	case 0x6C:
	case 0x6D:
	case 0x6E:
	case 0x6F:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0C;
		break;

	case 0x5A:
	case 0x5B:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0D;
		break;

	case 0x5C:
	case 0x5D:
	case 0x5E:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0E;
		break;

	case 0x55:
	case 0x56:
	case 0x57:
	case 0x58:
	case 0x59:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0F;
		break;

		// Customer Mode
	case 0x80:
		m_psD.iToW = 2;
		m_psD.iWInd[0] = 0x04;
		m_psD.iWInd[1] = 0x05;
		break;

	default:
		m_psD.iToW = 0;
	};
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setLpfBw(int index)
{
	cmbLpfBw.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x00);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxLPF_Module::getLpfBw()
{
	return cmbLpfBw.itemIndex;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setPwrLpfMods(bool state)
{
	chbPwrLpfMods.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x01);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxLPF_Module::getPwrLpfMods()
{
	return chbPwrLpfMods.checked;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setDecode(int index)
{
	rgrDecode.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x02);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxLPF_Module::getDecode()
{
	return rgrDecode.itemIndex;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setLpfByp(int index)
{
	rgrLpfByp.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x03);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxLPF_Module::getLpfByp()
{
	return rgrLpfByp.itemIndex;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setDCOffset(int index)
{
	cmbDCOffset.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x04);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxLPF_Module::getDCOffset()
{
	return cmbDCOffset.itemIndex;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setRcCal(int index)
{
	cmbRcCal.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x05);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxLPF_Module::getRcCal()
{
	return cmbRcCal.itemIndex;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setPwrLpf(bool state)
{
	chbPwrLpf.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x06);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxLPF_Module::getPwrLpf()
{
	return chbPwrLpf.checked;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setPwrDCDac(bool state)
{
	chbPwrDCDac.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x07);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxLPF_Module::getPwrDCDac()
{
	return chbPwrDCDac.checked;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setPwrDCRef(bool state)
{
	chbPwrDCRef.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x08);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxLPF_Module::getPwrDCRef()
{
	return chbPwrDCRef.checked;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setPwrDCCmpr(bool state)
{
	chbPwrDCCmpr.checked = state;
	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
	{
		if (m_bAllowSend)
		{
			MakeData(0x091);
			pMainModule->CMAutoDownload(m_cMAddr);
		};
	}
	else
	{
		if (m_bAllowSend)
		{
			MakeData(0x09);
			pMainModule->CMAutoDownload(m_cMAddr);
		};
	};
}

bool TxLPF_Module::getPwrDCCmpr()
{
	return chbPwrDCCmpr.checked;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setTX_DACBUF_EN(bool state)
{
	chbTX_DACBUF_EN.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x0A);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxLPF_Module::getTX_DACBUF_EN()
{
	return chbTX_DACBUF_EN.checked;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::setDCCalAddr(int index)
{
	cmbDCCalAddr.itemIndex = index;
	// Enable DC CAL clock

	if(m_cMAddr == RxLpfAddr)
	{
	if(m_bAllowSend)
		pMainModule->EnableSPIClockByMask(0x08);
	}
	else
	{
	if(m_bAllowSend)
		pMainModule->EnableSPIClockByMask(0x02);
	};

	if (m_bAllowSend)
	{
		MakeData(0xF0);
		pMainModule->CMAutoDownload(m_cMAddr);
	};

	// Restore DC CAL clock
	if(m_bAllowSend)
		pMainModule->RestoreAllSPIClocks();
}

int TxLPF_Module::getDCCalAddr()
{
	return cmbDCCalAddr.itemIndex;
}

// ---------------------------------------------------------------------------
void TxLPF_Module::JoinADDC(int addr)
{
	MakeData(addr);
	pMainModule->CMAutoDownload(m_cMAddr);
};

// ---------------------------------------------------------------------------
void TxLPF_Module::DCResetCalibration()
{
	// Enable DC CAL clock
	if(m_cMAddr == RxLpfAddr)
	{
		if(m_bAllowSend)
          	pMainModule->EnableSPIClockByMask(0x08);
	}
	else
	{
		if(m_bAllowSend)
			pMainModule->EnableSPIClockByMask(0x02);
	};

	char btmp;
	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x00; // Set Load Value Inactive
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x00; // Set Reset Active
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)cmbDCCalAddr.itemIndex;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x00; // Set Load Value Inactive
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)cmbDCCalAddr.itemIndex;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	m_DCClbrV[0] = 31;
	m_DCClbrV[1] = 31;
	m_DCClbrV[2] = 31;
	m_DCClbrV[3] = 31;
	m_DCClbrV[4] = 31;

	// Restore DC CAL clock
	if(m_bAllowSend)
		pMainModule->RestoreAllSPIClocks();
}

// ---------------------------------------------------------------------------
void TxLPF_Module::DCLoadValues(unsigned int value)
{
	cmbCalVal.itemIndex = value;

	char btmp;

	// Enable DC CAL clock
	if(m_cMAddr == RxLpfAddr)
	{
		if(m_bAllowSend)
			pMainModule->EnableSPIClockByMask(0x08);
	}
	else
	{
		if(m_bAllowSend)
			pMainModule->EnableSPIClockByMask(0x02);
	};

	if (m_bAllowSend)
	{
		MakeData(0xF0);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
	if (m_bAllowSend)
	{
		MakeData(0xF1);
		pMainModule->CMAutoDownload(m_cMAddr);
	};

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x01; // Load Value
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)cmbDCCalAddr.itemIndex;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x00; // Deactivate Load Value
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)cmbDCCalAddr.itemIndex;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	m_DCClbrV[cmbDCCalAddr.itemIndex] = cmbCalVal.itemIndex;

	// Restore DC CAL clock
	if(m_bAllowSend)
		pMainModule->RestoreAllSPIClocks();
}
// ---------------------------------------------------------------------------

/**
    Make all data to write
*/
void TxLPF_Module::MakeWriteAll()
{
	MakeData(0xFFFF);
	m_psD.iToW = m_psD.iLen;
	for (int i = 0; i < m_psD.iLen; i++)
	{
		m_psD.iWInd[i] = i;
	};
};

/**
    Prints chip configuration to stream
    @param out stream for output
    @param Caption title of data
    @param bWrAll write all data
*/
bool TxLPF_Module::ChipVsGui(ofstream &out, string Caption, bool bWrAll)
{
	bool bRez = true;
	bool btmp;
	char str[64] = "";
	int itmp;

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

	if (bWrAll)
	{
		// DC_REGVAL[5:0]
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_REGVAL[5:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, "Read Only");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = DC_REGVAL_r00_b50();
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_LOCK[2:0]
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_LOCK[2:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, "Read Only");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = DC_LOCK_r01_b42();
		out << hex << showbase << uppercase;
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_CLBR_DONE
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_CLBR_DONE";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, "Read Only");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		if (DC_CLBR_DONE_r01_b11())
			strcpy(str, "Calibration in Progress");
		else
			strcpy(str, "Calibration Done");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_UD
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_UD";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, "Read Only");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		if (DC_UD_r01_b00())
			strcpy(str, "Counting Up");
		else
			strcpy(str, "Counting Down");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_CNTVAL[5:0]
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_CNTVAL[5:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, "Read Only");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = DC_CNTVAL_r02_b50();
		out << dec; // << showbase << uppercase;
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_START_CLBR
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_START_CLBR";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		if (DC_START_CLBR_r03_b55())
			strcpy(str, "Start Active");
		else
			strcpy(str, "Start Not Active");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_LOAD
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_LOAD";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		if (DC_LOAD_r03_b44())
			strcpy(str, "Load Active");
		else
			strcpy(str, "Load Not Active");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_SRESET
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_SRESET";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		if (DC_SRESET_r03_b33())
			strcpy(str, "Reset Not Active");
		else
			strcpy(str, "Reset Active");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// DC_ADDR[2:0]
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DC_ADDR[2:0]";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = DC_ADDR_r03_b20();
		out << hex << showbase << uppercase;
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
	};

	// BWC_LPF[3:0]
	if ((cmbLpfBw.itemIndex != BWC_LPF_r04_b52()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BWC_LPF[3:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, cmbLpfBw.sItems[cmbLpfBw.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "MHz";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		itmp = BWC_LPF_r04_b52();
		strcpy(str, cmbLpfBw.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "MHz";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// EN
	if ((chbPwrLpfMods.checked != (bool)EN_r04_b11()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| EN";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPwrLpfMods.checked)
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
		if (EN_r04_b11())
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

	// DECODE
	if ((rgrDecode.itemIndex != DECODE_r04_b00()) || bWrAll)
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
		if (DECODE_r04_b00())
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

	// BYP_EN_LPF
	if ((rgrLpfByp.itemIndex != BYP_EN_LPF_r05_b66()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BYP_EN_LPF";
		out.width(2);
		out << "|";
		out.width(40);
		if (rgrLpfByp.itemIndex == 1)
			strcpy(str, "Bypass LPF");
		else
			strcpy(str, "Normal Operation");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (BYP_EN_LPF_r05_b66())
			strcpy(str, "Bypass LPF");
		else
			strcpy(str, "Normal Operation");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// DCO_DACCAL_LPF[5:0]
	if ((cmbDCOffset.itemIndex != DCO_DACCAL_r05_b50()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DCO_DACCAL_LPF[5:0]";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbDCOffset.itemIndex;
		out << hex << showbase << uppercase << itmp;
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = DCO_DACCAL_r05_b50();
		out << hex << showbase << uppercase;
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	if ((!bRez) || bWrAll)
	{
		out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |"
			<< endl;
	};

	// TX_DACBUF_EN
	if (m_cMAddr == TxLpfAddr)
	{
		if ((chbTX_DACBUF_EN.checked == (bool)TX_DACBUF_PD_r06_b77()) || bWrAll)
		{
			memset(str, '\0', sizeof(str));
			out.width(32);
			out << "| TX_DACBUF_EN";
			out.width(2);
			out << "|";
			out.width(40);
			if (chbTX_DACBUF_EN.checked)
				strcpy(str, "TX DAC Buffers powered up");
			else
				strcpy(str, "TX DAC Buffers powered down");
			out << str;
			out.width(10);
			out << "";
			out.width(2);
			out << "|";
			out.width(40);
			memset(str, '\0', sizeof(str));
			if (TX_DACBUF_PD_r06_b77())
				strcpy(str, "TX DAC Buffers powered down");
			else
				strcpy(str, "TX DAC Buffers powered up");
			out << str;
			out.width(10);
			out << "";
			out.width(1);
			out << "|";
			out << endl;
			bRez = false;
		};
	};

	// RCCAL_LPF[2:0]
	if ((cmbRcCal.itemIndex != RCCAL_LPF_PD_r06_b64()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| RCCAL_LPF[2:0]";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = cmbRcCal.itemIndex;
		out << hex << showbase << uppercase << itmp;
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = RCCAL_LPF_PD_r06_b64();
		out << hex << showbase << uppercase;
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// PD_DCOCMP_LPF
	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
	{
		if ((chbPwrDCCmpr.checked == (bool)PD_DCOCMP_LPF_r0F_b77_v1())
			|| bWrAll)
		{
			memset(str, '\0', sizeof(str));
			out.width(32);
			out << "| PD_DCOCMP_LPF";
			out.width(2);
			out << "|";
			out.width(40);
			if (chbPwrDCCmpr.checked)
				strcpy(str, "DC Offset Comparator powered up");
			else
				strcpy(str, "DC Offset Comparator powered down");
			out << str;
			out.width(10);
			out << "";
			out.width(2);
			out << "|";
			out.width(40);
			memset(str, '\0', sizeof(str));
			if (PD_DCOCMP_LPF_r0F_b77_v1())
				strcpy(str, "DC Offset Comparator powered down");
			else
				strcpy(str, "DC Offset Comparator powered up");
			out << str;
			out.width(10);
			out << "";
			out.width(1);
			out << "|";
			out << endl;
			bRez = false;
		};
	}
	else
	{
		if ((chbPwrDCCmpr.checked == (bool)PD_DCOCMP_LPF_r06_b33_v0())
			|| bWrAll)
		{
			memset(str, '\0', sizeof(str));
			out.width(32);
			out << "| PD_DCOCMP_LPF";
			out.width(2);
			out << "|";
			out.width(40);
			if (chbPwrDCCmpr.checked)
				strcpy(str, "DC Offset Comparator powered up");
			else
				strcpy(str, "DC Offset Comparator powered down");
			out << str;
			out.width(10);
			out << "";
			out.width(2);
			out << "|";
			out.width(40);
			memset(str, '\0', sizeof(str));
			if (PD_DCOCMP_LPF_r06_b33_v0())
				strcpy(str, "DC Offset Comparator powered down");
			else
				strcpy(str, "DC Offset Comparator powered up");
			out << str;
			out.width(10);
			out << "";
			out.width(1);
			out << "|";
			out << endl;
			bRez = false;
		};
	};

	// PD_DCODAC_LPF
	if ((chbPwrDCDac.checked == (bool)PD_DCODAC_LPF_r06_b22()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| PD_DCODAC_LPF";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPwrDCDac.checked)
			strcpy(str, "DC Offset DAC powered up");
		else
			strcpy(str, "DC Offset DAC powered down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (PD_DCODAC_LPF_r06_b22())
			strcpy(str, "DC Offset DAC powered down");
		else
			strcpy(str, "DC Offset DAC powered up");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// PD_DCOREF_LPF
	if ((chbPwrDCRef.checked == (bool)PD_DCOREF_LPF_r06_b11()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| PD_DCOREF_LPF";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPwrDCRef.checked)
			strcpy(str, "DC DAC Reference powered up");
		else
			strcpy(str, "DC DAC Reference powered down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (PD_DCOREF_LPF_r06_b11())
			strcpy(str, "DC DAC Reference powered down");
		else
			strcpy(str, "DC DAC Reference powered up");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// PD_FIL_LPF
	if ((chbPwrLpf.checked == (bool)PD_FIL_LPF_r06_b00()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| PD_FIL_LPF";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPwrLpf.checked)
			strcpy(str, "LPF powered up");
		else
			strcpy(str, "LPF powered down");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (PD_FIL_LPF_r06_b00())
			strcpy(str, "LPF powered down");
		else
			strcpy(str, "LPF powered up");
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

	if (m_ADDCmodule)
		m_ADDCmodule->ChipVsGui(m_psD, out, "ADDC Modules:", bWrAll);

	return bRez;
};

/**
    Writes register map to the file. According to the customer wish.
    @param out stream for output
*/
void TxLPF_Module::MakeRegisterFile(ofstream &out)
{
	int itmp;

	// *** To create file from GUI data instead of chip registers data. Start ***//
	MakeData(0xFF);
	memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
	// ***  To create file from GUI data instead of chip registers data. End  ***//

	// DC_REGVAL[5:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x30 MASK 05 : 00  =";
	else
		out << "REG 0x50 MASK 05 : 00  =";
	itmp = DC_REGVAL_r00_b50();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_REGVAL";
	else
		out << "  RXLPF_DC_REGVAL";
	out << endl;

	// DC_LOCK[2:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x31 MASK 04 : 02  =";
	else
		out << "REG 0x51 MASK 04 : 02  =";
	itmp = DC_LOCK_r01_b42();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_LOCK";
	else
		out << "  RXLPF_DC_LOCK";
	out << endl;

	// DC_CLBR_DONE
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x31 MASK 01 : 01  =";
	else
		out << "REG 0x51 MASK 01 : 01  =";
	itmp = DC_CLBR_DONE_r01_b11();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_CLBR_DONE";
	else
		out << "  RXLPF_DC_CLBR_DONE";
	out << endl;

	// DC_UD
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x31 MASK 00 : 00  =";
	else
		out << "REG 0x51 MASK 00 : 00  =";
	itmp = DC_UD_r01_b00();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_UD";
	else
		out << "  RXLPF_DC_UD";
	out << endl;

	// DC_CNTVAL[5:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x32 MASK 05 : 00  =";
	else
		out << "REG 0x52 MASK 05 : 00  =";
	itmp = DC_CNTVAL_r02_b50();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_CNTVAL";
	else
		out << "  RXLPF_DC_CNTVAL";
	out << endl;

	// DC_START_CLBR
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x33 MASK 05 : 05  =";
	else
		out << "REG 0x53 MASK 05 : 05  =";
	itmp = DC_START_CLBR_r03_b55();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_START";
	else
		out << "  RXLPF_DC_START";
	out << endl;

	// DC_LOAD
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x33 MASK 04 : 04  =";
	else
		out << "REG 0x53 MASK 04 : 04  =";
	itmp = DC_LOAD_r03_b44();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_LOAD";
	else
		out << "  RXLPF_DC_LOAD";
	out << endl;

	// DC_SRESET
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x33 MASK 03 : 03  =";
	else
		out << "REG 0x53 MASK 03 : 03  =";
	itmp = DC_SRESET_r03_b33();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_SRESET";
	else
		out << "  RXLPF_DC_SRESET";
	out << endl;

	// DC_ADDR[2:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x33 MASK 02 : 00  =";
	else
		out << "REG 0x53 MASK 02 : 00  =";
	itmp = DC_ADDR_r03_b20();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DC_ADDR";
	else
		out << "  RXLPF_DC_ADDR";
	out << endl;

	// BWC_LPF[3:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x34 MASK 05 : 02  =";
	else
		out << "REG 0x54 MASK 05 : 02  =";
	itmp = BWC_LPF_r04_b52();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_BWC_LPF";
	else
		out << "  RXLPF_BWC_LPF";
	out << endl;

	// EN
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x34 MASK 01 : 01  =";
	else
		out << "REG 0x54 MASK 01 : 01  =";
	itmp = EN_r04_b11();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_EN";
	else
		out << "  RXLPF_EN";
	out << endl;

	// DECODE
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x34 MASK 00 : 00  =";
	else
		out << "REG 0x54 MASK 00 : 00  =";
	itmp = DECODE_r04_b00();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DECODE";
	else
		out << "  RXLPF_DECODE";
	out << endl;

	// BYP_EN_LPF
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x35 MASK 06 : 06  =";
	else
		out << "REG 0x55 MASK 06 : 06  =";
	itmp = BYP_EN_LPF_r05_b66();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_BYP_EN";
	else
		out << "  RXLPF_BYP_EN";
	out << endl;

	// DCO_DACCAL_LPF[5:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x35 MASK 05 : 00  =";
	else
		out << "REG 0x55 MASK 05 : 00  =";
	itmp = DCO_DACCAL_r05_b50();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DCO_DACCAL";
	else
		out << "  RXLPF_DCO_DACCAL";
	out << endl;

	// TX_DACBUF_PD
	if (m_cMAddr == TxLpfAddr)
	{
		out.width(24);
		out << left;
		out << "REG 0x36 MASK 07 : 07  =";
		itmp = TX_DACBUF_PD_r06_b77();
		out.width(6);
		out << right;
		out << itmp;
		out << "  TX_DACBUF_PD";
		out << endl;
	};

	// RCCAL_LPF[2:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x36 MASK 06 : 04  =";
	else
		out << "REG 0x56 MASK 06 : 04  =";
	itmp = RCCAL_LPF_PD_r06_b64();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_RCCAL";
	else
		out << "  RXLPF_RCCAL";
	out << endl;

	// PD_DCOCMP_LPF
	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
	{
		out.width(24);
		out << left;
		if (m_cMAddr == TxLpfAddr)
			out << "REG 0x3F MASK 80 : 80  =";
		else
			out << "REG 0x5F MASK 80 : 80  =";
		itmp = PD_DCOCMP_LPF_r0F_b77_v1();
		out.width(6);
		out << right;
		out << itmp;
		if (m_cMAddr == TxLpfAddr)
			out << "  TXLPF_PD_DCOCMP";
		else
			out << "  RXLPF_PD_DCOCMP";
		out << endl;
	}
	else
	{
		out.width(24);
		out << left;
		if (m_cMAddr == TxLpfAddr)
			out << "REG 0x36 MASK 03 : 03  =";
		else
			out << "REG 0x56 MASK 03 : 03  =";
		itmp = PD_DCOCMP_LPF_r06_b33_v0();
		out.width(6);
		out << right;
		out << itmp;
		if (m_cMAddr == TxLpfAddr)
			out << "  TXLPF_PD_DCOCMP";
		else
			out << "  RXLPF_PD_DCOCMP";
		out << endl;
	};

	// PD_DCODAC_LPF
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x36 MASK 02 : 02  =";
	else
		out << "REG 0x56 MASK 02 : 02  =";
	itmp = PD_DCODAC_LPF_r06_b22();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DCODAC";
	else
		out << "  RXLPF_DCODAC";
	out << endl;

	// PD_DCOREF_LPF
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x36 MASK 01 : 01  =";
	else
		out << "REG 0x56 MASK 01 : 01  =";
	itmp = PD_DCOREF_LPF_r06_b11();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_DCOREF";
	else
		out << "  RXLPF_DCOREF";
	out << endl;

	// PD_FIL_LPF
	out.width(24);
	out << left;
	if (m_cMAddr == TxLpfAddr)
		out << "REG 0x36 MASK 00 : 00  =";
	else
		out << "REG 0x56 MASK 00 : 00  =";
	itmp = PD_FIL_LPF_r06_b00();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxLpfAddr)
		out << "  TXLPF_PD_FIL";
	else
		out << "  RXLPF_PD_FIL";
	out << endl;

	if (m_cMAddr == RxLpfAddr)
	{
		m_ADDCmodule->MakeRegisterFile(m_psD, out);
	};
}

/**
    Writes Register - Value format to the file.
    @param out stream for output
*/
void TxLPF_Module::MakeRVFFile(ofstream &out)
{
	int iRval;
	int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

	// *** To create file from GUI data instead of chip registers data. Start ***//
	MakeData(0xFF);
	memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
	// ***  To create file from GUI data instead of chip registers data. End  ***//

	// 0x00 - Read Only

	// 0x01 - Read Only

	// 0x02
	iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0x3F);
	out << iRval;
	out << endl;

	// 0x03
	iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0x3F);
	out << iRval;
	out << endl;

	// 0x04
	iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x3F);
	out << iRval;
	out << endl;

	// 0x05
	iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0x7F);
	out << iRval;
	out << endl;

	// 0x06
	if (m_cMAddr == TxLpfAddr)
	{
		iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
		out << iRval;
		out << endl;
	}
	else
	{
		iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
		out << iRval;
		out << endl;
	};

	if (m_cMAddr == RxLpfAddr)
	{
		m_ADDCmodule->MakeRVFFile(m_psD, out);
	};

	// To resolove Ver=2 Rev=2 Mask=1 version
	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1) &&
		(m_cMAddr == RxLpfAddr))
	{
		iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0x80);
		out << iRval;
		out << endl;
	};
};

/**
    Saves chip configuration using FRIF format
    @param out stream for output
    @param FRIF_SPI_A frif parameter
*/
void TxLPF_Module::MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A)
{
	int iRval;
	int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

	// *** To create file from GUI data instead of chip registers data. Start ***//
	MakeData(0xFF);
	memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
	// ***  To create file from GUI data instead of chip registers data. End  ***//

	if (m_cMAddr == TxLpfAddr)
		out << "echo \"Now programming the Lime Tx LPF\"" << endl << endl;
	else
		out << "echo \"Now programming the Lime Rx LPF\"" << endl << endl;

	// 0x00 - Read Only

	// 0x01 - Read Only

	// 0x02
	// out << "# Register(s): DC_CNTVAL[5:0]" << endl;
	iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0x3F);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x03
	// out << "# Register(s): DC_START_CLBR, DC_ADDR, DC_LOAD, DC_SRESET, DC_ADDR[2:0]" << endl;
	iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0x3F);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x04
	// out << "# Register(s): BWC_LPF[3:0], EN, DECODE" << endl;
	iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x3F);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x05
	// out << "# Register(s): BYP_EN_LPF, DCO_DACCAL[5:0]" << endl;
	iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0x7F);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x06
	if (m_cMAddr == TxLpfAddr)
	{
		// out << "# Register(s): TX_DACBUF_PD, RCCAL_LPF[2:0], PD_DCOCMP_LPF, PD_DCODAC_LPF, PD_DCOREF_LPF, PD_FIL_LPF" << endl;

		// To resolove Ver=2 Rev=2 Mask=1 version
		if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
		{
			iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xF7);
		}
		else
		{
			iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
		};

		out << FRIF_DIR_W;
		// out << hex << uppercase << showbase << iRval;
		out << "0x" << hex << uppercase << noshowbase << iRval;
		// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
		// else                      out << FRIF_SPI_A_RX;
		// out << endl;
		out << FRIF_SPI_A;
		out << endl;
	}
	else
	{
		// out << "# Register(s): RCCAL_LPF[2:0], PD_DCOCMP_LPF, PD_DCODAC_LPF, PD_DCOREF_LPF, PD_FIL_LPF" << endl;
		// out << "# Register(s): " << endl;
		iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
		out << FRIF_DIR_W;
		// out << hex << uppercase << showbase << iRval;
		out << "0x" << hex << uppercase << noshowbase << iRval;
		// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
		// else                      out << FRIF_SPI_A_RX;
		// out << endl;
		out << FRIF_SPI_A;
		out << endl;
	};

	if (m_cMAddr == RxLpfAddr)
	{
		m_ADDCmodule->MakeRFIFFile(m_psD, out, FRIF_SPI_A);
	}
	else
	{
		// 0x0F
		// out << "# Register(s): PD_DCOCMP_LPF" << endl;
		iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0x80);
		out << FRIF_DIR_W;
		// out << hex << uppercase << showbase << iRval;
		out << "0x" << hex << uppercase << noshowbase << iRval;
		// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
		// else                      out << FRIF_SPI_A_RX;
		// out << endl;
		out << FRIF_SPI_A;
		out << endl;
	};

	if (m_cMAddr == TxLpfAddr)
		out << endl << "echo \"Tx LPF programming complete\"" << endl << endl;
	else
		out << endl << "echo \"Rx LPF programming complete\"" << endl << endl;
};

/**
    Sets GUI under data from chip
*/
bool TxLPF_Module::SetGUIUnderReadback()
{
	int itmp;
	bool bRez = true;

	m_bAllowSend = false;

	// DC_REGVAL[5:0]
	itmp = DC_REGVAL_r00_b50();
	lbDC_REGVAL = itmp;

	// DC_LOCK[2:0]
	itmp = DC_LOCK_r01_b42();
	lblDC_LOCK = itmp;

	// DC_CLBR_DONE
	itmp = DC_CLBR_DONE_r01_b11();
	lblDC_CLBR_DONE = itmp;

	// DC_UD
	itmp = DC_UD_r01_b00();
	lblDC_UD = itmp;

	// DC_CNTVAL[5:0]
	itmp = DC_CNTVAL_r02_b50();
	cmbCalVal.itemIndex = itmp;

	// DC_START_CLBR
	itmp = DC_START_CLBR_r03_b55();

	// DC_LOAD
	itmp = DC_LOAD_r03_b44();

	// DC_SRESET
	itmp = DC_SRESET_r03_b33();

	// DC_ADDR[2:0]
	itmp = DC_ADDR_r03_b20();
	if (itmp > 4)
	{
		itmp = 4;
		bRez = false;
	}
	cmbDCCalAddr.itemIndex = itmp;

	// BWC_LPF[3:0]
	itmp = BWC_LPF_r04_b52();
	cmbLpfBw.itemIndex = itmp;

	// EN
	itmp = EN_r04_b11();
	chbPwrLpfMods.checked = itmp;

	// DECODE
	itmp = DECODE_r04_b00();
	rgrDecode.itemIndex = itmp;

	// BYP_EN_LPF
	itmp = BYP_EN_LPF_r05_b66();
	rgrLpfByp.itemIndex = itmp;

	// DCO_DACCAL_LPF[5:0]
	itmp = DCO_DACCAL_r05_b50();
	cmbDCOffset.itemIndex = itmp;

	// TX_DACBUF_EN
	if (m_cMAddr == TxLpfAddr)
	{
		itmp = TX_DACBUF_PD_r06_b77();
		chbTX_DACBUF_EN.checked = itmp;
		chbTX_DACBUF_EN.checked = !chbTX_DACBUF_EN.checked;
	};

	// RCCAL_LPF[2:0]
	itmp = RCCAL_LPF_PD_r06_b64();
	cmbRcCal.itemIndex = itmp;

	// PD_DCOCMP_LPF
	// To resolove Ver=2 Rev=2 Mask=1 version
	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
	{
		itmp = PD_DCOCMP_LPF_r0F_b77_v1();
	}
	else
	{
		itmp = PD_DCOCMP_LPF_r06_b33_v0();
	};
	chbPwrDCCmpr.checked = itmp;
	chbPwrDCCmpr.checked = !chbPwrDCCmpr.checked;

	// PD_DCODAC_LPF
	itmp = PD_DCODAC_LPF_r06_b22();
	chbPwrDCDac.checked = itmp;
	chbPwrDCDac.checked = !chbPwrDCDac.checked;

	// PD_DCOREF_LPF
	itmp = PD_DCOREF_LPF_r06_b11();
	chbPwrDCRef.checked = itmp;
	chbPwrDCRef.checked = !chbPwrDCRef.checked;

	// PD_FIL_LPF
	itmp = PD_FIL_LPF_r06_b00();
	chbPwrLpf.checked = itmp;
	chbPwrLpf.checked = !chbPwrLpf.checked;

	m_bAllowSend = true;

	if (m_ADDCmodule)
		m_ADDCmodule->SetGUIUnderReadback(m_psD);

	return bRez;
};

/**
    Saves configuration to ini file
    @param pini pointer to ini file parser
*/
void TxLPF_Module::SaveConf(ini_t *pini)
{
	char Sect[80];
    sprintf(Sect, "%i", (int)m_cMAddr);

	pini->Create(Sect);

	pini->Set("cmbDCCalAddr", cmbDCCalAddr.itemIndex);
	pini->Set("cmbCalVal", cmbCalVal.itemIndex);
	pini->Set("LPF_dco_I", GetCalVal(0x00));
	pini->Set("LPF_dco_Q", GetCalVal(0x01));

	pini->Set("cmbLpfBw", cmbLpfBw.itemIndex);
	pini->Set("chbPwrLpfMods", chbPwrLpfMods.checked);
	pini->Set("rgrDecode", rgrDecode.itemIndex);

	pini->Set("rgrLpfByp", rgrLpfByp.itemIndex);
	pini->Set("cmbDCOffset", cmbDCOffset.itemIndex);

	pini->Set("chbTX_DACBUF_EN", chbTX_DACBUF_EN.checked);
	pini->Set("cmbRcCal", cmbRcCal.itemIndex);
	pini->Set("chbPwrDCCmpr", chbPwrDCCmpr.checked);
	pini->Set("chbPwrDCDac", chbPwrDCDac.checked);
	pini->Set("chbPwrDCRef", chbPwrDCRef.checked);
	pini->Set("chbPwrLpf", chbPwrLpf.checked);
};

/**
    Reads configuration from ini file
    @param pini pointer to ini file parser
*/
void TxLPF_Module::ReadConf(ini_t *pini)
{
	char Sect[80];
    sprintf(Sect, "%i", (int)m_cMAddr);

	m_bAllowSend = false;

	pini->Select(Sect);

	cmbDCCalAddr.itemIndex = pini->Get("cmbDCCalAddr", 0);
	cmbCalVal.itemIndex = pini->Get("cmbCalVal", 31);
	m_DCClbrV[0] = pini->Get("LPF_dco_I", 31);
	m_DCClbrV[1] = pini->Get("LPF_dco_Q", 31);

	cmbLpfBw.itemIndex = pini->Get("cmbLpfBw", 0);
	chbPwrLpfMods.checked = pini->Get("chbPwrLpfMods", 1);
	rgrDecode.itemIndex = pini->Get("rgrDecode", 0);

	rgrLpfByp.itemIndex = pini->Get("rgrLpfByp", 0);
	cmbDCOffset.itemIndex = pini->Get("cmbDCOffset", 12);

	chbTX_DACBUF_EN.checked = pini->Get("chbTX_DACBUF_EN", 1);
	cmbRcCal.itemIndex = pini->Get("cmbRcCal", 3);
	chbPwrDCCmpr.checked = pini->Get("chbPwrDCCmpr", 1);
	chbPwrDCDac.checked = pini->Get("chbPwrDCDac", 1);
	chbPwrDCRef.checked = pini->Get("chbPwrDCRef", 1);
	chbPwrLpf.checked = pini->Get("chbPwrLpf", 1);
	m_bAllowSend = true;
};

/**
    Reads and returns DC calibration info
*/
int TxLPF_Module::DCGetCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue)
{
	char rez;

	if(m_cMAddr == RxLpfAddr)
	{
		pMainModule->EnableSPIClockByMask(0x08);
		rez = pMainModule->getSerPort()->SPI_Read_OneByte(0x50);
		calibVal = rez;

		rez = pMainModule->getSerPort()->SPI_Read_OneByte(0x51);

		lockPattern = (rez >> 2) & 0x07;
		calibStatus = (rez >> 1) & 0x01;
		compValue = rez & 0x01;
	}
	else
	{
		pMainModule->EnableSPIClockByMask(0x02);
		rez = pMainModule->getSerPort()->SPI_Read_OneByte(0x30);
		calibVal = rez;

		rez = pMainModule->getSerPort()->SPI_Read_OneByte(0x31);

		lockPattern = (rez >> 2) & 0x07;
		calibStatus = (rez >> 1) & 0x01;
		compValue = rez & 0x01;
	};

	if(m_bAllowSend)
		pMainModule->RestoreAllSPIClocks();
	return 0;
}

/**
    Activate start calibration command and then deactivate.
*/
void TxLPF_Module::DCStartCalibration()
{
	// Enable DC CAL clock
	if(m_cMAddr == RxLpfAddr)
	{
		if(m_bAllowSend)
			pMainModule->EnableSPIClockByMask(0x08);
	}
	else
	{
		if(m_bAllowSend)
			pMainModule->EnableSPIClockByMask(0x02);
	};

	StartCalibration(cmbDCCalAddr.itemIndex);

	// Restore DC CAL clock
	if(m_bAllowSend)
		pMainModule->RestoreAllSPIClocks();
}

void TxLPF_Module::StartCalibration(int Addr)
{
	char btmp;
	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_LOAD
	btmp = 0x01; // Start Calibration
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x00; // Load Value Inactive
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	// btmp = (char)cmbDCCalAddr.itemIndex;
	btmp = (char)Addr;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_LOAD
	btmp = 0x00; // Deactivate Start Calibration
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x00; // Load Value Inactive
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	// btmp = (char)cmbDCCalAddr.itemIndex;
	btmp = (char)Addr;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	// m_DCClbrV[cmbDCCalAddr.itemIndex] = GetCalVal(cmbDCCalAddr.itemIndex);
	m_DCClbrV[Addr] = GetCalVal(Addr);

};

int TxLPF_Module::GetCalVal(int Addr)
{
	char btmp;

	// Change address to Addr
	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x00; // Set Load Value Inactive
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)Addr;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	// Read SPI configuration
	pMainModule->CMRead(0, m_cMAddr);

	// Return value
	// DC_REGVAL[5:0]
	return (m_psD.cDataR[0x00] & 0x3F);
};

/**
    Write DC Calibration value
    @param Addr calibration address
    @param Val value to write
*/
void TxLPF_Module::SetCalVal(int Addr, int Val)
{
	char btmp;

	// Change address to Addr
	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_START_CLBR
	btmp = 0x00; // Set Load Value Inactive
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)Addr;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	// Write Value to DC_CNTVAL[5:0] register
	// ======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
	btmp = (char)Val;
	m_psD.cDataW[0x02] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x02;
	pMainModule->CMAutoDownload(m_cMAddr);

	// Perform Load Operation
	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x01; // Load Value Active
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)Addr;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	m_psD.cDataW[0x03] |= btmp;
	// DC_LOAD
	btmp = 0x00; // Load Value Inactive
	btmp = btmp << 4;
	m_psD.cDataW[0x03] |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	m_psD.cDataW[0x03] |= btmp;
	// DC_ADDR
	btmp = (char)Addr;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);
};

/**
    Write All DC Calibration values
*/
void TxLPF_Module::DownloadAllDCCalValues()
{
	SetCalVal(0x00, m_DCClbrV[0]);
	SetCalVal(0x01, m_DCClbrV[1]);
};

/**
    Returns DC Calibration Chain status (address 0x1)
    Address of DC Calibration Chain should be settled before.
*/
char TxLPF_Module::GetCalStatus()
{
	// Read SPI configuration
	pMainModule->CMRead(0, m_cMAddr);

	// Return value
	// DC_REGVAL[5:0]
	return m_psD.cDataR[0x01];
};

/**
    Set DC Calibration values in the class to defaults
*/
void TxLPF_Module::SetCalDefaults()
{
	m_DCClbrV[0] = 31;
	m_DCClbrV[1] = 31;
	m_DCClbrV[2] = 31;
	m_DCClbrV[3] = 31;
	m_DCClbrV[4] = 31;
};

// ---------------------------------------------------------------------------
// Functions for customer mode interface
// ---------------------------------------------------------------------------
void TxLPF_Module::CustSet_BypassLpfON()
{
	m_bAllowSend = false;
	rgrDecode.itemIndex = 0;
	chbPwrLpfMods.checked = false;
	rgrLpfByp.itemIndex = 1;
	m_bAllowSend = true;

	MakeData(0x80);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void TxLPF_Module::CustSet_BypassLpfOFF()
{
	m_bAllowSend = false;
	rgrDecode.itemIndex = 0;
	chbPwrLpfMods.checked = true;
	rgrLpfByp.itemIndex = 0;
	m_bAllowSend = true;

	MakeData(0x80);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void TxLPF_Module::LpfPowerOn(bool on)
{
	if(on)
	{
        m_bAllowSend = false;
		rgrDecode.itemIndex = 0;
		chbPwrLpfMods.checked = true;
		m_bAllowSend = true;

		MakeData(0x01);
		pMainModule->CMAutoDownload(m_cMAddr);
	}
	else
	{
        m_bAllowSend = false;
		rgrDecode.itemIndex = 0;
		chbPwrLpfMods.checked = false;
		m_bAllowSend = true;

		MakeData(0x01);
		pMainModule->CMAutoDownload(m_cMAddr);
    }
}

void TxLPF_Module::CustSet_EnableDCOffsetCompOnly()
{
	m_bAllowSend = false;
	rgrDecode.itemIndex = 1;
	chbPwrLpf.checked = false;
	chbPwrDCDac.checked = false;
	chbPwrDCRef.checked = false;
	chbPwrDCCmpr.checked = true;
	m_bAllowSend = true;

	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
	{
		MakeData(0x091);
	}
	else
	{
		MakeData(0x09);
	};
	pMainModule->CMAutoDownload(m_cMAddr);
};

void TxLPF_Module::CustSet_RestoreDCOffsetCompOnly()
{
	m_bAllowSend = false;
	rgrDecode.itemIndex = 0;
	chbPwrDCCmpr.checked = false;
	m_bAllowSend = true;

	if ((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
	{
		MakeData(0x091);
	}
	else
	{
		MakeData(0x09);
	};
	pMainModule->CMAutoDownload(m_cMAddr);
};

void TxLPF_Module::CustSet_BypassLPFOnlyOn()
{
	m_bAllowSend = false;
	setLpfByp(1);
	m_bAllowSend = true;

	MakeData(0x03);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void TxLPF_Module::CustSet_BypassLPFOnlyOff()
{
	m_bAllowSend = false;
	setLpfByp(0);
	m_bAllowSend = true;

	MakeData(0x03);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void TxLPF_Module::CustSet_LPFCALVAL(int Val)
{
	m_bAllowSend = false;
	setRcCal(Val);
	m_bAllowSend = true;

	MakeData(0x05);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void TxLPF_Module::CustSet_LPFDCVAL(int Val)
{
	m_bAllowSend = false;
	setDCOffset(Val);
	m_bAllowSend = true;

	MakeData(0x04);
	pMainModule->CMAutoDownload(m_cMAddr);
};

int TxLPF_Module::CustGet_DecodeState()
{
	return rgrDecode.itemIndex;
};

void TxLPF_Module::CustSet_DecodeState(int ind)
{
	setDecode(ind);
};

int TxLPF_Module::CustGet_LPFTestState()
{
	return rgrLpfByp.itemIndex;
};

void TxLPF_Module::CustSet_LPFTestState(int ind)
{
	setLpfByp(ind);
};

bool TxLPF_Module::CustGet_PwrLpfMods()
{
	return chbPwrLpfMods.checked;
};

bool TxLPF_Module::CustGet_PwrLpf()
{
	return chbPwrLpf.checked;
};

bool TxLPF_Module::CustGet_PwrDCDac()
{
	return chbPwrDCDac.checked;
};

bool TxLPF_Module::CustGet_PwrDCRef()
{
	return chbPwrDCRef.checked;
};

bool TxLPF_Module::CustGet_PwrDCCmpr()
{
	return chbPwrDCCmpr.checked;
};

void TxLPF_Module::CustSet_PwrLpfMods(bool state)
{
	// chbPwrLpfMods.checked = state;
	setPwrLpfMods(state);
};

void TxLPF_Module::CustSet_PwrLpf(bool state)
{
	// chbPwrLpf.checked = state;
	setPwrLpf(state);
};

void TxLPF_Module::CustSet_PwrDCDac(bool state)
{
	// chbPwrDCDac.checked = state;
	setPwrDCDac(state);
};

void TxLPF_Module::CustSet_PwrDCRef(bool state)
{
	// chbPwrDCRef.checked = state;
	setPwrDCRef(state);
};

void TxLPF_Module::CustSet_PwrDCCmpr(bool state)
{
	// chbPwrDCCmpr.checked = state;
	setPwrDCCmpr(state);
};

// ---------------------------------------------------------------------------
// Functions for register testing
// ---------------------------------------------------------------------------
void TxLPF_Module::RT_SetTestMask(char Mask)
{
	MakeWriteAll();

	for (int i = 0; i < m_psD.iToW; i++)
	{
		m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
	};

	pMainModule->CMAutoDownload(m_cMAddr);
};
