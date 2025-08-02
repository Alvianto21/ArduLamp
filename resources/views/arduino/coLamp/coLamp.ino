// libary
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "connection.h"

// variable declaration
String lamp;

// pins deklaration
const int RelayPin = 8;
const byte rxPin = 10;
const byte txPin = 9;

// setup new SofwareSerial object
SoftwareSerial espSerial(rxPin, txPin);

// send command to ESP
bool sendingCommand(const String cmd, const int timeout, String expec = "OK") {
  espSerial.println(cmd);
  String respon = "";
  unsigned long times = millis();
  while (millis() - times < timeout) {
    while (espSerial.available()) {
      char c = espSerial.read();
      respon += c;
      times = millis();
    }
  }
  
  // check response
  if (respon.indexOf(expec) != -1) {
    Serial.println("✓ " + cmd + " → " + expec);
    Serial.println("Pass, continue");
    return true;
  } 
  
  if (respon.indexOf("ERROR") != -1) {
    Serial.println("✗ " + cmd + " → ERROR");
    Serial.println("Failed");
    return false;
  }

  // if no response
  Serial.println("TimeOut");
  return false;
}

// Waiting server
bool waiter(const char* token, unsigned long timeout) {
  unsigned long times = millis() + timeout;
  String buff;
  while (millis() < times) {
    while (espSerial.available()) {
      buff += char(espSerial.read());
      if (buff.indexOf(token) != -1) return true;
    }
  }
  return false;
}

// TCP connection
bool TCPConnect() {
  String cmd2 = "AT+CIPSTART=\"TCP\",\"" + String(host) + "\"," + String(port) + "\r\n";
  if (!sendingCommand(cmd2, 5000)) return false;
  String reg = String("GET ") + rescource + " HTTP/1.1\r\n" + "Host: " + host + ":" + port + "\r\n" + "Connection: close\r\n" + "User-Agent: ESP01\r\n\r\n";
  if (!sendingCommand("AT+CIPSEND=" + String(reg.length()), 2000,">")) return false;
  espSerial.println(reg);
  if (!waiter("SEND OK", 5000)) return false;
  return true;
}

// Read response
void httpRead() {
  unsigned long times = millis() + 5000;
  String resp = "";
  while (millis() < times) {
    if (espSerial.available()) {
      char c = espSerial.read();
      resp += c;
      times = millis() + 1000;
    }
  }
  Serial.println("Response: ");
  Serial.println(resp);

  // find JSON data
  int p = resp.indexOf("+IPD,");
  if (p == -1) return;
  int q = resp.indexOf(':', p);
  if (q == 1) return;

  // Trim data
  String json = resp.substring(q + 1);
  json.trim();
  Serial.println(json);
  
  // Parsing response
  const String key = "\"status\":\"";
  int val = json.indexOf(key);
  if (val == -1) return;
  int start = val + key.length();
  int ending = json.indexOf('"', start);
  if (ending == -1) ending = json.length();
  lamp = json.substring(start, ending);
  Serial.println(lamp);

  // Reset data
  resp = "";
}

// connect to WiFi
void connection() {
  Serial.println("Connecting ....");

  // Check basic communication
  if (sendingCommand("AT", 2000)) {
    Serial.println("Comms online");
  } else {
    Serial.println("failed to connect to ESP");
  }

  // setup to station mode
  if (sendingCommand("AT+CWMODE=1", 2000)) {
    Serial.println("STA mode online");
  } else {
    Serial.println("Failed to change mode");
  }

  // conecting to WiFi
  String cmd = "AT+CWJAP=\"" + String(SSId) + "\",\"" + String(Password) + "\"";
  if (sendingCommand(cmd, 10000)) {
    Serial.println("Connected to WiFi");
  } else {
      Serial.println("Failed to connect");
   }

   // Setup connection
   if (espSerial.println("AT+CIPMUX=0")) {
    Serial.println("Connection setup");
   } else {
    Serial.println("Connection setup failed");
   }
}

// Lamp main program
void lampControl() {
  // initiate TCP connection
  if (TCPConnect()) {
    httpRead();
    // Close TCP
    espSerial.println("AT+CIPCLOSE");

    // control lamp
    if (lamp == "ON") {
      digitalWrite(RelayPin, HIGH);
    }

    if (lamp == "OFF") {
      digitalWrite(RelayPin, LOW);
    }
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
 // loop relay and http request
 lampControl();
 delay(5000);
}
