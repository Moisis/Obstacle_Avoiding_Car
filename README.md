Introduction:
The report presents an analysis of the Obstcale Avoidance program developed by Moisis George Mounir.The program 
implements various functions to control a SmartCar using a microcontroller(AVR) atmega32 .The Car is designed to move in 
different directions, avoid obstacles

-----------------------------------------------------------------------------------------------------------------------
Drivers:
- MCAL:  DIO, GI, TIMERS (Timer 0 , timer 1 , timer 2 ), 
- HAL:     Servo , ULTRASONIC , DC Motors  ,LCD 
- UTIL:       BIT_MATHS, STD_TYPES
-----------------------------------------------------------------------------------------------------------------------
Components:
- ATmega32 AMIT Kit
- 3x3.7v Batteries
- 4 DC-Motors
- 4 Wheels
- H-Bridge (L298N) 
- Servo Motor 
- Ultrasonic Sensor
- LCD
-----------------------------------------------------------------------------------------------------------------------

 This program implements functions to enable the SmartCar to avoid obstacles. It uses an ultrasonic sensor 
to detect the presence of obstacles. When an obstacle is detected, the SmartCar stops, reads distances from the left and right 
sides, and maneuvers to an empty road.

Note: 
The ultrasonic sensor works with ICU software Technique (ICU SW) using timer 2 to generate suitable pwm and External interuppt prepheral

-----------------------------------------------------------------------------------------------------------------------

Picture:


![WhatsApp Image 2024-03-21 at 3 02 24 PM](https://github.com/Moisis/Obstacle_Avoiding_Car/assets/19711568/795c6ecb-08ef-4a5e-b62c-827ecaf50c24)


-----------------------------------------------------------------------------------------------------------------------

Presentation link : 
https://prezi.com/view/bQjqHlqrArMc5hZ9qham/
