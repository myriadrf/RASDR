# Radio Astronomy Software Defined Receiver (RASDR) Components for Manufacture

![RASDR-COMPONENTS](https://github.com/myriadrf/RASDR/raw/master/design/rasdr2-with-usb3.jpg )
*RASDR2 hardware components consisting of DigiRED and MyriadRF modules*

![RASDR-CASE](https://github.com/myriadrf/RASDR/raw/master/docs/rasdr-case-front-new.png )
*RASDR2 case 3D model

## Directory Description ##

- **rasdr2-bom-and-components.xlsx** � contains a summary of all the components needed to build and assemble a complete RASDR device including all internal parts, case, connectors and cables.  A cost estimate of qty 10, 25 and 100 is given along with an extrapolation curve for numbers up to 1000.

- **DigiRED_v1r1** � contains the manufacturing files for the DigiRED USB digital interface board.  This board specifies a BOM that depopulates the TX side and USB to save cost.  It also specifies long-barrel SMA connectors to allow mounting to the custom case.

- **MyriadRF_v1r3e1** � contains the manufacturing files for the MyriadRF analog interface board.  This design is based on the via-off-pad, includes the resistors needed for proper operation with the DigiRED board, and has no vias less than 0.2mm to save cost.  It also specifies long-barrel SMA connectors to allow mounting to the custom case.

## Licensing ##
Unless otherwise specified, all hardware related designs and source artifacts are licensed under the  �Creative Commons Attribution 3.0 Unported�. To read the details of the license please review "license.html" or visit http://creativecommons.org/licenses/by/3.0/legalcode.

For specific information see the COPYING.MD file(s).
