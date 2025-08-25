/*
	|This is example of WiFi connection code and API server.
	|Port is your server port
	|Change it to suit your WiFi and enter it into your nain code in ESP-01
*/

#define SSId "Your_SSID"
#define Password "Your_Password"
const char* host = "Your_MQTT_server";
const char* user = "Your_MQTT_username";
const char* pass = "Your_MQTT_password";
const char* client_id = "Your_client_id";
const char* api_host = "Your_API_server";
const int api_port = 8000;
const char* api_route ="Your_API_routes";
const int port = 1883;