/*
Exploring Arduino, Second Edition
Code Listing 2-1: Turning on an LED
https://www.exploringarduino.com/content2/ch2

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

const int LED=9;            // Define LED for pin 9
void setup()
{
  pinMode (LED, OUTPUT);    // Set the LED pin as an output
  digitalWrite(LED, HIGH);  // Set the LED pin high
}

void loop()
{
  // We are not doing anything in the loop!
}
