/*
 * DIO_HAL.h
 *
 * Created: 10/11/2021 10:15:09 PM
 *  Author: Omar
 */ 


#ifndef DIO_HAL_H_
#define DIO_HAL_H_

#include "../../MCAL/DIO/dio.h"

/*******
	Function Description: this function enables the port to set the output on
	parameter: port_name: specify which port	   
	return: none
*/
void Enable_Port(uint8_t port_name);

/*******
	Function Description: this function set the output on the selected port
	parameter: port_name: specify which port
			   pins: the pins which the output will be on	   
	return: none
*/
void Port_Set_Output(uint8_t port_name, uint8_t pins);



#endif /* DIO_HAL_H_ */