/*
Exploring Arduino, Second Edition
Code Listing 13-2: Simple Timer Interrupt Blink Test
https://www.exploringarduino.com/content2/ch13

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Using Timer Interrupts with the Arduino
#include <TimerOne.h>
const int LED=13;
 
void setup() 
{
  pinMode(LED, OUTPUT);  
  Timer1.initialize(1000000); //Set a timer of length 1000000 microseconds
  Timer1.attachInterrupt(blinky); //Runs "blinky" on each timer interrupt
}
 
void loop()
{
  //Put any other code here.
}
 
//Timer interrupt function
void blinky()
{
  digitalWrite(LED, !digitalRead(LED)); //Toggle LED State
}
