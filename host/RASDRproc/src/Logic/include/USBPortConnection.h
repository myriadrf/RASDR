// -----------------------------------------------------------------------------
// FILE:        "USBPortConnection.h"
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
// FILE: 		USBPortConnection.h
// DESCRIPTION:	Header for USBPortConnection.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef USB_PORT_CONNECTION_H
#define USB_PORT_CONNECTION_H

#include "IConnection.h"
#include <string>
#include <vector>

using namespace std;

#define USB_BUFFER_LENGTH = 64;

#ifdef WIN32


#include "windows.h"
#include "CyAPI.h"
#else
#include <libusb-1.0/libusb.h>
#endif

#define USB_MAX_CONTEXTS 64 //maximum number of contexts for asynchronous transfers

class USBTransferContext
{
public:
	USBTransferContext() : used(false)
	{
		#ifdef WIN32
		inOvLap = new OVERLAPPED;
		inOvLap->hEvent = CreateEvent(NULL, true, false, NULL);    // manual-reset, non-signalled
		context = NULL;
		#else
		transfer = libusb_alloc_transfer(64);
		bytesXfered = 0;
		bytesExpected = 0;
		done = 0;
		#endif
	}
	~USBTransferContext()
	{
		#ifdef WIN32
		CloseHandle(inOvLap->hEvent);
		delete inOvLap;
		#else
		libusb_free_transfer(transfer);
		#endif
	}
	volatile long used;  // NB: needs to be long to be able to use InterlockedExchange()
	#ifdef WIN32
	PUCHAR context;
	OVERLAPPED *inOvLap;
	#else
	libusb_transfer* transfer;
	long bytesXfered;
	long bytesExpected;
	bool done;
	#endif
};

class USBPortConnection : public IConnection
{
public:
	USBPortConnection();
	~USBPortConnection();

	void DevicesChanged();
	int Open();
	int Open(unsigned index);
	void Close();
	void Reset();
	bool IsOpen();

	int SendData(const unsigned char *buffer, int length);
	int ReadData(unsigned char *buffer, int bytesRead);

	int BeginDataReading(unsigned char *buffer, long length);
	int WaitForReading(int contextHandle, unsigned int timeout_ms);
	int FinishDataReading(unsigned char *buffer, long length, int contextHandle);
	void AbortReading();
	void ResetReading();

	int BeginDataSending(unsigned char *buffer, long length);
	int WaitForSending(int contextHandle, unsigned int timeout_ms);
	int FinishDataSending(unsigned char *buffer, long length, int contextHandle);
	void AbortSending();

	int GetConnectionType();
	int CurrentDevice();

	string DeviceName();

	int LoadSettings(string configFilename);
	int SaveSettings(string configFilename);

	int SetCustomParameter(string paramName, void *value);
	int GetCustomParameter(string paramName, void *value);

private:
    int m_maxPacketSize;
    string m_hardwareName;
    int m_hardwareVer;

	USBTransferContext contexts[USB_MAX_CONTEXTS];
	USBTransferContext contextsToSend[USB_MAX_CONTEXTS];
	void Initialize();

	void FindAllUSBDevices();

	bool isConnected;
	int currentPortIndex;

	#ifdef WIN32
	CCyUSBDevice *USBDevicePrimary;
	//usb device for DigiRed transmitting
	CCyUSBDevice *USBDeviceSecondary;
	//control endpoints for DigiRed
	CCyControlEndPoint *InCtrlEndPt3;
	CCyControlEndPoint *OutCtrlEndPt3;

    //control endpoints for DigiGreen
	CCyUSBEndPoint *OutCtrEndPt;
	CCyUSBEndPoint *InCtrEndPt;

    //end points for samples reading and writing
	CCyUSBEndPoint *InEndPt;
	CCyUSBEndPoint *OutEndPt;

	#else
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = NULL; //a libusb session
	#endif
};

#endif
