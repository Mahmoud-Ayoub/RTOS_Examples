/*
 * PB.c
 *
 *  Author: Mahmoud Ayoub
 */ 
#include "PB.h"

/*
Description : function to initialize the pin connected to the push button
inputs		: port number (portA , portB , portC , portD) , pin number (0-7)
outputs		: none
*/
void PB_init (uint8 PortNumber , uint8 PinNumber) {
	DIO_SetPinDirection (PortNumber , PinNumber , INPUT) ; 
}

/*
Description : function to get the value of push button
inputs		: port number (portA , portB , portC , portD) , pin number (0-7)
outputs		: push button value (0 or 1)
*/
uint8 PB_read (uint8 PortNumber , uint8 PinNumber) {
	uint8 value ;
	value = DIO_GetPinValue (PortNumber , PinNumber) ;
	return value ; 
}