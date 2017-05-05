#include <IRremote.h>

int RECV_PIN = 6; //code used to be 6, remember!

IRrecv irrecv(RECV_PIN);

decode_results results;

int incomingByte;

const int firePin = 10;

void setup() {
  Serial.begin(115200);
  pinMode(firePin, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  
}

void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'D') {
      digitalWrite(firePin, HIGH);
      delay(3000);
      digitalWrite(firePin, LOW);
      Serial.flush();
    }
  }
  if (irrecv.decode(&results)) {
    //Serial.println(results.value);
    if (results.value == 687050){
      Serial.print('H');
    }
    //Serial.println(results.value);
    //Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}
