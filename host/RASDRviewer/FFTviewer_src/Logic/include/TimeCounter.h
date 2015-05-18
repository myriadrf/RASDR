// -----------------------------------------------------------------------------
// FILE: 		TimeCounter.h
// DESCRIPTION:	Header for TimeCounter.cpp
// DATE:		2013-08-27
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef TIME_COUNTER_H
#define TIME_COUNTER_H

#ifndef WIN32
#include "sys/time.h"
#include <unistd.h>

long GetTickCount();
#endif

void milSleep(long miliseconds);

#endif // TIME_COUNTER_H

