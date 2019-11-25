/*
 * Console.h
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy Ákos
 */

#ifndef CONTROLS_CONSOLE_H_
#define CONTROLS_CONSOLE_H_

#include "BasicControls.h"

typedef struct
{
	uint8_t		NeedToDraw;
	Event 		OnNewData;
	//Data
	Label		Rows[20];
	uint32_t	NumberOfRows; //Based on Size, Position
	uint32_t	NumberOfChar; //Based on Size, DRV_Display_GetFontXSize()
	uint32_t	Pointer; //Pointer to the current row
	//Appearance
	Pixel		Position;
	Pixel		Size;
} Console;

/**
 * Init console:
 * 	Initialize the necessary variables of the Console structure.
 * @param Pointer to a Console structure.
 * @return None.
 */
void InitConsole(Console* c);

/**
 * Draw console:
 * 	Use DRV Display/Drawing functions
 * 	Reset NeedToDraw flag
 * @param Pointer to a Console structure.
 * @return None.
 */
void DrawConsole(Console* c);

/**
 * Clear console:
 *  Clear Rows's labels
 *  Reset pointer
 * 	Set NeedToDraw flag
 * @param Pointer to a Console structure.
 * @return None.
 */
void ClearConsole(Console* c);

/**
 * Append a substring to the console
 *  Insert line break when necessary
 *  Clear console after last row
 * @param Pointer to a Console structure, string to append, number of chars to append.
 * @return None.
 */
void AppendLine(Console* c, char* str, uint32_t num);

/**
 * Update console data with a string:
 *  Insert new line at '\r' or '\n'
 *  Clear console after last row
 *  Append string with AppendLine static function
 * 	Set NeedToDraw flag
 * @param Pointer to a Console structure, null-terminated string.
 * @return None.
 */
void UpdateConsole(Console* c, char* str);

#endif /* CONTROLS_CONSOLE_H_ */
