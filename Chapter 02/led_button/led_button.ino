/*
Exploring Arduino, Second Edition
Code Listing 2-4: Simple LED Control with a Button
https://www.exploringarduino.com/content2/ch2

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

const int LED=9;         // The LED is connected to pin 9
const int BUTTON=2;      // The Button is connected to pin 2

void setup()
{
  pinMode (LED, OUTPUT);     // Set the LED pin as an output
  pinMode (BUTTON, INPUT);   // Set button as input (not required)
}

void loop()
{
  if (digitalRead(BUTTON) == LOW)
  {
    digitalWrite(LED, LOW);
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
}
