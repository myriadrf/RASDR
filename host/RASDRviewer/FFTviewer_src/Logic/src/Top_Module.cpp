// -----------------------------------------------------------------------------
// FILE: 		Top_Module.cpp
// DESCRIPTION:	Top control user interface
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Top_Module.h"
#include "Main_Module.h"
#include "ConnectionManager.h"
//---------------------------------------------------------------------------
//0x0
#define             DC_REGVAL_r00_b50() ((m_psD.cDataR[0x00] & 0x3F) >> 0)
//0x1
#define          RCCAL_LPFCAL_r01_b75() ((m_psD.cDataR[0x01] & 0xE0) >> 5)
#define               DC_LOCK_r01_b42() ((m_psD.cDataR[0x01] & 0x1C) >> 2)
#define          DC_CLBR_DONE_r01_b11() ((m_psD.cDataR[0x01] & 0x02) >> 1)
#define                 DC_UD_r01_b00() ((m_psD.cDataR[0x01] & 0x01) >> 0)
//0x2
#define             DC_CNTVAL_r02_b50() ((m_psD.cDataR[0x02] & 0x3F) >> 0)
//0x3
#define         DC_START_CLBR_r03_b55() ((m_psD.cDataR[0x03] & 0x20) >> 5)
#define               DC_LOAD_r03_b44() ((m_psD.cDataR[0x03] & 0x10) >> 4)
#define             DC_SRESET_r03_b33() ((m_psD.cDataR[0x03] & 0x08) >> 3)
#define               DC_ADDR_r03_b20() ((m_psD.cDataR[0x03] & 0x07) >> 0)
//0x4
#define                   VER_r04_b74() ((m_psD.cDataR[0x04] & 0xF0) >> 4)
#define                   REV_r04_b30() ((m_psD.cDataR[0x04] & 0x0F) >> 0)
//0x5
#define                DECODE_r05_b77() ((m_psD.cDataR[0x05] & 0x80) >> 7)
#define                SRESET_r05_b55() ((m_psD.cDataR[0x05] & 0x20) >> 5)
#define                    EN_r05_b44() ((m_psD.cDataR[0x05] & 0x10) >> 4)
#define                 STXEN_r05_b33() ((m_psD.cDataR[0x05] & 0x08) >> 3)
#define                 SRXEN_r05_b22() ((m_psD.cDataR[0x05] & 0x04) >> 2)
#define               TFWMODE_r05_b11() ((m_psD.cDataR[0x05] & 0x02) >> 1)
//0x6
#define         CLKSEL_LPFCAL_r06_b33() ((m_psD.cDataR[0x06] & 0x08) >> 3)
#define          PD_CLKLPFCAL_r06_b22() ((m_psD.cDataR[0x06] & 0x04) >> 2)
#define     ENF_EN_CAL_LPFCAL_r06_b11() ((m_psD.cDataR[0x06] & 0x02) >> 1)
#define        RST_CAL_LPFCAL_r06_b00() ((m_psD.cDataR[0x06] & 0x01) >> 0)
//0x7
#define         EN_CAL_LPFCAL_r07_b77() ((m_psD.cDataR[0x07] & 0x80) >> 7)
#define FORCE_CODE_CAL_LPFCAL_r07_b64() ((m_psD.cDataR[0x07] & 0x70) >> 4)
#define            BWC_LPFCAL_r07_b30() ((m_psD.cDataR[0x07] & 0x0F) >> 0)
//0x8
#define                 BBBYP_r08_b77() ((m_psD.cDataR[0x08] & 0x80) >> 7)
#define            LBEN_LPFIN_r08_b66() ((m_psD.cDataR[0x08] & 0x40) >> 6)
#define           LBEN_VGA2IN_r08_b55() ((m_psD.cDataR[0x08] & 0x20) >> 5)
#define             LBEN_OPIN_r08_b44() ((m_psD.cDataR[0x08] & 0x10) >> 4)
#define                  LBEN_r08_b64() ((m_psD.cDataR[0x08] & 0x70) >> 4)
#define                LBRFEN_r08_b30() ((m_psD.cDataR[0x08] & 0x0F) >> 0)
//0x9
#define               RXOUTSW_r09_b77() ((m_psD.cDataR[0x09] & 0x80) >> 7)
#define             PLLCLKOUT_r09_b66() ((m_psD.cDataR[0x09] & 0x40) >> 6)
#define               LPF_CAL_r09_b55() ((m_psD.cDataR[0x09] & 0x20) >> 5)
#define         Rx_VGA2_DCCAL_r09_b44() ((m_psD.cDataR[0x09] & 0x10) >> 4)
#define          Rx_LPF_DCCAL_r09_b33() ((m_psD.cDataR[0x09] & 0x08) >> 3)
#define            Rx_DSM_SPI_r09_b22() ((m_psD.cDataR[0x09] & 0x04) >> 2)
#define      Tx_LPF_SPI_DCCAL_r09_b11() ((m_psD.cDataR[0x09] & 0x02) >> 1)
#define            Tx_DSM_SPI_r09_b00() ((m_psD.cDataR[0x09] & 0x01) >> 0)
//0xA
#define                FDDTDD_r0A_b11() ((m_psD.cDataR[0x0A] & 0x02) >> 1)
#define                TDDMOD_r0A_b00() ((m_psD.cDataR[0x0A] & 0x01) >> 0)
//0xB
#define              PDXCOBUF_r0B_b44() ((m_psD.cDataR[0x0B] & 0x10) >> 4)
#define            SLFBXCOBUF_r0B_b33() ((m_psD.cDataR[0x0B] & 0x08) >> 3)
#define             BYPXCOBUF_r0B_b22() ((m_psD.cDataR[0x0B] & 0x04) >> 2)
#define      PD_DCOREF_LPFCAL_r0B_b11() ((m_psD.cDataR[0x0B] & 0x02) >> 1)
#define            RF_LBSW_PD_r0B_b00() ((m_psD.cDataR[0x0B] & 0x01) >> 0)


#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A ",20"


//---------------------------------------------------------------------------
Top_Module::Top_Module()
{
}

//---------------------------------------------------------------------------
Top_Module::~Top_Module()
{
	delete[] m_psD.cCmdW;
	delete[] m_psD.cDataW;
	delete[] m_psD.cCmdR;
	delete[] m_psD.cDataR;
	delete[] m_psD.iRInd;
	delete[] m_psD.iWInd;
	delete[] m_psD.cTestMap; //RT//
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Top_Module::Initialize(Main_Module *pMain, char MAddr)
{
	pMainModule = pMain;

	m_cMAddr = MAddr;

	m_psD.iLen = TopLen;
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
	m_psD.cTestMap[0x0] = 0x00;
	m_psD.cTestMap[0x1] = 0x00;
	m_psD.cTestMap[0x2] = 0x3F;
	m_psD.cTestMap[0x3] = 0x3F;
	m_psD.cTestMap[0x4] = 0x00;
	m_psD.cTestMap[0x5] = 0xBE; // 0xBC
	m_psD.cTestMap[0x6] = 0x0F;
	m_psD.cTestMap[0x7] = 0xFF;
	m_psD.cTestMap[0x8] = 0xFF;
	m_psD.cTestMap[0x9] = 0xFF;
	m_psD.cTestMap[0xA] = 0x03;
	m_psD.cTestMap[0xB] = 0x1F;
	// m_psD.cTestMap[0xC] = 0x00;
	// m_psD.cTestMap[0xD] = 0x00;
	// m_psD.cTestMap[0xE] = 0x00;
	// m_psD.cTestMap[0xF] = 0x00;

	SetDefaults();
};

//---------------------------------------------------------------------------
void Top_Module::SetDefaults()
{
	m_bAllowSend = false;

	// DECODE
	rgrDecode.itemIndex = 0;
	// SRESET
	rgrDsmRst.itemIndex = 1;
	// EN
	chbPwrTopMods.checked = true;
	// STXEN
	chbPwrSoftTx.checked = false;
	// SRXEN
	chbPwrSoftRx.checked = false;
	// TFWMODE
	rgrSpiMode.itemIndex = 1;

	// CLKSEL_LPFCAL
	rgrCLKSEL_LPFCAL.itemIndex = 1;
	rgrCLKSEL_LPFCAL.add("3 Wire");
	rgrCLKSEL_LPFCAL.add("4 Wire");
	// PD_CLKLPFCAL
	chbPD_CLKLPFCAL.checked = true;
	// ENF_EN_CAL_LPFCAL
	chbLpfCalEnEnf.checked = false;
	// RST_CAL_LPFCAL
	chbLpfCalRst.checked = true;

	// EN_CAL_LPFCAL
	chbLpfCalEn.checked = false;
	// FORCE_CODE_CAL_LPFCAL[2:0]
	rgrLpfCalCode.clear();
	for (int i = 0; i < 8; i++)
	{
		rgrLpfCalCode.add(i);
	};
	rgrLpfCalCode.itemIndex = 0;
	// BWC_LPFCAL[3:0]
	rgrLpfCalBw.clear();
	rgrLpfCalBw.add("14");
	rgrLpfCalBw.add("10");
	rgrLpfCalBw.add("7");
	rgrLpfCalBw.add("6");
	rgrLpfCalBw.add("5");
	rgrLpfCalBw.add("4.375");
	rgrLpfCalBw.add("3.5");
	rgrLpfCalBw.add("3");
	rgrLpfCalBw.add("2.75");
	rgrLpfCalBw.add("2.5");
	rgrLpfCalBw.add("1.92");
	rgrLpfCalBw.add("1.5");
	rgrLpfCalBw.add("1.375");
	rgrLpfCalBw.add("1.25");
	rgrLpfCalBw.add("0.875");
	rgrLpfCalBw.add("0.75");
	rgrLpfCalBw.itemIndex = 0;

	// BBBYP_RX
	chbRxTestModeEn.checked = false;
	// Control changed to radiobuttons instead of checkboxes,
	// while only one should be active at a time:
	// LBEN_LPFIN_RX
	// LBEN_VGA2IN_RX
	// LBEN_OPIN_RX
	rgrBBLB.itemIndex = 0;
	// LBRFEN_RXFE[3:0]
	rgrRFLB.itemIndex = 0;

	// RXOUTSW
	rgrRXOUTSW.itemIndex = 0;
	// CLK_EN[6:0]
	for (int i = 0; i < 6; i++)
	{
		chbaSpiClkBuf[i] = false;
	};
	chbaSpiClkBuf[6] = true;

	// FDDTDD
	rgrFDDTDD.itemIndex = 0;
	// TDDMOD
	rgrTDDMOD.itemIndex = 0;

	// PDXCOBUF
	chbPDXCOBUF.checked = false;
	// SLFBXCOBUF
	chbSLFBXCOBUF.checked = true;
	// BYPXCOBUF
	chbBYPXCOBUF.checked = false;
	// PD_DCOREF_LPFCAL
	chbPwrLpfCal.checked = true;
	// RFLBSW_EN
	chbPwrRfLbsw.checked = false;

	// DC_ADDR[3:0]
	cmbDCCalAddr.clear();
	for (int i = 0; i < 5; i++)
	{
		cmbDCCalAddr.add(i);
	};
	cmbDCCalAddr.itemIndex = 0;

	// DC_CNTVAL[5:0]
	rgrCalVal.clear();
	for (int i = 0; i < 64; i++)
	{
		rgrCalVal.add(i);
	};
	rgrCalVal.itemIndex = 31;

	m_DCClbrV[0] = 31;
	m_DCClbrV[1] = 31;
	m_DCClbrV[2] = 31;
	m_DCClbrV[3] = 31;
	m_DCClbrV[4] = 31;

	//SetGuiDecode();

	m_bAllowSend = true;
};

// ----------------------------------------------------------------------------
// Make data to download
// ----------------------------------------------------------------------------
void Top_Module::MakeData(int rAddr)
{
	char btmp;

	// ======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;

	// ======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;

	// ======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
	btmp = (char)rgrCalVal.itemIndex;
	m_psD.cDataW[0x02] |= btmp;

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x08; // Not to reset calibration modules
	// DC_ADDR
	btmp = (char)cmbDCCalAddr.itemIndex;
	m_psD.cDataW[0x03] |= btmp;

	// ======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x22;

	// ======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	// DECODE
	btmp = (char)rgrDecode.itemIndex;
	btmp = btmp << 7;
	m_psD.cDataW[0x05] |= btmp;
	// SRESET
	btmp = rgrDsmRst.itemIndex;
	btmp = btmp << 5;
	m_psD.cDataW[0x05] |= btmp;
	// EN
	btmp = chbPwrTopMods.checked == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x05] |= btmp;
	// STXEN
	btmp = chbPwrSoftTx.checked == true ? 1 : 0;
	btmp = btmp << 3;
	m_psD.cDataW[0x05] |= btmp;
	// SRXEN
	btmp = chbPwrSoftRx.checked == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x05] |= btmp;
	// TFWMODE
	btmp = rgrSpiMode.itemIndex;
	btmp = btmp << 1;
	m_psD.cDataW[0x05] |= btmp;

	// ======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
	// CLKSEL_LPFCAL
	btmp = rgrCLKSEL_LPFCAL.itemIndex;
	btmp = btmp << 3;
	m_psD.cDataW[0x06] |= btmp;
	// PD_CLKLPFCAL
	btmp = chbPD_CLKLPFCAL.checked == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x06] |= btmp;
	// ENF_EN_CAL
	btmp = chbLpfCalEnEnf.checked == true ? 1 : 0;
	btmp = btmp << 1;
	m_psD.cDataW[0x06] |= btmp;
	// RST_CAL_LPFCAL
	btmp = chbLpfCalRst.checked == true ? 1 : 0;
	btmp = btmp << 0;
	m_psD.cDataW[0x06] |= btmp;

	// ======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
	// EN_CAL_LPFCAL
	btmp = chbLpfCalEn.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x07] |= btmp;
	// FORCE_CODE_CAL_LPFCAL[2:0]
	btmp = rgrLpfCalCode.itemIndex;
	btmp = btmp << 4;
	m_psD.cDataW[0x07] |= btmp;
	// BWC_LPFCAL[3:0]
	btmp = rgrLpfCalBw.itemIndex;
	m_psD.cDataW[0x07] |= btmp;

	// ======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
	// BBBYP_RX
	btmp = chbRxTestModeEn.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x08] |= btmp;
	// LBEN_LPFIN_RX
	// btmp = chbBBLpf.checked == true ? 1 : 0;
	btmp = rgrBBLB.itemIndex == 1 ? 1 : 0;
	btmp = btmp << 6;
	m_psD.cDataW[0x08] |= btmp;
	// LBEN_VGA2IN_RX
	// btmp = chbBBRxOut.checked == true ? 1 : 0;
	btmp = rgrBBLB.itemIndex == 2 ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x08] |= btmp;
	// LBEN_OPIN_RX
	// btmp = chbBBVga2.checked == true ? 1 : 0;
	btmp = rgrBBLB.itemIndex == 3 ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x08] |= btmp;
	// LBRFEN_RXFE[3:0]
	btmp = rgrRFLB.itemIndex;
	m_psD.cDataW[0x08] |= btmp;

	// ======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
	// RXOUTSW
	btmp = rgrRXOUTSW.itemIndex;
	btmp = btmp << 7;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[6]
	btmp = chbaSpiClkBuf[6] == true ? 1 : 0;
	btmp = btmp << 6;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[5]
	btmp = chbaSpiClkBuf[5] == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[4]
	btmp = chbaSpiClkBuf[4] == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[3]
	btmp = chbaSpiClkBuf[3] == true ? 1 : 0;
	btmp = btmp << 3;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[2]
	btmp = chbaSpiClkBuf[2] == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[1]
	btmp = chbaSpiClkBuf[1] == true ? 1 : 0;
	btmp = btmp << 1;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[0]
	btmp = chbaSpiClkBuf[0] == true ? 1 : 0;
	btmp = btmp << 0;
	m_psD.cDataW[0x09] |= btmp;

	// ======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
	// FDDTDD
	btmp = rgrFDDTDD.itemIndex;
	btmp = btmp << 1;
	m_psD.cDataW[0x0A] |= btmp;
	// TDDMOD
	btmp = rgrTDDMOD.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x0A] |= btmp;

	// ======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
	// PDXCOBUF
	btmp = chbPDXCOBUF.checked == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x0B] |= btmp;
	// SLFBXCOBUF
	btmp = chbSLFBXCOBUF.checked == true ? 1 : 0;
	btmp = btmp << 3;
	m_psD.cDataW[0x0B] |= btmp;
	// BYPXCOBUF
	btmp = chbBYPXCOBUF.checked == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x0B] |= btmp;
	// PD_DCOREF_LPFCAL
	btmp = chbPwrLpfCal.checked == true ? 0 : 1;
	btmp = btmp << 1;
	m_psD.cDataW[0x0B] |= btmp;
	// RFLBSW_EN
	btmp = chbPwrRfLbsw.checked == true ? 1 : 0;
	m_psD.cDataW[0x0B] |= btmp;

	// ======= register addr 0x0C =======
	// m_psD.cDataW[0x0C] = 0x00;

	// ======= register addr 0x0D =======
	// m_psD.cDataW[0x0D] = 0x00;

	// ======= register addr 0x0E =======
	// m_psD.cDataW[0x0E] = 0x00;

	// ======= register addr 0x0F =======
	// m_psD.cDataW[0x0F] = 0x00;

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
	case 0x03:
	case 0x04:
	case 0x05:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x05;
		break;

	case 0x20:
	case 0x21:
	case 0x06:
	case 0x07:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x06;
		break;

	case 0x0E:
	case 0x0F:
	case 0x10:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x07;
		break;

	case 0x09:
	case 0x0A:
	case 0x0D:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x08;
		break;

	case 0x11:
	case 0x22:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x09;
		break;

	case 0x23:
	case 0x24:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0A;
		break;

		// Test mode
	case 0x12:
	case 0x15:
	case 0x25:
	case 0x26:
	case 0x27:
		m_psD.iToW = 2;
		m_psD.iWInd[0] = 0x05;
		m_psD.iWInd[1] = 0x0B;
		m_psD.iWInd[1] = 0x0B;
		break;

	default:
		m_psD.iToW = 0;
	};
}

//---------------------------------------------------------------------------
void Top_Module::setDecode(int index)
{
	rgrDecode.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x00);
		pMainModule->CMAutoDownload(m_cMAddr);
	}
}

int Top_Module::getDecode()
{
	return rgrDecode.itemIndex;
}

// ---------------------------------------------------------------------------
void Top_Module::setDsmRst(int index)
{
	rgrDsmRst.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x01);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int Top_Module::getDsmRst()
{
	return rgrDsmRst.itemIndex;
}

// ---------------------------------------------------------------------------
void Top_Module::setPwrTopMods(bool state)
{
	chbPwrTopMods.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x02);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool Top_Module::getPwrTopMods()
{
	return chbPwrTopMods.checked;
}

// ---------------------------------------------------------------------------
void Top_Module::setPwrSoftTx(bool state)
{
	chbPwrSoftTx.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x03);
		pMainModule->CMAutoDownload(m_cMAddr);
	};

	// 1.a. When Soft Tx is Enabled it automatically enables Tx DSM SPI.
	chbaSpiClkBuf[0] = chbPwrSoftTx.checked;
	SpiClkBufUpdate();
}

bool Top_Module::getPwrSoftTx()
{
	return chbPwrSoftTx.checked;
}

// ---------------------------------------------------------------------------
void Top_Module::setPwrSoftRx(bool state)
{
	chbPwrSoftRx.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x04);
		pMainModule->CMAutoDownload(m_cMAddr);
	};

	// 1.b. When Soft Rx is Enabled it automatically enables Rx DSM SPI.
	chbaSpiClkBuf[2] = chbPwrSoftRx.checked;
	SpiClkBufUpdate();
}

bool Top_Module::getPwrSoftRx()
{
	return chbPwrSoftRx.checked;
}

// ---------------------------------------------------------------------------
void Top_Module::setSpiMode(int index)
{
	rgrSpiMode.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x05);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int Top_Module::getSpiMode()
{
	return rgrSpiMode.itemIndex;
}

// ---------------------------------------------------------------------------
void Top_Module::setLpfCalEnEnf(bool state)
{
	chbLpfCalEnEnf.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x06);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool Top_Module::getLpfCalEnEnf()
{
	return chbLpfCalEnEnf.checked;
}

// ---------------------------------------------------------------------------
void Top_Module::setLpfCalRst(bool state)
{
	chbLpfCalRst.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x07);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool Top_Module::getLpfCalRst()
{
	return chbLpfCalRst.checked;
}

// ---------------------------------------------------------------------------
void Top_Module::setRxTestModeEn(bool state)
{
	chbRxTestModeEn.checked = state;
	if (m_bAllowSend)
	{
		MakeData(0x09);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool Top_Module::getRxTestModeEn()
{
	return chbRxTestModeEn.checked;
}

// ---------------------------------------------------------------------------
void Top_Module::setBBLB(int index)
{
	rgrBBLB.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x0A);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int Top_Module::getBBLB()
{
	return rgrBBLB.itemIndex;
}

//---------------------------------------------------------------------------
void Top_Module::setRFLB(int index)
{
    rgrRFLB.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0D); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getRFLB()
{
    return rgrRFLB.itemIndex;
}

//---------------------------------------------------------------------------
void Top_Module::setLpfCalEn(bool state)
{
	chbLpfCalEn.checked = state;
	if(m_bAllowSend){ MakeData(0x0E); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getLpfCalEn()
{
	return chbLpfCalEn.checked;
}

//---------------------------------------------------------------------------
void Top_Module::setLpfCalCode(int index)
{
	rgrLpfCalCode.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0F); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getLpfCalCode()
{
	return rgrLpfCalCode.itemIndex;
}

//---------------------------------------------------------------------------
void Top_Module::setLpfCalBw(int index)
{
	rgrLpfCalBw.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x10); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getLpfCalBw()
{
	return rgrLpfCalBw.itemIndex;
}

//---------------------------------------------------------------------------
void Top_Module::setSpiClkBuf(int index, bool state)
{
	chbaSpiClkBuf[index] = state;
	if(m_bAllowSend){ MakeData(0x11); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getSpiClkBuf(int index)
{
	return chbaSpiClkBuf[index];
}
void Top_Module::SpiClkBufUpdate()
{
	if(m_bAllowSend){ MakeData(0x11); pMainModule->CMAutoDownload(m_cMAddr); };
}



//---------------------------------------------------------------------------
void Top_Module::setPwrLpfCal(bool state)
{
	chbPwrLpfCal.checked = state;
	if(m_bAllowSend){ MakeData(0x12); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getPwrLpfCal()
{
	return chbPwrLpfCal.checked;
}

//---------------------------------------------------------------------------
void Top_Module::setPwrRfLbsw(bool state)
{
	chbPwrRfLbsw.checked = state;
	if(m_bAllowSend){ MakeData(0x15); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getPwrRfLbsw()
{
	return chbPwrRfLbsw.checked;
}

//---------------------------------------------------------------------------
void Top_Module::setDCCalAddr(int index)
{
	cmbDCCalAddr.itemIndex = index;
	if(m_bAllowSend){ MakeData(0xF0); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getDCCalAddr()
{
	return cmbDCCalAddr.itemIndex;
}

//---------------------------------------------------------------------------
void Top_Module::setCLKSEL_LPFCAL(int index)
{
	rgrCLKSEL_LPFCAL.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x20); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getCLKSEL_LPFCAL()
{
	return rgrCLKSEL_LPFCAL.itemIndex;
}
//---------------------------------------------------------------------------

void Top_Module::setPD_CLKLPFCAL(bool state)
{
	chbPD_CLKLPFCAL.checked = state;
	if(m_bAllowSend){ MakeData(0x21); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getPD_CLKLPFCAL()
{
	return chbPD_CLKLPFCAL.checked;
}
//---------------------------------------------------------------------------

void Top_Module::setRXOUTSW(int index)
{
	rgrRXOUTSW.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x22); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getRXOUTSW()
{
	return rgrRXOUTSW.itemIndex;
}
//---------------------------------------------------------------------------

void Top_Module::setFDDTDD(int index)
{
	rgrFDDTDD.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x23); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getFDDTDD()
{
	return rgrFDDTDD.itemIndex;
}
//---------------------------------------------------------------------------

void Top_Module::setTDDMOD(int index)
{
	rgrTDDMOD.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x24); pMainModule->CMAutoDownload(m_cMAddr); };
}
int Top_Module::getTDDMOD()
{
	return rgrTDDMOD.itemIndex;
}
//---------------------------------------------------------------------------

void Top_Module::setPDXCOBUF(bool state)
{
	chbPDXCOBUF.checked = state;
	if(m_bAllowSend){ MakeData(0x25); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getPDXCOBUF()
{
	return chbPDXCOBUF.checked;
}
//---------------------------------------------------------------------------

void Top_Module::setSLFBXCOBUF(bool state)
{
	chbSLFBXCOBUF.checked = state;
	if(m_bAllowSend){ MakeData(0x26); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getSLFBXCOBUF()
{
	return chbSLFBXCOBUF.checked;
}
//---------------------------------------------------------------------------

void Top_Module::setBYPXCOBUF(bool state)
{
	chbBYPXCOBUF.checked = state;
	if(m_bAllowSend){ MakeData(0x27); pMainModule->CMAutoDownload(m_cMAddr); };
}
bool Top_Module::getBYPXCOBUF()
{
	return chbBYPXCOBUF.checked;
}
//---------------------------------------------------------------------------

void Top_Module::DCResetCalibration()
{
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
}
//---------------------------------------------------------------------------

void Top_Module::DCLoadValues(unsigned int value)
{
	rgrCalVal.itemIndex = value;
	EnableSPIClocksByMask(0x20);

	char btmp;

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

	m_DCClbrV[cmbDCCalAddr.itemIndex] = rgrCalVal.itemIndex;

	RestoreAllSPIClocks();
}
//---------------------------------------------------------------------------

void Top_Module::DCStartCalibration()
{
	EnableSPIClocksByMask(0x20);
	StartCalibration(cmbDCCalAddr.itemIndex);
	RestoreAllSPIClocks();
}


//----------------------------------------------------------------------------
// Make all data to write
//----------------------------------------------------------------------------
void Top_Module::MakeWriteAll()
{
	MakeData(0xFFFF);
	m_psD.iToW = m_psD.iLen;
	// m_psD.iToW = 0xD;
	m_psD.iWInd[0x0] = 0x00;
	m_psD.iWInd[0x1] = 0x01;
	m_psD.iWInd[0x2] = 0x02;
	m_psD.iWInd[0x3] = 0x03;
	m_psD.iWInd[0x4] = 0x04;
	m_psD.iWInd[0x5] = 0x05;
	m_psD.iWInd[0x6] = 0x06;
	m_psD.iWInd[0x7] = 0x07;
	m_psD.iWInd[0x8] = 0x08;
	m_psD.iWInd[0x9] = 0x09;
	m_psD.iWInd[0xA] = 0x0A;
	m_psD.iWInd[0xB] = 0x0B;
};

//----------------------------------------------------------------------------
// Save the chip configuration to the file
//----------------------------------------------------------------------------
bool Top_Module::ChipVsGui(ofstream &out, string Caption, bool bWrAll)
{
	bool bRez = true;
	bool btmp;
	char str[64] = "";
	char str1[64] = "";
	int itmp, itmp1;

	 out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out.width(32); out << "| Register"; out.width(2); out << "|";
	out.width(50); out << "Value from PC"; out.width(2); out << "|";
	out.width(50); out << "Value from Chip"; out.width(1); out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------" << endl;

	if(bWrAll)
	{
  	//DC_REGVAL[5:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_REGVAL[5:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
  	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    itmp = DC_REGVAL_r00_b50();
  	out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //RCCAL_LPFCAL[2:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RCCAL_LPFCAL[2:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = RCCAL_LPFCAL_r01_b75(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_LOCK[2:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_LOCK[2:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = DC_LOCK_r01_b42(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_CLBR_DONE
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_CLBR_DONE"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	if(DC_CLBR_DONE_r01_b11()) strcpy(str, "Calibration in Progress"); else strcpy(str, "Calibration Done");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_UD
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_UD"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  if(DC_UD_r01_b00()) strcpy(str, "Counting Up"); else strcpy(str, "Counting Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_CNTVAL[5:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_CNTVAL[5:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = DC_CNTVAL_r02_b50(); out << dec;// << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_START_CLBR
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_START_CLBR"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  if(DC_START_CLBR_r03_b55()) strcpy(str, "Start Active"); else strcpy(str, "Start Not Active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_LOAD
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_LOAD"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	if(DC_LOAD_r03_b44()) strcpy(str, "Load Active"); else strcpy(str, "Load Not Active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_SRESET
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_SRESET"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  if(DC_SRESET_r03_b33()) strcpy(str, "Reset Not Active"); else strcpy(str, "Reset Active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_ADDR[2:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_ADDR[2:0]"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = DC_ADDR_r03_b20(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //VER[3:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| VER[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = VER_r04_b74(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //REV[3:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| REV[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = REV_r04_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
  }


	 //DECODE
	if((rgrDecode.itemIndex != DECODE_r05_b77()) || bWrAll)
	{
	memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
	if(rgrDecode.itemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	memset(str, '\0', sizeof(str));
	  if(DECODE_r05_b77()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
	out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
	bRez = false;
	};

	//SRESET
	if((rgrDsmRst.itemIndex != SRESET_r05_b55()) || bWrAll)
	{
	memset(str, '\0', sizeof(str));
	out.width(32); out << "| SRESET"; out.width(2); out << "|";	out.width(40);
	if(rgrDsmRst.itemIndex == 1) strcpy(str, "Inactive"); else strcpy(str, "Reset State");
	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	memset(str, '\0', sizeof(str));
	if(SRESET_r05_b55()) strcpy(str, "Inactive"); else strcpy(str, "Reset State");
	out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
	bRez = false;
	};

  //EN
  if((chbPwrTopMods.checked != (bool)EN_r05_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrTopMods.checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(EN_r05_b44()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //STXEN
  if((chbPwrSoftTx.checked != (bool)STXEN_r05_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| STXEN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrSoftTx.checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(STXEN_r05_b33()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //SRXEN
  if((chbPwrSoftRx.checked != (bool)SRXEN_r05_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| SRXEN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrSoftRx.checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(SRXEN_r05_b22()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TFWMODEA
  if((rgrSpiMode.itemIndex != TFWMODE_r05_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| TFWMODEA"; out.width(2); out << "|";	out.width(40);
    if(rgrSpiMode.itemIndex == 1) strcpy(str, "4 Wire"); else strcpy(str, "3 Wire");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(TFWMODE_r05_b11()) strcpy(str, "4 Wire"); else strcpy(str, "3 Wire");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLKSEL_LPFCAL
  if((rgrCLKSEL_LPFCAL.itemIndex != CLKSEL_LPFCAL_r06_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CLKSEL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrCLKSEL_LPFCAL.sItems[rgrSpiMode.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	strcpy(str, rgrCLKSEL_LPFCAL.sItems[CLKSEL_LPFCAL_r06_b33()].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_CLKLPFCAL
  if((chbPD_CLKLPFCAL.checked != (bool)PD_CLKLPFCAL_r06_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| PD_CLKLPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chbPD_CLKLPFCAL.checked) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(PD_CLKLPFCAL_r06_b22()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ENF_EN_CAL_LPFCAL
  if((chbLpfCalEnEnf.checked != (bool)ENF_EN_CAL_LPFCAL_r06_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| ENF_EN_CAL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chbLpfCalEnEnf.checked) strcpy(str, "Enforce Mode Enabled"); else strcpy(str, "Enforce Mode Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(ENF_EN_CAL_LPFCAL_r06_b11()) strcpy(str, "Enforce Mode Enabled"); else strcpy(str, "Enforce Mode Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RST_CAL_LPFCAL
  if((chbLpfCalRst.checked != (bool)RST_CAL_LPFCAL_r06_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| RST_CAL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chbLpfCalRst.checked) strcpy(str, "Reset State"); else strcpy(str, "Normal State");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(RST_CAL_LPFCAL_r06_b00()) strcpy(str, "Normal State"); else strcpy(str, "Reset State");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN_CAL_LPFCAL
  if((chbLpfCalEn.checked != (bool)EN_CAL_LPFCAL_r07_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| EN_CAL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chbLpfCalEn.checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(EN_CAL_LPFCAL_r07_b77()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FORCE_CODE_CAL_LPFCAL[2:0]
  if((rgrLpfCalCode.itemIndex != FORCE_CODE_CAL_LPFCAL_r07_b64()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| FORCE_CODE_CAL_LPFCAL[2:0]"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrLpfCalCode.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = FORCE_CODE_CAL_LPFCAL_r07_b64(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BWC_LPFCAL[3:0]
  if((rgrLpfCalBw.itemIndex != BWC_LPFCAL_r07_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BWC_LPFCAL[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrLpfCalBw.sItems[rgrLpfCalBw.itemIndex].c_str());
    out << str;	out.width(10); out << "MHz"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = BWC_LPFCAL_r07_b30();
    strcpy(str, rgrLpfCalBw.sItems[itmp].c_str());
    out << str;	out.width(10); out << "MHz"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BBBYP_RX
  if((chbRxTestModeEn.checked != BBBYP_r08_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BBBYP_RX"; out.width(2); out << "|";	out.width(40);
    if(chbRxTestModeEn.checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(BBBYP_r08_b77()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBEN_LPFIN_RX
  if(((rgrBBLB.itemIndex != 1) && LBEN_LPFIN_r08_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBEN_LPFIN_RX"; out.width(2); out << "|";	out.width(40);
    if(rgrBBLB.itemIndex == 1) strcpy(str, "loopbbbxx connected to the LPF input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LBEN_LPFIN_r08_b66()) strcpy(str, "loopbbbxx connected to the LPF input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBEN_VGA2IN_RX
  if(((rgrBBLB.itemIndex != 2) && LBEN_VGA2IN_r08_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBEN_VGA2IN_RX"; out.width(2); out << "|";	out.width(40);
    if(rgrBBLB.itemIndex == 2) strcpy(str, "loopbbbxx connected to the VGA2 input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LBEN_VGA2IN_r08_b55()) strcpy(str, "loopbbbxx connected to the VGA2 input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBEN_OPIN_RX
  if(((rgrBBLB.itemIndex != 3) && LBEN_OPIN_r08_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBEN_OPIN_RX"; out.width(2); out << "|";	out.width(40);
    if(rgrBBLB.itemIndex == 3) strcpy(str, "loopbbbxx connected to the RX output pins"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LBEN_OPIN_r08_b44()) strcpy(str, "loopbbbxx connected to the RX output pins"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBRFEN_RXFE[3:0]
  if((rgrRFLB.itemIndex != LBRFEN_r08_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBRFEN_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrRFLB.sItems[rgrRFLB.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
    itmp = LBRFEN_r08_b30();
  	if(itmp > 3) strcpy(str, "WRONG DATA!!!"); else strcpy(str, rgrRFLB.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RXOUTSW
  if((rgrRXOUTSW.itemIndex != RXOUTSW_r09_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CLKSEL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrRXOUTSW.sItems[rgrRXOUTSW.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	strcpy(str, rgrRXOUTSW.sItems[RXOUTSW_r09_b77()].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[6]
  if((chbaSpiClkBuf[6] != (bool)PLLCLKOUT_r09_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[6]"; out.width(2); out << "|";	out.width(40);
    if(chbaSpiClkBuf[6]) strcpy(str, "PLLCLKOUT Enabled"); else strcpy(str, "PLLCLKOUT Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(PLLCLKOUT_r09_b66()) strcpy(str, "PLLCLKOUT Enabled"); else strcpy(str, "PLLCLKOUT Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[5]
  if((chbaSpiClkBuf[5] != (bool)LPF_CAL_r09_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[5]"; out.width(2); out << "|";	out.width(40);
    if(chbaSpiClkBuf[6]) strcpy(str, "LPF CALCORE Clk Enabled"); else strcpy(str, "LPF CALCORE Clk Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LPF_CAL_r09_b55()) strcpy(str, "LPF CALCORE Clk Enabled"); else strcpy(str, "LPF CALCORE Clk Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[4]
  if((chbaSpiClkBuf[4] != (bool)Rx_VGA2_DCCAL_r09_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[4]"; out.width(2); out << "|";	out.width(40);
    if(chbaSpiClkBuf[4]) strcpy(str, "Rx VGA2 DCCLK Enabled"); else strcpy(str, "Rx VGA2 DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Rx_VGA2_DCCAL_r09_b44()) strcpy(str, "Rx VGA2 DCCLK Enabled"); else strcpy(str, "Rx VGA2 DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[3]
  if((chbaSpiClkBuf[3] != (bool)Rx_LPF_DCCAL_r09_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[3]"; out.width(2); out << "|";	out.width(40);
    if(chbaSpiClkBuf[3]) strcpy(str, "Rx LPF DCCLK Enabled"); else strcpy(str, "Rx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Rx_LPF_DCCAL_r09_b33()) strcpy(str, "Rx LPF DCCLK Enabled"); else strcpy(str, "Rx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[2]
  if((chbaSpiClkBuf[2] != (bool)Rx_DSM_SPI_r09_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[2]"; out.width(2); out << "|";	out.width(40);
    if(chbaSpiClkBuf[2]) strcpy(str, "Rx DSM SPI Enabled"); else strcpy(str, "Rx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Rx_DSM_SPI_r09_b22()) strcpy(str, "Rx DSM SPI Enabled"); else strcpy(str, "Rx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[1]
  if((chbaSpiClkBuf[1] != (bool)Tx_LPF_SPI_DCCAL_r09_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[1]"; out.width(2); out << "|";	out.width(40);
    if(chbaSpiClkBuf[1]) strcpy(str, "Tx LPF DCCLK Enabled"); else strcpy(str, "Tx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Tx_LPF_SPI_DCCAL_r09_b11()) strcpy(str, "Tx LPF DCCLK Enabled"); else strcpy(str, "Tx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[0]
  if((chbaSpiClkBuf[0] != (bool)Tx_DSM_SPI_r09_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[0]"; out.width(2); out << "|";	out.width(40);
    if(chbaSpiClkBuf[0]) strcpy(str, "Tx DSM SPI Enabled"); else strcpy(str, "Tx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Tx_DSM_SPI_r09_b00()) strcpy(str, "Tx DSM SPI Enabled"); else strcpy(str, "Tx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FDDTDD
  if((rgrFDDTDD.itemIndex != FDDTDD_r0A_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| FDDTDD"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrFDDTDD.sItems[rgrFDDTDD.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
    itmp = FDDTDD_r0A_b11();
  	strcpy(str, rgrFDDTDD.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TDDMOD
  if((rgrTDDMOD.itemIndex != TDDMOD_r0A_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| TDDMOD"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrTDDMOD.sItems[rgrTDDMOD.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
    itmp = TDDMOD_r0A_b00();
  	strcpy(str, rgrTDDMOD.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  if((!bRez) || bWrAll)
  {
    out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |" << endl;
  };

  //PDXCOBUF
  if((chbPDXCOBUF.checked != (bool)PDXCOBUF_r0B_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PDXCOBUF"; out.width(2); out << "|";	out.width(40);
    if(chbPDXCOBUF.checked) strcpy(str, "XCO buffer powered down"); else strcpy(str, "XCO buffer powered up");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PDXCOBUF_r0B_b44()) strcpy(str, "XCO buffer powered down"); else strcpy(str, "XCO buffer powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //SLFBXCOBUF
  if((chbSLFBXCOBUF.checked != (bool)SLFBXCOBUF_r0B_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| SLFBXCOBUF"; out.width(2); out << "|";	out.width(40);
    if(chbSLFBXCOBUF.checked) strcpy(str, "XCO buffer self bias enabled"); else strcpy(str, "XCO buffer self bias disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(SLFBXCOBUF_r0B_b33()) strcpy(str, "XCO buffer self bias enabled"); else strcpy(str, "XCO buffer self bias disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BYPXCOBUF
  if((chbBYPXCOBUF.checked != (bool)BYPXCOBUF_r0B_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| BYPXCOBUF"; out.width(2); out << "|";	out.width(40);
    if(chbBYPXCOBUF.checked) strcpy(str, "XCO buffer bypassed"); else strcpy(str, "XCO buffer active");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(BYPXCOBUF_r0B_b22()) strcpy(str, "XCO buffer bypassed"); else strcpy(str, "XCO buffer active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD[1]
  if((chbPwrLpfCal.checked == (bool)PD_DCOREF_LPFCAL_r0B_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD[1]"; out.width(2); out << "|";	out.width(40);
    if(chbPwrLpfCal.checked) strcpy(str, "PD_DCOREF_LPFCAL powered up"); else strcpy(str, "PD_DCOREF_LPFCAL powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_DCOREF_LPFCAL_r0B_b11()) strcpy(str, "PD_DCOREF_LPFCAL powered down"); else strcpy(str, "PD_DCOREF_LPFCAL powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD[0]
  if((chbPwrRfLbsw.checked != (bool)RF_LBSW_PD_r0B_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD[0]"; out.width(2); out << "|";	out.width(40);
    if(chbPwrRfLbsw.checked) strcpy(str, "RF loop back switch powered up"); else strcpy(str, "RF loop back switch powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(RF_LBSW_PD_r0B_b00()) strcpy(str, "RF loop back switch powered up"); else strcpy(str, "RF loop back switch powered down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  if(bRez && (!bWrAll))
  {
  	out.width(136); out << "| CHIP Configuration EQUALS GUI Configuration"; out.width(2); out << "|";
	  out << endl;
  };
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out << "" << endl;
	out << "" << endl;

  return bRez;
};

/**
    Writes register map to the file. According to the customer wish.
    @param out stream for output
*/
void Top_Module::MakeRegisterFile(ofstream &out)
{
  int itmp;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


	//DC_REGVAL[5:0]
  out.width(24); out << left; out << "REG 0x00 MASK 05 : 00  =";
  itmp = DC_REGVAL_r00_b50();
  out.width(6); out << right; out << itmp;
  out << "  DC_REGVAL"; out << endl;

	//RCCAL_LPFCAL[2:0]
  out.width(24); out << left; out << "REG 0x01 MASK 07 : 05  =";
  itmp = RCCAL_LPFCAL_r01_b75();
  out.width(6); out << right; out << itmp;
  out << "  RCCAL_LPFCAL"; out << endl;

  //DC_LOCK[2:0]
  out.width(24); out << left; out << "REG 0x01 MASK 04 : 02  =";
  itmp = DC_LOCK_r01_b42();
  out.width(6); out << right; out << itmp;
  out << "  DC_LOCK"; out << endl;

  //DC_CLBR_DONE
  out.width(24); out << left; out << "REG 0x01 MASK 01 : 01  =";
  itmp = DC_CLBR_DONE_r01_b11();
  out.width(6); out << right; out << itmp;
  out << "  DC_CLBR_DONE"; out << endl;

  //DC_UD
  out.width(24); out << left; out << "REG 0x01 MASK 00 : 00  =";
  itmp = DC_UD_r01_b00();
  out.width(6); out << right; out << itmp;
  out << "  DC_UD"; out << endl;

  //DC_CNTVAL[5:0]
  out.width(24); out << left; out << "REG 0x02 MASK 05 : 00  =";
  itmp = DC_CNTVAL_r02_b50();
  out.width(6); out << right; out << itmp;
  out << "  DC_CNTVAL"; out << endl;

  //DC_START_CLBR
  out.width(24); out << left; out << "REG 0x03 MASK 05 : 05  =";
  itmp = DC_START_CLBR_r03_b55();
  out.width(6); out << right; out << itmp;
  out << "  DC_START_CLBR"; out << endl;

  //DC_LOAD
  out.width(24); out << left; out << "REG 0x03 MASK 04 : 04  =";
  itmp = DC_LOAD_r03_b44();
  out.width(6); out << right; out << itmp;
  out << "  DC_LOAD"; out << endl;

  //DC_SRESET
  out.width(24); out << left; out << "REG 0x03 MASK 03 : 03  =";
  itmp = DC_SRESET_r03_b33();
  out.width(6); out << right; out << itmp;
  out << "  DC_SRESET"; out << endl;

  //DC_ADDR[2:0]
  out.width(24); out << left; out << "REG 0x03 MASK 02 : 00  =";
  itmp = DC_ADDR_r03_b20();
  out.width(6); out << right; out << itmp;
  out << "  DC_ADDR"; out << endl;

  //VER[3:0]
  out.width(24); out << left; out << "REG 0x04 MASK 07 : 04  =";
  itmp = VER_r04_b74();
  out.width(6); out << right; out << itmp;
  out << "  VER"; out << endl;

  //REV[3:0]
  out.width(24); out << left; out << "REG 0x04 MASK 03 : 00  =";
  itmp = REV_r04_b30();
  out.width(6); out << right; out << itmp;
  out << "  REV"; out << endl;

  //DECODE
  out.width(24); out << left; out << "REG 0x05 MASK 07 : 07  =";
  itmp = DECODE_r05_b77();
  out.width(6); out << right; out << itmp;
  out << "  DECODE"; out << endl;

  //SRESET
  out.width(24); out << left; out << "REG 0x05 MASK 05 : 05  =";
  itmp = SRESET_r05_b55();
  out.width(6); out << right; out << itmp;
  out << "  SRESET"; out << endl;

  //EN
  out.width(24); out << left; out << "REG 0x05 MASK 04 : 04  =";
  itmp = EN_r05_b44();
  out.width(6); out << right; out << itmp;
  out << "  EN"; out << endl;

  //STXEN
  out.width(24); out << left; out << "REG 0x05 MASK 03 : 03  =";
  itmp = STXEN_r05_b33();
  out.width(6); out << right; out << itmp;
  out << "  STXEN"; out << endl;

  //SRXEN
  out.width(24); out << left; out << "REG 0x05 MASK 02 : 02  =";
  itmp = SRXEN_r05_b22();
  out.width(6); out << right; out << itmp;
  out << "  SRXEN"; out << endl;

  //TFWMODE
  out.width(24); out << left; out << "REG 0x05 MASK 01 : 01  =";
  itmp = TFWMODE_r05_b11();
  out.width(6); out << right; out << itmp;
  out << "  TFWMODE"; out << endl;

  //CLKSEL_LPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 03 : 03  =";
  itmp = CLKSEL_LPFCAL_r06_b33();
  out.width(6); out << right; out << itmp;
  out << "  CLKSEL_LPFCAL"; out << endl;

  //PD_CLKLPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 02 : 02  =";
  itmp = PD_CLKLPFCAL_r06_b22();
  out.width(6); out << right; out << itmp;
  out << "  PD_CLKLPFCAL"; out << endl;

  //ENF_EN_CAL_LPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 01 : 01  =";
  itmp = ENF_EN_CAL_LPFCAL_r06_b11();
  out.width(6); out << right; out << itmp;
  out << "  ENF_EN_CAL_LPFCAL"; out << endl;

  //RST_CAL_LPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 00 : 00  =";
  itmp = RST_CAL_LPFCAL_r06_b00();
  out.width(6); out << right; out << itmp;
  out << "  RST_CAL_LPFCAL"; out << endl;

  //EN_CAL_LPFCAL
  out.width(24); out << left; out << "REG 0x07 MASK 07 : 07  =";
  itmp = EN_CAL_LPFCAL_r07_b77();
  out.width(6); out << right; out << itmp;
  out << "  EN_CAL_LPFCAL"; out << endl;

  //FORCE_CODE_CAL_LPFCAL[2:0]
  out.width(24); out << left; out << "REG 0x07 MASK 06 : 04  =";
  itmp = FORCE_CODE_CAL_LPFCAL_r07_b64();
  out.width(6); out << right; out << itmp;
  out << "  FORCE_CODE_CAL_LPFCAL"; out << endl;

  //BWC_LPFCAL[3:0]
  out.width(24); out << left; out << "REG 0x07 MASK 03 : 00  =";
  itmp = BWC_LPFCAL_r07_b30();
  out.width(6); out << right; out << itmp;
  out << "  BWC_LPFCAL"; out << endl;

  //BBBYP_RX
  out.width(24); out << left; out << "REG 0x08 MASK 07 : 07  =";
  itmp = BBBYP_r08_b77();
  out.width(6); out << right; out << itmp;
  out << "  BBBYP_RX"; out << endl;

  //LBEN_LPFIN_RX
  out.width(24); out << left; out << "REG 0x08 MASK 06 : 06  =";
  itmp = LBEN_LPFIN_r08_b66();
  out.width(6); out << right; out << itmp;
  out << "  LBEN_LPFIN_RX"; out << endl;

  //LBEN_VGA2IN_RX
  out.width(24); out << left; out << "REG 0x08 MASK 05 : 05  =";
  itmp = LBEN_VGA2IN_r08_b55();
  out.width(6); out << right; out << itmp;
  out << "  LBEN_VGA2IN_RX"; out << endl;

  //LBEN_OPIN_RX
  out.width(24); out << left; out << "REG 0x08 MASK 04 : 04  =";
  itmp = LBEN_OPIN_r08_b44();
  out.width(6); out << right; out << itmp;
  out << "  LBEN_OPIN_RX"; out << endl;

  //LBRFEN[3:0]
  out.width(24); out << left; out << "REG 0x08 MASK 03 : 00  =";
  itmp = LBRFEN_r08_b30();
  out.width(6); out << right; out << itmp;
  out << "  LBRFEN"; out << endl;

  //RXOUTSW
  out.width(24); out << left; out << "REG 0x09 MASK 07 : 07  =";
  itmp = RXOUTSW_r09_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXOUTSW"; out << endl;

  //CLK_EN[6]
  out.width(24); out << left; out << "REG 0x09 MASK 06 : 06  =";
  itmp = PLLCLKOUT_r09_b66();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[6]"; out << endl;

  //CLK_EN[5]
  out.width(24); out << left; out << "REG 0x09 MASK 05 : 05  =";
  itmp = LPF_CAL_r09_b55();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[5]"; out << endl;

  //CLK_EN[4]
  out.width(24); out << left; out << "REG 0x09 MASK 04 : 04  =";
  itmp = Rx_VGA2_DCCAL_r09_b44();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[4]"; out << endl;

  //CLK_EN[3]
  out.width(24); out << left; out << "REG 0x09 MASK 03 : 03  =";
  itmp = Rx_LPF_DCCAL_r09_b33();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[3]"; out << endl;

  //CLK_EN[2]
  out.width(24); out << left; out << "REG 0x09 MASK 02 : 02  =";
  itmp = Rx_DSM_SPI_r09_b22();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[2]"; out << endl;

  //CLK_EN[1]
  out.width(24); out << left; out << "REG 0x09 MASK 01 : 01  =";
  itmp = Tx_LPF_SPI_DCCAL_r09_b11();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[1]"; out << endl;

  //CLK_EN[0]
  out.width(24); out << left; out << "REG 0x09 MASK 00 : 00  =";
  itmp = Tx_DSM_SPI_r09_b00();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[0]"; out << endl;

  //FDDTDD
  out.width(24); out << left; out << "REG 0x0A MASK 01 : 01  =";
  itmp = FDDTDD_r0A_b11();
  out.width(6); out << right; out << itmp;
  out << "  FDDTDD"; out << endl;

  //TDDMOD
  out.width(24); out << left; out << "REG 0x0A MASK 00 : 00  =";
  itmp = TDDMOD_r0A_b00();
  out.width(6); out << right; out << itmp;
  out << "  TDDMOD"; out << endl;

  //PDXCOBUF
  out.width(24); out << left; out << "REG 0x0B MASK 04 : 04  =";
  itmp = PDXCOBUF_r0B_b44();
  out.width(6); out << right; out << itmp;
  out << "  PDXCOBUF"; out << endl;

  //SLFBXCOBUF
  out.width(24); out << left; out << "REG 0x0B MASK 03 : 03  =";
  itmp = SLFBXCOBUF_r0B_b33();
  out.width(6); out << right; out << itmp;
  out << "  SLFBXCOBUF"; out << endl;

  //BYPXCOBUF
  out.width(24); out << left; out << "REG 0x0B MASK 02 : 02  =";
  itmp = BYPXCOBUF_r0B_b22();
  out.width(6); out << right; out << itmp;
  out << "  BYPXCOBUF"; out << endl;

  //PD_DCOREF_LPFCAL
  out.width(24); out << left; out << "REG 0x0B MASK 01 : 01  =";
  itmp = PD_DCOREF_LPFCAL_r0B_b11();
  out.width(6); out << right; out << itmp;
  out << "  PD_DCOREF_LPFCAL"; out << endl;

  //RF_LBSW_PD
  out.width(24); out << left; out << "REG 0x0B MASK 00 : 00  =";
  itmp = RF_LBSW_PD_r0B_b00();
  out.width(6); out << right; out << itmp;
  out << "  RF_LBSW_PD"; out << endl;
};

/**
    Writes Register - Value format to the file
    @param out stream for output
*/
void Top_Module::MakeRVFFile(ofstream &out)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//

  //0x00 - Read Only

  //0x01 - Read Only

  //0x02
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0x3F);
  out << iRval; out << endl;

  //0x03
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0x3F);
  out << iRval; out << endl;

  //0x04 - Read Only

  //0x05
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xBE);
  out << iRval; out << endl;

  //0x06
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x0F);
  out << iRval; out << endl;

  //0x07
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << iRval; out << endl;

  //0x08
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << iRval; out << endl;

  //0x09
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xFF);
  out << iRval; out << endl;

  //0x0A
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x03);
  out << iRval; out << endl;

  //0x0B
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0x1F);
  out << iRval; out << endl;

};

/**
    Saves chip configuration using FRIF format
    @param FRIF_SPI_A frif parameter
*/
void Top_Module::MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  out << "echo \"Now programming the Lime Top modules\"" << endl << endl;

  //0x00 - Read Only

  //0x01 - Read Only

  //0x02
  //out << "# Register(s): DC_CNTVAL[5:0]" << endl;
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x03
  //out << "# Register(s): DC_START_CLBR, DC_ADDR, DC_LOAD, DC_SRESET, DC_ADDR[2:0]" << endl;
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x04 - Read Only

  //0x05
  //out << "# Register(s): DECODE, SRESET, EN, STXEN, SRXEN, TFWMODE" << endl;
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xBE);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x06
  //out << "# Register(s): CLKSEL_LPFCAL, PD_CLKLPFCAL, ENF_EN_CAL_LPFCAL, RST_CAL_LPFCAL" << endl;
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x0F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x07
  //out << "# Register(s): EN_CAL_LPFCAL, FORCE_CODE_CAL_LPFCAL[2:0], BWC_LPFCAL[3:0]" << endl;
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x08
  //out << "# Register(s): BBBYP, LBEN_LPFIN, LBEN_VGA2IN, LBEN_OPIN, LBRFEN[3:0]" << endl;
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x09
  //out << "# Register(s): RXOUTSW, CLK_EN[6:0]" << endl;
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0A
  //out << "# Register(s): FDDTDD, TDDMOD" << endl;
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x03);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0B
  //out << "# Register(s): PDXCOBUF, SLFBXCOBUF, BYPXCOBUF, PD[1:0]" << endl;
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0x1F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  out << endl << "echo \"TopSPI programming complete\"" << endl << endl;
};

/**
    Sets GUI under data from chip
*/
bool Top_Module::SetGUIUnderReadback()
{
  int itmp;
	bool bRez = true;

	m_bAllowSend = false;

	// DC_REGVAL[5:0]
	itmp = DC_REGVAL_r00_b50();
	lblDC_REGVAL = itmp;

	// RCCAL_LPFCAL[2:0]
	itmp = RCCAL_LPFCAL_r01_b75();
	lblRCCAL_LPFCAL = itmp;

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
	rgrCalVal.itemIndex = itmp;

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

	// VER[3:0]
	itmp = VER_r04_b74();

	// REV[3:0]
	itmp = REV_r04_b30();

	// DECODE
	itmp = DECODE_r05_b77();
	rgrDecode.itemIndex = itmp;

	// SRESET
	itmp = SRESET_r05_b55();
	rgrDsmRst.itemIndex = itmp;

	// EN
	itmp = EN_r05_b44();
	chbPwrTopMods.checked = itmp;

	// STXEN
	itmp = STXEN_r05_b33();
	chbPwrSoftTx.checked = itmp;

	// SRXEN
	itmp = SRXEN_r05_b22();
	chbPwrSoftRx.checked = itmp;

	// TFWMODEA
	itmp = TFWMODE_r05_b11();
	rgrSpiMode.itemIndex = itmp;

	// CLKSEL_LPFCAL
	itmp = CLKSEL_LPFCAL_r06_b33();
	rgrCLKSEL_LPFCAL.itemIndex = itmp;

	// PD_CLKLPFCAL
	itmp = PD_CLKLPFCAL_r06_b22();
	chbPD_CLKLPFCAL.checked = itmp;

	// ENF_EN_CAL_LPFCAL
	itmp = ENF_EN_CAL_LPFCAL_r06_b11();
	chbLpfCalEnEnf.checked = itmp;

	// RST_CAL_LPFCAL
	itmp = RST_CAL_LPFCAL_r06_b00();
	chbLpfCalRst.checked = itmp;
	// chbLpfCalRst.checked = !chbLpfCalRst.checked;

	// EN_CAL_LPFCAL
	itmp = EN_CAL_LPFCAL_r07_b77();
	chbLpfCalEn.checked = itmp;

	// FORCE_CODE_CAL_LPFCAL[2:0]
	itmp = FORCE_CODE_CAL_LPFCAL_r07_b64();
	rgrLpfCalCode.itemIndex = itmp;

	// BWC_LPFCAL[3:0]
	itmp = BWC_LPFCAL_r07_b30();
	rgrLpfCalBw.itemIndex = itmp;

	// BBBYP_RX
	itmp = BBBYP_r08_b77();
	chbRxTestModeEn.checked = itmp;

	/*
	 //LBEN_LPFIN_RX
	 itmp = m_psD.cDataR[0x08] & 0x40; itmp = itmp >> 6;
	 rgrBBLB.itemIndex = itmp;

	 //LBEN_VGA2IN_RX
	 itmp = m_psD.cDataR[0x08] & 0x20; itmp = itmp >> 5;
	 rgrBBLB.itemIndex = itmp;

	 //LBEN_OPIN_RX
	 itmp = m_psD.cDataR[0x08] & 0x10; itmp = itmp >> 4;
	 rgrBBLB.itemIndex = itmp;
	 */

	// LBEN_LPFIN_RX
	// LBEN_VGA2IN_RX
	// LBEN_OPIN_RX
	switch (LBEN_r08_b64())
	{
	case 0x00:
		itmp = 0x00;
		break;
	case 0x01:
		itmp = 0x03;
		break;
	case 0x02:
		itmp = 0x02;
		break;
	case 0x04:
		itmp = 0x01;
		break;
	default:
		itmp = 0;
		bRez = false;
	};
	rgrBBLB.itemIndex = itmp;

	// LBRFEN[3:0]
	itmp = LBRFEN_r08_b30();
	if (itmp > 3)
	{
		itmp = 3;
		bRez = false;
	}
	rgrRFLB.itemIndex = itmp;

	// RXOUTSW
	itmp = RXOUTSW_r09_b77();
	rgrRXOUTSW.itemIndex = itmp;

	// SPI_CLK_EN [6]
	itmp = PLLCLKOUT_r09_b66();
	chbaSpiClkBuf[6] = itmp;

	// SPI_CLK_EN [5]
	itmp = LPF_CAL_r09_b55();
	chbaSpiClkBuf[5] = itmp;

	// SPI_CLK_EN [4]
	itmp = Rx_VGA2_DCCAL_r09_b44();
	chbaSpiClkBuf[4] = itmp;

	// SPI_CLK_EN [3]
	itmp = Rx_LPF_DCCAL_r09_b33();
	chbaSpiClkBuf[3] = itmp;

	// SPI_CLK_EN [2]
	itmp = Rx_DSM_SPI_r09_b22();
	chbaSpiClkBuf[2] = itmp;

	// SPI_CLK_EN [1]
	itmp = Tx_LPF_SPI_DCCAL_r09_b11();
	chbaSpiClkBuf[1] = itmp;

	// SPI_CLK_EN [0]
	itmp = Tx_DSM_SPI_r09_b00();
	chbaSpiClkBuf[0] = itmp;

	// FDDTDD
	itmp = FDDTDD_r0A_b11();
	rgrFDDTDD.itemIndex = itmp;

	// TDDMOD
	itmp = TDDMOD_r0A_b00();
	rgrTDDMOD.itemIndex = itmp;

	// PDXCOBUF
	itmp = PDXCOBUF_r0B_b44();
	chbPDXCOBUF.checked = itmp;

	// SLFBXCOBUF
	itmp = SLFBXCOBUF_r0B_b33();
	chbSLFBXCOBUF.checked = itmp;

	// BYPXCOBUF
	itmp = BYPXCOBUF_r0B_b22();
	chbBYPXCOBUF.checked = itmp;

	// PD[1]
	itmp = PD_DCOREF_LPFCAL_r0B_b11();
	chbPwrLpfCal.checked = itmp;
	chbPwrLpfCal.checked = !chbPwrLpfCal.checked;

	// PD[0]
	itmp = RF_LBSW_PD_r0B_b00();
	chbPwrRfLbsw.checked = itmp;

	m_bAllowSend = true;
	return bRez;
};

void Top_Module::DCGetCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue)
{
	char rez = pMainModule->getSerPort()->SPI_Read_OneByte(0x00);
	calibVal = rez;

	rez = pMainModule->getSerPort()->SPI_Read_OneByte(0x01);

	lockPattern = (rez >> 2) & 0x07;
	calibStatus = (rez >> 1) & 0x01;
	compValue = rez & 0x01;
}
//---------------------------------------------------------------------------
void Top_Module::ReadRCCALValues(int &rccal)
{
	char rez = pMainModule->getSerPort()->SPI_Read_OneByte(0x01);
	rez = rez >> 5;
	lblRCCAL_LPFCAL = rez & 0x07;
	rccal = rez & 0x07;
}

/**
    Saves configuration to ini file
    @param pini pointer to ini file parser
*/
void Top_Module::SaveConf(ini_t *pini)
{
	char Sect[80];
	sprintf(Sect, "%i", (int)m_cMAddr);

	pini->Create(Sect);

	pini->Set("cmbDCCalAddr", cmbDCCalAddr.itemIndex);
	pini->Set("cmbCalVal", rgrCalVal.itemIndex);
	pini->Set("LPF_dco_CAL", GetCalVal(0x00));

	pini->Set("rgrDecode", rgrDecode.itemIndex);
	pini->Set("rgrDsmRst", rgrDsmRst.itemIndex);
	pini->Set("chbPwrTopMods", chbPwrTopMods.checked);
	pini->Set("chbPwrSoftTx", chbPwrSoftTx.checked);
	pini->Set("chbPwrSoftRx", chbPwrSoftRx.checked);
	pini->Set("rgrSpiMode", rgrSpiMode.itemIndex);

	pini->Set("rgrCLKSEL_LPFCAL", rgrCLKSEL_LPFCAL.itemIndex);
	pini->Set("chbPD_CLKLPFCAL", chbPD_CLKLPFCAL.checked);
	pini->Set("chkLpfCalEnEnf", chbLpfCalEnEnf.checked);
	pini->Set("chkLpfCalRst", chbLpfCalRst.checked);

	pini->Set("chkLpfCalEn", chbLpfCalEn.checked);
	pini->Set("cmbLpfCalCode", rgrLpfCalCode.itemIndex);
	pini->Set("cmbLpfCalBw", rgrLpfCalBw.itemIndex);

	pini->Set("chbRxTestModeEn", chbRxTestModeEn.checked);
	pini->Set("rgrBBLB", rgrBBLB.itemIndex);
	pini->Set("rgrRFLB", rgrRFLB.itemIndex);

	pini->Set("rgrRXOUTSW", rgrRXOUTSW.itemIndex);
	pini->Set("chbSpiClkBuf_0", chbaSpiClkBuf[0]);
	pini->Set("chbSpiClkBuf_1", chbaSpiClkBuf[1]);
	pini->Set("chbSpiClkBuf_2", chbaSpiClkBuf[2]);
	pini->Set("chbSpiClkBuf_3", chbaSpiClkBuf[3]);
	pini->Set("chbSpiClkBuf_4", chbaSpiClkBuf[4]);
	pini->Set("chbSpiClkBuf_5", chbaSpiClkBuf[5]);
	pini->Set("chbSpiClkBuf_6", chbaSpiClkBuf[6]);

	pini->Set("rgrFDDTDD", rgrFDDTDD.itemIndex);
	pini->Set("rgrTDDMOD", rgrTDDMOD.itemIndex);

	pini->Set("chbPDXCOBUF", chbPDXCOBUF.checked);
	pini->Set("chbSLFBXCOBUF", chbSLFBXCOBUF.checked);
	pini->Set("chbBYPXCOBUF", chbBYPXCOBUF.checked);
	pini->Set("chbPwrLpfCal", chbPwrLpfCal.checked);
	pini->Set("chbPwrRfLbsw", chbPwrRfLbsw.checked);
};

/**
    Reads configuration from ini file
    @param pini pointer to ini file parser
*/
void Top_Module::ReadConf(ini_t *pini)
{
	char Sect[80];
	sprintf(Sect, "%i", (int)m_cMAddr);

	pini->Select(Sect);

	m_bAllowSend = false;

	cmbDCCalAddr.itemIndex = pini->Get("cmbDCCalAddr", 0);
	rgrCalVal.itemIndex = pini->Get("cmbCalVal", 31);
	m_DCClbrV[0] = pini->Get("LPF_dco_CAL", 31);

	rgrDecode.itemIndex = pini->Get("rgrDecode", 0);
	rgrDsmRst.itemIndex = pini->Get("rgrDsmRst", 1);
	chbPwrTopMods.checked = pini->Get("chbPwrTopMods", 1);
	chbPwrSoftTx.checked = pini->Get("chbPwrSoftTx", 0);
	chbPwrSoftRx.checked = pini->Get("chbPwrSoftRx", 0);
	rgrSpiMode.itemIndex = pini->Get("rgrSpiMode", 1);

	rgrCLKSEL_LPFCAL.itemIndex = pini->Get("rgrCLKSEL_LPFCAL", 1);
	chbPD_CLKLPFCAL.checked = pini->Get("chbPD_CLKLPFCAL", 1);
	chbLpfCalEnEnf.checked = pini->Get("chkLpfCalEnEnf", 0);
	chbLpfCalRst.checked = pini->Get("chkLpfCalRst", 1);

	chbLpfCalEn.checked = pini->Get("chkLpfCalEn", 0);
	rgrLpfCalCode.itemIndex = pini->Get("cmbLpfCalCode", 0);
	rgrLpfCalBw.itemIndex = pini->Get("cmbLpfCalBw", 0);

	chbRxTestModeEn.checked = pini->Get("chbRxTestModeEn", 0);
	rgrBBLB.itemIndex = pini->Get("rgrBBLB", 0);
	rgrRFLB.itemIndex = pini->Get("rgrRFLB", 0);

	rgrRXOUTSW.itemIndex = pini->Get("rgrRXOUTSW", 0);
	chbaSpiClkBuf[0] = pini->Get("chbSpiClkBuf_0", 0);
	chbaSpiClkBuf[1] = pini->Get("chbSpiClkBuf_1", 0);
	chbaSpiClkBuf[2] = pini->Get("chbSpiClkBuf_2", 0);
	chbaSpiClkBuf[3] = pini->Get("chbSpiClkBuf_3", 0);
	chbaSpiClkBuf[4] = pini->Get("chbSpiClkBuf_4", 0);
	chbaSpiClkBuf[5] = pini->Get("chbSpiClkBuf_5", 0);
	chbaSpiClkBuf[6] = pini->Get("chbSpiClkBuf_6", 1);

	rgrFDDTDD.itemIndex = pini->Get("rgrFDDTDD", 0);
	rgrTDDMOD.itemIndex = pini->Get("rgrTDDMOD", 0);

	chbPDXCOBUF.checked = pini->Get("chbPDXCOBUF", 0);
	chbSLFBXCOBUF.checked = pini->Get("chbSLFBXCOBUF", 1);
	chbBYPXCOBUF.checked = pini->Get("chbBYPXCOBUF", 0);
	chbPwrLpfCal.checked = pini->Get("chbPwrLpfCal", 1);
	chbPwrRfLbsw.checked = pini->Get("chbPwrRfLbsw", 0);

	m_bAllowSend = true;
};

//---------------------------------------------------------------------------
void Top_Module::swResetOn()
{
	chbReset.checked = true;
	pMainModule->CMResetAct();
}

//---------------------------------------------------------------------------
void Top_Module::swResetOff()
{
	chbReset.checked = false;
	pMainModule->CMResetInAct();
}

/**
    Enables all SPI clock buffers
*/
void Top_Module::EnableAllSPIClocks()
{
 	//======= register addr 0x0A =======
	m_psD.cDataW[0x09] = 0x7F;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x09;

};

/**
    Enables SPI clock buffers by mask
    @param mask clock mask
*/
void Top_Module::EnableSPIClocksByMask(int mask)
{
    char btmp;

    //======= register addr 0x09 =======
    m_psD.cDataW[0x09] = 0x00;
    //RXOUTSW
    btmp = rgrRXOUTSW.itemIndex;
    btmp = btmp << 7; m_psD.cDataW[0x09] |= btmp;
    //SPI_CLK_EN[6]
    btmp = chbaSpiClkBuf[6] == true ? 1 : 0;
    btmp = btmp << 6; m_psD.cDataW[0x09] |= btmp;
    //SPI_CLK_EN[5]
    btmp = chbaSpiClkBuf[5] == true ? 1 : 0;
    btmp = btmp << 5; m_psD.cDataW[0x09] |= btmp;
    //SPI_CLK_EN[4]
    btmp = chbaSpiClkBuf[4] == true ? 1 : 0;
    btmp = btmp << 4; m_psD.cDataW[0x09] |= btmp;
    //SPI_CLK_EN[3]
    btmp = chbaSpiClkBuf[3] == true ? 1 : 0;
    btmp = btmp << 3; m_psD.cDataW[0x09] |= btmp;
    //SPI_CLK_EN[2]
    btmp = chbaSpiClkBuf[2] == true ? 1 : 0;
    btmp = btmp << 2; m_psD.cDataW[0x09] |= btmp;
    //SPI_CLK_EN[1]
    btmp = chbaSpiClkBuf[1] == true ? 1 : 0;
    btmp = btmp << 1; m_psD.cDataW[0x09] |= btmp;
    //SPI_CLK_EN[0]
    btmp = chbaSpiClkBuf[0] == true ? 1 : 0;
    btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

    //Set Mask
    m_psD.cDataW[0x09] |= (char)mask;

    m_psD.iToW = 1;
    m_psD.iWInd[0] = 0x09;
    pMainModule->CMAutoDownload(m_cMAddr);
};

/**
	Restores SPI clock bufer states according to GUI settings
*/
void Top_Module::RestoreAllSPIClocks()
{
  	char btmp;
	// ======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
	// RXOUTSW
	btmp = rgrRXOUTSW.itemIndex;
	btmp = btmp << 7;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[6]
	btmp = chbaSpiClkBuf[6] == true ? 1 : 0;
	btmp = btmp << 6;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[5]
	btmp = chbaSpiClkBuf[5] == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[4]
	btmp = chbaSpiClkBuf[4] == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[3]
	btmp = chbaSpiClkBuf[3] == true ? 1 : 0;
	btmp = btmp << 3;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[2]
	btmp = chbaSpiClkBuf[2] == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[1]
	btmp = chbaSpiClkBuf[1] == true ? 1 : 0;
	btmp = btmp << 1;
	m_psD.cDataW[0x09] |= btmp;
	// SPI_CLK_EN[0]
	btmp = chbaSpiClkBuf[0] == true ? 1 : 0;
	btmp = btmp << 0;
	m_psD.cDataW[0x09] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x09;
	pMainModule->CMAutoDownload(m_cMAddr);
};

/**
	Set Soft Tx enable values
	Returns GUI setting for Tx enable
*/
bool Top_Module::CustSet_SofTxOnOff(bool On)
{
	char btmp;
	// ======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	// DECODE
	btmp = (char)rgrDecode.itemIndex;
	btmp = btmp << 7;
	m_psD.cDataW[0x05] |= btmp;
	// SRESET
	btmp = rgrDsmRst.itemIndex;
	btmp = btmp << 5;
	m_psD.cDataW[0x05] |= btmp;
	// EN
	btmp = chbPwrTopMods.checked == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x05] |= btmp;
	// STXEN
	btmp = On;
	btmp = btmp << 3;
	m_psD.cDataW[0x05] |= btmp;
	// SRXEN
	btmp = chbPwrSoftRx.checked == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x05] |= btmp;
	// TFWMODE
	btmp = rgrSpiMode.itemIndex;
	btmp = btmp << 1;
	m_psD.cDataW[0x05] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x05;

	return chbPwrSoftTx.checked;
};

/**
	Set Soft Rx enable values
	Returns GUI setting for Rx enable
*/
bool Top_Module::CustSet_SofRxOnOff(bool On)
{
  char btmp;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	//DECODE
	btmp = (char)rgrDecode.itemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x05] |= btmp;
	//SRESET
	btmp = rgrDsmRst.itemIndex;
	btmp = btmp << 5; m_psD.cDataW[0x05] |= btmp;
	//EN
	btmp = chbPwrTopMods.checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x05] |= btmp;
	//STXEN
	btmp = chbPwrSoftTx.checked == true ? 1 : 0;
	btmp = btmp << 3; m_psD.cDataW[0x05] |= btmp;
	//SRXEN
	btmp = On;
	btmp = btmp << 2; m_psD.cDataW[0x05] |= btmp;
	//TFWMODE
	btmp = rgrSpiMode.itemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x05] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x05;

	return chbPwrSoftRx.checked;
};

/**
    Activate start calibration command and then deactivate.
*/
void Top_Module::StartCalibration(int Addr)
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
	btmp = (char)Addr;
	m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x03;
	pMainModule->CMAutoDownload(m_cMAddr);

	m_DCClbrV[Addr] = GetCalVal(Addr);
};

/**
    Read DC Calibration value
*/
int Top_Module::GetCalVal(int Addr)
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
	//SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);

	// Return value
	// DC_REGVAL[5:0]
	return (m_psD.cDataR[0x00] & 0x3F);
};

/**
    Write DC Calibration value
*/
void Top_Module::SetCalVal(int Addr, int Val)
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
    Set calibration chain address
*/
void Top_Module::SetCalAddr(int Addr)
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
};

/**
    Write All DC Calibration values
*/
void Top_Module::DownloadAllDCCalValues()
{
	SetCalVal(0x00, m_DCClbrV[0]);
};

/**
    Returns DC Calibration Chain status (address 0x1)
    Address of DC Calibration Chain should be settled before.
*/
char Top_Module::GetCalStatus()
{
	//Read SPI configuration
	//SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);

	//Return value
	//DC_REGVAL[5:0]
	return m_psD.cDataR[0x01];
};

/**
    Set DC Calibration values in the class to defaults
*/
void Top_Module::SetCalDefaults()
{
	m_DCClbrV[0] = 31;
	m_DCClbrV[1] = 31;
	m_DCClbrV[2] = 31;
	m_DCClbrV[3] = 31;
	m_DCClbrV[4] = 31;
};


//---------------------------------------------------------------------------
// Functions for customer mode interface
//---------------------------------------------------------------------------
void Top_Module::CustSet_Tia2OutON()
{
	m_bAllowSend = false;
	chbRxTestModeEn.checked = true;
	m_bAllowSend = true;

	MakeData(0x09); pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::CustSet_Tia2OutOFF()
{
  	m_bAllowSend = false;
	chbRxTestModeEn.checked = false;
	m_bAllowSend = true;

	MakeData(0x09);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::CustSet_LPFBandwidth(int ind)
{
	m_bAllowSend = false;
	rgrLpfCalBw.itemIndex = ind;
	m_bAllowSend = true;

	MakeData(0x10);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::CustSet_SetRFLB(int ind)
{
	m_bAllowSend = false;
	rgrRFLB.itemIndex = ind;
	m_bAllowSend = true;

	MakeData(0x0D);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::CustSet_SetBBLB(int ind)
{
	m_bAllowSend = false;
	rgrBBLB.itemIndex = ind;
	m_bAllowSend = true;

	MakeData(0x0A);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::TopPowerOn(bool on)
{
	m_bAllowSend = false;
	chbPwrTopMods.checked = on;
	rgrDecode.itemIndex = 0;
	m_bAllowSend = true;

	MakeData(0x02);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::CustSet_EnableLPFCAL(bool On)
{
	m_bAllowSend = false;
	chbLpfCalEn.checked = On;
	m_bAllowSend = true;

	MakeData(0x0E);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::CustSet_ResetLPFCAL(bool Active)
{
	m_bAllowSend = false;
	chbLpfCalRst.checked = Active;
	m_bAllowSend = true;

	MakeData(0x07);
	pMainModule->CMAutoDownload(m_cMAddr);
};

void Top_Module::CustGet_LPFCALVal(int &DCCALVal, int &LPFCALVal)
{
	MakeData(0xF0); pMainModule->CMAutoDownload(m_cMAddr);
	pMainModule->CMRead(1, m_cMAddr);

	//DC_REGVAL[5:0]
	DCCALVal = DC_REGVAL_r00_b50();

	//RCCAL_LPFCAL[2:0]
	LPFCALVal = RCCAL_LPFCAL_r01_b75();
};

int Top_Module::GetLPFTuningClockInd()
{
	return rgrCLKSEL_LPFCAL.itemIndex;
};

void Top_Module::SetLPFTuningClockInd(int Ind)
{
	setCLKSEL_LPFCAL(Ind);
};

bool Top_Module::CustGet_PD_CLKLPFCAL()
{
	 return chbPD_CLKLPFCAL.checked;
};

void Top_Module::CustSet_PD_CLKLPFCAL(bool Val)
{
	chbPD_CLKLPFCAL.checked = Val;
};

void Top_Module::CustSet_rgrRXOUTSW(int Ind)
{
  	rgrRXOUTSW.itemIndex = Ind;
};

void Top_Module::CustSet_PLLCLKOUT(bool Enabled)
{
	chbaSpiClkBuf[6] = Enabled;
	SpiClkBufUpdate();
};


//---------------------------------------------------------------------------
// Functions for register testing
//---------------------------------------------------------------------------
void Top_Module::RT_SetTestMask(char Mask)
{
  MakeWriteAll();

	for (int i = 0; i < m_psD.iToW; i++)
		// for(int i=0; i<m_psD.iLen; i++)
		// for(int i=0; i<5; i++)
	{
		m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
	};

	m_psD.cDataW[0x5] = m_psD.cDataW[0x5] | 0x02;
	pMainModule->CMAutoDownload(m_cMAddr);
};


