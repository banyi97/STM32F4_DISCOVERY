/*
 * BasicControls.c
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy Ákos
 */

#include "BasicControls.h"

Color white = {.red = 0xFF, .green = 0xFF, .blue = 0xFF };
Color blue = {.red = 0x00, .green = 0x00, .blue = 0xFF };
Color red = {.red = 0xFF, .green = 0x00, .blue = 0x00 };
Color green = {.red = 0x00, .green = 0xFF, .blue = 0x00 };
Color black = {.red = 0x00, .green = 0x00, .blue = 0x00 };

/*
 * Label
 */

void InitLabel(Label* lbl)
{
	lbl->NeedToDraw = 1;
}

void DrawLabel(Label* lbl)
{
	if (lbl->LeftAlign)
		DRV_Display_WriteStringAt(lbl->Position, lbl->Label, ALIGN_Left);
	else
		DRV_Display_WriteStringAt(lbl->Position, lbl->Label, ALIGN_Center);
	lbl->NeedToDraw = 0;
}

/*
 * Button
 */

void InitButton(Button* btn)
{
	btn->Label.Position.x = btn->Position.x + btn->Size.x/2;
	btn->Label.Position.y = btn->Position.y + btn->Size.y/2;
	btn->Label.LeftAlign = 0;
	btn->NeedToDraw = 1;
}

void DrawButton(Button* btn)
{
	DRV_DrawRectangle(btn->Position, btn->Size.y, btn->Size.x, black);
	DrawLabel(&btn->Label);
	btn->NeedToDraw = 0;
}
