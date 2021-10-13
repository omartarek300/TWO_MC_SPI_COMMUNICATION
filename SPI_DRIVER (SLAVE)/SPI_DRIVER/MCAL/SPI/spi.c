/*
 * spi.c
 *
 * Created: 9/26/2021 3:22:48 AM
 *  Author: Omar
 */ 
#include "spi.h"
void SPI_MasterInit()
{
	/* Set MOSI, SCK, SS output, MISO input */
	SETBIT(DDRB, bit7);
	SETBIT(DDRB, bit5);
	SETBIT(DDRB, bit4);
	CLRBIT(DDRB, bit6);
	SETBIT(PORTB,bit4); //set SS high
	
	/* enable SPI + enable Master + choose SPI clock = Fosc/4 */
	SETBIT(SPCR, bit6);
	SETBIT(SPCR, bit4);

}
void SPI_SlaveInit()
{
	/* Set MISO output, all others input */
	CLRBIT(DDRB, bit7);
	CLRBIT(DDRB, bit5);
	CLRBIT(DDRB, bit4);
	SETBIT(DDRB, bit6);
	/* Enable SPI */
	SETBIT(SPCR, bit6);
}
void SPI_Master_send_byte(uint8_t Data, uint8_t slave_ID)
{
	uint8_t read_data_reg = 0;
	
	for (uint8_t slave_num = 0; slave_num < slave_ID; slave_num++) // loop for daisy chain
	{
		CLRBIT(PORTB, bit4); //set SS low
		/* Start transmission */
		SPDR = Data;
		/* Wait for transmission complete */
		while(!GETBIT(SPSR, bit7));
		read_data_reg = SPDR; // to clear SPIF flag
		SETBIT(PORTB, bit4); //set SS high
	}
}
uint8_t SPI_Slave_receive_byte()
{
	/* Wait for reception complete */
	while(!GETBIT(SPSR, bit7));
	/* Return data register */
	return SPDR;
}
void SPI_Master_send_string(uint8_t* str, uint8_t slave_ID)
{
	uint8_t char_index = 0;
	while(str[char_index] != '\0')
	{
		SPI_Master_send_byte(str[char_index], slave_ID);
		char_index++;
	}
}
void SPI_Slave_receive_string(uint8_t* str)
{
	uint8_t char_index =0;
	str[char_index] = SPI_Slave_receive_byte();
	while(str[char_index] != '#')
	{
		char_index++;
		str[char_index] = SPI_Slave_receive_byte();
	}
	str[char_index] = '\0';
}