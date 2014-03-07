Board Description
-----------------

board designation           : MYRIAD RF Via Off Pad 
board type                  : Lead Free
board size                  : 49.0 mm x 47.0 mm
board thickness             : 1.6 mm +/- 10 %
board material              : FR4
number of layers            : 6
 

Top layer copper foil thickness: 17.5 um
Dielectric thickness between Top layer and 2nd layer: 173 um (6.8 mils)
Dielectric between Top layer and 2nd layer relative permittivity (Er): 4.2


minimum finished hole size  :  200 um
minimum spacing             :  100 um
minimum track width         :  100 um

Gerber file format          : RS-274-X 

drill diameters             : finished hole

plating finish (both sides) : immersion gold
                              0.08-0.20 um of gold over
                              2.50-5.00 um of nickel

edge connector plating      : 1.27 um hard gold over 1.27 um nickel


Important Notes
---------------

DRCs must be run on Gerber files before building boards.

All through hole vias may be plated shut.

Solder mask : black TAIYO, both sides, halogen free.

Silkscreen : white epoxy ink, halogen free, both sides.

Electrical test : 100 % netlist.

Boards are to be individually bagged.

Basic grid increment is 5 um.

Design software used:  KiCad



Controlled Impedance
--------------------

  * 50 Ohm coated single ended microstrip (Top layer)
    FR4, 6.8 mil, Er = 4.2, tand = 0.025, metal thickness 17.5 um
    track width 310 um


Board Stackup
----------------

1. Solder Paste Front		: MYRIAD_RF-SoldP_Front.gtp
2. Silk Screen Front		: MYRIAD_RF-SilkS_Front.gto
3. SolderMask Front		: MYRIAD_RF-Mask_Front.gts

4. Front Layer			: MYRIAD_RF-Front.gtl
5. Inner GND Layer		: MYRIAD_RF-Inner_GND.gbr																	
6. Inner Analog Signal Layer	: MYRIAD_RF-Inner_Analog_Signal.gbr
7. Inner Power Layer		: MYRIAD_RF-Inner_Power.gbr
8. Inner Digital Signal Layer	: MYRIAD_RF-Inner_Digital_Signal.gbr
9. Back Layer			: MYRIAD_RF-Back.gbl

10. SolderMask Back		: MYRIAD_RF-Mask_Back.gbs
11. Silk Screen Back		: MYRIAD_RF-SilkS_Back.gbo
12. Solder Paste Back      	: MYRIAD_RF-SoldP_Back.gbp



--------------------------------------------------
13. Drill map            	: MYRIAD_RF-drl.pho
14. NC Drill file	 	: MYRIAD_RF.drl

15. PCB edges           	: MYRIAD_RF-PCB_Edges.gbr



Reports folder
--------------
                  
MYRIAD_RF_erc.txt
MYRIAD_RF_drc.txt


