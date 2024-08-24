/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   3/24/2024  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   robotDance.cpp

Purp: Use funtions that drive the DC motors on a robot and make the robot
      Dance.

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#include <Arduino.h>
#include "motor.h"



void setup() {
  initMotorDriver();
}

void loop() {
  robotDance();
  delay(500);
  
}

