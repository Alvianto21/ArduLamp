// libary
#include <Arduino.h>

// pins deklaration
const int RelayPin = 8;

void setup() {
  // put your setup code here, to run once:
  // device deklaration
  pinMode(RelayPin, OUTPUT);
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
