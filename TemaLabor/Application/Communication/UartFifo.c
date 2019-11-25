/*
 * UartFifo.c
 *
 *  Created on: 2016. nov. 4.
 *      Author: Kovács Viktor
 */


#include "Fifo.h"

Fifo_t UartFifo;
uint8_t FifoData[200];


void UartFifoInit(){
	FifoInit(&UartFifo,FifoData,sizeof(FifoData));
}
uint8_t UartFifoPop(uint8_t* pdata){
	return FifoPop(&UartFifo,pdata);
}
uint8_t UartFifoPush(uint8_t data){
	return FifoPush(&UartFifo,data);
}
