/*
 * touch.h
 *
 *  Created on: 2016 okt. 26
 *      Author: csorvasig
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include <stdint.h>

/**
 * Initializes the touchscreen periphery
 */
void DRV_TS_Init(void);

/**
 * Returns the state of touch detection
 * @return
 */
uint8_t DRV_TS_IsTouchDetected(void);

/**
 * Returns the x position of the last touch
 * @return x position of the last touch
 */
uint16_t DRV_TS_GetX(void);

/**
 * Returns the y position of the last touch
 * @return y position of the last touch
 */
uint16_t DRV_TS_GetY(void);

#endif /* TOUCH_H_ */
