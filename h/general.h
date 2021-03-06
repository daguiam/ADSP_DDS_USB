/***************************************************************
	Filename:	general.h (general project includes and defines)
	Author:		Diogo Aguiam - diogo.aguiam@ist.utl.pt
	Date:		April 2013
	Version:	v1.0
	Purpose:	General and global definitions and project 
		specific includes to be shared by all source files.
			
	Usage:
	
	Extra:		
		
***************************************************************/

#ifndef _GENERAL_H_
#define _GENERAL_H_



#ifdef __ADSP21371__
	#include <Cdef21371.h>
	#include <def21371.h>
#elif __ADSP21375__
	#include <Cdef21375.h>
	#include <def21375.h>
#elif __ADSP21369__
	#include <Cdef21369.h>		// This board!
	#include <def21369.h>
#endif

#include <stdio.h>
#include <stdbool.h>

#include <sysreg.h>
#include <signal.h>
#include <sru.h>
//#include <services/int/adi_int.h>

#include "configADC.h"

#include "configDDS.h"
#include "configUSB.h"

#define TRUE 	1
#define FALSE	0


#endif

