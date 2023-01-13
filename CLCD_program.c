/******************************************************************************/
/******************************************************************************/
/********************    Author:Abdelrahman    ********************************/
/********************    Layer:Mcal            ********************************/
/********************    SWC:DIO               ********************************/
/********************    Version:1.00          ********************************/
/******************************************************************************/
/******************************************************************************/


#include "STD_TYPES.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"




void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_BIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_BIN,DIO_u8PIN_LOW);
	DIO_u8SetPortVAlue(CLCD_DATA_PORT,Copy_u8Command);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_BIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_BIN,DIO_u8PIN_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_BIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_BIN,DIO_u8PIN_LOW);
	DIO_u8SetPortVAlue(CLCD_DATA_PORT,Copy_u8Data);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_BIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_BIN,DIO_u8PIN_LOW);
}

void CLCD_voidInit(void)
{
	_delay_ms(40);
	/* function set :2lines,5x8 font size*/
	CLCD_voidSendCommand(0b00111000);
	/* Display On Off Control :Display enable , Display cursor,no blink cursor*/
	CLCD_voidSendCommand(0b00001100);
	/*Clear Display*/
	CLCD_voidSendCommand(0b00000001);
}


void CLCD_voidSendString(const char *Copy_pcString)
{
	u8 cnt=0;
	while(Copy_pcString[cnt]!='\0')
	{
		CLCD_voidSendData(Copy_pcString[cnt]);
		cnt++;
	}
}



void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8Adress;
	if(Copy_u8XPos==0)
	{
		Local_u8Adress=Copy_u8YPos;
	}
	else if(Copy_u8XPos==1)
	{
		Local_u8Adress=0x40+Copy_u8YPos;
	}
	CLCD_voidSendCommand(Local_u8Adress+128);
}



void CLCD_voidWriteSpecialCharacter(u8 *Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRamAddress=0,Local_u8Iterator;

	Local_u8CGRamAddress=Copy_u8PatternNumber*8;

	CLCD_voidSendCommand(Local_u8CGRamAddress+64);

	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

	CLCD_voidSendData(Copy_u8PatternNumber);
}


void CLCD_voidWriteNumber(u32 Copy_u32Number)
{
	u8 Local_u32Register[9],i=0;
	while(Copy_u32Number != 0)
	{
		Local_u32Register[i]=Copy_u32Number%10;
		Copy_u32Number/=10;
		i++;
	}

	while(i != 0)
	{
		CLCD_voidSendData(Local_u32Register[i-1]+48);
		i--;
	}
}
