/**
  ******************************************************************************
  * @file    serial_handler.c
  * @author  Marko Pavlin
  * @brief   This file contains all the functions for handling 
  *          serial communication.
  *          
  *          Rx is handled by Rx Interrupt
	*          Tx is direct
	*          
	*          On init, the Rx flag is reset. After receiving first character
	*          it is set for displaying. The Rx flag is set and all further 
	*          characters are passed through on Tx. 
	*          The CR or LF resets the flag and are passed directly to the Tx
	*          to reset flags in all modules in chain.
  *
  ******************************************************************************
  */

#include "stm32g0xx_hal.h"
#include "serial_handler.h"

/** UART handlers defined in MCU Init */
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

// Rx flag indicates received char
static volatile int Rx_Flag = 0;

// Tx flag indicates char should be transmitted
static volatile int Tx_Flag = 0;

// Display flag indicates char should be displayed
static volatile int Dispaly_Flag = 0;

// Rx buffer
static uint8_t Rx_Data;

// Tx buffer
static uint8_t Tx_Data;

// Tx buffer
static uint8_t Display_Data;


/** Init serial ports, The HAL part should be OK here before calling this function */
void Serial_Init(void) {

	HAL_HalfDuplex_EnableReceiver(&huart1);
	HAL_HalfDuplex_EnableTransmitter(&huart2);
	
  HAL_UART_Receive_IT(&huart1, &Rx_Data, 1); // initiate rx irq

}


/** Process the serial logic based on flags */
void Serial_Process(void) {
  
  if (Tx_Flag) {
		Tx_Flag = 0;
		HAL_UART_Transmit(&huart2,&Tx_Data, 1, 100);
	}
}

/** Returns display flag */
int GetDisplayFlag(void) {
	return Dispaly_Flag;
}

/** Returns display char */
uint8_t GetDisplayData(void) {
	return Display_Data;
}


// USART1 Rx Interrupt handler
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
  if (huart->Instance == USART1) {   // USART 1 receives chars 
		if (Rx_Data != 13)  // Char is not <CR>
		{
			if (Rx_Flag) { // Char already displayed, just retransmit it to next module in chain 
				Tx_Data = Rx_Data;
				Tx_Flag = 1;
			} else { // This is first char, let's display it, no further transmission needed
				Display_Data = Rx_Data;
				Rx_Flag = 1;
				Dispaly_Flag = 1;
			}
			
		} else { // Char is <CR>, reset the Rx flag and retransmit to next module in chain
			Tx_Data = 13;
			Tx_Flag = 1;
			Rx_Flag = 0;
		}

		// activate UART receive interrupt for next character
		HAL_UART_Receive_IT(&huart1, &Rx_Data, 1); 
	}
}



// USART1 Tx Interrupt handler
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) 
{
  if (huart->Instance == USART2) {   // USART 2 transmit chars
    Tx_Flag = 0;  // transfer completed
	}
}



/*************************************  Serial Interrupt handlers via HAL system ******************************/


/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}


/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart2);
}


