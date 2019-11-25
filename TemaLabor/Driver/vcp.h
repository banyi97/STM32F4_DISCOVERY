/*
 * vcp.h
 *
 *  Created on: 2016 okt. 26
 *      Author: Gabor
 */

#ifndef VCP_H_
#define VCP_H_

/**
 * Initializes the Virtual Communication Port (VCP)
 */
void DRV_VCP_Init(void);

/**
 * Writes a string on the VCP
 * @param str null terminated string
 */
void DRV_VCP_WriteString(char * str);

/**
 * Enables the VCP interrupt
 */
void DRV_VCP_EnableIT();

/**
 * Disables the VCP interrupt
 */
void DRV_VCP_DisableIT();

#endif /* VCP_H_ */
