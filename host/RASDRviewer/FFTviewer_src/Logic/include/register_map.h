// -----------------------------------------------------------------------------
// FILE:        "register_map.h"
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
#ifndef register_map_H
#define register_map_H

//Register map for use with AN428 (JumpStart)
//http://www.silabs.com/clocks 
//Copyright 2012 Silicon Laboratories
//#BEGIN_HEADER
//Date = 2012 m. liepos 12 d. 14:35
//File version = 3
//Software Name = ClockBuilder Desktop Software
//Software version = 5.0.0
//Software date = March 17, 2012
//Chip = Si5356
//Part Number = Si5356
//#END_HEADER
//Input Frequency (MHz): 30,720000000

//Input Frequency (MHz) = 30,720000000
//Input Type = OFF
//P1 = 1
//Input Mux = FbClk
//FDBK Input Frequency (MHz) = 30,720000000
//FDBK Input Type = CMOS_SSTL_HSTL
//P2 = 1
//FDBK Mux = FbClk
//PFD Input Frequency (MHz) = 30,720000000
//VCO Frequency (GHz) = 2,200000
//N = 71  59/96  (71,6146)
//Internal feedback enabled
//Maximum Output Clock Frequency (MHz) = VCO / 8 = 275,000000
//Output Clock 0
// Output is off
//Output Clock 1
// Output Frequency (MHz) = 30,000000000
// Mux Selection = IDn
// MultiSynth = 73  1/3  (73,3333)
// R = 1
//Output Clock 2
// Output Frequency (MHz) = 30,000000000
// Mux Selection = IDn
// MultiSynth = 73  1/3  (73,3333)
// R = 1
//Output Clock 3
// Output is off
//Driver 0
// Disabled
// Powered off
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Driver 1
// Enabled
// Powered on
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Driver 2
// Enabled
// Powered on
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Driver 3
// Disabled
// Powered off
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Initial phase offset 0 (ns) = 0,000
//Initial phase offset 1 (ns) = 0,000
//Initial phase offset 2 (ns) = 0,000
//Initial phase offset 3 (ns) = 0,000
//SSC is disabled

#define NUM_REGS_MAX 350

typedef struct Reg_Data{
   unsigned char Reg_Addr;
   unsigned char Reg_Val;
   unsigned char Reg_Mask;
} Reg_Data;

extern Reg_Data Reg_Store[NUM_REGS_MAX];

#endif
