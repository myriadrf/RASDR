
Board Description
-----------------

board designation           : MYRIAD RF Via Off Pad 
board version		    : version 1, revision 3, eco 1
board type                  : Lead Free
board size                  : 48.0 mm x 46.0 mm
board thickness             : 1.6 mm +/- 10 %
board material              : FR4
number of layers            : 6
Gerber file format          : RS-274-X 
Solder Mask                 : black TAIYO, both sides, halogen free.
Silkscreen                  : white epoxy ink, halogen free, both sides.
 

Top layer copper foil thickness: 17.5 um
Dielectric thickness between Top layer and 2nd layer: 173 um (6.8 mils)
Dielectric between Top layer and 2nd layer relative permittivity (Er): 4.2


minimum finished hole size  :  200 um
minimum spacing             :  100 um
minimum track width         :  100 um


drill diameters             : finished hole

plating finish (both sides) : electroless nickel immersion gold (ENIG)
                              0.08-0.13 um of gold over
                              3.00-6.00 um of nickel
                              per IPC-4552 Amendment 1

Important Notes
---------------

DRCs must be run on Gerber files before building boards.

All through hole vias may be plated shut.

Electrical test : 100 % netlist.

Boards are to be individually bagged.

Basic grid increment is 5 um.

Design software used:  KiCad

The BOM contains several NOFIT parts.  These have been carefully identified and do not need to be placed.  

The BOM contains an EMI shield from Laird Technologies (BMI-S-204-F) that comes in two parts.  The part that is soldered onto the PCB should be fitted, but the upper part does not need to be attached, and may be provided in a parts bag separately.  Both parts should be obtained when purchasing parts.


Controlled Impedance
--------------------

  * 50 Ohm coated single ended microstrip (Top layer)
    FR4, 6.8 mil, Er = 4.2, tand = 0.025, metal thickness 17.5 um
    track width 310 um


Board Stackup
----------------

Solder Paste Front              : MYRIAD_RF-F_Paste.gtp
Silk Screen Front               : MYRIAD_RF-F_SilkS.gto
SolderMask Front                : MYRIAD_RF-F_Mask.gts

1. Top Layer                    : MYRIAD_RF-01-Front.gtl
2. Inner GND Layer              : MYRIAD_RF-02-Inner_GND.gbr

3. Inner Layer 1                : MYRIAD_RF-03-Inner_Analog_Signal.gbr
4. Inner Power Layer            : MYRIAD_RF-04-Inner_Power.gbr
5. Inner Layer 2                : MYRIAD_RF-05-Inner_Digital_Signal.gbr
6. Bottom Layer                 : MYRIAD_RF-06-Back.gbl

SolderMask Back                 : MYRIAD_RF-B_Mask.gbs
Silk Screen Back                : MYRIAD_RF-B_SilkS.gbo
Solder Paste Back               : MYRIAD_RF-B_Paste.gbp


Additional Files
----------------
PCB edges                       : MYRIAD_RF-Edge_Cuts.gbr
Drawings                        : MYRIAD_RF-Dwgs_User.gbr
Drill map                       : MYRIAD_RF-drl_map.pho
NC Drill file                   : MYRIAD_RF.drl
Bill of Materials File          : MYRIAD_RF_BOM.xls

Descriptive Layer Stack Up      : MYRIAD_RF_PCB_Layer_Stack_Up.pdf

Schematics                      : MYRIAD_RF_Schematics_v1r2.pdf

Component Positions Reference   : MYRIAD_RF-all_pos.txt

