/*
Exploring Arduino, Second Edition
Code Listing 7-6: Arduino Code to send Data to the Computer
https://www.exploringarduino.com/content2/ch7

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Sending POT value to the computer

const int POT=0; //Pot on Analog Pin 0

int val; //For holding mapped pot value

void setup()
{
  Serial.begin(9600); //Start Serial
}

void loop()
{
  val = map(analogRead(POT), 0, 1023, 0, 255); //Read and map POT
  Serial.println(val);                         //Send value
  delay(50);                                   //Delay so we don't flood the computer
}

