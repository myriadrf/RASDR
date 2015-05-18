// -----------------------------------------------------------------------------
// FILE: 		ConnectionManager.cpp
// DESCRIPTION:	Manages data transfering through various connection types
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "ConnectionManager.h"

#include "IConnection.h"
#include "ComPortConnection.h"
#include "USBPortConnection.h"

#include "Main_Module.h"
#include "common.h"
#include "CallbackCodes.h"

//Comands
//I2C FPGA
//#define FPGA_ADDR 0xAA     // For I2C -> SPI in FPGA
#define SC18IS602_ADDR 0x28     // For I2C -> SPI in SC18IS602B
#define CMD_LMS_RESET 0x10
#define CMD_CFG_I2C_WR 0x14
#define CMD_CFG_I2C_RD 0x15

//LMS6002D
#define CMD_LMS_WR 0x16
#define CMD_LMS_RD 0x17

//I2C Si5356A
#define FSN_ADDR 0xE0
//#define CMD_FSN_I2C_WR 0x24
//#define CMD_FSN_I2C_RD 0x25

//Controls GPIOs in FX2LP
#define CMD_SET_LNA 0x30  //LNA selection by GPIO
#define CMD_SET_PA 0x31 //PA selection by GPIO2

#define CMD_USBFIFO_RESET 0x40
#define CMD_GET_INFO 0x50

#define USB_BUFFER_LENGTH 64
using namespace std;

/**
	@brief Setups available connection types.
	@param pMainModule Pointer to main module;
*/
ConnectionManager::ConnectionManager(Main_Module *pMainModule = NULL)
{
    pthread_mutex_init(&CriticalSection, NULL);
	chipConnected = false;
	pMain = pMainModule;
	port = new IConnection();
	connectionPorts.clear();
	connectionPorts.push_back(new ComPortConnection());
	connectionPorts.push_back(new USBPortConnection());
	Initialize();
}

/**
	@brief Deallocates memory used by connection ports.
*/
ConnectionManager::~ConnectionManager()
{
	for(int i=0; i<connectionPorts.size(); i++)
		delete connectionPorts[i];
    pthread_mutex_destroy(&CriticalSection);
}

/**
	@brief Actions when device change is detected
*/
void ConnectionManager::DevicesChanged()
{
	if(port->GetConnectionType() == -1)
	{
		Open();
		//set to false to indicate that there was no previously connected chip
		chipConnected = false;
	}
	else
    {
        port->DevicesChanged();
    }


	if(chipConnected == false && port->IsOpen() )
	{
		pMain->UpdateInterface(SHOW_LOG_MESSAGE, "Chip has been connected");
		pMain->UpdateInterface(CHIP_CONNECTED, NULL);
		pMain->getBoard2()->ConfigureSi5356A();
		chipConnected = true;
		pMain->UpdateVerRevMask();
	}
	else if(chipConnected == true && !port->IsOpen() )
	{
		pMain->UpdateInterface(SHOW_LOG_MESSAGE, "Chip has been disconnected");
		pMain->UpdateInterface(CHIP_DISCONNECTED, NULL);
		chipConnected = false;
		pMain->UpdateVerRevMask();
	}
}

/**
	@brief Initializes connection settings and discovers connected devices.
	@return 0 if success.
*/
int ConnectionManager::Initialize()
{
	Open();
	return 0;
}

/**
	@brief Automatically finds connected chip and opens connection to it.
	@return 1 - success, 0 - failure.
*/
int ConnectionManager::Open()
{
	Close();
	for(int i=0; i<connectionPorts.size(); i++)
	{
		if( connectionPorts[i]->Open() )
		{
			port = connectionPorts[i];
			chipConnected = true;
			return 1;
		}
	}
	return 0;
}

/**
	@brief Opens i-th port from the list.
	@param i Index of device.
	@return 1 - success, 0 -failure.
*/
int ConnectionManager::Open(unsigned int i)
{
	Close();
	if( i < port->DeviceCount() )
	{
		chipConnected = port->Open(i);
		return chipConnected;
	}
	return 0;
}

/**
	@brief Close opened port.
	@return 0 - success.
*/
int ConnectionManager::Close()
{
	chipConnected = false;
	port->Close();
	return 0;
}

/**
	@brief Checks if device is open.
	@return true - open, false - closed;
*/
bool ConnectionManager::IsOpen()
{
	return port->IsOpen();
}

/**
	@brief Changes connection to specified type.
	@param Type Connection port type
	@return setting succeeded
*/
bool ConnectionManager::SetConnectionType(enumPortType Type)
{
	if(Type < connectionPorts.size())
	{
		port = connectionPorts[Type];
		chipConnected = port->Open();
		return true;
	}
	return false;
}

/**
	@brief Activates and then deactivates Reset signal in the chip.
*/
void ConnectionManager::SPI_Rst()
{
    pthread_mutex_lock(&CriticalSection);
	unsigned char buf = 0x10;
	bool rez;
	unsigned char Buf[USB_BUFFER_LENGTH];
	memset(Buf, 0, USB_BUFFER_LENGTH);
	if (port->GetConnectionType() == COM_PORT)
	{
		rez = port->SendData(&buf, 1);
	}
	else if (port->GetConnectionType() == USB_PORT)
	{
		//Reset of LMS6002D is controlled via FPGA
  		Buf[0] = CMD_LMS_RESET;
		Buf[1] = SC18IS602_ADDR;
		Buf[2] = 2;
		Buf[4] = 0x00;  //LMS Reset is Active
		Buf[5] = 0x01;  //LMS Reset is Inactive

		rez = port->SendData(Buf, USB_BUFFER_LENGTH);
		rez = port->ReadData(Buf, USB_BUFFER_LENGTH);
	}
	pthread_mutex_unlock(&CriticalSection);
}

/**
	@brief Activates Reset signal in the chip.
*/
void ConnectionManager::SPI_RstAct()
{
    pthread_mutex_lock(&CriticalSection);
	unsigned char buf = 0x11;
	bool rez;
	unsigned char Buf[USB_BUFFER_LENGTH];
	memset(Buf, 0, USB_BUFFER_LENGTH);
	if (port->GetConnectionType() == COM_PORT)
	{
		rez = port->SendData(&buf, 1);
	}
	else if (port->GetConnectionType() == USB_PORT)
	{
		Buf[0] = CMD_LMS_RESET;
		Buf[1] = SC18IS602_ADDR;
		Buf[2] = 1;
		Buf[4] = 0x00;  //LMS Reset is Active

		rez = port->SendData(Buf, USB_BUFFER_LENGTH);
		rez = port->ReadData(Buf, USB_BUFFER_LENGTH);
	}
	pthread_mutex_unlock(&CriticalSection);
}

/**
	@brief Deactivates Reset signal in the chip.
*/
void ConnectionManager::SPI_RstInact()
{
    pthread_mutex_lock(&CriticalSection);
	unsigned char buf = 0x12;
	bool rez;
	unsigned char Buf[USB_BUFFER_LENGTH];
	memset(Buf, 0, USB_BUFFER_LENGTH);
	if (port->GetConnectionType() == COM_PORT)
	{
		rez = port->SendData(&buf, 1);
	}
	else if (port->GetConnectionType() == USB_PORT)
	{
		Buf[0] = CMD_LMS_RESET;
		Buf[1] = SC18IS602_ADDR;
		Buf[2] = 1;
		Buf[4] = 0x01;  //LMS Reset is Inactive

		rez = port->SendData(Buf, USB_BUFFER_LENGTH);
		rez = port->ReadData(Buf, USB_BUFFER_LENGTH);
	}
	pthread_mutex_unlock(&CriticalSection);
}

/**
	@brief Reads data from the chip using reading commands from given data structure
	and copies received data to the same structure.
	@return True - success, False - failure.
*/
bool ConnectionManager::SPI_Read(sPrData *pPD)
{
	unsigned char *buf = new unsigned char[CONNECTION_BUFFER_SIZE];
	unsigned char *inBuf = new unsigned char[CONNECTION_BUFFER_SIZE];
	int bytesRead = pPD->iToR;

	bool rez;
	int itmp = 0;
	memset(buf, 0, CONNECTION_BUFFER_SIZE);
	memset(inBuf, 0, CONNECTION_BUFFER_SIZE);

	// Construct write (uC->Chip) commands
	for (int j = 0; j < pPD->iToR; j++)
	{
		buf[itmp] = pPD->cCmdR[pPD->iRInd[j]];
		itmp++;
	};

	// Write commands
	rez = ReadData(buf, pPD->iToR, inBuf, bytesRead);

	// Read Data from Chip
	for (int j = 0; j < pPD->iToR && j < bytesRead; j++)
	{
		pPD->cDataR[pPD->iRInd[j]] = inBuf[j];
	};

	delete[]buf;
	delete[]inBuf;

	return rez;
}

/**
	@brief Reads one byte from the chip using Command.
	@param Command Address which to read.
	@return Received byte.
*/
char ConnectionManager::SPI_Read_OneByte(const unsigned char Command)
{
	unsigned char *buf = new unsigned char[CONNECTION_BUFFER_SIZE];
    int bytesRead = 1;

	bool rez;
	char cRez;
	memset(buf, 0x0, CONNECTION_BUFFER_SIZE);

	rez = ReadData(&Command, 1, buf, bytesRead);
	cRez = buf[0];
	delete[]buf;

	return cRez;
}

/**
	@brief Writes data to the chip using writing commands from given data structure.
	@return True - success, False - failure.
*/
bool ConnectionManager::SPI_Write(sPrData *pPD)
{
	int bytesToSend = 2 * pPD->iToW;
	unsigned char *buf = new unsigned char[bytesToSend];

	bool rez;
	int ind = 0;

	for (int j = 0; j < pPD->iToW; j++)
	{
		buf[ind] = pPD->cCmdW[pPD->iWInd[j]];
		ind++;
		buf[ind] = pPD->cDataW[pPD->iWInd[j]];
		ind++;
	};

	rez = SendData(buf, bytesToSend);
	delete[]buf;
	return rez;
}

/**
    @brief Sends data to ADF4002 chip
    @param pDD registers data
*/
void ConnectionManager::SPI_Wr_ADF(sPrData *pPD)
{
    pthread_mutex_lock(&CriticalSection);
    unsigned char *buf = new unsigned char[64];
    memset(buf, 0, 64);
    bool rez;
    int ind = 0;

    if(port->GetConnectionType() == 0)
    {
        buf[0] = 0xAD;
        for(int j=0; j<pPD->iToW; j++)
        {
            ind++;
            buf[ind] = pPD->cDataW[pPD->iWInd[j]];
        };
        rez = port->SendData(buf, pPD->iToW+1);
        rez = !rez;
    }
    if(port->GetConnectionType() == USB_PORT)
    {
        buf[0] = 0xAD;
        buf[1] = 0;
        buf[2] = 1;
        buf[3] = 0;
        ind = 4;
        for(int j=0; j<pPD->iToW; j++)
        {
            buf[ind] = pPD->cDataW[pPD->iWInd[j]];
            ++ind;
        };
        rez = port->SendData(buf, 64);
        rez = port->ReadData(buf, 64);
    }
    delete[] buf;
    pthread_mutex_unlock(&CriticalSection);
};

/**
	@brief Forms given data buffer according to used port type and writes buffer to the chip.
	@param buffer Pointer to data array.
	@param length size of data buffer.
*/
int ConnectionManager::SendData(const unsigned char *buffer, int &length)
{
    pthread_mutex_lock(&CriticalSection);
	int rez = 0;
	unsigned char outBuffer[CONNECTION_BUFFER_SIZE];
	memset(outBuffer, 0, CONNECTION_BUFFER_SIZE);
	int bytesToWrite = length;
	int bytesWritten = 0;
	if(port == NULL)
		return 0;
	if (port->GetConnectionType() == COM_PORT)
	{
		outBuffer[0] = 0x30;
		for (int i = 0; i < bytesToWrite; i++)
			outBuffer[i + 1] = buffer[i];
		bytesToWrite += 1;
		rez = port->SendData(outBuffer, bytesToWrite);
	}
	else if (port->GetConnectionType() == USB_PORT)
	{
		const int bytesPrefixed = 4;
		// if buffer is longer than 64 bytes, it is split into several buffers
		//int iterations = length / (USB_BUFFER_LENGTH-bytesPrefixed);

		int inBufferPos = 0;

		outBuffer[0] = CMD_LMS_WR;
		outBuffer[1] = SC18IS602_ADDR;
		outBuffer[2] = (length / 2); // number of address and data pairs
		outBuffer[3] = 0; //reserved

		for (int i = 0; i < outBuffer[2]*2; i++)
		{
			outBuffer[i + bytesPrefixed] = buffer[i];
		}
		rez = port->SendData(outBuffer, USB_BUFFER_LENGTH);
		if(!rez) // if sending failed
        {
            pthread_mutex_unlock(&CriticalSection);
            return 0;
        }
		// after writing, chip sends back empty buffer
		int bytesReadback = port->ReadData(outBuffer, USB_BUFFER_LENGTH);
	}
	pthread_mutex_unlock(&CriticalSection);
	return rez;
}

/**
	@brief Forms given reading commands according to used port type and writes them to chip, then receives incoming data
	@param readCommands Array of addresses to read.
	@param cmdCount Length of readCommands.
	@param readBuffer Array where to put received data.
	@param bytesToRead Number of to read.
	@return 1 - success, 0 - failure.
*/
int ConnectionManager::ReadData(const unsigned char *readCommands, int cmdCount, unsigned char *readBuffer, int &bytesToRead)
{
    pthread_mutex_lock(&CriticalSection);
	unsigned char outBuffer[CONNECTION_BUFFER_SIZE];
	memset(outBuffer, 0, CONNECTION_BUFFER_SIZE);
	unsigned char *recBuffer = new unsigned char[CONNECTION_BUFFER_SIZE];
	memset(recBuffer, 0, CONNECTION_BUFFER_SIZE);

	int rez = false;
	if(port == NULL)
		return 0;
	if (port->GetConnectionType() == COM_PORT) // if USB selected
	{
		// Construct write (uC->Chip) commands
		outBuffer[0] = 0x20;
		for(int i=0; i<cmdCount; i++)
			outBuffer[i+1] = readCommands[i];
		// Write commands
		rez = port->SendData(outBuffer, cmdCount+1);
		if(rez == 0)
        {
            pthread_mutex_unlock(&CriticalSection);
			return 0;
        }

		rez = port->ReadData(recBuffer, bytesToRead);
		if(rez == 0)
        {
            pthread_mutex_unlock(&CriticalSection);
			return 0;
        }
	}
	else if (port->GetConnectionType() == USB_PORT) // if USB selected
	{
		const int bytesPrefixed = 4;
		// splits buffer if it exceeds 64 bytes
		//int iterations = cmdCount / (USB_BUFFER_LENGTH-bytesPrefixed);

		//int inBufferPos = 0;
		//int recBufferPos = 0;

		outBuffer[0] = CMD_LMS_RD;
		outBuffer[1] = SC18IS602_ADDR;
		outBuffer[2] = cmdCount; // number of address and data pairs
		outBuffer[3] = 0; //reserved

		for (int i = 0; i < outBuffer[2]; i++)
		{
			outBuffer[i + bytesPrefixed] = readCommands[i];
		}
		rez = port->SendData(outBuffer, USB_BUFFER_LENGTH);
		if(!rez) // if sending failed
        {
            pthread_mutex_unlock(&CriticalSection);
			return 0;
        }

		rez = port->ReadData(outBuffer, USB_BUFFER_LENGTH);
		if(!rez) // if reading failed
        {
            pthread_mutex_unlock(&CriticalSection);
			return 0;
        }

		for(int j=0; j<USB_BUFFER_LENGTH; j++)
		{
			recBuffer[j] = outBuffer[j];
		}
	}

	for(int i=0; i<bytesToRead; i++)
	{
		readBuffer[i] = recBuffer[i];
	}

	delete[]recBuffer;
	pthread_mutex_unlock(&CriticalSection);
	return rez;
}

/**
	@brief Writes raw data buffer directly to chip.
	@param buffer Data array to send.
	@param length size of buffer.
	@return 1 - success, 0 - failure.
*/
int ConnectionManager::SendDataDirectly(const unsigned char *buffer, long &length)
{
    pthread_mutex_lock(&CriticalSection);
	int status = port->SendData(buffer, length);
	pthread_mutex_unlock(&CriticalSection);
	return status;
}

/**
	@brief Reads raw data coming from the chip.
	@param buffer Pointer to array where to put received data.
	@param bytesRead How many bytes to read.
	@return 1 - success, 0 - failure.
*/
int ConnectionManager::ReadDataDirectly(unsigned char *buffer, long &bytesRead)
{
    pthread_mutex_lock(&CriticalSection);
	int status = port->ReadData(buffer, bytesRead);
	pthread_mutex_unlock(&CriticalSection);
	return status;
}

/**
    @brief Start asynchronous data reading.
    @param buffer where to put received data
    @param length number of bytes to read.
    @return context handle
*/
int ConnectionManager::BeginDataReading(unsigned char *buffer, long length)
{
    return port->BeginDataReading(buffer, length);
}
/**
    @brief Blocks until data is received or set number of milliseconds have passed.
    @param contextHandle handle returned by BeginDataReading()
    @param timeout_ms number of milliseconds to wait
    @return 1-data received, 0-data not received
*/
int ConnectionManager::WaitForReading(int contextHandle, unsigned int timeout_ms)
{
    return port->WaitForReading(contextHandle, timeout_ms);
}
/**
    @brief Finished asynchronous data reading.
    @param buffer where to put received data
    @param length number of bytes to read, will be changed to actual number of bytes received
    @param contextHandle context handle returned by BeginDataReading()
    @return received data length
*/
int ConnectionManager::FinishDataReading(unsigned char *buffer, long &length, int contextHandle)
{
    return port->FinishDataReading(buffer, length, contextHandle);
}

/**
	@brief Aborts reading operations
*/
void ConnectionManager::AbortReading()
{
	port->AbortReading();
}

/**
    @brief Start asynchronous data sending.
    @param buffer where to put received data
    @param length number of bytes to read.
    @return context handle
*/
int ConnectionManager::BeginDataSending(const unsigned char *buffer, long length)
{
    return port->BeginDataSending(buffer, length);
}
/**
    @brief Blocks until data is received or set number of miliseconds have passed.
    @param contextHandle handle returned by BeginDataReading()
    @param timeout_ms number of miliseconds to wait
    @return 1-data received, 0-data not received
*/
int ConnectionManager::WaitForSending(int contextHandle, unsigned int timeout_ms)
{
    return port->WaitForSending(contextHandle, timeout_ms);
}
/**
    @brief Finished asynchronous data sending.
    @param buffer where to put received data
    @param length number of bytes to read, will be changed to actual number of bytes received
    @param contextHandle context handle returned by BeginDataReading()
    @return received data length
*/
int ConnectionManager::FinishDataSending(const unsigned char *buffer, long &length, int contextHandle)
{
    return port->FinishDataSending(buffer, length, contextHandle);
}

/**
	@brief Aborts sending operations
*/
void ConnectionManager::AbortSending()
{
	port->AbortSending();
}

/**
	@return connection type.
*/
int ConnectionManager::GetConnectionType()
{
	return port->GetConnectionType();
}

/**
	Returns Currently used port index in the port list.
	@return Port index.
*/
int ConnectionManager::CurrentDevice()
{
	return port->CurrentDevice();
}

/**
	@brief Returns vector of connected devices names.
	@return devices names list
*/
vector<string> ConnectionManager::GetDeviceList()
{
	return port->GetDeviceList();
}

/**
	Loads connection settings from configuration file.
*/
int ConnectionManager::LoadSettings(string configFilename)
{
	return 0;
}

/**
	Saves connection settings to configuration file
*/
int ConnectionManager::SaveSettings(string configFilename)
{
	return 0;
}

int ConnectionManager::SetCustomParameter(string paramName, void *value)
{
	port->SetCustomParameter(paramName, value);
	return 0;
}

int ConnectionManager::GetCustomParameter(string paramName, void *value)
{
	port->GetCustomParameter(paramName, value);
	return 0;
}

void ConnectionManager::SetBrdLNA(char Code)
{
    pthread_mutex_lock(&CriticalSection);
	unsigned char Buf[USB_BUFFER_LENGTH];
	bool rez;
	memset(Buf, 0, USB_BUFFER_LENGTH);

	if(port->GetConnectionType() == USB_PORT)   //if USB selected
	{
  		Buf[0] = CMD_SET_LNA;
		Buf[1] = 0x0;
		Buf[2] = 1;
		switch(Code)
		{
			case 1:
				Buf[4] = 0x03;
				break;
			case 2:
				Buf[4] = 0x01;
				break;
			case 3:
				Buf[4] = 0x00;
				break;
			default:
				Buf[4] = 0x03;
				break;
		}

		long length = USB_BUFFER_LENGTH;
		port->SendData(Buf, length);
		rez = port->ReadData(Buf, length);
	}
	pthread_mutex_unlock(&CriticalSection);
}

void ConnectionManager::SetBrdPA(char Code)
{
    pthread_mutex_lock(&CriticalSection);
	unsigned char Buf[USB_BUFFER_LENGTH];
	memset(Buf, 0, USB_BUFFER_LENGTH);

	if( port->GetConnectionType() == USB_PORT)   //if USB selected
	{
		Buf[0] = CMD_SET_PA;
		Buf[1] = 0x00;
		Buf[2] = 1;
		switch(Code)
		{
			case 1:
				Buf[4] = 0x00;
				break;
			case 2:
				Buf[4] = 0x01;
				break;
			default:
				Buf[4] = 0;
				break;
		}
		long length = USB_BUFFER_LENGTH;
		port->SendData(Buf, length);
	    port->ReadData(Buf, length);
	}
	pthread_mutex_unlock(&CriticalSection);
}
