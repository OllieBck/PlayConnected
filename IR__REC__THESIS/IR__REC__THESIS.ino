/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 6; //code used to be 6, remember!

IRrecv irrecv(RECV_PIN);

decode_results results;

int motorPin = 13;

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(motorPin, OUTPUT);
}

void loop() {
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
