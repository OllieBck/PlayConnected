/*
   WebSocketClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include "config.h"

int incomingByte;

const int switchPin = 5;
const int connectPin = 2;

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

//#define USE_SERIAL Serial1

void setup() {
  pinMode(switchPin, OUTPUT);
  pinMode(connectPin, OUTPUT);
  Serial.begin(115200);

  //Serial.setDebugOutput(true);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP(ssid, pass);

  //WiFi.disconnect();
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  //webSocket.begin("192.168.1.2", 9111);
  webSocket.begin("job271.itp.io", 9111);
  webSocket.onEvent(webSocketEvent);

}

void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'S') {
      digitalWrite(switchPin, HIGH);
      webSocket.sendTXT("Fire");
    }
  }
  webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("[WSc] Disconnected!\n");
      digitalWrite(connectPin, HIGH);
      break;
    case WStype_CONNECTED:
      {
        Serial.print("[WSc] Connected to url: %s\n");
        Serial.println((char*)payload);

        // send message to server when Connected
        webSocket.sendTXT("Huzzah Connected");
      }
      break;
    case WStype_TEXT:
//      Serial.print("received: ");
//      Serial.println((char*)payload);
//      if (strcmp((char*)payload, "tv on") == 0) {
//        digitalWrite(tvPin, HIGH);
//        Serial.print('O');
//      }
//      if (strcmp((char*)payload, "tv off") == 0) {
//        digitalWrite(tvPin, LOW);
//        Serial.print('O');
//      }
//      if (strcmp((char*)payload, "connected") == 0) {
//        digitalWrite(connectPin, LOW);
//      }
//      if (strcmp((char*)payload, "vol up") == 0) {
//        Serial.print('U');
//      }
//       if (strcmp((char*)payload, "vol down") == 0) {
//        Serial.print('D');
//      }
//       if (strcmp((char*)payload, "forward") == 0) {
//        Serial.print('F');
//      }
//       if (strcmp((char*)payload, "back") == 0) {
//        Serial.print('B');
//      }
      
      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary lenght: %u\n", lenght);
      //hexdump(payload, lenght);

      // send data to server
      // webSocket.sendBIN(payload, lenght);
      break;
  }

}
