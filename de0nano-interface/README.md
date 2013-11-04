## Overview

This interface board forms part of the original Myriad RF Development Kit, and is intended to be used together with the Myriad-RF 1 RF module and a DEO-Nano FPGA development kit.

The latest version of the Development Kit manual can be found in the docs/
directory.

## Structure

- docs - documentation
- firmware - firmware for the DE0-Nano USB controller
  - bin - binaries
  - src - sources
- gateware - FPGA RTL
  - prog_files - compiled RTL for device programming
- hardware - hardware design files

## Licensing

See the COPYING files.

## Host software

The ctr_6002dr2 utility requires a Windows host. Reports on experiences of using this under Wine on Linux/Mac, and porting offers, are welcomed.

### Cypress SuiteUSB

The SuiteUSB software can be downloaded from:

  http://www.cypress.com/?rID=34870

This contains the Generic USB Driver, along with the USB Control Center software which can be used to download firmware.

### ctr_6002dr2 GUI

This tool enables configuration and calibration of the LMS6002D transceiver. It can be found in the myriadrf-utils repository:

  https://github.com/myriadrf/myriadrf-utils
