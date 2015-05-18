// -----------------------------------------------------------------------------
// FILE: 		    common.cpp
// DESCRIPTION:	Common structures and definitions file.
// DATE:        2007.10.01
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "common.h"
#include <wx/wx.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Quadratic interpolation for CAP selection
//---------------------------------------------------------------------------
int QuadraticInterpol(int iRefVCnt, double *dFVco, double *dCVco, double dRealFvco)
{

  double dGV = 0;
  double dNum;
  double dDenom;

  for(int i=0; i<iRefVCnt; i++) //Loop through each reference point
  {
    dNum = 1;
    dDenom = 1;
    for(int j=0; j<iRefVCnt; j++)
    {
      if(i != j)
      {
        dNum    *= dRealFvco - dFVco[j];
        dDenom  *= dFVco[i]  - dFVco[j];
      };
    };
    dGV += (double)dCVco[i] * dNum / dDenom;

  };

  return (int)(dGV + 0.5);
};

string Int2Hex(int integer, int symCount)
{
	char temp[80];
	string format = "%#.";
	sprintf(temp, "%i", symCount);
	format.append( temp );
	format.append("x");
	sprintf(temp, format.c_str(), integer);
	return string(temp);
}

const char* toCString(wxString str)
{
	return str.ToStdString().c_str();
}
