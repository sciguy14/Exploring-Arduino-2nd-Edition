/*
Exploring Arduino, Second Edition
Code Listing 16-2: BTLE LED
https://www.exploringarduino.com/content2/ch16

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Control an LED over BTLE

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
const String BTLE_NAME = "Jeremy's LED";

// On-Board LED is connected to Pin 13
const int STATUS_LED = 13;

// LED to be controlled is connected to Pin 5
const int CTRL_LED = 5;

// Variables to keep track of LED state
bool led_state = LOW;
String cmd = "";
String reply = "";

void setup(void)
{
  // Set LEDs as outputs and turn off
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);
  pinMode(CTRL_LED, OUTPUT);
  digitalWrite(CTRL_LED, led_state);
  
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

  // If there is incoming data available, read and parse it
  while (btle.available() > 0)
  {
    // Blink the Status LED when we receive a request
    digitalWrite(STATUS_LED, HIGH);
    
    // Read the receive buffer until there is a newline
    cmd = btle.readStringUntil('\n');
      
    Serial.print(F("Received Command: "));
    Serial.println(cmd);
    
    // Makes it lower case so we recognize the command regardless of caps
    cmd.toLowerCase();

    // Parse commands with the word "red" or "led"
    if (cmd.indexOf(F("red")) != -1 || cmd.indexOf(F("led")) != -1)
    {
      // Command contains "on"
      if (cmd.indexOf(F("on")) != -1)
      {
        led_state = HIGH; 
        reply = F("OK! The LED has been turned on.");
      }
      
      // Command contains "off"
      else if (cmd.indexOf(F("off")) != -1)
      {
        led_state = LOW;
        reply = F("OK! The LED has been turned off.");
      }

      // Command contains "toggle"
      else if (cmd.indexOf(F("toggle")) != -1)
      {
        led_state = !led_state;
        if (led_state) reply = F("OK! The LED has been toggled on.");
        else reply = F("OK! The LED has been toggled off.");
      }

      // Command contained "red" or "led", but none of the other keywords
      else 
      {
        if (led_state) reply = F("The LED is currently on.");
        else reply = F("The LED is currently off.");
      }

      // Set the LED state
      digitalWrite(CTRL_LED, led_state);
    }
    else
    {
      reply = F("Command not understood.");
    }

    // Acknowledge Command
    btle.println(reply);
    Serial.print(F("Replied With: "));
    Serial.println(reply);
    btle.waitForOK();
    digitalWrite(STATUS_LED, LOW);
  }
}
