/*
Exploring Arduino, Second Edition
Code Listing 7-5: RGB LED Control via Serial
https://www.exploringarduino.com/content2/ch7

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Sending Multiple Variables at Once
//Send Data in this format: <0-100>,<0-100>,<0,100)>\n
//Where the three numbers represent percentage brightness of R, G, B.

//Define LED Pins
const int RED   = 11;
const int GREEN = 10;
const int BLUE  = 9;

void setup()
{
  Serial.begin(9600); //Serial Port at 9600 baud
  Serial.setTimeout(10); //Serial timeout to wait for for int
 
  //Set pins as outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  //Turn off the LED
  //It is common-anode, so setting the cathode pins to HIGH turns the LED off
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

void loop()
{
  //Read data when it's available in the buffer
  if (Serial.available() > 0)
  {
    //Expect to receive 3 integers over serial
    //parseInt will "block" until a valid integer is received
    //parseInt knows the full integer was received once a non-digit (comma or newline) is seen
    //parseInt only removes invalid characters before the found int, not after
    int val1 = Serial.parseInt();
    int val2 = Serial.parseInt();
    int val3 = Serial.parseInt();

    //Throw out anything that remains in the buffer after integers are read
    while (Serial.available())
    {
      Serial.read();
    }

    //Constrain the received values to be only from 0 to 100%
    int val1c = constrain(val1,0,100);
    int val2c = constrain(val2,0,100);
    int val3c = constrain(val3,0,100);

    //Map the values from percentages to analog values
    int rval = map(val1c,0,100,255,0);  //first valid integer
    int gval = map(val2c,0,100,255,0);  //second valid integer
    int bval = map(val3c,0,100,255,0);  //third valid integer

    //set LED brightness
    analogWrite(RED, rval);
    analogWrite(GREEN, gval);
    analogWrite(BLUE, bval);
    
    //Report Values that were used to set the LED
    Serial.println("Red:   " + String(val1c) + "%");
    Serial.println("Green: " + String(val2c) + "%");
    Serial.println("Blue:  " + String(val3c) + "%\n");
  }
}

