/**
  ******************************************************************************
  * @file    oled_handler.h
  * @author  Marko Pavlin
  * @brief   This file contains all the functions prototypes for the 
  *          oled handler module.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OLED_HANDLER_H
#define OLED_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

void OLED_Initialize(void);
void OLED_Process(void);

#ifdef __cplusplus
}
#endif

#endif /* OLED_HANDLER_H */

