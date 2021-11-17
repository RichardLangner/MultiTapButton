 /*By Richard Langner, Sheffield, UK, 17 November 2021.

Example code for the 'MultiTapButton' class.
See the ReadMe.md file to see what MultiTapButton can do.

I have used pins for Wemos D1 mini.

USAGE OF THIS EXAMPLE CODE (watch the output on the Serial port)
Try quickly tapping the button one or more times, or holding
it down for a few seconds to see the auto-repeat. 

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

	// Your multi-tap code here.
  	int x = button1.tapCount();
  	if(x>0){								
		  Serial.printf("Tapped %d times\n",x);
		  }

	// To detect if exactly 6 quick taps.
	if(x==6){
		Serial.printf("You tapped EXACTLY 6 times!\n");
	}

	// Auto-repeats if button pressed for more than 1.5 seconds
	if(button1.downMillis() > 1500){
		static int j;
		int i=(button1.downMillis()-1500) / 250;
		if(i==j){return;}	// Count did not change
		j=i;

		// Your auto-repeat code here
		Serial.printf("Toggles LED every 250ms\n");		
		digitalWrite(BUILTIN_LED, i%2);
		// Write an increasing auto-repeat number to serial
		Serial.printf("Auto repeat value = %4d\n",i);
	}
}

