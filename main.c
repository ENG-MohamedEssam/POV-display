#include"BIT_MATH.h"
#include "STD_TYPES.h"
#include"EXTI_interface.h"
#include"GIE_interface.h"
#include"DIO_interface.h"
#include"TIMER_interface.h"
#include<util/delay.h>
#include"DIO_private.h"
u8 Sec=0,Min=0,Hour=0,Timer1_Flag=0;
u8 EXTI_Flag=0;
u16 Global_u16SecTime=0,Global_TimerVal=0;
void EXTI_Handler(void);
void TIMER0_Handler(void);
void TIMER1_Handler(void);
void Clear_Leds(void);
void Sec_Maker(void);
void Min_Maker(void);
void Hour_Maker(void);

void main(void)
{
	u8 Local_u8counter=0;
	DIO_u8Init();
	GIE_voidEnable();
	EXTI_voidInt0init();
	EXTI_u8Int0SetCallBack(&EXTI_Handler);
	TIMER1_Init();
	TIMER0_Init();
	TIMER0_CallBack(&TIMER0_Handler);
	TIMER1_CallBack(&TIMER1_Handler);

	while(1){}
//	{
//
//		if(Global_u16SecTime!=0)
//		{
//
//			_delay_us(Global_u16SecTime);
//			Local_u8counter++;
//
//			if(Local_u8counter==60)
//			{
//				Local_u8counter=0;
//			}
//			if((Local_u8counter==0)||(Local_u8counter==90)||(Local_u8counter==180)||(Local_u8counter==270)||(Sec==Local_u8counter)||(Min==Local_u8counter)||(Hour*5==Local_u8counter))
//			{
//				if((Local_u8counter==0)||(Local_u8counter==90)||(Local_u8counter==180)||(Local_u8counter==270))
//				{
//					PORTA|=0b00000011;
//				}
//				if(Sec==Local_u8counter)
//				{
//					Sec_Maker();
//				}
//				if(Min==Local_u8counter)
//				{
//					Min_Maker();
//				}
//				if(Hour*5==Local_u8counter)
//				{
//					Hour_Maker();
//				}
//			}
//			else
//			{
//				Clear_Leds();
//			}
//		}
//
//	}
}

//void Clear_Leds(void)
//{
//	PORTB&=0;
//	PORTA&=0b11111100;
//}
//void Sec_Maker(void)
//{
//	PORTB|=0xff;
//}
//void Min_Maker(void)
//{
//	PORTB|=0xff;
//	PORTB&=0b01111111;
//}
//void Hour_Maker(void)
//{
//	PORTB|=0xff;
//	PORTB&=0b00111111;
//}
//
void EXTI_Handler(void)
{
	DIO_u8_PORTB_REG=0b11111111;
//	static u8 Local_ExtiCounter=1;
//
//	Local_ExtiCounter++;
//
//	if(Local_ExtiCounter%2==0)
//	{
//		TIMER1_NormalEnable();
//	}
//	else
//	{
//		EXTI_Flag=1;
//		if(Timer1_Flag==0)
//		{
//			TIMER1_NormalDisable();
//			/*Get the whole interval for 1 iteration*/
//			TIMER1_GetVal(&Global_TimerVal);
//			/*interval of 1 angle*/
//			Global_u16SecTime=Global_TimerVal/60;
//		}
//
//	}
//	if(Local_ExtiCounter==255)
//		Local_ExtiCounter=1;
}

void TIMER0_Handler(void)
{
//	Sec++;
//	if(Sec==60)
//	{
//		Sec=0;
//		Min++;
//		if(Min==60)
//		{
//			Min=0;
//			Hour++;
//			if(Hour==12)
//				Hour=0;
//		}
//	}
}
//
//
void TIMER1_Handler(void)
{
//	static u8 counter=0;
//	counter++;
//	Timer1_Flag=1;
//	if(EXTI_Flag==1)
//	{
//		TIMER1_GetVal(&Global_TimerVal);
//		Global_TimerVal=Global_TimerVal+(counter*65536);
//		Global_u16SecTime=Global_TimerVal/60;
//	}
//
}
