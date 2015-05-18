// -----------------------------------------------------------------------------
// FILE:        "ComPortConnection.h"
// DESCRIPTION: "Header File"
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
