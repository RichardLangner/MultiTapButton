# MultiTapButton : Buttons and switches made easy.

<strong>
<ul>
  <li>Detects Single or Multiple taps</li>
  <li>Detects Short or Long presses</li>
  <li>Built-in debouncer removes switch noise</li>
  <li>Use almost any GPIO pin; no need for interrupts</li>
  <li>Works with active LOW or active HIGH switches</li>
  <li>Auto-repeat can be enabled</li>
  <li>Each button has its own variable storage for cleaner code</li>
  <li>All timings can be customised</li>
</ul> 
</strong>

## WHY DO I NEED IT?
At at absolute minimum, it saves you writing debounce code for each button.<br>
But it can do a lot more - it's ideal for any device using single taps or multi-taps, or even a 10 second press to reboot a device, or perhaps all of these things using only one button.<br><br>
It can also simplify coding if you have several buttons, and has the advantage that each button contains its own settings and data.

## DEFINING A BUTTON
If you have a button which pulls GPIO2 LOW when pressed, and you want to define it as <strong>'button1'</strong> you can use <br>
`MultiTapButton button1(2,LOW);`

## CHECKING IF BUTTON WAS TAPPED
To check if the button was tapped, use <br>`if(button1.tapped()){...your code here}`<br>
## CHECKING IF BUTTON WAS TAPPED MULTIPLE TIMES
For multiple taps, you can find the number of taps with <br>`int x = button1.tapCount();`<br>Tip : x can be the button's internal variable<br>`button1.userIntA = button1.tapCount();`

## CHECKING IF BUTTON IS DOWN
To check if a button is currently down use<br> `if(button1.down()){...your code here}`

## CHECKING IF BUTTON HAS CHANGED STATE

To check if a button was just pressed (switch closed) use <br>`if(button1.downEvent()){...your code here}`<br>
To check if a button just released (switch opened) use <br>`if(button1.upEvent()){...your code here}`

## CHECKING BUTTON PRESS DURATION
To check how long the button has been down, use <br>`unsigned long x = button1.downMillis();`<br>Tip : x can be the button's internal variable<br>`button1.userUlongA = button1.downMillis();`

## AUTO-REPEATING TAPS AFTER A DELAY
Hold down the button for more than a second to start auto-repeating taps.<br>
To enable auto-repeat<br>
`button1.autoRepeatEnabled(true)`<br>
To disable auto-repeat<br>
`button1.autoRepeatEnabled(false)`<br>
To check if auto-repeat is enabled<br>
`if(button1.autoRepeatEnabled()){...your code here}`<br>
To set the delay to 1500ms before auto-repeat kicks in, followed by a repeat every 300ms<br>
`button1.autoRepeatConfig(1500,300);`<br>
the default is `button1.autoRepeatConfig(1000,250)`;

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
  `button1.userULongB`<br>

  # CUSTOMISING YOUR BUTTONS (FOR ADVANCED USERS)
  As you may have noticed, the minimum you need to create a MultiTapButton is two parameters, the GPIO port number and the active level.
  <br>This is how we connect GPIO2 to be pulled low when operated -<br>
  `MultiTapButton button1(2, LOW);`<br>
  <br>This is how we connect D4 to be pulled high when operated -<br>
  `MultiTapButton button1(D4, HIGH);`<br>
  
  ## Here are a few more parameters you can use:<br>
  'Noisy' contacts may require extra debounce time. The third parameter here sets debounce time to 20ms (the default is 10ms)<br>
  `MultiTapButton button1(2, LOW, 20);`<br><br>
  Sometimes you may want to set the maximum tap period (after which it becomes a press). The forth parameter here sets it to 400ms (default is 500ms)<br>
  `MultiTapButton button1(2, LOW, 20, 400);`<br><br>
  You may want to set the inter-tap gap (after which it returns the number of taps). The last parameter here sets it to 200ms (default is 250ms)<br>
  `MultiTapButton button1(2, LOW, 20, 400, 200);`<br><br>
  To set the delay to 1500ms before auto-repeat starts (default is 1000ms), and the interval of auto taps to 200ms (default is 250ms)<br>
  `button1.autoRepeatConfig(1500, 200)`<br>
  
  ## Ensure you check the button regularly in your code
  Ensure you check the button regularly in your code as the timing accuracy depends on refreshing the button's state. In practice you should have a fast non-blocking loop and check the button in the loop() function. Avoid using `delay(..)` as it blocks the program flow.
