/*
 * Blocks.c
 *
 *  Created on: Dec 1, 2019
 *      Author: atbar
 */

#include "Blocks.h"
#include "Game.h"
#include "display.h"
#include "drawing.h"
#include "BasicControls.h"

#include "BlocksWindow.h"

#include <stdio.h>
#include <math.h>

extern Color black;
extern Color red;
extern Color blue;
extern Color green;

void InitBlockGame(Blockgame* c){
	uint8_t i, j;
	c->NeedToDraw = 1;
	c->IsGameOver = 0;
	c->Tik = 0;
	c->Remaining = 32;
	c->BulletPosition.x = AREA_WIDTH/2 - BULLET_A/2;
	c->BulletPosition.y = BAR_HEIGHT;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 4; j++){
			c->Blocks[i][j].isActive = 1;
			c->Blocks[i][j].color = (((i+j)%2) ? blue : red);
		}
	}
	c->BulletSpeed.speed_X = 0;
	c->BulletSpeed.speed_Y = 5;
	c->BarPosition.x = AREA_WIDTH/2 - BAR_LENGTH/2;
	c->BarPosition.y = BAR_HEIGHT;
	c->BarSpeed.speed_X = 0;
	c->BarSpeed.speed_Y = 0;

	Window* win = GetBlocksWindow();
	win->ButtonsNum = 0;
}

void DrawBlockGame(Blockgame* c){
	c->NeedToDraw = 0;
	// Print or remove menu btn
	Window* win = GetBlocksWindow();
	if(c->IsGameOver == 1){
			win->ButtonsNum = 1;
	}

	// Print game area
	Pixel p;
	p.x = 0;
	p.y = 0;
	DRV_DrawRectangle(p, AREA_HEIGHT, AREA_WIDTH, black);

	// Print Blocks
	uint8_t i, j;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 4; j++){
			if(c->Blocks[i][j].isActive){
				p.x = i * BLOCK_WIDTH;
				p.y = BOTTOM_LINE + j * BLOCK_HEIGHT;
				DRV_FillRectangle(p, BLOCK_HEIGHT, BLOCK_WIDTH, c->Blocks[i][j].color);
			}
		}
	}
	// Print Bar
	DRV_DrawVerticalLine(c->BarPosition, BAR_LENGTH, black);
	// Print bullet
	DRV_FillRectangle(c->BulletPosition, BULLET_A, BULLET_A, black);

	// Print game time
	p.x = 235;
	p.y = 300;
	char time[24];
	uint32_t allsec = c->Tik / 100;
	uint16_t min = allsec / 60;
	uint8_t sec = allsec - (min*60);
	sprintf(time, "Remaining:%d Time:%02d:%02d",c->Remaining, min, sec);
	DRV_Display_WriteStringAt(p, time, ALIGN_Right);

}
// Gyro XYZ
//					x	(z)
//					x
//					x
//				   (0) xxxxxxxxxxxxxxxxxxxxx
//				x						(y)
//			x
//	(x)	x
//
//
void UpdateBlockGameData(Blockgame* c, int32_t val){
	static uint8_t dataState = 0;
	if(c->IsGameOver)
		return;
	if(dataState == 0){ // omega_x
		int16_t y = c->BulletPosition.y;
		y += c->BulletSpeed.speed_Y;
		if(y < 0){
			c->IsGameOver = 1;
			Window* win = GetBlocksWindow();
			win->Buttons[0].NeedToDraw = 1;
			return;
		}
		else if(y > (AREA_HEIGHT - BULLET_A)){
			collideWithHorizontal(c);
		}
		c->BulletPosition.y = y;

		dataState = 1;
	}
	else if(dataState == 1){ // omega_y
		int16_t x = c->BulletPosition.x;
		x += c->BulletSpeed.speed_X;
		if(x < 0 || x > (AREA_WIDTH - BULLET_A)){
			collideWithVertical(c);
		}
		c->BulletPosition.x = x;
		x = c->BarPosition.x;
		x += val / 9500;
		c->BarSpeed.speed_X = val / 9500;
		if(x < 0){
			x = 0;
			c->BarSpeed.speed_X = 0;
		}
		else if(x > (AREA_WIDTH - BAR_LENGTH)){
			x = AREA_WIDTH - BAR_LENGTH;
			c->BarSpeed.speed_X = 0;
		}
		c->BulletPosition.x = x;
		dataState = 2;
	}
	else if(dataState == 2){ // omega_z
		// Set print flag
		c->NeedToDraw = 1;
		// Cntr time
		++c->Tik;
		// Check for collision
		switch (checkCollision(c)){
			case none:
				break;
			case fromBottom:
				collideFromBottom(c);
				break;
			case fromTop:
				collideFromTop(c);
				break;
			case fromLeft:
				collideFromLeft(c);
				break;
			case fromRight:
				collideFromRight(c);
		}
		if(c->BulletPosition.y < BAR_HEIGHT && c->BulletSpeed.speed_Y < 0){
			if((c->BulletPosition.x + BULLET_A/2) > c->BarPosition.x && c->BulletPosition.x < (c->BarPosition.x + BAR_LENGTH)){
				collideWithBar(c);
			}
		}

		if(c->Remaining == 0){
			c->IsGameOver = 1;
			Window* win = GetBlocksWindow();
			win->Buttons[0].NeedToDraw = 1;
			return;
		}
		dataState = 0;
	}
}

Collision checkCollision(Blockgame* game){
	if(BOTTOM_LINE < game->BulletPosition.y && TOP_LINE > game->BulletPosition.y){
		if((game->BulletPosition.y + BULLET_A) % BLOCK_HEIGHT == 0 && game->BulletSpeed.speed_Y > 0)
			return fromBottom;
		if(game->BulletPosition.y % BLOCK_HEIGHT == 0 && game->BulletSpeed.speed_Y < 0)
			return fromTop;
		if((game->BulletPosition.x + BULLET_A) % BLOCK_WIDTH == 0 && game->BulletSpeed.speed_X > 0)
			return fromLeft;
		if((game->BulletPosition.x) % BLOCK_WIDTH == 0 && game->BulletSpeed.speed_X < 0)
			return fromRight;
	}
	return none;
}

uint8_t collideFromBottom(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x + BULLET_A/2;
	p.y = game->BulletPosition.y + BULLET_A/2;
	if(game->Blocks[p.x/BLOCK_WIDTH][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT + 1].isActive){
		game->Blocks[p.x/BLOCK_WIDTH][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT + 1].isActive = 0;
		collideWithHorizontal(game);
		return  1;
	}
	return 0;
}

uint8_t collideFromTop(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x + BULLET_A/2;
	p.y = game->BulletPosition.y + BULLET_A/2;
	if(game->Blocks[p.x/BLOCK_WIDTH][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT - 1].isActive){
		game->Blocks[p.x/BLOCK_WIDTH][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT - 1].isActive = 0;
		collideWithHorizontal(game);
		return  1;
	}
	return 0;
}

uint8_t collideFromLeft(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x + BULLET_A/2;
	p.y = game->BulletPosition.y + BULLET_A/2;
	if(game->Blocks[p.x/BLOCK_WIDTH + 1][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT].isActive){
		game->Blocks[p.x/BLOCK_WIDTH + 1][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT].isActive = 0;
		collideWithVertical(game);
		return  1;
	}
	return 0;
}

uint8_t collideFromRight(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x + BULLET_A/2;
	p.y = game->BulletPosition.y + BULLET_A/2;
	if(game->Blocks[p.x/BLOCK_WIDTH - 1][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT].isActive){
		game->Blocks[p.x/BLOCK_WIDTH - 1][(p.y - BOTTOM_LINE)/BLOCK_HEIGHT].isActive = 0;
		collideWithVertical(game);
		return  1;
	}
	return 0;
}

void collideWithHorizontal(Blockgame* game){
	game->BulletSpeed.speed_Y = -game->BulletSpeed.speed_Y;
}

void collideWithVertical(Blockgame* game){
	game->BulletSpeed.speed_X = -game->BulletSpeed.speed_X;
}

void collideWithBar(Blockgame* game){
	game->BulletSpeed.speed_Y = -game->BulletSpeed.speed_Y;
	game->BulletSpeed.speed_X = game->BulletSpeed.speed_X + game->BarSpeed.speed_X/2;
}

