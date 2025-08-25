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
      Serial.print("message got: ");
      Serial.println(baca);
    }
  }
 
  // Parsing response
  const String key1 = "[lamp/status]";
  const String key2 = "\"status\":\"";
  int val1 = baca.indexOf(key1);
  int val2 = baca.indexOf(key2);
  
  if (val1 != -1) {
    int start = val1 + key1.length();
    int end = baca.indexOf('"', start);
    if (end == -1) end = baca.length();
    lamp = baca.substring(start, end);

    // Trim data
    lamp.trim();

    // Print data
    Serial.print("Lamp: ");
    Serial.println(lamp);

    // check data
    Serial.print("data length= ");
    Serial.println(lamp.length());

    // Print all data
    for (int i = 0; i < lamp.length(); i++) {
      Serial.print(i);
      Serial.print(": ");
      Serial.println((int)lamp[i]);
    }

    // Reset data
    baca = "";
    return;
  }

  if (val2 != -1) {
    int start = val2 + key2.length();
    int end = baca.indexOf('""', start);
    if (end == -1) end = baca.length();
    lamp = baca.substring(start, end);

    // Print data
    Serial.print("Lamp: ");
    Serial.println(lamp);

    // Reset data
    baca = "";
    return;
  }

  // Reset data
  baca = "";
  return;
}

// Lamp main program
void lampControl() {
  // Read massage from ESP
  reading();

  // Lamp control
  if (lamp.equals("ON")) {
    digitalWrite(RelayPin, HIGH);
  }

  if (lamp.equals("OFF")) {
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
