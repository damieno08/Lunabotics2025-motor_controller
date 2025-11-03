
// change to actual pin later
//
const int photoPin = 1;

// change to actual after testing
//
const int minThreshold = 100;

bool blocked = false;

void setup(){
  pinMode(photoPin, INPUT);
}

// set a variable true or false based on if photodiode is blocked
//
void loop(){

  if(analogRead(photoPin) < minThreshold){

    blocked = true;

  } else{

    blocked = false;

  }

}
