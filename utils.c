#include <MK64F12.h>
#include "utils.h"
#include <stdlib.h>
/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void LED_Initialize(void) {

  SIM->SCGC5    |= (1 <<  9) | (1 <<  10) | (1 <<  11) | (1 <<  13) ;  /* Enable Clock to Port A, B, C & E */ 
  PORTB->PCR[22] = (1 <<  8) ;               /* Pin PTB22 is GPIO */
  PORTB->PCR[21] = (1 <<  8);                /* Pin PTB21 is GPIO */
  PORTE->PCR[26] = (1 <<  8);                /* Pin PTE26  is GPIO */
  
  PTB->PDOR = (1 << 21 | 1 << 22 );          /* switch Red/Green LED off  */
  PTB->PDDR = (1 << 21 | 1 << 22 );          /* enable PTB18/19 as Output */

  PTE->PDOR = 1 << 26;            /* switch Blue LED off  */
  PTE->PDDR = 1 << 26;            /* enable PTE26 as Output */
}


//trying to set sw2 and sw3 as gpio
void switch_setup(void) {
	PORTC->PCR[6] |= (1 <<  8) ;         /* Pin PTC6 is GPIO SW2*/
	PTC->PDDR =      (0 << 6);          /* enable PTC6 as input */
	PORTA->PCR[4] = (1 <<  8) ;         /* Pin PTA4 is GPIO SW3*/
	PTC->PDDR =      (0 << 4);          /* enable PTC6 as input */
	NVIC_EnableIRQ(PORTC_IRQn);          //setting portc interrupt
	NVIC_EnableIRQ(PORTA_IRQn);          //setting porta interrupt
	//PTB-> = PORT_ISFR_ISF(0x40); /* Clear interrupt status flag */
	//PORTA_ISFR = PORT_ISFR_ISF(0x10);
	PORTC->PCR[6] |= (1 << 1);             // internal pull up enable
	PORTC->PCR[6] |= (1 << 0);             // internal pull up enable
	PORTC->PCR[6] |= (1<<19);
	PORTC->PCR[6] |= (1<<16);             // interrupt on rising edge
	PORTA->PCR[4] |= (1 << 1);             // internal pull up enable
	PORTA->PCR[4] |= (1 << 0);             // internal pull up enable
	PORTA->PCR[4] |= (1<<19);
	PORTA->PCR[4] |= (1<<16);             // interrupt on rising edge
}


/*----------------------------------------------------------------------------
  Function that toggles the red LED
 *----------------------------------------------------------------------------*/

void LEDRed_Toggle (void) {
	PTB->PTOR = 1 << 22; 	   /* Red LED Toggle */
}

/*----------------------------------------------------------------------------
  Function that toggles the blue LED
 *----------------------------------------------------------------------------*/
void LEDBlue_Toggle (void) {
	PTB->PTOR = 1 << 21; 	   /* Blue LED Toggle */
}

/*----------------------------------------------------------------------------
  Function that toggles the green LED
 *----------------------------------------------------------------------------*/
void LEDGreen_Toggle (void) {
	PTE->PTOR = 1 << 26; 	   /* Green LED Toggle */
}

/*----------------------------------------------------------------------------
  Function that turns on Red LED & all the others off
 *----------------------------------------------------------------------------*/
void LEDRed_On (void) {
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	
  PTB->PCOR   = 1 << 22;   /* Red LED On*/
  PTB->PSOR   = 1 << 21;   /* Blue LED Off*/
  PTE->PSOR   = 1 << 26;   /* Green LED Off*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

/*----------------------------------------------------------------------------
  Function that turns on Green LED & all the others off
 *----------------------------------------------------------------------------*/
void LEDGreen_On (void) {
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	
  PTB->PSOR   = 1 << 21;   /* Blue LED Off*/
  PTE->PCOR   = 1 << 26;   /* Green LED On*/
  PTB->PSOR   = 1 << 22;   /* Red LED Off*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

/*----------------------------------------------------------------------------
  Function that turns on Blue LED & all the others off
 *----------------------------------------------------------------------------*/
void LEDBlue_On (void) {
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	
  PTE->PSOR   = 1 << 26;   /* Green LED Off*/
  PTB->PSOR   = 1 << 22;   /* Red LED Off*/
  PTB->PCOR   = 1 << 21;   /* Blue LED On*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

/*----------------------------------------------------------------------------
  Function that turns all LEDs off
 *----------------------------------------------------------------------------*/
void LED_Off (void) {	
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	
	PTB->PSOR   = 1 << 22;   /* Red LED Off*/
  PTB->PSOR   = 1 << 21;   /* Blue LED Off*/
  PTE->PSOR   = 1 << 26;   /* Green LED Off*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

void LEDTeal_On (void) {
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	PTB->PSOR   = 1 << 22;   /* Red LED Off*/
  PTB->PSOR   = 1 << 21;   /* Blue LED Off*/
  PTE->PSOR   = 1 << 26;   /* Green LED Off*/
  PTE->PCOR   = 1 << 26;   /* Green LED On*/
  PTB->PCOR   = 1 << 21;   /* Blue LED On*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

void LEDWhite_On (void) {
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	PTB->PSOR   = 1 << 22;   /* Red LED Off*/
  PTB->PSOR   = 1 << 21;   /* Blue LED Off*/
  PTE->PSOR   = 1 << 26;   /* Green LED Off*/
  PTE->PCOR   = 1 << 26;   /* Green LED On*/
  PTB->PCOR   = 1 << 22;   /* Red LED Off*/
  PTB->PCOR   = 1 << 21;   /* Blue LED On*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

void LEDYellow_On (void) {
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	PTB->PSOR   = 1 << 22;   /* Red LED Off*/
  PTB->PSOR   = 1 << 21;   /* Blue LED Off*/
  PTE->PSOR   = 1 << 26;   /* Green LED Off*/
  PTE->PCOR   = 1 << 26;   /* Green LED On*/
  PTB->PCOR   = 1 << 22;   /* Red LED On*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

void LEDPurple_On (void) {
	// Save and disable interrupts (for atomic LED change)
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
	PTB->PSOR   = 1 << 22;   /* Red LED Off*/
  PTB->PSOR   = 1 << 21;   /* Blue LED Off*/
  PTE->PSOR   = 1 << 26;   /* Green LED Off*/
  PTB->PCOR   = 1 << 22;   /* Red LED On*/
  PTB->PCOR   = 1 << 21;   /* Blue LED On*/
	
	// Restore interrupts
	__set_PRIMASK(m);
}

void LEDRed_Blink(void){
			delay();
			LEDRed_On();
			delay();
			LED_Off();
}

void LEDBlue_Blink(void){
			delay();
			LEDBlue_On();
			delay();
			LED_Off();
}

int LEDRed_Blink_num(int num){
		for (int i = 0; i<num; i++) {
			LEDRed_Blink();
		}
}

int LEDBlue_Blink_num(int num){
		for (int i = 0; i<num; i++) {
			LEDBlue_Blink();
		}
}
void game_break (void){
LEDWhite_On();
delay();
delay();
delay();
LED_Off();
}
void delay(void){
	int j;
	for(j=0; j<1000000; j++);
}

int multi_delay(int num){
for(int q = 0; q < num; q++)
	{delay();}
}

int var_delay(int num){
	int j;
	for(j=0; j<num; j++);
}

void check_led(int *arr, int total, int num){
		int check = 0;
		for(int c = 0; c <total; c++)
		{
			arr[c] = rand() %5 + 1;
		}
		
		for(int c =0; c <total; c++){
			
			if (arr[c] == num)
			{check = 1;}
		}
		if(check == 0){
			for(int c =0; c <(rand() %5 + 1); c++){
				arr[rand() % 10] = num;
			}
		}
}
