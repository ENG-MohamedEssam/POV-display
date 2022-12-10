

#include"BIT_MATH.h"
#include "STD_TYPES.h"
#include"TIMER_interface.h"
#include"TIMER_register.h"


void(*Local_pvCallBack)(void)=NULL;
void(*Local_pvCallBack1)(void)=NULL;
void TIMER0_Init(void)
{
	/*mode selection*/
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	/*wave form selection(CTC)*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	/*CTC Config*/
	OCR0=250;
	/*prescaller config*/
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS02);
	/*interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_OCR0);

}

void TIMER0_CallBack(void (*Copy_pvCallBack)(void))
{
	Local_pvCallBack=Copy_pvCallBack;
}

//////////////////////////////////////
void TIMER1_Init(void)
{
	/*mode selection*/
	CLR_BIT(TCCR1B,TCCR1A_COM1A0);
	CLR_BIT(TCCR1B,TCCR1A_COM1A1);

	/*wave form selection(Normal)*/
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	/*interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_TOIE1);

}

void TIMER1_CallBack(void (*Copy_pvCallBack)(void))
{
	Local_pvCallBack1=Copy_pvCallBack;
}

void TIMER1_NormalEnable(void)
{

	/*prescaler config /8*/
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
}


void TIMER1_NormalDisable(void)
{
	/*prescaler config Timer Disable*/
	CLR_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	TCNT1=0x0000;

}

void TIMER1_GetVal(u16 *Copy_u16Val)
{
	*Copy_u16Val=TCNT1;
}

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	//Local_pvCallBack();
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	static  u16 Local_u16Counter=0;
	Local_u16Counter++;
	if(Local_u16Counter==4000)
	{
		Local_u16Counter=0;
		Local_pvCallBack1();
	}


}


