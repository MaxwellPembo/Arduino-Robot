/*--------------------------------------------------------------------
Name:   Maxwell J. Pembo
Date:   23 Mar 19  
Course: CSCE 336 Embedded Systems (Spring 2024) 
File:   ir_decoder.h
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
#ifndef IR_DECODER_H
#define IR_DECODER_H

#include <avr/io.h>

#define		TRUE				1
#define		FALSE				0

/*-----------------------------------------------------------------
	Function prototypes found in project2.cpp
-----------------------------------------------------------------*/
void  IR_Decoder_Setup();


//-----------------------------------------------------------------
// Each ISC0n bit selects the external interrupt 0 edge for the corresponding I/O pin.
// Reference page 89 of the datasheet
//	Bits = 10 : The INT0 flag is set with a high-to-low (falling edge) transition
//  Bits = 11 : The INT0 flag is set with a low-to-high (rising edge) transition
//-----------------------------------------------------------------

//#define		IR_PIN			(P2IN & BIT6)
#define 	IR_DECODER_PIN  (PIND & (1 << PIND2))
#define 	IR_PIN    		(PIND2)
#define		HIGH_2_LOW		(EICRA = (EICRA & ~(1 << ISC00)) | (1 << ISC01))
#define		LOW_2_HIGH		(EICRA |= (1 << ISC00) | (1 << ISC01))


#define		averageLogic0Pulse  0x85   //0x0492 
#define		averageLogic1Pulse	0x0195 //0x450  //0x0D70 
#define		averageStartPulse	0x2760 //0x234E 
#define		minLogic0Pulse		averageLogic0Pulse - 100
#define		maxLogic0Pulse		averageLogic0Pulse + 100
#define		minLogic1Pulse		averageLogic1Pulse - 100
#define		maxLogic1Pulse		averageLogic1Pulse + 100
#define		minStartPulse		averageStartPulse - 100
#define		maxStartPulse		averageStartPulse + 100

/* Elegoo Remote */
#define		Elegoo_Up_Button		0x00FF629D
#define		Elegoo_Down_Button		0xFFA827
#define		Elegoo_Left_Button		0xFF2227
#define		Elegoo_Right_Button		0xFFC227
#define		Elegoo_Select_Button    0xFF0227

#define		Elegoo_Up_Arrow     0x00FF906F
#define		Elegoo_Down_Arrow   0x00FFE01F
#define		Elegoo_Pause        0x00FF02FD
#define		Elegoo_EQ           0x00FF9867

#define		Elegoo_0    0x00FF6897
#define		Elegoo_1    0x00FF30CF
#define		Elegoo_2    0x00FF18E7
#define		Elegoo_3    0x00FF7A85
#define		Elegoo_4    0x00FF10EF
#define		Elegoo_5    0x00FF38C7



/* Other Remote */
#define		Up_Button		0xE0E006F9
#define		Down_Button		0xE0E08679
#define		Left_Button		0xE0E0A659
#define		Right_Button	0xE0E046B9
#define		Select_Button	0xE0E016E9


#endif