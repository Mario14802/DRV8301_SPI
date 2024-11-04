/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
GPIO_InitTypeDef GPIO_InitStruct;

drv8301_t DRV=
{
		.Agonistic_HardwareInterface_t.SPI_AG_Transmit=SPI_AGHW_Transmit,
		.Agonistic_HardwareInterface_t.SPI_AG_TransmitReceive=SPI_AGHW_TransmitReceive,
		.Agonistic_HardwareInterface_t.SPI_AG_Recieve=SPI_AGHW_Receive,
		.Agonistic_HardwareInterface_t.GPIO_RESET_AG=GPIO_AGHW_ResetPin,
		.Agonistic_HardwareInterface_t.GPIO_SET_AG=GPIO_AGHW_SetPin


};

/* Function prototypes -------------------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);





/* Main function -------------------------------------------------------------*/
int main(void)
{

	/* Initialize the HAL Library */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();

	/* Variables to store DRV8301 communication data */
	uint16_t readData ;


	//DRV.Agonistic_HardwareInterface_t.GPIO_AGHW=GPIO_AGHW_WritePin;

	/* Infinite loop */
	while (1)
	{
		/* Write data to DRV8301 */
		DRV8301_Write(&DRV);

		/* Read data from DRV8301 */
		DRV8301_Read(&DRV);

		readData=DRV.readData;

		/* Add delay or perform other operations as needed */
		HAL_Delay(1000);  // 1 second delay
	}
}














/* SPI1 Initialization Function */
static void MX_SPI1_Init(void)
{
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_16BIT;           // DRV8301 requires 16-bit frames
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;          // Clock idle state low (CPOL = 0)
	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;              // Data sampled on second edge (CPHA = 1)
	hspi1.Init.NSS = SPI_NSS_SOFT;                      // NSS manually controlled
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;  // Safe clock speed (adjust as needed)
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;             // MSB transmitted first
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;

	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}
}

/* GPIO Initialization for NSS (Slave Select) Pin */
static void MX_GPIO_Init(void)
{
	/* Enable GPIO clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();  // Assuming NSS is on GPIOA

	/* Configure NSS (Slave Select) pin as output */
	GPIO_InitStruct.Pin = GPIO_PIN_5;   // NSS pin (PA4)
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Set NSS high to deselect DRV8301 */
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

/* Function to write data to the DRV8301 */


/* System Clock Configuration */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/* Error Handler */
void Error_Handler(void)
{
	/* Add your error handling code here */
}
