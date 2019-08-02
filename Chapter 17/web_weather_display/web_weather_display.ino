/*
Exploring Arduino, Second Edition
Code Listing 17-6: A Web-Connected Temperature Display
https://www.exploringarduino.com/content2/ch17

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Gets Live Weather Data and Displays it on a big 7-seg Readout

#include <SPI.h>
#include <WiFi101.h>
#include <Arduino_JSON.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// Wi-Fi Info
const char WIFI_SSID[]     = "PUT NETWORK NAME HERE";      // Wi-Fi SSID
const char WIFI_PASSWORD[] = "PUT NETWORK PASSWORD HERE";  // Wi-Fi Password

// API Info
const char SERVER[] = "api.openweathermap.org";
const char HOST_STRING[] = "HOST: api.openweathermap.org";
const String API_KEY = "PUT YOU API KEY HERE";
const String CITY = "San Francisco";  // Replace with your City
String UNITS = "F"; // Set to F or C

// Indicate connection status with the On-Board LED
const int ONBOARD_LED = 13;

// Make the 7-Seg Display Object
Adafruit_7segment seven_seg_display = Adafruit_7segment();

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

  // Initialize the display on its default I2C Address
  seven_seg_display.begin(0x70);

  // Start the Serial Interface
  Serial.begin(9600);

  // The M0 has a hardware USB interface, so you should leave the following
  // line uncommented if you want it to wait to start initializing until
  // you open the serial monitor. Comment out the following line if you
  // want the sketch to run without opening the serial console (or on battery).
  // while(!Serial);

  Serial.println("Web-Connected Temperature Display");

  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  WiFi.setTimeout(5000);  // Allow up to 5 seconds for Wi-Fi to connect
  while (wifi_status != WL_CONNECTED)
  {
    wifi_status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
  Serial.println("Connected!\n");
  digitalWrite(ONBOARD_LED, HIGH);  // Turn on the Onboard LED when we connect
}

void loop()
{
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
  
  // Show the temperature on the display
  int temp_round = constrain(round(temp), -99, 999);
  Serial.print("Displaying: ");
  Serial.print(temp_round);
  Serial.println(UNITS);

  // Prints right justified, so multiplying by 10 moves it left one digit
  // This makes room for the "C" or "F" unit to the right
  seven_seg_display.print(temp_round*10); 

  // This prints the dot that will serve as the degree sign
  seven_seg_display.writeDigitRaw(2, 0x10);  

  // Print the units
  if (UNITS == "F")
  {
    seven_seg_display.writeDigitRaw(4,0x71);  // Print a "F"
    UNITS = "C"; // Show the opposite unit on the next update
  }
  else
  {
    seven_seg_display.writeDigitRaw(4,0x39);  // Print a "C"
    UNITS = "F"; // Show the opposite unit on the next update
  }

  //Write to the display
  seven_seg_display.writeDisplay(); 

  // Wait about one minute before checking again
  Serial.print("Waiting one minute before next check.");
  for (int i = 0; i <60; i++)
  {
    Serial.print(".");
    delay(1000); // Delay 1 second
  }
  Serial.println("");
  Serial.println("");

}
