/*
 * Common.h
 *
 *  Created on: 2016 okt. 28
 *      Author: Nagy Ákos
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stm32f4xx.h>
#include "stm32f429i_discovery.h"

/**
 * Returns the systick counter's current value
 * @return systick value
 */
uint32_t DRV_GetTime(void);

/**
 * Initalizes timer interrupt for the drawing
 */
void DRV_InitDrawTimer(void);

/**
 * Initializes one of the board's led.
 * @param led enum secifies witch led is initalizes
 */
void DRV_InitLed(Led_TypeDef led);

/**
 * Set the specified led state
 * @param led enum specifies witch led is set
 * @param state the new state of the led
 */
void DRV_SetLed(Led_TypeDef led, FunctionalState state);

/**
 * Infinite loop for error handling
 */
void DRV_ErrorLoop(void);

#endif /* COMMON_H_ */
