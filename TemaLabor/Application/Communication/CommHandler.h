/*
 * CommHandler.h
 *
 *  Created on: 2016. nov. 4.
 *      Author: Kovács Viktor
 */

#ifndef COMMUNICATION_COMMHANDLER_H_
#define COMMUNICATION_COMMHANDLER_H_

#include "CommMessage.h"

#ifndef NULL
#define NULL ((void*)0)
#endif


/**
 * (Re)Initializes/empties a message structure, setting all values to default
 */
void InitMessage(pMessage_t msg);

/**
 * Handles a received byte to build the message structure
 * @param data The received byte
 * @return NULL if the message is not ready, else the complete message pointer
 */
pMessage_t CommByteReceived(uint8_t data);


#endif /* COMMUNICATION_COMMHANDLER_H_ */
