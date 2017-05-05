
/*
This adds the Websocket support for ESP8266 found here: https://github.com/Links2004/arduinoWebSockets
 */


#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include "config.h"  //--- this is a file to hanle the wifi settings

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

int incomingByte;

void setup() { 
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  
  WiFiMulti.addAP(ssid, pass);

   while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  webSocket.begin("192.168.1.7", 9111); // this needs to be the same IP address and port of the server
  webSocket.onEvent(webSocketEvent);
  
}

void loop() {
  webSocket.loop(); // maintains the Websocket connection
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 'F') {
      webSocket.sendTXT("forward");
    }
    if (incomingByte == 'S') {
      webSocket.sendTXT("stop");
    }
    
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
  
  switch (type) {
    case WStype_DISCONNECTED:
    Serial.println("disconnected");
    webSocket.sendTXT("disconnected");
    break;

    case WStype_CONNECTED:
    Serial.println("connected");
    webSocket.sendTXT("connected");
    break;
    
    case WStype_TEXT:
    Serial.println((char*)payload);
    break;
  }
}

