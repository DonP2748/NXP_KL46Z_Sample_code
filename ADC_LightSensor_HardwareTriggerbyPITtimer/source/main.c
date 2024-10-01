




#include <stdio.h>


#include "board.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
#include "MKL46Z4.h"

#include "adc.h"
#include "led.h"
#include "button.h"
#include "uart.h"
#include "pit.h"

#include "debug.h"


static void notify(void)
{
	uint32_t adc = adc_read(SC1_TYPE_A,ADC_CHANNEL);
	uint8_t buff[50] = {0};
	//itoa(adc,(char*)buff,10);
	sprintf((char*)buff,"ADC VALUE: %i/n",adc);
	debug_log_printf((char*)buff);
}


void main()
{
	led_init();
	debug_log_init();
	debug_log_printf("Hello World");
	adc_init(notify);
	pit_init((void*)0);
	while(1);
}




