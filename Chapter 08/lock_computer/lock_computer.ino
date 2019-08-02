/*
Exploring Arduino, Second Edition
Code Listing 8-2: Light-Based Computer Lock
https://www.exploringarduino.com/content2/ch8

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Locks your computer when you turn off the lights

#include <Keyboard.h>

const int LIGHT     =1;    //Light sensor on analog pin 1
const int THRESHOLD =500;  //Brightness must drop below this level to lock computer

void setup()
{
  Keyboard.begin(); 
}

void loop()
{
  int brightness = analogRead(LIGHT);    //Read the light level
 
  if (brightness < THRESHOLD)
  {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
  }
}

