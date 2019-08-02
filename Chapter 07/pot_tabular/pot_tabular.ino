/*
Exploring Arduino, Second Edition
Code Listing 7-2: Tabular Printing using Special Characters
https://www.exploringarduino.com/content2/ch7

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Tabular Serial Printing Test with a Potentiometer

const int POT=0;  //Pot on Analog Pin 0

void setup()
{
  Serial.begin(9600); //Start Serial Port with Baud = 9600
}

void loop()
{
  Serial.println("\nAnalog Pin\tRaw Value\tPercentage");
  Serial.println("------------------------------------------");
  for (int i = 0; i < 10; i++)
  {
    int val = analogRead(POT);           //Read Potentiometer
    int per = map(val, 0, 1023, 0, 100); //Convert to Percentage
  
    Serial.print("A0\t\t");
    Serial.print(val);
    Serial.print("\t\t");     
    Serial.print(per);           //Print Percentage Analog Value
    Serial.println("%");         //Print % Sign and Newline
    delay(1000);                 //Wait 1 second, then repeat
  }  
}

