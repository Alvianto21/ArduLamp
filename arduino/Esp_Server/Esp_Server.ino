// ToDo tes koneksi internet
// ToDo tes koneksi server, gunakan fetch atau yang lain
// ToDo kirim data ke Arduino
void setup() {
  // put your setup code here, to run once:
  // ToDo tes komunikasi
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write("Hello, from ESP \n");
  delay(3000);
}
