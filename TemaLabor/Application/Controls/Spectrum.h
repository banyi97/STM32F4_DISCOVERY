/*
 * Spectrum.h
 *
 *  Created on: 2016 nov. 3
 *      Author: Nagy Ákos
 */

#ifndef CONTROLS_SPECTRUM_H_
#define CONTROLS_SPECTRUM_H_

#include "BasicControls.h"

#define SPECTRUM_SAMPLES	200

typedef struct
{
	uint8_t		NeedToDraw;
	Event 		OnNewData;
	//Data
	int32_t		Fifo[SPECTRUM_SAMPLES]; //Measurements fifo
	uint32_t	Pointer; //Pointer for the Fifo
	float		Coeff_A[SPECTRUM_SAMPLES], Coeff_B[SPECTRUM_SAMPLES]; //DFT coefficients
	float		Mag[SPECTRUM_SAMPLES]; //Magnitudes
	float		Ymax; //Highest peak
	uint32_t	YmaxPos; //Highest peak position
	uint32_t	Time; //Last time tick
	float		SamplingTime;
	//Appearance
	Pixel		Position;
	uint32_t 	ColWidth;
	Pixel		Size;
} Spectrum;

/**
 * Init spectrum:
 * 	Initialize the necessary variables of the Spectrum structure.
 * @param Pointer to a Spectrum structure.
 * @return None.
 */
void InitSpectrum(Spectrum* c);

/**
 * Draw spectrum:
 * 	Use DRV Display/Drawing functions
 * 	Draw axis, spectrum, frequency label at the highest peak
 * 	Reset NeedToDraw flag
 * @param Pointer to a Spectrum structure.
 * @return None.
 */
void DrawSpectrum(Spectrum* c);

/**
 * Update spectrum data:
 *  Measure sampling time for highest peak frequency (DrawSpectrum)
 * 	Calculate DFT coefficients
 * 	Increase pointer to the FIFO array
 * 	Calculate magnitudes, set maximum magnitude (highest peak)
 * 	Set NeedToDraw flag
 * @param Pointer to a Spectrum structure, new value.
 * @return None.
 */
void UpdateSpectrumData(Spectrum* c, int32_t val);

#endif /* CONTROLS_SPECTRUM_H_ */
