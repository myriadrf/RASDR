# Radio Astronomy Software Defined Radio (RASDR)

This project provides access to the hardware designs, firmware, host system drivers and applications for the RASDR project.  RASDR is an Open Hardware project undertaken by members of the Society of Amateur Radio Astronomers (SARA) to develop a low cost, high performance software defined receiver for use by SARA members.  The goal of RASDR is to provide a low cost hardware that enables radio astronomers and educational institutions to perform high quality astronomical measurements.

At the core of this capability is the Lime Microsystems, Ltd. LMS6002D Field Programmable Radio Frequency device.  The device supports tunable RF reception over a wide range (400MHz to 3.8GHz) and high bandwidth (28Mhz).  Through the use of a Host Interface Module, the LMS6002D is connected to a personal computer (PC) over a standard USB link.  Both USB3 and USB2 are supported to enable the widest possible field of use, although full bandwidth of the LMS6002D is only achieved when using USB3.

![RASDR](https://github.com/myriadrf/RASDR/raw/master/design/rasdr2-with-usb3.jpg )
*RASDR2 hardware package consisting of DigiRED and MyriadRF modules*

## Device Specifications ##

Radio Astronomy research is dominated by sensitive front-end radio detection and amplification equipment, a wide-bandwidth analog to digital conversion stage, and finally, a digital processing system to extract and present information.  RASDR hardware is designed to provide all these functions in a low size, weight, and power form-factor.

![RASDR-DIAGRAM](https://github.com/myriadrf/RASDR/raw/master/design/myriadrf-base.png )
*RASDR2 block diagram showing basic use case and components*

One RF transceiver chip provides receive functionality.  The transmit section is calibrated to produce a continuous wave (CW) tone that is useful for up/down conversion of signals into the tuning band of the receive section.  Wideband SMA connectors are available to enable reception in the region between 400 MHz to 3.8 GHz with up to 28 MHz of bandwidth at 12 bit I/Q sampling.  The RASDR designs and driver source code are freely available at the RASDR Open Source project, please visit MyriadRF.org for details.

### Features ###

- Two channel simultaneous receive at max. 28 MHz bandwidth (transmit functions disabled in factory firmware and logic)
- Lime Microsystems, Ltd. FPRF transceiver programmable between 400 MHz to 3.8GHz with 12 bit I/Q sampling and 9 built-in RF Paths.
- Maximum Data Transfer of 160MB/s
- External reference clock input, enabling synchronous operation with test equipment and facility timing signals
- External general purpose I/O (GPIO) port providing 8 3.3V GPIOs and +5V power (1.25W maximum)
- Pulse Per Second (PPS) input on GPIO synchronously sampled and available in the receive data stream
- Power: +5V USB @ 0.75A (3.75W maximum required power)

### Electrical Interface ###

- SuperSpeed USB3 or **dual** USB2 data and power.  Max data rates: 160MB/s or 35MB/s respectively.
- SMA receive input, 50ohm, 400MHz to 3.8GHz
- SMA reference input, 50ohm, 10MHz
- SMA transmit output, 50ohm, 400MHz to 3.8GHz

### Physical Specifications ###

- Size:  70mm x 70mm x 32mm (2.75" x 2.75" x 1.25")
- Weight: approx. 48 gram (1.5 oz.)

## Directory Description ##

- **design** � directory contains high-level design documents and specifications for the RASDR2 module and host APIs. This directory also includes development and testing information.

- **DigiRED** � contains the hardware design files, firmware and information needed to manufacture the various host interfaces modules.  The embedded firmware for the FX3 provides the SuperSpeed USB 3.0 interface and can also be customized for conditional on board processing within the limits of the internal RAM.

- **host** � the host directory contains host processor APIs, device drivers and libraries for accessing the RASDR modules via USB. Support is provided for embedded C/C++ development.

## Licensing ##
Unless otherwise specified, all software source files are licensed using the GNU General Public license version 2.  All hardware related designs and source artifacts are licensed under the  �Creative Commons Attribution 3.0 Unported�. To read the details of the license please review "license.html" or visit http://creativecommons.org/licenses/by/3.0/legalcode.

For specific information see the COPYING.MD file(s).
