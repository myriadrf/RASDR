// -----------------------------------------------------------------------------
// FILE:        "clUARFCN.h"
// DESCRIPTION: "Header File"
// DATE:        "05/09/2015 06:44 AM "
// AUTHOR(s):   Lime Microsystems, Paul L. Oxley
// Copyright:   Society of Amateur Radio Astronomers (2014-2015)
//
// Based on original work from Zydrunas Tamosevicius (Lime Microsystems, Ltd.)
// and distributed under the Apache License 2.0 at:
// https://github.com/myriadrf/myriadrf-utils
//
// The RASDRviewer version has been specifically modified for Radio Astronomy
// by Paul L. Oxley for the Society of Amateur Radio Astronomers.  These
// modifications are provided to you under the Gnu Public License version 2.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// REVISIONS:   as appropriate
// -----------------------------------------------------------------------------
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
