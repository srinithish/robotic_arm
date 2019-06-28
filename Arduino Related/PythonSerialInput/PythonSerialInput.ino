#include "Keyboard.h"

void setup() {
  // open the serial port:
  Serial.begin(9600);
  // initialize control over the keyboard:
  
}

void loop() {
  // check for incoming serial data:

  readSerialTask();
}




void readAndPerformSerialTask(){

    double x , y ,z ;

    
    if (Serial.available() > 0) {
    // read incoming serial data:
    String str = Serial.readString();

      if (str.length() !=0){

          if (str.startsWith("MoveLeft")){
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
            Serial.println(getValue(str, ',', 1));
          }
          
          else if (str.startsWith("POS_WithoutApp")){
            //set global xyz to teh position requested
            Serial.println(getValue(str, ',', 1));
          }
          
          else if (str.startsWith("Release")){
            // with value
            
            Serial.println(getValue(str, ',', 1));
          }

          else if (str.startsWith("Hold")){
            // with value
            //set global xyz to teh position requested
            Serial.println(getValue(str, ',', 1));
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
