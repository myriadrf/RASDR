// -----------------------------------------------------------------------------
// FILE: 		IConnection.h
// DESCRIPTION:	Stub for undefined connection type
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

class IConnection
{
public:
	IConnection(){ portType = -1; };
	~IConnection(){};
	virtual void DevicesChanged() {};
	virtual int Open()
	{
        return 0;
    };
	virtual int Open(unsigned int index)
	{
	    return 0;
    };
	virtual void Close(){};
	virtual bool IsOpen(){return false;};

	virtual int SendData(const unsigned char *buffer, int lenght)
	{
	    return 0;
    };
	virtual int ReadData(unsigned char *buffer, int bytesRead)
	{
		char ctmp[] = {'E', 'M', 'P', 'T', 'Y', '\0'};
		memcpy(buffer, ctmp, 6);

		return 0;
	};

	virtual int BeginDataReading(unsigned char *buffer, long length){ cout << "Beginning ICOnnection" << endl; return -1; };
	virtual int WaitForReading(int contextHandle, unsigned int timeout_ms){ return 0;};
	virtual int FinishDataReading(unsigned char *buffer, long &length, int contextHandle){ cout << "Finish IC+onnection" << endl; return 0;}
	virtual void AbortReading(){};

	virtual int BeginDataSending(const unsigned char *buffer, long length){ return -1; };
	virtual int WaitForSending(int contextHandle, unsigned int timeout_ms){ return 0;};
	virtual int FinishDataSending(const unsigned char *buffer, long &length, int contextHandle){ return 0;}
	virtual void AbortSending(){};

	virtual int GetConnectionType() {return portType;};
	virtual int CurrentDevice() {return -1;};
	virtual int DeviceCount() {return m_deviceNames.size();};
	virtual string DeviceName(int index) {return "Undefined connection";};

	virtual int LoadSettings(string configFilename){return 0;};
	virtual int SaveSettings(string configFilename){return 0;};
	virtual int SetCustomParameter(string paramName, void *value) {return 0;};
	virtual int GetCustomParameter(string paramName, void *value) {return 0;};

	virtual vector<string> GetDeviceList()
	{
	    return m_deviceNames;
	}

protected:
	int portType;
	vector<string> m_deviceNames;
};

#endif
