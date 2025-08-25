// Library
#include <ESP8266WiFi.h>
#include "connection.h"
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

 // Global variable
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
// Define WiFiClient, MQTT, and HTTPClient object
WiFiClient EspClient;
PubSubClient client(EspClient);
HTTPClient http;

// Get initial data
boolean initialData() {
  // Setup HTTP GET
  http.begin(EspClient, api_host, api_port, api_route);

  // Request HTTP GET
  statusCode = http.GET();

  // Print response
  Serial.println(statusCode);
  body = http.getString();

  if (statusCode > 0) {
    if(statusCode == HTTP_CODE_OK) {
      Serial.println(body);
    }

    // Close server connection and clear data
    http.end();
    return true;
  }

  // Close server connection and clear data
  http.end();
  body = "";
  return false;
}

// read MQTT message
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Recive message [");
  Serial.print(topic);
  Serial.print("] ");

  // Print all message
  for (int i = 0; i < length; i++) {
    body += (char)payload[i];
  }
  Serial.println(body);
  body = "";
}
void ReconnApi() {
  // Loop until reconnect
  while (!client.connected()) {
    Serial.println("Attempt reconnect");
    if (client.connect(client_id)) {
      // resubscribe topic
      client.subscribe("lamp/status");
    } else {
      Serial.println("Reconnect failed, reattempt in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  // ToDo tes komunikasi
  Serial.begin(9600);

  // Connec to WiFi
  internet();
  delay(500);

  while (!initialData()) {
    delay(5000);
  }

  // Connect to MQTT server
  client.setServer(host, port);
  client.setCallback(callback);

  // ToDo gambungkan dengan HTTP 
  if (client.connect(client_id, user, pass)) {
    client.subscribe("lamp/status");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Send inisial data
  if (body.length() != 0) {
    Serial.println(body);
    body = "";
  }
  
  if (!client.connected()) {
    ReconnApi();
  }
  client.loop();
}
