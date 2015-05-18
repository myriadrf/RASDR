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
