/*
 * gyro.h
 *
 *  Created on: 2016 okt. 26
 *      Author: csorvasig
 */

#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_

typedef struct _gyro_t
{
	float omega_x;
	float omega_y;
	float omega_z;
} gyro_t;

/**
 * Initializes the gyroscope hardware
 */
void DRV_Gyro_Init(void);

/**
 * Resets the gyroscope
 */
void DRV_Gyro_Reset(void);

/**
 * Calibrates the gyroscope
 */
void DRV_Gyro_Calibration(void);

/**
 * Gets the gyrosope current value
 * @returns gyro_t with the values
 */
gyro_t DRV_Gyro_GetXYZ(void);

#endif /* GYROSCOPE_H_ */
