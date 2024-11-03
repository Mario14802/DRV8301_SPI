/*
 * DRV8301.h
 *
 *  Created on: Oct 31, 2024
 *      Author: MARIO
 */

#ifndef DEVICE_DRIVERS_DRV8301_DRV8301_H_
#define DEVICE_DRIVERS_DRV8301_DRV8301_H_

#include <stdint.h>

#define TimeOut  0xFFFFFFFFU



/*
DRV8301 Register Addresses
Register Address	Register Name	Description
0x00	Status Register 1	Contains various fault and status information.
0x01	Status Register 2	Contains additional status information.
0x02	Control Register 1	Configures current sense amplifiers and other settings.
0x03	Control Register 2	Configures driver settings, including gate current and timing.
Address Details
Status Register 1 (0x00): Provides feedback on faults like overcurrent and undervoltage, which can help in diagnosing system issues.
Status Register 2 (0x01): Includes additional status flags like device over-temperature.
Control Register 1 (0x02): Used to configure the current sense amplifier, shutdown modes, and overcurrent protection thresholds.
Control Register 2 (0x03): Controls other aspects of the motor driver, such as gate drive settings and cycle-by-cycle current limit options.
*/
// Define constants for DRV8301 addresses
#define DRV8301_STATUS_REG1_ADDR   0x00
#define DRV8301_STATUS_REG2_ADDR   0x01
#define DRV8301_CONTROL_REG1_ADDR  0x02
#define DRV8301_CONTROL_REG2_ADDR  0x03

typedef struct  {

	uint16_t readData ;
	uint16_t writeData;  // Example data to write
	uint16_t address;      // Example register address (check DRV8301 datasheet for valid addresses)

	struct
	{

		void (*SPI_AG_Transmit)(uint8_t *pData, uint16_t Size, uint32_t Timeout);

		uint16_t (*SPI_AG_TransmitReceive)(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

		uint16_t(*SPI_AG_Recieve)(uint8_t *pData, uint16_t Size, uint32_t Timeout);

		void (*GPIO_SET_AG)(uint16_t GPIO_Pin, uint8_t PinState);

		void (*GPIO_RESET_AG)(uint16_t GPIO_Pin, uint8_t PinState);
	}Agonistic_HardwareInterface_t;


}drv8301_t;

void DRV8301_Write(drv8301_t *DRV, uint16_t address, uint16_t data);
uint16_t  DRV8301_Read(drv8301_t *DRV,uint16_t address);

#endif /* DEVICE_DRIVERS_DRV8301_DRV8301_H_ */
