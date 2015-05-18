// -----------------------------------------------------------------------------
// FILE: 		RegisterTest.h
// DESCRIPTION:	Header for RegisterTest.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef REGISTER_TEST
#define REGISTER_TEST

#include <string>
#include "TextLog.h"

struct sPrData;

class RegisterTest : public TextLog
{
	public:
		RegisterTest();
		~RegisterTest();
		bool Compare(sPrData *pPrData);
		bool Comparators(int Min, int Max);
	private:
		std::string IntToHex(int integer, int symCount);
};	

#endif