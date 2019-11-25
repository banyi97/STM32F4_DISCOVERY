/*
 * SpectrumWindow.c
 *
 *  Created on: 2016 nov. 3
 *      Author: Nagy Ákos
 */

#include "SpectrumWindow.h"
#include "MenuWindow.h"
#include "WindowManager.h"
#include <string.h>

Window SpectrumWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void SpectrumNewData(void* args, uint32_t argsN);

Window* GetSpectrumWindow()
{
	return &SpectrumWindow;
}

void InitSpectrumWindow()
{
	//Labels
	SpectrumWindow.LabelsNum = 1;
	Label* Caption = &SpectrumWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 300;
	strcpy(Caption->Label, "Spectrum");

	//Buttons
	SpectrumWindow.ButtonsNum = 1;
	Button* MenuBtn = &SpectrumWindow.Buttons[0];
	MenuBtn->OnClick = &MenuButtonOnClick;
	strcpy(MenuBtn->Label.Label, "Menu");
	MenuBtn->Size.x = 70;
	MenuBtn->Size.y = 30;
	MenuBtn->Position.x = 15;
	MenuBtn->Position.y = 15;

	//Spectrum
	SpectrumWindow.SpectrumActive = 1;
	Spectrum* c = &SpectrumWindow.Spectrum;
	c->OnNewData = &SpectrumNewData;
	c->Position.x = 0;
	c->Position.y = 70;
	c->Size.x = 200;
	c->Size.y = 200;

	SpectrumWindow.CompassActive = 0;
	SpectrumWindow.ConsoleActive = 0;
	SpectrumWindow.ChartActive = 0;
}


static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetMenuWindow());
}

static void SpectrumNewData(void* args, uint32_t argsN)
{
	DataPacket* msg = args;
	Spectrum* c = &SpectrumWindow.Spectrum;

	for (uint32_t i = 0; i < argsN; ++i)
		UpdateSpectrumData(c, msg[i].Data);
}

