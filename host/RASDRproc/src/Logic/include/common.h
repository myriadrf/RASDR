// -----------------------------------------------------------------------------
// FILE:        "common.h"
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
// FILE: 		common.h
// DESCRIPTION:	Header for common.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef COMMON_H
#define COMMON_H

#ifdef WIN32


    #include "windows.h"
#endif
#include <vector>
#include <string>
#include <stdio.h>
#include "assert.h"
#include "iniParser.h"
using namespace std;

#define RegistryString "Software\\ctr_6002d\\Settings"

//--- Lengths should be = Last Used Address + 1;
#define TopLen    0x0C
#define TxPllLen  0x10
#define RxPllLen  0x10
#define TxLpfLen  0x10
#define RxLpfLen  0x10
#define TxRFLen   0x0F
#define RxVGA2Len 0x0F
#define RxFELen   0x0E
#define ADFLen    0x0C

#define TopAddr		0x00
#define TxPllAddr 	0x01
#define RxPllAddr 	0x02
#define TxLpfAddr 	0x03
#define TxRFAddr	0x04
#define RxLpfAddr 	0x05
#define RxVGA2Addr	0x06
#define RxFEAddr	0x07
#define ADFAddr 	0x10

#define DCClbrCnt	0x05

typedef INI <string, string, string> ini_t;

struct sPrData
{
	int iLen;		//Number of registers in the hardware SPI
	char *cCmdW;	//Write command bytes
	char *cDataW;	//Write data bytes
	char *cCmdR;	//Read command bytes
	char *cDataR;	//Read data bytes

	int iToR;		//How much bytes we need to read from Hardware
	int iToW;		//How much bytes we need to write to Hardware
	int *iRInd;		//Indexes of cDataR array, required to raed
	int *iWInd;		//Indexes of cDataW array, required to write

	//Registers testing
	char *cTestMap;
};

struct sVcoVsCap
{
	int iRef;		//Number of reference points
	double *dFreq;
	double *iCap;
};

int QuadraticInterpol(int iRefVCnt, double *dFVco, double *dCVco, double dRealFvco);

struct SelectionContainer
{
	int itemIndex; //currently selected item
	vector<string> sItems; //item names
	SelectionContainer();
	void clear();
	void add(string& str);
	void add(char* ch);
	void add(int integer);
	int indexOf(string str);
	int size();
};

struct LabelString
{
	string caption;
	LabelString();
	void set (const int& integer);
	void set (const string& str);
	void set (const double& dbl);
	double ToDouble();
	int ToInt();
};

struct BoolCheckBox
{
	bool checked;
	BoolCheckBox();
};

#endif
