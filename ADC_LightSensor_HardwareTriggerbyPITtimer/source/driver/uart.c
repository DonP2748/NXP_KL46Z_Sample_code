

#include "port.h"
#include "gpio.h"
#include "uart.h"

//Port A
#define UART_SCLOCK  			SCLK_PORTA
#define UART_PORT_PIN 			PORTA
#define UART_RX  				(1)
#define UART_TX 				(2)  
//UART 0 SRC
#define UART0_SRC_TX_POS  		(0)
#define UART0_SRC_TX_MASK  		0x03
#define UART0_SRC_RX_POS  		(2)
#define UART0_SRC_RX_MASK  		0x04

//UART SRC
#define UART_SRC_TX_POS  		UART0_SRC_TX_POS
#define UART_SRC_TX_MASK  		UART0_SRC_TX_MASK
#define UART_SRC_RX_POS  		UART0_SRC_RX_POS
#define UART_SRC_RX_MASK  		UART0_SRC_RX_MASK

//UART SRC CLOCK
#define UART_SRC_CLOCK_POS 		(26)
#define UART_SRC_CLOCK_MASK 	0xC000000

//UART Port
#define UART_PORT  				UART0

#define SYSTEM_CLOCK 			(4000000)  //Internal Reference Clock
#define SYS_CLK_DIV1 	  		(0x00)
#define SYS_CLK_DIV2 			(0x01)
#define SYS_CLK_DIV4 			(0x02)

#define BR115200 				(115200)
#define OSR115200  				(17)
#define BR9600					(9600)
#define OSR9600					(16) 		 // Over Sampling Ratio, can be from 4 to 32


static void mcgirclk_uart0_config(void);
static void uart_set_baud_rate(uint32_t baud);
static uint8_t get_osr_by_baud(uint32_t baud);


void uart_init(void)
{
	//use MCGIRCLK clock for uart0
	mcgirclk_uart0_config();
	//disable uart
	uart_tranceive_enable(UART_PORT,0);
	uart_set_baud_rate(BR115200);
	//uart io
	gpio_clock_init(UART_SCLOCK);
	port_mode_config(UART_PORT_PIN,UART_RX,MOD_ALT1);
	port_mode_config(UART_PORT_PIN,UART_TX,MOD_ALT1);
	//enable uart
	uart_tranceive_enable(UART_PORT,1);
}


void uart_config_src_pin(uint8_t rx, uint8_t tx)
{
	SIM->SOPT5 = (SIM->SOPT5 & ~(UART_SRC_TX_MASK|UART_SRC_RX_MASK))\
						   |((tx<<UART_SRC_TX_POS)&UART_SRC_TX_MASK)\
						   |((rx<<UART_SRC_RX_POS)&UART_SRC_RX_MASK);
}


void uart_config_src_clock(uint8_t clk)
{
	SIM->SOPT2 = (SIM->SOPT2 & ~(UART_SRC_CLOCK_MASK)) | ((clk<<UART_SRC_CLOCK_POS)&UART_SRC_CLOCK_MASK);
}


void uart_write_byte(uint8_t data)
{
	while(!((UART0->S1 & UART0_S1_TDRE_MASK)));
	UART0->D = data;
}

uint8_t uart_read_byte(void)
{
      while (!(UART0->S1 & UART0_S1_RDRF_MASK));
      return UART0->D;
}



void uart_tranceive_enable(UART0_Type *uart, uint8_t enable)
{
    if (enable){
        uart->C2 |=  (UART_C2_TE_MASK | UART_C2_RE_MASK);
    }
    else{
    	uart->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
    }
}


static void mcgirclk_uart0_config(void)
{
	MCG->C1 = (MCG->C1 & ~MCG_C1_IRCLKEN_MASK)|MCG_C1_IRCLKEN(1);
	SIM->SCGC4 |= SIM_SCGC4_UART0(1);
	//UART0SRC = MCGIRCLK
	SIM->SOPT2 = (SIM->SOPT2 & ~SIM_SOPT2_UART0SRC_MASK)|SIM_SOPT2_UART0SRC(0b11);
	//FCRDIV = 4, 4MHz for default and div4 so SYSTEMCLOCK is 1MHz, but why we need to div?
	//no div and sys clock still 4MHz
	MCG->SC = (MCG->SC & ~MCG_SC_FCRDIV_MASK)| MCG_SC_FCRDIV(SYS_CLK_DIV1);
	//CHOOSE IR High CLOCK
	MCG->C2 = (MCG->C2 & ~MCG_C2_IRCS_MASK)| MCG_C2_IRCS(1);

}

static void uart_set_baud_rate(uint32_t baud)
{
	UART0->C4 = (UART0->C4 & (~UART0_C4_OSR_MASK)) | (get_osr_by_baud(baud)-1);
	//set baud rate
	uint16_t sbr = (uint16_t)(SYSTEM_CLOCK/(baud*get_osr_by_baud(baud)));
	UART_PORT->BDH = (UART_PORT->BDH & ~UART0_BDH_SBR_MASK) | UART0_BDH_SBR(sbr>>8);
	UART_PORT->BDL = sbr & UART_BDL_SBR_MASK;
}


static uint8_t get_osr_by_baud(uint32_t baud)
{
	switch(baud){
		case BR9600:
			return OSR9600;
		case BR115200:
			return OSR115200;
		default:
			return 0;
	}
}
