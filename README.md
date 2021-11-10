# MultiTapButton : A class for buttons and switches.

Key features (read the __MultiTapButton.h__ file for more information)
<strong>
<ul>
  <li>Detects Single or Multiple taps</li>
  <li>Detects Short or Long presses</li>
  <li>Built-in debounce</li>
  <li>Works on any GPIO pin</li>
  <li>Does not use interrupts</li>
  <li>Works on active LOW or active HIGH switches</li>
  <li>Non-blocking code, so will not slow your program</li>
  <li>Free variable storage, making cleaner code</li>
  <li>Simple to use.</li>  
</ul> 
</strong>

## DEFINING A BUTTON
If you have a button (e.g. an active LOW switch) which pulls GPIO2 LOW when pressed, and you want to declare it as <strong>'button1'</strong> you can use <br>
`MultiTapButton button1(2,LOW);`

## CHECKING IF BUTTON WAS TAPPED
To check if the button was tapped, use <br>`if(button1.tapped()){...}`<br><br>
For multiple taps, you can find the number of taps with <br>`int x = button1.tapCount();`

## CHECKING IF THE BUTTON IS DOWN
To check if a button is currently down use `if(button1.down()){...}`

## CHECKING IF BUTTON CHANGED STATE
When a button is pressed or released it generates an event. These events only happen once per transition.<br>
To check if a button just went 'down' (switch closed) use <br>`if(button1.downEvent()){...}`<br>
To check if a button just went 'up' (switch opened) use <br>`if(button1.upEvent()){...}`

## CHECKING BUTTON PRESS DURATION
To check how long the button has been down, use <br>`unsigned long x = button1.downMillis();`

## STORAGE FOR YOUR PRIVATE VARIABLES
 For ease of coding I have provided each button with a set of general purpose variables that you can use for any purpose you like. You can use the <strong>integers</strong> as counters, <strong>booleans</strong> for toggling things on/off, and <strong>unsigned</strong>
 longs for large numbers such as milliseconds<br>
 These bonus variables can be addressed
  using the following code (assuming the switch is named 'button1')<br>
	`button1.userIntA`<br>
	`button1.userIntB`<br>
	`button1.userBoolA`<br>
	`button1.userBoolB`<br>
  `button1.userULongA`<br>
  `button1.userULongB`.

  ## CUSTOMISING YOUR BUTTONS
  All timing parameters are available to the user. You can set the debounce period, the milliseconds after which a tap becomes a press, and the maximum gap between multiple taps (the inter-tap gap, after which it decides taps have ceased and it will return the number of taps).
 Here is an example of setting all the available custom values when creating a button.<br><br>
 To create a button to be active HIGH pin on GPIO2, debounced for 20ms, have a tap maximum time of 400ms and inter-tap gap of no more than 200ms.<br>
 `MultiTapButton button1(2, HIGH, 20, 400, 200);`

  ## EXAMPLE CODE
  The example code demonstrates some of the events that MultiTapButton uses. Ensure you check the button regularly in your code as the timing accuracy depends on refreshing the button's state. Best practice is to have a fast non-blocking loop and check the button in the loop() code.
