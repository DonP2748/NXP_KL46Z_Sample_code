#include "port.h"
#include "gpio.h"

void gpio_clock_init(uint32_t sys_clock)
{
	SIM->SCGC5 |= sys_clock;
}

void gpio_set_dir(GPIO_Type* gpio, uint8_t pin, uint8_t dir)
{	
	if(!dir){
		gpio->PDDR &=~(1<<pin);  
	}
	else{
		gpio->PDDR |= (1<<pin); 
	}
}

void gpio_set_pin(GPIO_Type* gpio, uint8_t pin, uint8_t value)
{
	if(value){
		gpio->PDOR |= (1<<pin);
	}
	else{
		gpio->PDOR &=~(1<<pin);
	}
}

uint8_t gpio_get_pin(GPIO_Type* gpio, uint8_t pin)
{
	return (gpio->PDIR&(~(1<<pin))) ? 1 : 0;
}

void gpio_toggle_pin(GPIO_Type* gpio, uint8_t pin)
{
	gpio->PTOR |= (1<<pin);
}



