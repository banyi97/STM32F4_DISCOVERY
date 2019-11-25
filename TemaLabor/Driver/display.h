/*
 * display.h
 *
 *  Created on: 2016 okt. 26
 *      Author: Gabor
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include "drawing.h"

typedef enum TextAlignment {
	ALIGN_Left = 0,
	ALIGN_Center,
	ALIGN_Right,
} TextAlignment;

/**
 * Initializes the display driver
 * @param None.
 * @return None.
 */
void DRV_Display_Init(void);

/**
 * Clears the display
 * @param None.
 * @return None.
 */
void DRV_Display_Clear(void);

/**
 * Switches between display buffers
 * @param None.
 * @return None.
 */
void DRV_Display_SwitchBuffer(void);

/**
 * Draws a pixel at (x,y) coordinate with the specified color (rgbCode)
 * @param x position of the drawn pixel
 * @param y position of the drawn pixel
 * @param rgbCode color of the pixel in 0xFFRRGGBB
 * where RR is the red, GG is the green and BB is the blue value respectively.
 */
void DRV_Display_DrawPixel(uint16_t x, uint16_t y, uint32_t rgbCode);

/**
 * Writes a string on the display at the specified position
 * @param p specifies the position of the string
 * @param str is the string to display
 * @param align specifies the text alignment relative to the position.
 */
void DRV_Display_WriteStringAt(Pixel p, char * str, TextAlignment align);

/**
 * Writes a number on the display at the specified position
 * @param p specifies the position of the number
 * @param num is the number to display
 * @param align specifies the text alignment relative to the position.
 */
void DRV_Display_WriteIntAt(Pixel p, int num, TextAlignment align);

/**
 * Get the X size of the display in pixels
 * @return The width of the display in pixels
 */
uint16_t DRV_Display_GetXSize(void);

/**
 * Get the Y size of the display in pixels
 * @return The height of the display in pixels
 */
uint16_t DRV_Display_GetYSize(void);

/**
 * Returns the used font's character width in pixels
 * @return The character width of the used font
 */
uint16_t DRV_Display_GetFontXSize(void);

#endif /* DISPLAY_H_ */
