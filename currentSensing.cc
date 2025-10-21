  // Program will measure current input from pin and
  // send the user feedback based on whether it is within range
  //
  
  // A0 is the current sensor pin
  //
  const int CURRENT_PIN = A0;

  // define minimum operation current
  // 
  const float CURRENT_MIN = 1.0;

  // define maximum operation current
  //
  const float CURRENT_MAX = 30.0;

  // define our voltage range
  //
  const float inputVoltage = 5.0;

  // we use value/1023 because the voltage value of the arduino is 10 bits, meaning max value is 1023
  // and minimum value is 0
  const float bitRange = 1023.0;
// set up volts per amp
//
const float SENSOR_SENSITIVITY = 0.185;   // [V/A]

// set up minimum voltage
//
const float ZERO_CURRENT_VOLTAGE = 2.5;   // [V]

// initialize system
//
void setup() {

  // define the current pin as an input
  //
  pinMode(CURRENT_PIN, INPUT);

  // initialize serial communications
  //
  Serial.begin(9600);

}

// function will check if current value is between minimum and maximum
//
float checkCurrent(){
  
  // get numerical value of current
  //
  float sensorVoltage = (analogRead(CURRENT_PIN)/bitRange) * inputVoltage;
  float current = (sensorVoltage - ZERO_CURRENT_VOLTAGE) / SENSOR_SENSITIVITY;

  // decide if current is within range and print a statement accordingly
  //
  
  if (current < CURRENT_MIN){

    Serial.print("Current value[A]: ");
    Serial.println(current,3);
    Serial.println("ERROR: Below minimum current");

  } else if(current > CURRENT_MAX){
    Serial.print("Current value[A]: ");
    Serial.println(current,3);
    Serial.println("ERROR: Above maximum current");

  }
  else{

    Serial.print("Current value[A]: ");
    Serial.println(current,3);
    Serial.println("Current is within operational range.");

  }
  
  return current;
}

// main program
//
void loop() {

  // call our check current function
  //
  float current = checkCurrent();

  // give a 500ms delay
  //
  delay(500);

}
