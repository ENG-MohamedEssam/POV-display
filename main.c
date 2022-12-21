/*
 * main.c
 *
 *  Created on: Dec 20, 2022
 *      Author: Mohamed Essam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TMR_interface.h"
#include "LCD_interface.h"

#include <avr/delay.h>

//#define F_CPU	8000000UL

int main(void)
{
	DIO_u8Init();
	GIE_voidEnable();
	TMR_voidTMR0Init();
	LCD_voidInit();

	while(1)
	{
//		LCD_u8GoToXY(0,0);
		LCD_voidWriteNumber((u16)micros());
		_delay_ms(1000);
		LCD_voidClear();
//		LCD_voidWriteChar('g');
		//_delay_ms(1000);
//		LCD_u8GoToXY(1,0);
//		LCD_voidWriteNumber(micros());
//		LCD_voidWriteChar('y');
	}
	return 0;
}

