/*
Exploring Arduino, Second Edition
Code Listing 8-1: Temperature and Light Data Logger
https://www.exploringarduino.com/content2/ch8

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Light and Temp Logger

#include <Keyboard.h>

const int TEMP   =0;      //Temp sensor on analog pin 0
const int LIGHT  =1;      //Light sensor on analog pin 1
const int LED    =3;      //Red LED on pin 3
const int BUTTON =2;      //The button is connected to pin 2

boolean lastButton = LOW;    //Last button state
boolean currentButton = LOW; //Current button state
boolean running = false;     //Not running by default
int counter = 1;             //An index for logged data entries

void setup()
{
  pinMode (LED, OUTPUT);   //Set red LED as output
  Keyboard.begin();        //Start keyboard emulation
}

void loop()
{
  currentButton = debounce(lastButton);           //Read debounced state
 
  if (lastButton == LOW && currentButton == HIGH) //If it was pressed…
    running = !running;                           //Toggle running state
  
  lastButton = currentButton;                     //Reset button value
 
  if (running)                            //If the logger is running
  {
    digitalWrite(LED, HIGH);              //Turn the LED on
    if (millis() % 1000 == 0)             //If time is multiple of 1000ms
    {
      int temperature = analogRead(TEMP); //Read the temperature
      int brightness = analogRead(LIGHT); //Read the light level
      Keyboard.print(counter);            //Print the index number
      Keyboard.print(",");                //Print a comma
      Keyboard.print(temperature);        //Print the temperature
      Keyboard.print(",");                //Print a comma
      Keyboard.println(brightness);       //Print brightness (and a newline)
      counter++;                          //Increment the counter
    }
  }
  else
  {
    digitalWrite(LED, LOW);  //If the logger not running, the LED off
  }
}

/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);       //Read the button state
  if (last != current)                         //If it's different…
  {
    delay(5);                                  //Wait 5ms
    current = digitalRead(BUTTON);             //Read it again
  }
  return current;                              //Return the current value
}
