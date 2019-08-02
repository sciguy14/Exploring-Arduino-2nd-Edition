/*
Exploring Arduino, Second Edition
Code Listing 15-3: Lamp Remote
https://www.exploringarduino.com/content2/ch15

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//A Remote Control for a Lamp

//Assumes that the MOMENTARY Type RF Receiver is being used!
//The M4 momentary type RF receiver acts like a push button.
//When the remote button is held down, the D2 pin on the module goes HIGH.
//When the remote button is released, the D2 pin on the module goes LOW.

#include "pitches.h" //Header file with pitch definitions

//The Arduino I/O Pin connected to pin labeled "D2" on the RF Module
const int TRIGGER_PIN = 13; //Input from RF Module
const int SPEAKER = 9;      //Speaker Pin
const int LAMP = 2;         //Lamp Control

//Note Array
int notes[] = {NOTE_E3, NOTE_A4, NOTE_C5};

//The Duration of each note (in ms)
int times[] = {250, 250, 250};

//Default lamp to OFF
bool lamp_on = false;

void setup()
{
 pinMode(LAMP, OUTPUT); //Lamp Pin is an Output
 digitalWrite(LAMP, lamp_on); //Turn the Lamp off (this variable starts as false)
}

void loop()
{
  //When the button is pressed, change the state of the lamp
  if (digitalRead(TRIGGER_PIN))
  {
    lamp_on = !lamp_on; //Invert the state of the lamp control variable
    digitalWrite(LAMP, lamp_on); // Set the lamp to its new state
    
    //Play a different sound depending on whether the lamp turned on or off
    if (lamp_on)
    {
      // Play a tune for turning the lamp on
      for (int i = 0; i < 3; i++)
      {
        tone(SPEAKER, notes[i], times[i]);
        delay(times[i]);
      }
    }
    else
    {
      // Play a tune for turning the lamp off (same song, backwards
      for (int i = 2; i >= 0; i--)
      {
        tone(SPEAKER, notes[i], times[i]);
        delay(times[i]);
      }
    }
    
    //In case the button is still being held down after the song finishes,
    //wait here. This effectively debounces the remote signal.
    while(digitalRead(TRIGGER_PIN));
  }
}
