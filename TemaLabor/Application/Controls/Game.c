/*
 * Game.c
 *
 *  Created on: Nov 24, 2019
 *      Author: User
 */
#include "Game.h"
#include "display.h"
#include "drawing.h"
#include "BasicControls.h"

#include "GameWindow.h"

#include <stdio.h>
#include <math.h>

extern Color black;
extern Color red;
extern Color blue;

void InitGame(Game* c){
	c->NeedToDraw = 1;
	c->IsGameOver = 0;
	c->EnemiesNum = 0;
	c->Tik = 0;
	c->Level = 0;
	c->BulletPosition.x = AREA_WIDTH/2;
	c->BulletPosition.y = AREA_HEIGHT/2;
	Pixel p;
	do{
		p.x = generateNewXCoordinate(TARGET_R);
		p.y = generateNewYCoordinate(TARGET_R);
	}while(checkTargetIsInBullet(&c->BulletPosition, &p) == 0);
	c->TargetPosition.x = p.x;
	c->TargetPosition.y = p.y;

	Window* win = GetGameWindow();
	win->ButtonsNum = 0;
}

void DrawGame(Game* c){
	c->NeedToDraw = 0;
	// Print menu btn
	if(c->IsGameOver == 1){
		Window* win = GetGameWindow();
		win->ButtonsNum = 1;
	}

	// Print game area
	Pixel p;
	p.x = 0;
	p.y = 0;
	DRV_DrawRectangle(p, AREA_HEIGHT, AREA_WIDTH, black);

	// Print bullet
	DRV_FillCircle(c->BulletPosition, BULLET_R, black);

	// Print game time
	p.x = 235;
	p.y = 300;
	char time[20];
	uint32_t allsec = c->Tik / 100;
	uint16_t min = allsec / 60;
	uint8_t sec = allsec - (min*60);
	sprintf(time, "Level:%02d Time:%02d:%02d",c->Level, min, sec);
	DRV_Display_WriteStringAt(p, time, ALIGN_Right);

	// Print target
	DRV_FillCircle(c->TargetPosition, TARGET_R, blue);

	// Print enemies
	uint8_t i;
	for(i = 0; i < c->EnemiesNum; ++i){
		DRV_FillCircle(c->Enemies[i], ENEMIE_R, red);
	}
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
void UpdateGameData(Game* c, int32_t val){
	static uint8_t dataState = 0;
	if(c->IsGameOver)
		return;
	if(dataState == 0){ // omega_x
		int16_t y = c->BulletPosition.y;
		y -= val / GYRO_CORRECTOR;
		if(y - BULLET_R < 0){
			y = BULLET_R;
		}
		else if(y > (AREA_HEIGHT - BULLET_R)){
			y = AREA_HEIGHT - BULLET_R;
		}
		c->BulletPosition.y = y;

		dataState = 1;
	}
	else if(dataState == 1){ // omega_y
		int16_t x = c->BulletPosition.x;
		x += val / GYRO_CORRECTOR;
		if(x - BULLET_R < 0){
			x = BULLET_R;
		}
		else if(x > (AREA_WIDTH - BULLET_R)){
			x = AREA_WIDTH - BULLET_R;
		}
		c->BulletPosition.x = x;
		dataState = 2;
	}
	else if(dataState == 2){ // omega_z
		// Set print flag
		c->NeedToDraw = 1;
		// Set next state
		dataState = 0;
		// Cntr time
		++c->Tik;
		// Check bullet and enemies contact
		for(uint8_t i = 0; i < c->EnemiesNum; ++i){
			if(catchBulletIsInEnemie(&c->BulletPosition, &c->Enemies[i]) == 0){
				c->IsGameOver = 1;
				return;
			}
		}

		if(catchTargetIsInBullet(&c->BulletPosition, &c->TargetPosition) == 0){
			++c->Level;
			if(c->Level > 99){
				c->Level = 99;
			}
			uint8_t level = c->Level / 4;
			c->EnemiesNum = level > 15 ? 15 : level;
			Pixel p;
			do{
				p.x = generateNewXCoordinate(TARGET_R);
				p.y = generateNewYCoordinate(TARGET_R);
			}while(checkTargetIsInBullet(&c->BulletPosition, &p) == 0);
			c->TargetPosition.x = p.x;
			c->TargetPosition.y = p.y;
			for(uint8_t i = 0; i < c->EnemiesNum; ++i){
				do{
					p.x = generateNewXCoordinate(ENEMIE_R);
					p.y = generateNewYCoordinate(ENEMIE_R);
				}while(checkBulletIsInEnemie(&c->BulletPosition, &p) == 0 || checkTargetIsInEnemie(&c->TargetPosition, &p) == 0);
				c->Enemies[i].x = p.x;
				c->Enemies[i].y = p.y;
			}
		}
	}
}

uint8_t catchTargetIsInBullet(Pixel* bull, Pixel* targ){
	if(
			((bull->x - BULLET_R) <= (targ->x - TARGET_R) && (bull->x + BULLET_R) >= (targ->x + TARGET_R)) &&
			((bull->y - BULLET_R) <= (targ->y - TARGET_R) && (bull->y + BULLET_R) >= (targ->y + TARGET_R))
	){
		return 0;
	}
	else
		return 1;
}

uint8_t catchBulletIsInEnemie(Pixel* bull, Pixel* enem){
	if(
			abs(bull->x - enem->x) <= sqrt(BULLET_R*BULLET_R + ENEMIE_R*ENEMIE_R) &&
			abs(bull->y - enem->y) <= sqrt(BULLET_R*BULLET_R + ENEMIE_R*ENEMIE_R)
	){
		return 0;
	}
	else
		return 1;
}

uint8_t checkTargetIsInBullet(Pixel* bull, Pixel* targ){
	if(
			abs(bull->x - targ->x) < BULLET_R + TARGET_R &&
			abs(bull->y - targ->y) < BULLET_R + TARGET_R
	){
		return 0;
	}
	else
		return 1;
}

uint8_t checkBulletIsInEnemie(Pixel* bull, Pixel* enem){
	if(
			abs(bull->x - enem->x) < BULLET_R + ENEMIE_R &&
			abs(bull->y - enem->y) < BULLET_R + ENEMIE_R
	){
		return 0;
	}
	else
		return 1;
}

uint8_t checkTargetIsInEnemie(Pixel* targ, Pixel* enem){
	if(
			abs(targ->x - enem->x) < TARGET_R + ENEMIE_R &&
			abs(targ->y - enem->y) < TARGET_R + ENEMIE_R
	){
		return 0;
	}
	else
		return 1;
}

uint16_t generateNewXCoordinate(uint16_t padding){
	uint16_t x = rand() % AREA_WIDTH;
	if(x < padding)
		x = padding;
	if(x > AREA_WIDTH - padding)
		x = AREA_WIDTH - padding;
	return x;
}

uint16_t generateNewYCoordinate(uint16_t padding){
	uint16_t y = rand() % AREA_HEIGHT;
	if(y < padding)
		y = padding;
	if(y > AREA_HEIGHT - padding)
		y = AREA_HEIGHT - padding;
	return y;
}

