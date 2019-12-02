/*
 * Window.h
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy �kos
 */

#ifndef CONTROLS_WINDOW_H_
#define CONTROLS_WINDOW_H_

#include "BasicControls.h"
#include "Chart.h"
#include "Compass.h"
#include "Console.h"
#include "Histogram.h"
#include "Spectrum.h"

#include "Game.h"
#include "Blocks.h"

typedef struct
{
	Button		Buttons[5];
	uint32_t	ButtonsNum;
	Label		Labels[5];
	uint32_t	LabelsNum;
	Chart		Chart;
	uint8_t		ChartActive;
	Compass		Compass;
	uint8_t		CompassActive;
	Console		Console;
	uint8_t		ConsoleActive;
	Histogram	Histogram;
	uint8_t		HistogramActive;
	Spectrum	Spectrum;
	uint8_t		SpectrumActive;

	// Games
	Game		Game;
	uint8_t		GameActive;
	Blockgame	Blocks;
	uint8_t 	BlocksActive;

	uint8_t		NeedToDraw;
	uint8_t		DrawInProgress;
} Window;

void	InitWindow(Window* w);
uint8_t DrawWindow(Window* w);

#endif /* CONTROLS_WINDOW_H_ */
