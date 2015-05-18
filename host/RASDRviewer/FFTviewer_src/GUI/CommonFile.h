
// -----------------------------------------------------------------------------
// FILE: 		    common.h
// DESCRIPTION:	Header for common.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
#include <stdio.h>
#include "assert.h"
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
#define ADFAddr     0x10

#define DCClbrCnt	0x05
#define CM_READ (WM_APP + 1)
#define CM_AUTODOWNLOAD (WM_APP + 10)
#define CM_RSTACT (WM_APP + 11)
#define CM_RSTINACT (WM_APP + 12)
#define CM_ADDC2LPF (WM_APP + 13)
#define CM_UPDATELNA (WM_APP + 14)
#define CM_SOFT_TX_PD (WM_APP + 15)
#define CM_SPICLKONMASK (WM_APP + 16)
#define CM_SPICLKRESTORE (WM_APP + 17)
#define CM_LOG (WM_APP + 20)
#define CM_UPDATEINTERFACE (WM_APP + 21)

//#define HIDE_FREQ
//#define CUSTOMER_MODE

//This definition controls caption of Main form
//and "Altera Edition" visibility in About form.
//#define ALTERA_EDITION

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

//int QuadraticInterpol(int iRefVCnt, double *dFVco, double *dCVco, double dRealFvco);
string Int2Hex(int integer, int symCount);
string Val2Units(double value, char *units);
double Units2Val(char *str, char *units);

struct SelectionContainer
{
	//bool enabled;
	int itemIndex; //currently selected item
	vector<string> sItems; //item names
	SelectionContainer()
	{
		//enabled = true;
		itemIndex = -1;
	}
	void clear()
	{
		sItems.clear();
	};
	void add(string& str)
	{
		sItems.push_back(str);
	};
	void add(char* ch)
	{
		string stmp = ch;
		sItems.push_back(stmp);
	}
	void add(int integer)
	{
		char ctmp[32];
		memset (ctmp,'\0',32);
		sprintf(ctmp, "%i", integer);
		sItems.push_back(ctmp);
	};
	int indexOf(string str)
	{
		for(unsigned int i=0; i<sItems.size(); i++)
		{
			if(sItems[i] == str)
				return i;
		}
		return -1;
	}
	int size()
	{
		return sItems.size();
	}
};

struct LabelString
{
	string caption;
	LabelString()
	{
		caption = "";
	}
	void set (const int& integer)
	{
		char ctmp[32];
		memset (ctmp,'\0',32);
		sprintf(ctmp,"%i", integer);
		caption = ctmp;
	};
	void set (const string& str)
	{
		caption = str;
	};
	void set (const double& dbl)
	{
		char ctmp[32];
		memset (ctmp,'\0',32);
		sprintf(ctmp,"%f", dbl);
		caption = ctmp;
	};
	double ToDouble()
	{
		return atof(caption.c_str());
	};
	int ToInt()
	{
		return atoi(caption.c_str());
	}
};

struct BoolCheckBox
{
	//bool enabled;
	bool checked;
	//bool visible;
	BoolCheckBox()
	{
		//enabled = false;
		checked = false;
		//visible = true;
	};
};

/// converting wx String to c string
const char* toCString(wxString str);

#endif
