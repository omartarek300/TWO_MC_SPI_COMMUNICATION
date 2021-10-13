/*
 * SPI_HAL.h
 *
 * Created: 10/11/2021 10:12:07 PM
 *  Author: Omar
 */ 


#ifndef SPI_HAL_H_
#define SPI_HAL_H_
/****************************************** INCLUDES ****************************************************/

#include "../../MCAL/SPI/spi.h"

/****************************************** DATA TYPES***************************************************/

typedef enum
{
	MASTER, SLAVE
}OPERATING_MODE;

/**************************************** FUNCTIONS PROTOTYPES ****************************************/

/*******
	Function Description: this function initiates the SPI in micro controller in MASTER OR SLAVE mode
	parameter: mode: selects operating mode MASTER or SLAVE	   
	return: none
*/
void SPI_INIT(OPERATING_MODE mode);

/*******
	Function Description: this function sends a byte from master to slave
	parameter: Data: the sent byte
			   slave_num: selects which slave to receive data		   
	return: none
*/
void Master_Send_Byte(uint8_t data, uint8_t slave_num);

/*******
	Function Description: this function sends a string from master to slave
	parameter: str: the sent string
			   slave_num: selects which slave to receive data		   
	return: none
*/
void Master_Send_String(uint8_t* str, uint8_t slave_num);

/*******
	Function Description: this function receives a byte from master
	parameter: none		   
	return: the received byte
*/
uint8_t Slave_Receive_Byte();

/*******
	Function Description: this function receives a string from master
	parameter: str: string to be received		   
	return: none
*/
void Slave_Receive_String(uint8_t* str);


#endif /* SPI_HAL_H_ */