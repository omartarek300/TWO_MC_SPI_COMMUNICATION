/*
 * DIO_HAL.c
 *
 * Created: 10/11/2021 10:15:20 PM
 *  Author: Omar
 */ 
#include "DIO_HAL.h"
void Enable_Port(uint8_t port_name)
{
	DIO_init(port_name, ALL_PORT);
}
void Port_Set_Output(uint8_t port_name, uint8_t pins)
{
	DIO_set(port_name, pins);
}
 