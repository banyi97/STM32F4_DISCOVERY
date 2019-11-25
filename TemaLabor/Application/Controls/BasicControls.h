/*
 * BasicControls.h
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy Ákos
 */

#ifndef CONTROLS_BASICCONTROLS_H_
#define CONTROLS_BASICCONTROLS_H_

#include <stdint.h>
#include "drawing.h"
#include "display.h"

typedef void (*Event)(void* args, uint32_t argsN);


typedef struct
{
	uint8_t		NeedToDraw;
	Pixel		Position;
	uint8_t		LeftAlign;
	char		Label[40];
} Label;

typedef struct
{
	uint8_t		NeedToDraw;
	Event 		OnClick;
	Pixel		Position;
	Pixel		Size;
	Label		Label;
} Button;

extern Color white;
extern Color blue;
extern Color red;
extern Color green;
extern Color black;

/**
 * Init label:
 * 	Initialize the necessary variables of the Label structure.
 * @param Pointer to a Label structure.
 * @return None.
 */
void InitLabel(Label* btn);

/**
 * Draw label:
 *  Draw using DRV_Display_WriteStringAt
 * 	Reset NeedToDraw flag
 * @param Pointer to a Label structure.
 * @return None.
 */
void DrawLabel(Label* lbl);

/**
 * Init button:
 * 	Initialize the necessary variables of the Button structure.
 * @param Pointer to a Button structure.
 * @return None.
 */
void InitButton(Button* btn);

/**
 * Draw button:
 *  Draw using DRV_DrawRectangle, DrawLabel
 * 	Reset NeedToDraw flag
 * @param Pointer to a Button structure.
 * @return None.
 */
void DrawButton(Button* btn);

#endif /* CONTROLS_BASICCONTROLS_H_ */
