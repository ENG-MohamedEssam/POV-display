/*********************************************/
/* 				Name : Mohamed Essam 		 */
/*				Date : 4/12/2022			 */
/*				SWC  :	GIE		 			 */
/*			version  : 	1.0					 */
/*********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_private.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG,7);

}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG,7);

}
