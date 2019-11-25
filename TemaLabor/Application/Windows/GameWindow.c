/*
 * GameWindow.c
 *
 *  Created on: Nov 24, 2019
 *      Author: User
 */
#include "MenuWindow.h"
#include "WindowManager.h"
#include "Game.h"
#include "GameWindow.h"

Window GameWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void GameNewData(void* args, uint32_t argsN);

Window* GetGameWindow()
{
	return &GameWindow;
}

void InitGameWindow()
{
	// Dynamic label print in controls - game.c

	// Buttons
	GameWindow.ButtonsNum = 1;
	Button* GameBtn = &GameWindow.Buttons[0];
	GameBtn->OnClick = &MenuButtonOnClick;
	strcpy(GameBtn->Label.Label, "Go to menu");
	GameBtn->Size.x = 150;
	GameBtn->Size.y = 30;
	GameBtn->Position.x = DRV_Display_GetXSize()/2 - GameBtn->Size.x/2;
	GameBtn->Position.y = 30;

	// Game
	GameWindow.GameActive = 1;
	Game* c = &GameWindow.Game;
	c->OnNewData = &GameNewData;
	c->Position.x = 0;
	c->Position.y = 70;
	c->Size.x = 200;
	c->Size.y = 200;

	GameWindow.CompassActive = 0;
	GameWindow.ConsoleActive = 0;
	GameWindow.ChartActive = 0;
	GameWindow.SpectrumActive = 0;
}

static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	GameWindow.ButtonsNum = 0;
	SetActiveWindow(GetMenuWindow());
}

static void GameNewData(void* args, uint32_t argsN)
{
	DataPacket* msg = args;
	Game* c = &GameWindow.Game;
	for (uint32_t i = 0; i < argsN; ++i)
		UpdateGameData(c, msg[i].Data);
}
