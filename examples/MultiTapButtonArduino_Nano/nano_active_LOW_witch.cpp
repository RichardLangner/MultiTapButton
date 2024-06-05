/*By Richard Langner, Sheffield, UK, 5 June 2024.

Example code for the 'MultiTapButton' class to demonstrateExample code for the 'MultiTapButton' class to demonstrate
single tap, multi-tap, long press, press duration, auto-repeat.

*************************************************
*     GPIO pin numbers are for ARDUINO NANO     *
*     Change pins as required for your device   *
*************************************************

Connect a normally open button between a pin of your choice (e.g. D2) and GND.
   For a normally closed switch change
   MultiTapButton button1(BUTTON_1_PIN,HIGH);
   to
   MultiTapButton button1(BUTTON_1_PIN,LOW);

Results are sent to the serial port.

Pin numbers are for ARDUINO NANO:
*/

#include <Arduino.h>
#include "MultiTapButton.h"

// Set the button and the LED pin numbers for your microcontroller
#define BUTTON_1_PIN  2		// Button is connected between D2 and Ground
#define BUILTIN_LED 13		// Arduino Nano is pin 13

// Create a TapButton object with active LOW pin, 
MultiTapButton button1(BUTTON_1_PIN,LOW);

void setup() {
	pinMode(BUTTON_1_PIN, INPUT_PULLUP);	// Set the switched pin as an input with pullup
	pinMode(BUILTIN_LED, OUTPUT);			// Define LED pin
	digitalWrite(BUILTIN_LED, HIGH);		// Set LED to OFF
	Serial.begin(9600);						// Start the Serial output
}

void loop() {

	// Button just pressed down.
	if(button1.downEvent()){				
		Serial.println("EVENT: Button down");
		}

	// Button just released.
	if(button1.upEvent()){
		Serial.println("EVENT: Button up");
		}

	// Occurs *every* time button is tapped.
	if(button1.tapped()){					
		Serial.println("Tapped, toggle the LED");
		digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
		}

  	int x = button1.tapCount();
	// Your multi-tap code here.
  	if(x>0){								
		  Serial.print("Tapped ");
		  Serial.print(x);
		  Serial.println(" times");
		  }

	// Exactly 5 quick taps enable auto-repeat.
	if(x==5){
		Serial.println("You tapped EXACTLY 5 times and enabled autorepeat!");
		button1.autoRepeatEnabled(true);
	}

	// If button pressed for more than 6 seconds, disable auto-repeat
	// and show the seconds the button was held down.
	if(button1.downMillis() > 6000ul){
		button1.autoRepeatEnabled(false);
		if(button1.autoRepeatEnabled()){
			Serial.println("Auto-repeat is now disabled.");
		}
		Serial.print("Button has been pressed for ");
		Serial.print(button1.downMillis()/1000);
		Serial.println(" seconds.");
	}
}

