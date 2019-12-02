/*
 * BlocksWindow.c
 *
 *  Created on: Dec 1, 2019
 *      Author: User
 */
#include "MenuWindow.h"
#include "WindowManager.h"

#include "Blocks.h"
#include "BlocksWindow.h"

Window BlocksWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void BlocksNewData(void* args, uint32_t argsN);

Window* GetBlocksWindow()
{
	return &BlocksWindow;
}

void InitBlocksWindow()
{
	// Dynamic label print in controls - game.c

	// Buttons
	BlocksWindow.ButtonsNum = 1;
	Button* BlocksBtn = &BlocksWindow.Buttons[0];
	BlocksBtn->OnClick = &MenuButtonOnClick;
	strcpy(BlocksBtn->Label.Label, "Go to menu");
	BlocksBtn->Size.x = 150;
	BlocksBtn->Size.y = 30;
	BlocksBtn->Position.x = DRV_Display_GetXSize()/2 - BlocksBtn->Size.x/2;
	BlocksBtn->Position.y = 30;

	// Game
	BlocksWindow.BlocksActive = 1;
	Blockgame* c = &BlocksWindow.Blocks;
	c->OnNewData = &BlocksNewData;
	c->Position.x = 0;
	c->Position.y = 70;
	c->Size.x = 200;
	c->Size.y = 200;

	BlocksWindow.CompassActive = 0;
	BlocksWindow.ConsoleActive = 0;
	BlocksWindow.ChartActive = 0;
	BlocksWindow.SpectrumActive = 0;
	BlocksWindow.GameActive = 0;
}

static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetMenuWindow());
}

static void BlocksNewData(void* args, uint32_t argsN)
{
	DataPacket* msg = args;
	Blockgame* c = &BlocksWindow.Blocks;
	for (uint32_t i = 0; i < argsN; ++i)
		UpdateBlockGameData(c, msg[i].Data);
}
