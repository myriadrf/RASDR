// -----------------------------------------------------------------------------
// FILE:        "Packets.h"
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
// FILE: 		Packets.h
// DESCRIPTION:	defines data packets used for buffering
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef PACKETS_H
#define PACKETS_H

#define SPLIT_PACKET_SIZE 10880 //number of I and Q pairs in split packet
#define FFT_PACKET_SIZE 16384   // TODO: coordinate with pnlSpectrum.cpp, Packets.h, TestingModule.h/.cpp, globals.cpp and pnlSpectrum.wxs
#include <iostream>
using namespace std;
/**
    Packet used for transferring data from stream to fft calculation
*/
struct SplitPacket
{
public:
	SplitPacket(unsigned int packetSize) : used(false), size(packetSize)
	{
	    Idata = new float[packetSize];
	    Qdata = new float[packetSize];
	}
	~SplitPacket()
	{
	    delete []Idata;
	    delete []Qdata;
	}

	SplitPacket& operator=(SplitPacket& obj)
	{
	    unsigned int cpSize = 0;
	    if(size < obj.size)
            cpSize = size;
        else
            cpSize = obj.size;
		memcpy(this->Idata, obj.Idata, cpSize*sizeof(float));
		memcpy(this->Qdata, obj.Qdata, cpSize*sizeof(float));
		this->used = obj.used;
		this->timestamp = obj.timestamp;
		obj.used = true;
		return *this;
	}

	bool used;
	const unsigned int size;
	float *Idata;
	float *Qdata;
	double timestamp;           // UTC seconds since 1 January 1970 (Unix EPOCH)
};

/**
    Packet used for transferring FFT calculation results to graphs
*/
struct FFTPacket
{
public:
	FFTPacket(unsigned int packetSize) : used(false), size(packetSize)
	{
	    isamples = new float[packetSize];
	    qsamples = new float[packetSize];
	    amplitudes = new float[packetSize];
	}

	~FFTPacket()
	{
        delete isamples;
        delete qsamples;
        delete amplitudes;
	}

	FFTPacket& operator=(FFTPacket& obj)
	{
	    unsigned int cpSize = 0;
	    if(size < obj.size)
            cpSize = size;
        else
            cpSize = obj.size;
		memcpy(this->isamples, obj.isamples, sizeof(float)*cpSize);
		memcpy(this->qsamples, obj.qsamples, sizeof(float)*cpSize);
		memcpy(this->amplitudes, obj.amplitudes, sizeof(float)*cpSize);
		this->used = obj.used;
		this->timestamp = obj.timestamp;
		obj.used = true;
		return *this;
	}

	bool used;
	const unsigned int size;
	float *isamples;
	float *qsamples;
	float *amplitudes;
	double timestamp;           // UTC seconds since 1 January 1970 (Unix EPOCH)
};

/**
    Packet used for transferring Accumulated FFT calculation results to graphs
*/
struct FFTAvgPacket
{
public:
	FFTAvgPacket(unsigned int packetSize, float c=0.0, float o=0.0)
        : used(false), size(packetSize), fcenter(c), foffset(o), timestamp(0.0)
	{
	    offset_frequencies = new float[packetSize];
	    amplitudes = new float[packetSize];
	}

	~FFTAvgPacket()
	{
        delete offset_frequencies;
        delete amplitudes;
	}

	FFTAvgPacket& operator=(FFTAvgPacket& obj)
	{
	    unsigned int cpSize = 0;
	    if(size < obj.size)
            cpSize = size;
        else
            cpSize = obj.size;
		memcpy(this->offset_frequencies, obj.offset_frequencies, sizeof(float)*cpSize);
		memcpy(this->amplitudes, obj.amplitudes, sizeof(float)*cpSize);
		this->used = obj.used;
		this->fcenter = obj.fcenter;
		this->foffset = obj.foffset;
		this->timestamp = obj.timestamp;
		obj.used = true;
		return *this;
	}

	bool used;
	const unsigned int size;
	float *offset_frequencies;  // In MHz (FIXME: normalize to GHz)
	float *amplitudes;          // in dB
	float fcenter;              // In GHz
	float foffset;              // In GHz
	double timestamp;           // UTC seconds since 1 January 1970 (Unix EPOCH)
};

#endif
