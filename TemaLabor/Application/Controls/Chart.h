/*
 * Chart.h
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy Ákos
 */

#ifndef CONTROLS_CHART_H_
#define CONTROLS_CHART_H_

#include "BasicControls.h"

#define CHART_MAX_PIXELS 400

typedef struct
{
	uint8_t		NeedToDraw;
	Event 		OnNewData;
	//Data
	Pixel		DataPixels[CHART_MAX_PIXELS];
	int32_t		DataPointer; //Pointer to the current pixel
	float		DataValue; //Filtered measurement
	float		Factor; //Low-pass filter alpha constant
	//Appearance
	Pixel		Position;
	Pixel		Origin; //Origin position
	Pixel		Size;
	float		Xstep; //Can be changed during measurement!
	float		YScale; //Can be changed during measurement!
} Chart;

/**
 * Init chart:
 * 	Initialize the necessary variables of the Chart structure.
 * @param Pointer to a Chart structure.
 * @return None.
 */
void InitChart(Chart* c);

/**
 * Draw chart:
 * 	Use DRV Display/Drawing functions
 * 	Draw Axis, circles for the datapoints, X/Y labels
 * 	Reset NeedToDraw flag
 * @param Pointer to a Chart structure.
 * @return None.
 */
void DrawChart(Chart* c);

/**
 * Update chart data:
 *  Filter the new measurement using a low-pass filter
 *  Set the X,Y components of the new pixel
 *  Increase the pointer of the pixels
 *  Reset pointer when necessary
 * 	Set NeedToDraw flag
 * @param Pointer to a Chart structure, new value.
 * @return None.
 */
void UpdateChartData(Chart* c, int32_t val);

#endif /* CONTROLS_CHART_H_ */
