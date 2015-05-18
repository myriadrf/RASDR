// -----------------------------------------------------------------------------
// FILE: 		clUARFCN.h
// DESCRIPTION:	Header for clUARFCN.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ---------------------------------------------------------------------------
#ifndef clUARFCNH
#define clUARFCNH
// ---------------------------------------------------------------------------
#include "common.h"
#include "iniParser.h"
typedef INI<string, string, string>ini_t;

#define BandN 14

struct sUARFCNDef
{
	double dFul_low[BandN];
	double dFul_high[BandN];
	double dFul_offset[BandN];
};

class CUARFCN
{
public:
	CUARFCN();
	~CUARFCN();

	void SaveConf(ini_t *pini);
	void ReadConf(ini_t *pini);

	void Initialize();
	void SetBands(bool ULRX);
	void SetChannels(bool ULRX);
	double SetFrequency(bool ULRX);

	double selectBand(bool ULRX, int bandIndex);
	double selectChannel(bool ULRX, int ChanIndex);
	int ChName2ChInd(string ChName);

	double m_dULRXFreq; // frequency in MHz
	double m_dDLTXFreq; // frequency in MHz
	sUARFCNDef m_sRxUARFCNDef; // Uplink
	sUARFCNDef m_sTxUARFCNDef; // Downlink
	bool m_bBandEnable[BandN];
	string m_sBands[BandN];

	SelectionContainer cmbULRXBands;
	SelectionContainer cmbULRXChan;

	SelectionContainer cmbDLTXBands;
	SelectionContainer cmbDLTXChan;
};

#endif
