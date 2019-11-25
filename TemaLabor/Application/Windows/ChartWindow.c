/*
 * ChartWindow.c
 *
 *  Created on: 2016 okt. 21
 *      Author: Nagy Ákos
 */

#include "ChartWindow.h"
#include "MenuWindow.h"
#include "WindowManager.h"
#include <string.h>

Window ChartWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void ChartNewData(void* args, uint32_t argsN);
static void ChartXPlusOnClick(void* args, uint32_t argsN);
static void ChartXMinusOnClick(void* args, uint32_t argsN);
static void ChartYPlusOnClick(void* args, uint32_t argsN);
static void ChartYMinusOnClick(void* args, uint32_t argsN);

Window* GetChartWindow()
{
	return &ChartWindow;
}

void InitChartWindow()
{
	//Labels
	ChartWindow.LabelsNum = 2;
	Label* Caption = &ChartWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 300;
	strcpy(Caption->Label, "Chart");

	Label* ScaleLbl = &ChartWindow.Labels[1];
	ScaleLbl->Position.x = 152;
	ScaleLbl->Position.y = 40;
	strcpy(ScaleLbl->Label, "Scale:");

	//Buttons
	ChartWindow.ButtonsNum = 5;
	Button* MenuBtn = &ChartWindow.Buttons[0];
	MenuBtn->OnClick = &MenuButtonOnClick;
	strcpy(MenuBtn->Label.Label, "Menu");
	MenuBtn->Size.x = 70;
	MenuBtn->Size.y = 30;
	MenuBtn->Position.x = 15;
	MenuBtn->Position.y = 15;

	//Chart Buttons
	Button* ChartXPlusBtn = &ChartWindow.Buttons[1];
	ChartXPlusBtn->OnClick = &ChartXPlusOnClick;
	strcpy(ChartXPlusBtn->Label.Label, "+");
	ChartXPlusBtn->Size.x = 20;
	ChartXPlusBtn->Size.y = 20;
	ChartXPlusBtn->Position.x = 120;
	ChartXPlusBtn->Position.y = 10;

	Button* ChartXMinusBtn = &ChartWindow.Buttons[2];
	ChartXMinusBtn->OnClick = &ChartXMinusOnClick;
	strcpy(ChartXMinusBtn->Label.Label, "-");
	ChartXMinusBtn->Size.x = 20;
	ChartXMinusBtn->Size.y = 20;
	ChartXMinusBtn->Position.x = 142;
	ChartXMinusBtn->Position.y = 10;

	Button* ChartYPlusBtn = &ChartWindow.Buttons[3];
	ChartYPlusBtn->OnClick = &ChartYPlusOnClick;
	strcpy(ChartYPlusBtn->Label.Label, "+");
	ChartYPlusBtn->Size.x = 20;
	ChartYPlusBtn->Size.y = 20;
	ChartYPlusBtn->Position.x = 168;
	ChartYPlusBtn->Position.y = 10;

	Button* ChartYMinusBtn = &ChartWindow.Buttons[4];
	ChartYMinusBtn->OnClick = &ChartYMinusOnClick;
	strcpy(ChartYMinusBtn->Label.Label, "-");
	ChartYMinusBtn->Size.x = 20;
	ChartYMinusBtn->Size.y = 20;
	ChartYMinusBtn->Position.x = 190;
	ChartYMinusBtn->Position.y = 10;

	//Chart
	ChartWindow.ChartActive = 1;
	Chart* c = &ChartWindow.Chart;
	c->OnNewData = &ChartNewData;
	c->Position.x = 0;
	c->Position.y = 70;
	c->Size.x = 200;
	c->Size.y = 200;
	c->Xstep = 1.0;
	c->YScale = 0.03;
	c->Factor = 0.2;

	ChartWindow.CompassActive = 0;
	ChartWindow.ConsoleActive = 0;
}


static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetMenuWindow());
}

static void ChartNewData(void* args, uint32_t argsN)
{
	DataPacket* msg = args;
	Chart* c = &ChartWindow.Chart;

	for (uint32_t i = 0; i < argsN; ++i)
		UpdateChartData(c, msg[i].Data);
}

static void ChartXPlusOnClick(void* args, uint32_t argsN)
{
	Chart* c = &ChartWindow.Chart;
	c->Xstep *= 1.1;
	if (c->Xstep > 30.0f)
		c->Xstep = 30.0f;
}
static void ChartXMinusOnClick(void* args, uint32_t argsN)
{
	Chart* c = &ChartWindow.Chart;
	c->Xstep *= 0.9;
	if (c->Xstep < 1.0f)
		c->Xstep = 1.0f;
}
static void ChartYPlusOnClick(void* args, uint32_t argsN)
{
	Chart* c = &ChartWindow.Chart;
	c->YScale *= 1.1;
	if (c->YScale > 10.0f)
		c->YScale = 10.0f;
}
static void ChartYMinusOnClick(void* args, uint32_t argsN)
{
	Chart* c = &ChartWindow.Chart;
	c->YScale *= 0.9;
	if (c->YScale < 0.001f)
		c->YScale = 0.001f;
}

