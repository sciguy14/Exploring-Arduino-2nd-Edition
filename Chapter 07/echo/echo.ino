/*
Exploring Arduino, Second Edition
Code Listing 7-3: Arduino Serial Echo Test
https://www.exploringarduino.com/content2/ch7

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Echo every character

char data; //holds incoming character

void setup()
{
  Serial.begin(9600); //Serial Port at 9600 baud
}

void loop()
{
  //Only print when data is received
  if (Serial.available() > 0)
  {
    data = Serial.read(); //read byte of data
    Serial.print(data);   //print byte of data
  }
}

