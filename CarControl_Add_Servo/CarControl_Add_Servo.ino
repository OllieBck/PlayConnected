/*
  Simple WebSocket client for ArduinoHttpClient library
  Connects to the WebSocket server, and sends a hello
  message every 5 seconds
  note: WiFi SSID and password are stored in config.h file.
  If it is not present, add a new tab, call it "config.h"
  and add the following variables:
  char ssid[] = "ssid";     //  your network SSID (name)
  char pass[] = "password"; // your network password
  created 28 Jun 2016
  by Sandeep Mistry
  this example is in the public domain

  Combines some code from Tom Igoe's Wifi101 example

  Modified by OllieBck 19 November 2016 to work with Websocket Server

*/

#include <SPI.h>
#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include "config.h"
#include <Servo.h>

Servo stringServo;

IPAddress server(159,203,190,133);       // address of the server
int port = 9111; //change back to 9876

WiFiClient wifi;                // instance of the WIFi client library
WebSocketClient client = WebSocketClient(wifi, server, port);

int status = WL_IDLE_STATUS;      // WiFi status

const int connectionLED = 3;      // this LED indicates whether you're connected
const int motorForward = 6;
const int motorBack = 7;
const int motorRight = 9;
const int motorLeft = 8;

const int sendInterval = 100;     // minimum time between messages to the server
const int debounceInterval = 15;  // used to smooth out pushbutton readings
int prevButtonState = 0;          // previous state of the pushbutton
long lastTimeSent = 0;            // timestamp of the last server message

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  // initialize digital inputs and outputs:
  pinMode(connectionLED, OUTPUT);
  pinMode(motorForward, OUTPUT);
  pinMode(motorBack, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  stringServo.attach(4);

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 3 seconds for connection:
    delay(3000);
  }

  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  client.begin();
  while (client.connected()) {
    //Serial.print("connected");
   
    messageRec();

    delay(100);
  }
  Serial.println("disconnected");
  digitalWrite(connectionLED, LOW);
}

void messageRec() {
  // check if a message is available to be received
  int messageSize = client.parseMessage();
  String message;

  if (messageSize > 0) {
    Serial.println("Received a message:");
    String message = client.readString();
    if (message == "connected") {
      digitalWrite(connectionLED, HIGH);
    }
    if (message == "forward") {
      digitalWrite(motorForward, HIGH);
      digitalWrite(motorBack, LOW);
      digitalWrite(motorRight, LOW);
      digitalWrite(motorLeft, LOW);
    }
    if (message == "backward") {
      digitalWrite(motorForward, LOW);
      digitalWrite(motorBack, HIGH);
      digitalWrite(motorRight, LOW);
      digitalWrite(motorLeft, LOW);
    }
    if (message == "stop") {
      digitalWrite(motorForward, LOW);
      digitalWrite(motorBack, LOW);
      digitalWrite(motorRight, LOW);
      digitalWrite(motorLeft, LOW);
    }
    if (message == "right") {
      digitalWrite(motorForward, HIGH);
      digitalWrite(motorRight, HIGH);
      digitalWrite(motorLeft, LOW);
      digitalWrite(motorBack, LOW);
    }
    if (message == "left") {
      digitalWrite(motorForward, HIGH);
      digitalWrite(motorLeft, HIGH);
      digitalWrite(motorRight, LOW);
      digitalWrite(motorBack, LOW);
    }
    if (message == "b_left") {
      digitalWrite(motorForward, LOW);
      digitalWrite(motorLeft, HIGH);
      digitalWrite(motorRight, LOW);
      digitalWrite(motorBack, HIGH);
    }
    if (message == "b_right") {
      digitalWrite(motorForward, LOW);
      digitalWrite(motorLeft, LOW);
      digitalWrite(motorRight, HIGH);
      digitalWrite(motorBack, HIGH);
    }
    if (message == "shoot"){
      stringServo.write(0);
      delay(1000);
      stringServo.write(180);
    }
    Serial.println(message);
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
