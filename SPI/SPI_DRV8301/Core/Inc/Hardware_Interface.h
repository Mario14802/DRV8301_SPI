/*
 * Hardware_Interface.h
 *
 *  Created on: Oct 31, 2024
 *      Author: MARIO
 */

#ifndef HARDWARE_INTERFACE_HARDWARE_INTERFACE_H_
#define HARDWARE_INTERFACE_HARDWARE_INTERFACE_H_

#include "stm32f1xx_hal.h"  // Change to match your STM32 family, e.g., stm32f4xx_hal.h for STM32F4

//#define size                 1

//#define TimeOut      0xFFFFFFFFU
/* Extern declarations for SPI and GPIO configuration structures */

/* Status Type Enum for SPI */
typedef enum {
    SPI_OK       = 0x00U,
    SPI_ERROR    = 0x01U,
    SPI_BUSY     = 0x02U,
    SPI_TIMEOUT  = 0x03U
} SPI_AGHW_StatusTypeDef;




/* Function Prototypes */
void SPI_AGHW_Transmit(uint8_t *pData,uint16_t size,uint32_t DELAY);
uint16_t SPI_AGHW_Receive( uint8_t *pData,uint16_t size,uint32_t DELAY);
uint16_t SPI_AGHW_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData,uint16_t size,uint32_t DELAY);

void GPIO_AGHW_ResetPin(uint16_t GPIO_Pin, uint8_t PinState);
void GPIO_AGHW_SetPin(uint16_t GPIO_Pin, uint8_t PinState);
#endif /* HARDWARE_INTERFACE_HARDWARE_INTERFACE_H_ */
