/*
 * UartFifo.h
 *
 *  Created on: 2016. nov. 4.
 *      Author: Kovács Viktor
 */

#ifndef COMMUNICATION_UARTFIFO_H_
#define COMMUNICATION_UARTFIFO_H_

#include <stdint.h>

/**
 * Initializes/empties the uart fifo, must be set up before receiving anything
 */
void UartFifoInit();

/**
 * Gets a byte from the uart fifo
 * @param pdata address where to copy the byte
 * @return 1 if success, 0 otherwise
 */
uint8_t UartFifoPop(uint8_t* pdata);

/**
 * Puts a byte to the uart fifo
 * @param data the byte
 * @return 1 if success, 0 otherwise
 */
uint8_t UartFifoPush(uint8_t data);

#endif /* COMMUNICATION_UARTFIFO_H_ */
