/*
 * PB.h
 *
 *  Author: Mahmoud Ayoub
 */ 


#ifndef PB_H_
#define PB_H_

#include "../../MCAL/DIO/DIO_Config.h"

void PB_init (uint8 PortNumber , uint8 PinNumber) ;
uint8 PB_read (uint8 PortNumber , uint8 PinNumber) ; 





#endif /* PB_H_ */