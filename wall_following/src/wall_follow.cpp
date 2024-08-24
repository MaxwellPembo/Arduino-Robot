/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   3/28/2024  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   wall_follow.cpp

Purp: Use Motor and ultrasonic sensor to follow and stay 
    within 1 foot of a wall

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <Arduino.h>
#include "ultrasonic.h"
#include "motor.h"


#define GREENLED PIN3 //port B pin 3 DIGITAL 11

void setup() {
  Serial.begin(9600);
  initMotorDriver();
  setupServoTimer();
  setupUltraTimer();
  PINB |= (1 << GREENLED);
  PORTB &= ~(1 << GREENLED); //clear output 

  //moveServoRight();
  moveServoLeft();

}

void loop() {
  double ditstance = getDistance();


  /**
   * For when wall is on the Right side 
   * WORKS 90%
  */

  // if(ditstance > 7){
  //   PORTB |= (1 << GREENLED);
  //   Serial.println("MOVING RIGHT");
  //   stopMotors();
  //   nudgeRight(); 
  //   nudgeRight();
  //   startMotorHalfSpeed();
  //   delay(30);
  //   nudgeLeft();
  //   nudgeLeft();
  //   delay(30);
  //   PORTB &= ~(1 << GREENLED); //clear output 
  // }else if(ditstance < 5){
  //   PORTB |= (1 << GREENLED);
  //   Serial.println("MOVING Left");
  //   stopMotors();
  //   nudgeLeft();
  //   nudgeLeft();
  //   startMotorHalfSpeed();
  //   delay(55);
  //   nudgeRight();
  //   //nudgeLeft();
  //   delay(10);
  //   PORTB &= ~(1 << GREENLED); //clear output 
  // }



  /**
   * For when wall is on the LEFT side 
   * WORKS 90%
  */

  int leftTurn = 0;
  if((ditstance > 8) && (leftTurn <= 2)){
    PORTB |= (1 << GREENLED);
    Serial.println("MOVING LEFT");
    stopMotors();
    nudgeLeft(); 
    nudgeLeft();
    startMotorHalfSpeed();
    delay(20);//30
    nudgeRight();
    //nudgeRight(); //
    delay(10);
    PORTB &= ~(1 << GREENLED); //clear output 
    leftTurn ++;
  
  }
  else if(ditstance < 6){
    PORTB |= (1 << GREENLED);
    Serial.println("MOVING RIGHT");
    stopMotors();
    nudgeRight();
    nudgeRight();
    //nudgeRight();
    startMotorHalfSpeed();
    delay(55);//55
    nudgeLeft();
    //nudgeLeft();
    delay(30);
    PORTB &= ~(1 << GREENLED); //clear output 
    leftTurn = 0;
  }else{
    delay(5);
  }


   startMotorHalfSpeed();
   Serial.println(ditstance);


}

