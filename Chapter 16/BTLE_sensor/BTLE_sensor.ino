/*
Exploring Arduino, Second Edition
Code Listing 16-1: BTLE Sensor
https://www.exploringarduino.com/content2/ch16

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Send sensor data over BTLE

// Include the nRF51 SPI Library
#include "Adafruit_BluefruitLE_SPI.h"

// On the 32U4 Feather board, the nRF51 chip is connected to the
// 32U4 hardware SPI pins. When we create the BTLE object, we tell
// it what pins are used for CS (8), IRQ (7), and RST (4):
Adafruit_BluefruitLE_SPI btle(8, 7, 4);

// Set this to true for one time configuration
// This performs a factory reset, then changes the broadcast name.
// There is no harm in redoing this at each boot (leave true).
// You can set this to false after you have programmed the module one time.
const bool PERFORM_CONFIGURATION = true; 

// This is how the BTLE device will identify itself to your smartphone
const String BTLE_NAME = "Jeremy's Sensor";

// Potentiometer is connected to pin A0
const int POT = A0;

// On-Board LED is connected to Pin 13
const int STATUS_LED = 13;

void setup(void)
{
  // Set LED as output
  pinMode(STATUS_LED, OUTPUT);
  
  // We'll print debug info to the Serial console.
  Serial.begin(9600);
  
  // The 32U4 has a hardware USB interface, so you should leave the following
  // line uncommented if you want it to wait to start initializing until
  // you open the serial monitor. Comment out the following line if you
  // want the sketch to run without opening the serial console (or on battery).
  while(!Serial);

  // Connect to the module.
  Serial.print(F("Initializing BTLE Module..."));
  if (!btle.begin())
  {
    Serial.println("");
    Serial.println(F("Couldn't connect to nRF51 Module."));
    while(1);
  }
  Serial.println(F("Ready!"));

  // Reset the BTLE chip to factory defaults if specified.
  // You can trigger this to recover from any programming errors you
  // make that render the module unresponsive.
  // After doing factory reset of the module, it sets its broadcast name
  if (PERFORM_CONFIGURATION)
  {
    // Reset to defaults
    Serial.print(F("Resetting to Defaults..."));
    if (!btle.factoryReset())
    {
      Serial.println("");
      Serial.println(F("Couldn't reset module."));
      while(1);
    }
    Serial.println(F("Done!"));

    // Set the name to be broadcast using an AT Command
    Serial.print(F("Setting Device name..."));
    btle.print(F("AT+GAPDEVNAME="));
    btle.println(BTLE_NAME);
    if (!btle.waitForOK())
    {
      Serial.println(F("Could not set name."));
      while(1);
    }
    btle.reset(); // Restart the module for new name to take effect
    Serial.println(F("Done!"));
  }
  
  //Switch to Data mode (from command mode)
  btle.setMode(BLUEFRUIT_MODE_DATA);
}

void loop(void)
{
  // Wait for a smartphone to connect if it isn't already
  if (!btle.isConnected())
  {
    Serial.print("Waiting to connect to a smartphone...");
    while (!btle.isConnected())
    {
        delay(1000);
    }
    Serial.println("Connected!");
  }
  
  // Get the Value of the Potentiometer
  int val = analogRead(POT);

  // Print the value to the attached serial number
  Serial.print(F("Analog Value: "));
  Serial.print(val);
  Serial.print(F("\tSending..."));

  // Send the data to the BTLE module to be sent via BTLE Serial
  // Blink the LED when we do this.
  digitalWrite(STATUS_LED, HIGH);
  btle.println(val);
  
  // Wait for the BTLE module to acknowledge it received the data
  btle.waitForOK();
  Serial.println(F("OK!"));
  digitalWrite(STATUS_LED, LOW);
}
