/*
 * Obstacle_Avoiding_Car.c
 *
 * Created: 3/17/2024 2:57:11 AM
 * Author : future
 */ 

/* LIB */
#include "UTIL/STD_TYPES.h"
#include "UTIL/BIT_MATH.h"
//#include "stdio.h"
#define  F_CPU 8000000UL
#include <util/delay.h>
/* MCAL */
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/TIMER/TIMER_interface.h"
/* HAL */
#include "HAL/SERVO/SERVO_interface.h"
#include "HAL/ULTRASONIC/ULTRASONIC_interface.h"





/* Configuration L298 Port and pits */
#define Robot_u8_MOTOR_DRIVER_L298_PORT            DIO_PORTA
#define Robot_u8_MOTOR_DRIVER_L298_IN1             DIO_PIN0
#define Robot_u8_MOTOR_DRIVER_L298_IN2             DIO_PIN1
#define Robot_u8_MOTOR_DRIVER_L298_IN3             DIO_PIN2
#define Robot_u8_MOTOR_DRIVER_L298_IN4             DIO_PIN4
/* Init modes Speeds*/
#define Robot_u8_INIT_SPEED                        60 	/* 60 % */
#define Robot_u8_ObstacleAvoidingMode_SPEED        60  	/* 60 % */


void Set_Car_Speed(u8 Speed)
{
	/* Speed control by Timer0 and Timer2 */
	TIMER_voidTimer0GeneratePWM(Speed);
	TIMER_voidTimer2GeneratePWM(Speed);
}


/************************************************************************/
/*                                CAR MOVES                              */
/************************************************************************/


void Car_Stop(void)
{
	/* Stop motors */
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_PIN_LOW);
}
void Car_Forward(void)
{
	/* all motors forward */
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_PIN_HIGH);
}
void Car_Backward(void)
{
	/* all motors Backward */
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_PIN_LOW);
}
void Car_Left(void)
{
	/* Left motors forward and Right motors Backward */
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_PIN_HIGH);
}
void Car_Right(void)
{
	/* Left motors Backward and Right motors forward */
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_PIN_LOW);
}

void Robot_voidStep(void)
{
	/* After Stop take Step */
	Set_Car_Speed(60);
	Car_Forward();
	_delay_ms(170);
}

void Car_Right90(void)
{
	
	/* turn 90 degree Right */
	Set_Car_Speed(60);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_HIGH);
	DIO_setPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
	/* value of delay will change by change (voltage and arena) */
	
	_delay_ms(100);
	Car_Stop();
	Set_Car_Speed(Robot_u8_INIT_SPEED);

}
void Car_Left90(void)
{
	/* turn 90 degree Left */
	Set_Car_Speed(60);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	/* value of delay will change by change (voltage and arena) */
	_delay_ms(100);
	Car_Stop();
	Set_Car_Speed(Robot_u8_INIT_SPEED);
}
void Car_Reverse(void)
{
	/* turn 180 degree  */
	Set_Car_Speed(60);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_HIGH);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_LOW);
	DIO_setPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_LOW);
	DIO_setPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	/* value of delay will change by change (voltage and arena) */
	_delay_ms(300);
	Car_Stop();
	Set_Car_Speed(Robot_u8_INIT_SPEED);
}

void Car_Compare(u16 LeftObject,u16 RightObject)
{
	  /* Comparison between two directions and set Orientation */
	  if (LeftObject > RightObject)
	  {
		  Car_Left();
		  Car_Left();
	  }
	  else if (LeftObject <= RightObject)
	  {
		  Car_Right();
		  Car_Right();
	  }
	  else if (LeftObject < 10 && RightObject < 10)
	  {
		  Car_Reverse();
		  Car_Reverse();
	  }
}




void Start_AutoMode_Car(void)
{
  u16 Local_u16LeftObject = 0, Local_u16RightObject = 0, Local_u16DistanceObject = 0;
    Set_Car_Speed(Robot_u8_ObstacleAvoidingMode_SPEED);

    while (1)
    {
        /* Read distance -->if no object go forward */
        Local_u16DistanceObject = ULTRASONIC_u16GetDistance();
		
        if (Local_u16DistanceObject == 0)
        {
            Local_u16DistanceObject = 250;
        }
        if (Local_u16DistanceObject <= 15)
        {
            /* if find object stop
             * Read left and right
             * and Orientation to open road
             *   */
            Car_Backward();
            _delay_ms(300);
            /* Stop motors*/
            Car_Stop();
            _delay_ms(300);
            /* Servo turn to Left  then read distance*/
            SERVO_voidTimer1ServoSetAngleOCR1B(135);
			 _delay_ms(300);
            Local_u16LeftObject = ULTRASONIC_u16GetDistance();
			_delay_ms(300);
     
            /* Servo turn to Right then read distance*/
	
            SERVO_voidTimer1ServoSetAngleOCR1B(360);
          _delay_ms(300);
           Local_u16RightObject = ULTRASONIC_u16GetDistance();
           _delay_ms(300);
            /* Set Servo direction */

            SERVO_voidTimer1ServoSetAngleOCR1B(270);
            _delay_ms(300);
			
            /* Comparison between to direction and set Orientation*/
            Car_Compare(Local_u16LeftObject, Local_u16RightObject);
        }
        else
        {
            /* if no object go forward */
		
           Car_Forward();
            _delay_ms(1000);
        }
    }


}
/*********************************************************** Initialization ****************************************************************/
void Robot_voidInit(void)
{

	/************************** Init Timer ************************************/
	TIMER_voidTimer0Init();
	DIO_setPinDirection(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT);
	TIMER_voidTimer2Init();
	DIO_setPinDirection(DIO_PORTD , DIO_PIN7 , DIO_PIN_OUTPUT);
	/**************************** Init Servo **********************************/
	SERVO_voidTimer1InitOCR1B();
	SERVO_voidTimer1ServoSetAngleOCR1B(270);
//
	/**************************** Init ULTRASONIC *****************************/
	ULTRASONIC_voidInit();
	
/***************************** INIT SPEAD ****************************/
	Set_Car_Speed(Robot_u8_INIT_SPEED);
/************************************** MOTOR DRIVER L298******************************************************/
	DIO_setPinDirection(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_PIN_OUTPUT);
	DIO_setPinDirection(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN0,DIO_PIN_OUTPUT);
	
	DIO_setPinDirection( DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection( DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);
}


/************************************************************************/
/*                         Main                                          */
/************************************************************************/
int main(void){
	
	/* Initialization Robot */
	Robot_voidInit();	
    while(1)
    {         
		Start_AutoMode_Car();
	
    }

return 0;
}

