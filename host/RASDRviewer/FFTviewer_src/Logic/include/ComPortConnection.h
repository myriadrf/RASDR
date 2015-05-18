// -----------------------------------------------------------------------------
// FILE: 		ComPortConnection.h
// DESCRIPTION:	Header for ComPortConnection.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef COM_PORT_CONNECTION_H
#define COM_PORT_CONNECTION_H

#ifdef WIN32


	#include "windows.h"
#endif

#include "IConnection.h"
#include <string>
#include <vector>
using namespace std;

#include "iniParser.h"
#define COM_BUFFER_LENGTH 1024

class ComPortConnection : public IConnection
{
public:
	ComPortConnection();
	~ComPortConnection();

	void DevicesChanged();
	int Open();
	int Open(unsigned int index);
	void Close();
	bool IsOpen();

	int SendData(const unsigned char *buffer, int lenght);
	int ReadData(unsigned char *buffer, int bytesRead);

	int CurrentDevice();

	int LoadSettings(string configFilename);
	int SaveSettings(string configFilename);

	int SetCustomParameter(string paramName, char *value);
	int GetCustomParameter(string paramName, char *value);

private:
	void Initialize();
	void FindAllComPorts();
	void FindAllDevices();
	int Open(const char *comName, int baudrate);

	bool TestConnectivity();

	string comPortName;
	int comBaudrate;
	bool connected;

	int currentDeviceIndex;
	vector<string> comPortList;
	vector<string> m_deviceNames;

#ifdef WIN32
	HANDLE hComm;
	COMMTIMEOUTS m_ctmoNew;
	COMMTIMEOUTS m_ctmoOld;
	OVERLAPPED m_osROverlap;
	OVERLAPPED m_osWOverlap;
	DCB m_dcbCommPort;
#endif
};
#endif
