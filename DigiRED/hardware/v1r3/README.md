## DigiRED Design ##
This directory contains the hardware source artifacts for the DigiRED v1.0 Host Interface Module. This is the prototype design for the module and is provided as a reference.

The major unresolved problem with this design is an inability of the transmit FX3 to operate continuously without missing a sample as an internal buffer swap occurs (*).  This results in a buildup of samples for each buffer until a noticable skew is observed.  As the RASDR project does not require the ability to construct and transmit arbitrary waveforms, this limitation is considered acceptable for its field of use.   


(*) this is not normally a problem with designs incorporating an FPGA as the programmable logic buffers the two clock domains.  The RASDR desires to avoid incorporating an FPGA to reduce complexity and cost of the design.

## Directory Structure ##
The directory is organized into the various packages for schematic design and layout (KiCAD), PCB Manufacturing (Gerbers and Manufacturing), and Assembly (BOM, Reports).  The PDF directory is provided for easy access to the design and layout.

----------

## Designs / Source Artifacts Licensing ##
All hardware source artifacts contained within this directory are licensed under the “Creative Commons Attribution 3.0 Unported”.  To read the details of the license please review "COPYING" or visit [http://creativecommons.org/licenses/by/3.0/legalcode.](http://creativecommons.org/licenses/by/3.0/legalcode.)


