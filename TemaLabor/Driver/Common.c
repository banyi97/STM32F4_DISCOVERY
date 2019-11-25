/*
 * Common.c
 *
 *  Created on: 2016 okt. 28
 *      Author: Nagy Ákos
 */

#include "stm32f4xx_hal.h"
#include "Common.h"

TIM_HandleTypeDef    TimHandle;

uint32_t DRV_GetTime(void)
{
	return HAL_GetTick();
}

void DRV_InitDrawTimer(void)
{
	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* TIMx Peripheral clock enable */
	__HAL_RCC_TIM3_CLK_ENABLE();

	/*##-2- Configure the NVIC for TIMx ########################################*/
	/* Set the TIMx priority */
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);

	/* Enable the TIMx global Interrupt */
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	/* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
	uint16_t uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;

	/* Initialize TIM3 peripheral as follows:
	   + Period = 10000 - 1
	   + Prescaler = ((SystemCoreClock/2)/10000) - 1
	   + ClockDivision = 0
	   + Counter direction = Up
	*/

	/* Set TIMx instance */
	TimHandle.Instance = TIM3;
	TimHandle.Init.Period = 500 - 1;
	TimHandle.Init.Prescaler = uwPrescalerValue;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
		DRV_ErrorLoop();

	/*##-2- Start the TIM Base generation in interrupt mode ####################*/
	/* Start Channel1 */
	if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
		DRV_ErrorLoop();
}

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TimHandle);
}

void DRV_InitLed(Led_TypeDef led)
{
	BSP_LED_Init(led);
}

void DRV_SetLed(Led_TypeDef led, FunctionalState state)
{
	if (state == ENABLE)
		BSP_LED_On(led);
	else
		BSP_LED_Off(led);
}

void DRV_ErrorLoop(void)
{
	while(1)
	{
		DRV_SetLed(LED4, ENABLE);
		HAL_Delay(500);
		DRV_SetLed(LED4, DISABLE);
		HAL_Delay(500);
	}
}
