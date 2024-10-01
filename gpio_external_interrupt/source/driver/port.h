
#include "MKL46Z4.h"

//INT/DMA
#define DISABLE		0b0000 		//Interrupt/DMA request disabled.
#define DMA_RISE	0b0001 		//DMA request on rising edge.
#define DMA_FALL	0b0010 		//DMA request on falling edge.
#define DMA_BOTH	0b0011 		//DMA request on either edge.
#define INT_ZERO	0b1000 		//Interrupt when logic zero.
#define INT_RISE	0b1001 		//Interrupt on rising edge.
#define INT_FALL	0b1010 		//Interrupt on falling edge.
#define INT_BOTH	0b1011 		//Interrupt on either edge.
#define INT_ONE		0b1100 		//Interrupt when logic one.
//MODE
#define MOD_DISABLE	0b000
#define MOD_GPIO	0b001
//#define 		0b010
//#define 		0b011
//#define 		0b100
//#define 		0b101
//#define 		0b110
//#define 		0b111

#define RES_DISABLE     (0<<1)
#define RES_ENABLE  	(1<<1)
#define RES_PULL_DWN 	(0)
#define RES_PULL_UP 	(1)


void port_ext_int_config(PORT_Type *port, uint32_t pin, uint8_t config);
void port_mode_config(PORT_Type *port, uint32_t pin, uint8_t config);
void port_res_pull_config(PORT_Type *port, uint32_t pin, uint8_t config);







