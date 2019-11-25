/*
 * CompassWindow.c
 *
 *  Created on: 2016 okt. 27
 *      Author: Nagy Ákos
 */


#include "CompassWindow.h"
#include "MenuWindow.h"
#include "WindowManager.h"
#include "Common.h"
#include <string.h>

Window CompassWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void ZeroButtonOnClick(void* args, uint32_t argsN);
static void CompassNewData(void* args, uint32_t argsN);

Window* GetCompassWindow()
{
	return &CompassWindow;
}

void InitCompassWindow()
{
	//Labels
	CompassWindow.LabelsNum = 1;
	Label* Caption = &CompassWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 300;
	strcpy(Caption->Label, "Compass");

	//Buttons
	CompassWindow.ButtonsNum = 2;
	Button* MenuBtn = &CompassWindow.Buttons[0];
	MenuBtn->OnClick = &MenuButtonOnClick;
	strcpy(MenuBtn->Label.Label, "Menu");
	MenuBtn->Size.x = 70;
	MenuBtn->Size.y = 30;
	MenuBtn->Position.x = 15;
	MenuBtn->Position.y = 15;

	Button* ZeroBtn = &CompassWindow.Buttons[1];
	ZeroBtn->OnClick = &ZeroButtonOnClick;
	strcpy(ZeroBtn->Label.Label, "Zero");
	ZeroBtn->Size.x = 70;
	ZeroBtn->Size.y = 30;
	ZeroBtn->Position.x = 100;
	ZeroBtn->Position.y = 15;

	CompassWindow.CompassActive = 1;
	Compass* Compass = &CompassWindow.Compass;
	Compass->OnNewData = &CompassNewData;
	Compass->Factor = 0.85;
	Compass->Position.x = DRV_Display_GetXSize()/2;
	Compass->Position.y = DRV_Display_GetYSize()/2;
	Compass->Length = 80;

	CompassWindow.ChartActive = 0;
	CompassWindow.ConsoleActive = 0;
}


static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetMenuWindow());
}

static void ZeroButtonOnClick(void* args, uint32_t argsN)
{
	CompassWindow.Compass.Heading = 0.0;
}

static void CompassNewData(void* args, uint32_t argsN)
{
	DataPacket* msg = args;
	Compass* c = &CompassWindow.Compass;

	if (argsN > 0)
	{
		UpdateCompassData(c, msg[0].Data);
	}
}
