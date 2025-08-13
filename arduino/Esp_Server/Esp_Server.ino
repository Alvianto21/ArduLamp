// Library
#include <ESP8266WiFi.h>
#include "connection.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

 // Global variable
 static bool wait = false;
int statusCode;
String body;

// ToDo tes koneksi internet
void internet() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting to WiFi ");
  Serial.println(SSId);
  WiFi.begin(SSId, Password);

  // Attemps to connect
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("WiFi connected.");
  Serial.println(WiFi.localIP());
}

// ToDo tes koneksi server, gunakan fetch atau yang lain
void connApi() {
  // Setup WiFiClient and HTTPClient instance
  WiFiClient client;
  HTTPClient http;

  // Set HTTP connection
  http.begin(client, host, port, recource);

  // Request HTTP GET
  statusCode = http.GET();

  // Print HTTP Status Code and save response body
  Serial.println(statusCode);
  body = http.getString();

  // HTTP code will be negative on error
  if (statusCode > 0) {
    if (statusCode == HTTP_CODE_OK) {
      // ToDo kirim data ke Arduino
      Serial.println(body);
    }
  } else {
    Serial.println(http.errorToString(statusCode));
  }

  // Close server connection
  http.end();
  body = "";
  wait = true;
}

void setup() {
  // put your setup code here, to run once:
  // ToDo tes komunikasi
  Serial.begin(9600);

  // Connec to WiFi
  internet();
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (wait) {
    delay(1000);
    wait = false;
  } else {
    connApi();
  }
}
