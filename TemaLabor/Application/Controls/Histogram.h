/*
 * Histogram.h
 *
 *  Created on: 2016 nov. 1
 *      Author: Nagy Ákos
 */

#ifndef CONTROLS_HISTOGRAM_H_
#define CONTROLS_HISTOGRAM_H_

#include "BasicControls.h"

#define HISTOGRAM_NUM_OF_COL	8

typedef struct
{
	uint8_t		NeedToDraw;
	Event 		OnNewData;
	//Data
	int32_t		Data[HISTOGRAM_NUM_OF_COL];
	int32_t		Xmin, Xmax, Xstep; //Constants values
	int32_t		Ymax; //Maximum value, calculated at every new data
	//Appearance
	Pixel		Position;
	Pixel		Size;
	uint32_t 	ColWidth; //Width of one column
} Histogram;

/**
 * Init histogram:
 * 	Initialize the necessary variables of the Histogram structure.
 * @param Pointer to a Histogram structure.
 * @return None.
 */
void InitHistogram(Histogram* c);

/**
 * Draw histogram:
 * 	Use DRV Display/Drawing functions
 * 	Draw Axis, Columns, X/Y labels
 * 	Reset NeedToDraw flag
 * @param Pointer to a Histogram structure.
 * @return None.
 */
void DrawHistogram(Histogram* c);

/**
 * Update histogram data:
 *  Check new value with Xmin,Xmax
 * 	Increase the correspondent column count
 * 	Set Ymax based on maximum value
 * 	Set NeedToDraw flag
 * @param Pointer to a Histogram structure, new value.
 * @return None.
 */
void UpdateHistogramData(Histogram* c, int32_t val);

#endif /* CONTROLS_HISTOGRAM_H_ */
