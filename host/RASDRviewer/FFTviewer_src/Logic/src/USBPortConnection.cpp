// -----------------------------------------------------------------------------
// FILE: 		USBPortConnection.cpp
// DESCRIPTION:	implements data transfer through USB port
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "USBPortConnection.h"
#include <iostream>

#ifdef WIN32


	#include "windows.h"
	#include "CyAPI.h"
#else
	#include <libusb-1.0/libusb.h>
	#include "TimeCounter.h"
#define USB_TIMEOUT 1000

#endif

#define HW_DIGIRED "DigiRed"
#define HW_DIGIGREEN "DigiGreen"

#define HW_LDIGIRED L"DigiRed"
#define HW_LDIGIGREEN L"DigiGreen"

#define CTR_W_REQCODE 0xC1
#define CTR_W_VALUE 0x0000
#define CTR_W_INDEX 0x0000

#define CTR_R_REQCODE 0xC0
#define CTR_R_VALUE 0x0000
#define CTR_R_INDEX 0x0000

#define CMD_GET_INFO 0x50

using namespace std;
/**
	@brief Initializes port type and object necessary to communicate to usb device.
*/
USBPortConnection::USBPortConnection()
{
    m_maxPacketSize = 256;
    m_hardwareName = "";
    isConnected = false;
    portType = 1;
#ifdef WIN32
    USBDevicePrimary = new CCyUSBDevice(NULL);
    OutCtrEndPt = NULL;
    InCtrEndPt = NULL;
#else
    int r = libusb_init(&ctx); //initialize the library for the session we just declared
    if(r < 0)
    {
        cout<<"Init Error "<<r<<endl; //there was an error
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
#endif
    currentPortIndex = -1;
}

/**
	@brief Closes connection to chip and deallocates used memory.
*/
USBPortConnection::~USBPortConnection()
{
    Close();
#ifdef WIN32
    delete USBDevicePrimary;
#else
    libusb_exit(ctx);
#endif
}

/**
	@brief Actions to take on device change detection
*/
void USBPortConnection::DevicesChanged()
{
    Close();
    isConnected = false;
    {
        m_deviceNames.clear();
        Open();
    }
}

/**
	@brief Automatically open first available chip connected to usb port.
	@return 1-Success, 0-chip not found.
*/
int USBPortConnection::Open()
{
    currentPortIndex = -1;
    if(m_deviceNames.size() == 0)
        FindAllUSBDevices();

#ifdef WIN32
    for(int i=0; i<USBDevicePrimary->DeviceCount(); i++)
        if( Open(i) == 1)
        {
            currentPortIndex = i;
            return true;
        }
#else
    if(Open(0))
        return true;
#endif

    return false;
}

/**
	@brief Tries to open connected USB device and find communication endpoints.
	@return Returns 1-Success, 0-EndPoints not found or device didn't connect.
*/
int USBPortConnection::Open(unsigned index)
{
#ifdef WIN32
	unsigned short vID;
	unsigned short pID;
	wstring m_hardwareDesc = L"";
	int devicesFound = 0;
	if( index < USBDevicePrimary->DeviceCount())
	{
		if(USBDevicePrimary->Open(index))
		{

			vID = USBDevicePrimary->VendorID;
			pID = USBDevicePrimary->ProductID;

			//check if vendor and product ID matches
			if( vID != 1204 )
            {
                return 0;
            }
            else
            {
                if( pID != 241 && pID != 34323 )
                {
                    return 0;
                }
            }


            m_hardwareDesc = USBDevicePrimary->Product;

            int pos;
            pos = m_hardwareDesc.find(HW_LDIGIRED, 0);
            if( pos != wstring::npos )
            {
                m_hardwareName = "DigiRed";
            }
            else
            {
                m_hardwareName = "DigiGreen";
            }

            if(m_hardwareName != "DigiRed")
            {
                // DigiGreen, control through bulk endpoints
                int endPointsFound = 0;
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                {
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x01)
                    {
                        OutCtrEndPt = USBDevicePrimary->EndPoints[i];
                        endPointsFound++;
                        break;
                    }
                }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                {
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x81)
                    {
                        InCtrEndPt = USBDevicePrimary->EndPoints[i];
                        endPointsFound++;
                        break;
                    }
                }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x86)
                    {
                        InEndPt = USBDevicePrimary->EndPoints[i];
                        m_maxPacketSize = InEndPt->MaxPktSize;
                        //m_maxPacketSize = 1024;
                        long len = InEndPt->MaxPktSize * 64;
                        // Each xfer request will get PPX isoc packets
                        InEndPt->SetXferSize(len);
                    }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x02)
                    {
                        OutEndPt = USBDevicePrimary->EndPoints[i];
                    }

                if(endPointsFound == 2)
                {
                    currentPortIndex = index;
                    isConnected = true;
                    return true;
                }
                else
                    return false;
            }
            else //digired, controls through control end point
            {
                InCtrlEndPt3 = new CCyControlEndPoint(*USBDevicePrimary->ControlEndPt);
                OutCtrlEndPt3 = new CCyControlEndPoint(*USBDevicePrimary->ControlEndPt);

                InCtrlEndPt3->ReqCode = CTR_R_REQCODE;
                InCtrlEndPt3->Value = CTR_R_VALUE;
                InCtrlEndPt3->Index = CTR_R_INDEX;

                OutCtrlEndPt3->ReqCode = CTR_W_REQCODE;
                OutCtrlEndPt3->Value = CTR_W_VALUE;
                OutCtrlEndPt3->Index = CTR_W_INDEX;

                bool devIsTx;
                devIsTx = false;

                char unsigned tbuf[64];
                long len = 64;
                memset(tbuf, 0, len);
                tbuf[0] = CMD_GET_INFO;
                SendData(tbuf, len);
                ReadData(tbuf, len);

                if(tbuf[0] == 1)
                    devIsTx = true;

                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x01)
                    {
                        //cout << "out end point found " << endl;
                        OutEndPt = USBDevicePrimary->EndPoints[i];
                        //OutEndPt->MaxPktSize = OutEndPt->MaxPktSize;
                        long len = OutEndPt->MaxPktSize * 64;
                        // Each xfer request will get PPX isoc packets
                        OutEndPt->SetXferSize(len);
                        break;
                    }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x81)
                    {
                        //cout << "in end point found " << endl;
                        InEndPt = USBDevicePrimary->EndPoints[i];
                        m_maxPacketSize = InEndPt->MaxPktSize;
                        long len = InEndPt->MaxPktSize * 64;
                        // Each xfer request will get PPX isoc packets
                        InEndPt->SetXferSize(len);
                        break;
                    }
                isConnected = true;
                return true;
            }
            return false;
		} //successfully opened device
	} //if has devices
    return 0;
#else
    int usbDeviceCount = libusb_get_device_list(ctx, &devs);;
    if(usbDeviceCount > 0)
    {
        //open by pid and vid
		dev_handle = libusb_open_device_with_vid_pid(ctx, 1204, 34323);
//		dev_handle = libusb_open_device_with_vid_pid(ctx, 1204, 241);
		if(dev_handle == 0)
            return false;
        if(libusb_kernel_driver_active(dev_handle, 0) == 1)   //find out if kernel driver is attached
        {
            cout<<"Kernel Driver Active"<<endl;
            if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
                cout<<"Kernel Driver Detached!"<<endl;
        }
        int r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device
        if(r < 0)
        {
            cout<<"Cannot Claim Interface"<<endl;
            return 1;
        }
        cout<<"Claimed Interface"<<endl;
        libusb_free_device_list(devs, 1);
        isConnected = true;
        return true;
    }
    else
    {
        libusb_free_device_list(devs, 1);
        return false;
    }
#endif

}

/**
	@brief Closes communication to device.
*/
void USBPortConnection::Close()
{
    #ifdef WIN32
	USBDevicePrimary->Close();
	InEndPt = NULL;
	OutEndPt = NULL;
    #else
    int r = libusb_release_interface(dev_handle, 0);
    libusb_close(dev_handle);
    #endif
    isConnected = false;
}

/**
	@brief Returns connection status
	@return 1-connection open, 0-connection closed.
*/
bool USBPortConnection::IsOpen()
{
    #ifdef WIN32
    return USBDevicePrimary->IsOpen() && isConnected;
    #else
    return isConnected;
    #endif
}

/**
	@brief Sends given data buffer to chip through USB port.
	@param buffer data buffer, must not be longer than 64 bytes.
	@param length given buffer size.
	@return number of bytes sent.
*/
int USBPortConnection::SendData(const unsigned char *buffer, int length)
{
    unsigned char temp[64];
    if(length > 64)
        length = 64;
    memcpy(temp, buffer, length);
    if(IsOpen())
    {
        long len = length;
        if(m_hardwareName == HW_DIGIRED)
        {
            #ifdef WIN32
            if(OutCtrlEndPt3)
                return OutCtrlEndPt3->Write(temp, len);
            #endif
        }
        else
        {
            #ifdef WIN32
            if(OutCtrEndPt)
                return OutCtrEndPt->XferData(temp, len);
            else
                return 0;
            #else
                int actual = 0;
                libusb_bulk_transfer(dev_handle, 0x01, temp, len, &actual, USB_TIMEOUT);
                return actual;
            #endif
        }
    }
    return 0;
}

/**
	@brief Reads data coming from the chip through USB port.
	@param buffer pointer to array where received data will be copied, array must be
	big enough to fit received data.
	@param bytesRead number of bytes to read from chip.
	@return number of bytes received.
*/
int USBPortConnection::ReadData(unsigned char *buffer, int bytesRead)
{
    if(IsOpen())
    {
        long len = bytesRead;
        if(m_hardwareName == HW_DIGIRED)
        {
            #ifdef WIN32
            if(InCtrlEndPt3)
                return InCtrlEndPt3->Read((unsigned char*)buffer, len);
            #endif
        }
        else
        {
            #ifdef WIN32
            if(InCtrEndPt)
                return InCtrEndPt->XferData((unsigned char*)buffer, len);
            else
                return 0;
            #else
                int actual = 0;
                libusb_bulk_transfer(dev_handle, 0x81, (unsigned char*)buffer, len, &actual, USB_TIMEOUT);
                return actual;
            #endif
        }
    }
    return 0;
}

#ifndef WIN32
/**
	@brief Function for handling libusb callbacks
*/
void callback_libusbtransfer(libusb_transfer *trans)
{
	USBTransferContext *context = reinterpret_cast<USBTransferContext*>(trans->user_data);
	switch(trans->status)
	{
    case LIBUSB_TRANSFER_CANCELLED:
        //printf("Transfer canceled\n" );
        break;
    case LIBUSB_TRANSFER_COMPLETED:
        if(trans->actual_length == context->bytesExpected)
		{
			context->bytesXfered = trans->actual_length;
			context->done = true;
		}
        break;
    case LIBUSB_TRANSFER_ERROR:
        //printf("TRANSFER ERRRO\n");
        break;
    case LIBUSB_TRANSFER_TIMED_OUT:
        //printf("transfer timed out\n");

        break;
    case LIBUSB_TRANSFER_OVERFLOW:
        //printf("transfer overflow\n");

        break;
	}
}
#endif

/**
	@brief Starts asynchronous data reading from board
	@param *buffer buffer where to store received data
	@param length number of bytes to read
	@return handle of transfer context
*/
int USBPortConnection::BeginDataReading(unsigned char *buffer, long length)
{
    int i = 0;
	unsigned int Timeout = 1000;
	bool contextFound = false;
	//find not used context
    for(i = 0; i<USB_MAX_CONTEXTS; i++)
    {
        if(!contexts[i].used)
        {
            contextFound = true;
            break;
        }
    }
    if(!contextFound)
        return -1;
    contexts[i].used = true;
    #ifdef WIN32
    if(InEndPt)
        contexts[i].context = InEndPt->BeginDataXfer(buffer, length, contexts[i].inOvLap);
	return i;
    #else
    libusb_transfer *tr = contexts[i].transfer;
    libusb_set_iso_packet_lengths(contexts[i].transfer, 512*64);
	libusb_fill_bulk_transfer(tr, dev_handle, 0x86, buffer, length, callback_libusbtransfer, &contexts[i], Timeout);
	contexts[i].done = false;
	contexts[i].bytesXfered = 0;
	contexts[i].bytesExpected = length;
    libusb_submit_transfer(tr);
    #endif // WIN32
    return i;
}

/**
	@brief Waits for asynchronous data reception
	@param contextHandle handle of which context data to wait
	@param timeout_ms number of miliseconds to wait
	@return 1-data received, 0-data not received
*/
int USBPortConnection::WaitForReading(int contextHandle, unsigned int timeout_ms)
{
    if( contexts[contextHandle].used == true )
    {
    #ifdef WIN32
	int status = 0;
	if(InEndPt)
        status = InEndPt->WaitForXfer(contexts[contextHandle].inOvLap, timeout_ms);
	return status;
    #else
	unsigned long t1, t2;
	t2 = t1 = GetTickCount();
    while(contexts[contextHandle].bytesXfered < contexts[contextHandle].bytesExpected && (t2 - t1) < timeout_ms)
	{
		usleep(1000);
		libusb_handle_events(ctx);
		t2 = GetTickCount();
	}
	if((t2-t1) > timeout_ms)
		return 0;
    return 1;
    #endif
    }
    else
        return 0;
}

/**
	@brief Finishes asynchronous data reading from board
	@param buffer array where to store received data
	@param length number of bytes to read, function changes this value to number of bytes actually received
	@param contextHandle handle of which context to finish
	@return false failure, true success
*/
int USBPortConnection::FinishDataReading(unsigned char *buffer, long &length, int contextHandle)
{
    if( contexts[contextHandle].used == true)
    {
    #ifdef WIN32
    int status;
    if(InEndPt)
        status = InEndPt->FinishDataXfer(buffer, length, contexts[contextHandle].inOvLap, contexts[contextHandle].context);
    contexts[contextHandle].used = false;
    return status;
    #else
    //memset(buffer, 0, length);
    libusb_transfer *tr = contexts[contextHandle].transfer;
	memcpy(buffer, tr->buffer, contexts[contextHandle].bytesXfered);
	length = contexts[contextHandle].bytesXfered;
	contexts[contextHandle].used = false;
	return length;
    #endif
    }
    else
        return 0;
}

/**
	@brief Aborts reading operations
*/
void USBPortConnection::AbortReading()
{
#ifdef WIN32
	InEndPt->Abort();
#endif
}

/**
	@brief Starts asynchronous data Sending to board
	@param *buffer buffer to send
	@param length number of bytes to send
	@return handle of transfer context
*/
int USBPortConnection::BeginDataSending(unsigned char *buffer, long length)
{
    int i = 0;
	unsigned int Timeout = 1000;
	//find not used context
	bool contextFound = false;
     for(i = 0; i<USB_MAX_CONTEXTS; i++)
    {
        if(!contextsToSend[i].used)
        {
            contextFound = true;
            break;
        }
    }
    if(!contextFound)
        return -1;
    contextsToSend[i].used = true;
    #ifdef WIN32
    if(OutEndPt)
        contextsToSend[i].context = OutEndPt->BeginDataXfer(buffer, length, contextsToSend[i].inOvLap);
	return i;
    #else
    libusb_transfer *tr = contexts[i].transfer;
    libusb_set_iso_packet_lengths(contexts[i].transfer, 512*64);
	libusb_fill_bulk_transfer(tr, dev_handle, 0x86, buffer, length, callback_libusbtransfer, &contexts[i], Timeout);
	contexts[i].done = false;
	contexts[i].bytesXfered = 0;
	contexts[i].bytesExpected = length;
    libusb_submit_transfer(tr);
    #endif // WIN32
    return i;
}

/**
	@brief Waits for asynchronous data sending
	@param contextHandle handle of which context data to wait
	@param timeout_ms number of miliseconds to wait
	@return 1-data received, 0-data not received
*/
int USBPortConnection::WaitForSending(int contextHandle, unsigned int timeout_ms)
{
    if( contextsToSend[contextHandle].used == true )
    {
    #ifdef WIN32
	int status = 0;
	if(OutEndPt)
        status = OutEndPt->WaitForXfer(contextsToSend[contextHandle].inOvLap, timeout_ms);
	return status;
    #else
	unsigned long t1, t2;
	t2 = t1 = GetTickCount();
    while(contextsToSend[contextHandle].bytesXfered < contextsToSend[contextHandle].bytesExpected && (t2 - t1) < timeout_ms)
	{
		usleep(1000);
		libusb_handle_events(ctx);
		t2 = GetTickCount();
	}
	if((t2-t1) > timeout_ms)
		return 0;
    return 1;
    #endif
    }
    else
        return 0;
}

/**
	@brief Finishes asynchronous data sending to board
	@param buffer array where to store received data
	@param length number of bytes to read, function changes this value to number of bytes acctually received
	@param contextHandle handle of which context to finish
	@return false failure, true success
*/
int USBPortConnection::FinishDataSending(unsigned char *buffer, long &length, int contextHandle)
{
    if( contextsToSend[contextHandle].used == true)
    {
    #ifdef WIN32
	int status = 0;
	if(OutEndPt)
        status = OutEndPt->FinishDataXfer(buffer, length, contextsToSend[contextHandle].inOvLap, contextsToSend[contextHandle].context);
    contextsToSend[contextHandle].used = false;
    return length;
    #else
    //memset(buffer, 0, length);
    libusb_transfer *tr = contextsToSend[contextHandle].transfer;
	memcpy(buffer, tr->buffer, contextsToSend[contextHandle].bytesXfered);
	length = contextsToSend[contextHandle].bytesXfered;
	contextsToSend[contextHandle].used = false;
	return length;
    #endif
    }
    else
        return 0;
}

/**
	@brief Aborts sending operations
*/
void USBPortConnection::AbortSending()
{
#ifdef WIN32
	OutEndPt->Abort();
#endif
}



/**
	@return Connection port type.
*/
int USBPortConnection::GetConnectionType()
{
    return portType;
}

/**
	@return currently used device index.
*/
int USBPortConnection::CurrentDevice()
{
    return currentPortIndex;
}

/**
	@return name of currently opened device as string.
*/
string USBPortConnection::DeviceName()
{
	#ifdef WIN32
	string name;
	char tempName [256];
	//memcpy(&tempName, &USBDevicePrimary->DeviceName, 256);
	for(int i=0; i<256; ++i)
	{
		tempName[i] = USBDevicePrimary->DeviceName[i];
	}
    name = tempName;
    return name;
    #else
    string name = "no name";
    return name;
    #endif
}

int USBPortConnection::LoadSettings(string configFilename)
{
    return 0;
}
int USBPortConnection::SaveSettings(string configFilename)
{
    return 0;
}
int USBPortConnection::SetCustomParameter(string paramName, void *value)
{
    return 0;
}
int USBPortConnection::GetCustomParameter(string paramName, void *value)
{
    if(paramName == "HW_DigiRed")
        *(char*)value = (m_hardwareName == "DigiRed");

    if(paramName == "MaxPacketSize")
    {
        *(int*)value = m_maxPacketSize;
    }
    return 0;
}

/**
	@brief Finds all connected USB devices and tries to open connected chip.
*/
void USBPortConnection::Initialize()
{
    FindAllUSBDevices();
    Open();
}

/**
	@brief Checks all connected USB devices and found chips are added to list.
*/
void USBPortConnection::FindAllUSBDevices()
{
    #ifdef WIN32
    USBDevicePrimary->Close();
    currentPortIndex = -1;
    m_deviceNames.clear();
    string name;
    if (USBDevicePrimary->DeviceCount())
    {
        for (int i = 0; i < USBDevicePrimary->DeviceCount(); i++)
        {
            Open(i);
            name = DeviceName();
            if( m_hardwareName == "DigiRed")
            {
                unsigned char tbuf[64];
                long len = 64;
                memset(tbuf, 0, len);
                tbuf[0] = CMD_GET_INFO;
                SendData(tbuf, len);
                ReadData(tbuf, len);

                if(tbuf[0] == 1)
                    name.append( " (Transmitter)" );
                else
                    name.append( " (Receiver)" );
            }
            m_deviceNames.push_back(name);
        }
        currentPortIndex = -1;
    }
    #endif
}
