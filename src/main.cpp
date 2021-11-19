/*By Richard Langner, Sheffield, UK, 18 November 2021.

Example code for the 'MultiTapButton' class.

  Detects Single or Multiple taps
  Detects Short or Long presses
  Built-in debouncer removes switch noise
  Use almost any GPIO pin; no need for interrupts
  Works with active LOW or active HIGH switches
  Easy implementation of auto-repeat
  Each button has its own variable storage for cleaner code

See the ReadMe.md file to see what MultiTapButton can do.
*/

#include <Arduino.h>
#include "MultiTapButton.h"
#define BUTTON_1_PIN  D2	// Button between D2 (GPIO4) and Ground
#define BUILTIN_LED D4		// My Wemos D1 mini LED pin

// Create a TapButton object with active LOW pin, 
MultiTapButton button1(BUTTON_1_PIN,LOW);

void setup() {
	pinMode(BUTTON_1_PIN, INPUT_PULLUP);	// Set the switched pin as an input with pullup
	pinMode(BUILTIN_LED, OUTPUT);			// Define LED pin
	digitalWrite(BUILTIN_LED, HIGH);		// Set LED to OFF
	Serial.begin(74880);					// Select your baud rate or 
	// add monitor_speed = 74880 to the platformio.ini file.
}

void loop() {

	// Button just pressed down.
	if(button1.downEvent()){				
		Serial.printf("EVENT: Button down, toggle the LED\n");
		digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
		}

	// Button just released.
	if(button1.upEvent()){
		Serial.printf("EVENT: Button up\n");
		}

	// Occurs *every* time button is tapped.
	if(button1.tapped()){					
		Serial.printf("Tapped\n");}


  	int x = button1.tapCount();
	// Your multi-tap code here.
  	if(x>0){								
		  Serial.printf("Tapped %d times\n",x);
		  }

	// To detect if exactly 6 quick taps.
	if(x==6){
		Serial.printf("You tapped EXACTLY 6 times!\n");
	}

	// Auto-repeats if button pressed for more than 1.2 seconds
	if(button1.downMillis() > 1200ul){
		static unsigned long j;
		unsigned long i=(button1.downMillis() -1200ul) / 250;
		if(i==j){return;}	// Count same as last time, exit
		j=i;

		// Your auto-repeat code here
		digitalWrite(BUILTIN_LED, i%2);	// Toggle LED
		// Send number to serial
		Serial.printf("Toggles LED every 250ms %8d\n",i);
	}
}

