/**
  ******************************************************************************
  * @file    oled_handler.c
  * @author  Marko Pavlin
  * @brief   This file contains all the functions for handling the OLED display.
  *
  ******************************************************************************
  */

#include "oled.h"
#include "gfx.h"
#include "fonts.h"
#include "serial_handler.h"


void OLED_Initialize(void) {
	oled_init();

}

void OLED_Process(void) {
	char ch[2] = {0,0};
	if (GetDisplayFlag()) {
		// Display new char
		ch[0] = GetDisplayData();
		clear();
		graphics_text(1, 1, FONT_FIFTEEN_DOT, ch);
		oled_update();	
	}
}

