/*
Exploring Arduino, Second Edition
Code Listing 11-2: Accelerometer-Based Instrument
https://www.exploringarduino.com/content2/ch11

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Uses the each Axis of an Accelerometer to control lights and sounds

// Include Libraries
// This library will, itself, include the SPI and Universal Sensor Libraries
#include <Adafruit_LIS3DH.h>

// Define the pins (the SPI hardware pins are used by default)
const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int BLUE_PIN = 3;
const int SPEAKER = 9;
const int CS_PIN = 10;

// Pentatonic Piano C D E G A
#define NOTE_C  262 //Hz
#define NOTE_D  294 //Hz
#define NOTE_E  330 //Hz
#define NOTE_G  392 //Hz
#define NOTE_A  440 //Hz
#define NOTE_C2 523 //Hz

// Set up the accelerometer using the hardware SPI interface
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
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(BLUE_PIN, HIGH);
}

void loop()
{
  // Get X, Y, and Z accelerations
  accel.read();

  // Normalize the axis that is normal to the Earth
  // Subtract the raw equivalent of 1G of acceleration
  long norm_z = accel.z-16384;

  // Print all the accelerations so we can tune the thresholds below
  Serial.print(accel.x);
  Serial.print(" ");
  Serial.print(accel.y);
  Serial.print(" ");
  Serial.println(norm_z);

  // Trigger a different 100ms note based on the direction of acceleration 
  if (accel.x < -5000) tone(SPEAKER, NOTE_C, 100);
  if (accel.x > 5000) tone(SPEAKER, NOTE_D, 100);
  if (accel.y < -5000) tone(SPEAKER, NOTE_E, 100);
  if (accel.y > 5000) tone(SPEAKER, NOTE_G, 100);
  if (norm_z < -5000) tone(SPEAKER, NOTE_A, 100);
  if (norm_z > 5000) tone(SPEAKER, NOTE_C2, 100);

  // Light the LEDs proportional to the direction of acceleration
  analogWrite(RED_PIN, constrain(map(abs(accel.x),5000,20000,255,0),0,255));
  analogWrite(GREEN_PIN, constrain(map(abs(accel.y),5000,20000,255,0),0,255));
  analogWrite(BLUE_PIN, constrain(map(abs(norm_z),5000,20000,255,0),0,255));
}
