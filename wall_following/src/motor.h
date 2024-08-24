/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   3/24/2024  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   motor.h

Purp: Create funtions that drive the DC motors on a robot

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#ifndef MOTOR.H
#define MOTOR.H
#include <avr/io.h>

#define LEFT_ENABLE PIN5 //digital pin 5 Port-D 5
#define RIGHT_ENABLE PIN6 //digital pin 6 Port-D 6

#define RIGHT_IN1 PIN4 //digital pin 12 Port-B 4
#define RIGHT_IN2 PIN5 //digital pin 13 Port-B 5
#define LEFT_IN1 PIN4 //digital pin 4 Port-D 4
#define LEFT_IN2 PIN7 //digital pin 7 Port-D 7



/**
 * Initalizes the timers and pww to drive the motors
 * on the robot.
*/
void initMotorDriver();

/**
 * Stops the Motors competly
*/
void stopMotors();

/**
 *Initalizes a PWM to set the Right tire to go forward
*/
void rightTireForward();

/**
 *Initalizes a PWM to set the Right tire to go backward
*/
void rightTireBackward();

/**
 *Initalizes a PWM to set the Left tire to go forward
*/
void leftTireForward();

/**
 *Initalizes a PWM to set the Left tire to go backward
*/
void leftTireBackward();

/**
 *Initalizes values to set the motor speed to full
*/
void startMotorFullSpeed();

/**
 *Initalizes values to set the motor speed to half
*/
void startMotorHalfSpeed();

/**
 *Initalizes values to set the motor speed to full
  and go backward
*/
void startMotorBackwards();

/**
 *Nudeges the robot left 45 degrees
*/
void nudgeLeft();

/**
 *Nudeges the robot right 45 degrees
*/
void nudgeRight();

/**
 *turns the robot right 90 degrees
*/
void turnRight();

/**
 *turns the robot left 90 degrees
*/
void turnLeft();

/**
 *Uses functions above to make the robot dance
*/
void robotDance();

void drivelefttire();

void driveRighttire();

#endif