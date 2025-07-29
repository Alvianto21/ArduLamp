// libary
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "connection.h"

// variable declaration

// pins deklaration
const int RelayPin = 8;
const byte rxPin = 10;
const byte txPin = 9;

// setup new SofwareSerial object
SoftwareSerial espSerial(rxPin, txPin);

// send command to ESP
boolean sendCommand(String command, const int timeout, String succResp) {
  String responses = "";
  espSerial.println(command);
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (espSerial.available()) {
      char c = espSerial.read();
      responses += c;
    }

    // Check response
    if (responses.indexOf(succResp) != -1) {
      Serial.println("Found command: " + succResp);
      Serial.println(responses);
      return true;
    }
  }

  // if no response
  Serial.println("Timeout. " + responses + ", " + succResp);
}

// connect to WiFi
void connection() {
  Serial.println("Connecting ....");

  // Check basic communication
  if (sendCommand("AT", 2000, "OK")) {
    Serial.println("Comms online");
  } else {
    Serial.println("failed to connect to ESP");
  }

  // setup to station mode
  if (sendCommand("AT+CWMODE=1", 2000, "OK")) {
    Serial.println("STA mode online");
  } else {
    Serial.println("Failed to change mode");
  }

  // conecting to WiFi
  String cmd = "AT+CWJAP=\"" + String(SSId) + "\",\"" + String(Password) + "\"";
  if (sendCommand(cmd, 2000, "OK")) {
    Serial.println("Connected to WiFi");
  } else {
      Serial.println("Failed to connect");
    }
}

void setup() {
  // put your setup code here, to run once:
  // device deklaration
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(RelayPin, OUTPUT);

  // setup Serial and espSerial
  Serial.begin(9600);
  espSerial.begin(9600);
  Serial.println("Starting");

  //connecting to WiFi
  delay(1000);
  connection();
}

void loop() {
  // put your main code here, to run repeatedly:
 // loop relay
 digitalWrite(RelayPin, LOW);
 delay(100);
 digitalWrite(RelayPin, HIGH);
 delay(5000);
 digitalWrite(RelayPin, LOW);
 delay(5000);
 digitalWrite(RelayPin, HIGH);
 delay(5000);
 digitalWrite(RelayPin, LOW);
 delay(5000);
 digitalWrite(RelayPin, HIGH);
}
