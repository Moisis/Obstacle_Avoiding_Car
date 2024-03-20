/*
 * Ultrasonic_program.c
 *
 * Created: 12/11/2023 7:28:53 PM
 *  Author: Miso
 */ 

#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"
#include "../../MCAL/GI/GI_interface.h"

#include "../../HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "../../HAL/ULTRASONIC/ULTRASONIC_config.h"

u8 ULTRASONIC_EdgeCounter = 0;
u16 ULTRASONIC_TimeON = 0;

void ULTRASONIC_voidInit(void)
{
	GI_enable();
	TIMER_voidTimer1ICUInit();
	TIMER_voidTimer1ICUSetCallBack(&ULTRASONIC_voidEdgeProcessing);
	DIO_setPinDirection(ULTRASONIC_ECHO_PORT,ULTRASONIC_ECHO_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,DIO_PIN_OUTPUT);
	DIO_setPinValue(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,DIO_PIN_LOW);
	
}
void ULTRASONIC_Trigger(void)
{
	DIO_setPinValue(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,DIO_PIN_HIGH);
	_delay_us(10);
	DIO_setPinValue(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,DIO_PIN_LOW);
	
}
u16 ULTRASONIC_u16GetDistance(void)
{
	u16 Local_u16Distance;
	for (int Local_u8Couter=0;Local_u8Couter<16;Local_u8Couter++)
	{
		 ULTRASONIC_Trigger();
		 /* HC-SR-04 */
		 /* Sound velocity = 340.00 m/s = 34000 cm/s
		  * The distance of Object (in cm) = (340000∗Time)/2 = 17000 * Time
		  * Prescaler F_CPU/8 for timer frequency.
		  * The timer gets incremented after 1 us time elapse.
		  * Distance (cm)= 17000 x (TIMER value) x 1 x 10^-6 cm
	      * Distance (cm)= (TIMER value) / 58 cm
	      * */
	     Local_u16Distance=(ULTRASONIC_TimeON/(57.828125)); /* Calculating Distance In cm */
	}
	return Local_u16Distance;
}



void ULTRASONIC_voidEdgeProcessing(void)
{
	ULTRASONIC_EdgeCounter++;
	if(ULTRASONIC_EdgeCounter == 1)
	{
		TIMER_voidClearTimer1Value();
		TIMER_voidTimer1ICUSetTriggerEdge(TIMER1_ICU_FALLING_EDGY_TYPE_MODE);
	}
	else if(ULTRASONIC_EdgeCounter == 2)
	{
		ULTRASONIC_EdgeCounter = TIMER_voidTimer1ICUGetInputCaptureValue();
		TIMER_voidClearTimer1Value();
		ULTRASONIC_EdgeCounter=0;
		TIMER_voidTimer1ICUSetTriggerEdge(TIMER1_ICU_RISING_EDGY_TYPE_MODE);
	}
}
