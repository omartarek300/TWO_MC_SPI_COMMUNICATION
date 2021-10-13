/*
 * LCD.h
 *
 * Created: 9/14/2021 4:45:48 PM
 *  Author: Omar
 */ 


#ifndef LCD_H_
#define LCD_H_
#define UPPER_PORT_PINS
#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/TIMER/timer.h"
#include <string.h>
/* LCD Modes */
#define bit_mode 8
#define Four_bit_mode 4
#define Eight_bit_mode 8
/* LCD PINS */
#define RS 0 //register select
#define RW 1 // read write
#define E 2 //enable
/* LCD Rows */
#define first_row 0
#define second_row 1
#define  second_row_address 0x40

/* LCD Commands */
#define Display_ON 0x0C
#define two_line_8_bit_mode 0x38
#define two_line_4_bit_mode 0x28
#define CLEAR_COMMAND 0x01
#define cursor_location 0x80
#define four_high_bits(command) (command & 0XF0)
#define four_low_bits(command) ((command & 0X0F)<<4)
#if (bit_mode == Four_bit_mode)
#define CLR_high_bits 0xf0
//#define CLR_low_bits 0x0f
#else
#define CLR 0xff
#endif

/*********************************************** NEW DEFINETIONS ********************************************/
typedef struct
{
	uint8_t control_port;
	uint8_t data_port;
	uint8_t ctrl_pins;
	uint8_t data_pins;
}lcd_config;
/********************************************* GLOBAL VARIABLES *********************************************/
uint8_t ctrl_port;
uint8_t data_port;
/*********************************************** FUNCTIONS PROTOTYPE ****************************************/
/*******
	Function Description: this function initiates the control and data pins of the LCD and its mode of operation
	parameter: config: is a structure that holds the control port and data port names and the used pins of both
	return: none
*/
void LCD_init(lcd_config config);

/*******
	Function Description: this function sends instructions to LCD to specify the operations and modes
	parameter: command: is the instruction sent to LCD to be executed
	return: none
*/
void send_cmd(uint8_t command);

/*******
	Function Description: this function sends character to LCD to be displayed
	parameter: data_8: is 8 bit character s
	return: none
*/
void send_char(uint8_t data_8);

/*******
	Function Description: this function displays a string on LCD
	parameter: str: is the string to be displayed on LCD
	return: none
*/
void send_string(uint8_t* str);

/*******
	Function Description: this function converts integer data into string and display it on LCD
	parameter: data: is the integer to be displayed on LCD
	return: none
*/
void LCD_intgerToString(uint8_t data);

/*******
	Function Description: this function set the cursor at a specific location 
	parameter: row: selects the row of LCD
			   col: selects the column of LCD
	return: none
*/
void go_to_row_column(uint8_t row, uint8_t col);

/*******
	Function Description: this function set swap two numbers by reference
	parameter: num1: first number
			   num2: second number
	return: none
*/
void swap(uint8_t* num1, uint8_t* num2);
#endif /* LCD_H_ */