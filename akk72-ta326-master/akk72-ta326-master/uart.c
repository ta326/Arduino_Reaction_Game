#include <MK64F12.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
void uart_init(void) {
	// pins B16 and B17
	SIM->SCGC4 |= (1 << 10); // turn on clock to UART module
	SIM->SCGC5 |= (1 << 10); // turn on clock to PORTB module
	PORTB->PCR[16] &= ~PORT_PCR_MUX(7); 
	PORTB->PCR[16] |= PORT_PCR_MUX(3);
	PORTB->PCR[17] &= ~PORT_PCR_MUX(7); 
	PORTB->PCR[17] |= PORT_PCR_MUX(3); 	
	
	int16_t sbr = SystemCoreClock / ( 16 * 9600);
	
	UART0->C2 &= ~(0x0C); //Disable UART Module
	
	UART0->BDL = (uint8_t) (sbr & 0x00FF);
	UART0->BDH &= 0xE0;
	UART0->BDH |= (uint8_t) ( ( sbr & 0x1F00) >> 8 );
	UART0->C1 = 0; // Configure UART to default
	UART0->C2 |= (0x0C); // Enable UART module	
}

void uart_putchar (char ch) {
	while(!(UART0->S1 & 0x80) );
	UART0->D = (uint8_t) ch;
}

void uart_put(char *ptr_str) {
	while (*ptr_str) {
		uart_putchar (*ptr_str++);
	}
}
