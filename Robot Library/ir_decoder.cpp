/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   24 Mar 19  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   ir_decoder.cpp
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
#include "ir_decoder.h"




// -----------------------------------------------------------------------
// In order to decode IR packets, the Arduino needs to be configured to
// tell time and generate interrupts on positive going edges.  The
// edge sensitivity is used to detect the first incoming IR packet.
// The PinD2 (i.e. INT0) pin change ISR will then toggle the edge sensitivity of
// the interrupt in order to measure the times of the high and low
// pulses arriving from the IR decoder.
//
// Timer 1 must be enabled so that we can tell how long the pulses
// last.  In some degenerate cases, we will need to generate a interrupt
// when the timer rolls over.  This will indicate the end of a packet
// and will be used to alert main that we have a new packet.
// -----------------------------------------------------------------------
void IR_Decoder_Setup() {

  TCCR1A = 0;
  TCCR1B = 0;     /* Reset TCCR1A & TCCR1B to defaults */  
  TCCR1B |= (1 << WGM12);	   	/* Set Timer 1 to CTC with OCR1A as top */
  TCCR1B |= (1 << CS10) | (1 << CS11); 	    /* Set clock prescaler to clk/64 */
  /* Configure OCR1A (the counter top) to generate an interrupt every 65ms. */
  OCR1A = 16250;
  TCNT1H = 0;    	/* Clear timer 1 counter register high byte first*/
  TCNT1L = 0;

  /* Configure IR input on Port D, Pin 2 using registers and (1 << IR_PIN) value */
  DDRD &= ~(1 << IR_PIN);		/* Input IR on Port D, Pin 2 */
  PORTD |=	(1 << IR_PIN); 	/* Enable Pullup on Port D, Pin 2 */


  HIGH_2_LOW;				  /* check the header out.  INT0 edge select has changed */
  EIMSK |= (1 << INT0);       /* Enable External Interrupt Mask 0*/

}