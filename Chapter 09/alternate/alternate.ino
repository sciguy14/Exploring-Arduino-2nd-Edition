/*
Exploring Arduino, Second Edition
Code Listing 9-1: Alternating LED Pattern on a Shift Register
https://www.exploringarduino.com/content2/ch9

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Alternating LED Pattern using a Shift Register

const int SER   =8;    //Serial Output to Shift Register
const int LATCH =9;    //Shift Register Latch Pin
const int CLK   =10;   //Shift Register Clock Pin

void setup()
{
  //Set pins as outputs
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  
  digitalWrite(LATCH, LOW);                //Latch Low
  shiftOut(SER, CLK, MSBFIRST, B10101010); //Shift Most Sig. Bit First
  digitalWrite(LATCH, HIGH);               //Latch High - Show pattern
}

void loop()
{
  //Do nothing
}

