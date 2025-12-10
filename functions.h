#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include <Servo.h>

/* ============================================================
   SECTION 1 — CURRENT SENSOR
   ============================================================ */
extern const int CURRENT_PIN;
extern const float CURRENT_MIN;
extern const float CURRENT_MAX;
extern const float inputVoltage;
extern const float bitRange;
extern const float SENSOR_SENSITIVITY;
extern const float ZERO_CURRENT_VOLTAGE;

float checkCurrent();

/* ============================================================
   SECTION 2 — ENCODER READER
   ============================================================ */
extern const int e4tPinA;
extern const int e4tPinB;
extern const int ejectoseato;
extern volatile long encoderCount;

void updateEncoderCount();
void handleEncoder();

/* ============================================================
   SECTION 3 — HALL EFFECT SENSOR
   ============================================================ */
extern const int hallEffectPin;
extern const int hallMinOn;
extern bool hallMet;

void readHallEffect();

/* ============================================================
   SECTION 4 — PHOTODIODE SENSOR
   ============================================================ */
extern const int photoPin;
extern const int minThreshold;
extern bool blocked;

void readPhotodiode();

/* ============================================================
   SECTION 5 — SERVO MOTOR
   ============================================================ */
extern Servo myServo;

void runServoTest();

/* ============================================================
   SECTION 6 — TEMPERATURE SENSOR
   ============================================================ */
extern const int temp_sensor;
extern const float overheatTemp;
extern float currentTemp;
extern bool isOverheated;

float readTemperature();
void reportTemp();

/* ============================================================
   SECTION 7 — H-BRIDGE MOTOR CONTROL
   ============================================================ */

// H-bridge control pins (defined in .cpp)
extern const int motorIn1;
extern const int motorIn2;
extern const int motorPWM;

// Motor direction options
enum MotorDirection {
  FORWARD,
  REVERSE,
  BRAKE
};

// Function prototypes
void initMotor();
void runMotor(MotorDirection dir, int speedValue);

#endif
