#DEFINE 

int pins[] = {2, 3, 4, 5, 6, 7, 8};
int lastState[] = {0, 0, 0, 0, 0, 0, 0};
int currentState[] = {0, 0, 0, 0, 0, 0, 0};

void setup() {
  for(int i = 0; i < pins.length; i++){
    pinMode(pins[i], INPUT_PULLUP);
  }
  
}

void loop() {
  
}

void readPins(){
  lastState = currentState;
}
