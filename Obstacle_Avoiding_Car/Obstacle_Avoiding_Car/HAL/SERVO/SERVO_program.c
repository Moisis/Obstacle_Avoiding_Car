


/*UTIL Layer */
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"


/* HAL Layer */

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER/TIMER_1/TMR1_interface.h"



/* MCAL Layer */
#include "../../HAL/SERVO/SERVO_interface.h"



void SERVO_Init(void)
{
	/* OC1A pin as output pin */
	DIO_setPinDirection(SERVO_PORT, SERVO_PIN, DIO_PIN_OUTPUT);
	
	/* TMR1 init at pwm mode 14 */
	TMR1_init();
}




void SERVO_ON(f32 Angle)
{
	f32 DutyCycle;
	DutyCycle=5.0+(Angle/36.0);
	TMR1_setFastPWM_usingMode14(DutyCycle , 50 );
	TMR1_start();

}



void SERVO_Off(void)
{
	/* TMR1 stop */
	TMR1_stop();
}