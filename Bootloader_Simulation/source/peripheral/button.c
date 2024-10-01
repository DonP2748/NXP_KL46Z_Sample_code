#include "port.h"
#include "gpio.h"
#include "button.h"


#define BTN_IRQn  		PORTC_PORTD_IRQn
//Port C
#define BTN_GPIO  		GPIOC
#define BTN_PORT 		PORTC
#define BTN1_PIN 		(3)
#define BTN2_PIN		(12)




void button_init(void)
{
	gpio_clock_init(SCLK_PORTC);
	port_mode_config(BTN_PORT,BTN1_PIN,MOD_GPIO);
	port_mode_config(BTN_PORT,BTN2_PIN,MOD_GPIO);
	port_res_pull_config(BTN_PORT,BTN1_PIN,RES_ENABLE|RES_PULL_UP);
	port_res_pull_config(BTN_PORT,BTN2_PIN,RES_ENABLE|RES_PULL_UP);
	gpio_set_dir(BTN_GPIO,BTN1_PIN,DIR_IN);
	gpio_set_dir(BTN_GPIO,BTN2_PIN,DIR_IN);
//	//port irq
//	port_ext_int_config(BTN_PORT,BTN1_PIN,INT_FALL);
//	port_ext_int_config(BTN_PORT,BTN2_PIN,INT_FALL);
//	//core irq
//	NVIC_EnableIRQ(BTN_IRQn);
}

uint8_t button1_read_value(void)
{
	return (!gpio_get_pin(BTN_GPIO,BTN1_PIN));
}


void PORTC_PORTD_IRQHandler(void)
{
	//irq handler
  led1_toggle_value();
}



