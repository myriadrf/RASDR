#ifndef RASDR2BOARD_H
#define RASDR2BOARD_H

#include "boarddescription.h"


// The RASDR2 Board Case (http://rasdr.org)
// By: Bogdan Vacaliuc <bvacaliuc@gmail.com>
// Based on Anthony W. Rainer's BB-ATXRA board included with OOML-CASE-FACTORY
// All measured as if the board were turned so the 'DigiRED' label is in the bottom
//   left corner along the +Y axis.  The two SMA connectors are at the top and the
//   two USB connectors are along the right.
// All metric nut sizes from: http://www.fairburyfastener.com/xdims_metric_nuts.htm

BoardDescription rasdr2Board()
{
    BoardDescription b;
    float bd = 0.50; // buffer distance to give it some breathing room around the board
    // Board size
    b.size[0] = 59.00 + (bd*2); // x
    b.size[1] = 112.22 + (bd*2); // y
    b.thickness = 1.7 + 0.2;    // z, Add about +.2 to the actual board size

    // Board holes
    b.holes = {
	//x, y
    { 16.58+bd, 51.90+bd},	// top-left
	{ 54.58+bd, 51.90+bd},	// top-right
    { 16.58+bd, 11.90+bd},	// bottom-left
	{ 54.58+bd, 11.90+bd}	// bottom-right
    };
    b.holesRadius = 1.7; // 1.5 = M3, +0.1 to allow screw to move, +0.1 for tolerance

    b.holeNuts = {
	// index, width, thickness, distance (from holeNutsSide), insert_side
    {0, 6.0, 3.5, 5.0, East},   // see posts.h for a test box to tune these parameters
	{1, 6.0, 3.5, 5.0, West},
	{2, 6.0, 3.5, 5.0, East},
	{3, 6.0, 3.5, 5.0, West}
    };
    b.holeNutsSide = BottomSide;

    // Each area marks a cuboid in which no stuff should be placed (i.e., where some parts are on the board)
    b.bottomForbiddenAreas = {
	// x, y, sizex, sizey, sizez
    { 22.15+bd, 55.07+bd, 25.00, 13.15, 05.00+bd },   // 20-pin header
    { 00.00+bd, 28.50+bd, 05.00, 06.40, 00.80+bd },   // X7
    { 12.60+bd, 16.20+bd, 46.20, 31.40, 10.00+bd },   // MyriadRF board mounted on 10mm
    };
    b.topForbiddenAreas = {
    // x, y, sizex, sizey, sizez
    { 12.20+bd, 07.60+bd, 46.60, 48.60, 06.70+bd },    // MyriadRF board mounted on 5mm
    { 20.20+bd, 15.60+bd, 30.60, 32.60, 16.20+bd },    // MyriadRF RF shield and heatsink
    { 00.00+bd, 28.50+bd, 05.00, 06.40, 00.80+bd },    // X7
    };

    // ???
    b.topHoles = {
    };

    // The board ports (connections).
    b.bottomPorts = {
#if 1
        // switch port for PROG/RUN (tbd, RS#275-0006)
        {
            North, {
                // (x,z),(y,z) pairs
                {16.00+bd, 01.70},
                {12.80+bd, 01.70},
                {12.80+bd, 02.90},
                {16.00+bd, 02.90}
            },
            0.5,
            10.0
        },
#endif
        // X7
        {
            West, {
                // (x,z),(y,z) pairs
                {31.70+bd, 00.00},
                {25.30+bd, 00.00},
                {25.30+bd,-03.20},
                {31.70+bd,-03.20}
            },
            0.5,
            10.0
        },
    };
    b.topPorts = {
        // D3-D8 visibility window
        {
            Flat, {
                // x, y
                { 3.2+bd, 6.0+bd }
            },
            4.3,
            6.0
        },
        // X4
        {
            South, {
                // (x,z),(y,z) pairs
                {29.41+bd,-02.00},  // -2 to cut thru the lip of the top half
                {16.00+bd,-02.00},
                {16.00+bd, 03.00},
                {29.41+bd, 03.00}
            },
            0.5,
            10.0
        },
        // X5
        {
            South, {
                // (x,z),(y,z) pairs
                {50.00+bd,-02.00},  // -2 to cut thru the lip of the top half
                {37.00+bd,-02.00},
                {37.00+bd, 03.00},
                {50.00+bd, 03.00}
            },
            0.5,
            10.0
        },
        // X7
        {
            West, {
                // (x,z),(y,z) pairs
                {31.70+bd,-02.00},  // -2 to cut thru the lip of the top half
                {25.30+bd,-02.00},
                {25.30+bd, 03.20},
                {31.70+bd, 03.20}
            },
            0.5,
            10.0
        },
        // TXTEST (on MyriadRF)
        {
            East, {
                // (x,z),(y,z) pairs
                {22.82+bd,-02.00},  // -2 to cut thru the lip of the top half
                {16.42+bd,-02.00},
                {16.42+bd, 09.90},  // 3.20+5+1.7 because it is on the MyriadRF
                {22.82+bd, 09.90}
            },
            0.5,
            10.0
        },
        // RXTEST (on MyriadRF)
        {
            East, {
                // (x,z),(y,z) pairs
                {47.22+bd,-02.00},  // -2 to cut thru the lip of the top half
                {40.82+bd,-02.00},
                {40.82+bd, 09.90},  // 3.20+5+1.7 because it is on the MyriadRF
                {47.22+bd, 09.90}
            },
            0.5,
            10.0
        },
    };

    b.bottomWallSupports = {
    };
    b.topWallSupports = {
    };

    return b;
}


#endif // RASDR2BOARD_H
