/*
 * display.c
 *
 *  Created on: 2016 okt. 26
 *      Author: Gabor
 */

#include <stm32f429i_discovery.h>
#include <stm32f429i_discovery_lcd.h>
#include <string.h>
#include "display.h"

uint8_t ActiveFrame;

#define LCD_FRAME_BUFFER0                  LCD_FRAME_BUFFER
#define LCD_FRAME_BUFFER1                  (LCD_FRAME_BUFFER+0x100000)

void DRV_Display_Init(void)
{
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER0);
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER1);

	BSP_LCD_SelectLayer(0);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font16);

	BSP_LCD_SetLayerVisible(1, DISABLE);
	BSP_LCD_SetLayerVisible(0, ENABLE);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font16);
	ActiveFrame = 1;

	BSP_LCD_DisplayOn();
}

void DRV_Display_SwitchBuffer(void)
{
	if (ActiveFrame == 1)
	{
		ActiveFrame = 0;
		BSP_LCD_SetLayerVisible_NoReload(0, DISABLE);
		BSP_LCD_SetLayerVisible_NoReload(1, ENABLE);
		BSP_LCD_SelectLayer(0);
	}
	else
	{
		ActiveFrame = 1;
		BSP_LCD_SetLayerVisible_NoReload(1, DISABLE);
		BSP_LCD_SetLayerVisible_NoReload(0, ENABLE);
		BSP_LCD_SelectLayer(1);
	}
	BSP_LCD_Relaod(LCD_RELOAD_VERTICAL_BLANKING);
}

void DRV_Display_Clear(void)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);
}

void DRV_Display_DrawPixel(uint16_t x, uint16_t y, uint32_t rgbCode)
{
	y = BSP_LCD_GetYSize() - y;
	BSP_LCD_DrawPixel(x, y, rgbCode);
}

void DRV_Display_WriteStringAt(Pixel p, char * str, TextAlignment align)
{
	uint16_t len = strlen(str);
	sFONT *font = BSP_LCD_GetFont();

	p.y = BSP_LCD_GetYSize() - p.y;

	switch (align) {
		case ALIGN_Left:
			p.y -= font->Height;
			break;
		case ALIGN_Center:
			p.x -= (len * font->Width) / 2;
			p.y -= font->Height / 2 - 2;
			break;
		case ALIGN_Right:
			p.x -= (len * font->Width);
			p.y -= font->Height;
			break;
		default:
			break;
	}
	BSP_LCD_DisplayStringAt(p.x, p.y, (uint8_t*)str, LEFT_MODE);
}

void DRV_Display_WriteIntAt(Pixel p, int num, TextAlignment	align)
{
	char lbl[30];
	sprintf(lbl, "%d", num);
	DRV_Display_WriteStringAt(p, lbl , align);
}

uint16_t DRV_Display_GetXSize(void)
{
	return BSP_LCD_GetXSize();
}

uint16_t DRV_Display_GetYSize(void)
{
	return BSP_LCD_GetYSize();
}

uint16_t DRV_Display_GetFontXSize(void)
{
	return BSP_LCD_GetFont()->Width;
}
