/******************************************************************************/
/******************************************************************************/
/********************    Author:Abdelrahman    ********************************/
/********************    Layer:MCAL            ********************************/
/********************    SWC:TIMER         	   ********************************/
/********************    Version:1.00          ********************************/
/******************************************************************************/
/******************************************************************************/





#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

void TIMER0_Init(void);
void TIMER0_CallBack(void (*Copy_pvCallBack)(void));

void TIMER1_Init(void);
void TIMER1_NormalEnable(void);
void TIMER1_NormalDisable(void);
void TIMER1_CallBack(void (*Copy_pvCallBack)(void));
void TIMER1_GetVal(volatile u16 *Copy_u16Val);
void TIMER2_Init(void);
void TIMER2_Call_Back(void (*Copy_pvCallBack)(void));
void TIMER2_Delay(u32 Copy_u32Val);
void TIMER2_GetVal(u32 *Copy_Val);
void TIMER2_Enable(void);




#endif
