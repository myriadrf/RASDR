// -----------------------------------------------------------------------------
// FILE:        "CallbackCodes.h"
// DESCRIPTION: "Header File"
// DATE:        "05/09/2015 06:44 AM "
// AUTHOR(s):   Lime Microsystems, Paul L. Oxley
// Copyright:   Society of Amateur Radio Astronomers (2014-2015)
//
// Based on original work from Zydrunas Tamosevicius (Lime Microsystems, Ltd.)
// and distributed under the Apache License 2.0 at:
// https://github.com/myriadrf/myriadrf-utils
//
// The RASDRviewer version has been specifically modified for Radio Astronomy
// by Paul L. Oxley for the Society of Amateur Radio Astronomers.  These
// modifications are provided to you under the Gnu Public License version 2.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// REVISIONS:   as appropriate
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// FILE: 		CallbackCodes.h
// DESCRIPTION:	Callback codes for updating GUI
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef CALLBACK_CODES_H
#define CALLBACK_CODES_H

enum eUpdateCallbackCodes
{
	NOTHING = 0,
	SHOW_POPUP_MESSAGE, // param c-string
	UPDATE_INTERFACE_DATA, // param[0] - address of module to update
	SHOW_LOG_MESSAGE, // param c-string
	READ_ALL_LOG_MESSAGES,
	UPDATE_VER_REV_MASK,
	CHIP_CONNECTED,
	CHIP_DISCONNECTED,
	UPDATE_PROGRESS_BAR,
	SET_PROGRESS_BAR_STEPS, // param[0] - number of steps
	UPDATE_TEST_STATE, // param[0] - test index, param[1] - test state
	SHOW_TESTING_LOG_MESSAGE, // param c-string
	UPDATE_FFT_GRAPHS
};

#endif
