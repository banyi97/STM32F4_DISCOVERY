/*
 * Game.h
 *
 *  Created on: Nov 24, 2019
 *      Author: User
 */

#ifndef CONTROLS_GAME_H_
#define CONTROLS_GAME_H_

#include "BasicControls.h"

#define BULLET_R 7
#define TARGET_R 5
#define ENEMIE_R 7
#define AREA_HEIGHT 300
#define AREA_WIDTH 240

typedef struct
{
	int16_t 	speed_X;
	int16_t		speed_Y;
} Speed;

typedef struct
{
	Pixel		Position;
	uint8_t		isActive;
} Enemie;

typedef struct
{
	uint8_t		NeedToDraw;
	Event 		OnNewData;
	//Data
	uint8_t		Level;
	uint8_t		IsGameOver;
	Pixel		Enemies[16];
	uint8_t		EnemiesNum;
	Pixel		BulletPosition;
	Pixel		TargetPosition;
	uint32_t 	Tik;
	//Appearance
	Pixel		Position;
	Pixel		Size;
} Game;

void InitGame(Game* c);

void DrawGame(Game* c);

void UpdateGameData(Game* c, int32_t val);

uint8_t catchTargetIsInBullet(Pixel* bull, Pixel* targ);
uint8_t catchBulletIsInEnemie(Pixel* bull, Pixel* enem);
uint8_t checkTargetIsInBullet(Pixel* bull, Pixel* targ);
uint8_t checkBulletIsInEnemie(Pixel* bull, Pixel* enem);
uint8_t checkTargetIsInEnemie(Pixel* targ, Pixel* enem);
uint16_t generateNewXCoordinate(uint16_t padding);
uint16_t generateNewYCoordinate(uint16_t padding);


#endif /* CONTROLS_GAME_H_ */
