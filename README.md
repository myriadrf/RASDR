# Myriad-RF Hardware

This repository contains the [Myriad-RF](http://myriadrf.org/) reference hardware designs for Lime Microsystem's LMS6002D transceiver, in PDF and [KiCad](http://www.kicad-pcb.org) formats, along with the associated firmware.

## Contents

The directory structure for the hardware designs is as follows:

      <project>/hardware/<version>/
          BOM/                   - bill of materials spreadsheet
          Gerbers/               - Gerber CAM files
          KiCAD/                 - KiCAD schematic and layout files
          Manufacturing/         - Additional manufacturing information
          PDF/                   - Schematic and layout PDFs
          Reports/               - DRC, ERC and drill reports

### Myriad-RF 1 module

Hardware design files for the Myriad-RF 1 RF module.

Note that there are two versions of the design: one with vias in pads, and another with them off.

### DE0-Nano Interface

Hardware design files and firmware sources (FPGA HDL + Cypress FX2 code) for the DE0-Nano interface.

### Zipper Interface

This interface allows the Myriad-RF 1 to be used with FPGA development boards that have either a HSMC or FMC connector.

*Note that v1 of the hardware design was not made generally available.*

## Licensing

### Hardware

The hardware designs are licensed under a Creative Commons Attribution 3.0 Unported licence.

*Note: The Myriad-RF 1 and DE0-Nano Interface hardware designs were initially published under the Creative Commons Attribution-ShareAlike 3.0 Unported licence. As of 30th September 2013 these have been re-licensed under the more permissive Creative Commons Attribution 3.0 Unported licence.*

### Firmware

For details of firmware licensing please see the associated COPYING file(s).
