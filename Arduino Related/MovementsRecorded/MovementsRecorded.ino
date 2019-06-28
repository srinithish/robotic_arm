 /*
  testBraccio90.ino

 testBraccio90 is a setup sketch to check the alignment of all the servo motors
 This is the first sketch you need to run on Braccio
 When you start this sketch Braccio will be positioned perpendicular to the base
 If you can't see the Braccio in this exact position you need to reallign the servo motors position

 Created on 18 Nov 2015
 by Andrea Martino

 This example is in the public domain.
 */

#include <Braccio.h>
#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;





void setup() {  
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Braccio.begin();
//  delay(2000);
  





}

void loop() {
  /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed. 0,60
  */
  
  // the arm is aligned upwards  and the gripper is closed
                     //(step delay, M1, M2, M3, M4, M5, M6);
//  Braccio.ServoMovement(20,0, 28, 0, 69, 0,  20);  


 makeMovements();
 
}

void servoMovementWrapper(float M1,float M2, float M3,float M4,float M5, float M6){


  M2 = 180 - M2; // correction in theta
  
  M2 = M2 + 23; // error in z to bring it to ground
  M4 = M4 + 10; // error in y
  
  Braccio.ServoMovement(20,M1, M2, M3, M4, M5,  M6);  

}


void makeMovements(){
  servoMovementWrapper(0, 82.74, 24.24, 1.02, 0,  20); // reach position
  delay(2000);
  servoMovementWrapper(0, 82.74, 24.24, 1.02, 0,  50); //close
  delay(2000);
  servoMovementWrapper(60, 120, 26.24, 0, 0,  50); //rise up + tilt
  delay(2000);
  servoMovementWrapper(60, 82.74, 26.24, 0, 0,  50); // place below
  delay(2000);
  servoMovementWrapper(60, 82.74, 24.24, 1.02, 0,  20); // release
  delay(2000);
  servoMovementWrapper(60, 82.74, 24.24, 1.02, 0,  50); // release
  delay(2000);
  servoMovementWrapper(60, 120, 26.24, 0, 0,  50); //rise up
  delay(2000);
  servoMovementWrapper(0, 120, 26.24, 0, 0,  50); //tilt back
  delay(2000);
  servoMovementWrapper(0, 82.74, 24.24, 1.02, 0,  50); // reach below
  delay(2000);
  

  
}
