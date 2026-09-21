/*
Author: Joshua Dhaul
Start Date: 2026-09-16
End Date: NA
Desc: this file is inted to be a test file for reciving the input for a single finger (intended for index finger) when a button is pressed.
takes the input from the 3 pots on the finger and sends it throught the multi plexer( CD74HC4067) outputing the  values to the serial monitor for testing purposes.
the segments of the fingers are counted from the tip of the finger to the base of the finger, so segment 1 is the tip and segment 3 is the base.
*/
#include <Arduino.h>


float index[3];

const byte muxInput = A0; // A0 is the input pin from the multiplexer

const byte muxS0 = 3; // defines pins 3 - 6 as the select pins for the multiplexer
const byte muxS1 = 4;
const byte muxS2 = 5;
const byte muxS3 = 6;



const byte buttonPin = 2; // defines pin 2 as the input pin for the button

void setup() {
  Serial.begin(9600); // begins serial communication at 9600 baud rate

  pinMode(muxInput, INPUT_PULLUP); // sets all pins to the correct mode for the multiplexer and button
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);
  pinMode(muxS3, OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);
  
}

void loop() {

  if(digitalRead(buttonPin) == LOW)
  {

  index[0] = muxRead(0); //reads the value from channes 0 - 2 of the multiplexer and stores them in the index array
  index[1] = muxRead(1);
  index[2] = muxRead(2);

  
  Serial.print("index 1: "); // out puts the values of the index array to the serial monitor
  Serial.print(index[0]);
  Serial.print("\tindex 2: ");
  Serial.print(index[1]);
  Serial.print("\tindex 3: ");
  Serial.println(index[2]);

  
  }

}


float muxRead(int channel) { //function to read the value from the multiplexer

  float value = 0; // output value from the function

  int muxChannel[16][4] // defines the values for the select pins for each channel of the multiplexer
  = {
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15

  };

  digitalWrite(muxS0, muxChannel[channel][0]); // sets the select pins for the multiplexer to the values defined in the muxChannel array for the specified channel
  digitalWrite(muxS1, muxChannel[channel][1]);
  digitalWrite(muxS2, muxChannel[channel][2]);
  digitalWrite(muxS3, muxChannel[channel][3]);


  value = analogRead(muxInput); // updates the output variable with the value read from the multiplexer input pin

  return value; // returns the value read from the multiplexer input pin

}