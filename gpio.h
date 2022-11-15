#include "MKL25Z4.h"
/*******************************************************************************
 * DEFINITIONS
 ******************************************************************************/
#define Segment_a (0)
#define Segment_b (1)
#define Segment_c (2)
#define Segment_d (3) // port B - pinii 0-3
#define Segment_e (2) // PTC2
#define Segment_f (1) // PTC1
#define Segment_g (8) // PTC8
#define MASK(x)  (1UL << (x)) //Masca pt set/togle pe pinii respectivi

void Switch_Init(void);
void PORTA_IRQHandler(void);
void SevenSegment(void);
void delay(unsigned int length_ms);
void RGBLed_Init(void);
void UART0_IRQHandler(void);
