/*
Exploring Arduino, Second Edition
Code Listing 17-2: Bare Minimum Web Server Code
https://www.exploringarduino.com/content2/ch17

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Arduino Bare Minimum Web Server
// Some code adapted from Arduino Example Code written by Tom Igoe

#include <SPI.h>
#include <WiFi101.h>

// Wi-Fi Info
const char WIFI_SSID[]     = "PUT NETWORK NAME HERE";     // Wi-Fi SSID
const char WIFI_PASSWORD[] = "PUT NETWORK PASSWORD HERE"; // Wi-Fi Password

// Indicate connection status with the On-Board LED
const int ONBOARD_LED = 13;

// The server will listen on port 80 (the standard HTTP Port)
WiFiServer server(80);

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

  // Start the server
  server.begin();
  Serial.println("Server Started!");

  // Print the IP that was received via DHCP
  IPAddress ip = WiFi.localIP();
  Serial.print("Control this Arduino at: http://");
  Serial.println(ip);
  Serial.println("");
}

void loop()
{
  // Start a server that listens for incoming client connections
  WiFiClient client = server.available();

  // Has a client (browser) connected?
  if(client)
  {
    // While the connection is alive, loop through the incoming lines
    while (client.connected())
    {
      // We'll read in one line of incoming data at a time
      String incoming_line = "";
      // Use a do-while loop so that we don't start checking line formatting
      // until the String contains its first character
      do
      {
        while(!client.available());  // Wait for the next byte to come in
        char c = client.read();  // Once it does, read it in
        incoming_line += c;  // And append it to the current line
      } while (!incoming_line.endsWith("\r\n"));
      
      Serial.print(incoming_line);  // Print line that just arrived
  
      // If last line was empty (only had the carriage return and newline)
      // Then, that means we've received the entire incoming request.

      if (incoming_line == "\r\n")
      {
        // We must acknowledge that the request was received with a valid code
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();
        
        // We can now close the connection
        delay(50);
        client.stop();
      }
    }
  }
}
