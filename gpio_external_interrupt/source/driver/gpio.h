

#include "MKL46Z4.h"

//DIR
#define DIR_IN  	0
#define DIR_OUT  	1 
//PCR
#define SCLK_PORTE 	(1<<13)
#define SCLK_PORTD 	(1<<12) 	 
#define SCLK_PORTC 	(1<<11)


void gpio_clock_init(uint32_t sys_clock);
void gpio_set_dir(GPIO_Type* gpio, uint8_t pin, uint8_t dir);

void gpio_set_pin(GPIO_Type* gpio, uint8_t pin, uint8_t value);
void gpio_toggle_pin(GPIO_Type* gpio, uint8_t pin);
uint8_t gpio_get_pin(GPIO_Type* gpio, uint8_t pin);
