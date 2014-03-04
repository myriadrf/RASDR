/**
Copyright 2013 Lime Microsystems

-- ----------------------------------------------------------------------------	
-- FILE:	mipi_rffe.h
-- DESCRIPTION:	 
-- DATE:	2013.11.21
-- AUTHOR(s):	Lime Microsystems
-- REVISION: v0r2
-- ----------------------------------------------------------------------------	
*/

#ifndef MIPI_RFFE_H
#define MIPI_RFFE_H

// include project-dependent settings
#include "mipi_rffe_conf.h"

void MIPI_RFFE_Init (void);
void MIPI_RFFE_Write (unsigned char USID, unsigned char reg_addr, unsigned char data);
unsigned char MIPI_RFFE_Read (unsigned char USID, unsigned char reg_addr);

#endif

