// -----------------------------------------------------------------------------
// FILE: 		RegisterTest.h
// DESCRIPTION:
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "RegisterTest.h"
#include <sstream>
#include "common.h"

RegisterTest::RegisterTest()
{
}

RegisterTest::~RegisterTest()
{
}

/**
    Compares written and read data
    @return true - matches, false differs
*/
bool RegisterTest::Compare(sPrData *pPrData)
{
	string Str;
	unsigned char itmp;
	bool bTestRez = true;
	int mask;

	for(int i=0; i<pPrData->iToW; i++)
	{
        if((pPrData->cDataW[pPrData->iWInd[i]] & pPrData->cTestMap[pPrData->iWInd[i]]) != (pPrData->cDataR[pPrData->iWInd[i]] & pPrData->cTestMap[pPrData->iWInd[i]]))
        {
          bTestRez = false;

          stringstream sTemp;
		  sTemp << "Reg Addr = ";
		  sTemp << pPrData->iWInd[i];
		  sTemp << " Failed (Write/Read Values): ";
		  itmp = pPrData->cDataW[pPrData->iWInd[i]] & 0x00FF;
		  sTemp << IntToHex(itmp, 2);
		  sTemp << " / ";
		  itmp = pPrData->cDataR[pPrData->iWInd[i]];
		  sTemp << IntToHex(itmp, 2);

          Str = sTemp.str();
		  AddLine(Str);
        }
  }

  if(pPrData->iToW == 0) AddLine("Length Wrong!");

  if(bTestRez)
  {
    AddLine("Module test with this pattern is OK.");
  }
  else
  {
    AddLine("Module test with this pattern FAILED!");
  }
  return bTestRez;
}

bool RegisterTest::Comparators(int Min, int Max)
{
	string Str;

  if((Min == 0x2) && (Max == 0x1))
  {
    AddLine("VTUNE registers are OK.");
	return true;
  }
  else
  {
    AddLine("Some problems with VTUNE registers:");
    Str = "VTUNE_H (should be/acctual): 1/";
    if((Min == 0x2) && (Min == 0x0))
    {
      Str += "0;";
    }
    else
    {
      Str += "1;";
    };
    AddLine(Str);

    Str = "VTUNE_H (should be/acctual): 0/";
    if((Min == 0x2) && (Min == 0x0))
    {
      Str += "0;";
    }
    else
    {
      Str += "1;";
    };
    AddLine(Str);

    Str = "VTUNE_L (should be/acctual): 1/";
    if((Min == 0x1) && (Min == 0x0))
    {
      Str += "0;";
    }
    else
    {
      Str += "1;";
    };
    AddLine(Str);

    Str = "VTUNE_L (should be/acctual): 0/";
    if((Min == 0x1) && (Min == 0x0))
    {
      Str += "0;";
    }
    else
    {
      Str += "1;";
    };
    AddLine(Str);
	return false;
  };
}

/**
    @brief Converts integer to hex
    @param integer integer to convert
    @param symCount minimal number of hex symbols
*/
string RegisterTest::IntToHex(int integer, int symCount)
{
	char temp[80];
	string format = "%.";
	char ctemp[10];
	sprintf(ctemp, "%i", symCount);
	format.append( ctemp );
	format.append("X");
	sprintf(temp, format.c_str(), integer);
	return string(temp);
}
