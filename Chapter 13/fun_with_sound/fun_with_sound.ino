/*
Exploring Arduino, Second Edition
Code Listing 13-3: Sound Machine Code
https://www.exploringarduino.com/content2/ch13

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Use Hardware and Timer Interrupts for Fun with Sound

//Include the TimerOne library
#include <TimerOne.h>

//Button pins
const int BTN     = 2;  //Output of debounced button on pin 2
const int SPEAKER = 12; //Speaker on pin 12

//Music keys
#define NOTE_C 65
#define NOTE_D 73
#define NOTE_E 82
#define NOTE_F 87
#define NOTE_G 98
#define NOTE_A 110
#define NOTE_B 123

//Volatile variables can change inside interrupts
volatile int key = NOTE_C;
volatile int octave_multiplier = 1;

void setup()
{
  //Set up serial
  Serial.begin(9600);
 
  pinMode (SPEAKER, OUTPUT);
  
  //The pin is inverted, so we want to look at the rising edge
  attachInterrupt(digitalPinToInterrupt(BTN), changeKey, RISING);
 
  //Set up timer interrupt
  Timer1.initialize(500000);           // Trigger every 0.5 seconds
  Timer1.attachInterrupt(changePitch); //Runs "changePitch" on each interrupt
}

void changeKey()
{
  octave_multiplier = 1;
  if (key == NOTE_C)
    key = NOTE_D;
  else if (key == NOTE_D)
    key = NOTE_E;
  else if (key == NOTE_E)
    key = NOTE_F;
  else if (key == NOTE_F)
    key = NOTE_G;
  else if (key == NOTE_G)
    key = NOTE_A;
  else if (key == NOTE_A)
    key = NOTE_B;
  else if (key == NOTE_B)
    key = NOTE_C;
}

//Timer interrupt function
void changePitch()
{
  octave_multiplier = octave_multiplier * 2;
  if (octave_multiplier > 16) octave_multiplier = 1;
  tone(SPEAKER,key*octave_multiplier);
}

void loop()
{
  Serial.print("Key: ");
  Serial.print(key);
  Serial.print(" Multiplier: ");
  Serial.print(octave_multiplier);
  Serial.print(" Frequency: ");
  Serial.println(key*octave_multiplier);
  delay(100);
}
