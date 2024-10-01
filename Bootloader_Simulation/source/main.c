




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
#include "flash.h"
#include "debug.h"
#include "button.h"
#include "sysclock.h"
#include "app.h"









void main()
{
	system_clock_init();
	app_init();
	app_main_process();
	while(1);
}




