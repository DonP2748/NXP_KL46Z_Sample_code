#include "debug.h"
#include "port.h"
#include "gpio.h"
#include "adc.h"


#define ADC_PORT_PIN  			PORTE
#define ADC_PIN 				(22)

static void (*__callback)(void) = (void*) 0;
static void adc_internal_config(void);


void adc_init(void(*callback)(void))
{
	//io
	gpio_clock_init(SCLK_PORTE);
	port_mode_config(ADC_PORT_PIN,ADC_PIN,MOD_DISABLE); //analog
	SIM->SCGC6 |= (SIM_SCGC6_ADC0_MASK);
	SIM->SOPT7 = (SIM->SOPT7 & ~(SIM_SOPT7_ADC0TRGSEL_MASK|SIM_SOPT7_ADC0PRETRGSEL_MASK|SIM_SOPT7_ADC0ALTTRGEN_MASK))\
				|SIM_SOPT7_ADC0TRGSEL(4)|SIM_SOPT7_ADC0PRETRGSEL(0)|SIM_SOPT7_ADC0ALTTRGEN(1);
	// adc config
	adc_internal_config();
	//ADC interrupt NVIC
	NVIC_EnableIRQ(ADC0_IRQn);

	__callback = callback;
}



uint32_t adc_conversion_read(uint8_t type, uint8_t channel)
{
	ADC0->SC1[type] = (ADC0->SC1[type] & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(channel); 
	while(!(ADC0->SC1[type] & ADC_SC1_COCO_MASK));                        
	return ADC0->R[type];
}

uint32_t adc_read(uint8_t type, uint8_t channel)
{
	return ADC0->R[type];
}

void ADC0_IRQHandler(void)
{
	//debug_log_printf("ADC IRQ");
	if(__callback){
		__callback();
	}
}


static void adc_internal_config(void)
{
	//config
	ADC0->CFG1 = (ADC0->CFG1 & ~(ADC_CFG1_ADICLK_MASK|ADC_CFG1_MODE_MASK|ADC_CFG1_ADLSMP_MASK|ADC_CFG1_ADIV_MASK|ADC_CFG1_ADLPC_MASK))\
				 |ADC_CFG1_ADICLK(3)|ADC_CFG1_MODE(1)|ADC_CFG1_ADLSMP(4)|ADC_CFG1_ADIV(3)|ADC_CFG1_ADLPC(0);
	ADC0->CFG2 = (ADC0->CFG2 & ~(ADC_CFG2_ADACKEN_MASK|ADC_CFG2_ADLSTS_MASK|ADC_CFG2_ADHSC_MASK))\
				 |ADC_CFG2_ADACKEN(1)|ADC_CFG2_ADLSTS(4)|ADC_CFG2_ADHSC(0);
	ADC0->SC2 = (ADC0->SC2 & ~ADC_SC2_REFSEL_MASK)|ADC_SC2_REFSEL(0);  //voltage ref
	ADC0->SC3 = (ADC0->SC3 & ~ADC_SC3_ADCO_MASK)| ADC_SC3_ADCO(0);//turn off continous


	//auto calib
	//ADC0->SC3 |= ADC_SC3_CAL_MASK | ADC_SC3_CALF_MASK;

	//enable hardware trigger
	ADC0->SC2 = (ADC0->SC2 & ~ADC_SC2_ADTRG_MASK)|ADC_SC2_ADTRG(1);

	ADC0->SC1[SC1_TYPE_A] = (ADC0->SC1[SC1_TYPE_A]& ~ADC_SC1_AIEN_MASK)|ADC_SC1_AIEN(1); //enable interrupt
	ADC0->SC1[SC1_TYPE_A] = (ADC0->SC1[SC1_TYPE_A]& ~(ADC_SC1_DIFF_MASK|ADC_SC1_ADCH_MASK))| ADC_SC1_DIFF(0)|ADC_SC1_ADCH(3);//single end & input dp3


}


