/*
Exploring Arduino, Second Edition
Code Listing 15-1: RF Test
https://www.exploringarduino.com/content2/ch15

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//A Simple Test of the RF Link

//Assumes that the MOMENTARY Type RF Receiver is being used!
//The M4 momentary type RF receiver acts like a push button.
//When the remote button is held down, the D2 pin on the module goes HIGH.
//When the remote button is released, the D2 pin on the module goes LOW.

//The Arduino I/O Pin connected to pin labeled "D2" on the RF Module
const int TRIGGER_PIN = A1;

//We'll just light up the on-board LED while the button is held
const int LED_PIN = 13;

//Initialize variable for holding press start time
unsigned long start_time;

//And variable for tracking state of whether we announced a new press
boolean announced;

void setup()
{
  Serial.begin(9600);
  Serial.println("RF Test");
  
  //LED pin must be configured as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_PIN, LOW); //LED off when unpressed
  announced = false; //So we only announce a new press once

  //Stay in the following loop while button is held
  while (digitalRead(TRIGGER_PIN))
  {
    //Once-per-press, do this:
    if (!announced)
    {
      start_time = millis();
      Serial.print("PRESSED...");
      announced = true; // Only print message once per hold
    }
    digitalWrite(LED_PIN, HIGH);
  }

  //Once the button is released, note how long it was held for
  if (announced)
  {
    Serial.print("RELEASED after ");
    unsigned long duration = millis() - start_time;
    Serial.print(round(duration/1000.0)); //Print press duration in seconds
    Serial.println(" second(s)."); 
  }
}
