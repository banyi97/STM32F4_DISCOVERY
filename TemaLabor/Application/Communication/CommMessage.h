/*
 * CommMessage.h
 *
 *  Created on: 2016. nov. 4.
 *      Author: Kovács Viktor
 */

#ifndef COMMUNICATION_COMMMESSAGE_H_
#define COMMUNICATION_COMMMESSAGE_H_

#include <stdint.h>

typedef struct commmsg
{
	uint8_t Command;
	uint8_t DataLen;
	uint8_t Data[255];
	uint8_t Check;
	uint16_t Position;
} Message_t, *pMessage_t;

#endif /* COMMUNICATION_COMMMESSAGE_H_ */
