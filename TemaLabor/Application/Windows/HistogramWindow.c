/*
 * HistogramWindow.c
 *
 *  Created on: 2016 nov. 1
 *      Author: Nagy Ákos
 */
#include "HistogramWindow.h"
#include "MenuWindow.h"
#include "WindowManager.h"

#include <string.h>

Window HistogramWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void HistogramNewData(void* args, uint32_t argsN);

Window* GetHistogramWindow()
{
	return &HistogramWindow;
}

void InitHistogramWindow()
{
	//Labels
	HistogramWindow.LabelsNum = 1;
	Label* Caption = &HistogramWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 300;
	strcpy(Caption->Label, "Histogram");

	//Buttons
	HistogramWindow.ButtonsNum = 1;
	Button* MenuBtn = &HistogramWindow.Buttons[0];
	MenuBtn->OnClick = &MenuButtonOnClick;
	strcpy(MenuBtn->Label.Label, "Menu");
	MenuBtn->Size.x = 70;
	MenuBtn->Size.y = 30;
	MenuBtn->Position.x = 15;
	MenuBtn->Position.y = 15;

	//Histogram
	HistogramWindow.HistogramActive = 1;
	Histogram* c = &HistogramWindow.Histogram;
	c->OnNewData = &HistogramNewData;
	c->Position.x = 0;
	c->Position.y = 70;
	c->Size.x = 200;
	c->Size.y = 200;
	c->Xmin = -500;
	c->Xmax = 500;
	c->Ymax = 30;

	HistogramWindow.CompassActive = 0;
	HistogramWindow.ConsoleActive = 0;
	HistogramWindow.ChartActive = 0;
}


static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetMenuWindow());
}

static void HistogramNewData(void* args, uint32_t argsN)
{
	DataPacket* msg = args;
	Histogram* c = &HistogramWindow.Histogram;

	for (uint32_t i = 0; i < argsN; ++i)
		UpdateHistogramData(c, msg[i].Data);
}
