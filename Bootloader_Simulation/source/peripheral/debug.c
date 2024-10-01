#include <stdio.h>
#include <stdarg.h>
#include "port.h"
#include "gpio.h"
#include "uart.h"
#include "debug.h"
#include "led.h"




void debug_log_init(void)
{
	uart_init();
}



void debug_log_printf(const char* format,...)
{
	char data[256] = {0};

	va_list args;
	va_start(args, format);
	vsprintf(data,format,args);  //vsprintf is sprintf for va list
	va_end(args);

	uint8_t id = 0;
	while(data[id]){
		uart_write_byte(data[id]);
		id++;
	}
}










