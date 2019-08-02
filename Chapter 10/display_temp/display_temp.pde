/*
Exploring Arduino, Second Edition
Code Listing 10-3: Processing Sketch for Displaying Temperature Values
https://www.exploringarduino.com/content2/ch10

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Displays the temperature recorded by an I2C temp sensor

import processing.serial.*;
Serial port;
String temp_c = "";
String temp_f = "";
String data = "";
int index = 0;
PFont font;

void setup()
{
  size(400,400);
  //Change "COM9" to the name of the serial port on your computer
  port = new Serial(this, "COM9", 9600);
  port.bufferUntil('.'); 
  //Change the font name to reflect the name of the font you created
  font = loadFont("AgencyFB-Bold-200.vlw");
  textFont(font, 200);
}

void draw()
{
  background(0,0,0);
  fill(46, 209, 2);
  text(temp_c, 70, 175);
  fill(0, 102, 153);
  text(temp_f, 70, 370);
}
 
void serialEvent (Serial port)
{
  data = port.readStringUntil('.');
  data = data.substring(0, data.length() - 1);
 
  //Look for the comma between Celsius and Fahrenheit
  index = data.indexOf(",");
  // fetch the C Temp
  temp_c = data.substring(0, index);
  //Fetch the F temp
  temp_f = data.substring(index+1, data.length());
}
