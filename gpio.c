#include "gpio.h"
#include "Uart.h"
#define SWITCH_PIN (12) // PORT A


int8_t count = 0;
uint8_t reverse = 0;

void delay(unsigned int length_ms)
{
    SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;  // Make sure clock is enabled
    LPTMR0->CSR = 0;                     // Reset LPTMR settings
    LPTMR0->CMR = length_ms;             // Set compare value (in ms)

    // Use 1kHz LPO with no prescaler
    LPTMR0->PSR = LPTMR_PSR_PCS(1) | LPTMR_PSR_PBYP_MASK;

    // Start the timer and wait for it to reach the compare value
    LPTMR0->CSR = LPTMR_CSR_TEN_MASK;
    while (!(LPTMR0->CSR & LPTMR_CSR_TCF_MASK))
        ;

    LPTMR0->CSR = 0;                     // Turn off timer
}

void SevenSegment(void)
{
      switch (count)
      {
         case 0:
					 //GPIOB_PTOR |= (1<<Segment_a);
        	 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d));
					 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f));
         break;

         case 1:
        	PTB->PDOR = ~(MASK(Segment_b) | MASK(Segment_c));
				  PTC->PDOR = MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g);
         break;

         case 2:
         	 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_d));
					 PTC->PDOR = ~(MASK(Segment_e)| MASK(Segment_g));
         break;

         case 3:
        	 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d));
					 PTC->PDOR = ~(MASK(Segment_g)) | MASK(Segment_e)| MASK(Segment_f);
         break;

         case 4:
					 PTB->PDOR = MASK(Segment_a) | MASK(Segment_d);
        	 PTC->PDOR = ~(MASK(Segment_g) | MASK(Segment_f)) | MASK(Segment_e);
         break;

         case 5:
        	 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_c) | MASK(Segment_d)) | MASK(Segment_b);
					 PTC->PDOR = MASK(Segment_e);
         break;

         case 6:
					 PTB->PDOR = MASK(Segment_b) | ~(MASK(Segment_a) | MASK(Segment_c) | MASK(Segment_d));
        	 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g));
         break;

         case 7:
					 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c));
        	 PTC->PDOR = MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g);
         break;

         case 8:
        	 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d));
        	 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g));
         break;

         case 9:
        	 PTC->PDOR = MASK(Segment_e);
					 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d));
         break;
			 //hex only
			 case 10:
				 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c)) | MASK(Segment_d);
				 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g));
					 break;

			 case 11:
				 PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d));
						 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g));
					 break;

			 case 12:
				 PTB->PDOR =  MASK(Segment_b) | MASK(Segment_c) | ~(MASK(Segment_a) | MASK(Segment_d));
						 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f)) | MASK(Segment_g);
					 break;

			 case 13:
					PTB->PDOR = ~(MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d));
						 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f));
					 break;

			 case 14:
				 PTB->PDOR = MASK(Segment_b) | MASK(Segment_c) | ~(MASK(Segment_a) | MASK(Segment_d));
						 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g));
					 break;

			 case 15:
				 PTB->PDOR = ~(MASK(Segment_a)) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d);
						 PTC->PDOR = ~(MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g));
					 break;
    }
}

void RGBLed_Init(void){
	
	// Activarea semnalului de ceas pentru pinii folositi �n cadrul led-ului RGB
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;
	
	// Enable Clock to port A
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTB_MASK;
	// Make GPIO
	PORTB->PCR[Segment_a] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[Segment_a] |= PORT_PCR_MUX(1);
	PORTB->PCR[Segment_b] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[Segment_b] |= PORT_PCR_MUX(1);
	PORTB->PCR[Segment_c] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[Segment_c] |= PORT_PCR_MUX(1);
	PORTB->PCR[Segment_d] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[Segment_d] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[Segment_e] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[Segment_e] |= PORT_PCR_MUX(1);
	PORTC->PCR[Segment_f] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[Segment_f] |= PORT_PCR_MUX(1);
	PORTC->PCR[Segment_g] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[Segment_g] |= PORT_PCR_MUX(1);
		
	
	// Configurare pin pe post de output
	GPIOB_PDDR |= (1<<Segment_a);
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOB_PCOR |= (1<<Segment_a);
	
	// Configurare pin pe post de output
	GPIOB_PDDR |= (1<<Segment_b);
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOB_PCOR |= (1<<Segment_b);
	
	// Configurare pin pe post de output
	GPIOB_PDDR |= (1<<Segment_c);
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOB_PCOR |= (1<<Segment_c);
	
	// Configurare pin pe post de output
	GPIOB_PDDR |= (1<<Segment_d);
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOB_PCOR |= (1<<Segment_d);
	
	// Configurare pin pe post de output
	GPIOC_PDDR |= (1<<Segment_e);
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOC_PCOR |= (1<<Segment_e);
	
	// Configurare pin pe post de output
	GPIOC_PDDR |= (1<<Segment_f);
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOC_PCOR |= (1<<Segment_f);
	
	// Configurare pin pe post de output
	GPIOC_PDDR |= (1<<Segment_g);
	// Stingerea LED-ului (punerea pe 0 logic)
	GPIOC_PCOR |= (1<<Segment_g);
	
	PTB->PDOR = MASK(Segment_a) | MASK(Segment_b) | MASK(Segment_c) | MASK(Segment_d);
	PTC->PDOR = MASK(Segment_e) | MASK(Segment_f) | MASK(Segment_g);
}

void Switch_Init(void) {
	
	
	// Activarea semnalului de ceas pentru a putea folosi GPIO cu ajutorul pinului 1 de pe portul C
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	// Utilizarea GPIO impune selectarea variantei de multiplexare cu valorea 1
	PORTA->PCR[SWITCH_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SWITCH_PIN] |= PORT_PCR_MUX(1);
	
	// Activare �ntreruperi pe rising edge
	PORTA->PCR[SWITCH_PIN] |= PORT_PCR_IRQC(0x09) | PORT_PCR_PE_MASK;
	
	if(reverse)
		count = 15;
	else 
		count = 0;
	// Activare �ntrerupere pentru a folosi switch-ul
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	//NVIC_SetPriority(PORTA_IRQn, 128);
	NVIC_EnableIRQ(PORTA_IRQn);
}

int init = 0;
void addValue(int8_t cmd){
	count = count + cmd;
	
	if(count < 0)
		count = 15;
	if(count > 15)
		count = 0;
	if(init==0){
			count=0;
			init=1;
	}
	UART0_Transmit(count);
	delay(300);
	SevenSegment();
}

void PORTA_IRQHandler() {
	if(reverse){
		addValue(-1);
	} else {
		addValue(1);
	}	
	
	PORTA_ISFR = (1<<SWITCH_PIN);
}

void UART0_IRQHandler(void) {
		uint8_t c = 0;
		if(UART0->S1 & UART0_S1_RDRF_MASK) {
			c = UART0->D;
		}
		//Daca c este a seteaza reverse pe 0
		if(c == 'a'){
			reverse = 0;
		}
		//Daca c este d seteaza reverse pe 1
		if(c == 'd'){
			reverse = 1;
		}
	
		//Daca c este w incrementeaza valoarea lui count
		if(c == 'w'){
			addValue(1);
		}
		
		//Daca c este s decrementeaza valoarea lui count
		if(c == 's') {
			addValue(-1);
		}
		//delay(300);
		
		PORTA_ISFR = (1<<SWITCH_PIN);
}
