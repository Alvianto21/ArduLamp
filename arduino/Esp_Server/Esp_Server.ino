 #include <ESP8266WiFi.h>
 #include "connection.h"
 
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
// ToDo kirim data ke Arduino
void setup() {
  // put your setup code here, to run once:
  // ToDo tes komunikasi
  Serial.begin(115200);

  // Connec to WiFi
  internet();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write("Hello, from ESP \n");
  delay(3000);
}
