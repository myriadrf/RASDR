#include "ADF_Module.h"

#include <cmath>

#include "Main_Module.h"
#include "ConnectionManager.h"
extern string Int2Hex(int, int);

/** @brief ADF_Module
  *
  * @todo: document this function
  */
ADF_Module::ADF_Module()
{

}

/** @brief ~ADF_Module
  *
  * @todo: document this function
  */
ADF_Module::~ADF_Module()
{

}

/** @brief SetDefaults
  *
  * @todo: document this function
  */
void ADF_Module::SetDefaults()
{
    //Reference Counter Latch
    cmbLDP.itemIndex = 0;
    cmbABW.itemIndex = 0;
    txtRCnt = 125;

    //N Counter Latch
    cmbCPG.itemIndex = 0;
    txtNCnt = 384;

    //Function Latch
    rgrPD2_f.itemIndex = 0;
    cmbCS2_f.itemIndex = 7;
    cmbCS1_f.itemIndex = 7;
    cmbTC_f.itemIndex = 0;
    cmbFL_f.itemIndex = 0;
    rgrCPS_f.itemIndex = 0;
    rgrPDP_f.itemIndex = 1;
    cmbMOC_f.itemIndex = 1;
    rgrPD1_f.itemIndex = 0;
    rgrCR_f.itemIndex = 0;

    //Initialization Latch
    rgrPD2_i.itemIndex = 0;
    cmbCS2_i.itemIndex = 7;
    cmbCS1_i.itemIndex = 7;
    cmbTC_i.itemIndex = 0;
    cmbFL_i.itemIndex = 0;
    rgrCPS_i.itemIndex = 0;
    rgrPDP_i.itemIndex = 1;
    cmbMOC_i.itemIndex = 1;
    rgrPD1_i.itemIndex = 0;
    rgrCR_i.itemIndex = 0;

    //SetGuiDecode();
    CalculateRN();
}

/** @brief Initialize
  *
  * @todo: document this function
  */
void ADF_Module::Initialize(Main_Module *pMain, char MAddr)
{
    pMainModule = pMain;
    m_cMAddr = MAddr;

    m_psD.iLen = ADFLen;
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
    m_psD.cTestMap[0x0] = 0x00;
    m_psD.cTestMap[0x1] = 0x00;
    m_psD.cTestMap[0x2] = 0x00;
    m_psD.cTestMap[0x3] = 0x00;
    m_psD.cTestMap[0x4] = 0x00;
    m_psD.cTestMap[0x5] = 0x00;
    m_psD.cTestMap[0x6] = 0x00;
    m_psD.cTestMap[0x7] = 0x00;
    m_psD.cTestMap[0x8] = 0x00;
    m_psD.cTestMap[0x9] = 0x00;
    m_psD.cTestMap[0xA] = 0x00;
    m_psD.cTestMap[0xB] = 0x00;
    //m_psD.cTestMap[0xC] = 0xFF;
    //m_psD.cTestMap[0xD] = 0xFF;
    //m_psD.cTestMap[0xE] = 0xFF;
    //m_psD.cTestMap[0xF] = 0xFF;

}

/** @brief MakeRFIFFile
  *
  * @todo: document this function
  */
void ADF_Module::MakeRFIFFile(ofstream& out, char* FRIF_SPI_A)
{

}

/** @brief MakeData
  *
  * @todo: document this function
  */
void ADF_Module::MakeData(int rAddr)
{
    char btmp;
    unsigned int itmp;

    //======= register addr 0x00 =======
    m_psD.cDataW[0x00] = 0x00;
    //R Value LSB
    itmp = txtRCnt;
    btmp = (char)itmp;
    btmp = btmp << 2;
    m_psD.cDataW[0x00] |= btmp;
    //Addr
    btmp = 0x00;
    btmp = btmp << 0;
    m_psD.cDataW[0x00] |= btmp;

    //======= register addr 0x01 =======
    m_psD.cDataW[0x01] = 0x00;
    //R Value MSB
    btmp = (char)(itmp >> 6);
    btmp = btmp << 0;
    m_psD.cDataW[0x01] |= btmp;

    //======= register addr 0x02 =======
    m_psD.cDataW[0x02] = 0x00;
    //Anti-Backlash
    btmp = (char)cmbABW.itemIndex;
    if(btmp > 0) btmp++;
    btmp = btmp << 0;
    m_psD.cDataW[0x02] |= btmp;
    //Lock Detact Precision
    btmp = (char)cmbLDP.itemIndex;
    btmp = btmp << 4;
    m_psD.cDataW[0x02] |= btmp;



    //======= register addr 0x03 =======
    m_psD.cDataW[0x03] = 0x00;
    //Addr
    btmp = 0x01;
    btmp = btmp << 0;
    m_psD.cDataW[0x03] |= btmp;

    //======= register addr 0x04 =======
    m_psD.cDataW[0x04] = 0x00;
    //N Value LSB
    itmp = txtNCnt;
    btmp = (char)itmp;
    btmp = btmp << 0;
    m_psD.cDataW[0x04] |= btmp;

    //======= register addr 0x05 =======
    m_psD.cDataW[0x05] = 0x00;
    //N Value MSB
    itmp = txtNCnt;
    btmp = (char)(itmp >> 8);
    btmp = btmp << 0;
    m_psD.cDataW[0x05] |= btmp;
    //CP Gain
    btmp = (char)cmbCPG.itemIndex;
    btmp = btmp << 5;
    m_psD.cDataW[0x05] |= btmp;




    //======= register addr 0x06 =======
    m_psD.cDataW[0x06] = 0x00;
    //Addr
    btmp = 0x02;
    btmp = btmp << 0;
    m_psD.cDataW[0x06] |= btmp;
    //Counter Reset
    btmp = (char)rgrCR_f.itemIndex;
    btmp = btmp << 2;
    m_psD.cDataW[0x06] |= btmp;
    //PD 1
    btmp = (char)rgrPD1_f.itemIndex;
    btmp = btmp << 3;
    m_psD.cDataW[0x06] |= btmp;
    //Muxout Control
    btmp = (char)cmbMOC_f.itemIndex;
    btmp = btmp << 4;
    m_psD.cDataW[0x06] |= btmp;
    //PD Polarity
    btmp = (char)rgrPDP_f.itemIndex;
    btmp = btmp << 7;
    m_psD.cDataW[0x06] |= btmp;

    //======= register addr 0x07 =======
    m_psD.cDataW[0x07] = 0x00;
    //CP State
    btmp = (char)rgrCPS_f.itemIndex;
    btmp = btmp << 0;
    m_psD.cDataW[0x07] |= btmp;
    //Fastlock
    btmp = (char)cmbFL_f.itemIndex;
    if(btmp > 0) btmp++;
    btmp = btmp << 1;
    m_psD.cDataW[0x07] |= btmp;
    //Timer Counter
    btmp = (char)cmbTC_f.itemIndex;
    btmp = btmp << 3;
    m_psD.cDataW[0x07] |= btmp;
    //Current Setting 1 MSB
    btmp = (char)cmbCS1_f.itemIndex;
    btmp = btmp << 7;
    m_psD.cDataW[0x07] |= btmp;

    //======= register addr 0x08 =======
    m_psD.cDataW[0x08] = 0x00;
    //Current Setting 1 LSB
    btmp = (char)cmbCS1_f.itemIndex;
    btmp = btmp >> 1;
    m_psD.cDataW[0x08] |= btmp;
    //Current Setting 2
    btmp = (char)cmbCS2_f.itemIndex;
    btmp = btmp << 2;
    m_psD.cDataW[0x08] |= btmp;
    //PD 2
    btmp = (char)rgrPD2_f.itemIndex;
    btmp = btmp << 5;
    m_psD.cDataW[0x08] |= btmp;



    //======= register addr 0x09 =======
    m_psD.cDataW[0x09] = 0x00;
    //Addr
    btmp = 0x03;
    btmp = btmp << 0;
    m_psD.cDataW[0x09] |= btmp;
    //Counter Reset
    btmp = (char)rgrCR_i.itemIndex;
    btmp = btmp << 2;
    m_psD.cDataW[0x09] |= btmp;
    //PD 1
    btmp = (char)rgrPD1_i.itemIndex;
    btmp = btmp << 3;
    m_psD.cDataW[0x09] |= btmp;
    //Muxout Control
    btmp = (char)cmbMOC_i.itemIndex;
    btmp = btmp << 4;
    m_psD.cDataW[0x09] |= btmp;
    //PD Polarity
    btmp = (char)rgrPDP_i.itemIndex;
    btmp = btmp << 7;
    m_psD.cDataW[0x09] |= btmp;

    //======= register addr 0x0A =======
    m_psD.cDataW[0x0A] = 0x00;
    //CP State
    btmp = (char)rgrCPS_i.itemIndex;
    btmp = btmp << 0;
    m_psD.cDataW[0x0A] |= btmp;
    //Fastlock
    btmp = (char)cmbFL_i.itemIndex;
    if(btmp > 0) btmp++;
    btmp = btmp << 1;
    m_psD.cDataW[0x0A] |= btmp;
    //Timer Counter
    btmp = (char)cmbTC_i.itemIndex;
    btmp = btmp << 3;
    m_psD.cDataW[0x0A] |= btmp;
    //Current Setting 1 MSB
    btmp = (char)cmbCS1_i.itemIndex;
    btmp = btmp << 7;
    m_psD.cDataW[0x0A] |= btmp;

    //======= register addr 0x0B =======
    m_psD.cDataW[0x0B] = 0x00;
    //Current Setting 1 LSB
    btmp = (char)cmbCS1_i.itemIndex;
    btmp = btmp >> 1;
    m_psD.cDataW[0x0B] |= btmp;
    //Current Setting 2
    btmp = (char)cmbCS2_i.itemIndex;
    btmp = btmp << 2;
    m_psD.cDataW[0x0B] |= btmp;
    //PD 2
    btmp = (char)rgrPD2_i.itemIndex;
    btmp = btmp << 5;
    m_psD.cDataW[0x0B] |= btmp;


    memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
    switch(rAddr)
    {
    case 0x00:
        m_psD.iToW = 3;
        m_psD.iWInd[0] = 0x02;
        m_psD.iWInd[1] = 0x01;
        m_psD.iWInd[2] = 0x00;
        break;

    case 0x01:
        m_psD.iToW = 3;
        m_psD.iWInd[0] = 0x05;
        m_psD.iWInd[1] = 0x04;
        m_psD.iWInd[2] = 0x03;
        break;

    case 0x02:
        m_psD.iToW = 3;
        m_psD.iWInd[0] = 0x08;
        m_psD.iWInd[1] = 0x07;
        m_psD.iWInd[2] = 0x06;
        break;

    case 0x03:
        m_psD.iToW = 3;
        m_psD.iWInd[0] = 0x0B;
        m_psD.iWInd[1] = 0x0A;
        m_psD.iWInd[2] = 0x09;
        break;

    default:
        m_psD.iToW = 0;
    };
    cout << "DATA TO ADF -  address : " << rAddr << endl;
    for(int i=0; i<m_psD.iToW; ++i)
        cout << Int2Hex(m_psD.cDataW[m_psD.iWInd[i]], 2) << ' ';
    cout << endl;

}

/** @brief UpdateADFFvco
  *
  * @todo: document this function
  */
void ADF_Module::UpdateADFFvco()
{

}

/** @brief CalculateRN
  *
  * @todo: document this function
  */
void ADF_Module::CalculateRN()
{
    float x = txtFref*1000000;
    float y = txtFvco*1000000;
    float Fcomp;
    while((x!=0) && (y!=0))
    {
        if(x >= y)
        {
            x = fmod(x, y);
        }
        else
        {
            y = fmod(y, x);
        };
    };

    Fcomp = (x + y)/1000000.0;
    int R = ((float)txtFref/Fcomp)+0.5;
    int N = ((float)txtFvco/Fcomp)+0.5;

    txtRCnt = (int)R;
    txtNCnt = (int)N;
    //  lblFcomp->Caption = Fcomp;
    double dFvco;
    if(txtRCnt != 0) dFvco = txtNCnt * (txtFref)/txtRCnt;
    //lblFvco->Caption = dFvco;
}

void ADF_Module::SendConfig()
{
    CalculateRN();
    MakeData(0x03);
    pMainModule->getSerPort()->SPI_Wr_ADF(&m_psD);
    MakeData(0x02);
    pMainModule->getSerPort()->SPI_Wr_ADF(&m_psD);
    MakeData(0x00);
    pMainModule->getSerPort()->SPI_Wr_ADF(&m_psD);
    MakeData(0x01);
    pMainModule->getSerPort()->SPI_Wr_ADF(&m_psD);
}
