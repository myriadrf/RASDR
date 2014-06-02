# RASDR Case Design Tools

This sub-project generates a case model and manufacturing files for the RASDR project.  RASDR is an Open Hardware project undertaken by members of the Society of Amateur Radio Astronomers (SARA) to develop a low cost, high performance software defined receiver for use by SARA members.  The goal of RASDR is to provide a low cost hardware that enables radio astronomers and educational institutions to perform high quality astronomical measurements.

At the core of this capability is the Object Oriented Mechanics Library ([OOML](http://iearobotics.com/oomlwiki/doku.php)), which is used by the [OOML Case Factory](http://www.thingiverse.com/thing:70838) and custom code to produce the CAD files that are used to generate the STereoLithograpy (STL) files needed to produce a design.

![RASDR](https://github.com/myriadrf/RASDR/raw/master/design/case/rasdr2-case-mfg.png )
*RASDR2 case design generated using the OOML Case Factory with manufacturing aids*

## Setup of the Tools ##

You will need to setup the OOML and OpenSCAD on your machine.  Here are links:
- [OOML](http://iearobotics.com/oomlwiki/doku.php?id=download:start)
- [OpenSCAD](http://www.openscad.org/)

Forgive me if at this point, I don't have a step-by-step for all platforms.  The above links do a good job.  If you have problems, please send me an email and I'll try to help you out.

## Regenerating the Design ##

Once you have done that, just edit the Makefile to help it find the install location of the library (not needed if you installed into /usr/include/ooml)

Then, simply issue the following commands:

- $ make
- $ ./casefactory

This will produce (at least) the following files:

rasdr-case-bottom.scad
rasdr-case-top.scad
rasdr-case-mfg.scad

The first two are the individual top/bottom parts of the case.  The third is a "manufacturing" version of the case that contains *both* top and bottom parts, as well as 'rafts' to help keep the surfaces from curling.

## Viewing the Design ##

At this point, start OpenSCAD and open one of the above .scad files.  The tool will construct the rendering and you can use the tool to inspect the model from all perspectives, rotate, pan, zoom, etc.

Each time you run the above two commands, you will update the .scad files and OpenSCAD will refresh its rendering.  When you are ready to print the case, you *export* an STL file and send that to your slicer and *happy printing*.

## Licensing ##
These software source files are licensed using the *GNU General Public license version 3*.  This is because the OOML Case Factory is released under this license model.
For specific information see the LICENSE file.