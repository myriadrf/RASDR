#ifndef POSTSTEST_H
#define POSTSTEST_H

#include "boarddescription.h"


// Testing POSTS+HOLES for manufacturability
// All metric nut sizes from: http://www.fairburyfastener.com/xdims_metric_nuts.htm

BoardDescription postsBoard()
{
    BoardDescription b;
    float bd = 0.50; // buffer distance to give it some breathing room around the board
    // Board size
    b.size[0] = 34.0 + (bd*2); // x
    b.size[1] = 34.0 + (bd*2);// y
    b.thickness = 1.7 + 0.2;    // z, Add about +.2 to the actual board size

    // Board holes
    b.holes = {
	//x, y
    {  7.0+bd, 27.0+bd},	// top-left
	{ 27.0+bd, 27.0+bd},	// top-right
    {  7.0+bd,  7.0+bd},	// bottom-left
	{ 27.0+bd,  7.0+bd}     // bottom-right
    };
    b.holesRadius = 1.7; // 1.5 = M3, +0.1 to allow screw to move, +0.1 for tolerance

    b.holeNuts = {
	// index, width, thickness, distance (from holeNutsSide), insert_side
    {0, 6.0, 3.5, 4.0, South},   // experiment with width and thickness ranges
	{1, 6.0, 3.5, 5.0, West},
	{2, 6.0, 3.5, 6.0, East},
	{3, 6.0, 3.5, 7.0, North}
    };
    b.holeNutsSide = BottomSide;

    // Define the volume of the bottom
    b.bottomForbiddenAreas = {
	// x, y, sizex, sizey, sizez
    { 11.5+bd, 11.5+bd, 11.0, 11.0, 10.00+bd },
    };
    b.topForbiddenAreas = {
    // x, y, sizex, sizey, sizez
    //{ 0.5+bd, 0.5+bd, 33.0, 33.0, 4.0+bd },
    { 11.5+bd, 11.5+bd, 11.0, 11.0, 7.0+bd },
    };

    // not used for post tests (except the fiducial notch)
    b.topHoles = {
    };
    b.bottomPorts = {
	{
		South, {                    // fiducial notch
			// (x,z),(y,z) pairs
            {18.00+bd, 00.00},
            {16.00+bd, 00.00},
            {16.00+bd,-02.00},
            {18.00+bd,-02.00}
        },
		0.5,
		10.0
	},
    };
    b.topPorts = {
    };
    b.bottomWallSupports = {
    };
    b.topWallSupports = {
    };

    return b;
}


#endif // POSTSTEST_H
