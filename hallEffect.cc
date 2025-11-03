
// change to actual pin later
//
const int hallEffectPin = 1;

// change to actual after testing
//
const int minOn = 200;

bool met = false;

void setup(){
  pinMode(hallEffectPin, INPUT);
}

// set a variable true or false based on if hall effect is met
//
void loop(){

  if(analogRead(photoPin) < minOn){

    met = true;

  } else{

    met = false;

  }

}
