#include "port.h"
#include "gpio.h"
#include "led.h"


//Port D
#define LED1_GPIO  		GPIOD
#define LED1_PORT 		PORTD
#define LED1_PIN 	 	(5)
//Port E
#define LED2_GPIO  		GPIOE
#define LED2_PORT 		PORTE
#define LED2_PIN 		(29)


void led_init(void)
{
	gpio_clock_init(SCLK_PORTE|SCLK_PORTD);
	port_mode_config(LED1_PORT,LED1_PIN,MOD_GPIO);
	port_mode_config(LED2_PORT,LED2_PIN,MOD_GPIO);
	gpio_set_dir(LED1_GPIO,LED1_PIN,DIR_OUT);
	gpio_set_dir(LED2_GPIO,LED2_PIN,DIR_OUT);
	//default value
	led1_set_value(OFF);
	led2_set_value(OFF);
}

void led1_set_value(uint8_t val)
{
	gpio_set_pin(LED1_GPIO,LED1_PIN,!val);
}

void led2_set_value(uint8_t val)
{
	gpio_set_pin(LED2_GPIO,LED2_PIN,!val);
}


void led1_toggle_value(void)
{
	gpio_toggle_pin(LED1_GPIO,LED1_PIN);
}

void led2_toggle_value(void)
{
	gpio_toggle_pin(LED2_GPIO,LED2_PIN);
}

void PORTC_PORTD_IRQHandler(void)
{
	//irq handler
  led1_toggle_value();
}