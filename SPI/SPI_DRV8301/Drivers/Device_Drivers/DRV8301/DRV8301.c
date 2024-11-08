/*
 * DRV8301.c
 *
 *  Created on: Oct 31, 2024
 *      Author: MARIO
 */

#include "DRV8301.h"






void DRV8301_Write(drv8301_t *DRV)
{
	DRV->address=DRV8301_STATUS_REG1_ADDR  ;
	DRV->Send_Data =Data_sent;
	// Combine address and data into a 16-bit command
	uint16_t Tx_Data = (((DRV->address) & 0x7F) << 11) | (( DRV->Send_Data) & 0x07FF);

	// Split 16-bit command into two 8-bit parts
	uint8_t Tx_Data_8bit[2];
	Tx_Data_8bit[0] = (uint8_t)((Tx_Data >> 8) & 0xFF); // Higher 8 bits
	Tx_Data_8bit[1] = (uint8_t)(Tx_Data & 0xFF);        // Lower 8 bits

	// Select DRV8301 (NSS low)
	DRV->Agonistic_HardwareInterface_t.GPIO_RESET_AG(4, 0);

	// Transmit the 8-bit array
	DRV->Agonistic_HardwareInterface_t.SPI_AG_Transmit(Tx_Data_8bit, 2, TimeOut);

	// Deselect DRV8301 (NSS high)
	DRV->Agonistic_HardwareInterface_t.GPIO_SET_AG(4, 1);
}

void DRV8301_Read(drv8301_t *DRV)
{
	// Prepare 16-bit read command (MSB set for read)
	DRV->address=DRV8301_CONTROL_REG2_ADDR;


	uint16_t Read_Command = (((DRV->address) & 0x7F) << 11) | 0x8000;

	// Split 16-bit command into two 8-bit parts
	uint8_t Tx_Data_8bit[2];
	Tx_Data_8bit[0] = (uint8_t)((Read_Command >> 8) & 0xFF); // Higher 8 bits
	Tx_Data_8bit[1] = (uint8_t)(Read_Command & 0xFF);        // Lower 8 bits

	// Array to store received 8-bit data
	uint8_t Rx_Data_8bit[2] = {0};

	// Select DRV8301 (NSS low)
	DRV->Agonistic_HardwareInterface_t.GPIO_RESET_AG(4, 0);

	// Transmit read command and receive the response
	DRV->Agonistic_HardwareInterface_t.SPI_AG_TransmitReceive(Tx_Data_8bit, Rx_Data_8bit, 2, TimeOut);

	// Deselect DRV8301 (NSS high)
	DRV->Agonistic_HardwareInterface_t.GPIO_SET_AG(4, 1);

	// Combine received bytes into 16-bit data, returning only the 11 LSBs
	DRV->readData =  ((((uint16_t)Rx_Data_8bit[0] << 8) | Rx_Data_8bit[1]) & 0x07FF);
	//return Rx_Data & 0x07FF;  // Mask to keep only 11 valid bits
}

