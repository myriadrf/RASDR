/**
Copyright 2013 Lime Microsystems

-- ----------------------------------------------------------------------------	
-- FILE:	mipi_rffe_conf.h
-- DESCRIPTION:	MIPI interface ports and pins configuration 
-- DATE:	2013.11.21
-- AUTHOR(s):	Lime Microsystems
-- REVISION: v0r2
-- ----------------------------------------------------------------------------	
*/

#ifndef MIPI_RFFE_CONF_H
#define MIPI_RFFE_CONF_H

// SCLK line port
#define SCLK_PORT	PORTC	// MIPI RFFE SCLK port
#define SCLK_DDR	DDRC	// MIPI RFFE SCLK port direction

// SDATA line port
#define SDATA_PORT	PORTC	// MIPI RFFE SDATA port
#define SDATA_DDR	DDRC	// MIPI RFFE SDATA direction
#define SDATA_PIN	PINC	// MIPI RFFE SDATA port input

// pin assignments
#define SCLK		PC2		// MIPI RFFE SCLK pin
#define SDATA		PC5		// MIPI RFFE SDATA data pin

#endif
