
#include "MKL46Z4.h"

//SC1 type
#define SC1_TYPE_A   	0
#define SC1_TYPE_B 		1 		

#define ADC_CHANNEL 	3

void adc_init(void(*callback)(void));
uint32_t adc_conversion_read(uint8_t type, uint8_t channel);
uint32_t adc_read(uint8_t type, uint8_t channel);
