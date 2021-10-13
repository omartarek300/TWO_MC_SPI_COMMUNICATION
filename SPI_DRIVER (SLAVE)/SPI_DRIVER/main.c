/*
 * SPI_DRIVER.c
 *
 * Created: 9/26/2021 3:10:31 AM
 * Author : Omar
 */ 

#include "APP/app.h"

int main(void)
{
    /* Replace with your application code */
	
	APP_INIT(SLAVE);
	
    while (1) 
    {
		APP_Flow();
    }
}

