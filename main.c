#include <MKL25Z4.h>
#include "gpio.h"

int main(void)
{
			Switch_Init();
			RGBLed_Init();

			for(;;) {}
}
