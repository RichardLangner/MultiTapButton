 /*
Example code for the 'MultiTapButton' class which debounces switch/button presses and taps.
It reports how many times you multi-tapped the button, and reports if the
button is held for more than 2 secs.
** Monitor the Serial port for messages of what it is doing **

All button timings are customisable - see 'MultiTapButton_01.h' for the extended
parameter list.

Written by Richard Langner, Sheffield, UK, 12 November 2021.

This example should work on Arduino-type boards/Sonoff/ESP8266 etc.
as it doesn't use special interrupts or timers.

USAGE OF THIS EXAMPLE CODE
Try quickly tapping the button one or more times, or holding
it down for a few seconds, and see the results in the Serial port window.
*/

#include <Arduino.h>
#include "MultiTapButton.h"
#define BUTTON_1_PIN  D2					// My Wemos D1 mini button
#define BUILTIN_LED D4						// My Wemos D1 mini LED pin

// Create a TapButton object with active LOW pin, 
MultiTapButton button1(BUTTON_1_PIN,LOW);

void setup() {
	pinMode(BUTTON_1_PIN, INPUT_PULLUP);	// Set the switched pin as an input with pullup
	pinMode(BUILTIN_LED, OUTPUT);			// Define LED pin
	digitalWrite(BUILTIN_LED, HIGH);		// Set LED to OFF
	Serial.begin(74880);					// ESP8266 native baud rate, please add
											// monitor_speed = 74880
											// to the platformio.ini file
}

void loop() {

	if(button1.downEvent()){				// Button just pressed down.
		Serial.printf("EVENT: Button down, toggle the LED\n");
		digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
		}
	
	if(button1.upEvent()){					// Button just released.
		Serial.printf("EVENT: Button up\n");
		}

	if(button1.tapped()){					// *Every* time button is tapped.
		Serial.printf("Tapped\n");}

  	int x = button1.tapCount();
  	if(x>0){								// Your multi-tap code here.
		  Serial.printf("Tapped %d times\n",x);
		  }

	if(x==6){								// Exactly 6 quick taps.
		Serial.printf("You tapped EXACTLY 6 times!\n");
	}
	
	if(button1.downMillis() > 2000){		// Pressed for more than 2 seconds
		static int j;
		int i=(button1.downMillis()-2000) / 250;
		if(i==j){return;}
		j=i;
		// Auto-repeat toggles LED
		digitalWrite(BUILTIN_LED, i%2);
		// Write an increasing number to serial
		Serial.printf("Auto repeat value =%d\n",i);
	}
}

