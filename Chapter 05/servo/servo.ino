/*
Exploring Arduino, Second Edition
Code Listing 5-1: Servo Potentiometer Control
https://www.exploringarduino.com/content2/ch5

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Servo Potentiometer Control
#include <Servo.h>

const int SERVO = 9; //Servo on Pin 9
const int POT   = 0; //POT on Analog Pin 0

Servo myServo;
int val = 0; //For storing the reading from the POT

void setup()
{
  //Attach the Servo Object
  myServo.attach(SERVO);
}

void loop()
{
  val = analogRead(POT);           //Read Pot
  val = map(val, 0, 1023, 0, 179); //scale it to servo range 
  myServo.write(val);              //sets the servo 
  delay(15);                       //waits for the servo
}

