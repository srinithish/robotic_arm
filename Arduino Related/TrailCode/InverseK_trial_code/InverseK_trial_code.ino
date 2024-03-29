// Arduino/Teensy example for Arduino Braccio

// Include the library InverseK.h
#include <InverseK.h>

void setup() {
  // Setup the lengths and rotation limits for each link
  Link base, upperarm, forearm, hand;
  
  base.init(70, b2a(0.0), b2a(180.0));
  upperarm.init(120, b2a(15.0), b2a(165.0));
  forearm.init(120, b2a(0.0), b2a(180.0));
  hand.init(180, b2a(0.0), b2a(180.0));

  // Attach the links to the inverse kinematic model
  InverseK.attach(base, upperarm, forearm, hand);

  float a0, a1, a2, a3;

  // InverseK.solve() return true if it could find a solution and false if not. 
  
  // Calculates the angles without considering a specific approach angle
  // InverseK.solve(x, y, z, a0, a1, a2, a3)


  while (!Serial){
  if(InverseK.solve(0, -60, 60, a0, a1, a2, a3)) {
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
  } else {
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.println(a2b(0));
  }
  
  // Calculates the angles considering a specific approach angle 'phi'
  // InverseK.solve(x, y, z, a0, a1, a2, a3, phi)
  if(InverseK.solve(0, -100, 100, a0, a1, a2, a3, 90.0)) {
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
  } else {
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.println(a2b(0));
  }
}
}
void loop() {
   float a0, a1, a2, a3;
   Serial.println("Without APPROACH");
  if(InverseK.solve(0, -350, 100, a0, a1, a2, a3)) {
    
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
  } else {
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.println(a2b(0));
  }

  Serial.println("With  APPROACH");
   if(InverseK.solve(200, -350, 50, a0, a1, a2, a3, 0)) {
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
  } else {
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.print(a2b(0)); Serial.print(',');
    Serial.println(a2b(0));
  }


  
}

// Quick conversion from the Braccio angle system to radians 
float b2a(float b){ 
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) { 
  return (a + HALF_PI) * 180 / PI;
}
