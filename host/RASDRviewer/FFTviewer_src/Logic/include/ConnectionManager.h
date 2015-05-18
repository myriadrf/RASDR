// -----------------------------------------------------------------------------
// FILE:        "ConnectionManager.h"
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
// FILE: 		ConnectionManager.h
// DESCRIPTION:	Header for ConnectionManager.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <string>
#include <vector>

#ifdef WIN32


#include <windows.h>
#endif
#include <pthread.h>
using namespace std;

struct sPrData;
class IConnection;
class Main_Module;

/// Supported connection types.
enum enumPortType
{
	PORT_UNDEFINED = -1,
	COM_PORT = 0,
	USB_PORT = 1,
	//insert new types here
	PORT_TYPES_COUNT //used only for memory allocation
};

#define CONNECTION_BUFFER_SIZE 1024
#define MAX_DEVICE_NAME_LENGTH 256

/// Responsible for communications with the chip
class ConnectionManager
{
public:
	ConnectionManager(Main_Module *pMainModule);
	~ConnectionManager();
	int Initialize();
	void DevicesChanged();
	int Open();
	int Open(unsigned int i);
	int Close();
	bool IsOpen();
	bool SetConnectionType(enumPortType Type);

	void SPI_Rst();
	void SPI_RstAct();
	void SPI_RstInact();

    bool SPI_Read(sPrData *pPD);
	char SPI_Read_OneByte(const unsigned char Command);
	bool SPI_Write(sPrData *pPD);
	void SPI_Wr_ADF(sPrData *pPD);

	int SendData(const unsigned char *buffer, int &lenght);
	int ReadData(const unsigned char *readCommands, int cmdCount, unsigned char *readBuffer, int &bytesRead);
	int SendDataDirectly(const unsigned char *buffer, long &lenght);
	int ReadDataDirectly(unsigned char *buffer, long &bytesRead);

    int BeginDataReading(unsigned char *buffer, long length);
	int WaitForReading(int contextHandle, unsigned int timeout_ms);
	int FinishDataReading(unsigned char *buffer, long &length, int contextHandle);
	void AbortReading();

    int BeginDataSending(const unsigned char *buffer, long length);
	int WaitForSending(int contextHandle, unsigned int timeout_ms);
	int FinishDataSending(const unsigned char *buffer, long &length, int contextHandle);
	void AbortSending();

	int GetConnectionType();
	int CurrentDevice();
	vector<string> GetDeviceList();

	/// Loads connection settings from configuration file.
	int LoadSettings(std::string configFilename);
	/// Saves connection settings to configuration file.
	int SaveSettings(std::string configFilename);

	/// Sets custom parameter to connection port
	int SetCustomParameter(string paramName, void *value);
	/// Gets custom parameter from connection port
	int GetCustomParameter(string paramName, void *value);

	void SetBrdLNA(char code);
	void SetBrdPA(char code);

	void WriteToADF(const unsigned char *buffer, long length);

protected:
	/// Currently used port types.
	vector<IConnection*> connectionPorts;

	/// Port used for communication.
	IConnection *port;

	/// pointer to main module, needed just for logging messages.
	Main_Module *pMain;
	/// shows if chip is connected.
	bool chipConnected;

	pthread_mutex_t CriticalSection;
};

#endif
