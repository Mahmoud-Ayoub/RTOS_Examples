/*
 * LCD.c
 *
 *  Author: Mahmoud-Ayoub
 */ 
#include "LCD.h"

/*
Description : function to initialize LCD port , 4 bits mode , and send required commands for initialization
inputs		: none
outputs		: none
*/
void LCD_init (void) {
	DIO_SetPortDirection(portC , OUTPUT) ;		// all pins of PORT C is output
	DIO_SetPortValue(portC, 0) ;				// all pins are reseted
	            
	LCD_send_cmd(0x33) ;			// needed commands for 4 bits mode   (group of initial commands must be sent to LCD)
	LCD_send_cmd(0x32) ;
	LCD_send_cmd(0x28) ;
	LCD_send_cmd(0x0E) ;
	LCD_send_cmd(0x01) ;
	_delay_us(2000) ;
	LCD_send_cmd(0x06) ;
	
}

/*
Description : function to send command to LCD
inputs		: command
outputs		: none
*/
void LCD_send_cmd (char cmd) {
	
	char command ;
	
	command = (PORTC_REG & 0x0F) | (cmd & 0xF0);	// Sending upper nibble
	DIO_SetPortValue(portC , command) ;
	CLEAR_BIT (PORTC_REG , Rs) ;					// write command
	SET_BIT (PORTC_REG , E) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTC_REG , E) ;						// E is set low (telling LCD that we are done sending data)
	
	command = (PORTC_REG & 0x0F) | (cmd << 4);		// Sending lower nibble
	DIO_SetPortValue(portC , command) ;
	CLEAR_BIT (PORTC_REG , Rs) ;					// write command
	SET_BIT (PORTC_REG , E) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTC_REG , E) ;						// E is set low (telling LCD that we are done sending data)
}

/*
Description : function to send character to LCD
inputs		: char data
outputs		: none
*/
void LCD_send_char (char value) {
	
	char sent_value ; 
	
	sent_value = (PORTC_REG & 0x0F) | (value & 0xF0);/* Sending upper nibble */
	DIO_SetPortValue(portC , sent_value) ;
	SET_BIT (PORTC_REG , Rs) ;						// write data
	SET_BIT (PORTC_REG , E) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTC_REG , E) ;						// E is set low (telling LCD that we are done sending data)
	
	sent_value = (PORTC_REG & 0x0F) | (value << 4);  /* Sending lower nibble */
	DIO_SetPortValue(portC , sent_value) ;
	SET_BIT (PORTC_REG , Rs) ;						// write data
	SET_BIT (PORTC_REG , E) ;						//  E is set high (telling LCD to receive data)
	_delay_ms(1) ;
	CLEAR_BIT (PORTC_REG , E) ;						// E is set low (telling LCD that we are done sending data)
}

/*
Description : function to send string to LCD
inputs		: string data
outputs		: none
*/
void LCD_send_str (char* str) {
	unsigned int char_index = 0 ; 
	while (str[char_index] != '\0') {
		LCD_send_char(str[char_index]) ; 
		char_index ++ ; 
	}	
}

/*
Description : function to clear the LCD
inputs		: none
outputs		: none
*/
void LCD_clear (void) {
	LCD_send_cmd(0x01) ;         
}

/*
Description : function to Force cursor to beginning of second line
inputs		: none
outputs		: none
*/
void LCD_newline (void) {
	LCD_send_cmd(0xC0) ;
}

/*
Description : function to shift cursor left
inputs		: none
outputs		: none
*/
void LCD_shift_left (void) {
	LCD_send_cmd(0x10) ;
}

/*
Description : function to shift cursor right
inputs		: none
outputs		: none
*/
void LCD_shift_right (void) {
	LCD_send_cmd(0x14) ;
}

/*
Description : function to return cursor to its initial position (0,0)
inputs		: none
outputs		: none
*/
void LCD_home (void) {
	LCD_send_cmd(0x02) ;
}
