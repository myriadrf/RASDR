// -----------------------------------------------------------------------------
// FILE: 		TxRf_Module.cpp
// DESCRIPTION:	TxRF control user interface
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include "TxRf_Module.h"
#include "ConnectionManager.h"
#include "Main_Module.h"
//---------------------------------------------------------------------------

//0x0
#define           EN_r00_b11() ((m_psD.cDataR[0x00] & 0x02) >> 1)
#define       DECODE_r00_b00() ((m_psD.cDataR[0x00] & 0x01) >> 0)
//0x1
#define     VGA1GAIN_r01_b40() ((m_psD.cDataR[0x01] & 0x1F) >> 0)
//0x2
#define     VGA1DC_I_r02_b70() ((m_psD.cDataR[0x02] & 0xFF) >> 0)
//0x3
#define     VGA1DC_Q_r03_b70() ((m_psD.cDataR[0x03] & 0xFF) >> 0)
//0x4
#define        PA_EN_r04_b42() ((m_psD.cDataR[0x04] & 0x1C) >> 3) //Becouse LSB is not used
//#define    PD_DRVAUX_r04_b11() ((m_psD.cDataR[0x04] & 0x02) >> 1)
//#define     PD_PKDET_r04_b00() ((m_psD.cDataR[0x04] & 0x01) >> 0)
#define    PD_DRVAUX_r04_b11_v0() ((m_psD.cDataR[0x04] & 0x02) >> 1)  //When Ver=2, Rev=2, Mask=0
#define    PD_DRVAUX_r04_b22_v1() ((m_psD.cDataR[0x04] & 0x04) >> 2)  //When Ver=2, Rev=2, Mask=1
#define     PD_PKDET_r04_b00_v0() ((m_psD.cDataR[0x04] & 0x01) >> 0)  //When Ver=2, Rev=2, Mask=0
#define     PD_PKDET_r0E_b77_v1() ((m_psD.cDataR[0x0E] & 0x80) >> 7)  //When Ver=2, Rev=2, Mask=1

//0x5
#define     VGA2GAIN_r05_b73() ((m_psD.cDataR[0x05] & 0xF8) >> 3)
//#define         ENVD_r05_b21() ((m_psD.cDataR[0x05] & 0x06) >> 1)
#define         ENVD_r05_b22() ((m_psD.cDataR[0x05] & 0x04) >> 2)
//#define         ENVD_r05_b00() ((m_psD.cDataR[0x05] & 0x01) >> 0)
#define         ENVD_r05_b10() ((m_psD.cDataR[0x05] & 0x03) >> 0)
//0x6
#define        PKDBW_r06_b74() ((m_psD.cDataR[0x06] & 0xF0) >> 4)
#define     LOOPBBEN_r06_b32() ((m_psD.cDataR[0x06] & 0x0C) >> 2)
//#define    LOOPPKDEN_r06_b22() ((m_psD.cDataR[0x06] & 0x04) >> 2)
#define    FST_PKDET_r06_b11() ((m_psD.cDataR[0x06] & 0x02) >> 1)
#define FST_TXHFBIAS_r06_b00() ((m_psD.cDataR[0x06] & 0x01) >> 0)
//0x7
#define  ICT_TXLOBUF_r07_b74() ((m_psD.cDataR[0x07] & 0xF0) >> 4)
#define  VBCAS_TXDRV_r07_b30() ((m_psD.cDataR[0x07] & 0x0F) >> 0)
//0x8
#define    ICT_TXMIX_r08_b40() ((m_psD.cDataR[0x08] & 0x1F) >> 0)
//0x9
#define    ICT_TXDRV_r09_b40() ((m_psD.cDataR[0x09] & 0x1F) >> 0)
//0xA
#define    PW_VGA1_I_r0A_b44() ((m_psD.cDataR[0x0A] & 0x10) >> 4)
#define    PW_VGA1_Q_r0A_b33() ((m_psD.cDataR[0x0A] & 0x08) >> 3)
#define     PD_TXDRV_r0A_b22() ((m_psD.cDataR[0x0A] & 0x04) >> 2)
#define   PD_TXLOBUF_r0A_b11() ((m_psD.cDataR[0x0A] & 0x02) >> 1)
#define     PD_TXMIX_r0A_b00() ((m_psD.cDataR[0x0A] & 0x01) >> 0)
//0xB
#define    VGA1GAINT_r0B_b70() ((m_psD.cDataR[0x0B] & 0xFF) >> 0)
//0xC
#define     G_TXVGA2_r0C_b81() ((m_psD.cDataR[0x0C] & 0xFF) >> 0)
//0xD
#define     G_TXVGA2_r0D_b77() ((m_psD.cDataR[0x0D] & 0x80) >> 7)
//Combination of 0xC and 0xD addresses
#define     G_TXVGA2() ((G_TXVGA2_r0C_b81() << 1) + G_TXVGA2_r0D_b77())

#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A ",20"

//---------------------------------------------------------------------------
TxRf_Module::TxRf_Module()
{
	m_cVer = 2;
	m_cRev = 2;
	m_cMask = 0;
	pMainModule = NULL;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
TxRf_Module::~TxRf_Module(void)
{
	delete[] m_psD.cCmdW;
	delete[] m_psD.cDataW;
	delete[] m_psD.cCmdR;
	delete[] m_psD.cDataR;
	delete[] m_psD.iRInd;
	delete[] m_psD.iWInd;
	delete[] m_psD.cTestMap; //RT//
}

char TxRf_Module::getAddr()
{
	return m_cMAddr;
}

//---------------------------------------------------------------------------
void TxRf_Module::Initialize(Main_Module *pMain, char MAddr)
{
	pMainModule = pMain;
	m_cMAddr = MAddr;

	m_psD.iLen = TxRFLen;
	m_psD.cCmdW = new char[m_psD.iLen];
	m_psD.cDataW = new char[m_psD.iLen];
	m_psD.cCmdR = new char[m_psD.iLen];
	m_psD.cDataR = new char[m_psD.iLen];
	m_psD.iRInd = new int[m_psD.iLen];
	m_psD.iWInd = new int[m_psD.iLen];
	m_psD.cTestMap = new char[m_psD.iLen];  //RT//
	memset(m_psD.cCmdW, 0, m_psD.iLen);
	memset(m_psD.cDataW, 0, m_psD.iLen);
	memset(m_psD.cCmdR, 0, m_psD.iLen);
	memset(m_psD.cDataR, 0, m_psD.iLen);
	memset(m_psD.iRInd, 0, m_psD.iLen*sizeof(int));
	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	memset(m_psD.cTestMap, 0, m_psD.iLen);  //RT//
	m_psD.iToR = m_psD.iLen;
	m_psD.iToW = 0;
	for(int i=0; i<m_psD.iLen; i++)
	{
		//Write Command and Addresses
		m_psD.cCmdW[i] = 1;
		m_psD.cCmdW[i] = m_psD.cCmdW[i] << 3;
		m_psD.cCmdW[i] |= m_cMAddr;
		m_psD.cCmdW[i] = m_psD.cCmdW[i] << 4;
		m_psD.cCmdW[i] |= i;
		//Read Command and Addresses
		m_psD.cCmdR[i] = 0;
		m_psD.cCmdR[i] = m_psD.cCmdR[i] << 3;
		m_psD.cCmdR[i] |= m_cMAddr;
		m_psD.cCmdR[i] = m_psD.cCmdR[i] << 4;
		m_psD.cCmdR[i] |= i;

		m_psD.iRInd[i] = i;
	};

  //Register test mask //RT//
	for(int i=0; i<m_psD.iLen; i++)
	{
		m_psD.cTestMap[i] = 0x00;
	};
	m_psD.cTestMap[0x0] = 0x03;
	m_psD.cTestMap[0x1] = 0x1F;
	m_psD.cTestMap[0x2] = 0xFF;
	m_psD.cTestMap[0x3] = 0xFF;
	m_psD.cTestMap[0x4] = 0x1F;
	m_psD.cTestMap[0x5] = 0xFF;
	m_psD.cTestMap[0x6] = 0xFF;
	m_psD.cTestMap[0x7] = 0xFF;
	m_psD.cTestMap[0x8] = 0x1F;
	m_psD.cTestMap[0x9] = 0x1F;
	m_psD.cTestMap[0xA] = 0x1F;
	m_psD.cTestMap[0xB] = 0xFF;
	m_psD.cTestMap[0xC] = 0xFF;
	m_psD.cTestMap[0xD] = 0x80;
	m_psD.cTestMap[0xE] = 0x00;
	//m_psD.cTestMap[0xF] = 0xFF;

	SetDefaults();

};

/**
    Sets default parameter values
*/
void TxRf_Module::SetDefaults()
{
	int itmp;
	double dtmp;
	m_bAllowSend = false;

	//DECODE
	rgrDecode.itemIndex = 0;
	//EN
	chbPwrTxRfMods.checked = true;

	//VGA1GAIN[4:0]
	//VGA1GAINT[7:0]
	cmbVga1G_u.clear();
	cmbVga1G_t.clear();
	itmp = -35;
	for(int i=0; i<32; i++)
	{
		cmbVga1G_u.add(itmp);
		cmbVga1G_t.add(itmp);
		itmp++;
	};
	cmbVga1G_u.itemIndex = 21;
	cmbVga1G_t.itemIndex = 21;

	//VGA1DC_Q[7:0]
	//VGA1DC_I[7:0]
	cmbVga1DcI.clear();
	cmbVga1DcQ.clear();
	dtmp = -16;
	for(int i=0; i<256; i++)
	{
		cmbVga1DcI.add(dtmp);
		cmbVga1DcQ.add(dtmp);
		dtmp += 0.125;
	};
	cmbVga1DcI.itemIndex = 128;
	cmbVga1DcQ.itemIndex = 128;

	//PA_EN
	rgrPA.itemIndex = 1;
	//PD_DRVAUX
	chbPD_DRVAUX.checked = true;
	//PD_PKDET
	chbPD_PKDET.checked = true;

	//MIXVGA2GAIN[4:0]
	cmbVga2G_u.clear();
	for(int i=0; i<26; i++)
	{
		cmbVga2G_u.add(i);
	};
	cmbVga2G_u.itemIndex = 0;

	//MIXVGA2GAINT[8:0]
	cmbVga2G_t.clear();
	for(int i=0; i<512; i++)
	{
		cmbVga2G_t.add(i);
	};
	cmbVga2G_t.itemIndex = 0;

	//ENVD[1:0]
	cmbENVD.clear();
	cmbENVD.add("AUXPA ED output");
	cmbENVD.add("AUXPA PD output");
	cmbENVD.add("PA1 ED output");
	cmbENVD.add("PA2 PD output");
	cmbENVD.itemIndex = 0;

	//ENVD[2]
	cmbENVD2.clear();
	cmbENVD2.add("Reference DC");
	cmbENVD2.add("Detector Average");
	cmbENVD2.itemIndex = 0;

	//PKDBW[3:0]
	cmbPKDBW.clear();
	for(int i=0; i<16; i++)
	{
		cmbPKDBW.add(i);
	};
	cmbPKDBW.itemIndex = 0;
	//LOOPBBEN
	rgrLOOPBBEN.itemIndex = 0;
	//FST_PKDET
	chbFST_PKDET.checked = false;
	//FST_TXHFBIAS
	chbFST_TXHFBIAS.checked = false;

	//ICT_TXLOBUF[3:0]
	cmbICT_TXLOBUF.clear();
	for(int i=0; i<16; i++)
	{
		cmbICT_TXLOBUF.add(i);
	};
	//cmbICT_TXLOBUF.itemIndex = 6;
	cmbICT_TXLOBUF.itemIndex = 4;    //APARATUROJ 6, BET PAGAL RICARDO PAGEIDAVIMA PADARYTA 4.



	//VBCAS_TXDRV[3:0]
	cmbVBCAS_TXDRV.clear();
	for(int i=0; i<16; i++)
	{
		cmbVBCAS_TXDRV.add(i);
	};
	cmbVBCAS_TXDRV.itemIndex = 0;

	//ICT_TXMIX[4:0]
	cmbICT_TXMIX.clear();
	for(int i=0; i<32; i++)
	{
		cmbICT_TXMIX.add(i);
	};
	cmbICT_TXMIX.itemIndex = 12;

	//ICT_TXDRV[4:0]
	cmbICT_TXDRV.clear();
	for(int i=0; i<32; i++)
	{
		cmbICT_TXDRV.add(i);
	};
	cmbICT_TXDRV.itemIndex = 12;

	//
	chbPwrVga1_I.checked = true;
	chbPwrVga1_Q.checked = true;
	chbPD_TXDRV.checked = false;
	chbPD_TXLOBUF.checked = false;
	chbPwrVga2.checked = false;

	m_bAllowSend = true;
};

/**
    Set parameters according to the chip version, revision and mask
    @param Ver chip version
    @param Rev chip revision
    @param Mask chip mask
*/
void TxRf_Module::UpdateVerRevMask(char Ver, char Rev, char Mask)
{
  m_cVer = Ver;
  m_cRev = Rev;
  m_cMask = Mask;

  m_bAllowSend = false;
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    //PD_DRVAUX
    chbPD_DRVAUX.checked = false;
    //PD_PKDET
    chbPD_PKDET.checked = false;
  };

  m_bAllowSend = true;


  //Edit Register Test masks
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    m_psD.cTestMap[0xE] += 0x80;
    m_psD.cTestMap[0x4] -= 0x03;
  };

};

/**
    Make data to download
*/
void TxRf_Module::MakeData(int rAddr)
{
	char btmp, btmp1;

	//======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;
	//EN
	btmp = chbPwrTxRfMods.checked == true ? 1 : 0;
	btmp = btmp << 1; m_psD.cDataW[0x00] |= btmp;
	//DECODE
	btmp = (char)rgrDecode.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x00] |= btmp;

	//======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;
	//VGA1GAIN[4:0]
	btmp = (char)cmbVga1G_u.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x01] |= btmp;

	//======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
	//VGA1DC_I[7:0]
	btmp = (char)cmbVga1DcI.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x02] |= btmp;

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	//VGA1DC_Q[7:0]
	btmp = (char)cmbVga1DcQ.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x03] |= btmp;

	//======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
  //PA_EN[2:0]
	btmp = (rgrPA.itemIndex & 0x03) << 1;
	btmp = btmp << 2; m_psD.cDataW[0x04] |= btmp;
  //PD_DRVAUX
  btmp = chbPD_DRVAUX.checked == true ? 1 : 0;
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    btmp = btmp << 2; m_psD.cDataW[0x04] |= btmp;
  }
  else
  {
    btmp = btmp << 1; m_psD.cDataW[0x04] |= btmp;
  };
  //PD_PKDET
	btmp = chbPD_PKDET.checked == true ? 1 : 0;
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
	//Will be resolved at 0x0E
  }
  else
  {
    btmp = btmp << 0; m_psD.cDataW[0x04] |= btmp;
  };



	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
  //MIXVGA2GAIN[4:0]
	btmp = (char)cmbVga2G_u.itemIndex;
	btmp = btmp << 3; m_psD.cDataW[0x05] |= btmp;
  //ENVD[2]
	btmp = (char)cmbENVD2.itemIndex;
	btmp = btmp << 2; m_psD.cDataW[0x05] |= btmp;
  //ENVD[1:0]
	btmp = (char)cmbENVD.itemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x05] |= btmp;

	//======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
  //PKDBW[3:0]
	btmp = (char)cmbPKDBW.itemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x06] |= btmp;
  //LOOPBBEN[1:0]
	btmp = (char)rgrLOOPBBEN.itemIndex;
	btmp = btmp << 2; m_psD.cDataW[0x06] |= btmp;
  //FST_PKDET
	btmp = chbFST_PKDET.checked == true ? 1 : 0;
	btmp = btmp << 1; m_psD.cDataW[0x06] |= btmp;
  //FST_PKDET
	btmp = chbFST_TXHFBIAS.checked == true ? 1 : 0;
	btmp = btmp << 0; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
  //ICT_TXLOBUF[3:0]
	btmp = (char)cmbICT_TXLOBUF.itemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x07] |= btmp;
  //VBCAS_TXDRV[3:0]
	btmp = (char)cmbVBCAS_TXDRV.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x07] |= btmp;

	//======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
  //ICT_TXMIX[4:0]
	btmp = (char)cmbICT_TXMIX.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x08] |= btmp;

	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //ICT_TXDRV[4:0]
	btmp = (char)cmbICT_TXDRV.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

	//======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
	//PW_VGA1_I
	btmp = chbPwrVga1_I.checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x0A] |= btmp;
	//PW_VGA1_Q
	btmp = chbPwrVga1_Q.checked == true ? 1 : 0;
	btmp = btmp << 3; m_psD.cDataW[0x0A] |= btmp;
	//PD_TXDRV
	btmp = chbPD_TXDRV.checked == true ? 1 : 0;
	btmp = btmp << 2; m_psD.cDataW[0x0A] |= btmp;
	//PD_TXLOBUF
	btmp = chbPD_TXLOBUF.checked == true ? 1 : 0;
	btmp = btmp << 1; m_psD.cDataW[0x0A] |= btmp;
	//PD_TXMIX
	btmp = chbPwrVga2.checked == true ? 1 : 0;
	btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;

	//======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
	//VGA1GAINT[7:0]
	btmp = 0x00;
	switch(cmbVga1G_t.itemIndex)
	{
  	//DC Calibration
    case 0x0:
    	btmp = 0x06;
		break;
    case 0x1:
    	btmp = 0x07;
		break;
    case 0x2:
    	btmp = 0x08;
		break;
    case 0x3:
    	btmp = 0x09;
		break;
    case 0x4:
    	btmp = 0x0A;
		break;
    case 0x5:
    	btmp = 0x0B;
		break;
    case 0x6:
    	btmp = 0x0D;
		break;
    case 0x7:
    	btmp = 0x0F;
		break;
    case 0x8:
    	btmp = 0x11;
		break;
    case 0x9:
    	btmp = 0x13;
		break;
    case 0xA:
    	btmp = 0x15;
		break;
    case 0xB:
    	btmp = 0x18;
		break;
    case 0xC:
    	btmp = 0x1B;
		break;
    case 0x0D:
    	btmp = 0x1F;
		break;
    case 0x0E:
    	btmp = 0x23;
		break;
    case 0x0F:
    	btmp = 0x27;
		break;
    case 0x10:
    	btmp = 0x2C;
		break;
    case 0x11:
    	btmp = 0x32;
		break;
    case 0x12:
    	btmp = 0x38;
		break;
    case 0x13:
    	btmp = 0x3F;
		break;
    case 0x14:
    	btmp = 0x47;
		break;
    case 0x15:
    	btmp = 0x50;
		break;
    case 0x16:
    	btmp = 0x5A;
		break;
    case 0x17:
    	btmp = 0x65;
		break;
    case 0x18:
    	btmp = 0x71;
		break;
    case 0x19:
    	btmp = 0x7F;
		break;
    case 0x1A:
    	btmp = 0x8F;
		break;
    case 0x1B:
    	btmp = 0xA0;
		break;
    case 0x1C:
    	btmp = 0xB4;
		break;
    case 0x1D:
    	btmp = 0xCA;
		break;
    case 0x1E:
    	btmp = 0xE3;
		break;
    case 0x1F:
    	btmp = 0xFF;
		break;
  };
  btmp = btmp << 0; m_psD.cDataW[0x0B] |= btmp;

	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	//MIXVGA2GAINT[7:0]
	btmp = (char)((cmbVga2G_t.itemIndex & 0x1FF) >> 1);
  btmp = btmp >> 0; m_psD.cDataW[0x0C] |= btmp;

	//======= register addr 0x0D =======
	m_psD.cDataW[0x0D] = 0x00;
	//MIXVGA2GAINT[8]
	btmp = (char)(cmbVga2G_t.itemIndex & 0x01);
  btmp = btmp << 7; m_psD.cDataW[0x0D] |= btmp;

  //======= register addr 0x0E =======
	m_psD.cDataW[0x0E] = 0x00;
  //PD_PKDET
  btmp = chbPD_PKDET.checked == true ? 1 : 0;
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    btmp = btmp << 7; m_psD.cDataW[0x0E] |= btmp;
  }
  else
  {
    //Resolved at 0x04
  };


	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch(rAddr)
	{
		//User mode
		case 0x01:
		case 0x02:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x00;
		break;

		case 0x03:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x01;
		break;

		case 0x04:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x02;
		break;

		case 0x05:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x03;
		break;

		case 0x06:
		case 0x10:
		case 0x101:
		case 0x11:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x04;
		break;

		case 0x111:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0E;
		break;

		case 0x07:
		case 0x12:
		case 0x13:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x05;
		break;

		case 0x0D:
		case 0x14:
		case 0x15:
		case 0x16:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x06;
		break;

		case 0x17:
		case 0x18:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x07;
		break;

		case 0x19:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x08;
		break;

		case 0x1A:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x09;
		break;

		case 0x08:
		case 0x09:
		case 0x0C:
		case 0x1B:
		case 0x1D:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0A;
		break;

		case 0x0A:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0B;
		break;

		case 0x0B:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x0C;
			m_psD.iWInd[1] = 0x0D;
		break;

		default:
			m_psD.iToW = 0;
	};
}
//---------------------------------------------------------------------------
void TxRf_Module::setPwrTxRfMods(bool state)
{
	chbPwrTxRfMods.checked = state;
	if(m_bAllowSend){ MakeData(0x01); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getPwrTxRfMods()
{
	return chbPwrTxRfMods.checked;
}
//---------------------------------------------------------------------------
void TxRf_Module::setDecode(int index)
{
	rgrDecode.itemIndex = index;
	//SetGuiDecode();
	if(m_bAllowSend){ MakeData(0x02); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getDecode()
{
	return rgrDecode.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setVga1G_u(int index)
{
	cmbVga1G_u.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x03); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getVga1G_u()
{
	return cmbVga1G_u.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setVga1DcI(int index)
{
	cmbVga1DcI.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x04); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getVga1DcI()
{
	return cmbVga1DcI.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setVga1DcQ(int index)
{
	cmbVga1DcQ.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x05); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getVga1DcQ()
{
	return cmbVga1DcQ.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setPA(int index)
{
	rgrPA.itemIndex = index;
	if(m_bAllowSend)
	{
		MakeData(0x06);
		pMainModule->CMAutoDownload(m_cMAddr);

	};
	pMainModule->getSerPort()->SetBrdPA(index);
}
int TxRf_Module::getPA()
{
	return rgrPA.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setVga2G_u(int index)
{
	cmbVga2G_u.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x07); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getVga2G_u()
{
	return cmbVga2G_u.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setPwrVga1_I(bool state)
{
	chbPwrVga1_I.checked = state;
	if(m_bAllowSend){ MakeData(0x08); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getPwrVga1_I()
{
	return chbPwrVga1_I.checked;
}
//---------------------------------------------------------------------------
void TxRf_Module::setPwrVga2(bool state)
{
	chbPwrVga2.checked = state;
	if(m_bAllowSend){ MakeData(0x09); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getPwrVga2()
{
	return chbPwrVga2.checked;
}
//---------------------------------------------------------------------------
void TxRf_Module::setVga1G_t(int index)
{
	cmbVga1G_t.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0A); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getVga1G_t()
{
	return cmbVga1G_t.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setVga2G_t(int index)
{
	cmbVga2G_t.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0B); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getVga2G_t()
{
	return cmbVga2G_t.itemIndex;
}
//---------------------------------------------------------------------------
void TxRf_Module::setPwrVga1_Q(bool state)
{
	chbPwrVga1_Q.checked = state;
	if(m_bAllowSend){ MakeData(0x0C); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getPwrVga1_Q()
{
	return chbPwrVga1_Q.checked;
}
//---------------------------------------------------------------------------
void TxRf_Module::setLOOPBBEN(int index)
{
	rgrLOOPBBEN.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0D); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getLOOPBBEN()
{
	return rgrLOOPBBEN.itemIndex;
}
//---------------------------------------------------------------------------


/**
    Make all data to write
*/
void TxRf_Module::MakeWriteAll()
{
	MakeData(0xFFFF);
	m_psD.iToW = m_psD.iLen;
	for(int i=0; i<m_psD.iLen; i++)
	{
		m_psD.iWInd[i] = i;
	};
};

/**
    Save the chip configuration to the file
    @param out stream for output
    @param Caption title for data
    @param bWrAll write all parameters
*/
bool TxRf_Module::ChipVsGui(ofstream &out, string Caption, bool bWrAll)
{
	bool bRez = true;
	bool btmp;
	char str[64] = "";
	int itmp;

	out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out.width(32); out << "| Register"; out.width(2); out << "|";
	out.width(50); out << "Value from PC"; out.width(2); out << "|";
	out.width(50); out << "Value from Chip"; out.width(1); out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------" << endl;


  //EN
  if((chbPwrTxRfMods.checked != (bool)EN_r00_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrTxRfMods.checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(EN_r00_b11()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DECODE
  if((rgrDecode.itemIndex != DECODE_r00_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
    if(rgrDecode.itemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  if(DECODE_r00_b00()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
	bRez = false;
  };

  //VGA1GAIN[4:0]
  if((cmbVga1G_u.itemIndex != VGA1GAIN_r01_b40()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| VGA1GAIN[4:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVga1G_u.sItems[cmbVga1G_u.itemIndex].c_str());
    out << str;	out.width(10); out << "dB"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = VGA1GAIN_r01_b40();
    if(itmp < 32) strcpy(str, cmbVga1G_u.sItems[itmp].c_str());
    else strcpy(str, "Wrong Data!!!");
    out << str;	out.width(10); out << "dB"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //VGA1DC_I[7:0]
  if((cmbVga1DcI.itemIndex != VGA1DC_I_r02_b70()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| VGA1DC_I[7:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVga1DcI.sItems[cmbVga1DcI.itemIndex].c_str());
    out << str;	out.width(10); out << "mV"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = VGA1DC_I_r02_b70();
    strcpy(str, cmbVga1DcI.sItems[itmp].c_str());
    out << str;	out.width(10); out << "mV"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //VGA1DC_Q[7:0]
  if((cmbVga1DcQ.itemIndex != VGA1DC_Q_r03_b70()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| VGA1DC_Q[7:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVga1DcQ.sItems[cmbVga1DcQ.itemIndex].c_str());
    out << str;	out.width(10); out << "mV"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = VGA1DC_Q_r03_b70();
    strcpy(str, cmbVga1DcQ.sItems[itmp].c_str());
    out << str;	out.width(10); out << "mV"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PA_EN[2:0]
  itmp = PA_EN_r04_b42();
  if((rgrPA.itemIndex != itmp) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| VGA2PA"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrPA.sItems[rgrPA.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    if(itmp < 3) strcpy(str, rgrPA.sItems[itmp].c_str());
    else strcpy(str, "Wrong Data!!!");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_DRVAUX
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    if((chbPD_DRVAUX.checked != (bool)PD_DRVAUX_r04_b22_v1()) || bWrAll)
    {
      memset(str, '\0', sizeof(str));
	    out.width(32); out << "| PD_DRVAUX"; out.width(2); out << "|";	out.width(40);
      if(chbPD_DRVAUX.checked) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
      out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    	memset(str, '\0', sizeof(str));
  	  if(PD_DRVAUX_r04_b22_v1()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
      out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
      bRez = false;
    };
  }
  else
  {
    if((chbPD_DRVAUX.checked != (bool)PD_DRVAUX_r04_b11_v0()) || bWrAll)
    {
      memset(str, '\0', sizeof(str));
	    out.width(32); out << "| PD_DRVAUX"; out.width(2); out << "|";	out.width(40);
      if(chbPD_DRVAUX.checked) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
      out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    	memset(str, '\0', sizeof(str));
  	  if(PD_DRVAUX_r04_b11_v0()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
      out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
      bRez = false;
    };
  };

  //PD_PKDET
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    if((chbPD_PKDET.checked != (bool)PD_PKDET_r0E_b77_v1()) || bWrAll)
    {
      memset(str, '\0', sizeof(str));
	    out.width(32); out << "| PD_PKDET"; out.width(2); out << "|";	out.width(40);
      if(chbPD_PKDET.checked) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
      out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    	memset(str, '\0', sizeof(str));
  	  if(PD_PKDET_r0E_b77_v1()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
	  out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
      bRez = false;
    };
  }
  else
  {
    if((chbPD_PKDET.checked != (bool)PD_PKDET_r04_b00_v0()) || bWrAll)
    {
      memset(str, '\0', sizeof(str));
	    out.width(32); out << "| PD_PKDET"; out.width(2); out << "|";	out.width(40);
      if(chbPD_PKDET.checked) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
      out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    	memset(str, '\0', sizeof(str));
  	  if(PD_PKDET_r04_b00_v0()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
      out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
      bRez = false;
    };
  };

  //VGA2GAIN[4:0]
  if((cmbVga2G_u.itemIndex != VGA2GAIN_r05_b73()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| VGA2GAIN[4:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVga2G_u.sItems[cmbVga2G_u.itemIndex].c_str());
    out << str;	out.width(10); out << "dB"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = VGA2GAIN_r05_b73();
    strcpy(str, cmbVga2G_u.sItems[itmp].c_str());
    out << str;	out.width(10); out << "dB"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ENVD[2]
  if((cmbENVD2.itemIndex != ENVD_r05_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ENVD[2]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbENVD2.sItems[cmbENVD2.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = ENVD_r05_b22();
    strcpy(str, cmbENVD2.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ENVD[1:0]
  if((cmbENVD.itemIndex != ENVD_r05_b10()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ENVD[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbENVD.sItems[cmbENVD.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = ENVD_r05_b10();
    strcpy(str, cmbENVD.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };


  //PKDBW[3:0]
  if((cmbPKDBW.itemIndex != PKDBW_r06_b74()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PKDBW[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbPKDBW.sItems[cmbPKDBW.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = PKDBW_r06_b74();
    strcpy(str, cmbPKDBW.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LOOPBBEN[1:0]
  if((rgrLOOPBBEN.itemIndex != LOOPBBEN_r06_b32()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| LOOPBBEN[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrLOOPBBEN.sItems[rgrLOOPBBEN.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = LOOPBBEN_r06_b32();
    strcpy(str, rgrLOOPBBEN.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FST_PKDET
  if((chbFST_PKDET.checked != (bool)FST_PKDET_r06_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| FST_PKDET"; out.width(2); out << "|";	out.width(40);
    if(chbFST_PKDET.checked) strcpy(str, "Resistor shorted"); else strcpy(str, "Switch open");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(FST_PKDET_r06_b11()) strcpy(str, "Resistor shorted"); else strcpy(str, "Switch open");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FST_TXHFBIAS
  if((chbFST_TXHFBIAS.checked != (bool)FST_TXHFBIAS_r06_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| FST_TXHFBIAS"; out.width(2); out << "|";	out.width(40);
    if(chbFST_TXHFBIAS.checked) strcpy(str, "Resistor shorted"); else strcpy(str, "Switch open");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(FST_TXHFBIAS_r06_b00()) strcpy(str, "Resistor shorted"); else strcpy(str, "Switch open");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_TXLOBUF[3:0]
  if((cmbICT_TXLOBUF.itemIndex != ICT_TXLOBUF_r07_b74()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_TXLOBUF[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbICT_TXLOBUF.sItems[cmbICT_TXLOBUF.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = ICT_TXLOBUF_r07_b74();
    strcpy(str, cmbICT_TXLOBUF.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //VBCAS_TXDRV[3:0]
  if((cmbVBCAS_TXDRV.itemIndex != VBCAS_TXDRV_r07_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| VBCAS_TXDRV[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVBCAS_TXDRV.sItems[cmbVBCAS_TXDRV.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = VBCAS_TXDRV_r07_b30();
    strcpy(str, cmbVBCAS_TXDRV.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_TXMIX[4:0]
  if((cmbICT_TXMIX.itemIndex != ICT_TXMIX_r08_b40()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_TXMIX[4:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbICT_TXMIX.sItems[cmbICT_TXMIX.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = ICT_TXMIX_r08_b40();
	strcpy(str, cmbICT_TXMIX.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_TXDRV[4:0]
  if((cmbICT_TXDRV.itemIndex != ICT_TXDRV_r09_b40()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_TXDRV[4:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbICT_TXDRV.sItems[cmbICT_TXDRV.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = ICT_TXDRV_r09_b40();
    strcpy(str, cmbICT_TXDRV.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  if((!bRez) || bWrAll)
  {
    out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |" << endl;
  };

  //PW_VGA1_I
  if((chbPwrVga1_I.checked != (bool)PW_VGA1_I_r0A_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PW_VGA1_I"; out.width(2); out << "|";	out.width(40);
    if(chbPwrVga1_I.checked) strcpy(str, "VGA1 I powered up"); else strcpy(str, "VGA1 I powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PW_VGA1_I_r0A_b44()) strcpy(str, "VGA1 I powered up"); else strcpy(str, "VGA1 I powered down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PW_VGA1_Q
  if((chbPwrVga1_Q.checked != (bool)PW_VGA1_Q_r0A_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PW_VGA1_Q"; out.width(2); out << "|";	out.width(40);
    if(chbPwrVga1_Q.checked) strcpy(str, "VGA1 Q powered up"); else strcpy(str, "VGA1 Q powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PW_VGA1_Q_r0A_b33()) strcpy(str, "VGA1 Q powered up"); else strcpy(str, "VGA1 Q powered down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_TXDRV
  if((chbPD_TXDRV.checked != (bool)PD_TXDRV_r0A_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_TXDRV"; out.width(2); out << "|";	out.width(40);
    if(chbPD_TXDRV.checked) strcpy(str, "PA1, PA2, AUXPA Disabled"); else strcpy(str, "PA1, PA2, AUXPA Enabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_TXDRV_r0A_b22()) strcpy(str, "PA1, PA2, AUXPA Disabled"); else strcpy(str, "PA1, PA2, AUXPA Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_TXLOBUF
  if((chbPD_TXLOBUF.checked != (bool)PD_TXLOBUF_r0A_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_TXLOBUF"; out.width(2); out << "|";	out.width(40);
    if(chbPD_TXLOBUF.checked) strcpy(str, "TxLOBUF Disabled"); else strcpy(str, "TxLOBUF Enabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_TXLOBUF_r0A_b11()) strcpy(str, "TxLOBUF Disabled"); else strcpy(str, "TxLOBUF Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_TXMIX
  if((chbPwrVga2.checked != (bool)PD_TXMIX_r0A_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_TXMIX"; out.width(2); out << "|";	out.width(40);
    if(chbPwrVga2.checked) strcpy(str, "MIX and VGA2 powered down"); else strcpy(str, "MIX and VGA2 powered up");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_TXMIX_r0A_b00()) strcpy(str, "MIX and VGA2 powered down"); else strcpy(str, "MIX and VGA2 powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //VGA1GAINT[7:0]
  itmp = VGA1GAINT_r0B_b70();
  btmp = false;
  if( (itmp == 0x06) || (itmp == 0x07) || (itmp == 0x08) || (itmp == 0x09) || (itmp == 0x0A) ||
      (itmp == 0x0B) || (itmp == 0x0D) || (itmp == 0x0F) || (itmp == 0x11) || (itmp == 0x13) ||
      (itmp == 0x15) || (itmp == 0x18) || (itmp == 0x1B) || (itmp == 0x1F) || (itmp == 0x23) ||
      (itmp == 0x27) || (itmp == 0x2C) || (itmp == 0x32) || (itmp == 0x38) || (itmp == 0x3F) ||
      (itmp == 0x47) || (itmp == 0x50) || (itmp == 0x5A) || (itmp == 0x65) || (itmp == 0x71) ||
      (itmp == 0x7F) || (itmp == 0x8F) || (itmp == 0xA0) || (itmp == 0xB4) || (itmp == 0xCA) ||
      (itmp == 0xE3) || (itmp == 0xFF) )
  {
    btmp = true;
  };

  if((!btmp) || bWrAll)
  {

    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| VGA1GAINT[7:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVga1G_t.sItems[cmbVga1G_t.itemIndex].c_str());
    out << str;	out.width(10); out << "dB"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = m_psD.cDataR[0x0A] & 0xFF;
  	switch(itmp)
	  {
  	  //DC Calibration
      case 0x06 :
      	strcpy(str, cmbVga1G_t.sItems[0x00].c_str());
		  break;
      case 0x07:
        strcpy(str, cmbVga1G_t.sItems[0x01].c_str());
		  break;
      case 0x08:
        strcpy(str, cmbVga1G_t.sItems[0x02].c_str());
		  break;
      case 0x09:
        strcpy(str, cmbVga1G_t.sItems[0x03].c_str());
		  break;
      case 0x0A:
        strcpy(str, cmbVga1G_t.sItems[0x04].c_str());
		  break;
      case 0x0B:
        strcpy(str, cmbVga1G_t.sItems[0x05].c_str());
		  break;
      case 0x0D:
        strcpy(str, cmbVga1G_t.sItems[0x06].c_str());
		  break;
      case 0x0F:
        strcpy(str, cmbVga1G_t.sItems[0x07].c_str());
		  break;
      case 0x11:
        strcpy(str, cmbVga1G_t.sItems[0x08].c_str());
		  break;
      case 0x13:
        strcpy(str, cmbVga1G_t.sItems[0x09].c_str());
		  break;
      case 0x15:
        strcpy(str, cmbVga1G_t.sItems[0x0A].c_str());
		  break;
      case 0x18:
        strcpy(str, cmbVga1G_t.sItems[0x0B].c_str());
		  break;
      case 0x1B:
        strcpy(str, cmbVga1G_t.sItems[0x0C].c_str());
		  break;
      case 0x1F:
        strcpy(str, cmbVga1G_t.sItems[0x0D].c_str());
		  break;
      case 0x23:
        strcpy(str, cmbVga1G_t.sItems[0x0E].c_str());
		  break;
      case 0x27:
        strcpy(str, cmbVga1G_t.sItems[0x0F].c_str());
		  break;
      case 0x2C:
        strcpy(str, cmbVga1G_t.sItems[0x10].c_str());
		  break;
      case 0x32:
        strcpy(str, cmbVga1G_t.sItems[0x11].c_str());
		  break;
      case 0x38:
        strcpy(str, cmbVga1G_t.sItems[0x12].c_str());
		  break;
      case 0x3F:
        strcpy(str, cmbVga1G_t.sItems[0x13].c_str());
		  break;
      case 0x47:
        strcpy(str, cmbVga1G_t.sItems[0x14].c_str());
		  break;
      case 0x50:
        strcpy(str, cmbVga1G_t.sItems[0x15].c_str());
		  break;
      case 0x5A:
        strcpy(str, cmbVga1G_t.sItems[0x16].c_str());
		  break;
      case 0x65:
        strcpy(str, cmbVga1G_t.sItems[0x17].c_str());
		  break;
      case 0x71:
        strcpy(str, cmbVga1G_t.sItems[0x18].c_str());
		  break;
      case 0x7F:
        strcpy(str, cmbVga1G_t.sItems[0x19].c_str());
		  break;
      case 0x8F:
        strcpy(str, cmbVga1G_t.sItems[0x1A].c_str());
		  break;
      case 0xA0:
        strcpy(str, cmbVga1G_t.sItems[0x1B].c_str());
		  break;
      case 0xB4:
        strcpy(str, cmbVga1G_t.sItems[0x1C].c_str());
		  break;
      case 0xCA:
        strcpy(str, cmbVga1G_t.sItems[0x1D].c_str());
		  break;
      case 0xE3:
        strcpy(str, cmbVga1G_t.sItems[0x1E].c_str());
		  break;
      case 0xFF:
        strcpy(str, cmbVga1G_t.sItems[0x1F].c_str());
		  break;

      default:
      	strcpy(str, "WRONG DATA!!!");
    };
    out << str;	out.width(10); out << "dB"; out.width(1); out << "|"; out << endl;
  };

  //G_TXVGA2[8:0]
  int itt = G_TXVGA2();
  if((cmbVga2G_t.itemIndex != G_TXVGA2()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| G_TXVGA2[8:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVga2G_t.sItems[cmbVga2G_t.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = G_TXVGA2();
    strcpy(str, cmbVga2G_t.sItems[itmp].c_str());
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
    Writes Register - Value format to the file.
    @param out stream for output
*/
void TxRf_Module::MakeRVFFile(ofstream &out)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//

  //0x00
  iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0x03);
  out << iRval; out << endl;

  //0x01
  iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0x1F);
  out << iRval; out << endl;

  //0x02
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
  out << iRval; out << endl;

  //0x03
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
  out << iRval; out << endl;

  //0x04
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x1C);
  }
  else
  {
    iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x1F);
  };
  out << iRval; out << endl;

  //0x05
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << iRval; out << endl;

  //0x06
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
  out << iRval; out << endl;

  //0x07
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << iRval; out << endl;

  //0x08
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0x1F);
  out << iRval; out << endl;

  //0x09
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x1F);
  out << iRval; out << endl;

  //0x0A
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x1F);
  out << iRval; out << endl;

  //0x0B
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << iRval; out << endl;

  //0x0C
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
  out << iRval; out << endl;

  //0x0D
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0x80);
  out << iRval; out << endl;

  //0x0E
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    iRval = (iAddr | (0x0E << 8)) | (m_psD.cDataR[0x0E] & 0x80);
    out << iRval; out << endl;
  }
  else
  {
  };

  //0x0F

};

/**
    Saves chip configuration using FRIF format
    @param out stream for output
    @param FRIF_SPI_A frif parameter
*/
void TxRf_Module::MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  out << "echo \"Now programming the Lime Tx RF\"" << endl << endl;

  //0x00
  //out << "# Register(s): EN, DECODE" << endl;
  iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0x03);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x01
  //out << "# Register(s): VGA1GAIN[4:0]" << endl;
  iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0x1F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x02
  //out << "# Register(s): VGA1DC_I[7:0]" << endl;
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x03
  //out << "# Register(s): VGA1DC_Q[7:0]" << endl;
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x04
  //out << "# Register(s): PA_EN[2:0], PD_DRVAUX, PD_PKDET" << endl;
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x1C);
  }
  else
  {
    iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x1F);
  };
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x05
  //out << "# Register(s): VGA2GAIN[4:0], ENVD[2:0]" << endl;
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x06
  //out << "# Register(s): PKDBW[3:0], LOOPBBEN[1:0], FST_PKDET, FST_TXHFBIAS" << endl;
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x07
  //out << "# Register(s): ICT_TXLOBUF[3:0], VBCAS_TXDRV[3:0]" << endl;
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x08
  //out << "# Register(s): ICT_TXMIX[4:0]" << endl;
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0x1F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x09
  //out << "# Register(s): ICT_TXDRV[4:0]" << endl;
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x1F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0A
  //out << "# Register(s): PW_VGA1_I, PW_VGA1_Q, PD_TXDRV, PD_TXLOBUF, PD_TXMIX" << endl;
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x1F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0B
  //out << "# Register(s): VGA1GAINT[7:0]" << endl;
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0C
  //out << "# Register(s): G_TXVGA2[8:1]" << endl;
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0D
  //out << "# Register(s): G_TXVGA2[0]" << endl;
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0x80);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0E
  //out << "# Register(s): PD_PKDET" << endl;
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    iRval = (iAddr | (0x0E << 8)) | (m_psD.cDataR[0x0E] & 0x80);
  }
  else
  {
  };
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0F

  out << endl << "echo \"Tx RF programming complete\"" << endl << endl;

};

/**
    Sets GUI under data from chip
*/
bool TxRf_Module::SetGUIUnderReadback()
{
  int itmp;
  bool bRez = true;

  m_bAllowSend = false;

  //EN
  itmp = EN_r00_b11();
  chbPwrTxRfMods.checked = itmp;

  //DECODE
  itmp = DECODE_r00_b00();
  rgrDecode.itemIndex = itmp;

  //VGA1GAIN[4:0]
	itmp = VGA1GAIN_r01_b40();
  if(itmp > 31) { itmp = 31; bRez = false; };
  cmbVga1G_u.itemIndex = itmp;

  //VGA1DC_I[7:0]
  itmp = VGA1DC_I_r02_b70();
  cmbVga1DcI.itemIndex = itmp;

  //VGA1DC_Q[7:0]
  itmp = VGA1DC_Q_r03_b70();
  cmbVga1DcQ.itemIndex = itmp;

  //PA_EN[2:0]
  itmp = PA_EN_r04_b42();
  rgrPA.itemIndex = itmp;

  //PD_DRVAUX
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    itmp = PD_DRVAUX_r04_b22_v1();
  }
  else
  {
    itmp = PD_DRVAUX_r04_b11_v0();
  };
  chbPD_DRVAUX.checked = itmp;

  //PD_PKDET
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    itmp = PD_PKDET_r0E_b77_v1();
  }
  else
  {
    itmp = PD_PKDET_r04_b00_v0();
  };
  chbPD_PKDET.checked = itmp;

  //VGA2GAIN[4:0]
  itmp = VGA2GAIN_r05_b73();
  cmbVga2G_u.itemIndex = itmp;

  //ENVD[2]
  itmp = ENVD_r05_b22();
  cmbENVD2.itemIndex = itmp;

  //ENVD[1:0]
  itmp = ENVD_r05_b10();
  cmbENVD.itemIndex = itmp;

  //PKDBW[3:0]
  itmp = PKDBW_r06_b74();
  cmbPKDBW.itemIndex = itmp;

  //LOOPBBEN[1:0]
  itmp = LOOPBBEN_r06_b32();
  rgrLOOPBBEN.itemIndex = itmp;

  //FST_PKDET
  itmp = FST_PKDET_r06_b11();
  chbFST_PKDET.checked = itmp;

  //FST_TXHFBIAS
  itmp = FST_TXHFBIAS_r06_b00();
  chbFST_TXHFBIAS.checked = itmp;

  //ICT_TXLOBUF[3:0]
  itmp = ICT_TXLOBUF_r07_b74();
  cmbICT_TXLOBUF.itemIndex = itmp;

  //VBCAS_TXDRV[3:0]
  itmp = VBCAS_TXDRV_r07_b30();
  cmbVBCAS_TXDRV.itemIndex = itmp;

  //ICT_TXMIX[4:0]
  itmp = ICT_TXMIX_r08_b40();
  cmbICT_TXMIX.itemIndex = itmp;

  //ICT_TXDRV[4:0]
  itmp = ICT_TXDRV_r09_b40();
  cmbICT_TXDRV.itemIndex = itmp;

  //PW_VGA1_I
  itmp = PW_VGA1_I_r0A_b44();
  chbPwrVga1_I.checked = itmp;

  //PW_VGA1_Q
  itmp = PW_VGA1_Q_r0A_b33();
  chbPwrVga1_Q.checked = itmp;

  //PD_TXDRV
  itmp = PD_TXDRV_r0A_b22();
  chbPD_TXDRV.checked = itmp;

  //PD_TXLOBUF
  itmp = PD_TXLOBUF_r0A_b11();
  chbPD_TXLOBUF.checked = itmp;

  //PD_TXMIX
  itmp = PD_TXMIX_r0A_b00();
  chbPwrVga2.checked = itmp;

  //VGA1GAINT[7:0]
  itmp = VGA1GAINT_r0B_b70();
	switch(itmp)
	{
  	//DC Calibration
    case 0x06 :
    	cmbVga1G_t.itemIndex = 0x00;
		break;
    case 0x07:
      cmbVga1G_t.itemIndex = 0x01;
		break;
    case 0x08:
      cmbVga1G_t.itemIndex = 0x02;
		break;
    case 0x09:
      cmbVga1G_t.itemIndex = 0x03;
		break;
    case 0x0A:
      cmbVga1G_t.itemIndex = 0x04;
		break;
    case 0x0B:
      cmbVga1G_t.itemIndex = 0x05;
		break;
    case 0x0D:
      cmbVga1G_t.itemIndex = 0x06;
		break;
    case 0x0F:
      cmbVga1G_t.itemIndex = 0x07;
		break;
    case 0x11:
      cmbVga1G_t.itemIndex = 0x08;
		break;
    case 0x13:
      cmbVga1G_t.itemIndex = 0x09;
		break;
    case 0x15:
      cmbVga1G_t.itemIndex = 0x0A;
		break;
    case 0x18:
      cmbVga1G_t.itemIndex = 0x0B;
		break;
    case 0x1B:
      cmbVga1G_t.itemIndex = 0x0C;
		break;
    case 0x1F:
      cmbVga1G_t.itemIndex = 0x0D;
		break;
    case 0x23:
      cmbVga1G_t.itemIndex = 0x0E;
		break;
    case 0x27:
      cmbVga1G_t.itemIndex = 0x0F;
		break;
    case 0x2C:
      cmbVga1G_t.itemIndex = 0x10;
		break;
    case 0x32:
      cmbVga1G_t.itemIndex = 0x11;
		break;
    case 0x38:
      cmbVga1G_t.itemIndex = 0x12;
		break;
    case 0x3F:
      cmbVga1G_t.itemIndex = 0x13;
		break;
    case 0x47:
      cmbVga1G_t.itemIndex = 0x14;
		break;
    case 0x50:
      cmbVga1G_t.itemIndex = 0x15;
		break;
    case 0x5A:
      cmbVga1G_t.itemIndex = 0x16;
		break;
    case 0x65:
      cmbVga1G_t.itemIndex = 0x17;
		break;
    case 0x71:
      cmbVga1G_t.itemIndex = 0x18;
		break;
    case 0x7F:
      cmbVga1G_t.itemIndex = 0x19;
		break;
    case 0x8F:
      cmbVga1G_t.itemIndex = 0x1A;
		break;
    case 0xA0:
      cmbVga1G_t.itemIndex = 0x1B;
		break;
    case 0xB4:
      cmbVga1G_t.itemIndex = 0x1C;
		break;
    case 0xCA:
      cmbVga1G_t.itemIndex = 0x1D;
		break;
    case 0xE3:
      cmbVga1G_t.itemIndex = 0x1E;
		break;
    case 0xFF:
      cmbVga1G_t.itemIndex = 0x1F;
		break;

    default:
    	cmbVga1G_t.itemIndex = 0x1F;
		bRez = false;
  };

  //G_TXVGA2[8:0]
  itmp = G_TXVGA2();
  cmbVga2G_t.itemIndex = itmp;


  m_bAllowSend = true;
  return bRez;
};

/**
    Writes register map to the file. According to the customer wish.
    @param out stream for output
*/
void TxRf_Module::MakeRegisterFile(ofstream &out)
{
  int itmp;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  //EN
  out.width(24); out << left; out << "REG 0x40 MASK 01 : 01  =";
  itmp = EN_r00_b11();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_EN"; out << endl;

  //DECODE
  out.width(24); out << left; out << "REG 0x40 MASK 00 : 00  =";
  itmp = DECODE_r00_b00();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_DECODE"; out << endl;

  //VGA1GAIN[4:0]
  out.width(24); out << left; out << "REG 0x41 MASK 04 : 00  =";
  itmp = VGA1GAIN_r01_b40();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_VGA1GAIN"; out << endl;

  //VGA1DC_I[7:0]
  out.width(24); out << left; out << "REG 0x42 MASK 07 : 00  =";
  itmp = VGA1DC_I_r02_b70();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_VGA1DC_I"; out << endl;

  //VGA1DC_Q[7:0]
  out.width(24); out << left; out << "REG 0x43 MASK 07 : 00  =";
  itmp = VGA1DC_Q_r03_b70();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_VGA1DC_Q"; out << endl;

  //PA_EN[2:0]
  out.width(24); out << left; out << "REG 0x44 MASK 04 : 03  =";
  itmp = PA_EN_r04_b42();
  //itmp = itmp << 1;
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PA_EN"; out << endl;

  //PD_DRVAUX
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    out.width(24); out << left; out << "REG 0x44 MASK 02 : 02  =";
    itmp = PD_DRVAUX_r04_b22_v1();
  }
  else
  {
    out.width(24); out << left; out << "REG 0x44 MASK 01 : 01  =";
    itmp = PD_DRVAUX_r04_b11_v0();
  };
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PD_DRVAUX"; out << endl;

  //PD_PKDET
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    out.width(24); out << left; out << "REG 0x4E MASK 07 : 07  =";
    itmp = PD_PKDET_r0E_b77_v1();
  }
  else
  {
    out.width(24); out << left; out << "REG 0x44 MASK 00 : 00  =";
    itmp = PD_PKDET_r04_b00_v0();
  };
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PD_PKDET"; out << endl;

  //VGA2GAIN[4:0]
  out.width(24); out << left; out << "REG 0x45 MASK 07 : 03  =";
  itmp = VGA2GAIN_r05_b73();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_VGA2GAIN"; out << endl;

  //ENVD[2]
  out.width(24); out << left; out << "REG 0x45 MASK 00 : 00  =";
  itmp = ENVD_r05_b22();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_ENVD[2]"; out << endl;

  //ENVD[1:0]
  out.width(24); out << left; out << "REG 0x45 MASK 02 : 01  =";
  itmp = ENVD_r05_b10();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_ENVD[1:0]"; out << endl;

  //PKDBW[3:0]
  out.width(24); out << left; out << "REG 0x46 MASK 07 : 04  =";
  itmp = PKDBW_r06_b74();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PKDBW"; out << endl;

  //LOOPBBEN[1:0]
  out.width(24); out << left; out << "REG 0x46 MASK 03 : 02  =";
  itmp = LOOPBBEN_r06_b32();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_LOOPBBEN"; out << endl;

  //FST_PKDET
  out.width(24); out << left; out << "REG 0x46 MASK 01 : 01  =";
  itmp = FST_PKDET_r06_b11();
  out.width(6); out << right; out << itmp;
  out << "  FST_PKDET"; out << endl;

  //FST_TXHFBIAS
  out.width(24); out << left; out << "REG 0x46 MASK 00 : 00  =";
  itmp = FST_TXHFBIAS_r06_b00();
  out.width(6); out << right; out << itmp;
  out << "  FST_TXHFBIAS"; out << endl;

  //ICT_TXLOBUF[3:0]
  out.width(24); out << left; out << "REG 0x47 MASK 07 : 04  =";
  itmp = ICT_TXLOBUF_r07_b74();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_ICT_TXLOBUF"; out << endl;

  //VBCAS_TXDRV_r07_b30[3:0]
  out.width(24); out << left; out << "REG 0x47 MASK 03 : 00  =";
  itmp = VBCAS_TXDRV_r07_b30();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_VBCAS_TXDRV"; out << endl;

  //ICT_TXMIX[4:0]
  out.width(24); out << left; out << "REG 0x48 MASK 04 : 00  =";
  itmp = ICT_TXMIX_r08_b40();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_ICT_TXMIX"; out << endl;

  //ICT_TXDRV[4:0]
  out.width(24); out << left; out << "REG 0x98 MASK 04 : 00  =";
  itmp = ICT_TXDRV_r09_b40();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_ICT_TXDRV"; out << endl;

  //EN_VGA1_I
  out.width(24); out << left; out << "REG 0x4A MASK 04 : 04  =";
  itmp = PW_VGA1_I_r0A_b44();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PW_VGA1_I"; out << endl;

  //EN_VGA1_Q
  out.width(24); out << left; out << "REG 0x4A MASK 03 : 03  =";
  itmp = PW_VGA1_Q_r0A_b33();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PW_VGA1_Q"; out << endl;

  //PD_TXDRV
  out.width(24); out << left; out << "REG 0x4A MASK 02 : 02  =";
  itmp = PD_TXDRV_r0A_b22();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PD_TXDRV"; out << endl;

  //PD_TXLOBUF
  out.width(24); out << left; out << "REG 0x4A MASK 01 : 01  =";
  itmp = PD_TXLOBUF_r0A_b11();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PD_TXLOBUF"; out << endl;

  //PD_TXMIX
  out.width(24); out << left; out << "REG 0x4A MASK 00 : 00  =";
  itmp = PD_TXMIX_r0A_b00();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_PD_TXMIX"; out << endl;

  //VGA1GAINT[7:0]
  out.width(24); out << left; out << "REG 0x4B MASK 07 : 00  =";
  itmp = VGA1GAINT_r0B_b70();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_VGA1GAINT"; out << endl;

  //VGA2GAINT[8:1]
  out.width(24); out << left; out << "REG 0x4C MASK 07 : 00  =";
  itmp = G_TXVGA2_r0C_b81();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_G_TXVGA1[8:1]"; out << endl;

  //VGA2GAINT[0]
  out.width(24); out << left; out << "REG 0x4D MASK 07 : 07  =";
  itmp = G_TXVGA2_r0D_b77();
  out.width(6); out << right; out << itmp;
  out << "  TXRF_G_TXVGA1[0]"; out << endl;
}

/**
    Saves configuration to ini file
    @param pini pointer to ini file parser
*/
void TxRf_Module::SaveConf(ini_t *pini)
{
	char Sect[80];
	sprintf(Sect, "%i", (int)m_cMAddr);
	pini->Create(Sect);

	pini->Set("chbPwrTxRfMods", chbPwrTxRfMods.checked);
	pini->Set("rgrDecode", rgrDecode.itemIndex);

	pini->Set("cmbVga1G_u", cmbVga1G_u.itemIndex);
	pini->Set("cmbVga1DcI", cmbVga1DcI.itemIndex);
	pini->Set("cmbVga1DcQ", cmbVga1DcQ.itemIndex);

	pini->Set("rgrPA", rgrPA.itemIndex);
	pini->Set("chbPD_DRVAUX", chbPD_DRVAUX.checked);
	pini->Set("chbPD_PKDET", chbPD_PKDET.checked);

	pini->Set("cmbVga2G_u", cmbVga2G_u.itemIndex);
	pini->Set("cmbENVD", cmbENVD.itemIndex);
	pini->Set("cmbENVD2", cmbENVD2.itemIndex);

	pini->Set("cmbPKDBW", cmbPKDBW.itemIndex);
	pini->Set("rgrLOOPBBEN", rgrLOOPBBEN.itemIndex);
	pini->Set("chbFST_PKDET", chbFST_PKDET.checked);
	pini->Set("chbFST_TXHFBIAS", chbFST_TXHFBIAS.checked);

	pini->Set("cmbICT_TXLOBUF", cmbICT_TXLOBUF.itemIndex);
	pini->Set("cmbVBCAS_TXDRV", cmbVBCAS_TXDRV.itemIndex);

	pini->Set("cmbICT_TXMIX", cmbICT_TXMIX.itemIndex);

	pini->Set("cmbICT_TXDRV", cmbICT_TXDRV.itemIndex);

	pini->Set("chbPwrVga1_I", chbPwrVga1_I.checked);
	pini->Set("chbPwrVga1_Q", chbPwrVga1_Q.checked);
	pini->Set("chbPD_TXDRV", chbPD_TXDRV.checked);
	pini->Set("chbPD_TXLOBUF", chbPD_TXLOBUF.checked);
	pini->Set("chbPwrVga2", chbPwrVga2.checked);

	pini->Set("cmbVga1G_t", cmbVga1G_t.itemIndex);
	pini->Set("cmbVga2G_t", cmbVga2G_t.itemIndex);
};

/**
    Reads configuration from ini file
    @param pini pointer to ini file parser
*/
void TxRf_Module::ReadConf(ini_t *pini)
{
	char Sect[80];
	sprintf(Sect, "%i", (int)m_cMAddr);
	pini->Select(Sect);

	m_bAllowSend = false;

	chbPwrTxRfMods.checked = pini->Get("chbPwrTxRfMods", 1);
	rgrDecode.itemIndex = pini->Get("rgrDecode", 0);

	cmbVga1G_u.itemIndex = pini->Get("cmbVga1G_u", 21);
	cmbVga1DcI.itemIndex = pini->Get("cmbVga1DcI", 128);
	cmbVga1DcQ.itemIndex = pini->Get("cmbVga1DcQ", 128);

	rgrPA.itemIndex = pini->Get("rgrPA", 1);
	chbPD_DRVAUX.checked = pini->Get("chbPD_DRVAUX", 1);
	chbPD_PKDET.checked = pini->Get("chbPD_PKDET", 0);

	cmbVga2G_u.itemIndex = pini->Get("cmbVga2G_u", 0);
	cmbENVD.itemIndex = pini->Get("cmbENVD", 0);
	cmbENVD2.itemIndex = pini->Get("cmbENVD2", 0);

	cmbPKDBW.itemIndex = pini->Get("cmbPKDBW", 0);
	rgrLOOPBBEN.itemIndex = pini->Get("rgrLOOPBBEN", 0);
	chbFST_PKDET.checked = pini->Get("chbFST_PKDET", 0);
	chbFST_TXHFBIAS.checked = pini->Get("chbFST_TXHFBIAS", 0);

	cmbICT_TXLOBUF.itemIndex = pini->Get("cmbICT_TXLOBUF", 6);
	cmbVBCAS_TXDRV.itemIndex = pini->Get("cmbVBCAS_TXDRV", 0);

	cmbICT_TXMIX.itemIndex = pini->Get("cmbICT_TXMIX", 12);

	cmbICT_TXDRV.itemIndex = pini->Get("cmbICT_TXDRV", 12);

	chbPwrVga1_I.checked = pini->Get("chbPwrVga1_I", 1);
	chbPwrVga1_Q.checked = pini->Get("chbPwrVga1_Q", 1);
	chbPD_TXDRV.checked = pini->Get("chbPD_TXDRV", 0);
	chbPD_TXLOBUF.checked = pini->Get("chbPD_TXLOBUF", 0);
	chbPwrVga2.checked = pini->Get("chbPwrVga2", 0);

	cmbVga1G_t.itemIndex = pini->Get("cmbVga1G_t", 21);
	cmbVga2G_t.itemIndex = pini->Get("cmbVga2G_t", 0);

	m_bAllowSend = true;

};

void TxRf_Module::setPD_DRVAUX(bool state)
{
	chbPD_DRVAUX.checked = state;
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    if(m_bAllowSend){ MakeData(0x101); pMainModule->CMAutoDownload(m_cMAddr);  };
  }
  else
  {
    if(m_bAllowSend){ MakeData(0x10); pMainModule->CMAutoDownload(m_cMAddr);  };
  };
}
bool TxRf_Module::getPD_DRVAUX()
{
	return chbPD_DRVAUX.checked;
}
//---------------------------------------------------------------------------

void TxRf_Module::setPD_PKDET(bool state)
{
	chbPD_PKDET.checked = state;
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    if(m_bAllowSend){ MakeData(0x111); pMainModule->CMAutoDownload(m_cMAddr);  };
  }
  else
  {
    if(m_bAllowSend){ MakeData(0x11); pMainModule->CMAutoDownload(m_cMAddr);  };
  };
}
bool TxRf_Module::getPD_PKDET()
{
	return chbPD_PKDET.checked;
}
//---------------------------------------------------------------------------

void TxRf_Module::setENVD(int index)
{
	cmbENVD.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x12); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getENVD()
{
	return cmbENVD.itemIndex;
}
//---------------------------------------------------------------------------

void TxRf_Module::setENVD2(int index)
{
	cmbENVD2.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x13); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getENVD2()
{
	return cmbENVD2.itemIndex;
}
//---------------------------------------------------------------------------

void TxRf_Module::setPKDBW(int index)
{
	cmbPKDBW.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x14); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getPKDBW()
{
	return cmbPKDBW.itemIndex;
}
//---------------------------------------------------------------------------

void TxRf_Module::setFST_PKDET(bool state)
{
	chbFST_PKDET.checked = state;
	if(m_bAllowSend){ MakeData(0x15); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getFST_PKDET()
{
	return chbFST_PKDET.checked;
}
//---------------------------------------------------------------------------

void TxRf_Module::setFST_TXHFBIAS(bool state)
{
	chbFST_TXHFBIAS.checked = state;
	if(m_bAllowSend){ MakeData(0x16); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getFST_TXHFBIAS()
{
	return chbFST_TXHFBIAS.checked;
}
//---------------------------------------------------------------------------

void TxRf_Module::setICT_TXLOBUF(int index)
{
	cmbICT_TXLOBUF.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x17); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getICT_TXLOBUF()
{
	return cmbICT_TXLOBUF.itemIndex;
}
//---------------------------------------------------------------------------

void TxRf_Module::setVBCAS_TXDRV(int index)
{
	cmbVBCAS_TXDRV.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x18); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getVBCAS_TXDRV()
{
	return cmbVBCAS_TXDRV.itemIndex;
}
//---------------------------------------------------------------------------

void TxRf_Module::setICT_TXMIX(int index)
{
	cmbICT_TXMIX.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x19); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getICT_TXMIX()
{
	return cmbICT_TXMIX.itemIndex;
}
//---------------------------------------------------------------------------

void TxRf_Module::setICT_TXDRV(int index)
{
	cmbICT_TXDRV.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x1A); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int TxRf_Module::getICT_TXDRV()
{
	return cmbICT_TXDRV.itemIndex;
}
//---------------------------------------------------------------------------

void TxRf_Module::setPD_TXLOBUF(bool state)
{
	chbPD_TXLOBUF.checked = state;
	if(m_bAllowSend){ MakeData(0x1B); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getPD_TXLOBUF()
{
	return chbPD_TXLOBUF.checked;
}
//---------------------------------------------------------------------------

void TxRf_Module::setPD_TXDRV(bool state)
{
	chbPD_TXDRV.checked = state;
	if(m_bAllowSend){ MakeData(0x1D); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool TxRf_Module::getPD_TXDRV()
{
	return chbPD_TXDRV.checked;
}
//---------------------------------------------------------------------------

void TxRf_Module::CustSet_cmbICT_TXLOBUF(int Ind)
{
	setICT_TXLOBUF(Ind);
};

//---------------------------------------------------------------------------
// Functions for register testing
//---------------------------------------------------------------------------
void TxRf_Module::RT_SetTestMask(char Mask)
{
  MakeWriteAll();

	for(int i=0; i<m_psD.iToW; i++)
	{
    m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
  };

  pMainModule->CMAutoDownload(m_cMAddr);
};
