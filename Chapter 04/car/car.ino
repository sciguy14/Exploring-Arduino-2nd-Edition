/*
Exploring Arduino, Second Edition
Code Listing 4-4: Light-Driven Car
https://www.exploringarduino.com/content2/ch4

Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

//Self-Driving Car - Follows Light!

//H-Bridge Pins
const int RIGHT_EN  =9;  //Half Bridge Enable for Right Motor
const int RIGHT_MC1 =2;  //Right Bridge Switch 1 Control
const int RIGHT_MC2 =3;  //Right Bridge Switch 2 Control
const int LEFT_EN   =10; //Half Bridge Enable for Left Motor
const int LEFT_MC1  =4;  //Left Bridge Switch 1 Control
const int LEFT_MC2  =5;  //Left Bridge Switch 2 Control

//Light Sensor Pins
const int LEFT_LIGHT_SENSOR  =0; //Photoresistor on Analog Pin 0
const int RIGHT_LIGHT_SENSOR =1; //Photoresistor on Analog Pin 1

//Movement Thresholds and Speeds
const int LIGHT_THRESHOLD_MIN = 810;  //The min light level reading to cause movement
const int LIGHT_THRESHOLD_MAX = 1100; //The max light level reading to cause movement
const int SPEED_MIN = 150;            //Minimum motor speed
const int SPEED_MAX = 255;            //Maximum motor speed

void setup()
{
    //The H-Bridge Pins are Outputs
    pinMode(RIGHT_EN, OUTPUT);
    pinMode(RIGHT_MC1, OUTPUT);
    pinMode(RIGHT_MC2, OUTPUT);
    pinMode(LEFT_EN, OUTPUT);
    pinMode(LEFT_MC1, OUTPUT);
    pinMode(LEFT_MC2, OUTPUT);

    //Initialize with both motors stopped
    brake("left");
    brake("right");

    //Run a Serial interface for helping to calibrate the light levels.
    Serial.begin(9600);
}

void loop()
{
    //Read the light sensors
    int left_light  = analogRead(LEFT_LIGHT_SENSOR);
    int right_light = analogRead(RIGHT_LIGHT_SENSOR);

    //A small delay of 50ms so the Serial Output is readable
    delay(50);    

    //For each light sensor, set speed of opposite motor proportionally.
    //Below a minimum light threshold, do not turn the opposing motor.
    //Note: Left Sensor controls right motor speed, and vice versa.
    //      To turn left, you need to speed up the right motor.
    Serial.print("Right: ");
    Serial.print(right_light);
    Serial.print(" ");
    if (right_light >= LIGHT_THRESHOLD_MIN)
    {
      //Map light level to speed and constrain it
      int left_speed = map(right_light,
                           LIGHT_THRESHOLD_MIN, LIGHT_THRESHOLD_MAX,
                           SPEED_MIN, SPEED_MAX);
      left_speed = constrain(left_speed, SPEED_MIN, SPEED_MAX);
      Serial.print(left_speed);    //Print the drive speed
      forward("left", left_speed); //Drive opposing motor at computed speed
    }
    else
    {
      Serial.print("0");
      brake("left"); //Brake the opposing motor when light is below the min
    }

    Serial.print("\tLeft: ");
    Serial.print(left_light);
    Serial.print(" ");
    if (left_light >= LIGHT_THRESHOLD_MIN)
    {
      //Map light level to speed and constrain it
      int right_speed = map(left_light,
                            LIGHT_THRESHOLD_MIN, LIGHT_THRESHOLD_MAX,
                            SPEED_MIN, SPEED_MAX);
      right_speed = constrain(right_speed, SPEED_MIN, SPEED_MAX);
      Serial.println(right_speed);   //Print the drive speed
      forward("right", right_speed); //Drive opposing motor at computed speed
    }
    else
    {
      Serial.println("0");
      brake("right"); //Brake the opposing motor when light is below the min
    }
}

//Motor goes forward at given rate (from 0-255)
//Motor can be "left" or "right"
void forward (String motor, int rate)
{
    if(motor == "left")
    {
      digitalWrite(LEFT_EN, LOW);
      digitalWrite(LEFT_MC1, HIGH);
      digitalWrite(LEFT_MC2, LOW);
      analogWrite(LEFT_EN, rate);
    }
    else if(motor == "right")
    {  
      digitalWrite(RIGHT_EN, LOW);
      digitalWrite(RIGHT_MC1, HIGH);
      digitalWrite(RIGHT_MC2, LOW);
      analogWrite(RIGHT_EN, rate);
    }
}

//Stops motor
//Motor can be "left" or "right"
void brake (String motor)
{
    if(motor == "left")
    {
      digitalWrite(LEFT_EN, LOW);
      digitalWrite(LEFT_MC1, LOW);
      digitalWrite(LEFT_MC2, LOW);
      digitalWrite(LEFT_EN, HIGH);
    }
    else if(motor == "right")
    {
      digitalWrite(RIGHT_EN, LOW);
      digitalWrite(RIGHT_MC1, LOW);
      digitalWrite(RIGHT_MC2, LOW);
      digitalWrite(RIGHT_EN, HIGH);
    }
}
