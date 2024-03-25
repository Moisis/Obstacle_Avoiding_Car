/*
 * Ultrasonic_program.c
 *
 * Created: 12/11/2023 7:28:53 PM
 *  Author: Miso
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"

#include "../../MCAL/TIMER/TIMER_0/TIMER0_config.h"
#include "../../MCAL/TIMER/TIMER_0/TIMER0_interface.h"
#include "../../MCAL/TIMER/TIMER_0/TIMER0_private.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "../../MCAL/GI/GI_interface.h"
#include "../../MCAL/GI/GI_private.h"
#include "../../MCAL/EXTI/EXTI_interface.h"

#include "../../HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "../../HAL/ULTRASONIC/ULTRASONIC_config.h"

u8 sensor_working=0;
u8 rising_edge=0;
u32 timer_counter=0;
f64 distance;

void ULTRASONIC_Init(void)
{
	DIO_setPinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(ULTRASONIC_ECHO_PORT,ULTRASONIC_ECHO_PIN,DIO_PIN_INPUT);
	DIO_setPinValue(ULTRASONIC_ECHO_PORT,ULTRASONIC_ECHO_PIN,DIO_PIN_HIGH);
	EXTI_enable(EXTI_INT1,EXTI_ANY_LOGICAL_CHANGE);
	TMR0_init();
	TMR0_Start();
	
}
void Ultrasonic_Get_Distance(f64* DistanceValue)
{
	if (!sensor_working)
	{
		DIO_setPinValue(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,DIO_PIN_HIGH);
		_delay_us(15);
		DIO_setPinValue(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,DIO_PIN_LOW);
		sensor_working=1;

	}
	*DistanceValue=distance;
}


void  __vector_2(void) __attribute__((signal));
void  __vector_2(void)
{
	if(sensor_working==1)
	{
		if (rising_edge==0)
		{
			TCNT0=0X00;
			rising_edge=1;
			timer_counter=0;
		}
		else
		{
			distance=(343*(timer_counter*256+TCNT0)/320000)+1;
			_delay_ms(40);
			timer_counter=0;
			rising_edge=0;
		}
	}
}


void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	timer_counter++;
	if( timer_counter >1462)
	{
		TCNT0 = 0x00;
		sensor_working=0;
		rising_edge=0;
		timer_counter=0;
	}
	
}