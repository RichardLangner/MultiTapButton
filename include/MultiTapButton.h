/*
MultiTapButton Class v0.2 updated 25 May 2024.
Written by Richard Langner, Sheffield Hackspace, UK.
 
At its simplest, MultiTapButton debounces a physical button.
MultiTapButton does not use interrupts so it can be used on
just about any GPIO pin of your microprocessor board, and will
not upset interrupt timing in ESP8266 boards.

And there's plenty more functionality you can use.
 
Use a MultiTapButton to detect:
	SHORT PRESSES (TAPS)
	- if you tapped the button			if(button1.tapped()){...}
	- the number of taps				int x = button1.tapCount();
	EVENTS
	- if a button just went 'down'			if(button1.downEvent()){...}
	- if a button just went 'up'			if(button1.upEvent()){...}
	LONGER PRESSES
	- duration of press so far			unsigned long x = button1.downMillis();
	- if a button down				if(button1.down()){...}
	
Example code is provided in 'MultiTapButton' sketch.

-------------- USAGE --------------
SIMPLE: If you have 'button1' which pulls GPIO2 LOW when pressed -
	MultiTapButton button1(2,LOW);

NOISY ENVIRONMENTS: As above, but increase the debounce time to 20ms -
	MultiTapButton button1(2, LOW, 20)

ADVANCED: Button has active HIGH pin GPIO2 debounced for 20ms -
with tap maximum of 400ms and inter-tap gap of 200ms.
	MultiTapButton button1(2, HIGH, 20, 400, 200);

-------------- DEFAULTS --------------
Debounce time 10ms.
Maximum tap period 500ms, after which it's a long press.
Maximum gap between taps for multi-tap 250ms.

-------------- REQUIREMENTS --------------
Accuracy depends on how often you call any of the button's functions, so ensure
you have a fast non-blocking loop(); and check buttons regularly.

-------------- EXTRAS --------------
 For ease of coding, you can use each button's inbuilt general purpose user variables.
 E.G.use integers as counters, and booleans for toggling things on/off, unsigned
 longs for large numbers such as millis();
	button1.userIntA				Spare Integer, free for you to use.
	button1.userIntB				Spare Integer, free for you to use.
	button1.userBoolA				Spare Boolean, free for you to use.
	button1.userBoolB				Spare Boolean, free for you to use.
	button1.userULongA;				Spare Unsigned Long,free for you to use.
	button1.userULongB;				Spare Unsigned Long,free for you to use. 
*/

#include <Arduino.h>
#ifndef  MULTI_TAP_BUTTON_CLASS
#define  MULTI_TAP_BUTTON_CLASS

class MultiTapButton
{
private:
	unsigned long	_lastTimeDown		= millis();
	unsigned long	_lastTimeUp		= millis();
	unsigned long	_lastTimeTapped		= millis();
	unsigned long	_down_ms;
	unsigned long	_up_ms;

	unsigned long	_AR_dwell_ms	= 1000;		// Auto-repeat
	unsigned long	_AR_last_ms	= millis();	// Auto-repeat
	unsigned long	_AR_every_ms	= 250;		// Auto-repeat
	bool		_AR_enabled	= false;	// Auto-repeat

	bool			_longTapEnded = false;
	bool			_shortTapEnded = false;
	bool			_down = false;	
	bool			_downEvent=false;
	bool			_upEvent=false;
	bool			_tapped;
	int			_tapCounter;
	int			_tapCounter2;
	uint8_t			_buttonPin;		// Switch pin
	bool			_activeLevel = LOW;	// Pin goes low when pressed
	unsigned long		_debounce;		// Min tap duration ms(debounce)
	unsigned long		_tap_ms;		// Max tap duration ms, then longtap
	unsigned long		_tapGap_ms;		// Inter-tap gap, for multi-tap sensing

public:
	int			userIntA;		// Free to use
	int			userIntB;		// Free to use
	bool			userBoolA;		// Free to use
	bool			userBoolB;		// Free to use
    unsigned long   		userULongA;		// free to use
    unsigned long  		userULongB;		// free to use


// Create a TapButton object
MultiTapButton(int Button_Pin, bool ActiveLevel, unsigned long Debounce = 10, unsigned long Tap_msec = 500, unsigned long TapGap_ms =250){
	_buttonPin = Button_Pin;
	_activeLevel = ActiveLevel;
	_debounce = Debounce;
	_tap_ms = Tap_msec;
	_tapGap_ms = TapGap_ms;
	pinMode(Button_Pin,INPUT);
	}

unsigned long update() {
	// Reads the switch pin and saves the results
	if(digitalRead(_buttonPin) == _activeLevel) {		// Read the button level, invert if active HIGH
														// Button is down
		if((millis() - _lastTimeDown) > _debounce){		// Debounce the button
			_lastTimeUp = millis();						// Reset the UP timer
			if(!_down){									// Event - only just pressed
				_down = true;							// Remember the button is down
				_downEvent=true;						// Down event happened
				_down_ms = millis();					// Store the time it went down
				_longTapEnded = false;					// Reset the UP flag
				_shortTapEnded = false;					// Button is down
				return 1;								// Button DOWN event =1
			}
			// Auto-repeat code for Richard
			if(!_AR_enabled){return 0;};				// Auto-repeat enabled?
			if((millis() - _down_ms) < _AR_dwell_ms){	// Dwell time exceeded?
				return 0;};
			if((millis()-_AR_last_ms)>(_AR_every_ms)){	// Time for next auto-repeat?
				_AR_last_ms = millis();					// Update for last tap time
				_tapped=true;							// Update 'tapped' flag
			}
		}
		return 0;										// Nothing to report =0
	}	
	else
	{	// Button is up
	if((millis() - _lastTimeUp) > _debounce){		    // Debounce the button
		_lastTimeDown = millis();						// Reset the DOWN timer
		if(_down){										// Event - only just released
			_down = false;								// Remember the button is up
			_upEvent=true;								// Up event happened
			_up_ms = millis();							// Store the time it went up
			
			_longTapEnded = ((_up_ms - _down_ms) > _tap_ms);	// Long tap
			if(_longTapEnded){return (_up_ms - _down_ms);}
			
			_shortTapEnded = ((_up_ms - _down_ms) <= _tap_ms);	// Short tap
			if(_shortTapEnded){++_tapCounter;}			// Increment tap counter
			_lastTimeTapped = millis();					// Remember tap time
			_tapped=true;								// Set flag
			return 0;
			}				
		}
	}
	return 0;											// Nothing to report =0
}

// Returns TRUE if the button has just gone down
bool	downEvent(){update();
		if(_downEvent){_downEvent=false; return true;}
		return false;
		}
// Returns TRUE if the button has just been released
bool	upEvent(){update();
		if(_upEvent){_upEvent=false; return true;}
		return false;
		}
// Retruns TRUE if the button was tapped once
bool	tapped(){update();
		if(_tapped){_tapped=false; return true;}
		return false;
		}

// Returns the number of consecutive taps
int		tapCount(){update();
		if((millis() - _lastTimeTapped) > _tapGap_ms){	// If multiple taps ended
			int i = _tapCounter;						// Save tap counter value
			_tapCounter=0;								// Reset tap counter
			return i;									// Return tap couter
		} else {return 0;}								// Else still tapping
		}		

// Returns time in milliseconds that the button has been held down		
unsigned long downMillis(){update();
		return _down ? (millis() - _down_ms) : 0;
		}

bool	down(){ update();
			return _down;
		}

void	autoRepeatEnabled(bool b){
		_AR_enabled = b;		
		}

bool	autoRepeatEnabled(){
		return _AR_enabled;
		}

void	autoRepeatConfig(unsigned long dwell_ms, unsigned long every_ms){
		_AR_dwell_ms = dwell_ms;	// Delay before auto-repeat starts
		_AR_every_ms = every_ms;	// Auto-repeats a tap every ms
		}
};

#endif	// MULTI_TAP_BUTTON_CLASS
