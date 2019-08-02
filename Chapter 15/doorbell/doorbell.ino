/*
Exploring Arduino, Second Edition
Code Listing 15-2: Doorbell
https://www.exploringarduino.com/content2/ch15

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//A Doorbell using the Simple RF Receiver

//Assumes that the MOMENTARY Type RF Receiver is being used!
//The M4 momentary type RF receiver acts like a push button.
//When the remote button is held down, the D2 pin on the module goes HIGH.
//When the remote button is released, the D2 pin on the module goes LOW.

#include "pitches.h" //Header file with pitch definitions

//The Arduino I/O Pin connected to pin labeled "D2" on the RF Module
const int TRIGGER_PIN = 13;
const int SPEAKER = 9;  //Speaker Pin

//Note Array
int notes[] = {
 NOTE_A4, NOTE_E3, NOTE_A4, 0, 
 NOTE_A4, NOTE_E3, NOTE_A4, 0,
 NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
 NOTE_E4, NOTE_E3, NOTE_A4, 0
};

//The Duration of each note (in ms)
int times[] = {
 250, 250, 250, 250, 
 250, 250, 250, 250,
 125, 125, 125, 125, 125, 125, 125, 125,
 250, 250, 250, 250 
};

void setup()
{
//No setup necessary  
}

void loop()
{
  //While the button is held high, play the song once.
  if (digitalRead(TRIGGER_PIN))
  {
    for (int i = 0; i < 20; i++)
    {
      tone(SPEAKER, notes[i], times[i]);
      delay(times[i]);
    }
    //In case the button is still being held down after the song finishes,
    //wait here until it is released, before playing again
    while(digitalRead(TRIGGER_PIN));
  }
}
