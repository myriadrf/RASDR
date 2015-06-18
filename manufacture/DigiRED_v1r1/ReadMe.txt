QUOTATION PACKAGE --- FOR MANUFACTURE
=====================================

Please quote the following (PCB+Assembly):
A) QTY=100,  Delivery=PROD, Turnkey, first article service requested
B) QTY=250,  Delivery=PROD, Turnkey, first article service requested
C) QTY=1000, Delivery=PROD, Turnkey, first article service requested

Please direct technical questions to:

Bogdan Vacaliuc
bvacaliuc@gmail.com, vacaliucb@ornl.gov
603-591-2458 cell

Please direct financial questions to:
Melinda Lord
Treasurer, Society of Amateur Radio Astronomers
treasurer@radio-astronomy.org, ap_guardian@yahoo.com

For CTS/Valpey components, contact:
Janet Cicero (jcicero@doveonline.com )
Dove Electronic Components
39 Research Way
East Setauket, NY 11733
Freephone: 1 800 232 XTAL 
Telephone: 1 631 689 7733
Fax: 1 631 689 7362
http://www.doveonline.com/


Board Description
-----------------

board designation           : DigiRED v1 RX
board version               : version 1, revision 1	
board type                  : Lead Free
board size                  : 59.0 mm x 62.0 mm
board thickness             : 1.6 mm +/- 10 %
board material              : FR4
number of layers            : 6
Gerber file format          : RS-274-X
Solder Mask                 : black TAIYO, both sides, halogen free.
Silkscreen                  : white epoxy ink, halogen free, both sides.



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


Important Notes
---------------

DRCs must be run on Gerber files before building boards.

All through hole vias may be plated shut.

Electrical test : 100 % netlist.

Boards are to be individually bagged.

Design software used:  KiCad

The BOM contains several NOFIT parts.  These have been carefully identified and do not need to be placed.  The schematic shows R135 and TCXO2 as 'NF'.  The BOM shows TCXO1 as 'NF'.  The BOM is correct.  I did not wish to modify the schematic at this time as there are no changes except for the BOM.


Controlled Impedance
--------------------

1.  90 Ohm differential microstrip (Top layer)
    FR4, 180 um, Er = 4.4, tand = 0.025, metal thickness 18 um
    track width 280 um



Board Stackup
-------------

Solder Paste Front              : DigiRED_v1-F_Paste.gbp
Silk Screen Front               : DigiRED_v1-F_SilkS.gto
Solder Mask Front               : DigiRED_v1-F_Mask.gts


1. Top Layer                    : DigiRED_v1-01-Front_Cu.gtl
2. GND Layer                    : DigiRED_v1-02-GND_Cu.gbr				
3. Inner Layer 1                : DigiRED_v1-03-Signal_1_Cu.gbr
4. Inner Layer 2                : DigiRED_v1-04-Signal_2_Cu.gbr
5. Power Layer                  : DigiRED_v1-05-Power_Cu.gbr
6. Bottom Layer                 : DigiRED_v1-06-Back_Cu.gbl

Solder Mask Back                : DigiRED_v1-B_Mask.gbs
Silk Screen Back                : DigiRED_v1-B_SilkS.gbo
Solder Paste Back               : DigiRED_v1-B_Paste.gbp


Additional Files
----------------

PCB edges                       : DigiRED_v1-Edge_Cuts.gbr
Drill map                       : DigiRED_v1-drl_map.pho
NC Drill file                   : DigiRED_v1.drl
Bill of Materials File          : DigiRED_v1_BOM.xls

Descriptive Layer Stack Up      : DigiRED_v1_PCB_Layer_Stack_Up.pdf

Schematics                      : DigiRED_v1_Schematics_v1r1.pdf
Component Positions Reference   : DigiRED_v1-all_pos.txt


