/*
Exploring Arduino, Second Edition
Code Listing 3-1: Potentiometer Reading Sketch
https://www.exploringarduino.com/content2/ch3

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Potentiometer Reading Program

const int POT=0;  // Pot on Analog Pin 0
int val = 0;      // Variable to hold the analog reading from the POT

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  val = analogRead(POT);
  Serial.println(val);
  delay(500);
}
