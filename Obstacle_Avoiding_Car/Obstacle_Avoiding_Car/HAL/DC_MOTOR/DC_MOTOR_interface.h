/*
 * DC_MOTOR_interface.h
 *
 * Created: 3/17/2024 8:59:45 AM
 *  Author: Go
 */ 


#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_

void MOTORS_Init();
void CAR_MoveForward ();
void CAR_MoveBackward ();
void CAR_Stop ();
void CAR_MoveForwardRight ();
void CAR_MoveForwardleft ();
void CAR_MoveBackwardRight ();
void CAR_MoveBackwardleft ();
void CAR_SendDutyCycleAndStart(u8 speed);





#endif /* DC_MOTOR_INTERFACE_H_ */