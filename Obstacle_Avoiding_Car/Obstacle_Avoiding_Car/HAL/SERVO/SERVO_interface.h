
#ifndef SERVO_INTERFACE_H
#define SERVO_INTERFACE_H


#define SERVO_PORT DIO_PORTD
#define SERVO_PIN  DIO_PIN5



#define FORWARD_Angle      135 
#define RIGHT_Angle          45
#define LEFT_Angle  270

void SERVO_Init(void);
void SERVO_ON (f32 angle);
void SERVO_Off (void);





#endif
