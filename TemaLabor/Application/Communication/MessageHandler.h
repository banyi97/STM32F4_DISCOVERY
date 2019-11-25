/*
 * MessageHandler.h
 *
 *  Created on: 2016. nov. 4.
 *      Author: Kovács Viktor
 */

#ifndef COMMUNICATION_MESSAGEHANDLER_H_
#define COMMUNICATION_MESSAGEHANDLER_H_

#include "CommMessage.h"

#define COMMAND_FLOAT 1
#define COMMAND_INT 2
#define COMMAND_GYRO 3
#define COMMAND_TEXT 4


/**
 * Event handler of the received message
 * @param pMsg the received message
 */
void HandleMessage(pMessage_t pMsg);


#endif /* COMMUNICATION_MESSAGEHANDLER_H_ */
