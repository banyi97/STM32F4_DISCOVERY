/*
 * MessageHandler.c
 *
 *  Created on: 2016. nov. 4.
 *      Author: Kovács Viktor
 */
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "MessageHandler.h"
#include "WindowManager.h"

void HandleMessage(pMessage_t pMsg){
	int32_t i;
	float f;
	char str[255];
	switch (pMsg->Command){
		case COMMAND_INT:
			memcpy(&i,pMsg->Data,4);
			HandleChart(i);
			HandleCompass(i);
			HandleHistogram(i);
			HandleSpectrum((float)i);
			break;

		case COMMAND_FLOAT:
			memcpy(&f,pMsg->Data,4);
			i=(int32_t)f;
			HandleChart(i);
			HandleCompass(i);
			HandleHistogram(i);
			HandleSpectrum(f);
			break;

		case COMMAND_GYRO:
			memcpy(&f,pMsg->Data+8,4);
			i=(int32_t)f;
			HandleChart(i);
			HandleCompass(i);
			HandleHistogram(i);
			HandleSpectrum(f);
			break;

		case COMMAND_TEXT:
			memcpy(str,(char*)pMsg->Data,pMsg->DataLen);//HardFault sima pointeres címzéssel szóhatár probléma miatt!
			str[pMsg->DataLen]=0;
			HandleString(str);
			break;


	}



}
