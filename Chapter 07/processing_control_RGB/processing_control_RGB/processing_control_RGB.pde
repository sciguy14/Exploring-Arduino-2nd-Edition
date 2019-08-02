/*
Exploring Arduino, Second Edition
Code Listing 7-8: Processing Sketch to Set Arduino RGB Colors
https://www.exploringarduino.com/content2/ch7

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

import processing.serial.*; //Import Serial Library
PImage img;                 //Image Object	
Serial port;                //Serial Port Object

void setup()
{
  size(640,256); //Size of HSV Image
  img = loadImage("hsv.jpg"); //Load in Background Image
  port = new Serial(this, "COM3", 9600); //Open Serial port
  
}

void draw()
{
  background(0);    //Black Background
  image(img,0,0);   //Overlay  image
}

void mousePressed() 
{
  color c = get(mouseX, mouseY); //Get the RGB color where mouse was pressed
  int r = int(map(red(c),   0, 255, 0, 100));
  int g = int(map(green(c), 0, 255, 0, 100));
  int b = int(map(blue(c),  0, 255, 0, 100));
  String colors = r+","+g+","+b+"\n"; //extract values from color
  print(colors); //print colors for debugging
  port.write(colors); //Send values to Arduino
}
