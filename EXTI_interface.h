/*********************************************/
/* 				Name : Mohamed Essam 		 */
/*				Date : 9/10/2021			 */
/*				SWC  :	EXTI	 			 */
/*			version  : 1.0					 */
/*********************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define LOW_LEVEL		1
#define ON_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4

void EXTI_voidInt0init(void);
		  
void EXTI_voidInt1init(void);
		  
void EXTI_voidInt2init(void);
/* Description : A fuction to set the required sense control to INT0 using post build configuration
 * Input : Copy_u8Sense
 * Options :
 *			1- LOW_LEVEL
 *          2- ON_CHANGE
 *          3- FALLING_EDGE
 *          4- RISING_EDGE
 * Output : Error Status with type u8
 * */
u8 EXTI_u8Int0SetSenseControl(u8 Copy_u8Sense);
u8 EXTI_u8Int0SetCallBack(void (*Copy_PvInt0Func)(void));

#endif 
