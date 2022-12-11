/*********************************************/
/* 				Name : Mohamed Essam 		 */
/*				Date : 10/12/2022			 */
/*				SWC  :	TIMERS	 			 */
/*			version  : 	1.0					 */
/*********************************************/

#ifndef TMR_PRIVATE_H
#define TMR_PRIVATE_H

#define TMR_u8_TIMSK	*((volatile u8*)0x59)
#define TMR_u8_TIFR		*((volatile u8*)0x58)
#define TMR_u8_TCCR0	*((volatile u8*)0x53)
#define TMR_u8_TCNT0	*((volatile u8*)0x52)
#define TMR_u8_TCCR1A	*((volatile u8*)0x4F)
#define TMR_u8_TCCR1B	*((volatile u8*)0x4E)
#define TMR_u8_TCNT1H	*((volatile u8*)0x4D)
#define TMR_u8_TCNT1L	*((volatile u8*)0x4C)
#define TMR_u8_TCNT2	*((volatile u8*)0x44)




#endif