/*
Exploring Arduino, Second Edition
Code Listing 11-1: Accelerometer-Based Orientation Sensor
https://www.exploringarduino.com/content2/ch11

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Uses the Z-Axis of an Accelerometer to detect orientation

// Include Libraries
// This library will, itself, include the SPI and Universal Sensor Libraries
#include <Adafruit_LIS3DH.h>

// Define the pins (the SPI hardware pins are used by default)
const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int CS_PIN = 10;

// Set Up the accelerometer using the hardware SPI interface
Adafruit_LIS3DH accel = Adafruit_LIS3DH(CS_PIN);

void setup()
{
  Serial.begin(9600); // Set up the serial port so we can see readings

  // Connect to the accelerometer
  if (!accel.begin())
  {
    Serial.println("Could not find accelerometer.");
    while (1); // Loop forever
  }

  // Set the sensitivity of the accelerometer to +/-2G
  accel.setRange(LIS3DH_RANGE_2_G);


  // Set the LED cathode pins as outputs and turn them off
  // HIGH is off because this is a common anode LED
  pinMode(RED_PIN, OUTPUT);
  digitalWrite(RED_PIN, HIGH);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(GREEN_PIN, HIGH);
}

void loop()
{
  // Get X, Y, and Z accelerations
  accel.read();

  // Print the Raw Z Reading
  Serial.print("Raw: ");
  Serial.print(accel.z);

  // Map the Raw Z Reading G's based on +/-2G Range
  Serial.print("\tActual: ");
  Serial.print((float(accel.z)/32768.0)*2.0);
  Serial.println("G");

  // Check if we are upside-down
  if (accel.z < 0)
  {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
  else
  {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  }

  // Get new data every 100ms
  delay(100); 
}
