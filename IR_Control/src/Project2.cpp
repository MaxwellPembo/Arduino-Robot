/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   24 Mar 19  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   project2.iso
HW/Lab: Lab 5/Project 2, Decoding an IR Packet

Purp: Uses counters and interrupts to decode an IR packet for a 
    remote. 

Doc:  <list the names of the people who you helped>
    <list the names of the people who assisted you>

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <avr/io.h>
#include <Arduino.h>
#include "ir_decoder.h"
#include "motor.h"

#define SAMPLE_SIZE       34
#define   BIT0            0x00000001
volatile uint32_t irPacket;
volatile uint8_t  newIrPacket = FALSE;
volatile uint16_t packetData[34];
volatile uint8_t  packetIndex = 0;
volatile int speed = 1;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting up...");
  IR_Decoder_Setup();
  initMotorDriver();
  sei(); /* Enable Global Interrupts*/
}

/*
 * main loop
 */
void loop() {

  /* Check if new IR packet has arrived bad way */ 
//  if (packetIndex > 33) {
//    packetIndex = 0;
//  } // end if new IR packet arrived
  /* Check if new IR packet has arrived better way */ 
  if (newIrPacket == TRUE){
	  //code to convert packetData[] counts to 32 bit irpacket
	  Serial.println(irPacket, HEX);
    newIrPacket = FALSE;
    irPacket =0;
  } //end if newIrPacket
  
  /* Do something with new IR packet */ 
  if (irPacket == Up_Button || irPacket == Elegoo_Up_Button){    
    if(speed == 1){
      Serial.println("Up_Button: fast" );
      forward_move_fast();
    }else if(speed == 2){
      Serial.println("Up_Button: medium");
      forward_move_medium();
    }else{
      Serial.println("Up_Button: slow");
      forward_move_slow();
    }
    //Serial.println("Up_Button");
    irPacket = 0;     // Clear irPacket
  } else if (irPacket == Elegoo_Down_Button){
    backward_move();
    Serial.println("Down_Button");
    irPacket = 0;
  }else if (irPacket == Elegoo_Left_Button){
    turnLeft();
    Serial.println("Left_Button");
    irPacket = 0;
  }else if (irPacket == Elegoo_Right_Button){
    turnRight();
    Serial.println("Right_Button");
    irPacket = 0;
  }else if (irPacket == Elegoo_1){
    Serial.println("Low_Speed_Button");
    speed = 3;
    irPacket = 0;
  }else if (irPacket == Elegoo_2){
    Serial.println("Medum_Speed_Button");
    speed = 2; 
    irPacket = 0;
  }else if (irPacket == Elegoo_3){
    Serial.println("Fast_Speed_Button");
    speed = 1;
    irPacket = 0;
  }







}// end loop

// -----------------------------------------------------------------------
// Since the IR decoder is connected to INT0, we want an interrupt
// to occur every time that the pin changes - this will occur on
// a positive edge and a negative edge.
//
// Negative Edge:
// The negative edge is associated with end of the logic 1 half-bit and
// the start of the logic 0 half of the bit.  The timer contains the
// duration of the logic 1 pulse, so we'll pull that out, process it
// and store the bit in the global irPacket variable. Going forward there
// is really nothing interesting that happens in this period, because all
// the logic 0 half-bits have the same period.  So we will turn off
// the timer interrupts and wait for the next (positive) edge on INT0
//
// Positive Edge:
// The positive edge is associated with the end of the logic 0 half-bit
// and the start of the logic 1 half-bit.  There is nothing to do in
// terms of the logic 0 half bit because it does not encode any useful
// information.  On the other hand, we are going into the logic 1 half bit
// and the portion which determines the bit value, the start of the
// packet, or if the timer rolls over, the end of the ir packet.
// Since the duration of this half-bit determines the outcome
// we will turn on the timer and its associated interrupt.
// -----------------------------------------------------------------------

ISR(INT0_vect){

  uint8_t   pin;
  uint16_t  pulseDuration;      // The timer is 16-bits

  if (IR_DECODER_PIN)   pin=1;  else pin=0;
  switch (pin) {          // read the current pin level
    case 0:           // !!!!!!!!!NEGATIVE EDGE!!!!!!!!!!
      pulseDuration = TCNT1;    //**Note** Timer Count register is 16-bits

           
      if(pulseDuration > minLogic0Pulse && pulseDuration < maxLogic0Pulse){
        irPacket = irPacket << 1;
        //Serial.println(irPacket, BIN);
      }
      else if (pulseDuration > minLogic1Pulse && pulseDuration < maxLogic1Pulse){
        irPacket = irPacket << 1;
        irPacket |= (1 << 0);
        //Serial.println(irPacket, BIN);
      }


      packetData[packetIndex++] = pulseDuration;
      //Serial.println(pulseDuration, HEX);
			TIMSK1 &= ~(1 << OCIE1A);					//Disable interrupt on match with OCR1A
      LOW_2_HIGH;               // Set up pin INT0 on positive edge
      break;

    case 1:             // !!!!!!!!POSITIVE EDGE!!!!!!!!!!!
      TCNT1 = 0x0000;           // time measurements are based at time 
			TIFR1 |= (1 << OCF1A);		// Clear Timer/Counter1, Output Compare A Match Flag by writing 1 
			TIMSK1 |= (1 << OCIE1A);	// Enable interrupt on match with OCR1A
      HIGH_2_LOW;               // Set up pin INT0 on falling edge
      
      break;

    
  } // end switch


} // end pinChange ISR

// -----------------------------------------------------------------------
//            0 half-bit  1 half-bit    TIMER 1 COUNTS    TIMER 1 COUNTS
//  Logic 0   xxx
//  Logic 1
//  Start
//  End
//
// -----------------------------------------------------------------------
/**
 * This function is called whenever the timer 1 output compare match OCR1A
 * is generated.
 **/
ISR(TIMER1_COMPA_vect){
  TIMSK1 &= ~(1 << OCIE1A); // Disable interrupt on match with OCR1A
  packetIndex = 0; //clear packet index
  newIrPacket = TRUE;
  
}