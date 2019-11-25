/*
 * touch.c
 *
 *  Created on: 2016 okt. 26
 *      Author: csorvasig
 */

#include "touch.h"
#include "display.h"
#include "Common.h"

#include <stm32f429i_discovery_ts.h>

static TS_StateTypeDef  TS_State;

void DRV_TS_Init(void)
{
	if (BSP_TS_Init(DRV_Display_GetXSize(), DRV_Display_GetYSize()) != TS_OK)
		DRV_ErrorLoop();
}

uint8_t DRV_TS_IsTouchDetected(void)
{
	BSP_TS_GetState(&TS_State);
	return (uint8_t)TS_State.TouchDetected;
}

uint16_t DRV_TS_GetX(void)
{
	return TS_State.X;
}

uint16_t DRV_TS_GetY(void)
{
	return DRV_Display_GetYSize() - TS_State.Y;
}
