/** Include functions prototypes for the HAL module driver. */
#include "stm32g0xx_hal.h"
#include "serial_handler.h"
#include "oled_handler.h"

extern void MCU_Init(void);


int main(void) {
	
	MCU_Init();
	
  Serial_Init();
	OLED_Initialize();
	
	while (1) {
		Serial_Process();
    OLED_Process();
	}
}
