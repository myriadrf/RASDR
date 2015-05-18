// -----------------------------------------------------------------------------
// FILE:        "dlgSerPort.cpp"
// DESCRIPTION: "Source Code File"
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
#include "dlgSerPort.h"
#include "ctr_6002dr2_LogicDLL.h"
#include <string>
using namespace std;

//(*InternalHeaders(dlgSerPort)
#include <wx/sizer.h>
#include <wx/radiobox.h>
#include <wx/statline.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(dlgSerPort)
const long dlgSerPort::ID_RADIOBOX1 = wxNewId();
const long dlgSerPort::ID_COMBOBOX1 = wxNewId();
const long dlgSerPort::ID_COMBOBOX2 = wxNewId();
const long dlgSerPort::ID_RADIOBOX2 = wxNewId();
const long dlgSerPort::ID_STATICLINE1 = wxNewId();
const long dlgSerPort::ID_BUTTON1 = wxNewId();
const long dlgSerPort::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgSerPort,wxDialog)
	//(*EventTable(dlgSerPort)
	//*)
END_EVENT_TABLE()

dlgSerPort::dlgSerPort(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgSerPort::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgSerPort)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Connection settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("COM"),
		_("USB")
	};
	rgrPortSelection = new wxRadioBox(this, ID_RADIOBOX1, _("Port selection"), wxDefaultPosition, wxSize(133,44), 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrPortSelection->SetSelection(0);
	FlexGridSizer1->Add(rgrPortSelection, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer2 = new wxFlexGridSizer(3, 2, 10, 10);
	cmbComPorts = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(152,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	FlexGridSizer2->Add(cmbComPorts, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	cmbUSBDevices = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(152,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer2->Add(cmbUSBDevices, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	wxString __wxRadioBoxChoices_2[6] =
	{
		_("4 Mhz"),
		_("2 Mhz"),
		_("1 Mhz"),
		_("0.5 Mhz"),
		_("0.25 Mhz"),
		_("0.125 Mhz")
	};
	rgrBaud = new wxRadioBox(this, ID_RADIOBOX2, _("SPI Clock Frequency"), wxDefaultPosition, wxDefaultSize, 6, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrBaud->SetSelection(0);
	FlexGridSizer2->Add(rgrBaud, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	StaticLine1->Hide();
	FlexGridSizer2->Add(StaticLine1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnClose = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(btnClose, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(btnCancel, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgSerPort::OnbtnCloseClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgSerPort::OnbtnCancelClick);
	//*)
	connectionType = -1;
	cmbUSBDevices->Clear();
	cmbUSBDevices->Append("No USB Devices Found");
	cmbUSBDevices->SetSelection( 0);
	cmbComPorts->Clear();
	cmbComPorts->Append("No ports found");
	cmbComPorts->SetSelection(0);
	FormShow();
}

dlgSerPort::~dlgSerPort()
{
	//(*Destroy(dlgSerPort)
	//*)
}


void dlgSerPort::OnbtnCloseClick(wxCommandEvent& event)
{
    if(rgrPortSelection->GetSelection() == 1)
    {
        LMAL_SetConnectionType( rgrPortSelection->GetSelection() );
        LMAL_OpenI(cmbUSBDevices->GetSelection());
    }
    else
    {
        LMAL_SetConnectionType( rgrPortSelection->GetSelection() );
        LMAL_OpenI(cmbComPorts->GetSelection());
    }
    this->EndDialog(wxID_OK);
}

void dlgSerPort::OnrgrPortSelectionSelect(wxCommandEvent& event)
{
    LMAL_SetConnectionType(rgrPortSelection->GetSelection());
	GetConnectionInfo();
}

void dlgSerPort::OnrgrBaudSelect(wxCommandEvent& event)
{
    if( LMAL_GetConnectionType() == 0)
	{
		int baudrate = Code2Baud(rgrBaud->GetSelection());
		LMAL_SetPortCustomParameter("baudrate", (char*)&baudrate);
    }
}

void dlgSerPort::GetConnectionInfo()
{
	int currentDeviceInd = LMAL_CurrentDevice();
	rgrPortSelection->SetSelection( LMAL_GetConnectionType());
	if( connectionType != LMAL_GetConnectionType() )
	{
		connectionType = LMAL_GetConnectionType();
		string stmp;
		int nameBufLen = 256;
		char *devName = new char[nameBufLen];
		int nameLen = 0;
		int devicesCount = LMAL_DeviceCount();

		if(rgrPortSelection->GetSelection() == 0)
		{
			cmbComPorts->Clear();
			if(devicesCount == 0)
			{
				cmbComPorts->Append("No Devices Found");
				cmbComPorts->SetSelection( 0);
			}
			else
			{
				for(int i=0; i<devicesCount; i++)
                {
                    char name[512];
                    memset(name, 0, 512);
                    LMAL_DeviceName(name, i);
                    cmbComPorts->Append( name );
                }
				cmbComPorts->SetSelection( LMAL_CurrentDevice() );
			}
		}
		if(rgrPortSelection->GetSelection() == 1)
		{
			cmbUSBDevices->Clear();
			if(devicesCount == 0)
			{
				cmbUSBDevices->Append("No USB Devices Found");
				cmbUSBDevices->SetSelection( 0);
			}
			for(int i=0; i<devicesCount; i++)
			{
                char name[512];
                memset(name, 0, 512);
                LMAL_DeviceName(name, i);
                cmbUSBDevices->Append( name );
			}
			cmbUSBDevices->SetSelection( LMAL_CurrentDevice());
		}

		delete []devName;
    }
}

// ---------------------------------------------------------------------------
int dlgSerPort::Code2Baud(int Code)
{
	int baud;
	switch (Code)
	{
	case 1:
		baud = 14400;
		break;
	case 2:
		baud = 19200;
		break;
	case 3:
		baud = 38400;
		break;
	case 4:
		baud = 57600;
		break;
	case 5:
		baud = 115200;
		break;
	default:
		baud = 9600;
	};
	return baud;
};
int dlgSerPort::Baud2Code(int baudrate)
{
	int code;
	switch (baudrate)
	{
	case 14400:
		code = 1;
		break;
	case 19200:
		code = 2;
		break;
	case 38400:
		code = 3;
		break;
	case 57600:
		code = 4;
		break;
	case 115200:
		code = 5;
		break;
	default:
		code = 0;
	};
	return code;
};

// ---------------------------------------------------------------------------
void dlgSerPort::FormShow()
{
	GetConnectionInfo();
	int portType = LMAL_GetConnectionType();
	if( LMAL_IsOpen() )
	{
		if(portType == 0)
		{
			cmbComPorts->SetSelection( LMAL_CurrentDevice());
			int baudrate = 0;
			LMAL_GetPortCustomParameter("baudrate", (char*)&baudrate);
			rgrBaud->SetSelection( Baud2Code( baudrate));
		}
		else if( portType == 1)
			cmbUSBDevices->SetSelection( LMAL_CurrentDevice());
	}
}

void dlgSerPort::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndDialog( wxID_CANCEL );
}
