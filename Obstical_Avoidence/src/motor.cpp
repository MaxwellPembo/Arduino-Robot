/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   3/24/2024  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   motor.cpp

Purp: Create funtions that drive the DC motors on a robot

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#include <avr/io.h>
#include <Arduino.h>
#include "motor.h"


void initMotorDriver(){
  Serial.begin(9600);
  Serial.println("Starting Motor Driver Setup");
  Serial.println("Starting Timer 0 PWM");

  //Set the PWM pins as output
  DDRD |= (1 << LEFT_ENABLE); //digital pin 5
  DDRD |= (1 << RIGHT_ENABLE); //digital pin 6

  //set the driving pins as output (This is only the right inputs)
  DDRB |= (1 << RIGHT_IN1); //digital pin 12
  DDRB |= (1 << RIGHT_IN2); //digital pin 13

  //setup timer
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0B1) | (1 << COM0A1); // fast PWM mode (Non-Inverting)
  TCCR0B = (1 << CS02);  //256 CLK DIV

  Serial.println("Timer 0 PWM Setup Finished");
  Serial.println("Motor Driver Setup Finished");
}

void stopMotors(){
  PORTB &= ~(1 << RIGHT_IN1);
  PORTB &= ~(1 << RIGHT_IN2);
  PORTD &= ~(1 << LEFT_IN1);
  PORTD &= ~(1 << LEFT_IN2);
}

void rightTireForward(){
  PORTB |= (1 << RIGHT_IN2);
  PORTB &= ~(1 << RIGHT_IN1);
}

void rightTireBackward(){
  PORTB |= (1 << RIGHT_IN1);
  PORTB &= ~(1 << RIGHT_IN2);
}

void leftTireForward(){
  PORTD |= (1 << LEFT_IN2);
  PORTD &= ~(1 << LEFT_IN1);
}

void leftTireBackward(){
  PORTD |= (1 << LEFT_IN1);
  PORTD &= ~(1 << LEFT_IN2);
}

void startMotorFullSpeed(){
  OCR0A = 120; //drives left
  OCR0B = 120; // drives right

  rightTireForward();
  leftTireForward();
}

void startMotorHalfSpeed(){
  OCR0A = 80; //60
  OCR0B = 80; //60

  rightTireForward();
  leftTireForward();
}

void startMotorHalfSpeedmain(){
  OCR0A = 70; //60
  OCR0B = 70; //60

  rightTireForward();
  leftTireForward();
}

void drivelefttire(){
    rightTireForward();
    leftTireForward();
    OCR0A = 40; //drives left
    OCR0B = 0; // drives right

}
void driveRighttire(){
    rightTireForward();
    leftTireForward();
    OCR0A = 0; //drives left
    OCR0B = 40; // drives right

}

void startMotorBackwards(){
  OCR0A = 120; //drives left
  OCR0B = 120; // drives right

  rightTireBackward();
  leftTireBackward();
}

void nudgeLeft(){
  OCR0A = 120;
  OCR0B = 120;

  rightTireForward();
  leftTireBackward();
  //delay(50); // 45 degrees
  delay(20);
  stopMotors();
}

void nudgeRight(){
  OCR0A = 120;
  OCR0B = 120;

  rightTireBackward();
  leftTireForward();
  //delay(50); // 45 degrees
  delay(20);
  stopMotors();
}

void turnRight(){
  OCR0A = 100;
  OCR0B = 100;

  rightTireBackward();
  leftTireForward();
  //delay(50); // 45 degrees
  delay(80);
  stopMotors();
}

void turnLeft(){
  OCR0A = 100;
  OCR0B = 100;

  rightTireForward();
  leftTireBackward();
  //delay(50); // 45 degrees
  delay(80);
  stopMotors();
}

void robotDance(){
  startMotorFullSpeed();
  delay(100);
  stopMotors();
  delay(200);
  startMotorBackwards();  
  delay(100);
  stopMotors();
  delay(200);
  nudgeLeft();
  delay(200);
  nudgeRight();
  delay(200);
  turnLeft();
  delay(200);
  turnRight();
  delay(200);
}
