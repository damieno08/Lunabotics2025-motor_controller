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
