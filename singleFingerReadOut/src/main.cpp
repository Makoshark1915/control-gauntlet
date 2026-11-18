/*
Author: Joshua Dhaul
Start Date: 16/09/2026
Last edited: 18/11/2026
Desc: this file is inted to be a test file for reciving the input for a single finger (intended for index finger)
takes the input from the 4 pots on the finger and sends it throught the multi plexer (CD74HC4067) outputing the  values to the serial monitor for testing purposes.
the segments of the fingers are counted from the tip of the finger to the base of the finger, so segment 1 is the tip and segment 3 is the base 
segment 3 has an x and y component. whereas all other sements only have an x component.
*/
#include <Arduino.h>
#define PI 3.14159


const byte muxInput = A8; // A8 is the input pin from the multiplexer

const byte muxS0 = 3; // defines pins 3 - 6 as the select pins for the multiplexer
const byte muxS1 = 4;
const byte muxS2 = 5;
const byte muxS3 = 6;

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

  delay(10);// delay to make sure the mux is fully set

  value = analogRead(muxInput); // updates the output variable with the value read from the multiplexer input pin

  return value; // returns the value read from the multiplexer input pin

}

class Index{
  private:
    double segment1Hyp12 = 23.84796;// hypotnuse from swivel point going from the attachment point of the top bar on segment 1 to segment 1 to 2 rotation point
    double segment2Hyp12 = 18.73085;// hypotnuse from swivel point going from the attachment point of the top bar on segment 2 to segment 1 to 2 rotation point
    double segment2Hyp23 = 19.44994;// hypotnuse from swivel point going from the attachment point of the top bar on segment 2 to segment 2 to 3 rotation point
    double segment3Hyp23 = 20.88719;// hypotnuse from swivel point going from the attachment point of the top bar on segment 3 to segment 2 to 3 rotation point
    double segment3Hyp34 = 1;// hypotnuse from swivel point going from the attachment point of the top bar on segment 3 to segment 3 to 4 rotation point
    double segment4Hyp34 = 1;// hypotnuse from swivel point going from the attachment point of the top bar on segment 4 to segment 3 to 4 rotation point


    double segment1Ang12 = 29.755842;// angle formed from the hypotnus segmetn 1, 12 with the direction from the rotation point ofsegment 1 to 2 going along the middle to the next point
    double segment2Ang12 = 46.043019;// angle formed from the hypotnus segmetn 2, 12 with the direction from the rotation point of segment 1 to 2 going along the middle to the next point (2 to 3)
    double segment2Ang23 = 43.887671;// angle formed from the hypotnus segmetn 2, 23 with the direction from the rotation point of segment 2 to 3 going along the middle to the next point
    double segment3Ang23 = 43.559353;// angle formed from the hypotnus segmetn 3, 23 with the direction from the rotation point of segment 1 to 2 going along the middle to the next point 
    double segment3Ang34 = 0;// angle formed from the hypotnus segmetn 3, 34 with the direction from the rotation point of segment 3 to 4 going along the middle to the next point
    double segment4Ang34 = 0;// angle formed from the hypotnus segmetn 4, 34 with the direction from the rotation point of segment 4 to 3 going along the middle to the next point


    double topBar1 = 24.35548;
    double topBar2 = 24.87912;
    double topBar3 = 3;


  public:  
    double angle1Read;
    double angle2Read;
    double angle3Read;
    double rotAngleRead;

    double outputAngle1 = NULL;
    double outputAngle2 = NULL;
    double outputAngle3 = NULL;
    double rotAngle = NULL;

    double Segment1Output(){
      angle1Read = map(muxRead(0), 0, 1023, 0, PI);// updates the read angle from pot and maps it between 0 pi radians
      double segment1Callength = sqrt((2*sq(topBar1))-(2*(2*topBar1)*cos(angle1Read)));// calculates thedistance between the 2 point of rotation

      outputAngle1 = acos((sq(segment1Hyp12)*sq(segment2Hyp12)-sq(segment1Callength))//uses cosine law to calculate the angle between things (hard to explain)
                          /(2*segment1Hyp12*segment2Hyp12));

      outputAngle1 = 360 - outputAngle1 - segment1Ang12 - segment2Ang12;//sets the output angle to the angle of rotation at the joint
    
      return outputAngle1;
    }
    
    double Segment2Output(){
      angle2Read = map(muxRead(1), 0, 1023, 0, PI);// updates the read angle from pot and maps it between 0 pi radians
      double segment2Callength = sqrt((2*sq(topBar2))-(2*(2*topBar2)*cos(angle2Read)));// calculates thedistance between the 2 point of rotation

      outputAngle2 = acos((sq(segment2Hyp23)*sq(segment3Hyp23)-sq(segment2Callength))//uses cosine law to calculate the angle between things (hard to explain)
                          /(2*segment2Hyp23*segment3Hyp23));

      outputAngle2 = 360 - outputAngle2 - segment2Ang23 - segment3Ang23;//sets the output angle to the angle of rotation at the joint
    
      return outputAngle2;
    }

    double Segment3Output(){
      angle3Read = map(muxRead(2), 0, 1023, 0, PI);// updates the read angle from pot and maps it between 0 pi radians
      double segment3Callength = sqrt((2*sq(topBar3))-(2*(2*topBar3)*cos(angle3Read)));// calculates thedistance between the 2 point of rotation

      outputAngle3 = acos((sq(segment3Hyp34)*sq(segment4Hyp34)-sq(segment3Callength))//uses cosine law to calculate the angle between things (hard to explain)
                          /(2*segment3Hyp34*segment4Hyp34));

      outputAngle3 = 360 - outputAngle3 - segment3Ang34 - segment4Ang34;//sets the output angle to the angle of rotation at the joint
    
      return outputAngle3;
    }

    double RotAngleOutput(){
      rotAngleRead = map(muxRead(3), 0, 1023, 0, PI);// updates the read angle from pot and maps it between 0 pi radians
      rotAngle = rotAngleRead;
    
      return rotAngle;
    }
    
};

Index index;

void setup() {
  Serial.begin(9600); // begins serial communication at 9600 baud rate

  pinMode(muxInput, INPUT_PULLUP); // sets all pins to the correct mode for the multiplexer and button
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);
  pinMode(muxS3, OUTPUT);
  
}

void loop() {

Serial.print("segment 1 output: ");  
Serial.print(index.Segment1Output());
Serial.print("  segment 2 output: ");  
Serial.print(index.Segment2Output());
Serial.print("  segment 3 output: ");  
Serial.print(index.Segment3Output());
Serial.print("  rotation angle output: ");  
Serial.println(index.RotAngleOutput());


  
}