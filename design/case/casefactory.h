#ifndef CASEFACTORY_H
#define CASEFACTORY_H

#include <ooml/components.h>
#include <ooml/core/Hull.h>
#include <ooml/core/Intersection.h>
#include "geom.h"
#include "boarddescription.h"


// Small epsilon value for building differences where positive and negative parts have (partly) common faces.
// Should be small (<= .1mm) but not too small (>= .01mm).
// It does NOT affect the result unless set way too large (I suggest to not set it greater than 1mm).
static const double eps = .1;



struct CaseFactory
{
// Moved to boarddescription.h by: Bogdan Vacaliuc <bvacaliuc@gmail.com>
//    enum Side {
//        BottomSide,
//        TopSide
//    };


    //! Constructor. You have to tell the factory for which board you want to
    //! generate a case. (Note: This instance will be copied. Any changes made
    //! outside are invisible to this class.)
    CaseFactory(BoardDescription board);


    //! Generate the bottom part of the case.
    Component constructBottom();

    //! Generate the top part of the case.
    Component constructTop();

    //! Calculate the total outer dimensions of the assembled case.
    Vec outerDimensions();




    // CASE DIMENSION PARAMETERS - CHANGE THEM TO YOUR NEEDS BEFORE GENERATING ANY COMPONENTS.

    // case thickness
    double walls = 3.0;
    double floors = 2.0;

    // case holes at same position than the board holes, here for M3 screws
    double holesAddRadiusLoose = .4; // The screw needs to slide through the hole (but not its head)
    double holesAddRadiusTight = .0; // The screw needs to hold in the hole
    double holesSize = 5.8; // size of the cuboid-shaped hole on the bottom case where the screw head fits in (>= screw head diameter)
    double holesWalls = 1.3; // ...and their wall thickness
    double holesFloors = 4.0; // ...and their floor thickness

    // space between board and case in xy dimensions (should be somewhere between 0 and 1)
    double space = .3;

    // these numbers will be subtracted from the automatically calculated case's inner height (which itself will be the maximum z value of all components on the board)
    double smallerBottomHeight = 0.0;
    double smallerTopHeight = 0.0;

    // rounded corners (only on the outside)
    double cornerRadius = 2;
    double cornerFaces = 20; // should be >= 16.


    // what to build on which side (the contrary part is on the other side)
    Side screwHeadsOnSide = BottomSide;
    Side outerExtensionOnSide = BottomSide;



    // 3D PRINTING PARAMETERS - CHANGE THEM TO YOUR NEEDS BEFORE GENERATING ANY COMPONENTS.

    // 3D printing layer height.
    // Currently only required to model "safe bridges"; see below.
    double printLayerHeight = .2;

    // Number of layers for "safe bridges" to be printed.
    // Safe brides won't have holes in them, even if the final object should have.
    // This is to simplify printing bridges, as bridges with holes are almost impossible to print.
    // If your printer has problems printing bridges, set this value to 2 or even 3.
    double printSafeBridgeLayerCount = 1;





private:
    enum {
        ExtensionInside = 0,
        ExtensionOutside = 1
    };

    BoardDescription board;

    // Calculated in the constructor after the board is known
    double boardBottomInnerHeight;
    double boardTopInnerHeight;


    // Inner height of the case (measured from board's surface to inner surface of the case)
    inline double bottomInnerHeight() { return boardBottomInnerHeight - smallerBottomHeight; }
    inline double topInnerHeight() { return boardTopInnerHeight - smallerTopHeight; }

    // Outer height of the case (measured from board's surface to outer surface of the case)
    inline double bottomHeight() { return bottomInnerHeight() + floors; }
    inline double topHeight() { return topInnerHeight() + floors; }

    // Total height of the case. The extension has to be added ONCE to the total height (as it is half on the bottom, half on the top part)
    inline double extensionHeight() { return board.thickness; }
    inline double totalHeight() { return bottomHeight() + topHeight() + extensionHeight(); }

    // Additional size on each border in X and Y directions to the board's dimensions. (Case size = board size + 2 * outset)
    inline double outset() { return walls + space; }

    // Returns the case's size (see outset()).
    inline double outerWidth() { return board.size[0] + 2 * outset(); }
    inline double outerDepth() { return board.size[1] + 2 * outset(); }

    // Puts all things together required to build one part of the case (top / bottom)
    Component constructPart(Side whichSide);

    // Wall extension: 0 = on the inner half of the wall, 1 = on the outer half of the wall
    Component constructBase(double innerHeight, int extensionDirection);

    Component addWallSupport(const Component & component, double supportHeight, const WallSupportDescription & wallSupport);
    Component addHoleForScrew(const Component & component, double partOuterHeight, const Point & pos, double radius, bool screwHead);
    Component addHoleForPort(const Component & component, double partOuterHeight, const PortDescription & port);


    // Added by: Anthony W. Rainer <pristine.source@gmail.com>
    Component addCavityForNut(const Component & component, double partOuterHeight, const Point & pos, HoleNutDescription holeNut );
};


#endif // CASEFACTORY_H
