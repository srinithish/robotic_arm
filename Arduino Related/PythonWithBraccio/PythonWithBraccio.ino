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

#include <InverseK.h>


///globals//

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

float x , y ,z , approachAngle;
float a0 = 0, a1 = 90 , a2 = 90 , a3 = 90, a4 = 0.0 ,a5 = 20;
bool isSwitchedOn = false;

void setup() {  

  //////////////setup for inverse library////

  // Setup the lengths and rotation limits for each link
  Link base, upperarm, forearm, hand;
  
  base.init(70, b2a(0.0), b2a(180.0));
  upperarm.init(120, b2a(15.0), b2a(165.0));
  forearm.init(120, b2a(0.0), b2a(180.0));
  hand.init(180, b2a(0.0), b2a(180.0));

  // Attach the links to the inverse kinematic model
  InverseK.attach(base, upperarm, forearm, hand);


  //// set up for braccio library
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  
  Braccio.begin();

 
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

  
  readAndPerformSerialTask(); //sets global x y z and there by angles
  


  if (isSwitchedOn == true){
    servoMovementWrapper(a0, a1, a2, a3, a4,  a5);  
  }
  

//  servoMovementWrapper(0, 160, 90, 90, 0,  60);


  
 
}



///////////////////////SUPPORTING FUNCTIONS /////////////////////////////////////////////


/// wrapper for servomovements
void servoMovementWrapper(float M1,float M2, float M3,float M4,float M5, float M6){


    M2 = 180 - M2; // correction in theta
  
  Braccio.ServoMovement(20,M1, M2, M3, M4, M5,  M6);  

}


// Quick conversion from the Braccio angle system to radians 
float b2a(float b){ 
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) { 
  return (a + HALF_PI) * 180 / PI;
}



/// assigns current values to xyz
void readAndPerformSerialTask(){

    

    
    if (Serial.available() > 0) {
    // read incoming serial data:
    String str = Serial.readString();

      if (str.length() !=0){

          if (str.startsWith("Power_On")){
            
            
            isSwitchedOn = true;

            Serial.println("Successful Powered On");
          }

          else if (str.startsWith("Power_Off")){

            a0 = 0, a1 = 90 , a2 = 0 , a3 = 0, a4 =0, a5 = 20;
            servoMovementWrapper(a0, a1, a2, a3, a4,  a5);
            
            isSwitchedOn = false;

            Serial.println("Successful Powered off");
            
          }


           else if (str.startsWith("SetAngles")){
            //set global xyz,approach to teh position requested

            a0 = getValue(str, ',', 1).toFloat();
            a1 = getValue(str, ',', 2).toFloat();
            a2 = getValue(str, ',', 3).toFloat();
            a3 = getValue(str, ',', 4).toFloat();
            a4 = getValue(str, ',', 5).toFloat();
            a5 = getValue(str, ',', 6).toFloat();
            Serial.println("Successful");
          }
          
          else if (str.startsWith("MoveLeft")){
            Serial.println("CalledLeft");
          }
          
          else if (str.startsWith("MoveRight")){
            Serial.println("CalledRight");
          }
          
          else if (str.startsWith("MoveUp")){
            Serial.println("CalledUp");
          }
          
          else if (str.startsWith("MoveDown")){
            Serial.println("CalledDown");
          }
          else if (str.startsWith("POS_WithApp")){
            //set global xyz,approach to teh position requested
            int x1,y1,z1;
            double appAngle;
            x1 = getValue(str, ',', 1).toInt();
            y1 = getValue(str, ',', 2).toInt();
            z1 = getValue(str, ',', 3).toInt();
            appAngle = getValue(str, ',', 4).toDouble();
            setToPositionWithApproach(x1,y1,z1,appAngle);

            
          }
          
          else if (str.startsWith("POS_WithoutApp")){
            //set global xyz to teh position requested
            int x1,y1,z1;

            
            x1 = getValue(str, ',', 1).toInt();
            y1 = getValue(str, ',', 2).toInt();
            z1 = getValue(str, ',', 3).toInt();
            setToPosition(x1,y1,z1);
            
          }
          
          else if (str.startsWith("Release")){
            // with value
            float a5;
            a5 = 60;
          }

          else if (str.startsWith("Hold")){
            // with value
            //set global xyz to teh position requested

            float closeAngle;
            closeAngle = getValue(str, ',', 1).toDouble();
            a5 = closeAngle;
            Serial.println("Successful");

            
          }

          else if (str.startsWith("Get_Position")){

            Serial.println("isSwitchedOn : " + String(isSwitchedOn)+" The current cords are: " + String(x) + ";" + String(y) + ";" + String(z) + 
            " and angles are " + String(a0) + ";" + String(a1) + ";" + String(a2)+ ";" + String(a3)+ ";" + String(a4)+ ";" + String(a5) );
            
          }

          
  }
  }
  
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}



void setToPosition(int x1,int y1,int z1){

  
  float a0_temp, a1_temp, a2_temp, a3_temp;
  
  if(InverseK.solve(x1, y1, z1, a0_temp, a1_temp, a2_temp, a3_temp)) {

    x= x1,y = y1,z = z1;

    a0 = a2b(a0_temp), a1 = a2b(a1_temp), a2 = a2b(a2_temp), a3 = a2b(a3_temp);


    
    Serial.println("Successful and the cords are :" + String(x) + ";" + String(y) + ";" + String(z));

  } else {

    Serial.println("Not possible to acheive and the cords are: " + String(x) + ";" + String(y) + ";" + String(z));
    
  }
}



void setToPositionWithApproach(int x1,int y1,int z1,double appAngle){

  
  float a0_temp, a1_temp, a2_temp, a3_temp;

  if(InverseK.solve(x1, y1, z1, a0_temp, a1_temp, a2_temp, a3_temp, appAngle)) {
    
    x= x1,y = y1,z = z1;

    a0 = a2b(a0_temp), a1 = a2b(a1_temp), a2 = a2b(a2_temp), a3 = a2b(a3_temp);
    approachAngle = appAngle;

    Serial.println("Successful and the cords are :" + String(x) + ";" + String(y) + ";" + String(z) + " With app angle " + String(approachAngle) );
    
  } else {
    
    Serial.println("Not possible to acheive and the cords are: " + String(x) + ";" + String(y) + ";" + String(z));
  }
  

}
