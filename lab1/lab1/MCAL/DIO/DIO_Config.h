/*
 * DIO_Config.h
 *
 *  Author: Mahmoud Ayoub
 */ 


#ifndef DIO_INT_H_
#define DIO_INT_H_

#include "../Std_Types.h"
#include "../Bit_Math.h"
#include "DIO_REG.h"

#define portA 0
#define portB 1
#define portC 2
#define portD 3

#define OUTPUT 1
#define INPUT 0

void DIO_SetPinDirection (uint8 PortNumber , uint8 PinNumber , uint8 Direction) ;
void DIO_SetPinValue (uint8 PortNumber , uint8 PinNumber , uint8 Value) ; 
void DIO_TogglePinValue (uint8 PortNumber , uint8 PinNumber) ;

void DIO_SetPortDirection (uint8 PortNumber , uint8 Direction) ;
void DIO_SetPortValue (uint8 PortNumber , uint8 Value) ;
 
uint8 DIO_GetPinValue (uint8 PortNumber , uint8 PinNumber) ; 
uint8 DIO_GetPortValue (uint8 PortNumber) ; 

#endif /* DIO_INT_H_ */