/*
 * MenuWindow.c
 *
 *  Created on: 2016 okt. 21
 *      Author: Nagy �kos
 */

#include "ChartWindow.h"
#include "CompassWindow.h"
#include "WindowManager.h"
#include "ConsoleWindow.h"
#include "HistogramWindow.h"
#include "SpectrumWindow.h"
#include <string.h>

#include "Game.h"

Window MenuWindow;

static void CompassButtonOnClick(void* args, uint32_t argsN);
static void ChartButtonOnClick(void* args, uint32_t argsN);
static void ConsoleButtonOnClick(void* args, uint32_t argsN);
static void HistogramButtonOnClick(void* args, uint32_t argsN);
static void SpectrumButtonOnClick(void* args, uint32_t argsN);
static void GameButtonOnClick(void* args, uint32_t argsN);

Window* GetMenuWindow()
{
	return &MenuWindow;
}

void InitMenuWindow()
{
	//Labels
	MenuWindow.LabelsNum = 1;
	Label* Caption = &MenuWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 300;
	strcpy(Caption->Label, "Menu");

	//Buttons
	MenuWindow.ButtonsNum = 5;

	Button* ConsoleBtn = &MenuWindow.Buttons[0];
	ConsoleBtn->OnClick = &GameButtonOnClick;
	strcpy(ConsoleBtn->Label.Label, "Start Game");
	ConsoleBtn->Size.x = 180;
	ConsoleBtn->Size.y = 30;
	ConsoleBtn->Position.x = DRV_Display_GetXSize()/2 - ConsoleBtn->Size.x/2;
	ConsoleBtn->Position.y = 150;

	Button* CompassBtn = &MenuWindow.Buttons[1];
	CompassBtn->OnClick = &CompassButtonOnClick;
	strcpy(CompassBtn->Label.Label, "Compass Window");
	CompassBtn->Size.x = 180;
	CompassBtn->Size.y = 30;
	CompassBtn->Position.x = DRV_Display_GetXSize()/2 - CompassBtn->Size.x/2;
	CompassBtn->Position.y = 200;

	Button* ChartBtn = &MenuWindow.Buttons[2];
	ChartBtn->OnClick = &ChartButtonOnClick;
	strcpy(ChartBtn->Label.Label, "Chart Window");
	ChartBtn->Size.x = 180;
	ChartBtn->Size.y = 30;
	ChartBtn->Position.x = DRV_Display_GetXSize()/2 - ChartBtn->Size.x/2;
	ChartBtn->Position.y = 250;

	Button* HistogramBtn = &MenuWindow.Buttons[3];
	HistogramBtn->OnClick = &HistogramButtonOnClick;
	strcpy(HistogramBtn->Label.Label, "Histogram");
	HistogramBtn->Size.x = 180;
	HistogramBtn->Size.y = 30;
	HistogramBtn->Position.x = DRV_Display_GetXSize()/2 - HistogramBtn->Size.x/2;
	HistogramBtn->Position.y = 100;

	Button* SpectrumBtn = &MenuWindow.Buttons[4];
	SpectrumBtn->OnClick = &SpectrumButtonOnClick;
	strcpy(SpectrumBtn->Label.Label, "Spectrum");
	SpectrumBtn->Size.x = 180;
	SpectrumBtn->Size.y = 30;
	SpectrumBtn->Position.x = DRV_Display_GetXSize()/2 - SpectrumBtn->Size.x/2;
	SpectrumBtn->Position.y = 50;

	//Unused controls
	MenuWindow.ChartActive = 0;
	MenuWindow.CompassActive = 0;
	MenuWindow.ConsoleActive = 0;
}

static void CompassButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetCompassWindow());
}

static void ChartButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetChartWindow());
}

static void ConsoleButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetConsoleWindow());
}

static void HistogramButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetHistogramWindow());
}

static void SpectrumButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetSpectrumWindow());
}

static void GameButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetGameWindow());
}
