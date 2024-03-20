/*
 * GI_program.c
 *
 * Created: 12/25/2023 9:49:08 PM
 *  Author: Miso
 */ 


/* UTILES_LIB */
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"


/* MCAL */
#include "../../MCAL/GI/GI_interface.h"
#include "../../MCAL/GI/GI_private.h"


void GI_enable(void)
{
	SET_BIT(SREG,I);
}


void GI_disable(void)
{
	CLR_BIT(SREG,I);
}