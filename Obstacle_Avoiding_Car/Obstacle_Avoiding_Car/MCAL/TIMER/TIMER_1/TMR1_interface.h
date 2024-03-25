/*
 * TMR1_interface.h
 *
 * Created: 1/22/2024 9:48:55 PM
 *  Author: Kareem Hussein
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_


                       /*************** APIS PROTOTYPES ***************/ 
					   
void TMR1_init                  (void);
void TMR1_start                 (void);
void TMR1_stop                  (void);
void TMR1_setCallBackOVF        (void(*ptrToFun)(void));
void TMR1_setCallBackCTC        (void(*ptrToFun)(void));
void TMR1_setFastPWM_usingMode14(f32 dutyCycle, u16 frequency_hz);


#endif /* TMR1_INTERFACE_H_ */