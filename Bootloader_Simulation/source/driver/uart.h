
#include "MKL46Z4.h"

//SRC RX 
#define UART_RX_PIN 		0x00
#define UART_RX_CMP0		0x01
//SRC TX 
#define UART_TX_PIN 		0x00
#define UART_TX_TPM1  		0x01
#define UART_TX_TPM2   		0x02
//SRC CLOCK
#define UART_CLOCK_DIS  	0x00
#define UART_MCGFLLCLK  	0x01
#define UART_OSCERCLK  		0x02
#define UART_MCGIRCLK  		0x03

//BAUD
#define UART_BAUD_115200 	0x01


typedef void(*uart_rcv_callback)(uint8_t data);


void uart_init(void);
void uart_write_byte(uint8_t data);
void uart_tranceive_enable(uint8_t enable);
uint8_t uart_read_byte(void);

void uart_register_data_recv_cb(uart_rcv_callback callback);
void uart_enable_recv_interrupts(uint8_t val);













