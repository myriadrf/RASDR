// -----------------------------------------------------------------------------
// FILE:        "CommonFile.cpp"
// DESCRIPTION: "Source Code File"
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
