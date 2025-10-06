const int e4tPinA = 2; // Encoder pins, starting with 2 and 3 for simplicity
const int e4tPinB = 3; // Can change in future when combining projects
const int ejectoseato = 4; // Reset button for testing
volatile long encoderCount = 0;

// Red 5v; Black GND; White D2 (ChA); Green D3 (ChB)
// Pin A detects change
// Pin B detects in which direction

void setup() {
  Serial.begin(9600);
 
  pinMode(ejectoseato, INPUT_PULLUP); // Sets reset pin resistor to high
  pinMode(e4tPinA, INPUT_PULLUP); // Sets PinA resistor to high
  pinMode(e4tPinB, INPUT_PULLUP); // Sets PinB resistor to high

  attachInterrupt(digitalPinToInterrupt(e4tPinA), updateEncoderCount, CHANGE);
  // Watch PinA when it pulses pause and updateEncoderCount
}

void loop() {
  if (digitalRead(ejectoseato) == LOW) {
    noInterrupts(); // Pauses encoder
    encoderCount = 0; // If button is pressed, encoder reads low and resets
    interrupts(); // Unpauses encoder
    Serial.println("Ejecto Seato Cuz!");
    delay(300); // Prevents spam reset
  }

  noInterrupts(); // Pauses encoder
  long count = encoderCount; // Copies to local count
  interrupts(); // Unpauses encoder

  Serial.print("Encoder Count: ");
  Serial.println(count);
  delay(100); // Displays count every 100 miliseconds

}

void updateEncoderCount() {
  bool a = digitalRead(e4tPinA);
  bool b = digitalRead(e4tPinB); // Store values in Pins

  if (a == b) {
    encoderCount++; // If values are alike increase count (foward)
  } else {
    encoderCount--; // If values are different decrease count (Backward)
  }
}
