/*
Exploring Arduino, Second Edition
Code Listing 13-1: Hardware Interrupts for Multitasking
https://www.exploringarduino.com/content2/ch13

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Use a Hardware-Debounced Switch to Control an Interrupt

//Button pins
const int BTN   = 2;  //Output of debounced button on pin 2
const int RED   = 11; //Red Cathode LED on pin 11
const int GREEN = 10; //Green Cathode LED on pin 10
const int BLUE  = 9;  //Blue Cathode LED on pin 9

//Volatile variables can change inside interrupts
volatile int selectedLED = RED;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  //Turn the RGB LED off to start
  //(Inverted because we are controlling the cathode)
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
    
  //The pin is inverted, so we want to look at the rising edge
  attachInterrupt(digitalPinToInterrupt(BTN), swap, RISING);
}

void swap()
{
  //Turn off the current LED (Common Anode, so HIGH is Off)
  digitalWrite(selectedLED, HIGH);
  //Then, choose a new one.
  if (selectedLED == GREEN)
    selectedLED = RED;
  else if (selectedLED == RED)
    selectedLED = BLUE;
  else if (selectedLED == BLUE)
    selectedLED = GREEN;
}

void loop()
{
  //Ramp Brightness Up
  //(Inverted because we are controlling the cathode)
  for (int i=255; i>=0; i--)
  {
    analogWrite(selectedLED, i);
    delay(10);
  }
  //Ramp Brightness Down
  //(Inverted because we are controlling the cathode)
  for (int i=0; i<=255; i++)
  {
    analogWrite(selectedLED, i);
    delay(10);
  }
  delay(1000);
}
