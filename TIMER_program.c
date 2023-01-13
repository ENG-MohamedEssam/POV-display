

#include"BIT_MATH.h"
#include "STD_TYPES.h"
#include"TIMER_interface.h"
#include"TIMER_register.h"
//#include"DIO_interface.h"
static u32 Global_Counter2=0;
static u32 Local_counter=0;

void(*Local_pvCallBack)(void)=NULL;
void(*Local_pvCallBack1)(void)=NULL;
void(*Local_pvCallBack4)(void)=NULL;
void TIMER0_Init(void)
{
	/*mode selection*/
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	/*wave form selection(CTC)*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	TCNT0=0;
	/*CTC Config*/
	OCR0=250;
	/*prescaller config*/
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS02);

}

void TIMER0_CallBack(void (*Copy_pvCallBack)(void))
{
	Local_pvCallBack=Copy_pvCallBack;
	/*interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_OCR0);
}

//////////////////////////////////////
void TIMER1_Init(void)
{
	/*mode selection*/
	CLR_BIT(TCCR1B,TCCR1A_COM1A0);
	CLR_BIT(TCCR1B,TCCR1A_COM1A1);
	TCNT1=0;
	/*wave form selection(Normal)*/
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);



}

void TIMER1_CallBack(void (*Copy_pvCallBack)(void))
{
	Local_pvCallBack1=Copy_pvCallBack;
}

void TIMER1_NormalEnable(void)
{
	TCNT1=0;
	/*prescaler config /8*/
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	/*interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_TOIE1);
}


void TIMER1_NormalDisable(void)
{
	/*prescaler config Timer Disable*/
	CLR_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	CLR_BIT(TIMSK,TIMSK_TOIE1);
	TCNT1=0;
}

void TIMER1_GetVal(volatile u16 *Copy_u16Val)
{
	*Copy_u16Val=TCNT1;
}

//////////////////////////////////

void TIMER2_Init(void)
{
//	CLR_BIT(TCCR2,TCCR2_COM21);
//	CLR_BIT(TCCR2,TCCR2_COM20);
//	/*wave form selection(CTC)*/
//	CLR_BIT(TCCR2,TCCR2_WGM20);
//	SET_BIT(TCCR2,TCCR2_WGM21);
//	/*CTC Config*/
//	OCR2=250;
	/*mode selection*/
		CLR_BIT(TCCR2,TCCR2_COM21);
		CLR_BIT(TCCR2,TCCR2_COM20);
		/*wave form selection(CTC)*/
		CLR_BIT(TCCR2,TCCR2_WGM20);
		SET_BIT(TCCR2,TCCR2_WGM21);
		TCNT2=0;
		/*CTC Config*/
		OCR2=250;
		/*prescaller config*/
		CLR_BIT(TCCR2,TCCR0_CS01);
		CLR_BIT(TCCR2,TCCR0_CS00);
		CLR_BIT(TCCR2,TCCR0_CS02);



}
void TIMER2_Call_Back(void (*Copy_pvCallBack)(void))
{
	Local_pvCallBack4=Copy_pvCallBack;

}

void TIMER2_Delay(u32 Copy_u32Val)
{
	Global_Counter2=Copy_u32Val;
//	test=Global_Counter2;
	if(Copy_u32Val<=250)
	{
		TCNT2=250-Copy_u32Val;
		OCR2=250;
		SET_BIT(TIMSK,TIMSK_OCIE2);
	}
	else
	{
		SET_BIT(TIMSK,TIMSK_OCIE2);
	}
}

void TIMER2_Enable(void)
{
	Local_counter=0;

	SET_BIT(TCCR2,TCCR2_CS21);
	CLR_BIT(TCCR2,TCCR2_CS20);
	CLR_BIT(TCCR2,TCCR2_CS22);
//	SET_BIT(TIMSK,TIMSK_OCIE2);
}

void TIMER2_Disable(void)
{
	Local_counter=0;
	CLR_BIT(TCCR2,TCCR2_CS21);
	CLR_BIT(TCCR2,TCCR2_CS20);
	CLR_BIT(TCCR2,TCCR2_CS22);
	CLR_BIT(TIMSK,TIMSK_OCIE2);
}

void TIMER2_GetVal(u32 *Copy_Val)
{
	u8 timer=TCNT2;

	*Copy_Val=(u32)((Local_counter*250)+timer);
//	*Copy_Val=Local_counter;


}




void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	Local_pvCallBack1();
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	static  u16 Local_u16Counter=0;
	Local_u16Counter++;
	if(Local_u16Counter==4000)
	{
		Local_u16Counter=0;
		Local_pvCallBack();
	}


}

void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	static u32 Val1=0;
	static u32 val2=0;
	Local_counter++;
	Val1=Local_counter*250;
	val2=Global_Counter2-Val1;


	if(Global_Counter2<=250)
	{
		Local_counter=0;
		Local_pvCallBack4();
		CLR_BIT(TIMSK,TIMSK_OCIE2);
	}
	else if(val2 <= 250)
	{

		Global_Counter2=val2;
		TCNT2=250-val2;
		OCR2=250;
	}

}

