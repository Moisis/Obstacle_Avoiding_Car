/*
 * Obstacle_Avoiding_Car.c
 *
 * Created: 3/17/2024 2:57:11 AM
 * Author : future
 */ 

#define  F_CPU 16000000UL
#include <util/delay.h>
/* LIB */
#include "UTIL/STD_TYPES.h"
#include "UTIL/BIT_MATH.h"
//#include "stdio.h"

/* MCAL */
#include "MCAL/DIO/DIO_interface.h"

#include "MCAL/EXTI/EXTI_interface.h"
#include "MCAL/GI/GI_interface.h"

#include "MCAL/TIMER/TIMER_0/TIMER0_interface.h"
#include "MCAL/TIMER/TIMER_0/TIMER0_config.h"
#include "MCAL/TIMER/TIMER_1/TMR1_interface.h"
#include "MCAL/TIMER/TIMER_1/TMR1_config.h"
#include "MCAL/TIMER/TIMER_2/TMR2_interface.h"
#include "MCAL/TIMER/TIMER_2/TMR2_config.h"



/* HAL */
#include "HAL/SERVO/SERVO_interface.h"
#include "HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "HAL/DC_MOTOR/DC_MOTOR_interface.h"
#include "HAL/LCD/LCD_interface.h"



static u16 Speed=85;

#define MAX_SPEED                         100
#define MIN_SPEED                         0



/************************************************************************/
/*                         Main                                          */
/************************************************************************/
int main(void){
	
	/* Initialization Robot */
	
	LCD_init();
	
	GI_enable();
	SERVO_Init();
	SERVO_ON(FORWARD_Angle);
	
	ULTRASONIC_Init();
	
	MOTORS_Init();
	CAR_MoveForward();
	CAR_SendDutyCycleAndStart(Speed);
	
	DIO_setPinDirection( DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection( DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);

	f64 UltraSonic_ForwardValue;
	f64 UltraSonic_RightValue;
	f64 UltraSonic_LeftValue;
	
    while(1)
    {         
		
		Ultrasonic_Get_Distance(&UltraSonic_ForwardValue);
		
	
		if ( UltraSonic_ForwardValue>=20.00)
		{
			DIO_setPinValue( DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
			CAR_MoveForward();
			
			DIO_setPinValue( DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
		}
		else
		{
			
		DIO_setPinValue( DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
		_delay_ms(1000);
		DIO_setPinValue( DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
		
			CAR_Stop();
			CAR_MoveBackward();
			_delay_ms(500);
			CAR_Stop();

			// Measure Distance At Right
			SERVO_ON(RIGHT_Angle);
	
 			Ultrasonic_Get_Distance(&UltraSonic_RightValue);
			LCD_clear();
			LCD_goToSpecificPosition(1,1);
			LCD_writeString("R=");
			LCD_writeNumber(UltraSonic_RightValue);

			LCD_writeString("CM");

			_delay_ms(1000);
			// Measure Distance At Left
			SERVO_ON(LEFT_Angle);
			
			Ultrasonic_Get_Distance(&UltraSonic_LeftValue);
			 LCD_clear();
			LCD_goToSpecificPosition(1,2);
			LCD_writeString("L=");
			LCD_writeNumber(UltraSonic_LeftValue);
			LCD_writeString("CM");
			_delay_ms(1000);
			
			
			if (UltraSonic_RightValue > UltraSonic_LeftValue)
						{
							//MOVE Right
							LCD_clear();
							
							LCD_writeString("   Move Right  ");
							SERVO_ON(FORWARD_Angle);
							_delay_ms(100);
							CAR_MoveForwardRight();
							_delay_ms(500);
							CAR_Stop();

			}
 			else
 			{
				 
 				//MOVE Left
				 
				 LCD_clear();
				 LCD_writeString("  Move LEFT   ");
 				SERVO_ON(FORWARD_Angle);
 				_delay_ms(100);
 				CAR_MoveForwardleft();	
 				_delay_ms(500);
 				CAR_Stop();
	}
		}
		
	
    }

return 0;
}

