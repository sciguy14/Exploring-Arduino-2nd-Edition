/*
Exploring Arduino, Second Edition
Code Listing 4-2: Adjustable Speed Control
https://www.exploringarduino.com/content2/ch4

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Motor Speed Control with a Pot

const int MOTOR=9;  //Motor on Digital Pin 9
const int POT=0;    //POT on Analog Pin 0

int val = 0;

void setup()
{
    pinMode (MOTOR, OUTPUT);
}

void loop()
{
    val = analogRead(POT);
    val = map(val, 0, 1023, 0, 255);
    analogWrite(MOTOR, val);
}


