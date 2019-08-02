/*
Exploring Arduino, Second Edition
Code Listing 17-5: Get the Temperature from the Web!
https://www.exploringarduino.com/content2/ch17

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Gets Live Weather Data from the Web

#include <SPI.h>
#include <WiFi101.h>
#include <Arduino_JSON.h>

// Wi-Fi Info
const char WIFI_SSID[]     = "PUT NETWORK NAME HERE";      // Wi-Fi SSID
const char WIFI_PASSWORD[] = "PUT NETWORK PASSWORD HERE";  // Wi-Fi Password

// API Info
const char SERVER[] = "api.openweathermap.org";
const char HOST_STRING[] = "HOST: api.openweathermap.org";
const String API_KEY = "PUT YOUR API KEY HERE";
const String CITY = "San Francisco";  // Replace with your City
const String UNITS = "F"; // Set to F or C

// Indicate connection status with the On-Board LED
const int ONBOARD_LED = 13;

// The Arduino is the Client
WiFiClient client;

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

  Serial.println("Let's Get the Temperature from a Web API!");

  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  WiFi.setTimeout(5000);  // Allow up to 5 seconds for Wi-Fi to connect
  while (wifi_status != WL_CONNECTED)
  {
    wifi_status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
  Serial.println("Connected!\n");
  digitalWrite(ONBOARD_LED, HIGH);  // Turn on the Onboard LED when we connect

  // Prepare the API Request
  String api_units = "metric";
  if (UNITS == "F")
  {
    api_units = "imperial";
  }
  String request = "GET /data/2.5/weather?units=" + 
                   api_units + 
                   "&q=" + 
                   CITY + 
                   "&appid=" + 
                   API_KEY + 
                   " HTTP/1.1";

  // Connect to Server and issue a Request
  if (client.connect(SERVER, 80))
  {
    Serial.println("Sending Request: ");
    Serial.println(request);
    Serial.println("");
    client.println(request);
    client.println(HOST_STRING);
    client.println("Connection: close");
    client.println();
  }

  // Wait for available reply
  while (!client.available());
   
  // Throw data out until we get to the JSON object that starts with '{'
  // Print the header info so issues can be debugged
  while(true)
  {
    char h = client.read();
    if (h == '{') break;
    Serial.print(h);
  }

  // Once we hit the JSON data, read it into a String
  String json = "{";
  do
  {
    char c = client.read();
    json += c;
  } while (client.connected());
  client.stop();
  JSONVar api_object = JSON.parse(json);
  Serial.println("Raw JSON:");
  Serial.println(api_object);
  double temp = (double) api_object["main"]["temp"];
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(UNITS);
}

void loop()
{
  // Nothing! We're just getting the data one time in setup
}
