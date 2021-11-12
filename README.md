# MultiTapButton : Buttons and switches made easy.

<strong>
<ul>
  <li>Detects Single or Multiple taps</li>
  <li>Detects Short or Long presses</li>
  <li>Built-in debouncer removes switch noise</li>
  <li>Use almost any GPIO pin; no need for interrupts</li>
  <li>Works with active LOW or active HIGH switches</li>
  <li>Each button has its own variable storage for cleaner code</li>
</ul> 
</strong>

## WHY DO I NEED IT?
At at absolute minimum, it saves you writing debounce code for each button.<br>
But it can do a lot more - it's ideal for any device using single taps or multi-taps, or even a 10 second press to reboot a device, or perhaps all of these things using only one button.<br><br>
It can also simplify coding if you have several buttons, and has the advantage that each button contains its own settings and variables.

## DEFINING A BUTTON
If you have a button which pulls GPIO2 LOW when pressed, and you want to define it as <strong>'button1'</strong> you can use <br>
`MultiTapButton button1(2,LOW);`

## CHECKING IF BUTTON WAS TAPPED
To check if the button was tapped, use <br>`if(button1.tapped()){...your code here}`<br>
## CHECKING IF BUTTON WAS TAPPED MULTIPLE TIMES
For multiple taps, you can find the number of taps with <br>`int x = button1.tapCount();`

## CHECKING IF BUTTON IS DOWN
To check if a button is currently down use<br> `if(button1.down()){...your code here}`

## CHECKING IF BUTTON HAS CHANGED STATE

To check if a button just went 'down' (switch closed) use <br>`if(button1.downEvent()){...your code here}`<br>
To check if a button just went 'up' (switch opened) use <br>`if(button1.upEvent()){...your code here}`

## CHECKING BUTTON PRESS DURATION
To check how long the button has been down, use <br>`unsigned long x = button1.downMillis();`

## STORAGE FOR YOUR BUTTON'S VARIABLES
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

  ## CUSTOMISING YOUR BUTTONS (FOR ADVANCED USERS)
  The minimum you need to create a MultiTapButton is the GPIO port number and the active level, in this case GPIO2 and active low -<br>
  `MultiTapButton button1(2, LOW);`<br>
  ## There are 3 more parameters you can use:<br>

  'Noisy' contacts may require extra debounce time. The third parameter here sets it to 20ms (the default is 10ms)<br>
  `MultiTapButton button1(2, LOW, 20);`<br><br>
  You may want to set the maximum tap period (after which it becomes a press). The forth parameter here sets it to 400ms (default is 500ms)<br>
  `MultiTapButton button1(2, LOW, 20, 400);`<br><br>
  You may want to set the inter-tap gap (after which it returns the number of taps). The last parameter here sets it to 200ms (default is 250ms)<br>
  `MultiTapButton button1(2, LOW, 20, 400, 200);`<br><br>

 
  
  ## EXAMPLE CODE
  The example code provided demonstrates some of the events that MultiTapButton uses. Ensure you check the button regularly in your code as the timing accuracy depends on refreshing the button's state. Best practice is to have a fast non-blocking loop and check the button in the loop() code.
