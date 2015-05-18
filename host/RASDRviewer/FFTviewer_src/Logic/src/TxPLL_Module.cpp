// -----------------------------------------------------------------------------
// FILE: 		TxPLL_Module.cpp
// DESCRIPTION:	Tx/Rx control user interface
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ---------------------------------------------------------------------------
#include "TxPLL_Module.h"
#include "CallbackCodes.h"
#include "Main_Module.h"

// ---------------------------------------------------------------------------
// 0x0
#define                 NINT81_r00_b70() ((m_psD.cDataR[0x00] & 0xFF) >> 0)
// 0x1
#define                 NINT00_r01_b77() ((m_psD.cDataR[0x01] & 0x80) >> 7)
#define                           NINT() ((NINT81_r00_b70() << 1) + NINT00_r01_b77())
#define              NFRAC2216_r01_b60() ((m_psD.cDataR[0x01] & 0x7F) >> 0)
// 0x2
#define               NFRAC158_r02_b70() ((m_psD.cDataR[0x02] & 0xFF) >> 0)
// 0x3
#define                NFRAC70_r03_b70() ((m_psD.cDataR[0x03] & 0xFF) >> 0)
#define                          NFRAC()  ((((NFRAC2216_r01_b60() << 8) + NFRAC158_r02_b70()) << 8) + NFRAC70_r03_b70())
// 0x4
#define                 DITHEN_r04_b77() ((m_psD.cDataR[0x04] & 0x80) >> 7)
#define                  DITHN_r04_b64() ((m_psD.cDataR[0x04] & 0x70) >> 4)
#define                     EN_r04_b33() ((m_psD.cDataR[0x04] & 0x08) >> 3)
#define                AUTOBYP_r04_b22() ((m_psD.cDataR[0x04] & 0x04) >> 2)
#define                 DECODE_r04_b11() ((m_psD.cDataR[0x04] & 0x02) >> 1)
#define                   MODE_r04_b00() ((m_psD.cDataR[0x04] & 0x01) >> 0)
// 0x5
#define                 SELVCO_r05_b75() ((m_psD.cDataR[0x05] & 0xE0) >> 5)
#define                 FRANGE_r05_b42() ((m_psD.cDataR[0x05] & 0x1C) >> 2)
#define                 SELOUT_r05_b10() ((m_psD.cDataR[0x05] & 0x03) >> 0)
// 0x6
#define              EN_PFD_UP_r06_b77() ((m_psD.cDataR[0x06] & 0x80) >> 7)
#define            OEN_TSTD_SX_r06_b66() ((m_psD.cDataR[0x06] & 0x40) >> 6)
#define        PASSEN_TSTOD_SD_r06_b55() ((m_psD.cDataR[0x06] & 0x20) >> 5)
#define                   ICHP_r06_b40() ((m_psD.cDataR[0x06] & 0x1F) >> 0)
// 0x7
#define              BYPVCOREG_r07_b77() ((m_psD.cDataR[0x07] & 0x80) >> 7)
#define               PDVCOREG_r07_b66() ((m_psD.cDataR[0x07] & 0x40) >> 6)
#define               FSTVCOBG_r07_b55() ((m_psD.cDataR[0x07] & 0x20) >> 5)
#define                  OFFUP_r07_b40() ((m_psD.cDataR[0x07] & 0x1F) >> 0)
// 0x8
#define             VOVCOREG31_r08_b75() ((m_psD.cDataR[0x08] & 0xE0) >> 5)
#define                OFFDOWN_r08_b40() ((m_psD.cDataR[0x08] & 0x1F) >> 0)
// 0x9
#define             VOVCOREG00_r09_b77() ((m_psD.cDataR[0x09] & 0x80) >> 7)
#define                       VOVCOREG() ((VOVCOREG31_r08_b75() << 1) + (VOVCOREG00_r09_b77()))
#define                 VCOCAP_r09_b50() ((m_psD.cDataR[0x09] & 0x3F) >> 0)
// 0xA
#define                VTUNE_H_r0A_b77() ((m_psD.cDataR[0x0A] & 0x80) >> 7)
#define                VTUNE_L_r0A_b66() ((m_psD.cDataR[0x0A] & 0x40) >> 6)
#define                  BCODE_r0A_b50() ((m_psD.cDataR[0x0A] & 0x3F) >> 0)
// 0xB
#define                  ACODE_r0B_b74() ((m_psD.cDataR[0x0B] & 0xF0) >> 4)
#define          PD_VCOCOMP_SX_r0B_b33() ((m_psD.cDataR[0x0B] & 0x08) >> 3)
#define                ENLOBUF_r0B_b22() ((m_psD.cDataR[0x0B] & 0x04) >> 2)
#define                 ENLAMP_r0B_b11() ((m_psD.cDataR[0x0B] & 0x02) >> 1)
#define                    TRI_r0B_b00() ((m_psD.cDataR[0x0B] & 0x01) >> 0)
// 0xC
#define                    POL_r0C_b77() ((m_psD.cDataR[0x0C] & 0x80) >> 7)
#define                  PFDPD_r0C_b66() ((m_psD.cDataR[0x0C] & 0x40) >> 6)
#define              ENFEEDDIV_r0C_b55() ((m_psD.cDataR[0x0C] & 0x20) >> 5)
#define                PFDCLKP_r0C_b44() ((m_psD.cDataR[0x0C] & 0x10) >> 4)
#define                BCLKSEL_r0C_b32() ((m_psD.cDataR[0x0C] & 0x0C) >> 2)
#define                 BINSEL_r0C_b11() ((m_psD.cDataR[0x0C] & 0x02) >> 1)
#define                 BSTART_r0C_b00() ((m_psD.cDataR[0x0C] & 0x01) >> 0)
// 0xD
#define                 BSTATE_r0D_b77() ((m_psD.cDataR[0x0D] & 0x80) >> 7)
#define               BSIG2216_r0D_b60() ((m_psD.cDataR[0x0D] & 0x7F) >> 0)
// 0xE
#define                BSIG158_r0E_b70() ((m_psD.cDataR[0x0E] & 0xFF) >> 0)
// 0xF
#define                 BSIG70_r0F_b70() ((m_psD.cDataR[0x0F] & 0xFF) >> 0)
#define                           BSIG() ((((BSIG2216_r0D_b60() << 8) | BSIG158_r0E_b70()) << 8) | BSIG70_r0F_b70())

#define FRIF_DIR_W "rfIf Direct=16,"
// #define FRIF_SPI_A_TX ",20"
// #define FRIF_SPI_A_RX ",20"

// ---------------------------------------------------------------------------
TxPLL_Module::TxPLL_Module()
{
	m_FreqVsCap = new Data_FreqVsCap();
	m_dRefF = 30720000;

	pMainModule = NULL;
	dlgVcoCapLog = new TextLog();

	lblN_info=0;
	lblFvcoInt_info=0;
	lblFvco2Int_info=0;
	lblFvco4Int_info=0;
	lblFvco8Int_info=0;
	lblFvco16Int_info=0 ;

}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
TxPLL_Module::~TxPLL_Module(void)
{
	delete[]m_psD.cCmdW;
	delete[]m_psD.cDataW;
	delete[]m_psD.cCmdR;
	delete[]m_psD.cDataR;
	delete[]m_psD.iRInd;
	delete[]m_psD.iWInd;
	delete[]m_psD.cTestMap;
	delete m_FreqVsCap;
}

char TxPLL_Module::getAddr()
{
	return m_cMAddr;
}

/**
    initializes structures for sending and receiving data
    @param pMain pointer to main module
    @param MAddr module address
*/
void TxPLL_Module::Initialize(Main_Module *pMain, char MAddr)
{
	pMainModule = pMain;
	m_cMAddr = MAddr;

	if (m_cMAddr == RxPllAddr)
	{
		dblDesFreq = 1.950;
	}
	else
	{
		dblDesFreq = 2.140;
	};

	if (m_cMAddr == TxPllAddr)
	{
		m_FreqVsCap->Initialize("TxVCOFile");
	}
	else
	{
		m_FreqVsCap->Initialize("RxVCOFile");
	};

	m_psD.iLen = TxPllLen;
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
	m_psD.cTestMap[0x0] = 0xFF;
	m_psD.cTestMap[0x1] = 0xFF;
	m_psD.cTestMap[0x2] = 0xFF;
	m_psD.cTestMap[0x3] = 0xFF;
	m_psD.cTestMap[0x4] = 0xFF;
	m_psD.cTestMap[0x5] = 0xFF;
	m_psD.cTestMap[0x6] = 0xFF;
	m_psD.cTestMap[0x7] = 0xFF;
	m_psD.cTestMap[0x8] = 0xFF;
	m_psD.cTestMap[0x9] = 0xBF;
	m_psD.cTestMap[0xA] = 0x3F;
	m_psD.cTestMap[0xB] = 0xFF;
	m_psD.cTestMap[0xC] = 0xFF;
	m_psD.cTestMap[0xD] = 0x00;
	m_psD.cTestMap[0xE] = 0x00;
	m_psD.cTestMap[0xF] = 0x00;

	SetDefaults();
};

/**
    Sets default values to all settings
*/
void TxPLL_Module::SetDefaults()
{
	int itmp;
	double dtmp;
	m_bAllowSend = false;

	// ==== 0x04 ==========================
	// DITHEN
	chbDITHEN.checked = true;
	// DITHN[2:0]
	rgrDITHN.clear();
	for (int i = 0; i < 8; i++)
	{
		rgrDITHN.add(i + 1);
	};
	rgrDITHN.itemIndex = 0;
	// EN
	chbPwrPllMods.checked = true;
	// AUTOBYP
	chbAUTOBYP.checked = false;
	// DECODE
	rgrDecode.itemIndex = 0;
	// MODE
	rgrMODE.itemIndex = 0;

	// ==== 0x05 ==========================
	// SELVCO[2:0]
	rgrSELVCO.itemIndex = 2;
	m_iPrevVCO = rgrSELVCO.itemIndex;
	// FRANGE[2:0]
	rgrFRANGE.itemIndex = 1;
	// SELOUT[1:0]
	rgrSELOUT.itemIndex = 1;
	// ==== 0x06 ==========================
	// EN_PFD_UP
	chbEN_PFD_UP.checked = true;
	// OEN_TSTD_SX
	chbOEN_TSTD_SX.checked = false;
	// PASSEN_TSTOD_SD
	chbPASSEN_TSTOD_SD.checked = false;
	// ICHP[4:0]
	rgrICHP.clear();
	itmp = 0;
	for (int i = 0; i < 25; i++)
	{
		rgrICHP.add(itmp);
		itmp += 100;
	};
	rgrICHP.itemIndex = 12;
	// ==== 0x07 ==========================
	// BYPVCOREG
	chbBYPVCOREG.checked = true;
	// PDVCOREG
	chbPDVCOREG.checked = true;
	// FSTVCOBG
	chbFSTVCOBG.checked = true;
	// OFFUP[4:0]
	rgrOFFUP.clear();
	itmp = 0;
	for (int i = 0; i < 25; i++)
	{
		rgrOFFUP.add(itmp);
		itmp += 10;
	};
	rgrOFFUP.itemIndex = 0;
	// ==== 0x08 ==========================
	// VOVCOREG
	rgrVOVCOREG.clear();
	dtmp = 1.4;
	for (int i = 0; i < 13; i++)
	{
		rgrVOVCOREG.add(dtmp);
		dtmp += 0.1;
	};
	rgrVOVCOREG.itemIndex = 5;
	// OFFDOWN[4:0]
	rgrOFFDOWN.clear();
	itmp = 0;
	for (int i = 0; i < 25; i++)
	{
		rgrOFFDOWN.add(itmp);
		itmp += 10;
	};
	rgrOFFDOWN.itemIndex = 0;
	// ==== 0x09 ==========================
	// VCOCAP[5:0]
	rgrVCOCAP.clear();
	for (int i = 0; i < 64; i++)
	{
		rgrVCOCAP.add(i);
	};
	rgrVCOCAP.itemIndex = 20;
	// ==== 0x0A ==========================
	// BCODE[5:0]
	rgrBCODE.clear();
	for (int i = 7; i < 36; i++)
	{
		rgrBCODE.add(i);
	};
	rgrBCODE.itemIndex = 5;
	// ==== 0x0B ==========================
	// ACODE[3:0]
	rgrACODE.clear();
	for (int i = 0; i < 8; i++)
	{
		rgrACODE.add(i);
	};
	rgrACODE.itemIndex = 0;
	// PD_VCOCOMP_SX
	chbPD_VCOCOMP_SX.checked = true;
	// ENLOBUF
	chbENLOBUF.checked = true;
	// ENLAMP
	chbENLAMP.checked = true;
	// TRI
	chbTRI.checked = false;
	// ==== 0x0C ==========================
	// POL
	chbPOL.checked = false;
	// PFDPD
	chbPFDPD.checked = true;
	// ENFEEDDIV
	chbENFEEDDIV.checked = true;
	// PFDCLKP
	chbPFDCLKP.checked = true;
	// BCLKSEL
	rgrBCLKSEL.itemIndex = 2;
	// BINSEL
	rgrBINSEL.itemIndex = 0;

	// Set frequency
	if (m_cMAddr == RxPllAddr)
	{
		dblDesFreq = 1.950;
	}
	else
	{
		dblDesFreq = 2.140;
	};

	lblBSIG.set("0x000000");

	CalcIntPllData();
	CalcPLLData();

#ifdef HIDE_FREQ
	// grbFreq->Width = 160;
	// grbFreq->Height = 104;
	// grbOutFreq->Top = 16;
	rgrMODE->Visible = false;
#else
	// grbFreq->Width = 545;
	// grbFreq->Height = 273;
#endif

	m_bAllowSend = true;
};

// ----------------------------------------------------------------------------
// Calculates real frequency, Nint, Nfrac, VCO selection and VCO frequency
// ----------------------------------------------------------------------------
void TxPLL_Module::CalcFreq(double dDF, double &rdRF, double &dDiv, int &iDInd,
	int &Nint, int &Nfrac, int &iVCO, double &Fvco)
{
	double dMul = 1;
	double dFvco;
	double dN;
	double dTmp;
	int iNint;
	int iNfrac;

	// VCO 4-5GHz
	if ((dDF >= (m_FreqVsCap->sVco1.dFreq[0] / 2.0)) && (dDF <
		(m_FreqVsCap->sVco1.dFreq[m_FreqVsCap->sVco1.iRef - 1] / 2)))
	{
		dMul = (double)2.0 / 1.0;
		iDInd = 1;
		iVCO = 1;
	}
	else if ((dDF >= (m_FreqVsCap->sVco1.dFreq[0] / 4.0)) && (dDF <
		(m_FreqVsCap->sVco1.dFreq[m_FreqVsCap->sVco1.iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		iDInd = 2;
		iVCO = 1;
	}
	else if ((dDF >= (m_FreqVsCap->sVco1.dFreq[0] / 8.0)) && (dDF <
		(m_FreqVsCap->sVco1.dFreq[m_FreqVsCap->sVco1.iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		iDInd = 3;
		iVCO = 1;
	}
	else if ((dDF >= (m_FreqVsCap->sVco1.dFreq[0] / 16.0)) && (dDF <
		(m_FreqVsCap->sVco1.dFreq[m_FreqVsCap->sVco1.iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		iDInd = 4;
		iVCO = 1;
	}

	// VCO 5-6GHz
	else if ((dDF >= (m_FreqVsCap->sVco2.dFreq[0] / 2.0)) && (dDF <
		(m_FreqVsCap->sVco2.dFreq[m_FreqVsCap->sVco2.iRef - 1] / 2)))
	{
		dMul = (double)2.0 / 1.0;
		iDInd = 1;
		iVCO = 2;
	}
	else if ((dDF >= (m_FreqVsCap->sVco2.dFreq[0] / 4.0)) && (dDF <
		(m_FreqVsCap->sVco2.dFreq[m_FreqVsCap->sVco2.iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		iDInd = 2;
		iVCO = 2;
	}
	else if ((dDF >= (m_FreqVsCap->sVco2.dFreq[0] / 8.0)) && (dDF <
		(m_FreqVsCap->sVco2.dFreq[m_FreqVsCap->sVco2.iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		iDInd = 3;
		iVCO = 2;
	}
	else if ((dDF >= (m_FreqVsCap->sVco2.dFreq[0] / 16.0)) && (dDF <
		(m_FreqVsCap->sVco2.dFreq[m_FreqVsCap->sVco2.iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		iDInd = 4;
		iVCO = 2;
	}

	// VCO 6-7-Hz
	else if ((dDF >= (m_FreqVsCap->sVco3.dFreq[0] / 2.0)) && (dDF <
		(m_FreqVsCap->sVco3.dFreq[m_FreqVsCap->sVco3.iRef - 1] / 2)))
	{
		dMul = (double)2.0 / 1.0;
		iDInd = 1;
		iVCO = 3;
	}
	else if ((dDF >= (m_FreqVsCap->sVco3.dFreq[0] / 4.0)) && (dDF <
		(m_FreqVsCap->sVco3.dFreq[m_FreqVsCap->sVco3.iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		iDInd = 2;
		iVCO = 3;
	}
	else if ((dDF >= (m_FreqVsCap->sVco3.dFreq[0] / 8.0)) && (dDF <
		(m_FreqVsCap->sVco3.dFreq[m_FreqVsCap->sVco3.iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		iDInd = 3;
		iVCO = 3;
	}
	else if ((dDF >= (m_FreqVsCap->sVco3.dFreq[0] / 16.0)) && (dDF <
		(m_FreqVsCap->sVco3.dFreq[m_FreqVsCap->sVco3.iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		iDInd = 4;
		iVCO = 3;
	}

	// VCO 7-8-Hz
	// else if((dDF >= (m_FreqVsCap->sVco4.dFreq[0]/2.0)) && (dDF < (m_FreqVsCap->sVco4.dFreq[m_FreqVsCap->sVco4.iRef-1]/2))) { dMul = (double) 2.0 / 1.0; iDInd = 1; iVCO = 4; }
	else if ((dDF >= (m_FreqVsCap->sVco4.dFreq[0] / 2.0)))
	{
		dMul = (double)2.0 / 1.0;
		iDInd = 1;
		iVCO = 4;
	}
	else if ((dDF >= (m_FreqVsCap->sVco4.dFreq[0] / 4.0)) && (dDF <
		(m_FreqVsCap->sVco4.dFreq[m_FreqVsCap->sVco4.iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		iDInd = 2;
		iVCO = 4;
	}
	else if ((dDF >= (m_FreqVsCap->sVco4.dFreq[0] / 8.0)) && (dDF <
		(m_FreqVsCap->sVco4.dFreq[m_FreqVsCap->sVco4.iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		iDInd = 3;
		iVCO = 4;
	}
	else if ((dDF >= (m_FreqVsCap->sVco4.dFreq[0] / 16.0)) && (dDF <
		(m_FreqVsCap->sVco4.dFreq[m_FreqVsCap->sVco4.iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		iDInd = 4;
		iVCO = 4;
	}

	dFvco = dMul * dDF;
	Fvco = dFvco;
	dN = 1000000000 / m_dRefF;
	dN *= dFvco;

	// Because 203 = double 202.9999999999... and double casting to int gives 202, not 203!!!
	if ((int)dN < (int)(dN + 1 / pow(2.0, 23)))
		dN += 1 / pow(2.0, 23);

	iNint = (int)dN;
	iNfrac = (double)(dN - iNint) * pow(2.0, 23);
	Nint = iNint;
	Nfrac = iNfrac;

	dTmp = (double)iNfrac / (double)pow(2.0, 23);
	dDiv = (double)(dTmp + (double)iNint);
	rdRF = (m_dRefF / 1000000000) * (1.0 / dMul) * dDiv;

};

// ----------------------------------------------------------------------------
// Accoerding to Danny's Whish
// Calculates real frequency, Nint, Nfrac, VCO frequency
// ----------------------------------------------------------------------------
void TxPLL_Module::CalcFreqDannyWhish(double dDF, double &rdRF, double &dDiv,
	int &iDInd, int &Nint, int &Nfrac, int &iVCO, double &Fvco)
{
	double dMul;
	double dFvco;
	double dN;
	double dTmp;
	int iNint;
	int iNfrac;

	// VCO 7-8-Hz
	dMul = (double)4.0 / 1.0;
	iDInd = 2;
	iVCO = 4;

	dFvco = dMul * dDF;
	Fvco = dFvco;
	dN = 1000000000 / m_dRefF;
	dN *= dFvco;

	// Because 203 = double 202.9999999999... and double casting to int gives 202, not 203!!!
	if ((int)dN < (int)(dN + 1 / pow(2.0, 23)))
		dN += 1 / pow(2.0, 23);

	iNint = (int)dN;
	iNfrac = (double)(dN - iNint) * pow(2.0, 23);
	Nint = iNint;
	Nfrac = iNfrac;

	dTmp = (double)iNfrac / (double)pow(2.0, 23);
	dDiv = (double)(dTmp + (double)iNint);
	rdRF = (m_dRefF / 1000000000) * (1.0 / dMul) * dDiv;
};

// ----------------------------------------------------------------------------
// PLL fractional mode values calculation
// ----------------------------------------------------------------------------
void TxPLL_Module::CalcPLLData()
{
	double dReal;
	double dDiv;
	int iDivInd;
	int iNint;
	int iNfrac;
	int iVCO;
	int iCap;
	double dVCO;
	string Str;

	CalcFreq(dblDesFreq, dReal, dDiv, iDivInd, iNint, iNfrac, iVCO, dVCO);
	lblROutF_info = (dReal);
	lblDiv_info = (dDiv);
	lblNint_info = (iNint);
	lblNfrac_info = (iNfrac);
	lblVcoF_info = (dVCO);

	m_bAllowSend = false;
	rgrFRANGE.itemIndex = iDivInd;

	iCap = AutoSelectVcoCap(dVCO, iVCO);

	if ((iCap > 61) && ((iVCO == 2) || (iVCO == 3) || (iVCO == 4)))
	{
		iVCO--;
		iCap = AutoSelectVcoCap(dVCO, iVCO);
	};
	rgrSELVCO.itemIndex = iVCO;
	rgrVCOCAP.itemIndex = iCap;
	m_bAllowSend = true;
};

// ----------------------------------------------------------------------------
// PLL integer mode values calculation
// ----------------------------------------------------------------------------
void TxPLL_Module::CalcIntPllData()
{
	int N = 8 * (rgrBCODE.itemIndex + 7) + rgrACODE.itemIndex + 34;
	lblN_info = (N);
	double Fvco = (m_dRefF / 1000000000) * N;
	lblFvcoInt_info = (Fvco);
	lblFvco2Int_info = (Fvco / 2);
	lblFvco4Int_info = (Fvco / 4);
	lblFvco8Int_info = (Fvco / 8);
	lblFvco16Int_info = (Fvco / 16);
};

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
int TxPLL_Module::AutoSelectVcoCap(double Freq, int iVcoInd)
{
	int iCInd = 0;
	switch (iVcoInd)
	{
	case 1:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco1.iRef, m_FreqVsCap->sVco1.dFreq, m_FreqVsCap->sVco1.iCap, Freq);
		break;
	case 2:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco2.iRef, m_FreqVsCap->sVco2.dFreq, m_FreqVsCap->sVco2.iCap, Freq);
		break;
	case 3:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco3.iRef, m_FreqVsCap->sVco3.dFreq, m_FreqVsCap->sVco3.iCap, Freq);
		break;
	case 4:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco4.iRef, m_FreqVsCap->sVco4.dFreq, m_FreqVsCap->sVco4.iCap, Freq);
		break;
	default:
		iCInd = 0;
	};

	if (iCInd < 0)
		iCInd = 0;
	if (iCInd > 63)
		iCInd = 63;

	return iCInd;
};

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void TxPLL_Module::ChooseVcoCap()
{
	int iCInd;
	switch (rgrSELVCO.itemIndex)
	{
	case 1:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco1.iRef, m_FreqVsCap->sVco1.dFreq, m_FreqVsCap->sVco1.iCap,
			lblVcoF_info);
		break;
	case 2:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco2.iRef, m_FreqVsCap->sVco2.dFreq, m_FreqVsCap->sVco2.iCap,
			lblVcoF_info);
		break;
	case 3:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco3.iRef, m_FreqVsCap->sVco3.dFreq, m_FreqVsCap->sVco3.iCap,
			lblVcoF_info);
		break;
	case 4:
		iCInd = QuadraticInterpol(m_FreqVsCap->sVco4.iRef, m_FreqVsCap->sVco4.dFreq, m_FreqVsCap->sVco4.iCap,
			lblVcoF_info);
		break;
	default:
		iCInd = 0;
	};

	m_bAllowSend = false;
	if (iCInd < 0)
		iCInd = 0;
	if (iCInd > 63)
		iCInd = 63;
	setVCOCAP(iCInd);
	m_bAllowSend = true;

	MakeData(0x00);
};

// ----------------------------------------------------------------------------
// Make data to download
// ----------------------------------------------------------------------------
void TxPLL_Module::MakeData(int rAddr)
{
	char btmp;
	int itmp;

	// ======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;
	// NINT[8:1]
	itmp = lblNint_info;
	itmp = itmp >> 1;
	m_psD.cDataW[0x00] |= itmp;

	// ======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;
	// NINT[0]
	itmp = lblNint_info;
	itmp = itmp & 0x01;
	itmp = itmp << 7;
	m_psD.cDataW[0x01] |= itmp;
	// NFRAC[22:16]
	itmp = 0x7F0000 & lblNfrac_info;
	itmp = itmp >> 16;
	m_psD.cDataW[0x01] |= (char)itmp;

	// ======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
	// NFRAC[15:8]
	itmp = 0xFF00 & lblNfrac_info;
	itmp = itmp >> 8;
	m_psD.cDataW[0x02] |= (char)itmp;

	// ======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	// NFRAC[7:0]
	itmp = 0xFF & lblNfrac_info;
	m_psD.cDataW[0x03] |= (char)itmp;

	// ======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
	// DITHEN
	btmp = chbDITHEN.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x04] |= btmp;
	// DITHN[2:0]
	btmp = (char)rgrDITHN.itemIndex;
	btmp = btmp << 4;
	m_psD.cDataW[0x04] |= btmp;
	// EN
	btmp = chbPwrPllMods.checked == true ? 1 : 0;
	btmp = btmp << 3;
	m_psD.cDataW[0x04] |= btmp;
	// AUTOBYP
	btmp = chbAUTOBYP.checked == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x04] |= btmp;
	// DECODE
	btmp = (char)rgrDecode.itemIndex;
	btmp = btmp << 1;
	m_psD.cDataW[0x04] |= btmp;
	// MODE
	btmp = rgrMODE.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x04] |= btmp;

	// ======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	// SELVCO[2:0]
	switch (rgrSELVCO.itemIndex)
	{
	case 0:
		btmp = 0x00;
		break;
	case 1:
		btmp = 0x04;
		break;
	case 2:
		btmp = 0x05;
		break;
	case 3:
		btmp = 0x06;
		break;
	case 4:
		btmp = 0x07;
		break;
	default:
		btmp = 0x00;
	};
	btmp = btmp << 5;
	m_psD.cDataW[0x05] |= btmp;
	// FRANGE[2:0]
	switch (rgrFRANGE.itemIndex)
	{
	case 0:
		btmp = 0x00;
		break;
	case 1:
		btmp = 0x04;
		break;
	case 2:
		btmp = 0x05;
		break;
	case 3:
		btmp = 0x06;
		break;
	case 4:
		btmp = 0x07;
		break;
	default:
		btmp = 0x00;
	};
	btmp = btmp << 2;
	m_psD.cDataW[0x05] |= btmp;
	// SELOUT[1:0]
	btmp = (char)rgrSELOUT.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x05] |= btmp;

	// ======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
	// EN_PFD_UP
	btmp = chbEN_PFD_UP.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x06] |= btmp;
	// OEN_TSTD_SX
	btmp = chbOEN_TSTD_SX.checked == true ? 1 : 0;
	btmp = btmp << 6;
	m_psD.cDataW[0x06] |= btmp;
	// PASSEN_TSTOD_SD
	btmp = chbPASSEN_TSTOD_SD.checked == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x06] |= btmp;
	// ICHP[4:0]
	btmp = (char)rgrICHP.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x06] |= btmp;

	// ======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
	// BYPVCOREG
	btmp = chbBYPVCOREG.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x07] |= btmp;
	// PDVCOREG
	btmp = chbPDVCOREG.checked == true ? 1 : 0;
	btmp = btmp << 6;
	m_psD.cDataW[0x07] |= btmp;
	// FSTVCOBG
	btmp = chbFSTVCOBG.checked == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x07] |= btmp;
	// OFFUP[4:0]
	btmp = (char)rgrOFFUP.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x07] |= btmp;

	// ======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
	// VOVCOREG[3:1]
	btmp = (char)rgrVOVCOREG.itemIndex;
	btmp = btmp >> 1;
	btmp = btmp << 5;
	m_psD.cDataW[0x08] |= btmp;
	// rgrOFFDOWN[4:0]
	btmp = (char)rgrOFFDOWN.itemIndex;
	btmp = btmp << 0;
	m_psD.cDataW[0x08] |= btmp;

	// ======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
	// VOVCOREG[0]
	btmp = (char)rgrVOVCOREG.itemIndex;
	btmp = btmp & 0x01;
	btmp = btmp << 7;
	m_psD.cDataW[0x09] |= btmp;
	// VCOCAP[5:0]
	btmp = 0x3F & rgrVCOCAP.itemIndex;

	btmp = btmp << 0;
	m_psD.cDataW[0x09] |= btmp;

	// ======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
	// BCODE[5:0]
	btmp = 0x00;
	switch (rgrBCODE.itemIndex)
	{
	case 0x0:
		btmp = 0x09;
		break;
	case 0x1:
		btmp = 0x08;
		break;
	case 0x2:
		btmp = 0x0C;
		break;
	case 0x3:
		btmp = 0x0E;
		break;
	case 0x4:
		btmp = 0x0F;
		break;
	case 0x5:
		btmp = 0x03;
		break;
	case 0x6:
		btmp = 0x01;
		break;
	case 0x7:
		btmp = 0x00;
		break;
	case 0x8:
		btmp = 0x04;
		break;
	case 0x9:
		btmp = 0x06;
		break;
	case 0xA:
		btmp = 0x07;
		break;
	case 0xB:
		btmp = 0x23;
		break;
	case 0xC:
		btmp = 0x21;
		break;
	case 0x0D:
		btmp = 0x20;
		break;
	case 0x0E:
		btmp = 0x24;
		break;
	case 0x0F:
		btmp = 0x26;
		break;
	case 0x10:
		btmp = 0x27;
		break;
	case 0x11:
		btmp = 0x33;
		break;
	case 0x12:
		btmp = 0x31;
		break;
	case 0x13:
		btmp = 0x30;
		break;
	case 0x14:
		btmp = 0x34;
		break;
	case 0x15:
		btmp = 0x36;
		break;
	case 0x16:
		btmp = 0x37;
		break;
	case 0x17:
		btmp = 0x3B;
		break;
	case 0x18:
		btmp = 0x39;
		break;
	case 0x19:
		btmp = 0x38;
		break;
	case 0x1A:
		btmp = 0x3C;
		break;
	case 0x1B:
		btmp = 0x3E;
		break;
	case 0x1C:
		btmp = 0x3F;
		break;
	};
	btmp = btmp << 0;
	m_psD.cDataW[0x0A] |= btmp;

	// ======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
	// ACODE[3:0]
	btmp = 0x00;
	switch (rgrACODE.itemIndex)
	{
		// DC Calibration
	case 0x0:
		btmp = 0x07;
		break;
	case 0x1:
		btmp = 0x03;
		break;
	case 0x2:
		btmp = 0x01;
		break;
	case 0x3:
		btmp = 0x00;
		break;
	case 0x4:
		btmp = 0x08;
		break;
	case 0x5:
		btmp = 0x0C;
		break;
	case 0x6:
		btmp = 0x0E;
		break;
	case 0x7:
		btmp = 0x0F;
		break;
	};
	btmp = btmp << 4;
	m_psD.cDataW[0x0B] |= btmp;
	// PD_VCOCOMP_SX
	btmp = chbPD_VCOCOMP_SX.checked == true ? 0 : 1;
	btmp = btmp << 3;
	m_psD.cDataW[0x0B] |= btmp;
	// ENLOBUF
	btmp = chbENLOBUF.checked == true ? 1 : 0;
	btmp = btmp << 2;
	m_psD.cDataW[0x0B] |= btmp;
	// ENLAMP
	btmp = chbENLAMP.checked == true ? 1 : 0;
	btmp = btmp << 1;
	m_psD.cDataW[0x0B] |= btmp;
	// TRI
	btmp = chbTRI.checked == true ? 1 : 0;
	btmp = btmp << 0;
	m_psD.cDataW[0x0B] |= btmp;

	// ======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	// POL
	btmp = chbPOL.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDPD
	btmp = chbPFDPD.checked == true ? 0 : 1;
	btmp = btmp << 6;
	m_psD.cDataW[0x0C] |= btmp;
	// ENFEEDDIV
	btmp = chbENFEEDDIV.checked == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDCLKP
	btmp = chbPFDCLKP.checked == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x0C] |= btmp;
	// BCLKSEL
	btmp = (char)(rgrBCLKSEL.itemIndex & 0x03);
	btmp = btmp << 2;
	m_psD.cDataW[0x0C] |= btmp;
	// BINSEL
	btmp = (char)(rgrBINSEL.itemIndex & 0x01);
	btmp = btmp << 1;
	m_psD.cDataW[0x0C] |= btmp;
	// BSTART
	btmp = 0x00;
	btmp = btmp << 0;
	m_psD.cDataW[0x0C] |= btmp;

	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch (rAddr)
	{
		// User mode
	case 0x00:
		m_psD.iToW = 5;
		m_psD.iWInd[0] = 0x00;
		m_psD.iWInd[1] = 0x01;
		m_psD.iWInd[2] = 0x02;
		m_psD.iWInd[3] = 0x03;
		m_psD.iWInd[4] = 0x05;
		break;

	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
	case 0x05:
	case 0x1B:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x04;
		break;

	case 0x06:
	case 0x07:
	case 0x08:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x05;
		break;

	case 0x09:
	case 0x19:
	case 0x1A:
	case 0x1C:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x06;
		break;

	case 0x0A:
	case 0x1D:
	case 0x1E:
	case 0x1F:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x07;
		break;

	case 0x0B:
	case 0x0C:
	case 0x20:
		m_psD.iToW = 2;
		m_psD.iWInd[0] = 0x08;
		m_psD.iWInd[1] = 0x09;
		break;

		// Test mode
	case 0x0D:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0A;
		break;

	case 0x0E:
	case 0x0F:
	case 0x18:
	case 0x10:
	case 0x11:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0B;
		break;

	case 0x12:
	case 0x13:
	case 0x15:
	case 0x17:
	case 0x21:
	case 0x22:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x0C;
		break;

		// Customer Mode
	case 0x80:
		m_psD.iToW = 1;
		m_psD.iWInd[0] = 0x05;
		break;

	default:
		m_psD.iToW = 0;
	};
}

// ---------------------------------------------------------------------------
// Calculates PLLData
// ---------------------------------------------------------------------------
void TxPLL_Module::Calculate()
{
	// if((dblDesFreq < 0.25) || (dblDesFreq > 4.5))
	double dDesFreq = dblDesFreq;
	if ((dDesFreq < 0.2) || (dDesFreq > 4.5))
	{
		pMainModule->ShowMessage("Incorrect Frequency Value.\nShould be between 0.2 and 4.5GHz.");
		return;
	};

	CalcPLLData();

	CalcIntPllData();
	if (m_bAllowSend)
	{
		MakeData(0x00);
		pMainModule->CMAutoDownload(m_cMAddr);
	};

	// Download VCO Cap as well
	if (m_bAllowSend)
	{
		MakeData(0x0C);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
	//Tune();
}

void TxPLL_Module::setDITHEN(int checked)
{
	chbDITHEN.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x01);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getDITHEN()
{
	return chbDITHEN.checked;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setDITHN(int index)
{
	rgrDITHN.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x02);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getDITHN()
{
	return rgrDITHN.itemIndex;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setPwrPllMods(bool checked)
{
	chbPwrPllMods.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x03);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getPwrPllMods()
{
	return chbPwrPllMods.checked;
}

// ---------------------------------------------------------------------------

void TxPLL_Module::setDecode(int index)
{
	this->rgrDecode.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x04);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getDecode()
{
	return rgrDecode.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setMODE(int index)
{
	rgrMODE.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x05);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getMODE()
{
	return rgrMODE.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setSELVCO(int index)
{
	rgrSELVCO.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x06);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getSELVCO()
{
	return rgrSELVCO.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setFRANGE(int index)
{
	rgrFRANGE.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x07);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getFRANGE()
{
	return rgrFRANGE.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setSELOUT(int index)
{
	rgrSELOUT.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x08);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getSELOUT()
{
	return rgrSELOUT.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setICHP(int index)
{
	rgrICHP.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x09);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getICHP()
{
	return rgrICHP.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setOFFUP(int index)
{
	rgrOFFUP.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x0A);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getOFFUP()
{
	return rgrOFFUP.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setOFFDOWN(int index)
{
	rgrOFFDOWN.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x0B);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getOFFDOWN()
{
	return rgrOFFDOWN.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setVCOCAP(int index)
{
	rgrVCOCAP.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x0C);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getVCOCAP()
{
	return rgrVCOCAP.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setBCODE(int index)
{
	rgrBCODE.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x0D);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
	CalcIntPllData();
}

int TxPLL_Module::getBCODE()
{
	return rgrBCODE.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setACODE(int index)
{
	rgrACODE.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x0E);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
	CalcIntPllData();
}

int TxPLL_Module::getACODE()
{
	return rgrACODE.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setENLOBUF(bool checked)
{
	chbENLOBUF.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x0F);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getENLOBUF()
{
	return chbENLOBUF.checked;
}

// ---------------------------------------------------------------------------

void TxPLL_Module::setENLAMP(bool checked)
{
	chbENLAMP.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x10);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getENLAMP()
{
	return chbENLAMP.checked;
}

// ---------------------------------------------------------------------------

void TxPLL_Module::setTRI(bool checked)
{
	chbTRI.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x11);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getTRI()
{
	return chbTRI.checked;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setPOL(bool checked)
{
	chbPOL.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x12);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getPOL()
{
	return chbPOL.checked;
}

// ---------------------------------------------------------------------------

void TxPLL_Module::setPFDPD(bool checked)
{
	chbPFDPD.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x13);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getPFDPD()
{
	return chbPFDPD.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setENFEEDDIV(bool checked)
{
	chbENFEEDDIV.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x15);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getENFEEDDIV()
{
	return chbENFEEDDIV.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setPFDCLKP(bool checked)
{
	chbPFDCLKP.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x17);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getPFDCLKP()
{
	return chbPFDCLKP.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setPD_VCOCOMP_SX(bool checked)
{
	chbPD_VCOCOMP_SX.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x18);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getPD_VCOCOMP_SX()
{
	return chbPD_VCOCOMP_SX.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setOEN_TSTD_SX(bool checked)
{
	chbOEN_TSTD_SX.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x19);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getOEN_TSTD_SX()
{
	return chbOEN_TSTD_SX.checked;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setPASSEN_TSTOD_SD(bool checked)
{
	chbPASSEN_TSTOD_SD.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x1A);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getPASSEN_TSTOD_SD()
{
	return chbPASSEN_TSTOD_SD.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setAUTOBYP(bool checked)
{
	chbAUTOBYP.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x1B);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getAUTOBYP()
{
	return chbAUTOBYP.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setEN_PFD_UP(bool checked)
{
	chbEN_PFD_UP.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x1C);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getEN_PFD_UP()
{
	return chbEN_PFD_UP.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setBYPVCOREG(bool checked)
{
	chbBYPVCOREG.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x1D);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getBYPVCOREG()
{
	return chbBYPVCOREG.checked;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setPDVCOREG(bool checked)
{
	chbPDVCOREG.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x1E);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getPDVCOREG()
{
	return chbPDVCOREG.checked;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setFSTVCOBG(bool checked)
{
	chbFSTVCOBG.checked = checked;
	if (m_bAllowSend)
	{
		MakeData(0x1F);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

bool TxPLL_Module::getFSTVCOBG()
{
	return chbFSTVCOBG.checked;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setVOVCOREG(int index)
{
	rgrVOVCOREG.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x20);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getVOVCOREG()
{
	return rgrVOVCOREG.itemIndex;
}

// ---------------------------------------------------------------------------
void TxPLL_Module::setBCLKSEL(int index)
{
	rgrBCLKSEL.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x21);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getBCLKSEL()
{
	return rgrBCLKSEL.itemIndex;
}
// ---------------------------------------------------------------------------

void TxPLL_Module::setBINSEL(int index)
{
	rgrBINSEL.itemIndex = index;
	if (m_bAllowSend)
	{
		MakeData(0x22);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

int TxPLL_Module::getBINSEL()
{
	return rgrBINSEL.itemIndex;
}
// ---------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Make all data to write
// ----------------------------------------------------------------------------
void TxPLL_Module::MakeWriteAll()
{
	MakeData(0xFFFF);

	m_psD.iToW = 0xD;
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
	m_psD.iWInd[0xC] = 0x0C;
};

// ----------------------------------------------------------------------------
// Saves the chip configuration to the file
// ----------------------------------------------------------------------------
bool TxPLL_Module::ChipVsGui(ofstream &out, string Caption, bool bWrAll)
{
	bool bRez = true;
	char str[64] = "";
	char str1[64] = "";
	int itmp, itmp1;

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

	// NINT[8:0]
	// x itmp = 0;
	// x itmp = m_psD.cDataR[0x00] & 0xFF;
	// x itmp = itmp << 1;
	// x itmp = itmp | ((m_psD.cDataR[0x01] & 0x80) >> 7);
	itmp = NINT();
	if ((lblNint_info != itmp) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| NINT[8:0]";
		out.width(2);
		out << "|";
		out.width(40);
		//strcpy(str, lblNint_info.caption.c_str());
		out << lblNint_info;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// NFRAC[22:0]
	// x itmp = 0;
	// x itmp = 0x7F & m_psD.cDataR[0x01];
	// x itmp = itmp << 8;
	// x itmp = itmp | (0xFF & m_psD.cDataR[0x02]);
	// x itmp = itmp << 8;
	// x itmp = itmp | (0xFF & m_psD.cDataR[0x03]);
	itmp = NFRAC();
	if ((lblNfrac_info != itmp) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| NFRAC[22:0]";
		out.width(2);
		out << "|";
		out.width(40);
		//strcpy(str, lblNfrac_info.caption.c_str());
		out << lblNfrac_info;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// DITHEN
	if ((chbDITHEN.checked != (bool)DITHEN_r04_b77()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DITHEN";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbDITHEN.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (DITHEN_r04_b77())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// DITHN[2:0]
	if (((rgrDITHN.itemIndex) != DITHN_r04_b64()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| DITHN[2:0]";
		out.width(2);
		out << "|";
		out.width(40);
		itmp = rgrDITHN.itemIndex + 1;
		out << itmp;
		out.width(10);
		out << "Bit(s)";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		itmp = DITHN_r04_b64();
		itmp++;
		out << itmp;
		out.width(10);
		out << "Bit(s)";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// EN
	if ((chbPwrPllMods.checked != (bool)EN_r04_b33()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| EN";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPwrPllMods.checked)
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
		if (EN_r04_b33())
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

	// AUTOBYP
	if ((chbAUTOBYP.checked != (bool)AUTOBYP_r04_b22()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| AUTOBYP";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbAUTOBYP.checked)
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
		if (AUTOBYP_r04_b22())
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

	// DECODE
	if ((rgrDecode.itemIndex != DECODE_r04_b11()) || bWrAll)
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
		if (DECODE_r04_b11())
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

	// MODE
	if ((rgrMODE.itemIndex != MODE_r04_b00()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| MODE";
		out.width(2);
		out << "|";
		out.width(40);
		if (rgrMODE.itemIndex == 1)
			strcpy(str, "Integer Mode");
		else
			strcpy(str, "Fractional Mode");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (MODE_r04_b00())
			strcpy(str, "Integer Mode");
		else
			strcpy(str, "Fractional Mode");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// SELVCO[2:0]
	memset(str1, '\0', sizeof(str1));
	// x itmp = m_psD.cDataR[0x05] & 0xE0;
	// x itmp = itmp >> 5;
	itmp = SELVCO_r05_b75();
	switch (itmp)
	{
	case 0x00:
		strcpy(str1, rgrSELVCO.sItems[0].c_str());
		itmp1 = 0;
		break;
	case 0x04:
		strcpy(str1, rgrSELVCO.sItems[1].c_str());
		itmp1 = 1;
		break;
	case 0x05:
		strcpy(str1, rgrSELVCO.sItems[2].c_str());
		itmp1 = 2;
		break;
	case 0x06:
		strcpy(str1, rgrSELVCO.sItems[3].c_str());
		itmp1 = 3;
		break;
	case 0x07:
		strcpy(str1, rgrSELVCO.sItems[4].c_str());
		itmp1 = 4;
		break;
	default:
		strcpy(str1, "WRONG DATA!!!");
		itmp1 = -2;
	};

	if ((rgrSELVCO.itemIndex != itmp1) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| SELVCO[2:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrSELVCO.sItems[rgrSELVCO.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		out << str1;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// FRANGE[2:0]
	memset(str1, '\0', sizeof(str1));
	// x itmp = m_psD.cDataR[0x05] & 0x1C;
	// x itmp = itmp >> 2;
	itmp = FRANGE_r05_b42();
	switch (itmp)
	{
	case 0x00:
		strcpy(str1, rgrFRANGE.sItems[0].c_str());
		itmp = 0;
		break;
	case 0x04:
		strcpy(str1, rgrFRANGE.sItems[1].c_str());
		itmp = 1;
		break;
	case 0x05:
		strcpy(str1, rgrFRANGE.sItems[2].c_str());
		itmp = 2;
		break;
	case 0x06:
		strcpy(str1, rgrFRANGE.sItems[3].c_str());
		itmp = 3;
		break;
	case 0x07:
		strcpy(str1, rgrFRANGE.sItems[4].c_str());
		itmp = 4;
		break;
	default:
		itmp = -2;
		strcpy(str, "WRONG DATA!!!");
	};
	if ((itmp != rgrFRANGE.itemIndex) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| FRANGE[2:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrFRANGE.sItems[rgrFRANGE.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		out << str1;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// SELOUT[1:0]
	if ((rgrSELOUT.itemIndex != SELOUT_r05_b10()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| SELOUT[1:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrSELOUT.sItems[rgrSELOUT.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		itmp = SELOUT_r05_b10();
		strcpy(str, rgrSELOUT.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// EN_PFD_UP
	if ((chbEN_PFD_UP.checked != (bool)EN_PFD_UP_r06_b77()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| EN_PFD_UP";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbEN_PFD_UP.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (EN_PFD_UP_r06_b77())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// OEN_TSTD_SX
	if ((chbOEN_TSTD_SX.checked != (bool)OEN_TSTD_SX_r06_b66()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| OEN_TSTD_SX";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbOEN_TSTD_SX.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (OEN_TSTD_SX_r06_b66())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// PASSEN_TSTOD_SD
	if ((chbPASSEN_TSTOD_SD.checked != (bool)PASSEN_TSTOD_SD_r06_b55())
		|| bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| PASSEN_TSTOD_SD";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPASSEN_TSTOD_SD.checked)
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (PASSEN_TSTOD_SD_r06_b55())
			strcpy(str, "Enabled");
		else
			strcpy(str, "Disabled");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// ICHP[4:0]
	if ((rgrICHP.itemIndex != ICHP_r06_b40()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ICHP[4:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrICHP.sItems[rgrICHP.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		itmp = ICHP_r06_b40();
		strcpy(str, rgrICHP.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// BYPVCOREG
	if ((chbBYPVCOREG.checked != (bool)BYPVCOREG_r07_b77()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BYPVCOREG";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbBYPVCOREG.checked)
			strcpy(str, "Bypassed");
		else
			strcpy(str, "Not Bypassed");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (BYPVCOREG_r07_b77())
			strcpy(str, "Bypassed");
		else
			strcpy(str, "Not Bypassed");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// PDVCOREG
	if ((chbPDVCOREG.checked != (bool)PDVCOREG_r07_b66()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| PDVCOREG";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPDVCOREG.checked)
			strcpy(str, "Powered Down");
		else
			strcpy(str, "Powered Up");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (PDVCOREG_r07_b66())
			strcpy(str, "Powered Down");
		else
			strcpy(str, "Powered Up");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// FSTVCOBG
	if ((chbFSTVCOBG.checked != (bool)FSTVCOBG_r07_b55()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| FSTVCOBG";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbFSTVCOBG.checked)
			strcpy(str, "Resistor Shorted");
		else
			strcpy(str, "Switch Open");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (FSTVCOBG_r07_b55())
			strcpy(str, "Resistor Shorted");
		else
			strcpy(str, "Switch Open");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// OFFUP[4:0]
	if ((rgrOFFUP.itemIndex != OFFUP_r07_b40()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| OFFUP[4:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrOFFUP.sItems[rgrOFFUP.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		itmp = OFFUP_r07_b40();
		strcpy(str, rgrOFFUP.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// VOVCOREG[3:0]
	if ((rgrVOVCOREG.itemIndex != VOVCOREG()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| VOVCOREG[3:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrVOVCOREG.sItems[rgrVOVCOREG.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "V";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		itmp = VOVCOREG();
		strcpy(str, rgrVOVCOREG.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "V";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// OFFDOWN[4:0]
	if ((rgrOFFDOWN.itemIndex != OFFDOWN_r08_b40()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| OFFDOWN[4:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrOFFDOWN.sItems[rgrOFFDOWN.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		itmp = OFFDOWN_r08_b40();
		strcpy(str, rgrOFFDOWN.sItems[itmp].c_str());
		out << str;
		out.width(10);
		out << "uA";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// VCOCAP[5:0]
	// itmp1  = m_psD.cDataR[0x0F] & 0x01;
	// itmp1  = itmp1 << 5;
	// itmp1 |= m_psD.cDataR[0x09] & 0x1F;
	itmp1 = VCOCAP_r09_b50();
	if ((rgrVCOCAP.itemIndex != itmp1) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| VCOCAP[5:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrVCOCAP.sItems[rgrVCOCAP.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrVCOCAP.sItems[itmp1].c_str());
		out << str;
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

	if (bWrAll)
	{
		// VTUNE_H
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| VTUNE_H";
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
		memset(str, '\0', sizeof(str));
		if (VTUNE_H_r0A_b77())
			strcpy(str, "1");
		else
			strcpy(str, "0");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// VTUNE_L
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| VTUNE_L";
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
		memset(str, '\0', sizeof(str));
		if (VTUNE_L_r0A_b66())
			strcpy(str, "1");
		else
			strcpy(str, "0");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
	};

	// BCODE[5:0]
	memset(str1, '\0', sizeof(str1));
	itmp = BCODE_r0A_b50();
	switch (itmp)
	{
	case 0x3F:
		itmp1 = 35;
		break;
	case 0x3E:
		itmp1 = 34;
		break;
	case 0x3C:
		itmp1 = 33;
		break;
	case 0x38:
		itmp1 = 32;
		break;
	case 0x39:
		itmp1 = 31;
		break;
	case 0x3B:
		itmp1 = 30;
		break;
	case 0x37:
		itmp1 = 29;
		break;
	case 0x36:
		itmp1 = 28;
		break;
	case 0x34:
		itmp1 = 27;
		break;
	case 0x30:
		itmp1 = 26;
		break;
	case 0x31:
		itmp1 = 25;
		break;
	case 0x33:
		itmp1 = 24;
		break;
	case 0x27:
		itmp1 = 23;
		break;
	case 0x26:
		itmp1 = 22;
		break;
	case 0x24:
		itmp1 = 21;
		break;
	case 0x20:
		itmp1 = 20;
		break;
	case 0x21:
		itmp1 = 19;
		break;
	case 0x23:
		itmp1 = 18;
		break;
	case 0x07:
		itmp1 = 17;
		break;
	case 0x06:
		itmp1 = 16;
		break;
	case 0x04:
		itmp1 = 15;
		break;
	case 0x00:
		itmp1 = 14;
		break;
	case 0x01:
		itmp1 = 13;
		break;
	case 0x03:
		itmp1 = 12;
		break;
	case 0x0F:
		itmp1 = 11;
		break;
	case 0x0E:
		itmp1 = 10;
		break;
	case 0x0C:
		itmp1 = 9;
		break;
	case 0x08:
		itmp1 = 8;
		break;
	case 0x09:
		itmp1 = 7;
		break;
	default:
		itmp1 = -2;
		strcpy(str1, "WRONG DATA!!!");
	};
	if (((itmp1 < 0) || (itmp1 - 7 != rgrBCODE.itemIndex)) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BCODE[5:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrBCODE.sItems[rgrBCODE.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		if (itmp1 > 0)
			out << itmp1;
		else
			out << str1;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// ACODE[3:0]
	itmp = ACODE_r0B_b74();
	switch (itmp)
	{
	case 0x0F:
		itmp1 = 7;
		break;
	case 0x0E:
		itmp1 = 6;
		break;
	case 0x0C:
		itmp1 = 5;
		break;
	case 0x08:
		itmp1 = 4;
		break;
	case 0x00:
		itmp1 = 3;
		break;
	case 0x01:
		itmp1 = 2;
		break;
	case 0x03:
		itmp1 = 1;
		break;
	case 0x07:
		itmp1 = 0;
		break;
	default:
		itmp1 = -2;
		strcpy(str1, "WRONG DATA!!!");
	};
	if (((itmp1 < 0) || (itmp1 != rgrACODE.itemIndex)) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ACODE[3:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrACODE.sItems[rgrACODE.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		// memset(str, '\0', sizeof(str));
		if (itmp1 > 0)
			out << itmp1;
		else
			out << str1;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// PD_VCOCOMP_SX
	if ((chbPD_VCOCOMP_SX.checked == (bool)PD_VCOCOMP_SX_r0B_b33()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| PD_VCOCOMP_SX";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPD_VCOCOMP_SX.checked)
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
		if (PD_VCOCOMP_SX_r0B_b33())
			strcpy(str, "Powered Down");
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

	// ENLOBUF
	if ((chbENLOBUF.checked != (bool)ENLOBUF_r0B_b22()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ENLOBUF";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbENLOBUF.checked)
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
		if (ENLOBUF_r0B_b22())
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

	// ENLAMP
	if ((chbENLAMP.checked != (bool)ENLAMP_r0B_b11()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ENLAMP";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbENLAMP.checked)
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
		if (ENLAMP_r0B_b11())
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

	// TRI
	if ((chbTRI.checked != (bool)TRI_r0B_b00()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| TRI";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbTRI.checked)
			strcpy(str, "Tri-State Mode");
		else
			strcpy(str, "Normal Mode");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (TRI_r0B_b00())
			strcpy(str, "Tri-State Mode");
		else
			strcpy(str, "Normal Mode");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// POL
	if ((chbPOL.checked != (bool)POL_r0C_b77()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| POL";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPOL.checked)
			strcpy(str, "Inverted");
		else
			strcpy(str, "Normal");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (POL_r0C_b77())
			strcpy(str, "Inverted");
		else
			strcpy(str, "Normal");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// PFDPD
	if ((chbPFDPD.checked == (bool)PFDPD_r0C_b66()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| PFDPD";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPFDPD.checked)
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
		if (PFDPD_r0C_b66())
			strcpy(str, "Powered Down");
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

	// ENFEEDDIV
	if ((chbENFEEDDIV.checked != (bool)ENFEEDDIV_r0C_b55()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ENFEEDDIV";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbENFEEDDIV.checked)
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
		if (ENFEEDDIV_r0C_b55())
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

	// PFDCLKP
	if ((chbPFDCLKP.checked != (bool)PFDCLKP_r0C_b44()) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| ENFEEDDIV";
		out.width(2);
		out << "|";
		out.width(40);
		if (chbPFDCLKP.checked)
			strcpy(str, "Inverted");
		else
			strcpy(str, "In Phase");
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (PFDCLKP_r0C_b44())
			strcpy(str, "Inverted");
		else
			strcpy(str, "In Phase");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// BCLKSEL[1:0]
	itmp1 = BCLKSEL_r0C_b32();
	if ((rgrBCLKSEL.itemIndex != itmp1) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BCLKSEL[1:0]";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrBCLKSEL.sItems[rgrBCLKSEL.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		if (itmp1 > 2)
		{
			itmp1 = 2;
			false;
		};
		strcpy(str, rgrBCLKSEL.sItems[itmp1].c_str());
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	// BINSEL
	itmp1 = BINSEL_r0C_b11();
	if ((rgrBINSEL.itemIndex != itmp1) || bWrAll)
	{
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BINSEL";
		out.width(2);
		out << "|";
		out.width(40);
		strcpy(str, rgrBINSEL.sItems[rgrBINSEL.itemIndex].c_str());
		out << str;
		out.width(10);
		out << "";
		out.width(2);
		out << "|";
		out.width(40);
		memset(str, '\0', sizeof(str));
		strcpy(str, rgrBINSEL.sItems[itmp1].c_str());
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
		bRez = false;
	};

	if (bWrAll)
	{
		// BSTART
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BSTART";
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
		memset(str, '\0', sizeof(str));
		if (BSTART_r0C_b00())
			strcpy(str, "1");
		else
			strcpy(str, "0");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// BSTATE
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BSTATE";
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
		memset(str, '\0', sizeof(str));
		if (BSTATE_r0D_b77())
			strcpy(str, "1");
		else
			strcpy(str, "0");
		out << str;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// BSIG[22:16]
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BSIG[22:16]";
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
		itmp = BSIG2216_r0D_b60();
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// BSIG[15:8]
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BSIG[15:8]";
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
		itmp = BSIG158_r0E_b70();
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;

		// BSIG[7:0]
		memset(str, '\0', sizeof(str));
		out.width(32);
		out << "| BSIG[7:0]";
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
		itmp = BSIG70_r0F_b70();
		out << itmp;
		out.width(10);
		out << "";
		out.width(1);
		out << "|";
		out << endl;
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

// ----------------------------------------------------------------------------
// Writes Register - Value format to the file.
// ----------------------------------------------------------------------------
void TxPLL_Module::MakeRVFFile(ofstream &out)
{
	int iRval;
	int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

	// *** To create file from GUI data instead of chip registers data. Start ***//
	MakeData(0xFF);
	memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
	// ***  To create file from GUI data instead of chip registers data. End  ***//

	// 0x00
	iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0xFF);
	out << iRval;
	out << endl;

	// 0x01
	iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0xFF);
	out << iRval;
	out << endl;

	// 0x02
	iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
	out << iRval;
	out << endl;

	// 0x03
	iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
	out << iRval;
	out << endl;

	// 0x04
	iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0xFF);
	out << iRval;
	out << endl;

	// 0x05
	iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
	out << iRval;
	out << endl;

	// 0x06
	iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
	out << iRval;
	out << endl;

	// 0x07
	iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
	out << iRval;
	out << endl;

	// 0x08
	iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
	out << iRval;
	out << endl;

	// 0x09
	iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xBF);
	out << iRval;
	out << endl;

	// 0x0A
	iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x3F);
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

	// 0x0E - Read Only

	// 0x0F - Read Only

};

// ----------------------------------------------------------------------------
// Writes RFIF register format to the file.
// ----------------------------------------------------------------------------
void TxPLL_Module::MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A)
{
	int iRval;
	int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

	// *** To create file from GUI data instead of chip registers data. Start ***//
	MakeData(0xFF);
	memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
	// ***  To create file from GUI data instead of chip registers data. End  ***//

	if (m_cMAddr == TxPllAddr)
		out << "echo \"Now programming the Lime Tx PLL\"" << endl << endl;
	else
		out << "echo \"Now programming the Lime Rx PLL\"" << endl << endl;

	// 0x00
	// out << "# Register(s): NINT[8:1]" << endl;
	iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x01
	// out << "# Register(s): NINT[0], NFRAC[22:16]" << endl;
	iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x02
	// out << "# Register(s): NFRAC[15:8]" << endl;
	iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x03
	// out << "# Register(s): NFRAC[7:0]" << endl;
	iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x04
	// out << "# Register(s): DITHEN, DITHN[2:0], EN, AUTOBYP, DECODE, MODE" << endl;
	iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x05
	// out << "# Register(s): SELVCO[2:0], FRANGE[2:0], SELOUT[1:0]" << endl;
	iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x06
	// out << "# Register(s): EN_PFD_UP, OEN_TSTD_SX, PASSEN_TSTOD_SD, ICHP[4:0]" << endl;
	iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x07
	// out << "# Register(s): BYPVCOREG, PDVCOREG, FSTVCOBG, OFFUP[4:0]" << endl;
	iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x08
	// out << "# Register(s): VOVCOREG[3:1], OFFDOWN[4:0]" << endl;
	iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x09
	// out << "# Register(s): VOVCOREG[0], VCOCAP[5:0]" << endl;
	iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xBF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0A
	// out << "# Register(s): BCODE[5:0]" << endl;
	iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x3F);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0B
	// out << "# Register(s): ACODE[3:0], PD_VCOCOMP_SX, ENLOBUF, ENLAMP, TRI" << endl;
	iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0C
	// out << "# Register(s): POL, PFDPD, ENFEEDDIV, PFDCLKP, BCLKSEL[1:0], BINSEL, BSTART" << endl;
	iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
	out << FRIF_DIR_W;
	// out << hex << uppercase << showbase << iRval;
	out << "0x" << hex << uppercase << noshowbase << iRval;
	// if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
	// else                      out << FRIF_SPI_A_RX;
	// out << endl;
	out << FRIF_SPI_A;
	out << endl;

	// 0x0D - Read Only

	// 0x0E - Read Only

	// 0x0F - Read Only

	if (m_cMAddr == TxPllAddr)
		out << endl << "echo \"Tx PLL programming complete\"" << endl << endl;
	else
		out << endl << "echo \"Rx PLL programming complete\"" << endl << endl;

};

// ---------------------------------------------------------------------------
// Sets configuration according to values received from the chip
// data reading is performed by Main_Module
// ---------------------------------------------------------------------------
bool TxPLL_Module::SetGUIUnderReadback()
{
	int itmp;
	bool bRez = true;
	int iNint;
	int iFrac;
	double dFreq;

	m_bAllowSend = false;

	// NINT[8:0]
	// itmp = 0;
	// itmp = m_psD.cDataR[0x00] & 0xFF;
	// itmp = itmp << 1;
	// itmp = itmp | ((m_psD.cDataR[0x01] & 0x80) >> 7);
	itmp = NINT();
	lblNint_info = itmp;
	iNint = itmp;

	// NFRAC[22:0]
	// itmp = 0;
	// itmp = 0x7F & m_psD.cDataR[0x01];
	// itmp = itmp << 8;
	// itmp = itmp | (0xFF & m_psD.cDataR[0x02]);
	// itmp = itmp << 8;
	// itmp = itmp | (0xFF & m_psD.cDataR[0x03]);
	itmp = NFRAC();
	lblNfrac_info = itmp;
	iFrac = itmp;

	// DITHEN
	itmp = DITHEN_r04_b77();
	chbDITHEN.checked = itmp;

	// DITHN[2:0]
	itmp = DITHN_r04_b64(); // itmp++;
	rgrDITHN.itemIndex = itmp;

	// EN
	itmp = EN_r04_b33();
	chbPwrPllMods.checked = itmp;

	// AUTOBYP
	itmp = AUTOBYP_r04_b22();
	chbAUTOBYP.checked = itmp;

	// DECODE
	itmp = DECODE_r04_b11();
	rgrDecode.itemIndex = itmp;

	// MODE
	itmp = MODE_r04_b00();
	rgrMODE.itemIndex = itmp;

	// SELVCO[2:0]
	itmp = SELVCO_r05_b75();
	switch (itmp)
	{
	case 0x00:
		rgrSELVCO.itemIndex = 0;
		break;
	case 0x04:
		rgrSELVCO.itemIndex = 1;
		break;
	case 0x05:
		rgrSELVCO.itemIndex = 2;
		break;
	case 0x06:
		rgrSELVCO.itemIndex = 3;
		break;
	case 0x07:
		rgrSELVCO.itemIndex = 4;
		break;
	default:
		rgrSELVCO.itemIndex = 4;
		bRez = false;
	};

	// FRANGE[2:0]
	itmp = FRANGE_r05_b42();
	dFreq = (double)iNint + ((double)iFrac / pow(2.0, 23));
	dFreq = (double)dFreq / (1000000000 / m_dRefF);
	switch (itmp)
	{
	case 0x00:
		rgrFRANGE.itemIndex = 0;
		break;
	case 0x04:
		rgrFRANGE.itemIndex = 1;
		dFreq = dFreq / 2.0;
		break;
	case 0x05:
		rgrFRANGE.itemIndex = 2;
		dFreq = dFreq / 4.0;
		break;
	case 0x06:
		rgrFRANGE.itemIndex = 3;
		dFreq = dFreq / 8.0;
		break;
	case 0x07:
		rgrFRANGE.itemIndex = 4;
		dFreq = dFreq / 16.0;
		break;
	default:
		rgrFRANGE.itemIndex = 4;
		dFreq = dFreq / 16.0;
		bRez = false;
	};
	dblDesFreq = dFreq;

	// SELOUT[1:0]
	itmp = SELOUT_r05_b10();
	rgrSELOUT.itemIndex = itmp;

	// EN_PFD_UP
	itmp = EN_PFD_UP_r06_b77();
	chbEN_PFD_UP.checked = itmp;

	// OEN_TSTD_SX
	itmp = OEN_TSTD_SX_r06_b66();
	chbOEN_TSTD_SX.checked = itmp;

	// PASSEN_TSTOD_SD
	itmp = PASSEN_TSTOD_SD_r06_b55();
	chbPASSEN_TSTOD_SD.checked = itmp;

	// ICHP[4:0]
	itmp = ICHP_r06_b40();
	rgrICHP.itemIndex = itmp;

	// BYPVCOREG
	itmp = BYPVCOREG_r07_b77();
	chbBYPVCOREG.checked = itmp;

	// PDVCOREG
	itmp = PDVCOREG_r07_b66();
	chbPDVCOREG.checked = itmp;

	// FSTVCOBG
	itmp = FSTVCOBG_r07_b55();
	chbFSTVCOBG.checked = itmp;

	// OFFUP[4:0]
	itmp = OFFUP_r07_b40();
	if (itmp > 24)
	{
		itmp = 24;
		bRez = false;
	}
	rgrOFFUP.itemIndex = itmp;

	// VOVCOREG[3:0]
	itmp = VOVCOREG();
	if (itmp > 0x0C)
	{
		itmp = 0x0C;
		bRez = false;
	}
	rgrVOVCOREG.itemIndex = itmp;

	// OFFDOWN[4:0]
	itmp = OFFDOWN_r08_b40();
	if (itmp > 24)
	{
		itmp = 24;
		bRez = false;
	}
	rgrOFFDOWN.itemIndex = itmp;

	// VCOCAP[5:0]
	itmp = VCOCAP_r09_b50();
	rgrVCOCAP.itemIndex = itmp;

	// VTUNE_H
	itmp = VTUNE_H_r0A_b77();
	if (itmp)
		lblVTUNE_H.set("1");
	else
		lblVTUNE_H.set("0");

	// VTUNE_L
	itmp = VTUNE_L_r0A_b66();
	if (itmp)
		lblVTUNE_L.set("1");
	else
		lblVTUNE_L.set("0");

	// BCODE[5:0]
	itmp = BCODE_r0A_b50();
	switch (itmp)
	{
	case 0x3F:
		rgrBCODE.itemIndex = 35 - 7;
		break;
	case 0x3E:
		rgrBCODE.itemIndex = 34 - 7;
		break;
	case 0x3C:
		rgrBCODE.itemIndex = 33 - 7;
		break;
	case 0x38:
		rgrBCODE.itemIndex = 32 - 7;
		break;
	case 0x39:
		rgrBCODE.itemIndex = 31 - 7;
		break;
	case 0x3B:
		rgrBCODE.itemIndex = 30 - 7;
		break;
	case 0x37:
		rgrBCODE.itemIndex = 29 - 7;
		break;
	case 0x36:
		rgrBCODE.itemIndex = 28 - 7;
		break;
	case 0x34:
		rgrBCODE.itemIndex = 27 - 7;
		break;
	case 0x30:
		rgrBCODE.itemIndex = 26 - 7;
		break;
	case 0x31:
		rgrBCODE.itemIndex = 25 - 7;
		break;
	case 0x33:
		rgrBCODE.itemIndex = 24 - 7;
		break;
	case 0x27:
		rgrBCODE.itemIndex = 23 - 7;
		break;
	case 0x26:
		rgrBCODE.itemIndex = 22 - 7;
		break;
	case 0x24:
		rgrBCODE.itemIndex = 21 - 7;
		break;
	case 0x20:
		rgrBCODE.itemIndex = 20 - 7;
		break;
	case 0x21:
		rgrBCODE.itemIndex = 19 - 7;
		break;
	case 0x23:
		rgrBCODE.itemIndex = 18 - 7;
		break;
	case 0x07:
		rgrBCODE.itemIndex = 17 - 7;
		break;
	case 0x06:
		rgrBCODE.itemIndex = 16 - 7;
		break;
	case 0x04:
		rgrBCODE.itemIndex = 15 - 7;
		break;
	case 0x00:
		rgrBCODE.itemIndex = 14 - 7;
		break;
	case 0x01:
		rgrBCODE.itemIndex = 13 - 7;
		break;
	case 0x03:
		rgrBCODE.itemIndex = 12 - 7;
		break;
	case 0x0F:
		rgrBCODE.itemIndex = 11 - 7;
		break;
	case 0x0E:
		rgrBCODE.itemIndex = 10 - 7;
		break;
	case 0x0C:
		rgrBCODE.itemIndex = 9 - 7;
		break;
	case 0x08:
		rgrBCODE.itemIndex = 8 - 7;
		break;
	case 0x09:
		rgrBCODE.itemIndex = 7 - 7;
		break;
	default:
		rgrBCODE.itemIndex = 35 - 7;
		bRez = false;
	};

	// ACODE[3:0]
	itmp = ACODE_r0B_b74();
	switch (itmp)
	{
	case 0x0F:
		rgrACODE.itemIndex = 7;
		break;
	case 0x0E:
		rgrACODE.itemIndex = 6;
		break;
	case 0x0C:
		rgrACODE.itemIndex = 5;
		break;
	case 0x08:
		rgrACODE.itemIndex = 4;
		break;
	case 0x00:
		rgrACODE.itemIndex = 3;
		break;
	case 0x01:
		rgrACODE.itemIndex = 2;
		break;
	case 0x03:
		rgrACODE.itemIndex = 1;
		break;
	case 0x07:
		rgrACODE.itemIndex = 0;
		break;
	default:
		rgrACODE.itemIndex = 7;
		bRez = false;
	};

	// PD_VCOCOMP_SX
	itmp = PD_VCOCOMP_SX_r0B_b33();
	chbPD_VCOCOMP_SX.checked = itmp;
	chbPD_VCOCOMP_SX.checked = !chbPD_VCOCOMP_SX.checked;

	// ENLOBUF
	itmp = ENLOBUF_r0B_b22();
	chbENLOBUF.checked = itmp;

	// ENLAMP
	itmp = ENLAMP_r0B_b11();
	chbENLAMP.checked = itmp;

	// TRI
	itmp = TRI_r0B_b00();
	chbTRI.checked = itmp;

	// POL
	itmp = POL_r0C_b77();
	chbPOL.checked = itmp;

	// PFDPD
	itmp = PFDPD_r0C_b66();
	chbPFDPD.checked = itmp;
	chbPFDPD.checked = !chbPFDPD.checked;

	// ENFEEDDIV
	itmp = ENFEEDDIV_r0C_b55();
	chbENFEEDDIV.checked = itmp;

	// PFDCLKP
	itmp = PFDCLKP_r0C_b44();
	chbPFDCLKP.checked = itmp;

	// BCLKSEL
	itmp = BCLKSEL_r0C_b32();
	if (itmp > 2)
	{
		itmp = 2;
		bRez = false;
	};
	rgrBCLKSEL.itemIndex = itmp;

	// BINSEL
	itmp = BINSEL_r0C_b11();
	rgrBINSEL.itemIndex = itmp;

	// BSTART
	itmp = BSTART_r0C_b00();

	// BSTATE
	//BIST_ShowState(BSTATE_r0D_b77());

	// BSIG
	BIST_ShowSignature(BSIG());

	m_bAllowSend = true;
	return bRez;
};

// ----------------------------------------------------------------------------
// Writes register map to the file. According to the customer wish.
// ----------------------------------------------------------------------------
void TxPLL_Module::MakeRegisterFile(ofstream &out)
{
	int itmp;

	// *** To create file from GUI data instead of chip registers data. Start ***//
	MakeData(0xFF);
	memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
	// ***  To create file from GUI data instead of chip registers data. End  ***//

	// PLL_NINT[8:1]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x10 MASK 07 : 00  =";
	else
		out << "REG 0x20 MASK 07 : 00  =";
	itmp = NINT81_r00_b70();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_NINT[8:1]";
	else
		out << "  RXPLL_NINT[8:1]";
	out << endl;

	// PLL_NINT[0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x11 MASK 07 : 07  =";
	else
		out << "REG 0x21 MASK 07 : 07  =";
	itmp = NINT00_r01_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_NINT[0]";
	else
		out << "  RXPLL_NINT[0]";
	out << endl;

	// PLL_NFRAC[22:16]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x11 MASK 06 : 00  =";
	else
		out << "REG 0x21 MASK 06 : 00  =";
	itmp = NFRAC2216_r01_b60();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_NFRAC[22:16]";
	else
		out << "  RXPLL_NFRAC[22:16]";
	out << endl;

	// PLL_NFRAC[15:8]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x12 MASK 07 : 00  =";
	else
		out << "REG 0x22 MASK 07 : 00  =";
	itmp = NFRAC158_r02_b70();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_NFRAC[15:8]";
	else
		out << "  RXPLL_NFRAC[15:8]";
	out << endl;

	// PLL_NFRAC[7:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x13 MASK 07 : 00  =";
	else
		out << "REG 0x23 MASK 07 : 00  =";
	itmp = NFRAC70_r03_b70();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_NFRAC[7:0]";
	else
		out << "  RXPLL_NFRAC[7:0]";
	out << endl;

	// DITHEN
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x14 MASK 07 : 07  =";
	else
		out << "REG 0x24 MASK 07 : 07  =";
	itmp = DITHEN_r04_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_DITHEN";
	else
		out << "  RXPLL_DITHEN";
	out << endl;

	// DITHN[2:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x14 MASK 06 : 04  =";
	else
		out << "REG 0x24 MASK 06 : 04  =";
	itmp = DITHN_r04_b64();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_DITHN";
	else
		out << "  RXPLL_DITHN";
	out << endl;

	// EN
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x14 MASK 03 : 03  =";
	else
		out << "REG 0x24 MASK 03 : 03  =";
	itmp = EN_r04_b33();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_EN";
	else
		out << "  RXPLL_EN";
	out << endl;

	// AUTOBYP
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x14 MASK 02 : 02  =";
	else
		out << "REG 0x24 MASK 02 : 02  =";
	itmp = AUTOBYP_r04_b22();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_AUTOBYP";
	else
		out << "  RXPLL_AUTOBYP";
	out << endl;

	// DECODE
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x14 MASK 01 : 01  =";
	else
		out << "REG 0x24 MASK 01 : 01  =";
	itmp = DECODE_r04_b11();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_DECODE";
	else
		out << "  RXPLL_DECODE";
	out << endl;

	// MODE
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x14 MASK 00 : 00  =";
	else
		out << "REG 0x24 MASK 00 : 00  =";
	itmp = MODE_r04_b00();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_MODE";
	else
		out << "  RXPLL_MODE";
	out << endl;

	// FREQSEL[7:2]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x15 MASK 07 : 02  =";
	else
		out << "REG 0x25 MASK 07 : 02  =";
	itmp = m_psD.cDataR[0x05] & 0xFC;
	itmp = itmp >> 2;
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_FREQSEL";
	else
		out << "  RXPLL_FREQSEL";
	out << endl;

	// SELOUT[1:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x15 MASK 01 : 00  =";
	else
		out << "REG 0x25 MASK 01 : 00  =";
	itmp = SELOUT_r05_b10();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_SELOUT";
	else
		out << "  RXPLL_SELOUT";
	out << endl;

	// EN_PFD_UP
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x16 MASK 07 : 07  =";
	else
		out << "REG 0x26 MASK 07 : 07  =";
	itmp = EN_PFD_UP_r06_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_EN_PFD_UP";
	else
		out << "  RXPLL_EN_PFD_UP";
	out << endl;

	// OEN_TSTD_SX
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x16 MASK 06 : 06  =";
	else
		out << "REG 0x26 MASK 06 : 06  =";
	itmp = OEN_TSTD_SX_r06_b66();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_OEN_TSTD_SX";
	else
		out << "  RXPLL_OEN_TSTD_SX";
	out << endl;

	// PASSEN_TSTOD_SD
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x16 MASK 05 : 05  =";
	else
		out << "REG 0x26 MASK 05 : 05  =";
	itmp = PASSEN_TSTOD_SD_r06_b55();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_PASSEN_TSTOD_SD";
	else
		out << "  RXPLL_PASSEN_TSTOD_SD";
	out << endl;

	// ICHP[4:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x16 MASK 04 : 00  =";
	else
		out << "REG 0x26 MASK 04 : 00  =";
	itmp = ICHP_r06_b40();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_ICHP";
	else
		out << "  RXPLL_ICHP";
	out << endl;

	// BYPVCOREG
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x17 MASK 07 : 07  =";
	else
		out << "REG 0x27 MASK 07 : 07  =";
	itmp = BYPVCOREG_r07_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BYPVCOREG";
	else
		out << "  RXPLL_BYPVCOREG";
	out << endl;

	// PDVCOREG
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x17 MASK 06 : 06  =";
	else
		out << "REG 0x27 MASK 06 : 06  =";
	itmp = PDVCOREG_r07_b66();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_PDVCOREG";
	else
		out << "  RXPLL_PDVCOREG";
	out << endl;

	// FSTVCOBG
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x17 MASK 05 : 05  =";
	else
		out << "REG 0x27 MASK 05 : 05  =";
	itmp = FSTVCOBG_r07_b55();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_FSTVCOBG";
	else
		out << "  RXPLL_FSTVCOBG";
	out << endl;

	// OFFUP[4:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x17 MASK 04 : 00  =";
	else
		out << "REG 0x27 MASK 04 : 00  =";
	itmp = OFFUP_r07_b40();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_OFFUP";
	else
		out << "  RXPLL_OFFUP";
	out << endl;

	// VOVCOREG[3:1]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x18 MASK 07 : 05  =";
	else
		out << "REG 0x28 MASK 07 : 05  =";
	itmp = VOVCOREG31_r08_b75();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_VOVCOREG[3:1]";
	else
		out << "  RXPLL_VOVCOREG[3:1]";
	out << endl;

	// OFFDOWN[4:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x18 MASK 04 : 00  =";
	else
		out << "REG 0x28 MASK 04 : 00  =";
	itmp = OFFDOWN_r08_b40();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_OFFDOWN";
	else
		out << "  RXPLL_OFFDOWN";
	out << endl;

	// VOVCOREG[0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x19 MASK 07 : 07  =";
	else
		out << "REG 0x29 MASK 07 : 07  =";
	itmp = VOVCOREG00_r09_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_VOVCOREG[0]";
	else
		out << "  RXPLL_VOVCOREG[0]";
	out << endl;

	// VCOCAP[5:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x19 MASK 05 : 00  =";
	else
		out << "REG 0x29 MASK 05 : 00  =";
	itmp = VCOCAP_r09_b50();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_VCOCAP[5:0]";
	else
		out << "  RXPLL_VCOCAP[5:0]";
	out << endl;

	// VTUNE_H
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1A MASK 07 : 07  =";
	else
		out << "REG 0x2A MASK 07 : 07  =";
	itmp = VTUNE_H_r0A_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_VTUNE_H";
	else
		out << "  RXPLL_VTUNE_H";
	out << endl;

	// VTUNE_L
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1A MASK 06 : 06  =";
	else
		out << "REG 0x2A MASK 06 : 06  =";
	itmp = VTUNE_L_r0A_b66();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_VTUNE_L";
	else
		out << "  RXPLL_VTUNE_L";
	out << endl;

	// BCODE[5:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1A MASK 05 : 00  =";
	else
		out << "REG 0x2A MASK 05 : 00  =";
	itmp = BCODE_r0A_b50();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BCODE[5:0]";
	else
		out << "  RXPLL_BCODE[5:0]";
	out << endl;

	// ACODE[3:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1B MASK 07 : 04  =";
	else
		out << "REG 0x2B MASK 07 : 04  =";
	itmp = ACODE_r0B_b74();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_ACODE[3:0]";
	else
		out << "  RXPLL_ACODE[3:0]";
	out << endl;

	// PD_VCOCOMP_SX
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1B MASK 03 : 03  =";
	else
		out << "REG 0x2B MASK 03 : 03  =";
	itmp = PD_VCOCOMP_SX_r0B_b33();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_PD_VCOCOMP_SX";
	else
		out << "  RXPLL_PD_VCOCOMP_SX";
	out << endl;

	// ENLOBUF
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1B MASK 02 : 02  =";
	else
		out << "REG 0x2B MASK 02 : 02  =";
	itmp = ENLOBUF_r0B_b22();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_ENLOBUF";
	else
		out << "  RXPLL_ENLOBUF";
	out << endl;

	// ENLAMP
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1B MASK 01 : 01  =";
	else
		out << "REG 0x2B MASK 01 : 01  =";
	itmp = ENLAMP_r0B_b11();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_ENLAMP";
	else
		out << "  RXPLL_ENLAMP";
	out << endl;

	// TRI
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1B MASK 00 : 00  =";
	else
		out << "REG 0x2B MASK 00 : 00  =";
	itmp = TRI_r0B_b00();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_TRI";
	else
		out << "  RXPLL_TRI";
	out << endl;

	// POL
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1C MASK 07 : 07  =";
	else
		out << "REG 0x2C MASK 07 : 07  =";
	itmp = POL_r0C_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_POL";
	else
		out << "  RXPLL_POL";
	out << endl;

	// PFDPD
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1C MASK 06 : 06  =";
	else
		out << "REG 0x2C MASK 06 : 06  =";
	itmp = PFDPD_r0C_b66();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_PFDPD";
	else
		out << "  RXPLL_PFDPD";
	out << endl;

	// ENFEEDDIV
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1C MASK 05 : 05  =";
	else
		out << "REG 0x2C MASK 05 : 05  =";
	itmp = ENFEEDDIV_r0C_b55();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_ENFEEDDIV";
	else
		out << "  RXPLL_ENFEEDDIV";
	out << endl;

	// PFDCLKP
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1C MASK 04 : 04  =";
	else
		out << "REG 0x2C MASK 04 : 04  =";
	itmp = PFDCLKP_r0C_b44();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_PFDCLKP";
	else
		out << "  RXPLL_PFDCLKP";
	out << endl;

	// BCLKSEL[1:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1C MASK 03 : 02  =";
	else
		out << "REG 0x2C MASK 03 : 02  =";
	itmp = BCLKSEL_r0C_b32();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BCLKSEL";
	else
		out << "  RXPLL_BCLKSEL";
	out << endl;

	// BINSEL
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1C MASK 01 : 01  =";
	else
		out << "REG 0x2C MASK 01 : 01  =";
	itmp = BINSEL_r0C_b11();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BINSEL";
	else
		out << "  RXPLL_BINSEL";
	out << endl;

	// BSTART
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1C MASK 00 : 00  =";
	else
		out << "REG 0x2C MASK 00 : 00  =";
	itmp = BSTART_r0C_b00();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BSTART";
	else
		out << "  RXPLL_BSTART";
	out << endl;

	// BSTATE
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1D MASK 07 : 07  =";
	else
		out << "REG 0x2D MASK 07 : 07  =";
	itmp = BSTATE_r0D_b77();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BSTATE";
	else
		out << "  RXPLL_BSTATE";
	out << endl;

	// BSIG[22:16]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1D MASK 06 : 00  =";
	else
		out << "REG 0x2D MASK 06 : 00  =";
	itmp = BSIG2216_r0D_b60();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BSIG[22:16]";
	else
		out << "  RXPLL_BSIG[22:16]";
	out << endl;

	// BSIG[15:8]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1E MASK 07 : 00  =";
	else
		out << "REG 0x2E MASK 07 : 00  =";
	itmp = BSIG158_r0E_b70();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BSIG[15:8]";
	else
		out << "  RXPLL_BSIG[15:8]";
	out << endl;

	// BSIG[7:0]
	out.width(24);
	out << left;
	if (m_cMAddr == TxPllAddr)
		out << "REG 0x1F MASK 07 : 00  =";
	else
		out << "REG 0x2F MASK 07 : 00  =";
	itmp = BSIG70_r0F_b70();
	out.width(6);
	out << right;
	out << itmp;
	if (m_cMAddr == TxPllAddr)
		out << "  TXPLL_BSIG[7:0]";
	else
		out << "  RXPLL_BSIG[7:0]";
	out << endl;
};

// ---------------------------------------------------------------------------
// Saves current configuration to ini file
// ---------------------------------------------------------------------------
void TxPLL_Module::SaveConf(ini_t *pini)
{
	char Sect[80];
//	itoa((int)m_cMAddr, Sect, 10);
sprintf(Sect, "%i", (int)m_cMAddr);
	pini->Create(Sect);

	pini->Set("txtDesFreq", dblDesFreq);

	pini->Set("chkDITHEN", chbDITHEN.checked);
	pini->Set("cmbDITHN", rgrDITHN.itemIndex);
	pini->Set("chbPwrPllMods", chbPwrPllMods.checked);
	pini->Set("chbAUTOBYP", chbAUTOBYP.checked);
	pini->Set("rgrDecode", rgrDecode.itemIndex);
	pini->Set("rgrMODE", rgrMODE.itemIndex);

	pini->Set("rgrSELVCO", rgrSELVCO.itemIndex);
	pini->Set("rgrFRANGE", rgrFRANGE.itemIndex);
	pini->Set("cmbSELOUT", rgrSELOUT.itemIndex);

	pini->Set("chbEN_PFD_UP", chbEN_PFD_UP.checked);
	pini->Set("chkOEN_TSTD_SX", chbOEN_TSTD_SX.checked);
	pini->Set("chkPASSEN_TSTOD_SD", chbPASSEN_TSTOD_SD.checked);
	pini->Set("cmbICHP", rgrICHP.itemIndex);

	pini->Set("chbBYPVCOREG", chbBYPVCOREG.checked);
	pini->Set("chbPDVCOREG", chbPDVCOREG.checked);
	pini->Set("chbFSTVCOBG", chbFSTVCOBG.checked);
	pini->Set("cmbOFFUP", rgrOFFUP.itemIndex);

	pini->Set("cmbVOVCOREG", rgrVOVCOREG.itemIndex);
	pini->Set("cmbOFFDOWN", rgrOFFDOWN.itemIndex);

	pini->Set("cmbVCOCAP", rgrVCOCAP.itemIndex);

	pini->Set("cmbBCODE", rgrBCODE.itemIndex);

	pini->Set("cmbACODE", rgrACODE.itemIndex);
	pini->Set("cmbPD_VCOCOMP_SX", chbPD_VCOCOMP_SX.checked);
	pini->Set("chkENLOBUF", chbENLOBUF.checked);
	pini->Set("chkENLAMP", chbENLAMP.checked);
	pini->Set("chkTRI", chbTRI.checked);

	pini->Set("chkPOL", chbPOL.checked);
	pini->Set("chkPFDPD", chbPFDPD.checked);
	pini->Set("chkENFEEDDIV", chbENFEEDDIV.checked);
	pini->Set("chkPFDCLKP", chbPFDCLKP.checked);
	pini->Set("rgrBCLKSEL", rgrBCLKSEL.itemIndex);
	pini->Set("rgrBINSEL", rgrBINSEL.itemIndex);

	char temp[16];
	sprintf(temp, "%f", m_dRefF);

	pini->Set("RefClk", temp);
};

// ---------------------------------------------------------------------------
// Loads configuration from ini file
// ---------------------------------------------------------------------------
void TxPLL_Module::ReadConf(ini_t *pini)
{
	char Sect[80];
//	itoa((int)m_cMAddr, Sect, 10);
sprintf(Sect, "%i", (int)m_cMAddr);
	pini->Select(Sect);

	m_bAllowSend = false;

	dblDesFreq = pini->Get("txtDesFreq", 5.21);

	chbDITHEN.checked = pini->Get("chkDITHEN", 1);
	rgrDITHN.itemIndex = pini->Get("cmbDITHN", 0);
	chbPwrPllMods.checked = pini->Get("chbPwrPllMods", 1);
	chbAUTOBYP.checked = pini->Get("chbAUTOBYP", 0);
	rgrDecode.itemIndex = pini->Get("rgrDecode", 0);
	rgrMODE.itemIndex = pini->Get("rgrMODE", 0);

	rgrSELVCO.itemIndex = pini->Get("rgrSELVCO", 2);
	rgrFRANGE.itemIndex = pini->Get("rgrFRANGE", 1);
	rgrSELOUT.itemIndex = pini->Get("cmbSELOUT", 1);

	chbEN_PFD_UP.checked = pini->Get("chbEN_PFD_UP", 1);
	chbOEN_TSTD_SX.checked = pini->Get("chkOEN_TSTD_SX", 0);
	chbPASSEN_TSTOD_SD.checked = pini->Get("chkPASSEN_TSTOD_SD", 0);
	rgrICHP.itemIndex = pini->Get("cmbICHP", 12);

	chbBYPVCOREG.checked = pini->Get("chbBYPVCOREG", 1);
	chbPDVCOREG.checked = pini->Get("chbPDVCOREG", 1);
	chbFSTVCOBG.checked = pini->Get("chbFSTVCOBG", 1);
	rgrOFFUP.itemIndex = pini->Get("cmbOFFUP", 0);

	rgrVOVCOREG.itemIndex = pini->Get("cmbVOVCOREG", 5);
	rgrOFFDOWN.itemIndex = pini->Get("cmbOFFDOWN", 0);

	rgrVCOCAP.itemIndex = pini->Get("cmbVCOCAP", 20);

	rgrBCODE.itemIndex = pini->Get("cmbBCODE", 5);

	rgrACODE.itemIndex = pini->Get("cmbACODE", 0);
	chbPD_VCOCOMP_SX.checked = pini->Get("cmbPD_VCOCOMP_SX", 1);
	chbENLOBUF.checked = pini->Get("chkENLOBUF", 1);
	chbENLAMP.checked = pini->Get("chkENLAMP", 1);
	chbTRI.checked = pini->Get("chkTRI", 0);

	chbPOL.checked = pini->Get("chkPOL", 0);
	chbPFDPD.checked = pini->Get("chkPFDPD", 0);
	chbENFEEDDIV.checked = pini->Get("chkENFEEDDIV", 1);
	chbPFDCLKP.checked = pini->Get("chkPFDCLKP", 1);
	rgrBCLKSEL.itemIndex = pini->Get("rgrBCLKSEL", 1);
	rgrBINSEL.itemIndex = pini->Get("rgrBINSEL", 2);

	m_dRefF = pini->Get("RefClk", 30720000);

	CalcPLLData();
	CalcIntPllData();

	// Not to override by CalcPLLData()
	rgrVCOCAP.itemIndex = pini->Get("rgrVCOCAP", 20);

	m_bAllowSend = true;
};

// ---------------------------------------------------------------------------

void TxPLL_Module::btnChooseVcoCapClick()
{
	ChooseVcoCap();
	if (m_bAllowSend)
	{
		MakeData(0x0C);
		pMainModule->CMAutoDownload(m_cMAddr);
	};
}

// ---------------------------------------------------------------------------
// sets, gets modules reference clock
// ---------------------------------------------------------------------------
void TxPLL_Module::SetRefClk(double RefClk)
{
	m_dRefF = RefClk;
};
double TxPLL_Module::GetRefClk()
{
	return m_dRefF;
};
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Functions for customer mode interface
// ---------------------------------------------------------------------------
void TxPLL_Module::CustSet_ActiveLOBuff(int ind)
{
	rgrSELOUT.itemIndex = ind;
	MakeData(0x80);
	pMainModule->CMAutoDownload(m_cMAddr);
};

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void TxPLL_Module::CustSet_LoadFrequency(double FreqGHz)
{
	dblDesFreq = FreqGHz;
	Calculate();
	Tune();
	char addr = m_cMAddr;
	pMainModule->UpdateInterface(UPDATE_INTERFACE_DATA, &addr);

};

void TxPLL_Module::PLLPowerOn(bool on)
{
	if(on)
	{
		m_bAllowSend = false;
		setDecode(0);
		setPwrPllMods(true);
		m_bAllowSend = true;

		MakeData(0x03);
		pMainModule->CMAutoDownload(m_cMAddr);
	}
	else
	{
		m_bAllowSend = false;
		setDecode(0);
		setPwrPllMods(false);
		m_bAllowSend = true;

		MakeData(0x03);
		pMainModule->CMAutoDownload(m_cMAddr);
	}
};

void TxPLL_Module::CustSet_cmbOFFUP(int Ind)
{
	setOFFUP(Ind);
};

// ---------------------------------------------------------------------------
//	Read VTune states from chip
// ---------------------------------------------------------------------------
void TxPLL_Module::btnReadVtuneClick()
{
	int State = GetVTuneState();
	switch (State)
	{
	case 0x00:
		lblVTUNE_H.set("0");
		lblVTUNE_L.set("0");
		break;

	case 0x01:
		lblVTUNE_H.set("0");
		lblVTUNE_L.set("1");
		break;

	case 0x02:
		lblVTUNE_H.set("1");
		lblVTUNE_L.set("0");
		break;

	default:
		lblVTUNE_H.set("1");
		lblVTUNE_L.set("1");
	};
}

// ---------------------------------------------------------------------------
// VTUNE_H, VTUNE_L, Returns
// 0        0        0x00
// 0        1        0x01
// 1        0        0x02
// 1        1        0x03 (ERROR)
// ---------------------------------------------------------------------------
int TxPLL_Module::GetVTuneState()
{
	int rez = 0;
	pMainModule->CMRead(0, m_cMAddr);

	// VTUNE_H
	// if(m_psD.cDataR[0x0A] & 0x80) rez = rez | 0x02;
	if (VTUNE_H_r0A_b77())
		rez = rez | 0x02;

	// VTUNE_L
	// if(m_psD.cDataR[0x0A] & 0x40) rez = rez | 0x01;
	if (VTUNE_L_r0A_b66())
		rez = rez | 0x01;
	return rez;
};

// ---------------------------------------------------------------------------
// Method according to Danny. Stops, when reaches 0.5V or 2.8V value of Vtune
// ---------------------------------------------------------------------------
void TxPLL_Module::CapAutoTune_D()
{
	bool bContinue;
	bool bPD_VCOCOMP_SX_state;
	int irgrDecode_state;

	// Remember the PD_VCOCOMP_SX state
	bPD_VCOCOMP_SX_state = chbPD_VCOCOMP_SX.checked;
	// Remember decode state
	irgrDecode_state = rgrDecode.itemIndex;

	// Check DECODE and enable if neccessary
	if (rgrDecode.itemIndex == 0)
	{
		setDecode(1);
	};

	// Check PD_VCOCOMP_SX and enable if neccessary
	if (!chbPD_VCOCOMP_SX.checked)
	{
		// chbPD_VCOCOMP_SX.checked = true;
		setPD_VCOCOMP_SX(true);
	};

	// Read VTUNE_H and VTUNE_L
	int State = GetVTuneState();
	switch (State)
	{
		// VTUNE_H, VTUNE_L, Value
		// 0        0      0x00
	case 0x00:
		// lblVTUNE_H->Caption = "0";
		// lblVTUNE_L->Caption = "0";
		lblAutoTuneStatus.set("0 - OK");
		break;

		// VTUNE_H, VTUNE_L, Value
		// 0        1      0x01
	case 0x01:
		// lblVTUNE_H->Caption = "0";
		// lblVTUNE_L->Caption = "1";
		bContinue = true;
		do
		{
			State = GetVTuneState();
			if ((State != 0x00) && (rgrVCOCAP.itemIndex > 0))
			{
				rgrVCOCAP.itemIndex--;
				setVCOCAP(rgrVCOCAP.itemIndex);
			}
			else
			{
				bContinue = false;
			};
		}
		while (bContinue);

		if (State == 0x00)
		{
			lblAutoTuneStatus.set("1 - OK");
		}
		else
		{
			lblAutoTuneStatus.set("1 - Err");
		};
		break;

		// VTUNE_H, VTUNE_L, Value
		// 1        0      0x02
	case 0x02:
		// lblVTUNE_H->Caption = "1";
		// lblVTUNE_L->Caption = "0";
		bContinue = true;
		do
		{
			State = GetVTuneState();
			if ((State != 0x00) && (rgrVCOCAP.itemIndex < 63))
			{
				rgrVCOCAP.itemIndex++;
				setVCOCAP(rgrVCOCAP.itemIndex);
			}
			else
			{
				bContinue = false;
			};
		}
		while (bContinue);

		if (State == 0x00)
		{
			lblAutoTuneStatus.set("2 - OK");
		}
		else
		{
			lblAutoTuneStatus.set("2 - Err");
		};
		break;

		// VTUNE_H, VTUNE_L, Value
		// 1        1      0x03 (ERROR)
	default:
		// lblVTUNE_H->Caption = "1";
		// lblVTUNE_L->Caption = "1";
		lblAutoTuneStatus.set("3 - Err");
	};

	// Set back PD_VCOCOMP_SX if neccessary
	if (!bPD_VCOCOMP_SX_state)
	{
		// chbPD_VCOCOMP_SX.checked = false;
		setPD_VCOCOMP_SX(false);
	};

	// Set back DECODE if neccessary
	if (irgrDecode_state == 0)
	{
		// rgrDecode.itemIndex = 0;
		setDecode(0);
	};
};

// ---------------------------------------------------------------------------
// Increments VCOCAP until given state, outputs state results to textlog
// ---------------------------------------------------------------------------
bool TxPLL_Module::CapIncrement(int UntilState, TextLog *VcoCapLog)
{
	bool bContinue;
	int CurrentState;

	if (VcoCapLog)
		VcoCapLog->AddLine("=== Start CAP Incrementing ===");

	bContinue = true;
	do
	{
		stringstream Str;
		Str << "State = ";
		// Sleep(10);
		CurrentState = GetVTuneState();
		Str << CurrentState;
		if ((CurrentState != UntilState) && (rgrVCOCAP.itemIndex < 63))
		{
			rgrVCOCAP.itemIndex++;
			setVCOCAP(rgrVCOCAP.itemIndex);
		}
		else
		{
			bContinue = false;
		};
		Str << "; CAP = ";
		Str << rgrVCOCAP.itemIndex;
		if (VcoCapLog)
			VcoCapLog->AddLine(Str.str());
	}
	while (bContinue);

	if (VcoCapLog)
		VcoCapLog->AddLine("=== Stop CAP Incrementing ===");

	if (CurrentState == UntilState)
		return true;
	else
		return false;
};

// ---------------------------------------------------------------------------
// Decrements VCOCAP until given state, outputs state results to textlog
// ---------------------------------------------------------------------------
bool TxPLL_Module::CapDecrement(int UntilState, TextLog *VcoCapLog)
{
	bool bContinue;
	int CurrentState;

	if (VcoCapLog)
		VcoCapLog->AddLine("=== Start CAP Decrementing ===");

	bContinue = true;
	do
	{
		stringstream Str;
		Str << "State = ";
		// Sleep(10);
		CurrentState = GetVTuneState();
		Str << CurrentState;
		if ((CurrentState != UntilState) && (rgrVCOCAP.itemIndex > 0))
		{
			rgrVCOCAP.itemIndex--;
			setVCOCAP(rgrVCOCAP.itemIndex);
		}
		else
		{
			bContinue = false;
		};
		Str << "; CAP = ";
		Str << rgrVCOCAP.itemIndex;
		if (VcoCapLog)
			VcoCapLog->AddLine(Str.str());
	}
	while (bContinue);

	if (VcoCapLog)
		VcoCapLog->AddLine("=== Stop CAP Decrementing ===");

	if (CurrentState == UntilState)
		return true;
	else
		return false;
};

// ---------------------------------------------------------------------------
// Method according to Srdjan. Finds Cap values for 0.5V and 2.5V value of
// Vtune and then calculates Cap value for Vtune 1.5V.
// ---------------------------------------------------------------------------
int TxPLL_Module::CapAutoTune_S(TextLog *dVcoCapLog)
{
	bool bContinue;
	bool bPD_VCOCOMP_SX_state;
	int irgrDecode_state;
	int iInitialCap;
	int iCl;
	int iCh;
	int CapState;
	int Result;
	string Str;

	// ------ Remember Controls state. Begin. ---------------------------------------
	/* For 6002D version
	 //Remember the PD_VCOCOMP_SX state
	 bPD_VCOCOMP_SX_state = chbPD_VCOCOMP_SX.checked;
	 //Remember decode state
	 irgrDecode_state = rgrDecode.itemIndex;

	 //Check DECODE and enable if neccessary
	 if(rgrDecode.itemIndex == 0)
	 {
	 rgrDecode.itemIndex = 1;
	 setDecode(Application);
	 };

	 //Check PD_VCOCOMP_SX and enable if neccessary
	 if(!chbPD_VCOCOMP_SX.checked)
	 {
	 chbPD_VCOCOMP_SX.checked = true;
	 setPD_VCOCOMP_SX(Application);
	 };
	 */
	// ------ Remember Controls state. End. -----------------------------------------

	// ------ Algorithm. Begin. -----------------------------------------------------
	// Read VTUNE_H and VTUNE_L
	CapState = GetVTuneState();
	iInitialCap = rgrVCOCAP.itemIndex;
	Result = 0;

	switch (CapState)
	{
		// VTUNE_H, VTUNE_L, Value
		// 0        0      0x00
	case 0x00:
		// lblVTUNE_H->Caption = "0";
		// lblVTUNE_L->Caption = "0";

		Result = 0x10;
		// Decrement Cap until H=1, L=0
		if (!CapDecrement(0x02, dVcoCapLog))
		{
			Result += 0x02;
			// break;
		};
		iCh = rgrVCOCAP.itemIndex;

		// Go to initial value for speeding things up.
		rgrVCOCAP.itemIndex = iInitialCap;
		// setVCOCAP(Application);

		// Increment Cap until H=0, L=1
		if (!CapIncrement(0x01, dVcoCapLog))
		{
			Result += 0x01;
			// break;
		};
		iCl = rgrVCOCAP.itemIndex;
		break;

		// VTUNE_H, VTUNE_L, Value
		// 0        1      0x01
	case 0x01:
		// lblVTUNE_H->Caption = "0";
		// lblVTUNE_L->Caption = "1";

		Result = 0x20;
		// Decrement Cap until H=0, L=0
		if (!CapDecrement(0x00, dVcoCapLog))
		{
			Result += 0x04;
			// break;
		};
		iCl = rgrVCOCAP.itemIndex;
		// Decrement Cap until H=1, L=0
		if (!CapDecrement(0x02, dVcoCapLog))
		{
			Result += 0x02;
			// break;
		};
		iCh = rgrVCOCAP.itemIndex;
		break;

		// VTUNE_H, VTUNE_L, Value
		// 1        0      0x02
	case 0x02:
		// lblVTUNE_H->Caption = "1";
		// lblVTUNE_L->Caption = "0";

		Result = 0x30;
		// Increment Cap until H=0, L=0
		if (!CapIncrement(0x00, dVcoCapLog))
		{
			Result += 0x04;
			// break;
		};
		iCh = rgrVCOCAP.itemIndex;
		// Increment Cap until H=0, L=1
		if (!CapIncrement(0x01, dVcoCapLog))
		{
			Result += 0x01;
			// break;
		};
		iCl = rgrVCOCAP.itemIndex;
		break;

		// VTUNE_H, VTUNE_L, Value
		// 1        1      0x03 (ERROR)
	default:
		// lblVTUNE_H->Caption = "1";
		// lblVTUNE_L->Caption = "1";
		Result = 7;
	};

	if (Result != 7) // Values are OK, calculate new Cap Value
	{
		// rgrVCOCAP.itemIndex = (int)(((2.0-2.5)*(iCh-iCl)/(2.5-0.5)) + iCh + 0.5);
		setVCOCAP((int)(((2.0 - 2.5)*(iCh - iCl) / (2.5 - 0.5)) + iCh + 0.5));
	}
	else // Error occuread. Set Cap Value to initial.
	{
		// rgrVCOCAP.itemIndex = iInitialCap;
		setVCOCAP(iInitialCap);
	};

	// ------ Algorithm. End. -------------------------------------------------------

	// ------ Set Back Controls state. Begin. ---------------------------------------
	/* For 6002D version
	 //Set back PD_VCOCOMP_SX if neccessary
	 if(!bPD_VCOCOMP_SX_state)
	 {
	 chbPD_VCOCOMP_SX.checked = false;
	 setPD_VCOCOMP_SX(Application);
	 };

	 //Set back DECODE if neccessary
	 if(irgrDecode_state == 0)
	 {
	 rgrDecode.itemIndex = 0;
	 setDecode(Application);
	 };
	 */
	// ------ Set Back Controls state. End. -----------------------------------------


	if ((Result == 0x10) || (Result == 0x20) || (Result == 0x30))
	{
		char ctemp[20];
		dVcoCapLog->AddLine("VCO Cap Tuning successful.");
		Str = "Cap value for Vtuning 0.5V = ";
		sprintf(ctemp, "%i", iCl);
		Str += ctemp;
		dVcoCapLog->AddLine(Str);
		Str = "Cap value for Vtuning 2.5V = ";
		sprintf(ctemp, "%i", iCh);
		Str += ctemp;
		dVcoCapLog->AddLine(Str);
		Str = "Selected Cap value for Vtuning 1.5V = ";
		sprintf(ctemp, "%i", rgrVCOCAP.itemIndex);
		Str += ctemp;
		dVcoCapLog->AddLine(Str);
		Str = "Initial Cap value was = ";
		sprintf(ctemp, "%i", iInitialCap);
		Str += ctemp;
		dVcoCapLog->AddLine(Str);
	}
	else
	{
		char ctemp[20];
		if (Result == 7)
		{
			dVcoCapLog->AddLine("VCO Cap Tuning UNSUCCESSFUL.");
			Str = "Initial Cap value = ";
			sprintf(ctemp, "%i", iInitialCap);
			Str += ctemp;
			dVcoCapLog->AddLine(Str);
			Str = "Initial comparator value: VTUNE_L = 1; VTUNE_H = 1.";
			dVcoCapLog->AddLine(Str);
			dVcoCapLog->AddLine("");
			dVcoCapLog->AddLine("Check please SPI cable, connecion etc.");
		}
		else
		{
			dVcoCapLog->AddLine("VCO Cap Tuning ISSUES.");
			Str = "Initial Cap value = ";
			sprintf(ctemp, "%i", iInitialCap);
			Str += ctemp;
			dVcoCapLog->AddLine(Str);

			Str = "Initial comparator value: ";
			if (CapState == 0x00)
				Str += "VTUNE_L = 0; VTUNE_H = 0.";
			else if (CapState == 0x01)
				Str += "VTUNE_L = 0; VTUNE_H = 1.";
			else if (CapState == 0x02)
				Str += "VTUNE_L = 1; VTUNE_H = 0.";
			else
				Str += "VTUNE_L = 1; VTUNE_H = 1.";
			dVcoCapLog->AddLine(Str);

			if ((Result & 0x01) == 0x01)
			{
				Str = "Issue: Can not reach state, where VTUNE_L = 1; VTUNE_H = 0.";
				dVcoCapLog->AddLine(Str);
			};
			if ((Result & 0x02) == 0x02)
			{
				Str = "Issue: Can not reach state, where VTUNE_L = 0; VTUNE_H = 1.";
				dVcoCapLog->AddLine(Str);
			};
			if ((Result & 0x04) == 0x04)
			{
				Str = "Issue: Can not reach state, where VTUNE_L = 0; VTUNE_H = 0.";
				dVcoCapLog->AddLine(Str);
			};
		};
	};
	return Result;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void TxPLL_Module::Tune()
{
	bool tempAutodownload = pMainModule->getAutoDownload();
	pMainModule->setAutoDownload(true);
	if(dlgVcoCapLog)
	{
		delete dlgVcoCapLog;
		dlgVcoCapLog = new TextLog();
	}
	LookForCap(dlgVcoCapLog);
	char addr = m_cMAddr;
	pMainModule->UpdateInterface(UPDATE_INTERFACE_DATA, &addr);
	pMainModule->setAutoDownload(tempAutodownload);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int TxPLL_Module::LookForCap(TextLog *dVcoCapLog)
{
	int iCap00;
	int iCap63;
	int iCapTuneRes;
	int iInitCap;
	int iInitVco;

	// Remember the initial states of CAP and VCO
	iInitCap = rgrVCOCAP.itemIndex;
	iInitVco = rgrSELVCO.itemIndex;

	// for(int i=4; i>=1; i--)
	for (int i = 1; i <= 4; i++)
	{
		stringstream Str;
		Str << "=== Trying VCO Nr. ";
		Str << (5 - i);
		Str << " ===";
		dVcoCapLog->AddLine(Str.str());
		Str.str("");

		// Choose VCO
		//rgrSELVCO.itemIndex = i;
		setSELVCO(i);

		// Set CAP to '0'
		// rgrVCOCAP.itemIndex = 0;
		setVCOCAP(0);

		// See what the values of Vh and Vl are
		iCap00 = GetVTuneState();

		// Set CAP to '63'
		// rgrVCOCAP.itemIndex = 63;
		setVCOCAP(63);

		// See what are the values of Vh and Vl
		iCap63 = GetVTuneState();

		Str << "Vtune for CAP=0 is ";
		Str << iCap00;
		dVcoCapLog->AddLine(Str.str());
		Str.str("");
		Str << "Vtune for CAP=63 is ";
		Str << iCap63;
		dVcoCapLog->AddLine(Str.str());
		Str.str("");

		if ((rgrSELVCO.itemIndex == 4) && (iCap00 == 0x02) && (iCap63 == 0x02))
		{
			break;
		};

		if ((iCap00 == 0x02) && (iCap63 == 0x01))
		{
			dVcoCapLog->AddLine("VCO can deliver required frequency.");
			dVcoCapLog->AddLine("Starting Procedure.");

			// Set CAP in the middle of the range
			// rgrVCOCAP.itemIndex = 31;
			setVCOCAP(31);

			// Try to Tune
			iCapTuneRes = CapAutoTune_S(dVcoCapLog);

			Str << "Selected CAP = ";
			Str << rgrVCOCAP.itemIndex;
			dVcoCapLog->AddLine(Str.str());
			Str.str("");

			return iCapTuneRes;
		};
		dVcoCapLog->AddLine("VCO is not suitable.");
		dVcoCapLog->AddLine("");
	};

	dVcoCapLog->AddLine("Any VCO can not deliver required frequency.");
	dVcoCapLog->AddLine("Communication problems?");
	dVcoCapLog->AddLine("Check please SPI cable, connecion etc.");
	dVcoCapLog->AddLine("Setting VCO and CAP back to initial values");

	// Set CAP and VCO to initial values
	// rgrVCOCAP.itemIndex = iInitCap;
	setVCOCAP(iInitCap);
	// rgrSELVCO.itemIndex = iInitVco;
	setSELVCO(iInitVco);

	return 0;
};

// ---------------------------------------------------------------------------
// Enables VCO TUNE comparators
// Selects required VCO and CAP
// Returns VCO TUNE comparator values
// ---------------------------------------------------------------------------
int TxPLL_Module::GetVTuneState(int vco, int cap)
{
	int iVCOState;
	int iCAPState;
	int result;

	// Remember VCO and CAP
	iVCOState = rgrSELVCO.itemIndex;
	iCAPState = rgrVCOCAP.itemIndex;

	// Set VCO
	//rgrSELVCO.itemIndex = vco;
	setSELVCO(vco);

	// Set CAP
	// rgrVCOCAP.itemIndex = cap;
	setVCOCAP(cap);

	result = GetVTuneState();

	// Restore VCO and CAP
	//rgrSELVCO.itemIndex = iVCOState;
	setSELVCO(iVCOState);
	// rgrVCOCAP.itemIndex = iCAPState;
	setVCOCAP(iCAPState);

	return result;
};

// ---------------------------------------------------------------------------
// Functions for register testing
// ---------------------------------------------------------------------------
void TxPLL_Module::RT_SetTestMask(char Mask)
{
	MakeWriteAll();
	for (int i = 0; i < m_psD.iToW; i++)
	{
		m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
	};
	pMainModule->CMAutoDownload(m_cMAddr);
};

// ---------------------------------------------------------------------------
// Reads BIST state from chip and returns result
// ---------------------------------------------------------------------------
bool TxPLL_Module::BIST_GetState()
{
	pMainModule->CMRead(0, m_cMAddr);
	return (bool)BSTATE_r0D_b77();
};

string TxPLL_Module::getBIST_Signature()
{
	return lblBSIG.caption;
}

// ---------------------------------------------------------------------------
unsigned int TxPLL_Module::BIST_GetSignature()
{
	pMainModule->CMRead(0, m_cMAddr);
	return (unsigned int) BSIG();
};

// ---------------------------------------------------------------------------
void TxPLL_Module::BIST_ShowSignature(int Signature)
{
	// lblBSIG->Caption = IntToHex(Signature, 6);
	char ctmp[10];

	if (Signature == 0x1B256D)
	{
		memset(ctmp, '\0', 10);
		sprintf(ctmp, "%X", Signature);
		lblBSIG.set("0x" + string(ctmp) + " - OK");
	}
	else
	{
		memset(ctmp, '\0', 10);
		sprintf(ctmp, "%X", Signature);
		lblBSIG.set("0x" + string(ctmp) + " - Failed");
	};
};

// ---------------------------------------------------------------------------
void TxPLL_Module::ReadBISTSignature()
{
	int iBS = BIST_GetSignature();
	BIST_ShowSignature(iBS);
}

// ---------------------------------------------------------------------------
// Activate start BIST command and the deactivate.
// ---------------------------------------------------------------------------
void TxPLL_Module::BIST_Start()
{
	char btmp;

	// ======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	// POL
	btmp = chbPOL.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDPD
	btmp = chbPFDPD.checked == true ? 0 : 1;
	btmp = btmp << 6;
	m_psD.cDataW[0x0C] |= btmp;
	// ENFEEDDIV
	btmp = chbENFEEDDIV.checked == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDCLKP
	btmp = chbPFDCLKP.checked == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x0C] |= btmp;
	// BCLKSEL
	btmp = (char)(rgrBCLKSEL.itemIndex & 0x03);
	btmp = btmp << 2;
	m_psD.cDataW[0x0C] |= btmp;
	// BINSEL
	btmp = (char)(rgrBINSEL.itemIndex & 0x01);
	btmp = btmp << 1;
	m_psD.cDataW[0x0C] |= btmp;
	// BSTART
	btmp = 0x00; // DEACTIVATE START BIST
	btmp = btmp << 0;
	m_psD.cDataW[0x0C] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x0C;
	pMainModule->CMAutoDownload(m_cMAddr);

	// ======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	// POL
	btmp = chbPOL.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDPD
	btmp = chbPFDPD.checked == true ? 0 : 1;
	btmp = btmp << 6;
	m_psD.cDataW[0x0C] |= btmp;
	// ENFEEDDIV
	btmp = chbENFEEDDIV.checked == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDCLKP
	btmp = chbPFDCLKP.checked == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x0C] |= btmp;
	// BCLKSEL
	btmp = (char)(rgrBCLKSEL.itemIndex & 0x03);
	btmp = btmp << 2;
	m_psD.cDataW[0x0C] |= btmp;
	// BINSEL
	btmp = (char)(rgrBINSEL.itemIndex & 0x01);
	btmp = btmp << 1;
	m_psD.cDataW[0x0C] |= btmp;
	// BSTART
	btmp = 0x01; // START BIST!!!
	btmp = btmp << 0;
	m_psD.cDataW[0x0C] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x0C;
	pMainModule->CMAutoDownload(m_cMAddr);

	// ======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	// POL
	btmp = chbPOL.checked == true ? 1 : 0;
	btmp = btmp << 7;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDPD
	btmp = chbPFDPD.checked == true ? 0 : 1;
	btmp = btmp << 6;
	m_psD.cDataW[0x0C] |= btmp;
	// ENFEEDDIV
	btmp = chbENFEEDDIV.checked == true ? 1 : 0;
	btmp = btmp << 5;
	m_psD.cDataW[0x0C] |= btmp;
	// PFDCLKP
	btmp = chbPFDCLKP.checked == true ? 1 : 0;
	btmp = btmp << 4;
	m_psD.cDataW[0x0C] |= btmp;
	// BCLKSEL
	btmp = (char)(rgrBCLKSEL.itemIndex & 0x03);
	btmp = btmp << 2;
	m_psD.cDataW[0x0C] |= btmp;
	// BINSEL
	btmp = (char)(rgrBINSEL.itemIndex & 0x01);
	btmp = btmp << 1;
	m_psD.cDataW[0x0C] |= btmp;
	// BSTART
	btmp = 0x00; // DEACTIVATE START BIST
	btmp = btmp << 0;
	m_psD.cDataW[0x0C] |= btmp;

	m_psD.iToW = 1;
	m_psD.iWInd[0] = 0x0C;
	pMainModule->CMAutoDownload(m_cMAddr);
};

// ---------------------------------------------------------------------------
// returns output frequency in GHz
// ---------------------------------------------------------------------------
double TxPLL_Module::getFrequency()
{
	return dblDesFreq;
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Procedure used from Main form, when calibrating LPF CAL Core
// and Ref frequency is not 40MHz
// ---------------------------------------------------------------------------
void TxPLL_Module::SetPLLTo320MHz()
{
	m_F320M_Data.F320M_rgrDecode = rgrDecode.itemIndex;
	m_F320M_Data.F320M_chbPwrPllMods = chbPwrPllMods.checked;
	m_F320M_Data.F320M_rgrMODE = rgrMODE.itemIndex;
	m_F320M_Data.F320M_cmbVCOCAP = rgrVCOCAP.itemIndex;
	m_F320M_Data.F320M_rgrSELVCO = rgrSELVCO.itemIndex;
	m_F320M_Data.F320M_rgrFRANGE = rgrFRANGE.itemIndex;
	m_F320M_Data.F320M_txtDesFreq = dblDesFreq;

	//rgrDecode.itemIndex = 0;
	setDecode(0);
	//chbPwrPllMods.checked = true;
	setPwrPllMods(true);
	//rgrMODE.itemIndex = 0;
	setMODE(0);
	dblDesFreq = 0.32;
	Calculate();
};

// ---------------------------------------------------------------------------
// Restores configuration settings changed by SetPLLTo320MHz()
// ---------------------------------------------------------------------------
void TxPLL_Module::RestoreAfterSetPLLTo320MHz()
{
	dblDesFreq = m_F320M_Data.F320M_txtDesFreq;
	Calculate();

	setDecode(m_F320M_Data.F320M_rgrDecode);
	setPwrPllMods(m_F320M_Data.F320M_chbPwrPllMods);

	setMODE(m_F320M_Data.F320M_rgrMODE);
	setVCOCAP(m_F320M_Data.F320M_cmbVCOCAP);
	setSELVCO(m_F320M_Data.F320M_rgrSELVCO);
	setFRANGE(m_F320M_Data.F320M_rgrFRANGE);
};
