/**
  ******************************************************************************
  * @file    serial_handler.h
  * @author  Marko Pavlin
  * @brief   This file contains all the functions prototypes for the 
  *          serial handler module.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

void Serial_Init(void);
void Serial_Process(void);

int GetDisplayFlag(void);
uint8_t GetDisplayData(void);




#ifdef __cplusplus
}
#endif

#endif /* SERIAL_HANDLER_H */

