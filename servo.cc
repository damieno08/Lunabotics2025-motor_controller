#include <Servo.h>

// create servo object
//
Servo myServo;

void setup() {
  // change to real pin later
  //
  myServo.attach(9); 
}
void loop() {
  // move forward
  //
  myServo.write(180); 
  delay(3000);        

  // stop servo
  //
  myServo.write(90);
  delay(1000);

  // move backward
  //
  myServo.write(0);   
  delay(3000);        

  // stop again
  //
  myServo.write(90);
  delay(2000);        
}
