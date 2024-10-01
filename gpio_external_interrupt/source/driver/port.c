

#include "port.h"

#define INT_POS  (16)
#define INT_MASK 0x0F0000
#define MOD_POS  (8)
#define MOD_MASK 0x000700
#define RES_POS  (0)
#define RES_MASK 0x000003




void port_ext_int_config(PORT_Type *port, uint32_t pin, uint8_t config)
{
	port->PCR[pin] = (port->PCR[pin] & ~INT_MASK) | ((config<<INT_POS)&INT_MASK);
}


void port_mode_config(PORT_Type *port, uint32_t pin, uint8_t config)
{
	port->PCR[pin] = (port->PCR[pin] & ~MOD_MASK) | ((config<<MOD_POS)&MOD_MASK);
}


void port_res_pull_config(PORT_Type *port, uint32_t pin, uint8_t config)
{
	port->PCR[pin] = (port->PCR[pin] & ~RES_MASK) | ((config<<RES_POS)&RES_MASK);
}
