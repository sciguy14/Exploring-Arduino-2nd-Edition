/*
Exploring Arduino, Second Edition
Code Listing 5-3: Stepper Control
https://www.exploringarduino.com/content2/ch5

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Simple Stepper Control with an H-Bridge

#include <Stepper.h>

//Motor Constants
//Most NEMA-17 Motors have 200 steps/revolution
const int STEPS_PER_REV = 200; //200 steps/rev

//H-Bridge Pins
const int COIL1_MC1  = 2;  //COIL 1 Switch 1 Control
const int COIL1_MC2  = 3;  //COIL 1 Switch 2 Control
const int COIL2_MC1  = 4;  //COIL 2 Switch 1 Control
const int COIL2_MC2  = 5;  //COIL 2 Switch 2 Control

// Initialize the stepper library - pass it the Switch control pins
Stepper myStepper(STEPS_PER_REV, COIL1_MC1, COIL1_MC2, COIL2_MC1, COIL2_MC2);

void setup()
{
  //Set the stepper speed
  myStepper.setSpeed(60); //60 RPM
}

void loop()
{
  // step one revolution in one direction:
  myStepper.step(STEPS_PER_REV);
  delay(500);

  // step one revolution in the other direction:
  myStepper.step(-STEPS_PER_REV);
  delay(500);
}
