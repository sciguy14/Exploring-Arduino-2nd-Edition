/*
Exploring Arduino, Second Edition
Code Listing 17-1: Connect to Wi-Fi
https://www.exploringarduino.com/content2/ch17

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Connect a Feather M0 with ATWINC1500 to Wi-Fi

#include <SPI.h>
#include <WiFi101.h>

// Wi-Fi Info
const char WIFI_SSID[]     = "PUT NETWORK NAME HERE";      // Wi-Fi SSID
const char WIFI_PASSWORD[] = "PUT NETWORK PASSWORD HERE";  // Wi-Fi Password

// Indicate connection status with the On-Board LED
const int ONBOARD_LED = 13;

// To keep track of whether we are associated with a Wi-Fi Access Point:
int wifi_status = WL_IDLE_STATUS; 

void setup()
{
  // Configure the right pins for the Wi-Fi chip
  WiFi.setPins(8,7,4,2);

  // Setup the Pins
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);

  // Start the Serial Interface
  Serial.begin(9600);

  // The M0 has a hardware USB interface, so you should leave the following
  // line uncommented if you want it to wait to start initializing until
  // you open the serial monitor. Comment out the following line if you
  // want the sketch to run without opening the serial console (or on battery).
  while(!Serial);

  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  WiFi.setTimeout(5000);  // Allow up to 5 seconds for Wi-Fi to connect
  while (wifi_status != WL_CONNECTED)
  {
    wifi_status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
  Serial.println("Connected!\n");
  digitalWrite(ONBOARD_LED, HIGH);  // Turn on the Onboard LED when we connect

  // Print the IP that was received via DHCP
  IPAddress ip = WiFi.localIP();
  Serial.print("This Arduino's IP is: ");
  Serial.println(ip);
  Serial.println("");
}

void loop()
{
  // Do Nothing
}
