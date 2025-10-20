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
  float current = (analogRead(CURRENT_PIN)/bitRange) * inputVoltage;

  // decide if current is within range and print a statement accordingly
  //
  if (current < CURRENT_MIN){

    Serial.printf("Current value[A]: %5.2f\n", current);
    Serial.println("ERROR: Below minimum current");

  } else if(current > CURRENT_MAX){

    Serial.printf("Current value[A]: %5.2f\n", current);
    Serial.println("ERROR: Above maximum current");

  }
  else{

    Serial.printf("Current value[A]: %5.2f\n", current);
    Serial.println("Current is within operational range.");

  }
  return current;
}

// main program
//
void loop() {

  // call our check current function
  //
  checkCurrent();

  // give a 500ms delay
  //
  delay(500);

}
