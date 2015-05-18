// -----------------------------------------------------------------------------
// FILE: 		TimeCounter.cpp
// DESCRIPTION:	Functions used for counting time in non windows platforms
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef TIME_COUNTER_H
#define TIME_COUNTER_H

#ifdef WIN32


#include <windows.h>
#else
#include "TimeCounter.h"
#include "sys/time.h"
#include <unistd.h>

long GetTickCount()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return time_in_mill;
}
#endif

void milSleep(long miliseconds)
{
#ifdef WIN32
    Sleep(miliseconds);
#else
    usleep(miliseconds*1000);
#endif // WIN32
}


#endif // TIME_COUNTER_H

