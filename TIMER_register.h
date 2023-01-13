/******************************************************************************/
/******************************************************************************/
/********************    Author:Abdelrahman    ********************************/
/********************    Layer:MCAL            ********************************/
/********************    SWC:GIE          	   ********************************/
/********************    Version:1.00          ********************************/
/******************************************************************************/
/******************************************************************************/



#ifndef TIMER_REGISTER_H
#define TIMER_REGISTER_H
/*timer0 registers*/
#define TCCR0				*((volatile u8*)0x53)
#define TCCR0_WGM00			6
#define TCCR0_WGM01			3
#define TCCR0_COM01			5
#define TCCR0_COM00			4
#define TCCR0_CS02			2
#define TCCR0_CS01			1
#define TCCR0_CS00			0
#define TCNT0				*((volatile u8*)0x52)
#define OCR0				*((volatile u8*)0x5C)
#define TIMSK 				*((volatile u16*)0x59)
#define TIMSK_OCR0			1
///////////////////////////////////////
/*timer 1 Registers*/
#define TCCR1A				*((volatile u8*)0x4F)
#define TCCR1A_COM1A1		7
#define TCCR1A_COM1A0		6
#define TCCR1A_WGM11		1
#define TCCR1A_WGM10		0

#define TCCR1B				*((volatile u8*)0x4E)
#define TCCR1B_WGM13		4
#define TCCR1B_WGM12		3
#define TCCR1B_CS12			2
#define TCCR1B_CS11			1
#define TCCR1B_CS10			0


#define TIMSK_TOIE1			2
#define TCNT1				*((volatile u16*)0x4C)

////////////////////////////////
#define TCCR2				*((volatile u8*)0x45)
#define TCCR2_WGM20			6
#define TCCR2_COM21			5
#define TCCR2_COM20			4
#define TCCR2_WGM21			3
#define TCCR2_CS22			2
#define TCCR2_CS21			1
#define TCCR2_CS20			0
#define TCNT2				*((volatile u8*)0x44)
#define OCR2				*((volatile u8*)0x43)
#define TIMSK_OCIE2			7
#endif
