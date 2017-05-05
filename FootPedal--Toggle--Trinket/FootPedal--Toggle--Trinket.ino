int analogPin = A3;
int change = 0;
int state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogVal = analogRead(analogPin);
  delay(100);

  if (analogVal < 700){
    // get a variable to hold the current state
    state = 1;
    //Serial.print('F');
  }

  else{

    state = 0;
    
    //Serial.print('S');
  }

  // if that state changes, mark it
  if (state != change){
    if (state == 1){
      Serial.print('S');
      delay(100);
    }
    else{
      Serial.print('F');
      delay(100);
    }
  }

  change = state;

  
  
}
