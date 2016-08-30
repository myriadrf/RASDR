// -----------------------------------------------------------------------------
// FILE: 		ComPortConnection.cpp
// DESCRIPTION:	implements data transferring through COM port
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "ComPortConnection.h"
#ifdef WIN32
#define milSleep Sleep
#else
#define milSleep usleep
#endif // WIN32
typedef INI <string, string, string> ini_t;

ComPortConnection::ComPortConnection()
{
	connected = false;
	comPortList.clear();
	m_deviceNames.clear();
	portType = 0;
#ifdef WIN32
	hComm = INVALID_HANDLE_VALUE;
#endif
	comBaudrate = 115200;
	currentDeviceIndex = -1;
	Initialize();
}

ComPortConnection::~ComPortConnection()
{
	Close();
}

/**
    Tests if chip connection status has changed, if changed tries to reconnect
*/
void ComPortConnection::DevicesChanged()
{
	bool deviceConnected = TestConnectivity();
	if( deviceConnected != connected)
	{
		comPortList.clear();
		m_deviceNames.clear();
		Open();
	}
}

/**
    Opens connection to first found chip
*/
int ComPortConnection::Open()
{
	Close();
	currentDeviceIndex = -1;
	bool opened = false;

	comPortList.clear();
	if(comPortList.size() == 0)
		FindAllComPorts();

	m_deviceNames.clear();
	if(m_deviceNames.size() == 0)
		FindAllDevices();

	for(int i=0; i<m_deviceNames.size(); i++)
	{
		opened = Open(i);
		if( opened )
		{
			currentDeviceIndex = i;
			break;
		}
	}
	return opened;
}

/**
    Opens connection to selected chip
    @param index chip index in device list
*/
int ComPortConnection::Open(unsigned int index)
{
	Close();
	if(index >= 0 || index < m_deviceNames.size() )
	{
		comPortName = m_deviceNames[index];
		connected = Open(comPortName.c_str(), comBaudrate);
		if( connected )
		{
			currentDeviceIndex = index;
			return connected;
		}
	}
	return false;
}

/**
    Closes connection to chip
*/
void ComPortConnection::Close()
{
#ifdef WIN32
	connected = false;
	if (hComm != INVALID_HANDLE_VALUE)
	{
		SetCommTimeouts(hComm, &m_ctmoOld);
		CloseHandle(hComm);
	}
	hComm = INVALID_HANDLE_VALUE;
#endif
}

/**
    Returns whether chip is connected
    @return chip is connected
*/
bool ComPortConnection::IsOpen()
{
    #ifdef WIN32
	if (hComm != INVALID_HANDLE_VALUE && TestConnectivity() )
		return true;
	else
		return false;
    #endif
    return false;
}

/**
    Sends data through COM port
    @param buffer pointer to data buffer
    @param length size of data buffer
    @return 1 if success, 0 if failed
*/
int ComPortConnection::SendData(const unsigned char *buffer, int length)
{
#ifdef WIN32
	unsigned long bytesWriten = 0;
	bool writeSuccess = false;

	milSleep(20);
	PurgeComm(hComm, PURGE_TXCLEAR|PURGE_RXCLEAR);
	if (!WriteFile(hComm, buffer, length , &bytesWriten, &m_osWOverlap))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			if (WaitForSingleObjectEx(m_osWOverlap.hEvent, (int)100, true) == WAIT_TIMEOUT)
				writeSuccess = false;
			else
				writeSuccess = true;
		}
		else
			writeSuccess = false;
	}
	else
		writeSuccess = true;

	return writeSuccess;
#else
    return false;
#endif
}

/**
    Reads data from COM port
    @param buffer pointer to data buffer for receiving
    @param bytesRead number of bytes to read
*/
int ComPortConnection::ReadData(unsigned char *buffer, int bytesRead)
{
    memset(buffer, 0, bytesRead);
	unsigned long bytesReaded = 0;
	bool readSuccess = false;
	char cRawData[COM_BUFFER_LENGTH];
	unsigned long bytesToRead = bytesRead;

	memset(cRawData, '\0', sizeof(cRawData[0])*COM_BUFFER_LENGTH);
	readSuccess = false;
#ifdef WIN32
	milSleep(20);
	if ( !ReadFile(hComm, cRawData, bytesToRead, &bytesReaded, &m_osROverlap) )
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			if (WaitForSingleObject(m_osROverlap.hEvent, (int)100) == WAIT_TIMEOUT)
			{
				readSuccess = false;
			}
			else
			{
				readSuccess = true;
				memcpy(buffer, cRawData, bytesRead);
			};
		}
		else
		{
			readSuccess = false;
		}
	}
	else
	{
		readSuccess = true;
		memcpy(buffer, cRawData, bytesRead);
	};
#endif
	return readSuccess;
}

/**
    Returns currently open device index
*/
int ComPortConnection::CurrentDevice()
{
	return currentDeviceIndex;
}

/**
    Loads connection settings from file
    @param configFilename input filename
*/
int ComPortConnection::LoadSettings(string configFilename)
{
	ini_t *ini;
	string Name;
	Name = "COM Port";

	ini = new ini_t(configFilename.c_str());
	ini->Select(Name);

	string defaultPort = "COM1";
	comPortName = ini->Get("Port", defaultPort);
	comBaudrate = ini->Get("BaudRate", 0);
	delete ini;

	Open(comPortName.c_str(), comBaudrate);
	return 0;
}

/**
    Saves connection settings to file
    @param configFilename output filename
*/
int ComPortConnection::SaveSettings(string configFilename)
{
	ini_t *ini;
	string Name;
	Name = "COM Port";

	ini = new ini_t(configFilename);
	ini->Create(Name);
	ini->Set("Port", comPortName);
	ini->Set("BaudRate", comBaudrate);
	ini->Save();
	delete ini;
	return 1;
}


int ComPortConnection::SetCustomParameter(string paramName, char *value)
{
	if(paramName == "baudrate")
	{
		int newBaudrate;
		memcpy(&newBaudrate, value, sizeof(newBaudrate));
		comBaudrate = newBaudrate;
	}
	return 0;
}

int ComPortConnection::GetCustomParameter(string paramName, char *value)
{
	if(paramName == "baudrate")
	{
		memcpy(value, &comBaudrate, sizeof(comBaudrate));
	}
	return 0;
}

/**
    Opens connection to first found chip
*/
void ComPortConnection::Initialize()
{
	Open();
}

/**
    Searches for available COM ports and adds them to list
*/
void ComPortConnection::FindAllComPorts()
{
	comPortList.clear();

#ifdef WIN32
	HKEY hSERIALCOMM;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, ("HARDWARE\\DEVICEMAP\\SERIALCOMM"),	0, KEY_QUERY_VALUE, &hSERIALCOMM) == ERROR_SUCCESS)
	{
		// Get the max value name and max value lengths
		DWORD dwMaxValueNameLen;
		DWORD dwMaxValueLen;
		DWORD dwQueryInfo = RegQueryInfoKey(hSERIALCOMM, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL);
		if (dwQueryInfo == ERROR_SUCCESS)
		{
			DWORD dwMaxValueNameSizeInChars = dwMaxValueNameLen + 1;
			// Include space for the NULL terminator
			DWORD dwMaxValueNameSizeInBytes = dwMaxValueNameSizeInChars*sizeof(char);
			DWORD dwMaxValueDataSizeInChars = dwMaxValueLen / sizeof(char) + 1;
			// Include space for the NULL terminator
			DWORD dwMaxValueDataSizeInBytes = dwMaxValueDataSizeInChars*sizeof(char);

			// Allocate some space for the value name and value data
			char *szValueName = new char[dwMaxValueNameSizeInChars];
			char *byValue = new char[dwMaxValueDataSizeInBytes];
			if (szValueName && byValue)
			{
				// Enumerate all the values underneath HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
				DWORD dwIndex = 0;
				DWORD dwType;
				DWORD dwValueNameSize = dwMaxValueNameSizeInChars;
				DWORD dwDataSize = dwMaxValueDataSizeInBytes;
				memset(szValueName, 0, dwMaxValueNameSizeInBytes);
				memset(byValue, 0, dwMaxValueDataSizeInBytes);
				LONG nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, (LPBYTE)byValue, &dwDataSize);
				while (nEnum == ERROR_SUCCESS)
				{
					// If the value is of the correct type, then add it to the array
					if (dwType == REG_SZ)
					{
						char* szPort = reinterpret_cast<char*>(byValue);
						comPortList.push_back(szPort);
					}
					// Prepare for the next time around
					dwValueNameSize = dwMaxValueNameSizeInChars;
					dwDataSize = dwMaxValueDataSizeInBytes;
					memset(szValueName, 0, dwMaxValueNameSizeInBytes);
					memset(byValue, 0, dwMaxValueDataSizeInBytes);
					++dwIndex;
					nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName,	&dwValueNameSize, NULL, &dwType, (LPBYTE)byValue, &dwDataSize);
				}
			}
		}

		// Close the registry key now that we are finished with it
		RegCloseKey(hSERIALCOMM);

		if (dwQueryInfo != ERROR_SUCCESS)
			SetLastError(dwQueryInfo);
	}
#endif
}

/**
    Opens COM port
    @param comName COM port name
    @param baudrate COM port baudrate
*/
int ComPortConnection::Open(const char *comName, int baudrate)
{
	Close();
	if (strlen(comName) == 0)
		return 0;

	int errorCode = 0;

	// Close port if open
	Close();

#ifdef WIN32
	// Initialize Overlap structures
	m_osROverlap.Internal = 0;
	m_osROverlap.InternalHigh = 0;
	m_osROverlap.Offset = 0;
	m_osROverlap.OffsetHigh = 0;
	m_osROverlap.hEvent = CreateEvent(NULL, false, false, NULL);    // auto-reset, non-signalled

	m_osWOverlap.Internal = 0;
	m_osWOverlap.InternalHigh = 0;
	m_osWOverlap.Offset = 0;
	m_osWOverlap.OffsetHigh = 0;
	m_osWOverlap.hEvent = CreateEvent(NULL, false, false, NULL);    // auto-reset, non-signalled

	// Initialize DSB structure
	memset(&m_dcbCommPort, 0, sizeof(m_dcbCommPort));

	m_dcbCommPort.BaudRate = comBaudrate;
	m_dcbCommPort.fBinary = 1;
	m_dcbCommPort.fParity = 0;
	m_dcbCommPort.fOutxCtsFlow = 0;
	m_dcbCommPort.fOutxDsrFlow = 0;
	m_dcbCommPort.fDtrControl = 0;
	m_dcbCommPort.fDsrSensitivity = 0;
	m_dcbCommPort.fTXContinueOnXoff = 0;
	m_dcbCommPort.fOutX = 0;
	m_dcbCommPort.fInX = 0;
	m_dcbCommPort.fErrorChar = 0;
	m_dcbCommPort.fNull = 0;
	m_dcbCommPort.fRtsControl = 0;
	m_dcbCommPort.fAbortOnError = 0;
	m_dcbCommPort.fDummy2 = 0;
	// m_dcbCommPort.wReserved = 0;
	m_dcbCommPort.XonLim = 512;
	m_dcbCommPort.XoffLim = 512;
	m_dcbCommPort.ByteSize = 8;
	m_dcbCommPort.Parity = 0;
	m_dcbCommPort.StopBits = 0;
	//m_dcbCommPort.StopBits = 1;
	m_dcbCommPort.XonChar = 17;
	m_dcbCommPort.XoffChar = 19;
	m_dcbCommPort.ErrorChar = 0;
	m_dcbCommPort.EofChar = 26;
	m_dcbCommPort.EvtChar = 0;
	m_dcbCommPort.wReserved1 = 0;
	m_dcbCommPort.DCBlength = sizeof(DCB);

	// Initialize Timeout's
	m_ctmoNew.ReadIntervalTimeout = 20;
	m_ctmoNew.ReadTotalTimeoutMultiplier = 0;
	m_ctmoNew.ReadTotalTimeoutConstant = 0; // 1;
	m_ctmoNew.WriteTotalTimeoutMultiplier = 0;
	m_ctmoNew.WriteTotalTimeoutConstant = 0;

	// Open COM port
	string stmp;
	stmp = "\\\\.\\";
	stmp.append(comName);
	hComm = CreateFile(stmp.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);

	if (hComm != INVALID_HANDLE_VALUE)
	{
		// Set Events
		if (!SetCommMask(hComm, 0))
			errorCode = -1;

		// Set Timeouts
		GetCommTimeouts(hComm, &m_ctmoOld);
		if (!SetCommTimeouts(hComm, &m_ctmoNew))
			errorCode = -2;

		// Set DCB
		if (!SetCommState(hComm, &m_dcbCommPort))
			errorCode = -4;
	}
	else
	{
		errorCode = -8;
	};

	// Check the results
	if (errorCode != 0)
	{
		unsigned long err = GetLastError();
		CloseHandle(hComm);
		hComm = INVALID_HANDLE_VALUE;
		return errorCode;
	}
	else
	{
		PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
		return 1;
	}
#endif
    return 0;
}

/**
    Checks if chip is connected to currently open port
    @return chip is connected
*/
bool ComPortConnection::TestConnectivity()
{
#ifdef WIN32
	if (hComm != INVALID_HANDLE_VALUE)
	{
		unsigned char command = 'T';
		unsigned char *answer = new unsigned char[40];
		memset(answer, 0, 40);
		if( SendData(&command, 1) )
			if(ReadData(answer, 10) )
				if( answer[2] == 'O' || answer[3] == 'K')
					return true;
				else
				{
					CloseHandle(hComm);
					hComm = INVALID_HANDLE_VALUE;
					return false;
				}
	}
	else
	{
		return Open();
	}

#endif
	return false;
}

/**
    Finds all chips connected to com ports
*/
void ComPortConnection::FindAllDevices()
{
	m_deviceNames.clear();
	string comName;
	for(int i=0; i<comPortList.size(); i++)
	{
		comName = comPortList[i];
		if( Open(comName.c_str(), comBaudrate) > 0)
		{
			if( TestConnectivity() )
				m_deviceNames.push_back(comName);
		}
	}
}
