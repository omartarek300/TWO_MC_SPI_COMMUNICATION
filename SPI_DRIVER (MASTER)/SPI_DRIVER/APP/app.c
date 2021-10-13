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
}
void APP_Flow()
{
	Master_Send_Byte('A', SLAVE_ONE);
	delay_ms(1000);
	Master_Send_Byte('B', SLAVE_ONE);
	delay_ms(1000);
	Master_Send_Byte('C', SLAVE_ONE);
	delay_ms(1000);
}