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
