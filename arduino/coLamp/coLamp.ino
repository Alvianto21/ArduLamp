// libary
#include <Arduino.h>
// [x] Main goal 2 detik delay

// variable declaration
String lamp;
String baca = "";

// pins deklaration
const int RelayPin = 8;

 // FixMe gunakan AltSoftSerial atau Arduino Serial (pin 0 dan 1, cabut saat upload)

// ToDo ganti bagian ini agar hanya membaca pesan dari ESP dan eksekusinya
void reading() {
  // Read response
  if (Serial.available() > 0) {
    baca = Serial.readStringUntil('\n');

    if (baca.length() > 0) {
      Serial.println("message got: ");
      Serial.println(baca);
    }
  }
 
  // Parsing response
  const String key = "\"status\":\"";
  int val = baca.indexOf(key);
  if (val == -1) return;
  int start = val + key.length();
  int end = baca.indexOf('"', start);
  if (end == -1) end = baca.length();
  lamp = baca.substring(start, end);
  Serial.println(lamp);

  // Reset data
  baca = "";
}

// Lamp main program
void lampControl() {
  // Read massage from ESP
  reading();

  // Lamp control
  if (lamp == "ON") {
    digitalWrite(RelayPin, HIGH);
  }

  if (lamp == "OFF") {
    digitalWrite(RelayPin, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  // device deklaration
  pinMode(RelayPin, OUTPUT);

  // ToDo setup coms for Arduino and ESP
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  lampControl();
}
