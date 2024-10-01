#include <stddef.h>
#include "sysclock.h"



void system_clock_init(void)
{
	// Enable the external crystal oscillator
	MCG->C2 = MCG_C2_RANGE0(1) | MCG_C2_EREFS0_MASK;
	// Select the external reference clock
	MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);
	// Wait for the oscillator to initialize
	while (!(MCG->S & MCG_S_OSCINIT0_MASK));
	// Wait for the reference clock status bit to update
	while (MCG->S & MCG_S_IREFST_MASK);
	// Wait for the clock status bits to update
	while ((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(2));
	// Configure the PLL
	MCG->C5 = MCG_C5_PRDIV0(3); // Divide by 4
	MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); // Multiply by 24
	// Wait for the PLL to lock
	while (!(MCG->S & MCG_S_PLLST_MASK));
	while (!(MCG->S & MCG_S_LOCK0_MASK));
	// Select the PLL as the clock source
	MCG->C1 &= ~MCG_C1_CLKS_MASK;
	// Wait for the clock status bits to update
	while ((MCG->S & MCG_S_CLKST_MASK) != MCG_S_CLKST(3));
	// Update the SystemCoreClock variable
	SystemCoreClockUpdate();
}





