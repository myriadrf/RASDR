Board Description
-----------------

board designation           : Digital Interface v1.0
board type                  : Lead Free
board size                  : 100.0 mm x 80.0 mm
board thickness             : 1.6 mm +/- 10 %
board material              : FR4
number of layers            : 4
Gerber file format          : RS-274-X

Top layer copper foil thickness	: 18 um
Dielectric thickness between Top layer and 2nd layer: 180 um
Dielectric between Top layer and 2nd layer relative permittivity (Er): 4.4



Board Stackup
-------------

SMD paste Top		: DigitalInterface_v1.0-SoldP_Front.GTP
Silk Top		: DigitalInterface_v1.0-SilkS_Front.GTO
SolderMask Top		: DigitalInterface_v1.0-Mask_Front.GTS

Top Layer		: DigitalInterface_v1.0-Front.GTL															
Inner Layer 1		: DigitalInterface_v1.0-Inner1.GBR
Inner Layer 2		: DigitalInterface_v1.0-Inner2.GBR
Bottom Layer		: DigitalInterface_v1.0-Back.GBL

SolderMask Bottom	: DigitalInterface_v1.0-Mask_Back.GBS
SMD paste Bottom	: DigitalInterface_v1.0-SoldP_Back.GBP

----------------

Drill map            	: DigitalInterface_v1.0-drl.PHO
NC Drill file		: DigitalInterface_v1.0.DRL

PCB edges               : DigitalInterface_v1.0-PCB_Edges.GBR


Controlled Impedance
--------------------

1.  50 Ohm single ended microstrip (Top layer)
    FR4, 180 um, Er = 4.4, tand = 0.025, metal thickness 18 um
    track width 310 um.

2.  90 Ohm differential microstrip (Top layer)
    FR4, 180 um, Er = 4.4, tand = 0.025, metal thickness 18 um
    track width 280 um