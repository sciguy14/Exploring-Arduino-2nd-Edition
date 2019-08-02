/*
Exploring Arduino, Second Edition
Code Listing 9-2: Light Rider Sequence Code
https://www.exploringarduino.com/content2/ch9

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Make a light rider animation

const int SER   =8;    //Serial Output to Shift Register
const int LATCH =9;    //Shift Register Latch Pin
const int CLK   =10;   //Shift Register Clock Pin

//Sequence of LEDs
int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2};

void setup()
{
  //Set pins as outputs
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 14; i++)
  {
    digitalWrite(LATCH, LOW);             //Latch Low - start sending
    shiftOut(SER, CLK, MSBFIRST, seq[i]); //Shift Most Sig. Bit First
    digitalWrite(LATCH, HIGH);            //Latch High - stop sending
    delay(100);                           //Animation Speed
  }
}

