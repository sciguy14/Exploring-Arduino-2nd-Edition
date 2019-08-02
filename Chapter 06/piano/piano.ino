/*
Exploring Arduino, Second Edition
Code Listing 6-2: Pentatonic Micro Piano
https://www.exploringarduino.com/content2/ch6

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Pentatonic Piano
//C D E G A
 
#define NOTE_C  262 //Hz
#define NOTE_D  294 //Hz
#define NOTE_E  330 //Hz
#define NOTE_G  392 //Hz
#define NOTE_A  440 //Hz

const int SPEAKER=9;   //Speaker on Pin 9

const int BUTTON_C=7;  //Button Pin
const int BUTTON_D=6;  //Button Pin
const int BUTTON_E=5;  //Button Pin
const int BUTTON_G=4;  //Button Pin
const int BUTTON_A=3;  //Button Pin


void setup()
{
 //No setup needed
 //Tone function sets outputs
}

void loop()
{
 while (digitalRead(BUTTON_C))
  tone(SPEAKER, NOTE_C);
 while(digitalRead(BUTTON_D))
  tone(SPEAKER, NOTE_D);
 while(digitalRead(BUTTON_E))
  tone(SPEAKER, NOTE_E);
 while(digitalRead(BUTTON_G))
  tone(SPEAKER, NOTE_G);
 while(digitalRead(BUTTON_A))
  tone(SPEAKER, NOTE_A);
 
 //Stop playing if all buttons have been released
 noTone(SPEAKER);
}

