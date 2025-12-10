#include <Servo.h>

/* ============================================================
   SECTION 1 — CURRENT SENSOR
   ============================================================ */
const int CURRENT_PIN = A1;
const float CURRENT_MIN = 1.0;
const float CURRENT_MAX = 30.0;
const float inputVoltage = 5.0;
const float bitRange = 1023.0;
const float ZERO_CURRENT_VOLTAGE = 2.58;
const int SENSOR_SENSITIVITY = inputVoltage/105; // volts / A must be somewhere between 66 and 185 according to datasheet

// Note that sensor may need more adjusting at lower currents but works for high current
//
float checkCurrent() {
  float sensorVoltage = (analogRead(CURRENT_PIN) / bitRange) * inputVoltage;
  float current = (ZERO_CURRENT_VOLTAGE - sensorVoltage) / SENSOR_SENSITIVITY;

  Serial.print("Voltage value [V]: ");
  Serial.println(sensorVoltage, 3);
  Serial.print("Current value [A]: ");
  Serial.println(current, 3);

  if (current < CURRENT_MIN) {
    Serial.println("ERROR: Below minimum current");
  } else if (current > CURRENT_MAX) {
    Serial.println("ERROR: Above maximum current");
  } else {
    Serial.println("Current is within operational range.");
  }

  return current;
}

/* ============================================================
   SECTION 2 — ENCODER READER
   ============================================================ */
const int e4tPinA = 2;
const int e4tPinB = 3;
const int ejectoseato = 4;
volatile long encoderCount = 0;

void updateEncoderCount() {
  bool a = digitalRead(e4tPinA);
  bool b = digitalRead(e4tPinB);
  if (a == b) encoderCount++;
  else encoderCount--;
}

void handleEncoder() {
  if (digitalRead(ejectoseato) == LOW) {
    noInterrupts();
    encoderCount = 0;
    interrupts();
    Serial.println("Ejecto Seato Cuz!");
    delay(300);
  }

  noInterrupts();
  long count = encoderCount;
  interrupts();

  Serial.print("Encoder Count: ");
  Serial.println(count);
}

/* ============================================================
   SECTION 3 — HALL EFFECT SENSOR
   ============================================================ */
const int hallEffectPin = 5;   
const int hallMinOn = 200;
bool hallMet = false;

void readHallEffect() {
  int v = analogRead(hallEffectPin);
  hallMet = (v < hallMinOn);

  Serial.print("Hall Effect: ");
  Serial.println(hallMet ? "TRIGGERED" : "NOT TRIGGERED");
}

/* ============================================================
   SECTION 4 — PHOTODIODE SENSOR
   ============================================================ */
const int photoPin = 6;   // changed from pin 1
const int minThreshold = 100;
bool blocked = false;

void readPhotodiode() {
  int v = analogRead(photoPin);
  blocked = (v < minThreshold);

  Serial.print("Photodiode Blocked: ");
  Serial.println(blocked ? "YES" : "NO");
}

/* ============================================================
   SECTION 5 — SERVO MOTOR
   ============================================================ */
Servo myServo;

void runServoTest() {
  myServo.write(180);  
  delay(3000);

  myServo.write(90);
  delay(1000);

  myServo.write(0);
  delay(3000);

  myServo.write(90);
  delay(2000);
}

/* ============================================================
   SECTION 6 — TEMPERATURE SENSOR
   ============================================================ */
const int temp_sensor = A2;
const float overheatTemp = 50.0;
float currentTemp = 0.0;
bool isOverheated = false;
const float TEMP_ZERO_VOLTS = 0.55;
const int TEMP_SENSITIVITY = 100; // volts per degree C according to datasheet

float readTemperature() {
  float volt = (analogRead(temp_sensor) * inputVoltage) / bitRange;
  return (volt - TEMP_ZERO_VOLTS) * TEMP_SENSITIVITY;
}

void reportTemp() {
  currentTemp = readTemperature();

  Serial.print("Temp: ");
  Serial.print(currentTemp);
  Serial.print(" °C | Status: ");

  if (currentTemp >= overheatTemp) {
    if (!isOverheated) Serial.println("OVERHEAT");
    isOverheated = true;
  } else {
    if (isOverheated) Serial.println("OK");
    isOverheated = false;
  }

  Serial.println(isOverheated ? "OVERHEAT" : "OK");
}

/* ============================================================
   SECTION 7 — H-bridge
   ============================================================ */

// ====== H-BRIDGE PINS ======
const int motorIn1 = 10;   // IN1
const int motorIn2 = 11;   // IN2
const int motorPWM = 9;    // ENA / PWM pin

// Motor directions
enum MotorDirection {
  FORWARD,
  REVERSE,
  BRAKE
};

// ====== Initialize Motor Pins ======
void initMotor() {
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorPWM, OUTPUT);

  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorPWM, 0);
}

// ====== Run Motor ======
void runMotor(MotorDirection dir, int speedValue) {
  speedValue = constrain(speedValue, 0, 255);  

  switch (dir) {

    case FORWARD:
      digitalWrite(motorIn1, HIGH);
      digitalWrite(motorIn2, LOW);
      analogWrite(motorPWM, speedValue);
      break;

    case REVERSE:
      digitalWrite(motorIn1, LOW);
      digitalWrite(motorIn2, HIGH);
      analogWrite(motorPWM, speedValue);
      break;

    case BRAKE:
      digitalWrite(motorIn1, LOW);
      digitalWrite(motorIn2, LOW);
      analogWrite(motorPWM, 0);
      break;
  }
}


