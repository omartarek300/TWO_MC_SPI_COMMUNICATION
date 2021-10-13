/*
 * app.c
 *
 * Created: 10/11/2021 11:06:21 PM
 *  Author: Omar
 */ 
#include "app.h"
void APP_INIT(OPERATING_MODE mode)
{
	SPI_INIT(mode);
	lcd_config lcd_conf = {PD,PC,CTRL_PINS,DATA_PINS}; // initialize LCD
	LCD_init(lcd_conf);
}
void APP_Flow()
{
	uint8_t received_byte = Slave_Receive_Byte();
	send_char(received_byte);
	go_to_row_column(FIRST_ROW, FIRST_COL);
}