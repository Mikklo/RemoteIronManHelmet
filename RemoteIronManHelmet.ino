#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Jarvis";
const char* password = "iamironman";

const char* url1 = "http://192.168.0.1/eyes";
const char* url2 = "http://192.168.0.1/mask";

WiFiClient client;
HTTPClient http;

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (digitalRead(0) == LOW) {
    Serial.println("Button 0 pressed");
    if (WiFi.status() == WL_CONNECTED) {
      if (http.begin(client, url1)) {
        int httpCode = http.GET();
        if (httpCode > 0) {
          String payload = http.getString();
          Serial.println(payload);
        }
        http.end();
      }
    }
    delay(1000);
  }

  if (digitalRead(2) == LOW) {
    Serial.println("Button 2 pressed");
    if (WiFi.status() == WL_CONNECTED) {
      if (http.begin(client, url2)) {
        int httpCode = http.GET();
        if (httpCode > 0) {
          String payload = http.getString();
          Serial.println(payload);
        }
        http.end();
      }
    }
    delay(1000);
  }
}
