/*
 * vcp.c
 *
 *  Created on: 2016 okt. 26
 *      Author: Gabor
 */

#include "vcp.h"
#include "UartFifo.h"
#include <string.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal.h>

UART_HandleTypeDef huart;

void DRV_VCP_Init()
{
	GPIO_InitTypeDef gpio;

	HAL_Init();

	__GPIOA_CLK_ENABLE();
	__USART1_CLK_ENABLE();

	gpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FAST;
	gpio.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &gpio);

	huart.Instance = USART1;
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart);

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    DRV_VCP_EnableIT();
}

void DRV_VCP_EnableIT(){
	//__HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
	huart.Instance->CR1|=UART_FLAG_RXNE;//(1<<5);
}
void DRV_VCP_DisableIT(){
	//__HAL_UART_DISABLE_IT(&huart, UART_IT_RXNE);
	huart.Instance->CR1&=~UART_FLAG_RXNE;//(1<<5);
}

void DRV_VCP_WriteString(char * str)
{
	uint32_t len = strlen(str);
	HAL_UART_Transmit(&huart, str, len, HAL_MAX_DELAY);
}


void USART1_IRQHandler(void)
{
	char b;
	volatile uint32_t sr=huart.Instance->SR;
	b = huart.Instance->DR & (uint16_t)0x01FFU;
	if (__HAL_UART_GET_IT_SOURCE(&huart, UART_IT_RXNE) != RESET)
	{
		UartFifoPush(b);
	}
	HAL_NVIC_ClearPendingIRQ(USART1_IRQn);
}
