/*********************************************/
/* 				Name : Mohamed Essam 		 */
/*				Date : 9/10/2021			 */
/*				SWC  :	GIE 	 			 */
/*			version  : 1.0					 */
/*********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_register.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG,SREG_I);
}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG,SREG_I);
}
