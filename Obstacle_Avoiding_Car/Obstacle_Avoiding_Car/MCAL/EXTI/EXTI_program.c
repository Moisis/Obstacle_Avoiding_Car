/*
 * EXTI_program.c
 *
 * Created: 12/25/2023 7:57:39 PM
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"

/* MCAL */
#include "EXTI_interface.h"
#include "EXTI_private.h"


static void (*private_pCallBackINT0)(void) = NULL;
static void (*private_pCallBackINT1)(void) = NULL;
static void (*private_pCallBackINT2)(void) = NULL;


void EXTI_enable(u8 interruptSource, u8 interruptTriggerEdge)
{
	switch(interruptSource)
	{
		case EXTI_INT0:
		switch(interruptTriggerEdge)
		{
			case EXTI_RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
			case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
			case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			
			case EXTI_ANY_LOGICAL_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
		}
		SET_BIT(GICR,INT0); // Enable INT0
		break;
		
		case EXTI_INT1:
		switch(interruptTriggerEdge)
		{
			case EXTI_RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
			case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
			case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			
			case EXTI_ANY_LOGICAL_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
		}
		SET_BIT(GICR,INT1); // Enable INT1
		break;
		
		case EXTI_INT2:
		switch(interruptTriggerEdge)
		{
			case EXTI_RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
			
			case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
		}
		SET_BIT(GICR,INT2); // Enable INT2
		break;
	}
}


void EXTI_disable(u8 interruptSource)
{
	switch(interruptSource)
	{
		case EXTI_INT0:
		CLR_BIT(GICR,INT0); // Disable INT0
		break;
		
		case EXTI_INT1:
		CLR_BIT(GICR,INT1); // Disable INT1
		break;
		
		case EXTI_INT2:
		CLR_BIT(GICR,INT2); // Disable INT2
		break;
	}
}


void EXTI_setCallBackINT0(void (*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackINT0 = ptrToFun;
	}
}


void EXTI_setCallBackINT1(void (*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackINT1 = ptrToFun;
	}
}


void EXTI_setCallBackINT2(void (*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackINT2 = ptrToFun;
	}
}


void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(private_pCallBackINT0 != NULL)
	{
		private_pCallBackINT0();	
	}
}





void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if(private_pCallBackINT2 != NULL)
	{
		private_pCallBackINT2();
	}
}