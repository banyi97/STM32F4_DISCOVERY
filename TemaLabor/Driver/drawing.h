/*
 * drawing.h
 *
 *  Created on: 2016 okt. 26
 *      Author: Gabor
 */

#ifndef DRAWING_H_
#define DRAWING_H_

#include <stdint.h>

typedef struct Pixel {
	int16_t x;
	int16_t y;
} Pixel;

typedef struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} Color;

/**
 * Draws a line relative to start position with color
 * @param start beginning of the line
 * @param distanceX X length of the line
 * @param distanceY Y length of the line
 * @param color specifies the color of the line
 */
void DRV_DrawRelLine(Pixel start, uint16_t distanceX, uint16_t distanceY, Color color);

/**
 * Draws a line from start to end with color
 * @param start beginning of the line
 * @param end goal position of the line
 * @param color specifies the color of the line
 */
void DRV_DrawLine(Pixel start, Pixel end, Color color);

/**
 * Draws a horizontal line from start with the specified length
 * @param start specifies the start position of the line
 * @param length specifies the length of the line
 * @param color specifies the color
 */
void DRV_DrawHorizontalLine(Pixel start, int16_t length, Color color);

/**
 * Draws a vertical line from start with the specified length
 * @param start specifies the start position of the line
 * @param length specifies the length of the line
 * @param color specifies the color
 */
void DRV_DrawVerticalLine(Pixel start, int16_t length, Color color);

/**
 * Draws a rectangle at the specified location
 * @param p bottom left corner of the rectangle
 * @param height specifies the height of the rectangle
 * @param width specifies the width of the rectangle
 * @param color specifies the color of the rectangle
 */
void DRV_DrawRectangle(Pixel p, uint16_t height, uint16_t width, Color color);

/**
 * Draws a circle at the specified location with the specified color
 * @param center specifies the location of the circle's center
 * @param r specifies the radius of the circle
 * @param color specifies the color of the circle
 */
void DRV_DrawCircle(Pixel center, uint16_t r, Color color);

/**
 * Draws a filled rectangle at the specified position
 * @param p bottom left corner of the rectangle
 * @param height specifies the height of the rectangle
 * @param width specifies the width of the rectangle
 * @param color specifies the color of the rectangle
 */
void DRV_FillRectangle(Pixel p, uint16_t height, uint16_t width, Color color);

/**
 * Draws a filled circle at the specified position
 * @param center specifies the location of the circle's center
 * @param r specifies the radius of the circle
 * @param color specifies the color of the circle
 */
void DRV_FillCircle(Pixel center, uint16_t r, Color color);


#endif /* DRAWING_H_ */
