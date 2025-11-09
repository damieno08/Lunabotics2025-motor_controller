// Program monitors temperature, signals shutdown process if temperature is too high

// Setting A0 to current sensor pin
const int temp_sensor = A0;

// Temperature variables and threshold
const float overheatTemp = 50.0; // Max temperature (TBD)
float currentTemp = 0.0;
bool isOverheated = false;

// variables for analog conversion
const float bitRange = 1023.0;
const float inputVoltage = 5.0;
const float offsetVoltage = 0.5;
const float scale = 100.0;

// Function to calculate temperature from analog read
float readTemperature() {
  int analogValue = analogRead(temp_sensor);
  float volt = (analogValue * inputVoltage) / bitRange;
  float cTemp = (volt - offsetVoltage) * scale;
  return cTemp;
}

// Function to report temperature
void reportTemp() {
  currentTemp = readTemperature();

  // Overheat Check 
  if (currentTemp >= overheatTemp) {
    if (!isOverheated) {
      Serial.println("OVERHEAT");
      isOverheated = true;
    }
  } else {
    // OK Temp Check 
    if (isOverheated) {
      Serial.println("OK");
      isOverheated = false;
    }
  }

  // Current status report
  Serial.print("Temp: ");
  Serial.print(currentTemp);
  Serial.print(" °C | Status: ");
  if (isOverheated) {
    Serial.println("OVERHEAT");
  } else {
    Serial.println("OK");
  }
}

// initializing system
void setup() {
  Serial.begin(9600);
}

// Loop that calls the report function w/ delay
void loop() {
  reportTemp();

  delay(500);
}
