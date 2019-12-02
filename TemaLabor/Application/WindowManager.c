/*
 * WindowManager.c
 *
 *  Created on: 2016 okt. 21
 *      Author: Nagy �kos
 */

#include "WindowManager.h"
#include "ChartWindow.h"
#include "CompassWindow.h"
#include "MenuWindow.h"
#include "SetupWindow.h"
#include "ConsoleWindow.h"
#include "HistogramWindow.h"
#include "SpectrumWindow.h"

#include "GameWindow.h"
#include "BlocksWindow.h"

Window* ActiveWindow = 0;

static uint8_t IsInnerPoint(Button* btn, Pixel p);

void InitWindowManager(void)
{
	//Init windows
	InitChartWindow();
	InitMenuWindow();
	InitCompassWindow();
	InitSetupWindow();
	InitConsoleWindow();
	InitHistogramWindow();
	InitSpectrumWindow();

	InitGameWindow();
	InitBlocksWindow();

	//Set startup window
	SetActiveWindow(GetSetupWindow());
}

void SetActiveWindow(Window* w)
{
	ActiveWindow = w;

	//Init window
	InitWindow(w);
}

void HandleTouch(int TouchX, int TouchY)
{
	Pixel p;
	p.x = TouchX;
	p.y = TouchY;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		for (uint32_t i = 0; i < ActiveWindow->ButtonsNum; ++i)
		{
			if (IsInnerPoint(&ActiveWindow->Buttons[i], p))
			{
				ActiveWindow->Buttons[i].OnClick(0,0);
				break;
			}
		}
	}
}

uint8_t IsInnerPoint(Button* btn, Pixel p)
{
	if ((p.x < btn->Position.x) || ((btn->Position.x + btn->Size.x) < p.x))
		return 0;

	if ((p.y < btn->Position.y) || ((btn->Position.y + btn->Size.y) < p.y))
		return 0;

	return 1;
}

void HandleString(char* str)
{
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->ConsoleActive > 0)
			ActiveWindow->Console.OnNewData(str, 1);
	}
}

void HandleChart(int32_t data){
	DataPacket d;
	d.Data = data;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->ChartActive > 0)
			ActiveWindow->Chart.OnNewData(&d, 1);
	}
}

void HandleCompass(int32_t data){
	DataPacket d;
	d.Data = data;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->CompassActive > 0)
			ActiveWindow->Compass.OnNewData(&d,1);
	}
}

void HandleHistogram(int32_t data){
	DataPacket d;
	d.Data = data;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->HistogramActive > 0)
			ActiveWindow->Histogram.OnNewData(&d,1);
	}
}

void HandleSpectrum(float data){
	DataPacket d;
	d.Data = data;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->SpectrumActive > 0)
			ActiveWindow->Spectrum.OnNewData(&d,1);
	}
}

void HandleGame(gyro_t data){
	DataPacket d[3];
	d[0].Data = data.omega_x;
	d[1].Data = data.omega_y;
	d[2].Data = data.omega_z;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->GameActive > 0)
			ActiveWindow->Game.OnNewData(&d,3);
	}
}

void HandleBlockGame(gyro_t data){
	DataPacket d[3];
	d[0].Data = data.omega_x;
	d[1].Data = data.omega_y;
	d[2].Data = data.omega_z;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->BlocksActive > 0)
			ActiveWindow->Blocks.OnNewData(&d,3);
	}
}

void HandleNewData(DataPacket* d)
{
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->ChartActive > 0)
			ActiveWindow->Chart.OnNewData(d, 1);
		if (ActiveWindow->CompassActive > 0)
			ActiveWindow->Compass.OnNewData(d,1);
		if (ActiveWindow->HistogramActive > 0)
			ActiveWindow->Histogram.OnNewData(d,1);
		if (ActiveWindow->SpectrumActive > 0)
			ActiveWindow->Spectrum.OnNewData(d,1);
		//
		if (ActiveWindow->GameActive > 0)
			ActiveWindow->Game.OnNewData(d,1);
		if (ActiveWindow->BlocksActive > 0)
			ActiveWindow->Blocks.OnNewData(d,1);
	}
}

uint8_t HandleDraw(void)
{
	if (ActiveWindow != 0)
	{
		return DrawWindow(ActiveWindow);
	}
	return 0;
}
