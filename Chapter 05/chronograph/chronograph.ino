/*
Exploring Arduino, Second Edition
Code Listing 5-4: Chronograph Project
https://www.exploringarduino.com/content2/ch5

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//One Minute Chronograph with Start/Stop/Reset

#include <Stepper.h>

//Most NEMA-17 Motors have 200 steps/revolution
const int STEPS_PER_REV = 200; //200 steps/rev

//To do one rotation in a minute,
//we need to know the milliseconds required between steps:
//60 seconds * 1000ms / 200 steps = 300 ms/step
const int MS_PER_STEP = 300; 

//H-Bridge Pins
const int COIL1_MC1  = 2;  //COIL 1 Switch 1 Control
const int COIL1_MC2  = 3;  //COIL 1 Switch 2 Control
const int COIL2_MC1  = 4;  //COIL 2 Switch 1 Control
const int COIL2_MC2  = 5;  //COIL 2 Switch 2 Control

//Button Pins
const int START = 8;  //Start Button
const int STOP  = 9;  //Stop Button

//Tracking Variables
unsigned long last_time = 0;
unsigned long curr_time = 0;
int steps_taken = 0;

// Initialize the stepper library - pass it the Switch control pins
Stepper chronograph(STEPS_PER_REV, COIL1_MC1, COIL1_MC2, COIL2_MC1, COIL2_MC2);

void setup()
{
  //Set the stepper speed high so each "tick" is fast
  chronograph.setSpeed(200); //200 RPM

  //Setup Pullups on Buttons
  pinMode(START, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
}

void loop()
{
  //Endless Loop - wait here until start is pressed
  //The Semicolon after the while loop definitions keeps us
  //here until the condition is no longer met
  while(digitalRead(START) == HIGH);

  last_time = millis(); //Get the time when we started

  //Keep Going in this loop until stopped, or minute has elapsed
  while(digitalRead(STOP) == HIGH && steps_taken < STEPS_PER_REV)
  {
    curr_time = millis();
    
    //If enough time has passed, go one step
    if(curr_time - last_time >= MS_PER_STEP)
    {
      chronograph.step(1); //Move one step
      steps_taken++; //Increment the steps_taken variable
      last_time=curr_time; //Set the last time equal to the current time
    }
  }

  //If we get here, the stop button has been pressed or a minute elapsed.
  //If we didn't go the full rotation, return to start
  if (steps_taken < STEPS_PER_REV) chronograph.step(-steps_taken);
  //Reset the step tracker
  steps_taken = 0;
  
}
