/*
 * Compass.h
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy Ákos
 */

#ifndef CONTROLS_COMPASS_H_
#define CONTROLS_COMPASS_H_

#include "BasicControls.h"

typedef struct
{
	uint8_t		NeedToDraw;
	Event 		OnNewData;
	//Data
	float		Heading;
	float		AngVelocity;
	float		Factor; //Low-pass filter alpha constant
	uint32_t	Time; //Last time tick
	//Appearance
	Pixel		Position;
	int16_t		Length;
} Compass;

/**
 * Init compass:
 * 	Initialize the necessary variables of the Compass structure.
 * @param Pointer to a Compass structure.
 * @return None.
 */
void InitCompass(Compass* c);

/**
 * Draw compass:
 * 	Use DRV Display/Drawing functions
 * 	Reset NeedToDraw flag
 * @param Pointer to a Compass structure.
 * @return None.
 */
void DrawCompass(Compass* c);

/**
 * Update compass heading data:
 *  Filter the new measurement using a low-pass filter
 *  Save the filtered value to AngVelocity
 * 	Set Heading based on AngVelocity
 * 	Set NeedToDraw flag
 * @param Pointer to a Compass structure, new angular velocity.
 * @return None.
 */
void UpdateCompassData(Compass* c, int32_t w);

#endif /* CONTROLS_COMPASS_H_ */
