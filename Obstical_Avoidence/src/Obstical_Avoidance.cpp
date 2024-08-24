/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   4/30/2024  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   Obstical_Avoidacne.cpp

Purp: Use the motor and the ultrasonic sensor functions to follow 
      a wall and avoid obsticals.

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <Arduino.h>
#include "motor.h"
#include "ultrasonic.h"

void setup() {
  //Setup 
  setupServoTimer();
  setupUltraTimer();
  initMotorDriver();

}

void loop() {
  moveServoLeft();
  //go forward about a foot following wall on left
  startMotorHalfSpeed();
  delay(250);
  stopMotors();
  delay(10);

  //check distance form wall on left
  moveServoLeft();
  double wallDistance = getDistance();
  if (wallDistance > 15){
    nudgeLeft();
    delay(50);
    startMotorHalfSpeed();
    delay(100);
    stopMotors();
    delay(10);
    wallDistance = getDistance();

  }else if (wallDistance < 10){
    nudgeRight();
    delay(50);
    startMotorHalfSpeed();
    delay(150);
    stopMotors();
    delay(10);
    wallDistance = getDistance();
  }

  //check distance ahead
  moveServoMiddle();
  double forwardDistance = getDistance();
  if(forwardDistance < 14){
    //stopMotors();
    delay(10);
    //Obstical ahead
    //Pivot Right
    turnRight();
    delay(100);

    //Go forward (Long)
    startMotorHalfSpeed();
    delay(400);
    stopMotors();
    delay(10);

    //pivot Left
    turnLeft();
    delay(10);

    //Go forward (short)
    startMotorHalfSpeed();
    delay(600);
    stopMotors();
    delay(50);

    //pivot Left
    turnLeft();
    delay(50);

    //Go forward (Long)
    startMotorHalfSpeed();
    delay(300);
    stopMotors();
    delay(10);

    //Pivot Left
    nudgeRight();
    delay(50);

    turnRight();
    turnRight();
  }
    

}   
