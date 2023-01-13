#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "TIMER_interface.h"

//#include"CLCD_interface.h"
//#define F_CPU 8000000UL
//#include<avr/delay.h>

#define CLK		*((volatile u8*)0x51)

u8 Delay_Flag=0,TIMER2_Flag=0;
u8 Global_T2Flag=0;
u8 Sec=0,Min=0,Hour=0,Timer1_Flag=0;
u8 EXTI_Flag=0;
volatile u32 Global_u16SecTime=0;
volatile u16 Global_TimerVal=0;
u8 Local_u8counter=0;


void EXTI_Handler(void);
void TIMER0_Handler(void);
void TIMER1_Handler(void);
void Clear_Leds(void);
void Sec_Maker(void);
void Min_Maker(void);
void Hour_Maker(void);
void Dot_maker(void);
void TIMER2_Handler(void);

void main(void)
{
	SET_BIT(CLK,0);
	SET_BIT(CLK,1);
	SET_BIT(CLK,2);
	SET_BIT(CLK,3);
	//	u32 TIMER2_Val=0,Dot_Maker=0;

	PORT_voidInit();
	GIE_voidEnable();
	EXTI_voidInt0init();
	TIMER0_Init();
	TIMER1_Init();
	TIMER2_Init();


	EXTI_u8Int0SetCallBack(&EXTI_Handler);
	TIMER0_CallBack(&TIMER0_Handler);
	TIMER1_CallBack(&TIMER1_Handler);
	TIMER2_Call_Back(&TIMER2_Handler);
//	CLCD_voidInit();

	//	CLR_BIT(PORTD,0);
	//	_delay_ms(500);
	//	SET_BIT(PORTD,0);
	//	CLR_BIT(PORTD,0);

	while(1)
	{

//		CLCD_voidGoToXY(0,0);
//		CLCD_voidWriteNumber(Local_u8counter);
//		CLCD_voidGoToXY(1,0);
//		CLCD_voidWriteNumber(Global_u16SecTime*60);
//		CLCD_voidGoToXY(0,5);
//		CLCD_voidWriteNumber(Hour);
//		CLCD_voidGoToXY(0,7);
//		CLCD_voidSendData(":");
//		CLCD_voidGoToXY(0,8);
//		CLCD_voidWriteNumber(Min);
//		CLCD_voidGoToXY(0,10);
//		CLCD_voidSendData(":");
//		CLCD_voidGoToXY(0,11);
//		CLCD_voidWriteNumber(Sec);

		if(Global_TimerVal==0)
		{
			if(TIMER2_Flag==1)
			{
				TIMER2_Flag=0;
				TIMER2_Delay(Global_u16SecTime);
			}
		}

		if(Local_u8counter==60)
		{
			Local_u8counter=0;
			Global_u16SecTime=0;

		}
		if(Global_u16SecTime!=0)
		{
			if((Sec==Local_u8counter)||(Min==Local_u8counter)||(Hour*5==Local_u8counter)||(Local_u8counter==0)||(Local_u8counter==15)||(Local_u8counter==45)||(Local_u8counter==30))
			{
				if((Local_u8counter==0)||(Local_u8counter==15)||(Local_u8counter==45)||(Local_u8counter==30))
					Dot_maker();
				if(Sec==Local_u8counter)
				{
					Sec_Maker();
				}
				if(Min==Local_u8counter)
				{
					Min_Maker();
				}
				if(Hour*5==Local_u8counter)
				{
					Hour_Maker();
				}
			}
			else
			{
				Clear_Leds();
			}

		}
	}

}



void Clear_Leds(void)
{
	PORTB&=0;
	PORTA&=0b11111100;
}

void Sec_Maker(void)
{
	PORTB=0xff;
}

void Min_Maker(void)
{
	PORTB=0b01111111;
}

void Hour_Maker(void)
{
	PORTB=0b00111111;
}

void Dot_maker(void)
{
	PORTA|=0b00000011;
}

void EXTI_Handler(void)
{

	static u8 Flag_State=0;

	if(Flag_State==0)
	{
		Flag_State=1;
		Timer1_Flag=0;
		EXTI_Flag=0;
		TIMER1_NormalEnable();
		Global_TimerVal=0;
	}

	else
	{
		Flag_State=0;
		EXTI_Flag=1;

		if(Timer1_Flag==0)
		{

			TIMER1_NormalDisable();

			/*Get the whole interval for 1 iteration*/
			TIMER1_GetVal(&Global_TimerVal);
			/*interval of 1 angle*/
			Global_u16SecTime=Global_TimerVal/60;
			TIMER2_Enable();
			TIMER2_Delay(Global_u16SecTime);
		}

	}
}


void TIMER0_Handler(void)
{
	Sec++;
	if(Sec==60)
	{
		Sec=0;
		Min++;
		if(Min==60)
		{
			Min=0;
			Hour++;
			if(Hour==12)
				Hour=0;
		}
	}
}


void TIMER1_Handler(void)
{

	static u32 counter=0;
	counter++;
	Timer1_Flag=1;
	if(EXTI_Flag==1)
	{
		TIMER1_GetVal(&Global_TimerVal);
		Global_u16SecTime=Global_TimerVal+(counter*65536);
		Global_u16SecTime=Global_u16SecTime/60;
		TIMER2_Enable();
		TIMER2_Delay(Global_u16SecTime);

		TIMER1_NormalDisable();
		counter=0;
	}
}

void TIMER2_Handler(void)
{
	TIMER2_Flag=1;
	Local_u8counter++;
}
