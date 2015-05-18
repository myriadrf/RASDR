// -----------------------------------------------------------------------------
// FILE: 		Data_FreqVsCap.h
// DESCRIPTION:	Header for data_FreqVsCap.cpp
// DATE:
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
#ifndef Data_FreqVsCapH
#define Data_FreqVsCapH
// ----------------------------------------------------------------------------
#include "common.h"
#include <vector>
#include <string>
using namespace std;
// ----------------------------------------------------------------------------
class Data_FreqVsCap
{
public:
	Data_FreqVsCap();
	~Data_FreqVsCap();

	sVcoVsCap sVco1;
	sVcoVsCap sVco2;
	sVcoVsCap sVco3;
	sVcoVsCap sVco4;

	void Initialize(string Name);

	void Save(string fname);
	void LoadValuesFromFile(string FName);

	sVcoVsCap* getVco1();
	sVcoVsCap* getVco2();
	sVcoVsCap* getVco3();
	sVcoVsCap* getVco4();

	void setVco1(sVcoVsCap *pSource);
	void setVco2(sVcoVsCap *pSource);
	void setVco3(sVcoVsCap *pSource);
	void setVco4(sVcoVsCap *pSource);

private:
	void DestroyValues(sVcoVsCap &Vco);
	void SavePathToReg(string Path);
	string ReadPathFromReg();

	void setVco(sVcoVsCap *source, sVcoVsCap *destination);

	bool FileExists(string filename);

	string m_sName;
	string m_sLastUsedVCOFile;
};
#endif
