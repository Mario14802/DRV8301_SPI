/*
 * Hardware_Interface.c
 *
 *  Created on: Oct 31, 2024
 *      Author: MARIO
 */

#include "../Inc/Hardware_Interface.h"
extern SPI_HandleTypeDef hspi1;
extern GPIO_InitTypeDef GPIO_InitStruct;


/* Function to Transmit data over SPI */
void SPI_AGHW_Transmit(uint8_t *pData,uint16_t size,uint32_t DELAY) {
	HAL_SPI_Transmit(&hspi1, pData, size, DELAY);

}

/* Function to Receive data over SPI */
uint16_t SPI_AGHW_Receive( uint8_t *pData,uint16_t size,uint32_t DELAY) {
	return HAL_SPI_Receive(&hspi1, pData, size, DELAY);

}

/* Function to Transmit and Receive data over SPI */
uint16_t SPI_AGHW_TransmitReceive( uint8_t *pTxData, uint8_t *pRxData,uint16_t size,uint32_t DELAY)
{
	return HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, size, DELAY);

}

/* Function to Write to a GPIO Pin */
void GPIO_AGHW_ResetPin(uint16_t GPIO_Pin, uint8_t PinState) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}
void GPIO_AGHW_SetPin(uint16_t GPIO_Pin, uint8_t PinState) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}
