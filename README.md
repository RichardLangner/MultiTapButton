# MultiTapButton : Buttons and switches made easy.

<strong>
<ul>
  <li>Detects Single or Multiple taps</li>
  <li>Detects Short or Long presses</li>
  <li>Built-in debounce</li>
  <li>Works on any GPIO pin</li>
  <li>Does not use interrupts</li>
  <li>Works on active LOW or active HIGH switches</li>
  <li>Private variable storage, making cleaner code</li>
</ul> 
</strong>

## WHY DO I NEED IT?
At at absolute minimum, it saves you writing debounce code for each button.<br>
But it can do a lot more - it's ideal for any device using single taps or multi-taps, or even a 10 second press to reboot a device, or perhaps all of these things using one button.

## DEFINING A BUTTON
If you have a button which pulls GPIO2 LOW when pressed, and you want to define it as <strong>'button1'</strong> you can use <br>
`MultiTapButton button1(2,LOW);`

## CHECKING IF BUTTON WAS TAPPED
To check if the button was tapped, use <br>`if(button1.tapped()){...}`<br>
## CHECKING IF BUTTON WAS TAPPED MULTIPLE TIMES
For multiple taps, you can find the number of taps with <br>`int x = button1.tapCount();`

## CHECKING IF BUTTON IS DOWN
To check if a button is currently down use<br> `if(button1.down()){...}`

## CHECKING IF BUTTON HAS CHANGED STATE

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
  `button1.userULongB`

  ## CUSTOMISING YOUR BUTTONS
  All timing parameters are available to the user. You can set the debounce period, the milliseconds after which a tap becomes a press, and the maximum gap between multiple taps (the inter-tap gap, after which it decides taps have ceased and it will return the number of taps).
  Below is an example of setting all the available custom values when creating a button.<br><br>
  To use a button connected to the GPIO2 pin which is active HIGH, debounced for 20ms, has a tap maximum time of 400ms and inter-tap gap of no more than 200ms, it is coded thus<br>
 `MultiTapButton button1(2, HIGH, 20, 400, 200);`

  ## EXAMPLE CODE
  The example code demonstrates some of the events that MultiTapButton uses. Ensure you check the button regularly in your code as the timing accuracy depends on refreshing the button's state. Best practice is to have a fast non-blocking loop and check the button in the loop() code.
