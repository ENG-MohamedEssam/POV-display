/*********************************************/
/* 				Name : Mohamed Essam 		 */
/*				Date : 9/10/2021			 */
/*				SWC  :	EXTI	 			 */
/*			version  : 1.0					 */
/*********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_register.h"
#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

/* Global Pointer to function to hold INT0 ISR Adress */
void (*EXTI_PvInt0Func)(void) = NULL ;


void EXTI_voidInt0init(void)
{
	/* 1- Check Sense Control */
#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#else
#error "Wrong INT0_SENSE configuration option"
#endif
	/* Check prephiral interrupt enable inital state */
#if INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);

#elif INT0_INITIAL_STATE == ENABLED
	ClR_BIT(GICR,GICR_INT0);

#else
#error "Wrong INT0_INITIAL_STATE input option"
#endif

}

u8 EXTI_u8Init0SetSenseControl(u8 Copy_u8Sense)
{

	switch(Copy_u8Sense)
	{
	case LOW_LEVEL :
		CLR_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
		break;
	case ON_CHANGE :
		SET_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
		break;
	case FALLING_EDGE :
		CLR_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
		break;
	case RISING_EDGE :
		SET_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
		break;
	default : break;
	}
	return 0;
}

u8 EXTI_u8Int0SetCallBack(void (*Copy_PvInt0Func)(void))
{
	u8 Local_u8ErrorState = 0;
	if (Copy_PvInt0Func != NULL)
	{
		EXTI_PvInt0Func = Copy_PvInt0Func;
	}
	else
	{
		Local_u8ErrorState = 1;
	}


	return Local_u8ErrorState;

}

/* ISR of INT0 */
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if (EXTI_PvInt0Func != NULL)
	{
		EXTI_PvInt0Func();
	}
	else
	{
		/* Do nothing   */
	}
}
