#include <MKL25Z4.h>
#include "gpio.h"
#include "Uart.h"

int main(void)
{
			Switch_Init();
			RGBLed_Init();
			UART0_Init(115200);

			for(;;) {}
}
