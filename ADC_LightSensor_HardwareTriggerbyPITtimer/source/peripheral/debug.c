#include "port.h"
#include "gpio.h"
#include "uart.h"
#include "debug.h"






void debug_log_init(void)
{
	uart_init();
}



void debug_log_printf(char* data)
{
	while(*data){
		uart_write_byte(*data++);
	}
}












