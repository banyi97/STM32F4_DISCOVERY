/*
 * gyro.c
 *
 *  Created on: 2016 okt. 26
 *      Author: csorvasig
 */

#include "gyroscope.h"

#include <stm32f429i_discovery_gyroscope.h>

typedef union _gyro_union_t {
	float xyz[3];
	gyro_t omega;
} gyro_union_t;

gyro_t offset;

void DRV_Gyro_Init(void)
{
	BSP_GYRO_Init();
}

void DRV_Gyro_Reset(void)
{
	BSP_GYRO_Reset();
}

void DRV_Gyro_Calibration(void)
{
	uint32_t duration = 1000;
	uint32_t time = HAL_GetTick();
	uint32_t n = 0;
	gyro_t sum;

	offset.omega_x = 0; offset.omega_y = 0; offset.omega_z = 0;
	sum = offset;
	while ((HAL_GetTick() - time) < duration)
	{
		sum.omega_x += DRV_Gyro_GetXYZ().omega_x;
		sum.omega_y += DRV_Gyro_GetXYZ().omega_y;
		sum.omega_z += DRV_Gyro_GetXYZ().omega_z;
		n++;
	}
	sum.omega_x /= n; sum.omega_y /= n; sum.omega_z /= n;

	offset = sum;
}

gyro_t DRV_Gyro_GetXYZ(void)
{
	gyro_union_t gyroVal;
	BSP_GYRO_GetXYZ(gyroVal.xyz);
	gyroVal.omega.omega_x -= offset.omega_x;
	gyroVal.omega.omega_y -= offset.omega_y;
	gyroVal.omega.omega_z -= offset.omega_z;
	return gyroVal.omega;
}
