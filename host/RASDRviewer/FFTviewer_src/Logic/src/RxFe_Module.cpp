// -----------------------------------------------------------------------------
// FILE: 		RxFe_Module.cpp
// DESCRIPTION:	RxFE control user interface
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "RxFe_Module.h"
#include "ConnectionManager.h"
#include "Main_Module.h"
//---------------------------------------------------------------------------
//0x0
#define                      DECODE_r00_b11() ((m_psD.cDataR[0x00] & 0x02) >> 1)
#define                          EN_r00_b00() ((m_psD.cDataR[0x00] & 0x01) >> 0)
//0x1
#define             IN1SEL_MIX_RXFE_r01_b77() ((m_psD.cDataR[0x01] & 0x80) >> 7)
#define                DCOFF_I_RXFE_r01_b60() ((m_psD.cDataR[0x01] & 0x7F) >> 0)
//0x2
#define             INLOAD_LNA_RXFE_r02_b77() ((m_psD.cDataR[0x02] & 0x80) >> 7)
#define                DCOFF_Q_RXFE_r02_b60() ((m_psD.cDataR[0x02] & 0x7F) >> 0)
//0x3
#define              XLOAD_LNA_RXFE_r03_b77() ((m_psD.cDataR[0x03] & 0x80) >> 7)
#define              IP2TRIM_I_RXFE_r03_b60() ((m_psD.cDataR[0x03] & 0x7F) >> 0)
//0x4
#define              IP2TRIM_Q_RXFE_r04_b60() ((m_psD.cDataR[0x04] & 0x7F) >> 0)
//0x5
#define                  G_LNA_RXFE_r05_b76() ((m_psD.cDataR[0x05] & 0xC0) >> 6)
#define                 LNASEL_RXFE_r05_b54() ((m_psD.cDataR[0x05] & 0x30) >> 4)
#define                CBE_LNA_RXFE_r05_b30() ((m_psD.cDataR[0x05] & 0x0F) >> 0)
//0x6
#define                RFB_TIA_RXFE_r06_b60() ((m_psD.cDataR[0x06] & 0x7F) >> 0)
//0x7
#define                CFB_TIA_RXFE_r07_b60() ((m_psD.cDataR[0x07] & 0x7F) >> 0)
//0x8
#define             RDLEXT_LNA_RXFE_r08_b50() ((m_psD.cDataR[0x08] & 0x3F) >> 0)
//0x9
#define             RDLINT_LNA_RXFE_r09_b50() ((m_psD.cDataR[0x09] & 0x3F) >> 0)
//0xA
#define                ICT_MIX_RXFE_r0A_b74() ((m_psD.cDataR[0x0A] & 0xF0) >> 4)
#define                ICT_LNA_RXFE_r0A_b30() ((m_psD.cDataR[0x0A] & 0x0F) >> 0)
//0xB
#define                ICT_TIA_RXFE_r0B_b74() ((m_psD.cDataR[0x0B] & 0xF0) >> 4)
#define              ICT_MXLOB_RXFE_r0B_b30() ((m_psD.cDataR[0x0B] & 0x0F) >> 0)
//0xC
#define               LOBN_MIX_RXFE_r0C_b63() ((m_psD.cDataR[0x0C] & 0x78) >> 3)
#define              RINEN_MIX_RXFE_r0C_b22() ((m_psD.cDataR[0x0C] & 0x04) >> 2)
#define            G_FINE_LNA3_RXFE_r0C_b10() ((m_psD.cDataR[0x0C] & 0x03) >> 0)
//0xD
#define                 PD_TIA_RXFE_r0D_b33() ((m_psD.cDataR[0x0D] & 0x08) >> 3)
#define              PD_MXLOB_RXFE2_r0D_b22() ((m_psD.cDataR[0x0D] & 0x04) >> 2)
#define                 PD_MIX_RXFE_r0D_b11() ((m_psD.cDataR[0x0D] & 0x02) >> 1)
#define                 PD_LNA_RXFE_r0D_b00() ((m_psD.cDataR[0x0D] & 0x01) >> 0)


#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A ",20"

//---------------------------------------------------------------------------
RxFe_Module::RxFe_Module()
{
	pMainModule = NULL;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
RxFe_Module::~RxFe_Module()
{
	delete[] m_psD.cCmdW;
	delete[] m_psD.cDataW;
	delete[] m_psD.cCmdR;
	delete[] m_psD.cDataR;
	delete[] m_psD.iRInd;
	delete[] m_psD.iWInd;
	delete[] m_psD.cTestMap; //RT//
}

char RxFe_Module::getAddr()
{
	return m_cMAddr;
}

//---------------------------------------------------------------------------
void RxFe_Module::Initialize(Main_Module *pMain, char MAddr)
{
	pMainModule = pMain;
	m_cMAddr = MAddr;

	m_psD.iLen = RxFELen;
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
  m_psD.cTestMap[0x0] = 0x03;
  m_psD.cTestMap[0x1] = 0xFF;
  m_psD.cTestMap[0x2] = 0xFF;
  m_psD.cTestMap[0x3] = 0xFF;
  m_psD.cTestMap[0x4] = 0x7F;
  m_psD.cTestMap[0x5] = 0xFF;
  m_psD.cTestMap[0x6] = 0x7F;
  m_psD.cTestMap[0x7] = 0x7F;
  m_psD.cTestMap[0x8] = 0x3F;
  m_psD.cTestMap[0x9] = 0x3F;
  m_psD.cTestMap[0xA] = 0xFF;
  m_psD.cTestMap[0xB] = 0xFF;
  m_psD.cTestMap[0xC] = 0x7F;
  m_psD.cTestMap[0xD] = 0x0F;
  //m_psD.cTestMap[0xE] = 0xFF;
  //m_psD.cTestMap[0xF] = 0xFF;

  SetDefaults();

};

//---------------------------------------------------------------------------
void RxFe_Module::SetDefaults()
{
	int itmp;
	m_bAllowSend = false;

	//DECODE
  rgrDecode.itemIndex = 0;
  //EN
  chbPwrRxFeMods.checked = true;

  //IN1SEL_MIX_RXFE
  cmbIN1SEL_MIX_RXFE.clear();
  cmbIN1SEL_MIX_RXFE.add("To Pads");
  cmbIN1SEL_MIX_RXFE.add("To LNA Out");
  cmbIN1SEL_MIX_RXFE.itemIndex = 1;

	//DCOFF_I_RXFE[6:0]
  //DCOFF_Q_RXFE[6:0]
	cmbDCOFF_I_RXFE.clear();
  cmbDCOFF_Q_RXFE.clear();
  for(int i=0; i<127; i++)
  {
  	cmbDCOFF_I_RXFE.add(i-63);
    cmbDCOFF_Q_RXFE.add(i-63);
  };
  cmbDCOFF_I_RXFE.itemIndex = 63;
  cmbDCOFF_Q_RXFE.itemIndex = 63;

  //INLOAD_LNA_RXFE
  chbINLOAD_LNA_RXFE.checked = true;

  //XLOAD_LNA_RXFE
  chbXLOAD_LNA_RXFE.checked = false;

	//IP2TRIM_I_RXFE[6:0]
  //IP2TRIM_Q_RXFE[6:0]
	cmbIP2TRIM_I_RXFE.clear();
  cmbIP2TRIM_Q_RXFE.clear();
  for(int i=0; i<127; i++)
  {
  	cmbIP2TRIM_I_RXFE.add(i-63);
    cmbIP2TRIM_Q_RXFE.add(i-63);
  };
  cmbIP2TRIM_I_RXFE.itemIndex = 63;
  cmbIP2TRIM_Q_RXFE.itemIndex = 63;

  //G_LNA_RXFE[1:0]
  cmbG_LNA_RXFE.clear();
  //cmbG_LNA_RXFE.add("TBC");
  cmbG_LNA_RXFE.add("Bypass");
  cmbG_LNA_RXFE.add("Mid Gain");
  cmbG_LNA_RXFE.add("Max Gain");
  cmbG_LNA_RXFE.itemIndex = 2;

  //LNASEL_RXFE[1:0]
  cmbLNASEL_RXFE.clear();
  cmbLNASEL_RXFE.add("Disabled");
  cmbLNASEL_RXFE.add("LNA 1");
  cmbLNASEL_RXFE.add("LNA 2");
  cmbLNASEL_RXFE.add("LNA 3");
  cmbLNASEL_RXFE.itemIndex = 1;

	//CBE_LNA_RXFE[3:0]
	cmbCBE_LNA_RXFE.clear();
  for(int i=0; i<16; i++)
  {
  	cmbCBE_LNA_RXFE.add(i);
  };
  cmbCBE_LNA_RXFE.itemIndex = 0;

	//RFB_TIA_RXFE[6:0]
	cmbRFB_TIA_RXFE.clear();
  for(int i=0; i<128; i++)
  {
  	cmbRFB_TIA_RXFE.add(i);
  };
  cmbRFB_TIA_RXFE.itemIndex = 120;

	//CFB_TIA_RXFE[6:0]
	cmbCFB_TIA_RXFE.clear();
  for(int i=0; i<128; i++)
  {
  	cmbCFB_TIA_RXFE.add(i);
  };
  cmbCFB_TIA_RXFE.itemIndex = 0;

	//RDLEXT_LNA_RXFE[6:0]
  //RDLINT_LNA_RXFE[6:0]
	cmbRDLEXT_LNA_RXFE.clear();
  cmbRDLINT_LNA_RXFE.clear();
  for(int i=0; i<64; i++)
  {
  	cmbRDLEXT_LNA_RXFE.add(i);
    cmbRDLINT_LNA_RXFE.add(i);
  };
  cmbRDLEXT_LNA_RXFE.itemIndex = 28;
  cmbRDLINT_LNA_RXFE.itemIndex = 28;

	//ICT_MIX_RXFE[3:0]
	cmbICT_MIX_RXFE.clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_MIX_RXFE.add(i);
  };
  cmbICT_MIX_RXFE.itemIndex = 7;
	//ICT_LNA_RXFE[3:0]
	cmbICT_LNA_RXFE.clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_LNA_RXFE.add(i);
  };
  cmbICT_LNA_RXFE.itemIndex = 7;

	//ICT_TIA_RXFE[3:0]
	cmbICT_TIA_RXFE.clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_TIA_RXFE.add(i);
  };
  cmbICT_TIA_RXFE.itemIndex = 7;
	//ICT_MXLOB_RXFE[3:0]
	cmbICT_MXLOB_RXFE.clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_MXLOB_RXFE.add(i);
  };
  cmbICT_MXLOB_RXFE.itemIndex = 7;

	//LOBN_MIX_RXFE[3:0]
	cmbLOBN_MIX_RXFE.clear();
  for(int i=0; i<16; i++)
  {
  	cmbLOBN_MIX_RXFE.add(i);
  };
  cmbLOBN_MIX_RXFE.itemIndex = 3;
  //RINEN_MIX_RXFE
	chbRINEN_MIX_RXFE.checked = false;
	//G_FINE_LNA3_RXFE[1:0]
	cmbG_FINE_LNA3_RXFE.clear();
  cmbG_FINE_LNA3_RXFE.add("+0 dB");
  cmbG_FINE_LNA3_RXFE.add("+1 dB");
  cmbG_FINE_LNA3_RXFE.add("+2 dB");
  cmbG_FINE_LNA3_RXFE.add("+3 dB");
	cmbG_FINE_LNA3_RXFE.itemIndex = 0;

  //PD_TIA_RXFE
  chbPD_TIA_RXFE.checked = true;
  //PD_MXLOB_RXFE
  chbPD_MXLOB_RXFE.checked = true;
  //PD_MIX_RXFE
  chbPD_MIX_RXFE.checked = true;
  //PD_LNA_RXFE
  chbPD_LNA_RXFE.checked = true;


  //SetGuiDecode();

  m_bAllowSend = true;
};

//----------------------------------------------------------------------------
// Make data to download
//----------------------------------------------------------------------------
void RxFe_Module::MakeData(int rAddr)
{
	char btmp;
  int itmp;

	//======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;
	//DECODE
	btmp = (char)rgrDecode.itemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x00] |= btmp;
	//EN
	btmp = chbPwrRxFeMods.checked == true ? 1 : 0;
	btmp = btmp << 0; m_psD.cDataW[0x00] |= btmp;

	//======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;
  //IN1SEL_MIX_RXFE
	btmp = (char)cmbIN1SEL_MIX_RXFE.itemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x01] |= btmp;
  //DCOFF_I_RXFE
	//btmp = (char)((cmbDCOFF_I_RXFE.itemIndex-64)&0x7F);
  itmp = (cmbDCOFF_I_RXFE.itemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x01] |= btmp;

	//======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
  //INLOAD_LNA_RXFE
	btmp = chbINLOAD_LNA_RXFE.checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x02] |= btmp;
  //DCOFF_Q_RXFE
	//btmp = (char)((cmbDCOFF_Q_RXFE.itemIndex-64)&0x7F);
  itmp = (cmbDCOFF_Q_RXFE.itemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x02] |= btmp;

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //XLOAD_LNA_RXFE
	btmp = chbXLOAD_LNA_RXFE.checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x03] |= btmp;
  //IP2TRIM_I_RXFE
	//btmp = (char)((cmbIP2TRIM_I_RXFE.itemIndex-64)&0x7F);
  itmp = (cmbIP2TRIM_I_RXFE.itemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x03] |= btmp;

	//======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
  //IP2TRIM_Q_RXFE
	//btmp = (char)((cmbIP2TRIM_Q_RXFE.itemIndex-64)&0x7F);
  itmp = (cmbIP2TRIM_Q_RXFE.itemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x04] |= btmp;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
  //G_LNA_RXFE
	btmp = (char)cmbG_LNA_RXFE.itemIndex + 1;
	btmp = btmp << 6; m_psD.cDataW[0x05] |= btmp;
  //LNASEL_RXFE
	btmp = (char)cmbLNASEL_RXFE.itemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x05] |= btmp;
  //CBE_LNA_RXFE
	btmp = (char)cmbCBE_LNA_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x05] |= btmp;

	//======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
  //RFB_TIA_RXFE
	btmp = (char)cmbRFB_TIA_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
  //CFB_TIA_RXFE
	btmp = (char)cmbCFB_TIA_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x07] |= btmp;

	//======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
  //RDLEXT_LNA_RXFE
	btmp = (char)cmbRDLEXT_LNA_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x08] |= btmp;

	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //RDLINT_LNA_RXFE
	btmp = (char)cmbRDLINT_LNA_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

	//======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
  //ICT_MIX_RXFE[3:0]
	btmp = (char)cmbICT_MIX_RXFE.itemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0A] |= btmp;
  //ICT_LNA_RXFE[3:0]
	btmp = (char)cmbICT_LNA_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;

	//======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
  //ICT_TIA_RXFE[3:0]
	btmp = (char)cmbICT_TIA_RXFE.itemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0B] |= btmp;
  //ICT_MXLOB_RXFE[3:0]
	btmp = (char)cmbICT_MXLOB_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0B] |= btmp;

	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
  //LOBN_MIX_RXFE
	btmp = (char)cmbLOBN_MIX_RXFE.itemIndex;
	btmp = btmp << 3; m_psD.cDataW[0x0C] |= btmp;
  //RINEN_MIX_RXFE
	btmp = chbRINEN_MIX_RXFE.checked == true ? 1 : 0;
	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
	//G_FINE_LNA3_RXFE[1:0]
	btmp = cmbG_FINE_LNA3_RXFE.itemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;

	//======= register addr 0x0D =======
	m_psD.cDataW[0x0D] = 0x00;
  //PD_TIA_RXFE
	btmp = chbPD_TIA_RXFE.checked == true ? 0 : 1;
	btmp = btmp << 3; m_psD.cDataW[0x0D] |= btmp;
  //PD_MXLOB_RXFE
	btmp = chbPD_MXLOB_RXFE.checked == true ? 0 : 1;
	btmp = btmp << 2; m_psD.cDataW[0x0D] |= btmp;
  //PD_MIX_RXFE
	btmp = chbPD_MIX_RXFE.checked == true ? 0 : 1;
	btmp = btmp << 1; m_psD.cDataW[0x0D] |= btmp;
  //PD_LNA_RXFE
	btmp = chbPD_LNA_RXFE.checked == true ? 0 : 1;
	btmp = btmp << 0; m_psD.cDataW[0x0D] |= btmp;



	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch(rAddr)
	{

		//User mode
		case 0x00:
		case 0x01:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x00;
		break;

		case 0x02:
		case 0x03:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x01;
		break;

		case 0x04:
		case 0x05:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x02;
		break;

		case 0x06:
		case 0x07:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x03;
		break;

		case 0x08:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x04;
		break;

		case 0x09:
		case 0x0A:
    case 0x0B:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x05;
		break;

    case 0x0C:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x06;
		break;

    case 0x0D:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x07;
		break;

    case 0x0E:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x08;
		break;

    case 0x0F:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x09;
		break;

		case 0x10:
    case 0x11:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0A;
		break;

		case 0x12:
    case 0x13:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0B;
		break;

		case 0x19:
		case 0x1F:
    case 0x1E:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0C;
		break;

    //Test mode
		case 0x1A:
    case 0x1B:
		case 0x1C:
    case 0x1D:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0D;
		break;

    //Customer Mode
		case 0x80:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x05;
		break;

		default:
			m_psD.iToW = 0;
	};
}
void RxFe_Module::setDecode(int index)
{
	rgrDecode.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x00); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getDecode()
{
	return rgrDecode.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setPwrRxFeMods(bool state)
{
	chbPwrRxFeMods.checked = state;
	if(m_bAllowSend){ MakeData(0x01); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getPwrRxFeMods()
{
	return chbPwrRxFeMods.checked;
}
//---------------------------------------------------------------------------
void RxFe_Module::setIN1SEL_MIX_RXFE(int index)
{
	cmbIN1SEL_MIX_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x02); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getIN1SEL_MIX_RXFE()
{
	return cmbIN1SEL_MIX_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setDCOFF_I_RXFE(int index)
{
	cmbDCOFF_I_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x03); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getDCOFF_I_RXFE()
{
	return cmbDCOFF_I_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setINLOAD_LNA_RXFE(bool state)
{
	chbINLOAD_LNA_RXFE.checked = state;
	if(m_bAllowSend){ MakeData(0x04); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getINLOAD_LNA_RXFE()
{
	return chbINLOAD_LNA_RXFE.checked;
}
//---------------------------------------------------------------------------
void RxFe_Module::setDCOFF_Q_RXFE(int index)
{
	cmbDCOFF_Q_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x05); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getDCOFF_Q_RXFE()
{
	return cmbDCOFF_Q_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setXLOAD_LNA_RXFE(bool state)
{
	chbXLOAD_LNA_RXFE.checked = state;
	if(m_bAllowSend){ MakeData(0x06); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getXLOAD_LNA_RXFE()
{
	return chbXLOAD_LNA_RXFE.checked;
}
//---------------------------------------------------------------------------
void RxFe_Module::setIP2TRIM_I_RXFE(int index)
{
	cmbIP2TRIM_I_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x07); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getIP2TRIM_I_RXFE()
{
	return cmbIP2TRIM_I_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setIP2TRIM_Q_RXFE(int index)
{
	cmbIP2TRIM_Q_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x08); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getIP2TRIM_Q_RXFE()
{
	return cmbIP2TRIM_Q_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setG_LNA_RXFE(int index)
{
	cmbG_LNA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x09); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getG_LNA_RXFE()
{
	return cmbG_LNA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setLNASEL_RXFE(int index)
{
	cmbLNASEL_RXFE.itemIndex = index;
	if(m_bAllowSend)
	{
		MakeData(0x0A);
		pMainModule->CMAutoDownload(m_cMAddr);
		pMainModule->Cust_setLNASEL(cmbLNASEL_RXFE.itemIndex);
	};
}
int RxFe_Module::getLNASEL_RXFE()
{
	return cmbLNASEL_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setCBE_LNA_RXFE(int index)
{
	cmbCBE_LNA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0B); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getCBE_LNA_RXFE()
{
	return cmbCBE_LNA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setRFB_TIA_RXFE(int index)
{
	cmbRFB_TIA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0C); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getRFB_TIA_RXFE()
{
	return cmbRFB_TIA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setCFB_TIA_RXFE(int index)
{
	cmbCFB_TIA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0D); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getCFB_TIA_RXFE()
{
	return cmbCFB_TIA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setRDLEXT_LNA_RXFE(int index)
{
	cmbRDLEXT_LNA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0E); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getRDLEXT_LNA_RXFE()
{
	return cmbRDLEXT_LNA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setRDLINT_LNA_RXFE(int index)
{
	cmbRDLINT_LNA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x0F); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getRDLINT_LNA_RXFE()
{
	return cmbRDLINT_LNA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setICT_MIX_RXFE(int index)
{
	cmbICT_MIX_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x10); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getICT_MIX_RXFE()
{
	return cmbICT_MIX_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setICT_LNA_RXFE(int index)
{
	cmbICT_LNA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x11); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getICT_LNA_RXFE()
{
	return cmbICT_LNA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setICT_TIA_RXFE(int index)
{
	cmbICT_TIA_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x12); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getICT_TIA_RXFE()
{
	return cmbICT_TIA_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setICT_MXLOB_RXFE(int index)
{
	cmbICT_MXLOB_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x13); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getICT_MXLOB_RXFE()
{
	return cmbICT_MXLOB_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setLOBN_MIX_RXFE(int index)
{
	cmbLOBN_MIX_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x19); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getLOBN_MIX_RXFE()
{
	return cmbLOBN_MIX_RXFE.itemIndex;
}
//---------------------------------------------------------------------------
void RxFe_Module::setPD_TIA_RXFE(bool state)
{
	chbPD_TIA_RXFE.checked = state;
	if(m_bAllowSend){ MakeData(0x1A); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getPD_TIA_RXFE()
{
	return chbPD_TIA_RXFE.checked;
}
//---------------------------------------------------------------------------
void RxFe_Module::setPD_MXLOB_RXFE(bool state)
{
	chbPD_MXLOB_RXFE.checked = state;
	if(m_bAllowSend){ MakeData(0x1B); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getPD_MXLOB_RXFE()
{
	return chbPD_MXLOB_RXFE.checked;
}
//---------------------------------------------------------------------------
void RxFe_Module::setPD_MIX_RXFE(bool state)
{
	chbPD_MIX_RXFE.checked = state;
	if(m_bAllowSend){ MakeData(0x1C); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getPD_MIX_RXFE()
{
	return chbPD_MIX_RXFE.checked;
}
//---------------------------------------------------------------------------
void RxFe_Module::setPD_LNA_RXFE(bool state)
{
	chbPD_LNA_RXFE.checked = state;
	if(m_bAllowSend){ MakeData(0x1D); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getPD_LNA_RXFE()
{
	return chbPD_LNA_RXFE.checked;
}
//---------------------------------------------------------------------------
void RxFe_Module::setG_FINE_LNA3_RXFE(int index)
{
	cmbG_FINE_LNA3_RXFE.itemIndex = index;
	if(m_bAllowSend){ MakeData(0x1E); pMainModule->CMAutoDownload(m_cMAddr);  };
}
int RxFe_Module::getG_FINE_LNA3_RXFE()
{
	return cmbG_FINE_LNA3_RXFE.itemIndex;
}
//---------------------------------------------------------------------------

void RxFe_Module::setRINEN_MIX_RXFE(bool state)
{
	chbRINEN_MIX_RXFE.checked = state;
	if(m_bAllowSend){ MakeData(0x1F); pMainModule->CMAutoDownload(m_cMAddr);  };
}
bool RxFe_Module::getRINEN_MIX_RXFE()
{
	return chbRINEN_MIX_RXFE.checked;
}
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Make all data to write
//----------------------------------------------------------------------------
void RxFe_Module::MakeWriteAll()
{
	MakeData(0xFFFF);
	m_psD.iToW = m_psD.iLen;
	for(int i=0; i<m_psD.iLen; i++)
	{
		m_psD.iWInd[i] = i;
	};
};

//----------------------------------------------------------------------------
// Save the chip configuration to the file
//----------------------------------------------------------------------------
bool RxFe_Module::ChipVsGui(ofstream &out, string Caption, bool bWrAll)
{
  bool bRez = true;
  bool btmp;
	char str[64] = "";
  int itmp, itmpC;

  out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out.width(32); out << "| Register"; out.width(2); out << "|";
	out.width(50); out << "Value from PC"; out.width(2); out << "|";
	out.width(50); out << "Value from Chip"; out.width(1); out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------" << endl;


  //DECODE
  if((rgrDecode.itemIndex != DECODE_r00_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
    if(rgrDecode.itemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	if(DECODE_r00_b11()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN
  if((chbPwrRxFeMods.checked != (bool)EN_r00_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrRxFeMods.checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
	  if(EN_r00_b00()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };


  //IN1SEL_MIX_RXFE
  if((cmbIN1SEL_MIX_RXFE.itemIndex != IN1SEL_MIX_RXFE_r01_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| IN1SEL_MIX_RXFE"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbIN1SEL_MIX_RXFE.sItems[cmbIN1SEL_MIX_RXFE.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = IN1SEL_MIX_RXFE_r01_b77();
    strcpy(str, cmbIN1SEL_MIX_RXFE.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DCOFF_I_RXFE[6:0]
  itmpC = DCOFF_I_RXFE_r01_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
  //itmpC = (m_psD.cDataR[0x01] & 0x7F)>>0;
  //if(itmpC & 0x40) itmpC = itmpC & 0x3F;
  //else itmpC = itmpC + 64;
  if((cmbDCOFF_I_RXFE.itemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DCOFF_I_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = ((cmbDCOFF_I_RXFE.itemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //INLOAD_LNA_RXFE
  if((chbINLOAD_LNA_RXFE.checked != (bool)INLOAD_LNA_RXFE_r02_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| INLOAD_LNA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chbINLOAD_LNA_RXFE.checked) strcpy(str, "Internal Load Active"); else strcpy(str, "Internal Load Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(INLOAD_LNA_RXFE_r02_b77()) strcpy(str, "Internal Load Active"); else strcpy(str, "Internal Load Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DCOFF_Q_RXFE[6:0]
  itmpC = DCOFF_Q_RXFE_r02_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
//  itmpC = (m_psD.cDataR[0x02] & 0x7F)>>0;
//  if(itmpC & 0x40) itmpC = itmpC & 0x3F;
//  else itmpC = itmpC + 64;
  if((cmbDCOFF_Q_RXFE.itemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DCOFF_Q_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = ((cmbDCOFF_Q_RXFE.itemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; itmp = itmp >> 0; out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //XLOAD_LNA_RXFE
  if((chbXLOAD_LNA_RXFE.checked != (bool)XLOAD_LNA_RXFE_r03_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| XLOAD_LNA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chbXLOAD_LNA_RXFE.checked) strcpy(str, "External Load Active"); else strcpy(str, "External Load Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
	  if(XLOAD_LNA_RXFE_r03_b77()) strcpy(str, "External Load Active"); else strcpy(str, "External Load Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //IP2TRIM_I_RXFE[6:0]
  itmpC = IP2TRIM_I_RXFE_r03_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
//  itmpC = (m_psD.cDataR[0x03] & 0x7F)>>0;
//  if(itmpC & 0x40) itmpC = itmpC & 0x3F;
//  else itmpC = itmpC + 64;
  if((cmbIP2TRIM_I_RXFE.itemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| IP2TRIM_I_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
  	itmp = ((cmbIP2TRIM_I_RXFE.itemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; itmp = itmp >> 0; out << hex << showbase << uppercase;
    out << itmpC;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //IP2TRIM_Q_RXFE[6:0]
  itmpC = IP2TRIM_Q_RXFE_r04_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
//  itmpC = (m_psD.cDataR[0x04] & 0x7F)>>0;
//  if(itmpC & 0x40) itmpC = itmpC & 0x3F;
//  else itmpC = itmpC + 64;
  if((cmbIP2TRIM_Q_RXFE.itemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| IP2TRIM_Q_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = ((cmbIP2TRIM_Q_RXFE.itemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; itmp = itmp >> 0; out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //G_LNA_RXFE[1:0]
  if(((cmbG_LNA_RXFE.itemIndex + 1) != G_LNA_RXFE_r05_b76()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| G_LNA_RXFE[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbG_LNA_RXFE.sItems[cmbG_LNA_RXFE.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = G_LNA_RXFE_r05_b76();
    if(itmp > 0) itmp--;
    else itmp = 0;
    //strcpy(str, cmbG_LNA_RXFE.sItems[itmp-1].c_str());
    strcpy(str, cmbG_LNA_RXFE.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LNASEL_RXFE[1:0]
  if((cmbLNASEL_RXFE.itemIndex != LNASEL_RXFE_r05_b54()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| LNASEL_RXFE[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbLNASEL_RXFE.sItems[cmbLNASEL_RXFE.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = LNASEL_RXFE_r05_b54();
    strcpy(str, cmbLNASEL_RXFE.sItems[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CBE_LNA_RXFE[3:0]
  if((cmbCBE_LNA_RXFE.itemIndex != CBE_LNA_RXFE_r05_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CBE_LNA_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbCBE_LNA_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = CBE_LNA_RXFE_r05_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RFB_TIA_RXFE[6:0]
  if((cmbRFB_TIA_RXFE.itemIndex != RFB_TIA_RXFE_r06_b60()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RFB_TIA_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbRFB_TIA_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = RFB_TIA_RXFE_r06_b60(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CFB_TIA_RXFE[6:0]
  if((cmbCFB_TIA_RXFE.itemIndex != CFB_TIA_RXFE_r07_b60()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CFB_TIA_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbCFB_TIA_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = CFB_TIA_RXFE_r07_b60(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RDLEXT_LNA_RXFE[5:0]
  if((cmbRDLEXT_LNA_RXFE.itemIndex != RDLEXT_LNA_RXFE_r08_b50()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RDLEXT_LNA_RXFE[5:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbRDLEXT_LNA_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = RDLEXT_LNA_RXFE_r08_b50(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RDLINT_LNA_RXFE[5:0]
  if((cmbRDLINT_LNA_RXFE.itemIndex != RDLINT_LNA_RXFE_r09_b50()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RDLINT_LNA_RXFE[5:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbRDLINT_LNA_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = RDLINT_LNA_RXFE_r09_b50(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_MIX_RXFE[3:0]
  if((cmbICT_MIX_RXFE.itemIndex != ICT_MIX_RXFE_r0A_b74()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_MIX_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_MIX_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_MIX_RXFE_r0A_b74(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_LNA_RXFE[3:0]
  if((cmbICT_LNA_RXFE.itemIndex != ICT_LNA_RXFE_r0A_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_LNA_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_LNA_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_LNA_RXFE_r0A_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_TIA_RXFE[3:0]
  if((cmbICT_TIA_RXFE.itemIndex != ICT_TIA_RXFE_r0B_b74()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_TIA_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_TIA_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_TIA_RXFE_r0B_b74(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_MXLOB_RXFE[3:0]
  if((cmbICT_MXLOB_RXFE.itemIndex != ICT_MXLOB_RXFE_r0B_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_MXLOB_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_MXLOB_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_MXLOB_RXFE_r0B_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LOBN_MIX_RXFE[3:0]
  if((cmbLOBN_MIX_RXFE.itemIndex != LOBN_MIX_RXFE_r0C_b63()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| LOBN_MIX_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbLOBN_MIX_RXFE.itemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = LOBN_MIX_RXFE_r0C_b63(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RINEN_MIX_RXFE
  if((chbRINEN_MIX_RXFE.checked != (bool)RINEN_MIX_RXFE_r0C_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| RINEN_MIX_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chbRINEN_MIX_RXFE.checked) strcpy(str, "Active"); else strcpy(str, "Inactive");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(RINEN_MIX_RXFE_r0C_b22()) strcpy(str, "Active"); else strcpy(str, "Inactive");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //G_FINE_LNA3_RXFE[1:0]
  if((cmbG_FINE_LNA3_RXFE.itemIndex != G_FINE_LNA3_RXFE_r0C_b10()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| G_FINE_LNA3_RXFE[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbG_FINE_LNA3_RXFE.sItems[cmbG_FINE_LNA3_RXFE.itemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = G_FINE_LNA3_RXFE_r0C_b10();
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbG_FINE_LNA3_RXFE.sItems[itmp].c_str());
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
  };

  if((!bRez) || bWrAll)
  {
    out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |" << endl;
  };

  //PD_TIA_RXFE
  if((chbPD_TIA_RXFE.checked == (bool)PD_TIA_RXFE_r0D_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_TIA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chbPD_TIA_RXFE.checked) strcpy(str, "TIA powered up"); else strcpy(str, "TIA powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_TIA_RXFE_r0D_b33()) strcpy(str, "TIA powered down"); else strcpy(str, "TIA powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_MXLOB_RXFE
  if((chbPD_MXLOB_RXFE.checked == (bool)PD_MXLOB_RXFE2_r0D_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| PD_MXLOB_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chbPD_MXLOB_RXFE.checked) strcpy(str, "MXLOB powered up"); else strcpy(str, "MXLOB powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(PD_MXLOB_RXFE2_r0D_b22()) strcpy(str, "MXLOB powered down"); else strcpy(str, "MXLOB powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_MIX_RXFE
  if((chbPD_MIX_RXFE.checked == (bool)PD_MIX_RXFE_r0D_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_MIX_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chbPD_MIX_RXFE.checked) strcpy(str, "MIX powered up"); else strcpy(str, "MIX powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_MIX_RXFE_r0D_b11()) strcpy(str, "MIX powered down"); else strcpy(str, "MIX powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_LNA_RXFE
  if((chbPD_LNA_RXFE.checked == (bool)PD_LNA_RXFE_r0D_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| PD_LNA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chbPD_LNA_RXFE.checked) strcpy(str, "LNA powered up"); else strcpy(str, "LNA powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(PD_LNA_RXFE_r0D_b00()) strcpy(str, "LNA powered down"); else strcpy(str, "LNA powered up");
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
void RxFe_Module::MakeRVFFile(ofstream &out)
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
  iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0xFF);
  out << iRval; out << endl;

  //0x02
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
  out << iRval; out << endl;

  //0x03
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
  out << iRval; out << endl;

  //0x04
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x7F);
  out << iRval; out << endl;

  //0x05
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << iRval; out << endl;

  //0x06
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
  out << iRval; out << endl;

  //0x07
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0x7F);
  out << iRval; out << endl;

  //0x08
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0x7F);
  out << iRval; out << endl;

  //0x09
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x3F);
  out << iRval; out << endl;

  //0x0A
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
  out << iRval; out << endl;

  //0x0B
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << iRval; out << endl;

  //0x0C
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0x7F);
  out << iRval; out << endl;

  //0x0D
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0x7F);
  out << iRval; out << endl;

};

/**
    Saves chip configuration using FRIF format
    @param out stream for output
    @param FRIF_SPI_A rfif param
*/
void RxFe_Module::MakeRFIFFile(ofstream &out, const char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  out << "echo \"Now programming the Lime Rx FE\"" << endl << endl;

  //0x00
  //out << "# Register(s): DECODE, EN" << endl;
  iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0x03);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x01
  //out << "# Register(s): IN1SEL_MIX_RXFE, DCOFF_I_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x02
  //out << "# Register(s): INLOAD_LNA_RXFE, DCOFF_Q_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x03
  //out << "# Register(s): XLOAD_LNA_RXFE, IP2TRIM_I_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x04
  //out << "# Register(s): IP2TRIM_Q_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x05
  //out << "# Register(s): G_LNA_RXFE[1:0], LNASEL_RXFE[1:0], CBE_LNA_RXFE[3:0]" << endl;
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x06
  //out << "# Register(s): RFB_TIA_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x07
  //out << "# Register(s): CFB_TIA_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x08
  //out << "# Register(s): RDLEXT_LNA_RXFE[5:0]" << endl;
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x09
  //out << "# Register(s): RDLINT_LNA_RXFE[5:0]" << endl;
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0A
  //out << "# Register(s): ICT_MIX_RXFE[3:0], ICT_LNA_RXFE[3:0]" << endl;
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0B
  //out << "# Register(s): ICT_TIA_RXFE[3:0], ICT_MXLOB_RXFE[3:0]" << endl;
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0C
  //out << "# Register(s): LOBN_MIX_RXFE[3:0], RINEN_MIX_RXFE, G_FINE_LNA3_RXFE[1:0]" << endl;
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0D
  //out << "# Register(s): PD_TIA_RXFE, PD_MXLOB_RXFE, PD_MIX_RXFE, PD_LNA_RXFE" << endl;
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  out << endl << "echo \"Rx FE programming complete\"" << endl << endl;

};

/**
    Sets configuration settings under data received from chip
*/
bool RxFe_Module::SetGUIUnderReadback()
{
  int itmp;
  bool bRez = true;

  m_bAllowSend = false;

  //DECODE
  itmp = DECODE_r00_b11();
  rgrDecode.itemIndex = itmp;

  //EN
  itmp = EN_r00_b00();
  chbPwrRxFeMods.checked = itmp;

  //IN1SEL_MIX_RXFE
  itmp = IN1SEL_MIX_RXFE_r01_b77();
  cmbIN1SEL_MIX_RXFE.itemIndex = itmp;

  //DCOFF_I_RXFE[6:0]
  itmp = DCOFF_I_RXFE_r01_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x01] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbDCOFF_I_RXFE.itemIndex = itmp;

  //INLOAD_LNA_RXFE
  itmp = INLOAD_LNA_RXFE_r02_b77();
  chbINLOAD_LNA_RXFE.checked = itmp;

  //DCOFF_Q_RXFE[6:0]
  itmp = DCOFF_Q_RXFE_r02_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x02] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbDCOFF_Q_RXFE.itemIndex = itmp;

  //XLOAD_LNA_RXFE
  itmp = XLOAD_LNA_RXFE_r03_b77();
  chbXLOAD_LNA_RXFE.checked = itmp;

  //IP2TRIM_I_RXFE[6:0]
  itmp = IP2TRIM_I_RXFE_r03_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x03] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbIP2TRIM_I_RXFE.itemIndex = itmp;

  //IP2TRIM_Q_RXFE[6:0]
  itmp = IP2TRIM_Q_RXFE_r04_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x04] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbIP2TRIM_Q_RXFE.itemIndex = itmp;

  //G_LNA_RXFE[1:0]
  itmp = G_LNA_RXFE_r05_b76();
  if(itmp > 0) itmp--;
  else itmp = 0;
  cmbG_LNA_RXFE.itemIndex = itmp;

  //LNASEL_RXFE[1:0]
  itmp = LNASEL_RXFE_r05_b54();
  cmbLNASEL_RXFE.itemIndex = itmp;

  //CBE_LNA_RXFE[3:0]
  itmp = CBE_LNA_RXFE_r05_b30();
  cmbCBE_LNA_RXFE.itemIndex = itmp;

  //RFB_TIA_RXFE[6:0]
  itmp = RFB_TIA_RXFE_r06_b60();
  cmbRFB_TIA_RXFE.itemIndex = itmp;

  //CFB_TIA_RXFE[6:0]
  itmp = CFB_TIA_RXFE_r07_b60();
  cmbCFB_TIA_RXFE.itemIndex = itmp;

  //RDLEXT_LNA_RXFE[5:0]
  itmp = RDLEXT_LNA_RXFE_r08_b50();
  cmbRDLEXT_LNA_RXFE.itemIndex = itmp;

  //RDLINT_LNA_RXFE[5:0]
  itmp = RDLINT_LNA_RXFE_r09_b50();
  cmbRDLINT_LNA_RXFE.itemIndex = itmp;

  //ICT_MIX_RXFE[3:0]
  itmp = ICT_MIX_RXFE_r0A_b74();
  cmbICT_MIX_RXFE.itemIndex = itmp;

  //ICT_LNA_RXFE[3:0]
  itmp = ICT_LNA_RXFE_r0A_b30();
  cmbICT_LNA_RXFE.itemIndex = itmp;

  //ICT_TIA_RXFE[3:0]
  itmp = ICT_TIA_RXFE_r0B_b74();
  cmbICT_TIA_RXFE.itemIndex = itmp;

  //ICT_MXLOB_RXFE[3:0]
  itmp = ICT_MXLOB_RXFE_r0B_b30();
  cmbICT_MXLOB_RXFE.itemIndex = itmp;

  //LOBN_MIX_RXFE[3:0]
  itmp = LOBN_MIX_RXFE_r0C_b63();
  cmbLOBN_MIX_RXFE.itemIndex = itmp;

  //RINEN_MIX_RXFE
  itmp = RINEN_MIX_RXFE_r0C_b22();
  chbRINEN_MIX_RXFE.checked = itmp;

  //G_FINE_LNA3_RXFE[1:0]
  itmp = G_FINE_LNA3_RXFE_r0C_b10();
  cmbG_FINE_LNA3_RXFE.itemIndex = itmp;

  //PD_TIA_RXFE
  itmp = PD_TIA_RXFE_r0D_b33();
  chbPD_TIA_RXFE.checked = itmp;
  chbPD_TIA_RXFE.checked = !chbPD_TIA_RXFE.checked;

  //PD_MXLOB_RXFE
  itmp = PD_MXLOB_RXFE2_r0D_b22();
  chbPD_MXLOB_RXFE.checked = itmp;
  chbPD_MXLOB_RXFE.checked = !chbPD_MXLOB_RXFE.checked;

  //PD_MIX_RXFE
  itmp = PD_MIX_RXFE_r0D_b11();
  chbPD_MIX_RXFE.checked = itmp;
  chbPD_MIX_RXFE.checked = !chbPD_MIX_RXFE.checked;

  //PD_LNA_RXFE
  itmp = PD_LNA_RXFE_r0D_b00();
  chbPD_LNA_RXFE.checked = itmp;
  chbPD_LNA_RXFE.checked = !chbPD_LNA_RXFE.checked;


  m_bAllowSend = true;
  return bRez;
};

/**
    Writes register map to the file. According to the customer wish.
    @param out stream for output
*/
void RxFe_Module::MakeRegisterFile(ofstream &out)
{
  int itmp;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  //DECODE
  out.width(24); out << left; out << "REG 0x70 MASK 01 : 01  =";
  itmp = DECODE_r00_b11();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_DECODE"; out << endl;

  //EN
  out.width(24); out << left; out << "REG 0x70 MASK 00 : 00  =";
  itmp = EN_r00_b00();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_EN"; out << endl;

  //IN1SEL_MIX_RXFE
  out.width(24); out << left; out << "REG 0x71 MASK 07 : 07  =";
  itmp = IN1SEL_MIX_RXFE_r01_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_INSEL_MIX"; out << endl;

  //DCOFF_I_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x71 MASK 06 : 00  =";
  itmp = DCOFF_I_RXFE_r01_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_DCOFF_I"; out << endl;

  //INLOAD_LNA_RXFE
  out.width(24); out << left; out << "REG 0x72 MASK 07 : 07  =";
  itmp = INLOAD_LNA_RXFE_r02_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_INLOAD_LNA"; out << endl;

  //DCOFF_Q_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x72 MASK 06 : 00  =";
  itmp = DCOFF_Q_RXFE_r02_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_DCIFF_Q"; out << endl;

  //XLOAD_LNA_RXFE
  out.width(24); out << left; out << "REG 0x73 MASK 07 : 07  =";
  itmp = XLOAD_LNA_RXFE_r03_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_XLOAD_LNA"; out << endl;

  //IP2TRIM_I_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x73 MASK 06 : 00  =";
  itmp = IP2TRIM_I_RXFE_r03_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_IP2TRIM_I"; out << endl;

  //IP2TRIM_Q_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x74 MASK 06 : 00  =";
  itmp = IP2TRIM_Q_RXFE_r04_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_IP2TRIM_Q"; out << endl;

  //G_LNA_RXFE[1:0]
  out.width(24); out << left; out << "REG 0x75 MASK 07 : 06  =";
  itmp = G_LNA_RXFE_r05_b76();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_G_LNA"; out << endl;

  //LNASEL_RXFE[1:0]
  out.width(24); out << left; out << "REG 0x75 MASK 05 : 04  =";
  itmp = LNASEL_RXFE_r05_b54();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_LNASEL"; out << endl;

  //CBE_LNA_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x75 MASK 03 : 00  =";
  itmp = CBE_LNA_RXFE_r05_b30();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_CBE_LNA"; out << endl;

  //RFB_TIA_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x76 MASK 06 : 00  =";
  itmp = RFB_TIA_RXFE_r06_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_RFB_TIA"; out << endl;

  //CFB_TIA_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x77 MASK 06 : 00  =";
  itmp = CFB_TIA_RXFE_r07_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_CFB_TIA"; out << endl;

  //RDLEXT_LNA_RXFE[5:0]
  out.width(24); out << left; out << "REG 0x78 MASK 05 : 00  =";
  itmp = RDLEXT_LNA_RXFE_r08_b50();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_RDLEXT_LNA"; out << endl;

  //RDLINT_LNA_RXFE[5:0]
  out.width(24); out << left; out << "REG 0x79 MASK 05 : 00  =";
  itmp = RDLINT_LNA_RXFE_r09_b50();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_RDL_INT_LNA"; out << endl;

  //ICT_MIX_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7A MASK 07 : 04  =";
  itmp = ICT_MIX_RXFE_r0A_b74();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_MIX"; out << endl;

  //ICT_LNA_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7A MASK 03 : 00  =";
  itmp = ICT_LNA_RXFE_r0A_b30();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_LNA"; out << endl;

  //ICT_TIA_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7B MASK 07 : 04  =";
  itmp = ICT_TIA_RXFE_r0B_b74();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_TIA"; out << endl;

  //ICT_MXLOB_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7B MASK 03 : 00  =";
  itmp = ICT_MXLOB_RXFE_r0B_b30();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_MXLOB"; out << endl;

  //LOBN_MIX_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7C MASK 06 : 03  =";
  itmp = LOBN_MIX_RXFE_r0C_b63();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_LOBN_MIX"; out << endl;

  //RINEN_MIX_RXFE
  out.width(24); out << left; out << "REG 0x7C MASK 02 : 02  =";
  itmp = RINEN_MIX_RXFE_r0C_b22();
  out.width(6); out << right; out << itmp;
  out << "  RINEN_MIX_RXFE"; out << endl;

  //G_FINE_LNA3_RXFE[1:0]
  out.width(24); out << left; out << "REG 0x7C MASK 01 : 00  =";
  itmp = G_FINE_LNA3_RXFE_r0C_b10();
  out.width(6); out << right; out << itmp;
  out << "  G_FINE_LNA3_RXFE"; out << endl;

  //PD_TIA_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 03 : 03  =";
  itmp = PD_TIA_RXFE_r0D_b33();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_TIA"; out << endl;

  //PD_MXLOB_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 02 : 02  =";
  itmp = PD_MXLOB_RXFE2_r0D_b22();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_MXLOB"; out << endl;

  //PD_MIX_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 01 : 01  =";
  itmp = PD_MIX_RXFE_r0D_b11();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_MIX"; out << endl;

  //PD_LNA_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 00 : 00  =";
  itmp = PD_LNA_RXFE_r0D_b00();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_LNA"; out << endl;


}


/**
    @brief Saves configuration to ini file
    @param pini pointer to ini file parser
*/
void RxFe_Module::SaveConf(ini_t *pini)
{

	char Sect[80];
	//itoa((int)m_cMAddr, Sect, 10);
	sprintf(Sect, "%i", (int)m_cMAddr);
	pini->Create(Sect);

	pini->Set("rgrDecode", rgrDecode.itemIndex);
  pini->Set("chbPwrRxFeMods", chbPwrRxFeMods.checked);

  pini->Set("cmbIN1SEL_MIX_RXFE", cmbIN1SEL_MIX_RXFE.itemIndex);
  pini->Set("cmbDCOFF_I_RXFE", cmbDCOFF_I_RXFE.itemIndex);

  pini->Set("chkINLOAD_LNA_RXFE", chbINLOAD_LNA_RXFE.checked);
  pini->Set("cmbDCOFF_Q_RXFE", cmbDCOFF_Q_RXFE.itemIndex);

  pini->Set("chkXLOAD_LNA_RXFE", chbXLOAD_LNA_RXFE.checked);
  pini->Set("cmbIP2TRIM_I_RXFE", cmbIP2TRIM_I_RXFE.itemIndex);

  pini->Set("cmbIP2TRIM_Q_RXFE", cmbIP2TRIM_Q_RXFE.itemIndex);

  pini->Set("cmbG_LNA_RXFE", cmbG_LNA_RXFE.itemIndex);
  pini->Set("cmbLNASEL_RXFE", cmbLNASEL_RXFE.itemIndex);
  pini->Set("cmbCBE_LNA_RXFE", cmbCBE_LNA_RXFE.itemIndex);

  pini->Set("cmbRFB_TIA_RXFE", cmbRFB_TIA_RXFE.itemIndex);
  pini->Set("cmbCFB_TIA_RXFE", cmbCFB_TIA_RXFE.itemIndex);
  pini->Set("cmbRDLEXT_LNA_RXFE", cmbRDLEXT_LNA_RXFE.itemIndex);
  pini->Set("cmbRDLINT_LNA_RXFE", cmbRDLINT_LNA_RXFE.itemIndex);

  pini->Set("cmbICT_MIX_RXFE", cmbICT_MIX_RXFE.itemIndex);
  pini->Set("cmbICT_LNA_RXFE", cmbICT_LNA_RXFE.itemIndex);

  pini->Set("cmbICT_TIA_RXFE", cmbICT_TIA_RXFE.itemIndex);
  pini->Set("cmbICT_MXLOB_RXFE", cmbICT_MXLOB_RXFE.itemIndex);

  pini->Set("cmbLOBN_MIX_RXFE", cmbLOBN_MIX_RXFE.itemIndex);
  pini->Set("chkRINEN_MIX_RXFE", chbRINEN_MIX_RXFE.checked);
  pini->Set("cmbG_FINE_LNA3_RXFE", cmbG_FINE_LNA3_RXFE.itemIndex);

  pini->Set("chkPD_TIA_RXFE", chbPD_TIA_RXFE.checked);
  pini->Set("chkPD_MXLOB_RXFE", chbPD_MXLOB_RXFE.checked);
  pini->Set("chkPD_MIX_RXFE", chbPD_MIX_RXFE.checked);
  pini->Set("chkPD_LNA_RXFE", chbPD_LNA_RXFE.checked);

};

/**
    @brief Reads configuration from ini file
    @param pini pointer to ini file parser
*/
void RxFe_Module::ReadConf(ini_t *pini)
{

	char Sect[80];
//	itoa((int)m_cMAddr, Sect, 10);
sprintf(Sect, "%i", (int)m_cMAddr);
	pini->Select(Sect);

  m_bAllowSend = false;

	rgrDecode.itemIndex = pini->Get("rgrDecode", 0);
  chbPwrRxFeMods.checked = pini->Get("chbPwrRxFeMods", 1);

  cmbIN1SEL_MIX_RXFE.itemIndex = pini->Get("cmbIN1SEL_MIX_RXFE", 1);
  cmbDCOFF_I_RXFE.itemIndex = pini->Get("cmbDCOFF_I_RXFE", 63);

  chbINLOAD_LNA_RXFE.checked = pini->Get("chkINLOAD_LNA_RXFE", 1);
  cmbDCOFF_Q_RXFE.itemIndex = pini->Get("cmbDCOFF_Q_RXFE", 63);

  chbXLOAD_LNA_RXFE.checked = pini->Get("chkXLOAD_LNA_RXFE", 0);
  cmbIP2TRIM_I_RXFE.itemIndex = pini->Get("cmbIP2TRIM_I_RXFE", 63);

  cmbIP2TRIM_Q_RXFE.itemIndex = pini->Get("cmbIP2TRIM_Q_RXFE", 63);

  cmbG_LNA_RXFE.itemIndex = pini->Get("cmbG_LNA_RXFE", 2);
  cmbLNASEL_RXFE.itemIndex = pini->Get("cmbLNASEL_RXFE", 1);
  cmbCBE_LNA_RXFE.itemIndex = pini->Get("cmbCBE_LNA_RXFE", 0);

  cmbRFB_TIA_RXFE.itemIndex = pini->Get("cmbRFB_TIA_RXFE", 120);
  cmbCFB_TIA_RXFE.itemIndex = pini->Get("cmbCFB_TIA_RXFE", 0);
  cmbRDLEXT_LNA_RXFE.itemIndex = pini->Get("cmbRDLEXT_LNA_RXFE", 28);
  cmbRDLINT_LNA_RXFE.itemIndex = pini->Get("cmbRDLINT_LNA_RXFE", 28);

  cmbICT_MIX_RXFE.itemIndex = pini->Get("cmbICT_MIX_RXFE", 7);
  cmbICT_LNA_RXFE.itemIndex = pini->Get("cmbICT_LNA_RXFE", 7);

  cmbICT_TIA_RXFE.itemIndex = pini->Get("cmbICT_TIA_RXFE", 7);
  cmbICT_MXLOB_RXFE.itemIndex = pini->Get("cmbICT_MXLOB_RXFE", 7);

  cmbLOBN_MIX_RXFE.itemIndex = pini->Get("cmbLOBN_MIX_RXFE", 3);
  chbRINEN_MIX_RXFE.checked = pini->Get("chkRINEN_MIX_RXFE", 0);
  cmbG_FINE_LNA3_RXFE.itemIndex = pini->Get("cmbG_FINE_LNA3_RXFE", 0);

  chbPD_TIA_RXFE.checked = pini->Get("chkPD_TIA_RXFE", 1);
  chbPD_MXLOB_RXFE.checked = pini->Get("chkPD_MXLOB_RXFE", 1);
  chbPD_MIX_RXFE.checked = pini->Get("chkPD_MIX_RXFE", 1);
  chbPD_LNA_RXFE.checked = pini->Get("chkPD_LNA_RXFE", 1);

  pMainModule->Cust_setLNASEL(cmbLNASEL_RXFE.itemIndex);

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
// Functions for customer mode interface
//---------------------------------------------------------------------------
void RxFe_Module::CustSet_ActiveLNA(int ind)
{
  m_bAllowSend = false;
  cmbLNASEL_RXFE.itemIndex = ind;
  m_bAllowSend = true;
  pMainModule->getSerPort()->SetBrdLNA(ind);

  MakeData(0x80); pMainModule->CMAutoDownload(m_cMAddr);
};

void RxFe_Module::LNAPowerOn(bool on)
{
	if(on)
	{
		m_bAllowSend = false;
		rgrDecode.itemIndex = 0;
		chbPD_LNA_RXFE.checked = true;
		m_bAllowSend = true;

		MakeData(0x1D); pMainModule->CMAutoDownload(m_cMAddr);
	}
	else
	{
		m_bAllowSend = false;
		rgrDecode.itemIndex = 1;
		chbPD_LNA_RXFE.checked = false;
		m_bAllowSend = true;

		MakeData(0x1D); pMainModule->CMAutoDownload(m_cMAddr);
	}
}

void RxFe_Module::PowerOn(bool on)
{
	if(on)
	{
		m_bAllowSend = false;
		rgrDecode.itemIndex = 0;
		chbPwrRxFeMods.checked = true;
		m_bAllowSend = true;

		MakeData(0x01); pMainModule->CMAutoDownload(m_cMAddr);
	}
	else
	{
		m_bAllowSend = false;
		rgrDecode.itemIndex = 0;
		chbPwrRxFeMods.checked = false;
		m_bAllowSend = true;

		MakeData(0x01); pMainModule->CMAutoDownload(m_cMAddr);
    }
}

void RxFe_Module::CustSet_DCOffsetCancellationI(int ind)
{
  m_bAllowSend = false;
  cmbDCOFF_I_RXFE.itemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x03); pMainModule->CMAutoDownload(m_cMAddr);
};

void RxFe_Module::CustSet_DCOffsetCancellationQ(int ind)
{
  m_bAllowSend = false;
  cmbDCOFF_Q_RXFE.itemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x05); pMainModule->CMAutoDownload(m_cMAddr);
};

int RxFe_Module::CustGet_DCOffsetCancellationI()
{
  return cmbDCOFF_I_RXFE.itemIndex;
};

int RxFe_Module::CustGet_DCOffsetCancellationQ()
{
  return cmbDCOFF_Q_RXFE.itemIndex;
};

void RxFe_Module::CustSet_cmbRDLINT_LNA_RXFE(int Ind)
{
	setRDLINT_LNA_RXFE(Ind);
};

//---------------------------------------------------------------------------
// Functions for register testing
//---------------------------------------------------------------------------
void RxFe_Module::RT_SetTestMask(char Mask)
{
  MakeWriteAll();

	for(int i=0; i<m_psD.iToW; i++)
	{
    m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
  };

  pMainModule->CMAutoDownload(m_cMAddr);
};
