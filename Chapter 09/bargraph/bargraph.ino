/*
Exploring Arduino, Second Edition
Code Listing 9-3: A Bar Graph that responds to a distance sensor
https://www.exploringarduino.com/content2/ch9

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//A bar graph that responds to how close you are

const int SER   =8;    //Serial Output to Shift Register
const int LATCH =9;    //Shift Register Latch Pin
const int CLK   =10;   //Shift Register Clock Pin
const int DIST  =0;    //Distance Sensor on Analog Pin 0

//Possible LED settings
int vals[9] = {0,1,3,7,15,31,63,127,255};

//Maximum value provided by sensor
int maxVal = 500;

//Minimum value provided by sensor
int minVal = 0;

void setup()
{
  //Set pins as outputs
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop()
{
  int distance = analogRead(DIST);
  distance = map(distance, minVal, maxVal, 0, 8);
  distance = constrain(distance,0,8);

  digitalWrite(LATCH, LOW);                     //Latch low - start sending
  shiftOut(SER, CLK, MSBFIRST, vals[distance]); //Send data, MSB first
  digitalWrite(LATCH, HIGH);                    //Latch high - stop sending
  delay(10);                                    //Animation speed

}
