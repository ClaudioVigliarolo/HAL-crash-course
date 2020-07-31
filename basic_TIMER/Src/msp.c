/*
 * msp.c
 *
 *  Created on: 02-Jun-2018
 *      Author: kiran
 */


#include "main.h"

void HAL_MspInit(void)
{
 //Here will do low level processor specific inits.
	//1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16; //usage fault, memory fault and bus fault system exceptions

	//3. configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	 GPIO_InitTypeDef usart_pins;

	 //enable the clock for usart2 and gpios
	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_USART2_CLK_ENABLE();

	 usart_pins.Alternate = GPIO_AF7_USART2;
	 usart_pins.Mode = GPIO_MODE_AF_PP;
	 usart_pins.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	 usart_pins.Pull = GPIO_PULLUP;
	 usart_pins.Speed = GPIO_SPEED_FREQ_MEDIUM;
	 usart_pins.Pull = GPIO_PULLUP;

	 HAL_GPIO_Init(GPIOA, &usart_pins);

	 //enable the irq and set the priority
	 HAL_NVIC_SetPriority(USART2_IRQn, 5, 5);
	 HAL_NVIC_EnableIRQ(USART2_IRQn);

}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{

	//1. enable the clock for the TIM6 peripheral
	__HAL_RCC_TIM6_CLK_ENABLE();

	//2. Enable the IRQ of TIM6
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//3. setup the priority for TIM6_DAC_IRQn
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn,15,0);

}


