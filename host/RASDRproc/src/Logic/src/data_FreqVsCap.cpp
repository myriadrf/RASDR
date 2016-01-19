// -----------------------------------------------------------------------------
// FILE: 		Data_FreqVsCap.cpp
// DESCRIPTION:
// DATE:
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

// ---------------------------------------------------------------------
#include "data_FreqVsCap.h"
// ---------------------------------------------------------------------
Data_FreqVsCap::Data_FreqVsCap()
{

	sVco1.iRef = 0;
	sVco1.dFreq = NULL;
	sVco1.iCap = NULL;
	sVco2.iRef = 0;
	sVco2.dFreq = NULL;
	sVco2.iCap = NULL;
	sVco3.iRef = 0;
	sVco3.dFreq = NULL;
	sVco3.iCap = NULL;
	sVco4.iRef = 0;
	sVco4.dFreq = NULL;
	sVco4.iCap = NULL;

	DestroyValues(sVco1);
	sVco1.iRef = 3;
	sVco1.dFreq = new double[sVco1.iRef];
	sVco1.iCap = new double[sVco1.iRef];
	sVco1.dFreq[0] = 3.76;
	sVco1.dFreq[1] = 4.20;
	sVco1.dFreq[2] = 4.84;
	sVco1.iCap[0] = 0;
	sVco1.iCap[1] = 31;
	sVco1.iCap[2] = 63;

	DestroyValues(sVco2);
	sVco2.iRef = 3;
	sVco2.dFreq = new double[sVco2.iRef];
	sVco2.iCap = new double[sVco2.iRef];
	sVco2.dFreq[0] = 4.68;
	sVco2.dFreq[1] = 5.32;
	sVco2.dFreq[2] = 6.04;
	sVco2.iCap[0] = 0;
	sVco2.iCap[1] = 31;
	sVco2.iCap[2] = 63;

	DestroyValues(sVco3);
	sVco3.iRef = 3;
	sVco3.dFreq = new double[sVco3.iRef];
	sVco3.iCap = new double[sVco3.iRef];
	sVco3.dFreq[0] = 5.72;
	sVco3.dFreq[1] = 6.44;
	sVco3.dFreq[2] = 7.36;
	sVco3.iCap[0] = 0;
	sVco3.iCap[1] = 31;
	sVco3.iCap[2] = 63;

	DestroyValues(sVco4);
	sVco4.iRef = 3;
	sVco4.dFreq = new double[sVco4.iRef];
	sVco4.iCap = new double[sVco4.iRef];
	sVco4.dFreq[0] = 6.92;
	sVco4.dFreq[1] = 7.36;
	sVco4.dFreq[2] = 8.398;
	sVco4.iCap[0] = 0;
	sVco4.iCap[1] = 31;
	sVco4.iCap[2] = 63;

	m_sLastUsedVCOFile = "";
}

sVcoVsCap* Data_FreqVsCap::getVco1()
{
	return &sVco1;
}

sVcoVsCap* Data_FreqVsCap::getVco2()
{
	return &sVco2;
}

sVcoVsCap* Data_FreqVsCap::getVco3()
{
	return &sVco3;
}

sVcoVsCap* Data_FreqVsCap::getVco4()
{
	return &sVco4;
}

void Data_FreqVsCap::setVco1(sVcoVsCap *pSource)
{
	DestroyValues(sVco1);
	sVco1.iRef = pSource->iRef;
	sVco1.dFreq = new double[sVco1.iRef];
	sVco1.iCap = new double[sVco1.iRef];
	int temp = 0;
	for (int i = 0; i < sVco1.iRef; i++)
	{
		sVco1.dFreq[i] = pSource->dFreq[i];
		sVco1.iCap[i] = pSource->iCap[i];
	}
}

void Data_FreqVsCap::setVco2(sVcoVsCap *pSource)
{
	DestroyValues(sVco2);
	sVco2.iRef = pSource->iRef;
	sVco2.dFreq = new double[sVco2.iRef];
	sVco2.iCap = new double[sVco2.iRef];
	for (int i = 0; i < sVco2.iRef; i++)
	{
		sVco2.dFreq[i] = pSource->dFreq[i];
		sVco2.iCap[i] = pSource->iCap[i];
	}
}

void Data_FreqVsCap::setVco3(sVcoVsCap *pSource)
{
	DestroyValues(sVco3);
	sVco3.iRef = pSource->iRef;
	sVco3.dFreq = new double[sVco3.iRef];
	sVco3.iCap = new double[sVco3.iRef];
	for (int i = 0; i < sVco3.iRef; i++)
	{
		sVco3.dFreq[i] = pSource->dFreq[i];
		sVco3.iCap[i] = pSource->iCap[i];
	}
}

void Data_FreqVsCap::setVco4(sVcoVsCap *pSource)
{
	DestroyValues(sVco4);
	sVco4.iRef = pSource->iRef;
	sVco4.dFreq = new double[sVco4.iRef];
	sVco4.iCap = new double[sVco4.iRef];
	for (int i = 0; i < sVco4.iRef; i++)
	{
		sVco4.dFreq[i] = pSource->dFreq[i];
		sVco4.iCap[i] = pSource->iCap[i];
	}
}

Data_FreqVsCap::~Data_FreqVsCap()
{
	DestroyValues(sVco1);
	DestroyValues(sVco2);
	DestroyValues(sVco3);
	DestroyValues(sVco4);
}

// ---------------------------------------------------------------------------
void Data_FreqVsCap::Save(string fname)
{
	int iCnt;
	double dTmp;

	fstream pfItems;
	pfItems.open(fname.c_str(), ios::out | ios::binary);
	if (!pfItems.is_open())
	{
		return;
	}

	// VCO1 Values
	iCnt = sVco1.iRef;
	pfItems.write((const char*)&iCnt, sizeof(iCnt));
	for (int i = 1; i <= iCnt; i++)
	{
		dTmp = sVco1.dFreq[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
		dTmp = sVco1.iCap[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
	};

	// VCO2 Values
	iCnt = sVco2.iRef;
	pfItems.write((const char*)&iCnt, sizeof(iCnt));
	for (int i = 1; i <= iCnt; i++)
	{
		dTmp = sVco2.dFreq[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
		dTmp = sVco2.iCap[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
	};

	// VCO3 Values
	iCnt = sVco3.iRef;
	pfItems.write((const char*)&iCnt, sizeof(iCnt));
	for (int i = 1; i <= iCnt; i++)
	{
		dTmp = sVco3.dFreq[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
		dTmp = sVco3.iCap[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
	};

	// VCO4 Values
	iCnt = sVco4.iRef;
	pfItems.write((const char*)&iCnt, sizeof(iCnt));
	for (int i = 1; i <= iCnt; i++)
	{
		dTmp = sVco4.dFreq[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
		dTmp = sVco4.iCap[i];
		pfItems.write((const char*)&dTmp, sizeof(dTmp));
	};
	pfItems.close();
}

// ---------------------------------------------------------------------------
void Data_FreqVsCap::DestroyValues(sVcoVsCap &Vco)
{
	if (Vco.iRef)
	{
		Vco.iRef = 0;
		if (Vco.dFreq != NULL)
			delete[]Vco.dFreq;
		Vco.dFreq = NULL;
		if (Vco.iCap != NULL)
			delete[]Vco.iCap;
		Vco.iCap = NULL;
	};
};

// ---------------------------------------------------------------------------
void Data_FreqVsCap::Initialize(string Name)
{
	string FName;
	string Str;
	m_sName = Name;

	// Load VCO calibration values from last used file
	// FName = ReadPathFromReg();

	if (!FileExists(FName))
	{
		if (m_sName == "TxVCOFile")
		{
			// FName = ChangeFileExt(ApplicationExeName,".tco");
			FName = "6002Dr2_Test.tco";
		}
		else
		{
			// FName = ChangeFileExt(ApplicationExeName,".rco");
			FName = "6002Dr2_Test.rco";
		};
	};

	if (FileExists(FName))
	{
		LoadValuesFromFile(FName);
	}
	else
	{
		Str = "Can't find VCO calibration values file for" + Name;
		Str = Str + "\nDefault values are used.";
	};
};

// ---------------------------------------------------------------------------
void Data_FreqVsCap::SavePathToReg(string Path)
{
	/*
	 TRegistry* reg = new TRegistry;
	 //reg->OpenKey("Software\\ctr_6002d\\Settings", true);
	 reg->OpenKey(RegistryString, true);
	 reg->WriteString(m_sName, Path);
	 //reg->WriteString("LastDirectory", "C:\\");
	 //reg->WriteInteger("Data", 1);
	 delete reg;
	 */
};

// ---------------------------------------------------------------------------
string Data_FreqVsCap::ReadPathFromReg()
{
	/*
	 string FileName;
	 TRegistry* reg = new TRegistry;
	 //reg->OpenKey("Software\\ctr_6002d\\Settings", true);
	 reg->OpenKey(RegistryString, true);
	 FileName = reg->ReadString(m_sName);
	 delete reg;
	 return FileName;
	 */
	return string("Error");
};

// ---------------------------------------------------------------------------
void Data_FreqVsCap::LoadValuesFromFile(string FName)
{
	int iCnt;
	double dTmp;
	sVcoVsCap VcoVsCap;

	fstream pfItems;
	pfItems.open(FName.c_str(), ios::in | ios::binary);

	if (!pfItems.is_open())
	{
		return;
	}

	// --===== Save path to registry. BEGIN =====--
	// SavePathToReg(FName);
	m_sLastUsedVCOFile = FName;
	// --=====  Save path to registry. END  =====--

	// VCO1 Values
	pfItems.read((char *)&iCnt, sizeof(iCnt));
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.dFreq[i - 1] = dTmp;
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	setVco(&VcoVsCap, &sVco1);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	// VCO2 Values
	pfItems.read((char *)&iCnt, sizeof(iCnt));
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.dFreq[i - 1] = dTmp;
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	setVco(&VcoVsCap, &sVco2);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	// VCO3 Values
	pfItems.read((char *)&iCnt, sizeof(iCnt));
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.dFreq[i - 1] = dTmp;
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	setVco(&VcoVsCap, &sVco3);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	// VCO4 Values
	pfItems.read((char *)&iCnt, sizeof(iCnt));
	VcoVsCap.iRef = iCnt;
	VcoVsCap.dFreq = new double[iCnt];
	VcoVsCap.iCap = new double[iCnt];
	for (int i = 1; i <= iCnt; i++)
	{
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.dFreq[i - 1] = dTmp;
		pfItems.read((char*)&dTmp, sizeof(dTmp));
		VcoVsCap.iCap[i - 1] = dTmp;
	};
	setVco(&VcoVsCap, &sVco4);
	delete[]VcoVsCap.dFreq;
	delete[]VcoVsCap.iCap;

	pfItems.close();
};

void Data_FreqVsCap::setVco(sVcoVsCap *source, sVcoVsCap *destination)
{
	destination->iRef = source->iRef;
	for (int i = 0; i < source->iRef; i++)
	{
		destination->dFreq[i] = source->dFreq[i];
		destination->iCap[i] = source->iCap[i];
	}
}

bool Data_FreqVsCap::FileExists(string filename)
{
	bool exists = false;
	fstream fin;
	fin.open(filename.c_str(), ios::in);
	if (fin.is_open())
	{
		exists = true;
	}
	fin.close();
	return exists;
}
