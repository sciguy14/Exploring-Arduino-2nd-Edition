/*
Exploring Arduino, Second Edition
Code Listing 3-3: Automatic Nightlight Sketch
https://www.exploringarduino.com/content2/ch3

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Automatic Night Light

const int WLED=9;        // White LED Anode on pin 9 (PWM)
const int LIGHT=0;       // Light Sensor on Analog Pin 0
const int MIN_LIGHT=200; // Minimum Expected light value
const int MAX_LIGHT=900; // Maximum Expected Light value
int val = 0;             // Variable to hold the analog reading

void setup()
{
  pinMode(WLED, OUTPUT); // Set White LED pin as output
}

void loop()
{
  val = analogRead(LIGHT);                      // Read the light sensor
  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0); // Map the light reading
  val = constrain(val, 0, 255);                 // Constrain light value
  analogWrite(WLED, val);                       // Control the White LED
}
