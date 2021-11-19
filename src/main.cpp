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
		Serial.printf("EVENT: Button down\n");
		}

	// Button just released.
	if(button1.upEvent()){
		Serial.printf("EVENT: Button up\n");
		}

	// Occurs *every* time button is tapped.
	if(button1.tapped()){					
		Serial.printf("Tapped, toggle the LED\n");
		digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
		}

  	int x = button1.tapCount();
	// Your multi-tap code here.
  	if(x>0){								
		  Serial.printf("Tapped %d times\n",x);
		  }

	// To detect if exactly 5 quick taps.
	if(x==5){
		Serial.printf("You tapped EXACTLY 5 times!\n");
		button1.autoRepeat(true);
	}

	// If button pressed for more than 6 seconds, disable auto-repeat
	if(button1.downMillis() > 6000ul){
		button1.autoRepeat(false);
		Serial.printf("Button down for %10lu milliseconds\n",button1.downMillis());
	}
}

