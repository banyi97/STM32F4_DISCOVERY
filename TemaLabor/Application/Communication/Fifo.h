/*
 * Fifo.h
 *
 *  Created on: 2016. nov. 4.
 *      Author: Kovács Viktor
 */

#ifndef COMMUNICATION_FIFO_H_
#define COMMUNICATION_FIFO_H_

#include <stdint.h>

typedef struct fifo_struct{
	uint8_t* data;
	uint8_t datalen;
	uint8_t size;
	uint8_t wptr;
	uint8_t rptr;
} Fifo_t, *pFifo_t;


/**
 * Initializes or empties the fifo/ringbuffer
 * @param pfifo which structure to initialize
 * @param pdata points to the data buffer
 * @param length size of the data buffer
 */
void FifoInit(pFifo_t pfifo,uint8_t* pdata,uint8_t length);

/**
 * Gets the first data byte from the fifo
 * @param pfifo which fifo
 * @param pdata where to copy the byte
 * @return 1 if pdata is valid, 0 if not (fifo was empty)
 */
uint8_t FifoPop(pFifo_t pfifo,uint8_t* pdata);

/**
 * Puts a byte to the fifo
 * @param pfifo which fifo
 * @param data the byte to be copied to the fifo
 * @return 1 if success 0 otherwise (fifo was full)
 */
uint8_t FifoPush(pFifo_t pfifo,uint8_t data);

#endif /* COMMUNICATION_FIFO_H_ */
