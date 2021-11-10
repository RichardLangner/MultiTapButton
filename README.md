# MultiTapButton Class : for Buttons and Switches.

Key features:
<strong>
<ul>
  <li>Detects Single or Multiple taps</li>
  <li>Detects Short or Long presses</li>
  <li>Built-in debounce</li>
  <li>Does not use interrupts</li>
  <li>Works on any GPIO pin</li>
  <li>Works on active LOW or active HIGH switches</li>
  <li>Free variable storage, making cleaner code</li>
  <li>Simple to use.</li>  
</ul> 
</strong>

## DEBOUNCE EXAMPLE (simple)
At its simplest, MultiTapButton debounces a physical button or switch.

If you have <strong>'button1'</strong>which pulls GPIO2 LOW when pressed (active LOW), declare it thus<br>
`MultiTapButton button1(2,LOW);`

## DEBOUNCE EXAMPLE (noisy environment)
In noisy environments, you may want to specify a longer debounce period.	
Here is how you define 20ms debounce period <br>
`MultiTapButton button1(2, LOW, 20)`

## TAPS
To check if the button was tapped use `if(button1.tapped()){...}`<br><br>
If you need to know the number of taps use `int x = button1.tapCount();`
	
## BUTTON EVENTS
You can check if a button (or swith) has just changed state.<br>
if a button just went 'down' (switched closed) use `if(button1.downEvent()){...}`
if a button just went 'up' (switched closed) use `if(button1.upEvent()){...}`

## LONG PRESSES
You can check if a button is down (switch closed) and how long for.<br><br>
To check if a button down use `if(button1.down()){...}`<br>
To check how long the button was down for use `unsigned long x = button1.downMillis();`
if button is still down after (ms)	`if(button1.downMillis(1000)){...}`
		

 For ease of coding, you can use each button's inbuilt general purpose user variables.
 E.G.use integers as counters, and booleans for toggling things on/off, unsigned
 longs for large numbers such as millis();
	`button1.userIntA`				Spare Integer, free for you to use.
	`button1.userIntB`				Spare Integer, free for you to use.
	`button1.userBoolA`				Spare Boolean, free for you to use.
	`button1.userBoolB`				Spare Boolean, free for you to use.
    `button1.userULongA`			Spare Unsigned Long,free for you to use.
    `button1.userULongB`			Spare Unsigned Long,free for you to use. 
*/
