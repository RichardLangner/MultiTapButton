/*By Richard Langner, Sheffield, UK, 20 November 2021.

Example code for the 'MultiTapButton' class.

Connect a button between D2 (GPIO4) and ground (0v).
When you tap or long press the button, watch the onboard LED 
(D4 on Wemos D1 mini), and watch messages sent to the serial port.

All the functions of MultiTapButton are demonstated here, but you 
can just pick the functions you want to use in your own code.

	*	Tapping the button toggles the LED on/off.

	*	Auto-repeat can be enabled by 5 quick taps.

	*	Holding the button down for more than 1sec auto-repeats 
		(if enabled) and makes the LED toggle on/off every 250ms.

	*	After 6secs the auto-repeat is disabled, but can be
		re-enabled by 5 quick taps.

This demo code doesn't have a real-world application - play with it 
to get familiar with the parts you find most useful.
See the ReadMe.md file to see all that MultiTapButton can do.
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

	// Exactly 5 quick taps enable auto-repeat.
	if(x==5){
		Serial.printf("You tapped EXACTLY 5 times!\n");
		button1.autoRepeatEnabled(true);
	}

	// If button pressed for more than 6 seconds, disable auto-repeat
	if(button1.downMillis() > 6000ul){
		button1.autoRepeatEnabled(false);
		Serial.printf("Button down for %10lu milliseconds\n",button1.downMillis());
	}
}

