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