// Program monitors temperature, starts shutdown process if temperature is too high
//This version basically is checking for safe temps, more physical actions are commented out.


// Defining h-bridge pins and encoder pins - more physical so not used in this version
const int lpwn_pin = 5;      
const int rpwm_pin = 6;      
const int rEnable_pin = 7;  
const int lEnable_pin = 8;  

const int encoderA = 2; 
const int encoderB = 3; 

// Setting A0 to current sensor pin
const int temp_sensor = A0;


// Define encoder count variable - not used in this version
volatile long encoderCount = 0;

// Temperature variables and threshold
const float overheatTemp = 50.0; // Max temperature (TBD)
float currentTemp = 0.0;
bool isOverheated = false; 

// variables for analog conversion
const float bitRange = 1023.0;
const float inputVoltage = 5.0;
const float offsetVoltage = 0.5;
const float scale = 100.0;

//Converts analog value to temp in Celsius - not certain if conversion is correct
float readTemperature() {
  int analogValue = analogRead(temp_sensor);
  float volt = (analogValue * inputVoltage) / bitRange;
  float currentTemp = (volt - offsetVoltage) * scale;
  return currentTemp;
}

void updateEncoderCount() {
  // Encoder code to change count
  // Not used in this version
}

//initalizing system
void setup() {
  Serial.begin(9600);
  
  // Encoder + h-bridge setup - not used in this version
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderA), updateEncoderCount, CHANGE);

  pinMode(lpwn_pin, OUTPUT);
  pinMode(rpwm_pin, OUTPUT);
  pinMode(rEnable_pin, OUTPUT);
  pinMode(lEnable_pin, OUTPUT);

}

// Recurring loop that checks conditions for safe/unsafe temps
void loop() {
  currentTemp = readTemperature();

  if (currentTemp >= overheatTemp) {
    if (!isOverheated) {
      Serial.println("OVERHEAT");
      isOverheated = true;
    }
    // analogWrite(lpwn_pin, 0); digitalWrite(rEnable_pin, LOW); 
    
  } else if (isOverheated) {
    // Checks for safe temp level
    Serial.println("OK");
    isOverheated = false;
    // digitalWrite(rEnable_pin, HIGH);
  }
  
  // noInterrupts(); long count = encoderCount; interrupts();

  // Temp status
  Serial.print(currentTemp);
  
  // Delayed by .5s - overheat status
  if (isOverheated) {
    Serial.println("SHUTDOWN");
  } else {
    Serial.println("OK");
  }
  
  delay(500); 

}
