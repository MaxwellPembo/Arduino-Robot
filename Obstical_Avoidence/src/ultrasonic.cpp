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

#include <avr/io.h>
#include <Arduino.h>

//Definitons for the PWM pins
#define OCR2A_PWM PINB3
#define OCR2B_PWM PIND3
//Definitions for Port B & D registors 
#define PINB_Reg (*((volatile uint8_t *) 0x23)) 
#define DDRB_Reg (*((volatile uint8_t *) 0x24))
#define PORTB_Reg (*((volatile uint8_t *) 0x25))
#define PIND_Reg (*((volatile uint8_t *) 0x29))
#define DDRD_Reg (*((volatile uint8_t *) 0x2a)) 
#define PORTD_Reg (*((volatile uint8_t *) 0x2b)) 
//Definitions for LED assignments: 
#define BOARD_LED 5 //pin 13 is PortB bit 5
#define RED_LED 5 //pin 5 is PortD bit 5
#define GREEN_LED 6 //pin 6 is PortD bit 6 
#define BLUE_LED 7 //pin 7 is PortD bit 6
// Definitions for ultrasonic Sensor
#define USS_Trigg 1 //pin 9 is PortB bit 1
#define USS_Echo 0 //pin 8 (ICP) is Port B bit 0

void initLEDS(){
  Serial.println("Initalising LEDs");
  
  DDRB_Reg |= (1 << RED_LED);
  DDRB_Reg |= (1 << GREEN_LED);
  DDRB_Reg |= (1 << BLUE_LED);

  PORTD_Reg &= ~(1 << RED_LED); //clear output
  PORTD_Reg &= ~(1 << GREEN_LED); //clear output
  PORTD_Reg &= ~(1 << BLUE_LED); //clear output

  for(int i=0; i<5; i++){
    PORTD_Reg |= (1 << RED_LED); //set output
    PORTD_Reg |= (1 << GREEN_LED); //set output
    PORTD_Reg |= (1 << BLUE_LED); //set output
    delay(300);
    PORTD_Reg &= ~(1 << RED_LED); //clear output
    PORTD_Reg &= ~(1 << GREEN_LED); //clear output
    PORTD_Reg &= ~(1 << BLUE_LED); //clear output
    delay(300);
  }
  Serial.println("Finished Initalising LEDs");
}


void setupServoTimer(){
  Serial.println("Servo Setup starting");

  DDRD |= (1 << OCR2B_PWM);
  DDRB |= (1 << OCR2B_PWM);
  TCCR2A = 0b10100011; //compare match mode, clear on Bottom, Phase Correct mode PWM
  TCCR2B = 0b00000111;  //1024 Clk devider
  OCR2A = 200; 

  Serial.println("Servo setup Finished");
}

void setupUltraTimer(){
  Serial.println("Ultrasonic sensor Setup starting");
  DDRB = (1 << USS_Trigg);// output
  DDRB &= ~(1 << USS_Echo);// input
  
  TCCR1A = 0; // Normal Mode timer
  TCCR1B = (1 << CS11) | (1 << CS10);//63
  TCCR1B &= ~(1 << ICES1); 
  TCCR1C = 0;
  TCNT1 = 0;
  Serial.println("Ultrasonic sensor Setup finished");
}

void moveServoLeft(){
  OCR2B = 39; // Moves servo Left
  delay(500);
}

void moveServoMiddle(){
  OCR2B = 23; // Moves servo middle
  delay(500);
}

void moveServoRight(){
  OCR2B = 8; // Moves servo Right
  delay(500);
}

/**
 * Returns the Distance using the ultrasonic sensor
*/
double getDistance(){
  double distance = 0;

  //Send 10 uS pulse through trigger
  PORTB_Reg |= (1 << USS_Trigg); //set output
  delayMicroseconds(10);
  PORTB_Reg &= ~(1 << USS_Trigg); //clear output


  // wait for Echo to go High
  while(!(PINB & (1 << USS_Echo))){
  }

  // clear ICR1
  TCNT1 = 0;
  ICR1 = 0;
  delay(60);
  int ICR1_Value = ICR1; // Time Echo is High

  distance = ((double)ICR1_Value * 4) / 148; //Distance in Inches
    
  return distance;
}