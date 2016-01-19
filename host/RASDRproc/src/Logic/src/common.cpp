// -----------------------------------------------------------------------------
// FILE: 		common.cpp
// DESCRIPTION:	Common structures and definitions file.
// DATE:        2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "common.h"

//---------------------------------------------------------------------------
// Quadratic interpolation for CAP selection
//---------------------------------------------------------------------------
/*
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
*/

SelectionContainer::SelectionContainer()
{
	sItems.resize(10, "empty string");
	//enabled = true;
	itemIndex = -1;
}
void SelectionContainer::clear()
{
	sItems.clear();
};
void SelectionContainer::add(string& str)
{
	sItems.push_back(str);
};
void SelectionContainer::add(char* ch)
{
	string stmp = ch;
	sItems.push_back(stmp);
}
void SelectionContainer::add(int integer)
{
	char ctmp[32];
	memset (ctmp,'\0',32);
	sprintf(ctmp, "%i", integer);
	sItems.push_back(ctmp);
};
int SelectionContainer::indexOf(string str)
{
	for(unsigned int i=0; i<sItems.size(); i++)
	{
		if(sItems[i] == str)
			return i;
	}
	return -1;
}
int SelectionContainer::size()
{
	return sItems.size();
}

LabelString::LabelString()
{
	caption = "";
}
void LabelString::set (const int& integer)
{
	char ctmp[32];
	memset (ctmp,'\0',32);
	sprintf(ctmp,"%i", integer);
	caption = ctmp;
};
void LabelString::set (const string& str)
{
	caption = str;
};
void LabelString::set (const double& dbl)
{
	char ctmp[32];
	memset (ctmp,'\0',32);
	sprintf(ctmp,"%i", dbl);
	caption = ctmp;
};
double LabelString::ToDouble()
{
	return atof(caption.c_str());
};
int LabelString::ToInt()
{
	return atoi(caption.c_str());
}

BoolCheckBox::BoolCheckBox() : checked(false) {};
