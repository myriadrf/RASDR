Board Description
-----------------

board designation           : DigiRED v1.0
board type                  : Lead Free
board size                  : 59.0 mm x 62.0 mm
board thickness             : 1.6 mm +/- 10 %
board material              : FR4
number of layers            : 6
Gerber file format          : RS-274-X
Solder Mask                 : Red

Top layer copper foil thickness	: 18 um
Dielectric thickness between Top layer and 2nd layer: 180 um
Dielectric between Top layer and 2nd layer relative permittivity (Er): 4.4

plating finish (both sides) : electroless nickel immersion gold (ENIG)
                              0.08-0.13 um of gold over
                              3.00-6.00 um of nickel
                              per IPC-4552 Amendment 1

Min track width 	    : 0.20 mm  
Min Via hole drill          : 0.20 mm  
Min pads and track clearance: 0.10 mm   	

Board Stackup
-------------

SMD paste Top		: DigiRED_v1.0-F_Paste.gbp
Silk Top		: DigiRED_v1.0-F_SilkS.gto
SolderMask Top		: DigiRED_v1.0-F_Mask.gts

Top Layer		: DigiRED_v1.0-Front_Cu.gtl
GND Layer		: DigiRED_v1.0-GND_Cu.gbr				
Inner Layer 1		: DigiRED_v1.0-Signal_1_Cu.gbr
Inner Layer 2		: DigiRED_v1.0-Signal_2_Cu.gbr
Power Layer             : DigiRED_v1.0-Power_Cu.gbr
Bottom Layer		: DigiRED_v1.0-Back_Cu.gbl

SolderMask Bottom	: DigiRED_v1.0-B_Mask.gbs
Silk Bottom		: DigiRED_v1.0-B_SilkS.gbo
SMD paste Bottom	: DigiRED_v1.0-B_Paste.gbp

----------------

PCB edges               : DigiRED_v1.0-Edge_Cuts.gbr

Drill map            	: DigiRED_v1-drl_map.pho
NC Drill file		: DigiRED_v1.0.drl

Controlled Impedance
--------------------

1.  90 Ohm differential microstrip (Top layer)
    FR4, 180 um, Er = 4.4, tand = 0.025, metal thickness 18 um
    track width 280 um
