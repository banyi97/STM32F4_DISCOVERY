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

#include "stm32f429i_discovery_lcd.h"

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
	c->Remaining = NUM_OF_COLS * NUM_OF_ROWS;
	c->BulletPosition.x = AREA_WIDTH/2 - BULLET_A/2;
	c->BulletPosition.y = BAR_HEIGHT;
	for(i = 0; i < NUM_OF_COLS; i++){
		for(j = 0; j < NUM_OF_ROWS; j++){
			c->Blocks[i][j].isActive = 1;
			c->Blocks[i][j].color = (((i+j)%2) ? LCD_COLOR_BLUE : LCD_COLOR_BLACK);
		}
	}
	c->BulletSpeed.speed_X = 0;
	c->BulletSpeed.speed_Y = 3;
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
	if(c->IsGameOver == 1){
		Window* win = GetBlocksWindow();
		win->ButtonsNum = 1;
	}
	// Print game area
	Pixel p;
	p.x = 0;
	p.y = 0;
	DRV_DrawRectangle(p, AREA_HEIGHT, AREA_WIDTH, black);

	uint32_t col = BSP_LCD_GetTextColor();
	// Print Blocks
	uint8_t i, j;
	for(i = 0; i < NUM_OF_COLS; i++){
		for(j = 0; j < NUM_OF_ROWS; j++){
			if(c->Blocks[i][j].isActive){
				p.x = i * BLOCK_WIDTH;
				p.y = 320-(BOTTOM_LINE + (j + 1) * BLOCK_HEIGHT);
				BSP_LCD_SetTextColor(c->Blocks[i][j].color);
				BSP_LCD_FillRect(p.x,p.y,BLOCK_WIDTH,BLOCK_HEIGHT);
				//DRV_FillRectangle(p, BLOCK_HEIGHT, BLOCK_WIDTH, c->Blocks[i][j].color);
			}
		}
	}
	BSP_LCD_SetTextColor(col);

	// Print Bar
	DRV_DrawHorizontalLine(c->BarPosition, BAR_LENGTH, black);
	// Print bullet
	DRV_FillRectangle(c->BulletPosition, BULLET_A, BULLET_A, red);

	// Print game time
	p.x = 235;
	p.y = 300;
	char time[20];
	uint32_t allsec = c->Tik / 100;
	uint16_t min = allsec / 60;
	uint8_t sec = allsec - (min*60);
	sprintf(time, "Rem:%d Time:%02d:%02d",c->Remaining, min, sec);
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
	static uint8_t crossedBar = 0;
	if(c->IsGameOver)
		return;
	if(dataState == 0){ // omega_x
		dataState = 1;
		int16_t y = c->BulletPosition.y;
		y += c->BulletSpeed.speed_Y;
		if(y < 0){
			y = 0;
			c->BulletPosition.y = 0;
			c->IsGameOver = 1;
			c->NeedToDraw = 1;
			dataState = 0;
			return;
		}
		else if(y > (AREA_HEIGHT - BULLET_A)){
			y = AREA_HEIGHT - BULLET_A;
			collideWithHorizontal(c);
		}
		else if((y + BULLET_A) >= BOTTOM_LINE && y <= TOP_LINE){
			//ha alulról átlépegy határt
			if((y + BLOCK_HEIGHT + BULLET_A - BOTTOM_LINE)/BLOCK_HEIGHT - (c->BulletPosition.y + BLOCK_HEIGHT + BULLET_A - BOTTOM_LINE)/BLOCK_HEIGHT == 1 && y + BULLET_A < TOP_LINE){
				c->BulletPosition.y = y;
				collideFromBottom(c);
			}
			//ha fölülről átlép egy határt
			if((c->BulletPosition.y - BOTTOM_LINE)/BLOCK_HEIGHT - (y - BOTTOM_LINE)/BLOCK_HEIGHT == 1 && y > BOTTOM_LINE){
				c->BulletPosition.y = y;
				collideFromTop(c);
			}
		}
		//ha átlépi a bar vonalát
		if(y <= BAR_HEIGHT && c->BulletPosition.y > BAR_HEIGHT){
			crossedBar = 1;
		}
		c->BulletPosition.y = y;
	}
	else if(dataState == 1){ // omega_y
		dataState = 2;
		int16_t x = c->BulletPosition.x;
		//int16_t y = c->BulletPosition.y;
		x += c->BulletSpeed.speed_X;
		if(x <= 0 || x > (AREA_WIDTH - BULLET_A)){
			collideWithVertical(c);
			if(x < 0) x = 0;
			if(x > AREA_WIDTH - BULLET_A) x = AREA_WIDTH - BULLET_A;
		}
		else if((c->BulletPosition.y + BULLET_A) >= BOTTOM_LINE && c->BulletPosition.y <= TOP_LINE){
			//ha balról lép át egy határt
			if((x + BULLET_A)/BLOCK_WIDTH - (c->BulletPosition.x + BULLET_A)/BLOCK_WIDTH == 1 ){
				c->BulletPosition.x = x;
				collideFromLeft(c);
			}
			//ha jobbról lép át egy határt
			if(c->BulletPosition.x/BLOCK_WIDTH - x/BLOCK_WIDTH == 1 ){
				c->BulletPosition.x = x;
				collideFromRight(c);
			}
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
		c->BarPosition.x = x;
		//ha találkozott a bar-ral
		if(crossedBar && c->BulletPosition.x + BULLET_A > x && c->BulletPosition.x - BULLET_A < x + BAR_LENGTH){
			collideWithBar(c);
			crossedBar = 0;
		}
	}
	else if(dataState == 2){ // omega_z
		dataState = 0;
		// Set print flag
		c->NeedToDraw = 1;
		// Cntr time
		++c->Tik;
		// Check for collision							//már megtörtént
		/*switch (checkCollision(c)){
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
		//check if hits bar								//ez is
		if(c->BulletPosition.y < BAR_HEIGHT + 4 && c->BulletPosition.y > BAR_HEIGHT - 1 && c->BulletSpeed.speed_Y < 0){
			if((c->BulletPosition.x + BULLET_A/2) > c->BarPosition.x && c->BulletPosition.x < (c->BarPosition.x + BAR_LENGTH)){
				collideWithBar(c);
			}
		}*/

		if(c->Remaining == 0){
			c->IsGameOver = 1;
			return;
		}
	}
}

/*Collision checkCollision(Blockgame* game){
	if((game->BulletPosition.y + BULLET_A) >= BOTTOM_LINE && game->BulletPosition.y <= TOP_LINE){
		//collide horizontally
		if((game->BulletPosition.y + BULLET_A/2) % BLOCK_HEIGHT <= BULLET_A){
			if(game->BulletSpeed.speed_Y > 0){
				return fromBottom;
			}
			else{
				return fromTop;
			}
		}
		//collide vertically
		if((game->BulletPosition.x + BULLET_A/2) % BLOCK_WIDTH <= BULLET_A){
			if(game->BulletSpeed.speed_X > 0){
				return fromLeft;
			}
			else{
				if(game->BulletSpeed.speed_X < 0){
					return fromRight;
				}
			}
		}
	}
	return none;
}*/

uint8_t collideFromBottom(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x;
	p.y = game->BulletPosition.y;
	int16_t i = (p.x + BULLET_A/2)/BLOCK_WIDTH;
	int16_t j = (p.y + BULLET_A - BOTTOM_LINE)/BLOCK_HEIGHT;
	if(j >= 0 && j < NUM_OF_ROWS && game->Blocks[i][j].isActive){
		game->Blocks[i][j].isActive = 0;
		collideWithHorizontal(game);
		game->Remaining -= 1;
		return  1;
	}
	return 0;
}

uint8_t collideFromTop(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x;
	p.y = game->BulletPosition.y;
	int16_t i = (p.x + BULLET_A/2)/BLOCK_WIDTH;
	int16_t j = (p.y - BOTTOM_LINE)/BLOCK_HEIGHT;
	if(j >= 0 && j < NUM_OF_ROWS && game->Blocks[i][j].isActive){
		game->Blocks[i][j].isActive = 0;
		collideWithHorizontal(game);
		game->Remaining -= 1;
		return  1;
	}
	return 0;
}

uint8_t collideFromLeft(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x;
	p.y = game->BulletPosition.y;
	int16_t i = (p.x + BULLET_A)/BLOCK_WIDTH;
	int16_t j = (p.y + BULLET_A/2 - BOTTOM_LINE)/BLOCK_HEIGHT;
	if(i >= 0 && i < NUM_OF_COLS && game->Blocks[i][j].isActive){
		game->Blocks[i][j].isActive = 0;
		collideWithVertical(game);
		game->Remaining -= 1;
		return  1;
	}
	return 0;
}

uint8_t collideFromRight(Blockgame* game){
	Pixel p;
	p.x = game->BulletPosition.x;
	p.y = game->BulletPosition.y;
	int16_t i = p.x/BLOCK_WIDTH;
	int16_t j = (p.y + BULLET_A/2 - BOTTOM_LINE)/BLOCK_HEIGHT;
	if(i >= 0 && i < NUM_OF_COLS && game->Blocks[i][j].isActive){
		game->Blocks[i][j].isActive = 0;
		collideWithVertical(game);
		game->Remaining -= 1;
		return  1;
	}
	return 0;
}

void collideWithHorizontal(Blockgame* game){
	game->BulletSpeed.speed_Y = 0-game->BulletSpeed.speed_Y;
	game->BulletSpeed.speed_X = game->BulletSpeed.speed_X;
}

void collideWithVertical(Blockgame* game){
	game->BulletSpeed.speed_X = 0-game->BulletSpeed.speed_X;
	game->BulletSpeed.speed_Y = game->BulletSpeed.speed_Y;
}

void collideWithBar(Blockgame* game){
	game->BulletSpeed.speed_Y = 0-game->BulletSpeed.speed_Y;
	int32_t speedx = game->BulletSpeed.speed_X + game->BarSpeed.speed_X/2;
	if(speedx < -6) speedx = -6;
	if(speedx > 6) speedx = 6;
	game->BulletSpeed.speed_X = speedx;
}

