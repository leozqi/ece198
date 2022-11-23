/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdlib.h>
#include "utci.h"
#include "dht.h"

//#define LOGGING

#ifdef LOGGING
#include <stdio.h>
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
#define BUTTON_DELAY 500

DHT_t am2301;
uint8_t am2301_ok;

enum state {
	ALARM_ON,       // Alarm currently on: light red, speaker playing
	ALARM_CHECKING, // Device monitoring temperature: light green, speaker off
	ALARM_OFF // Alarm off due to override: light yellow, speaker off, no monitoring
};

#define TEST1_TARGET 1000 //MS delay
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
#ifdef LOGGING
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
#endif
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void set_LED(enum state curr_state)
{
	bool R = false; // Boolean to write to pin D9
	bool G = false; // Boolean to write to pin D10
	bool B = false; // Boolean to write to pin D11

	switch (curr_state) {
	case ALARM_ON:       // Red colour
		R = true;
		G = false;
		B = false;
		break;
	case ALARM_CHECKING: // Green colour
		R = false;
		G = true;
		B = false;
		break;
	case ALARM_OFF:      // Yellow colour
		R = true;
		G = true;
		B = false;
		break;
	}

	if (R) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	}

	if (G) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	}

	if (B) {
		HAL_GPIO_WritePin(GPIOA, LD2_Pin | GPIO_PIN_7, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(GPIOA, LD2_Pin | GPIO_PIN_7, GPIO_PIN_RESET);
	}
}

float calc_humidex(float temp, float humidity)
{
	return (temp + (0.5555 * (humidity - 10.0)));
}

#define HIGH_TEMP 39
#define LOW_TEMP 0

/**
 * Define situation as above "moderate heat stress" and below "moderate cold stress"
 */
void change_state(enum state *curr_state, float humidex_temp)
{
	if ((*curr_state) == ALARM_OFF) {
		return;
	}

	if (humidex_temp > HIGH_TEMP || humidex_temp < LOW_TEMP) {
		(*curr_state) = ALARM_ON;
	} else {
		(*curr_state) = ALARM_CHECKING;
	}
}

#define R_TEMP_LOW 10
#define R_TEMP_HIGH 50
#define R_HUMID_LOW 0
#define R_HUMID_HIGH 100

void test2_random()
{
	enum state test_state = ALARM_CHECKING;

	uint32_t rand_temp = 0;
	uint32_t rand_humid = 0;
	float validate = 0.0;
	float humidex_temp = 0.0;
	bool success = false;

	srand(HAL_GetTick());


	for (uint32_t i = 0; i < 100; ++i) {
		test_state = ALARM_CHECKING;
		success = false;
		rand_temp = R_TEMP_LOW + rand() % (R_TEMP_HIGH - R_TEMP_LOW);
		rand_humid = R_HUMID_LOW + rand() % (R_HUMID_HIGH - R_HUMID_LOW);

		humidex_temp = calc_humidex(rand_temp, rand_humid);

		change_state(&test_state, humidex_temp);

		set_LED(test_state);

		validate = rand_temp + (0.5555 * (rand_humid - 10.0));
		switch(test_state) {
		case ALARM_ON:
			success = (validate > HIGH_TEMP) || (validate < LOW_TEMP);
			break;
		case ALARM_CHECKING:
			success = (validate <= HIGH_TEMP) || (validate >= LOW_TEMP);
			break;
		case ALARM_OFF:
			success = false;
		}

		if (success) {
			HAL_GPIO_WritePin(GPIOB, TEST_2_Pin | GPIO_PIN_6, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOB, TEST_2_Pin | GPIO_PIN_6, GPIO_PIN_RESET);
		}

		HAL_Delay(1000);
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_TIM1_Init();
	/* USER CODE BEGIN 2 */
	DHT_init(&am2301, DHT_Type_AM2301, &htim1, 84, TEMP_GPIO_Port,
	TEMP_Pin);

	enum state curr_state = ALARM_CHECKING;
	bool alarm_set = false;
	bool testing = false;
	float temp = 0.0;
	float humidity = 0.0; // in RH
	float utci_temp = 0.0;

	uint32_t test1_tstart = 0;
	uint32_t test1_elapsed = 0;

	test2_random();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (true) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		if (HAL_GPIO_ReadPin(TEST_ON_GPIO_Port, TEST_ON_Pin)) {
			testing = true;
		} else {
			testing = false;
		}

		if (testing) {
			test1_tstart = HAL_GetTick(); // stores current time since system start in MS
		}

		set_LED(curr_state);

		if (alarm_set) {
			HAL_Delay(BUTTON_DELAY);
			alarm_set = false;
		}

		if (!(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))) {
			switch (curr_state) {
			case ALARM_ON:
			case ALARM_CHECKING:
				curr_state = ALARM_OFF;
				break;
			case ALARM_OFF:
				curr_state = ALARM_CHECKING;
				break;
			}

			alarm_set = true;
		}

		am2301_ok = DHT_readData(&am2301, &temp, &humidity);

#ifdef LOGGING
		printf("Data OK: %d\n", am2301.dataValid);
		printf("Raw: %4.2f %4.2f\n", am2301.temperature,
				am2301.humidity);
		printf("Temperature: %4.2f %4.2f\n", temp, humidity);
#endif

		humidex_temp = (float) calc_humidex(temp, humidity);

#ifdef LOGGING
		printf("UTCI temperature: %4.2f\n", utci_temp);
#endif

		change_state(&curr_state, humidex_temp);

		if (testing) {
			test1_elapsed = HAL_GetTick() - test1_tstart;
			if (test1_elapsed < TEST1_TARGET) {
				HAL_GPIO_WritePin(GPIOB, TEST_1_Pin | GPIO_PIN_6,
						GPIO_PIN_SET);
			} else {
				HAL_GPIO_WritePin(GPIOB, TEST_1_Pin | GPIO_PIN_6,
						GPIO_PIN_RESET);
			}
		} else {
			HAL_GPIO_WritePin(GPIOB, TEST_1_Pin | GPIO_PIN_6,
									GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, TEST_2_Pin | GPIO_PIN_6,
									GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, TEST_3_Pin | GPIO_PIN_6,
									GPIO_PIN_RESET);
		}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)
			!= HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void)
{

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 0;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 65535;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LD2_Pin | GPIO_PIN_7, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			TEST_1_Pin | TEST_2_Pin | TEST_3_Pin | GPIO_PIN_6,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LD2_Pin PA7 */
	GPIO_InitStruct.Pin = LD2_Pin | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : TEST_1_Pin TEST_2_Pin TEST_3_Pin PB6 */
	GPIO_InitStruct.Pin = TEST_1_Pin | TEST_2_Pin | TEST_3_Pin | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PC7 */
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : TEMP_Pin */
	GPIO_InitStruct.Pin = TEMP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TEMP_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : TEST_ON_Pin */
	GPIO_InitStruct.Pin = TEST_ON_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(TEST_ON_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == am2301.pin) {
		DHT_pinChangeCallBack(&am2301);
	}
}

#ifdef LOGGING
/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}
#endif

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
