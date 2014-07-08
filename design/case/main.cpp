#include <fstream>
#include <ooml/core/IndentWriter.h>

#include "casefactory.h"
//#include "cubieboard.h"
//#include "bb-atxra.h"   // Added by: Anthony W. Rainer <pristine.source@gmail.com>
#include "posts.h"      // Testing POSTS+HOLES for manufacturability
#include "rasdr2.h"

// Small helper function which writes the model to a file in SCAD format.
void write(std::string fileName, const Component & model)
{
    IndentWriter writer;
    writer << model;

    std::ofstream outFile;
    outFile.open(fileName);
    outFile << writer;
}


int main()
{
    // Here, you can change the board for which a case you want to construct.
    // Don't forget to change the #include statement above.
#if 1
    BoardDescription board = rasdr2Board();
    std::string name = "rasdr2"; // File name prefix
#else
    BoardDescription board = postsBoard();
    std::string name = "posts"; // File name prefix
#endif

    // Create a factory to build a case for this board.
    CaseFactory factory(board);

    // customize some parameters (note some of these should be in the board description)
    factory.screwHeadsOnSide = TopSide;
    factory.holesAddRadiusLoose = .1; // posts that have the recessed head (screwHeadsOnSide)
    factory.holesAddRadiusTight = .1; // posts that have the captive nut (not screwHeadsOnSide)
    factory.holesFloors = 12.7;       // NB: related to max z height of top forbidden areas (16.20 for rasdr2)
    factory.walls  = 3.0;
    factory.floors = 2.0;
    factory.cornerRadius = 1;         // NB: complex dependency on walls/floors; dont make this too big or be prepared to fiddle...
    factory.cornerFaces = 20; // should be >= 16.

    // Now we can fine-tune some dimension parameters for the case model. See the class CaseFactory for more options, such as wall thickness, screw hole radius etc.
    factory.smallerBottomHeight = .5; // We want the bottom part to be a bit less high (so the GPIO pin ends will be within the floor; this is just to demonstrate the power of the feature "forbidden areas")
    factory.printLayerHeight = .2;
    factory.printSafeBridgeLayerCount = 3;


    // Generate the models
    Component bottom = factory.constructBottom();
    Component top = factory.constructTop();


    // Write these models to SCAD files. We generate 3(4) files.
    // 1) Only the bottom:
    write(name + "-case-bottom.scad", bottom);
    // 2) Only the top:
    write(name + "-case-top.scad", top);
    // 3) Both parts side by side:
    double distance = 15; // in mm; give enough space to add 'pads' to hold the edges down
    double offset   = factory.outerDimensions().x + distance;
    bool adjacent_in_x = true;
    if( adjacent_in_x ) {
        write(name + "-case.scad", bottom + top.translatedCopy(offset, 0, 0));  // put offset into x or y based on above...
    } else {
        offset = factory.outerDimensions().y + distance; // choose .x or .y
        write(name + "-case.scad", bottom + top.translatedCopy(0, offset, 0));  // put offset into x or y based on above...
    }

    // Write an SCAD file for printing that has 'pads' to keep the rounded edges from curling
    if( factory.cornerRadius > 0.0 ) {
        double cr = factory.cornerRadius;
        double r = (distance - cr/2)/2;
        double x = factory.outerDimensions().x;
        double y = factory.outerDimensions().y;
        double w = factory.walls;
        double h = cr<2?cr/2:0.75;
        Component pad = Cylinder(r, h, 32, false);
        Component pads, part;

        double aa = 2*w-w+cr;               // adjust x
        double bb = ((cr>w)?cr-w:0)+cr/2;   // adjust for cr exceeding w
        double cc = -cr+cr/4;               // adjust y

        // pads based on 'bottom' dimensions
        pads =        pad.translatedCopy(x+r-aa, r-w, 0)    + pad.translatedCopy(x+r-aa, y-2*r, 0);     // EAST face
        pads = pads + pad.translatedCopy(-r-w+bb, r/2, 0)   + pad.translatedCopy(-r-w+bb, y-2*r, 0);    // WEST face
        pads = pads + pad.translatedCopy(r-w, -r-w+cr/2, 0) + pad.translatedCopy(x-2*r, -r-w+cr/2, 0);  // SOUTH face
        pads = pads + pad.translatedCopy(r-w, y+r-w+cc, 0)  + pad.translatedCopy(x-2*r, y+r-w+cc, 0);   // NORTH face

        if( adjacent_in_x ) {
            part = bottom + pads;
            part = part   + top.translatedCopy(offset-cr, 0, 0) + pads.translatedCopy(offset-cr, 0, 0);
        } else {
            part = bottom + pads;
            part = part   + top.translatedCopy(0, offset-cr, 0) + pads.translatedCopy(0, offset-cr, 0);
        }
        write(name + "-case-mfg.scad", part);
    }
    return 0;
}


