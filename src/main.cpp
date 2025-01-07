/*By Richard Langner, Sheffield, UK, 6 Jan 2025

Example code using the 'MultiTapButton' class
*************************************************
*     ROTARY ENCODER without interrupts         *
*     GPIO pin numbers are for Wemos D1 mini    *
*     Change pins as required for your device   *
*************************************************

Captures clicks and direction of a rotary encoder
All pins have pull-ups enabled in software
Pins CLK=D7  DAT=D6  BUTTON=D5
Results are sent to the serial port.
*/

#include <Arduino.h>
#include "MultiTapButton.h"

// Set the button and the pin numbers for your microcontroller
#define CLK 	D7		// Switch is connected between D7 and Ground
#define DAT 	D6		// Switch is connected between D6 and Ground
#define BUTTON	D6		// Switch is connected between D5 and Ground

// Create 3 MultiTapButton objects with active LOW pins, 
MultiTapButton clk(CLK,LOW),dat(DAT,LOW), button(BUTTON,LOW);

void setup() {
	pinMode(CLK, 	INPUT_PULLUP);	// Set the switched pins as an input with pullup
	pinMode(DAT, 	INPUT_PULLUP);
	pinMode(BUTTON, INPUT_PULLUP);
	Serial.begin(74880);			// Start the Serial output
}

void loop() {

	// Check if just changed.
	if(clk.downEvent() or clk.upEvent()){	
		if(dat.down()){
		Serial.println("EVENT: right");
		}
		else{
			Serial.println("EVENT: left");
		}
	}
}

