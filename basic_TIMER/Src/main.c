/*
 * main.c
 *
 *  Created on: 02-Jun-2018
 *      Author: kiran
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include <time.h>


void TIMER6_Init(void);
void GPIO_Init(void);
void Error_handler(void);
void USART2_init(void);
TIM_HandleTypeDef htimer6;
char *space = "\n\r";
UART_HandleTypeDef huart2;
uint32_t millis1;
uint32_t millis2;
uint8_t isEnd = 0;

int main(void) {
	HAL_Init();
	TIMER6_Init();
	USART2_init();

	//Lets start timer in IT mode
	HAL_TIM_Base_Start_IT(&htimer6);

	while (1);

	return 0;
}




void USART2_init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;

	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_handler();
	}

}

void TIMER6_Init(void) {
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 64000 - 1;

	if (HAL_TIM_Base_Init(&htimer6) != HAL_OK) {
		Error_handler();
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	char data[300];

	if (isEnd) {
		millis2 = HAL_GetTick();
		uint32_t tot = millis2 - millis1;
		sprintf(data, "%lu", tot);
		uint16_t len = strlen(data);
		HAL_UART_Transmit(&huart2, (uint8_t*) data, len, HAL_MAX_DELAY);
		uint16_t len2 = strlen(space);
		HAL_UART_Transmit(&huart2, (uint8_t*) space, len2, HAL_MAX_DELAY);
		isEnd = 0;
	} else {
		millis1 = HAL_GetTick();
		isEnd = 1;
	}

}

void Error_handler(void) {
	while (1)
		;
}

