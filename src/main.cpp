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
#include "SimpleTimer.h"

// Set the button and the pin numbers for your microcontroller
#define CLK 	D7		// Switch is connected between D7 and Ground
#define DAT 	D6		// Switch is connected between D6 and Ground
#define BUTTON	D5		// Switch is connected between D5 and Ground

// Create 3 MultiTapButton objects with active LOW pins, 
MultiTapButton C(CLK,LOW,2),D(DAT,LOW,5), button(BUTTON,LOW);
SimpleTimer timer1;
int counter=0;

void setup() {
	pinMode(CLK, 	INPUT_PULLUP);	// Set the switched pins as an input with pullup
	pinMode(DAT, 	INPUT_PULLUP);
	pinMode(BUTTON, INPUT_PULLUP);
	 pinMode(D4, OUTPUT);
	Serial.begin(74880);			// Start the Serial output
	Serial.println("Ready");
	digitalWrite(D4, HIGH);	// OFF
}
unsigned long lastProcessedTime = 0;
const unsigned long processInterval = 500;  // Minimum interval between normal events in ms
const unsigned long fastEventThreshold = 50;  // Time threshold for fast event detection (ms)
bool newDirection = false; // Default direction is false (counterclockwise)

void loop() {
    // Check if there is a change in encoder state (either down or up event)
    if (C.downEvent() || C.upEvent()) {

        unsigned long currentTime = millis(); // Current time for timing check

        // Check if the time since the last processed event is larger than the fast event threshold
        if (currentTime - lastProcessedTime > fastEventThreshold) {
            if (D.down() != C.down()) {
                newDirection = true;  // Clockwise
                counter++;  // Increase counter by 1 for clockwise movement
            } else {
                newDirection = false; // Counterclockwise
                counter--;  // Decrease counter by 1 for counterclockwise movement
            }
					Serial.printf("Counter is %3d direction %d\n", counter, newDirection);
        }

        // Update last processed time
        lastProcessedTime = currentTime;

        // Toggle LED for feedback (optional)
        digitalWrite(D4, !digitalRead(D4));

    }
}
