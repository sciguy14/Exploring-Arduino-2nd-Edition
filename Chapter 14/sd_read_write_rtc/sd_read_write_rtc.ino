/*
Exploring Arduino, Second Edition
Code Listing 14-3: SD Reading and Writing with an RTC
https://www.exploringarduino.com/content2/ch14

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//SD read and write with RTC

//Uncomment following line if your board uses the DS1307 instead of the PCF8523
//#define RTC_CHIP_IS_DS1307

//Uncomment following line if you want to force the time to be set
//Should always be commented out before "running in the field"
//#define FORCE_UPDATE

#include <SD.h> //Include the SD Card Library
#include <Wire.h>  //For RTC I2C
#include "RTClib.h" //For RTC

//SD Card is on standard SPI Pins
//RTC is on standard I2C Pins

//We always need to set the CS Pin for the SD Card
const int CS_PIN  = 10;

//Default rate of 5 seconds can be overwritten by speed.txt file
int refresh_rate = 5000;

// Use compiler flags to set up the right chip type
#ifdef RTC_CHIP_IS_DS1307
  RTC_DS1307 RTC;
  String chip = "DS1307";
#else
  RTC_PCF8523 RTC;
  String chip = "PCF8532";
#endif

// Use compiler flags to decide if an update should be forced
#ifdef FORCE_UPDATE
  bool update_clock = true;
#else
  bool update_clock = false;
#endif

//Initialize date and time strings
String time, date;

void updateDateTime()
{
  //Get the current date and time info and store in strings
  DateTime datetime = RTC.now();
  String year  = String(datetime.year(),  DEC);
  String month = String(datetime.month(), DEC);
  String day  = String(datetime.day(),  DEC);
  String hour  = String(datetime.hour(),  DEC);
  String minute = String(datetime.minute(), DEC);
  String second = String(datetime.second(), DEC);
 
  //Concatenate the strings into date and time
  date = year + "/" + month + "/" + day;
  time = hour + ":" + minute + ":" + second;
}

void setup()
{
  Serial.begin(9600);
 
  //CS pin must be configured as an output
  pinMode(CS_PIN, OUTPUT);
 
  //Initiate the RTC library
  RTC.begin();
 
  //Always update the time if the RTC isn't running
  #ifdef RTC_CHIP_IS_DS1307
    if (!RTC.isrunning()) update_clock = true;
  #else
    if (!RTC.initialized()) update_clock = true;
  #endif

  //If RTC not running or if we force it, set RTC to computer's compile time
  if (update_clock)
  {
    Serial.print(F("Setting "));
    Serial.print(chip);
    Serial.print(F(" time to compile time..."));
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println(F("Done!"));
  }
  else
  {
    Serial.print(chip);
    Serial.println(F(" time is already set!"));
  }

  //Show the time
  updateDateTime();
  Serial.print(F("RTC Date: "));
  Serial.println(date);
  Serial.print(F("RTC time: "));
  Serial.println(time);
 
  //Initialize SD card
  Serial.print(F("Initializing SD Card..."));
  if (!SD.begin(CS_PIN))
  {
    Serial.println(F("Card Failure!"));
    while(1);
  }
  Serial.println(F("Card Ready!"));
 
//Read the configuration information (speed.txt)
  File commandFile = SD.open("speed.txt");
  if (commandFile)
  {
     Serial.print(F("Reading Command File..."));
  
     while(commandFile.available())
     {
       refresh_rate = commandFile.parseInt();
     }
     Serial.print(F("Refresh Rate = "));
     Serial.print(refresh_rate);
     Serial.println(F("ms"));
     commandFile.close(); //Close the file when finished
  }  
  else
  {
    Serial.println(F("Could not read command file."));
    Serial.print(F("Will use default refresh rate of "));
    Serial.print(refresh_rate);
    Serial.println(F("ms!"));
  } 
 
  //Write column headers
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(F("\nNew Log Started!"));
    dataFile.println(F("Date,Time,Phrase"));
    dataFile.close(); //Data isn't written until we run close()!
  
    //Print same thing to the screen for debugging
    Serial.println(F("\nNew Log Started!"));
    Serial.println(F("Date,Time,Phrase"));
  }
  else
  {
    Serial.println(F("Couldn't open log file"));
    while(1);
  }
 
}

void loop()
{ 
  updateDateTime(); //Get the current date/time
  String dataString = "Hello There!";
 
  //Open a file and write to it.
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    
    dataFile.print(date);
    dataFile.print(F(","));
    dataFile.print(time);
    dataFile.print(F(","));
    dataFile.println(dataString);
    dataFile.close(); //Data isn't written until we run close()!
  
    //Print same thing to the screen for debugging
    Serial.print(date);
    Serial.print(F(","));
    Serial.print(time);
    Serial.print(F(","));
    Serial.println(dataString);
  }
  else
  {
    Serial.println(F("Couldn't open log file!"));
  }
  delay(refresh_rate);
}
