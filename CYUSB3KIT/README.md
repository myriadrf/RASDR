# CYPRESS USB 3.0 SuperSpeed Explorer Kit

A Cypress FX3-based interface with general purpose connectivity.

## Contents

This folder contains projects used in debugging RASDR components using the Cypress SuperSpeed Explorer Kit.  This is an inexpensive development board distributed by Cypress Semiconductor, Ltd.

![CYUSB3KIT](http://www.cypress.com/sites/default/files/inline/fckImages/myresources/Kit%20Image%20sm.jpg)

The hardware can be ordered directly from Cypress; see the information page [here](http://www.cypress.com/documentation/development-kitsboards/cyusb3kit-003-ez-usb-fx3-superspeed-explorer-kit).

## Software

The 'streamer' folder contains a modified version of the Cypress streamer example program that is distributed in the [EZ-USB FX3 Software Development Kit](http://www.cypress.com/documentation/software-and-drivers/ez-usb-fx3-software-development-kit).  It has been updated to compile in Microsoft Visual Studio 2013 Express, to compile outside of the FX3 installation folder, and to allow a queue size of up to 512 transfers.

## Firmware

The 'ssek_emu' folder contains a firmware that is a modified version of the SS Explorer Kit project 'USBBulkSourceSinkLED' .  It has been modified to respond to the RASDR Vendor Command Set, and identify itself as a compatible RASDR device.  The firmware produces representative I/Q data of 'noise' in a replay-buffer manner, at approximately the same rate as a real RASDR device would

The firmware can be loaded to the CYUSB3Kit board by fitting the PMODE jumper J4, resetting the device, and using the CyControl program provided by the RASDR distribution to load the 'ssek_emu.img' to RAM.

To install the firmware into the I2C EEPROM, simply load the 'ssek_emu.img' to I2C.  Upon removing the PMODE jumper and resetting the CYUSB3KIT, the device will function as a RASDR emulator.

## Driver

Use the driver provide by the RASDR distribution for the above firmware(s).  Using the above firmware with the CYUSB3KIT will identify itself as a DigiRED_EMU device.

## Acknowledgement

The RASDR developers wish to thank Cypress Semiconductor, Ltd. for producing the SuperSpeed Explorer Kit, its resulting firmware files.  Inspecting these files has been instrumental in repairing a few long-standing deficiencies in the behavior of RASDR devices and USB3.0.

In addition, the availability of the Kit enables would-be RASDR users to obtain hardware and begin to explore the use of the RASDRviewer and other softwares in advance of obtaining an actual RASDR device which are currently circulating in a loaner program for [Society of Amateur Radio Astronomers](http://www.radio-astronomy.org/) members.

## Licensing

### Software

For details of software licensing please see the associated license.txt files in each folder.

### Firmware

For details of firmware licensing please see the associated license.txt or COPYING file(s) in each folder.

