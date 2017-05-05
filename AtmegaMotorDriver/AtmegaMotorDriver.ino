#include <IRremote.h>

int RECV_PIN = 6; //code used to be 6, remember!

IRrecv irrecv(RECV_PIN);

decode_results results;

int incomingByte;

const int motorPin_1 = 10;
const int motorPin_2 = 9;
const int motorPin_3 = 12;
const int motorPin_4 = 11;

void setup() {
  Serial.begin(115200);
  pinMode(motorPin_1, OUTPUT);
  pinMode(motorPin_2, OUTPUT);
  pinMode(motorPin_3, OUTPUT);
  pinMode(motorPin_4, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  digitalWrite(motorPin_1, LOW);
  digitalWrite(motorPin_3, LOW);
  digitalWrite(motorPin_2, LOW);
  digitalWrite(motorPin_4, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'F') {
      digitalWrite(motorPin_1, HIGH);
      digitalWrite(motorPin_3, HIGH);
      digitalWrite(motorPin_2, LOW);
      digitalWrite(motorPin_4, LOW);
      Serial.flush();
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'B') {
      digitalWrite(motorPin_1, LOW);
      digitalWrite(motorPin_3, LOW);
      digitalWrite(motorPin_2, HIGH);
      digitalWrite(motorPin_4, HIGH);
      Serial.flush();
    }
    if (incomingByte == 'L') {
      digitalWrite(motorPin_1, LOW);
      digitalWrite(motorPin_3, HIGH);
      digitalWrite(motorPin_2, LOW);
      digitalWrite(motorPin_4, LOW);
      Serial.flush();
    }
    if (incomingByte == 'R') {
      digitalWrite(motorPin_1, HIGH);
      digitalWrite(motorPin_3, LOW);
      digitalWrite(motorPin_2, LOW);
      digitalWrite(motorPin_4, LOW);
      Serial.flush();
    }
    if (incomingByte == 'S') {
      digitalWrite(motorPin_1, LOW);
      digitalWrite(motorPin_3, LOW);
      digitalWrite(motorPin_2, LOW);
      digitalWrite(motorPin_4, LOW);
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
