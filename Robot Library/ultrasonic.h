/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   3/24/2024  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   ultrasonic.cpp

Purp: Create funtions that utilize the ultrasonic senor and servo 
         on a robot

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include <Arduino.h>

/**
 * Inilises LEDS on board
*/
void initLEDS();

/**
 * Sets the Servo PWM using timer 2
*/
void setupServoTimer();

/**
 * Sets the Ultrasonic sensor timer using timer 1
*/
void setupUltraTimer();

void moveServoLeft();

void moveServoMiddle();

void moveServoRight();

/**
 * Returns the Distance using the ultrasonic sensor
*/
double getDistance();

#endif