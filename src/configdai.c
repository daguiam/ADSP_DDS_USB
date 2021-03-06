#include <sru.h>
#include <def21369.h>

// This function will setup the SRU Registers
void InitSRU(void)
{
	// Enable pull-up resistors on unused DAI pins
	* (volatile int *)DAI_PIN_PULLUP = 0xfffff;

	// Enable pull-up resistors on unused DPI pins
	* (volatile int *)DPI_PIN_PULLUP = 0x3fff;

	//Generating Code for connecting : TIMER0 to MISCB0
	SRU (TIMER0_O, MISCB0_I); 


}
