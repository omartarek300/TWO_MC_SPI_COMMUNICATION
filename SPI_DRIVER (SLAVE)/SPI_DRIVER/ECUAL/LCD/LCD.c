/*
 * LCD.c
 *
 * Created: 9/14/2021 4:45:38 PM
 *  Author: Omar
 */ 
#include "LCD.h"
void LCD_init(lcd_config config)
{
	ctrl_port = config.control_port;
	data_port = config.data_port;
	DIO_init(ctrl_port, config.ctrl_pins); /* Configure the control port as output port */ 
	#if (bit_mode == Four_bit_mode)
		DIO_init(data_port,config.data_pins); /* Configure the data port as output port */
		send_cmd(0x02);
		send_cmd(two_line_4_bit_mode); /* use 4_bit mode and 2 line LCD */
	#elif (bit_mode == Eight_bit_mode)
		DIO_init(data_port,config.data_pins); /* Configure the data port as output port */ 
		send_cmd(two_line_8_bit_mode); /* use 8_bit mode and 2 line LCD */
	#endif
	send_cmd(Display_ON); /* turn display on */
	send_cmd(CLEAR_COMMAND); /* clear LCD at the beginning */
	
}
void send_cmd(uint8_t command)
{ 
	DIO_CLR_BIT(ctrl_port, RS); /* Instruction Mode RS=0 */
	DIO_CLR_BIT(ctrl_port, RW); /* write data to LCD so RW=0 */
	delay_ms(1); /* delay for tas */
	DIO_SET_BIT(ctrl_port, E); /* enable writing data on D0-->D7 */
	delay_ms(1); /* delay for tpw - tpws*/
	#if (bit_mode == Four_bit_mode)
	 /******************* 4_Bit_Imstructions ********************
	 *	1- clear data port before the new command
		2- out the higher bits of the required command to the data bus D4 --> D7
		3- disable E PIN
		4- enable writing data on D4-->D7 again
		5- clear data port before the new command
		6- out the lower bits of the required command to the data bus D4 --> D7 
		7- disable E PIN
	 */
		DIO_CLR(data_port, CLR_high_bits); 
		DIO_set(data_port, four_high_bits(command));
		delay_ms(1); /* delay for tpsw*/
		DIO_CLR_BIT(ctrl_port, E); 
		delay_ms(1); /* delay for th*/
		DIO_SET_BIT(ctrl_port, E);
		delay_ms(1); /* delay for tpw - tpws*/
		DIO_CLR(data_port, CLR_high_bits);
		DIO_set(data_port, four_low_bits(command));
		delay_ms(1); /* delay for tpsw*/
		DIO_CLR_BIT(ctrl_port, E);
		delay_ms(1); /* delay for th*/
	#elif (bit_mode == Eight_bit_mode)
		DIO_CLR(data_port, CLR); /* clear data port before the new command*/
		DIO_set(data_port, command); /* out the required command to the data bus D0 --> D7 */
		delay_ms(1); /* delay for tpsw*/
		DIO_CLR_BIT(ctrl_port, E); /* disable E PIN */
		delay_ms(1); /* delay for th*/
	#endif
}
void send_char( uint8_t data_8)
{
	
	DIO_SET_BIT(ctrl_port, RS); /* data Mode RS=0 */
	DIO_CLR_BIT(ctrl_port, RW); /* write data to LCD so RW=0 */
	delay_ms(1); /* delay for tas*/
	DIO_SET_BIT(ctrl_port, E); /* enable writing data on D0-->D7 */
	delay_ms(1); /* delay for tpw - tpws*/
	#if (bit_mode == Four_bit_mode)
	/******************* 4_Bit_Imstructions ********************
	 *	1- clear data port before the new command
		2- out the higher bits of the required command to the data bus D4 --> D7
		3- disable E PIN
		4- enable writing data on D4-->D7 again
		5- clear data port before the new command
		6- out the lower bits of the required command to the data bus D4 --> D7 
		7- disable E PIN
	 */
		DIO_CLR(data_port, CLR_high_bits); 
		DIO_set(data_port, four_high_bits(data_8));
		delay_ms(1); /* delay for tpsw*/
		DIO_CLR_BIT(ctrl_port, E); 
		delay_ms(1); /* delay for th*/
		DIO_SET_BIT(ctrl_port, E); 
		delay_ms(1); /* delay for tpw - tpws*/
		DIO_CLR(data_port, CLR_high_bits); 
		DIO_set(data_port, four_low_bits(data_8));
		delay_ms(1); /* delay for tpsw*/
		DIO_CLR_BIT(ctrl_port, E); 
		delay_ms(1); /* delay for th*/
	#elif (bit_mode == Eight_bit_mode)
		DIO_CLR(data_port, CLR); 
		DIO_set(data_port, data_8); 
		delay_ms(1); /* delay for tpsw*/
		DIO_CLR_BIT(ctrl_port, E); 
		delay_ms(1); /* delay for th*/
	#endif	
}
void send_string(uint8_t* str)
{
	uint8_t char_index = 0;
	while(str[char_index] != '\0')
	{
		send_char(str[char_index]);
		char_index ++;
	}
}

void LCD_intgerToString(uint8_t data)
{
	uint8_t* str = "0";
	if(data < 10 && -10 < data)
	{
		str[0] = data + '0'; // add 0 ascii to convert to character 
		str[1] = '\0';	 // null terminator
	}
	else
	{
		uint8_t iterator = 0;
		while((data / 10) != 0)
		{
			str[iterator] = (data % 10) + '0';
			data /= 10;
			iterator++;
		}
		str[iterator] = data + '0'; // last number
		iterator++;
		str[iterator] = '\0';	 // null terminator
		for(uint8_t num_index = 0; num_index < iterator/2; num_index++) 
		{
			swap(&str[num_index], &str[ iterator - num_index-1]);
		}
	}
	send_string(str);
}
void go_to_row_column(uint8_t row, uint8_t col)
{
	uint8_t address = 0;
	switch(row)
	{
		case first_row:
			address = col;
			break;
		case second_row:
			address = col + second_row_address;
			break;
	}
	send_cmd (address | cursor_location); // address + 0x80
}
void swap(uint8_t* num1, uint8_t* num2)
{
	*num1 ^= *num2;
	*num2 ^= *num1;
	*num1 ^= *num2;
}

