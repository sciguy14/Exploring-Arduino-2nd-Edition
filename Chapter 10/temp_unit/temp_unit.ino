/*
Exploring Arduino, Second Edition
Code Listing 10-2: I2C Temperature Sensors Code with Shift Register LEDs and Serial Communication
https://www.exploringarduino.com/content2/ch10

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Reads temp from I2C temperature sensor
//show it on the LED bar graph, and show it in Processing

//Include Wire I2C library
#include <Wire.h>

const int SER   =8;  //Serial Output to Shift Register
const int LATCH =9;  //Shift Register Latch Pin
const int CLK   =10; //Shift Register Clock Pin

int temp_address = 72;

//Possible LED settings
int vals[8] = {1,3,7,15,31,63,127,255};

void setup()
{
  //Instantiate serial communication at 9600 bps
  Serial.begin(9600);
 
  //Create a Wire Object
  Wire.begin();
 
  //Set shift register pins as outputs
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop()
{
  //Send a request
  //Start talking to the device at the specified address
  Wire.beginTransmission(temp_address); 
  //Send a bit asking for register zero, the data register
  Wire.write(0); 
  //Complete Transmission 
  Wire.endTransmission(); 
 
  //Read the temperature from the device
  //Request 1 Byte from the specified address
  int returned_bytes = Wire.requestFrom(temp_address, 1); 

  //If no data was returned, then something is wrong.
  if (returned_bytes == 0)
  {
    Serial.print("Err,Err."); //Print an error
    while(1);
  }
    
  // Get the temp and read it into a variable
  int c = Wire.read(); 
 
  //Map the temperatures to LED settings
  int graph = map(c, 24, 31, 0, 7);
  graph = constrain(graph,0,7);

  digitalWrite(LATCH, LOW);         //Latch low - start sending data
  shiftOut(SER, CLK, MSBFIRST, vals[graph]); //Send data, MSB first
  digitalWrite(LATCH, HIGH);        //Latch high - stop sending data
 
  //Do some math to convert the Celsius to Fahrenheit
  int f = round(c*9.0/5.0 +32.0);
 
  Serial.print(c);
  Serial.print("C,");
  Serial.print(f);
  Serial.print("F.");
 
  delay(500);
}
