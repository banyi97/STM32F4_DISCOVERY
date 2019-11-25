/*
 * TextWindow.c
 *
 *  Created on: 2016 okt. 28
 *      Author: Nagy Ákos
 */

#include "ConsoleWindow.h"
#include "WindowManager.h"
#include "MenuWindow.h"
#include <string.h>

Window ConsoleWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void ClearButtonOnClick(void* args, uint32_t argsN);
static void ConsoleNewData(void* args, uint32_t argsN);

Window* GetConsoleWindow()
{
	return &ConsoleWindow;
}

void InitConsoleWindow()
{
	//Labels
	ConsoleWindow.LabelsNum = 1;
	Label* Caption = &ConsoleWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 300;
	strcpy(Caption->Label, "Console");

	//Buttons
	ConsoleWindow.ButtonsNum = 2;
	Button* MenuBtn = &ConsoleWindow.Buttons[0];
	MenuBtn->OnClick = &MenuButtonOnClick;
	strcpy(MenuBtn->Label.Label, "Menu");
	MenuBtn->Size.x = 70;
	MenuBtn->Size.y = 30;
	MenuBtn->Position.x = 15;
	MenuBtn->Position.y = 15;

	Button* ClearBtn = &ConsoleWindow.Buttons[1];
	ClearBtn->OnClick = &ClearButtonOnClick;
	strcpy(ClearBtn->Label.Label, "Clear");
	ClearBtn->Size.x = 70;
	ClearBtn->Size.y = 30;
	ClearBtn->Position.x = 100;
	ClearBtn->Position.y = 15;

	//Console
	ConsoleWindow.ConsoleActive = 1;
	Console* Console = &ConsoleWindow.Console;
	Console->Position.x = 15;
	Console->Position.y = 70;
	Console->Size.x = DRV_Display_GetXSize() - Console->Position.x*2;
	Console->Size.y = 215;
	Console->OnNewData = &ConsoleNewData;

	//Unused controls
	ConsoleWindow.ChartActive = 0;
	ConsoleWindow.CompassActive = 0;
}

static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetMenuWindow());
}

static void ClearButtonOnClick(void* args, uint32_t argsN)
{
	ClearConsole(&ConsoleWindow.Console);
}

static void ConsoleNewData(void* args, uint32_t argsN)
{
	UpdateConsole(&ConsoleWindow.Console, args);
}

