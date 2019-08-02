/*
Exploring Arduino, Second Edition
Code Listing 16-3: Proximity Lamp
https://www.exploringarduino.com/content2/ch16

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Automatically turns on/off a lamp when a smartphone connects/disconnects

// Include the nRF51 SPI Library
#include "Adafruit_BluefruitLE_SPI.h"

// On the 32U4 Feather board, the nRF51 chip is connected to the
// 32U4 hardware SPI pins. When we create the BTLE object, we tell
// it what pins are used for CS (8), IRQ (7), and RST (4):
Adafruit_BluefruitLE_SPI btle(8, 7, 4);

// This is how the BTLE device will identify itself to your smartphone
const String BTLE_NAME = "Smart Lamp";

// Set Power Level to change activation Range
// Allowed options are: -40, -20, -16, -12, -8, -4, 0, 4
// Higher numbers increase connection range
const int POWER_LEVEL = -20;

// Lamp Control Pin
const int LAMP_PIN = 5;

void setup(void)
{
  // Set Lamp Control Pin as Output and turn off
  pinMode(LAMP_PIN, OUTPUT);
  digitalWrite(LAMP_PIN, LOW);

  // We'll print debug info to the Serial console.
  Serial.begin(9600);

  // The 32U4 has a hardware USB interface, so you should leave the following
  // line uncommented if you want it to wait to start initializing until
  // you open the serial monitor. Comment out the following line if you
  // want the sketch to run without opening the serial console (or on battery).
  //while (!Serial);

  // Connect to the module.
  Serial.print(F("Initializing BTLE Module..."));
  if (!btle.begin())
  {
    Serial.println("");
    Serial.println(F("Couldn't connect to nRF51 Module."));
    while (1);
  }
  Serial.println(F("Ready!"));

  // Reset to defaults
  Serial.print(F("Resetting to Defaults..."));
  if (!btle.factoryReset())
  {
    Serial.println("");
    Serial.println(F("Couldn't reset module."));
    while (1);
  }
  Serial.println(F("Done!"));

  // Set the name to be broadcast using an AT Command
  Serial.print(F("Setting Device name..."));
  btle.print(F("AT+GAPDEVNAME="));
  btle.println(BTLE_NAME);
  if (!btle.waitForOK())
  {
    Serial.println(F("Could not set name."));
    while (1);
  }
  Serial.println(F("Done!"));

  // Set the Power Level
  Serial.print(F("Setting Power level..."));
  btle.print(F("AT+BLEPOWERLEVEL="));
  btle.println(String(POWER_LEVEL));
  if (!btle.waitForOK())
  {
    Serial.println(F("Set Power Level."));
    while (1);
  }
  Serial.println(F("Done!"));

  // Enable the HID Keyboard Profile
  // (Necessary or iOS to Recognize it without app)
  Serial.print(F("Enabling HID Keyboard..."));
  btle.println(F("AT+BLEKEYBOARDEN=1"));
  if (!btle.waitForOK())
  {
    Serial.println(F("Could not enable HID Keyboard Profile."));
    while (1);
  }
  Serial.println(F("Done!"));

  btle.reset(); // Restart the module for settings to take effect
}

void loop(void)
{
  if (btle.isConnected())
  {
    // Turn on the Lamp if connected
    digitalWrite(LAMP_PIN, HIGH);
  }
  if (!btle.isConnected())
  {
    // Turn off the Lamp if disconnected
    digitalWrite(LAMP_PIN, LOW);
  }
}
