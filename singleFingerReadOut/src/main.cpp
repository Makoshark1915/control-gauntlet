/*
Author: Joshua Dhaul
Start Date: 2026-09-16
End Date: NA
Desc: this file is inted to be a test file for reciving the input for a single finger (intended for index finger),
takes the input from the 3 pots on the finger and sends it directly to the arduino side stepping the multiplexer and outputing to the serial monitor for testing purposes.
the segments of the fingers are counted from the tip of the finger to the base of the finger, so segment 1 is the tip and segment 3 is the base.
*/
#include <Arduino.h>


float segments[3];

const byte segment1Pin = A0;
const byte segment2Pin = A1;
const byte segment3Pin = A2;



void setup() {
  Serial.begin(9600);

  pinMode(segment1Pin, INPUT);
  pinMode(segment2Pin, INPUT);
  pinMode(segment3Pin, INPUT);

  
}

void loop() {

  segments[0] = analogRead(segment1Pin);
  segments[1] = analogRead(segment2Pin);
  segments[2] = analogRead(segment3Pin);

  Serial.print("Segment 1: ");
  Serial.print(segments[0]);
  Serial.print("\tSegment 2: ");
  Serial.print(segments[1]);
  Serial.print("\tSegment 3: ");
  Serial.println(segments[2]);

  delay(100);  


}