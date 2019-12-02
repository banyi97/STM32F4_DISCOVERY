/*
 * WindowManager.h
 *
 *  Created on: 2016 okt. 21
 *      Author: Nagy �kos
 */

#ifndef WINDOWMANAGER_WINDOWMANAGER_H_
#define WINDOWMANAGER_WINDOWMANAGER_H_

#include "Window.h"
#include "gyroscope.h"

typedef struct
{
	int32_t Data;
} DataPacket;

void InitWindowManager(void);
void SetActiveWindow(Window* w);
void HandleTouch(int TouchX, int TouchY);
void HandleNewData(DataPacket* d);
uint8_t HandleDraw(void);

/**
 * Passes a null-terminated string console
 * @param str the string to draw
 */
void HandleString(char* str);

/**
 * Passes an int32 to the line chart
 * @param data the number
 */
void HandleChart(int32_t data);

/**
 * Passes an int32 to the compass
 * @param data angular velocity in mdeg/sec
 */
void HandleCompass(int32_t data);

/**
 * Passes an int32 to the histogram chart
 * @param data the number
 */
void HandleHistogram(int32_t data);

/**
 * Passes a float to the spectrum chart
 * @param data the floating point number
 */
void HandleSpectrum(float data);

void HandleGame(gyro_t data);

void HandleBlockGame(gyro_t data);

#endif /* WINDOWMANAGER_WINDOWMANAGER_H_ */
