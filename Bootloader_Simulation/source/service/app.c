
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "adc.h"
#include "led.h"
#include "button.h"
#include "uart.h"
#include "pit.h"
#include "sysclock.h"
#include "flash.h"
#include "debug.h"
#include "button.h"
#include "srec_parsing.h"
#include "service.h"
#include "img_manager.h"
#include "app.h"


static void app_firmware_run(void);

extern uint32_t SystemCoreClock;




void app_init(void)
{
	led_init();
	button_init();
	debug_log_init();
	debug_log_printf("Hello World %d\r\n",SystemCoreClock);


	uart_register_data_recv_cb(data_receive_callback);
	process_register_firmware_data_done_cb(app_firmware_run);
}


void app_main_process(void)
{
	if(button1_read_value()){
		debug_log_printf("ENTER BOOT MODE\r\n");
		process_firmware_set_status(PROC_STATE_DOWNLOADING);
	}
	else{
		debug_log_printf("ENTER APPLICATION MODE\r\n");
		uint8_t status = image_check_firmware_update();

		debug_log_printf("STATUS %d\r\n",status);
		switch(status){
			case IMG_NONE:
				process_firmware_set_status(PROC_STATE_DONE);	//jump app
				break;
			case IMG_UPGRADE:
				process_firmware_set_status(PROC_STATE_MOVING);
				break;
			case IMG_UPDATE:
				process_firmware_set_status(PROC_STATE_DOWNLOADING);
				break;
			default:
				break;
		}
	}
	process_firmware_data();
}



typedef void(*reset_hanlder)(void);

static void app_firmware_run(void)
{
	// disable all interrupts
	__disable_irq();
	// Set the vector table offset register to the application start address
	SCB->VTOR = FW_RUNNING;
	// Set the stack pointer (CMSIS function)
	__set_MSP(*(volatile uint32_t*)FW_RUNNING);
	// Set the program counter to the application's reset handler
	reset_hanlder app_run = (reset_hanlder)(*((volatile uint32_t*)(FW_RUNNING + 4)));
	debug_log_printf("Jump to Application!\r\n");
	app_run();
}




