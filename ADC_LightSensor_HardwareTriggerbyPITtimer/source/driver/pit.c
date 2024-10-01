#include <stddef.h>
#include "pit.h"

#define PIT_INTERRUPT_PERIOD  	(500*(4000000/1000)) 	// 4MHz ~ 1s, 0.5s timeout
#define PIT_TIMER_CHANNEL  		(0) 					// Example uses channel 0


static void (*__callback)(void) = NULL;



// Function to initialize the PIT
void pit_init(void (*callback)(void)) 
{
	// Enable clock for PIT
	SIM->SCGC6 |= SIM_SCGC6_PIT(1);
	// Enable module, freeze timers in debug mode
	PIT->MCR = (PIT->MCR & ~PIT_MCR_MDIS_MASK)|PIT_MCR_FRZ(1);
	// Initialize PIT0 to count down from load_value
	PIT->CHANNEL[PIT_TIMER_CHANNEL].LDVAL = PIT_INTERRUPT_PERIOD;
	// Enable interrupt and timer
	PIT->CHANNEL[PIT_TIMER_CHANNEL].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	// Enable IRQ on the NVIC
	NVIC_EnableIRQ(PIT_IRQn);
	// register callback
	__callback = callback;

}

// PIT0 ISR
void PIT_IRQHandler(void) 
{
	// Clear interrupt flag
	PIT->CHANNEL[PIT_TIMER_CHANNEL].TFLG = PIT_TFLG_TIF_MASK;
	// code to execute when the timer expires
	if(__callback){
		__callback();
	}
}






