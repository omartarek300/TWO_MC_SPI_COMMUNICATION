/*
 * spi.h
 *
 * Created: 9/26/2021 3:23:01 AM
 *  Author: Omar
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "../../MC/My_avr.h"
#include "../../bit_operations.h"
/**************************************** FUNCTIONS PROTOTYPES ****************************************/

/*******
	Function Description: this function initiates the SPI in micro controller in MASTER mode
	parameter: none		   
	return: none
*/
void SPI_MasterInit();

/*******
	Function Description: this function initiates the SPI in micro controller in SLAVE mode
	parameter: none		   
	return: none
*/
void SPI_SlaveInit();

/*******
	Function Description: this function sends a byte from master to slave
	parameter: Data: the sent byte
			   slave_ID: selects which slave to receive data		   
	return: none
*/
void SPI_Master_send_byte(uint8_t Data, uint8_t slave_ID);

/*******
	Function Description: this function receives a byte from master
	parameter: none		   
	return: the received byte
*/
uint8_t SPI_Slave_receive_byte();

/*******
	Function Description: this function sends a string from master to slave
	parameter: str: the sent string
			   slave_ID: selects which slave to receive data		   
	return: none
*/
void SPI_Master_send_string(uint8_t* str, uint8_t slave_ID);

/*******
	Function Description: this function receives a string from master
	parameter: str: string to be received		   
	return: none
*/
void SPI_Slave_receive_string(uint8_t* str);



#endif /* SPI_H_ */