#include "functions.h"

// setup all functions and pins
//
void setup() {
  Serial.begin(9600);

  // Current sensor
  //
  pinMode(CURRENT_PIN, INPUT);

  // Encoder
  //
  pinMode(ejectoseato, INPUT_PULLUP);
  pinMode(e4tPinA, INPUT_PULLUP);
  pinMode(e4tPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(e4tPinA), updateEncoderCount, CHANGE);

  // Hall and Photodiode
  //
  pinMode(hallEffectPin, INPUT);
  pinMode(photoPin, INPUT);

  // Servo
  //
  myServo.attach(9);

  Serial.println("System Initialized.");
}

// call all functions
//
void loop() {
  checkCurrent();
  handleEncoder();
  readHallEffect();
  readPhotodiode();
  reportTemp();
  // runServoTest();

  delay(500);
}
