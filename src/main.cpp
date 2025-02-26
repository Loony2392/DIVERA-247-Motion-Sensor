#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <WebSerial.h>
#include <WiFiManager.h> // Hinzufügen der WiFiManager-Bibliothek

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // WiFiManager initialisieren
  WiFiManager wifiManager;
  wifiManager.autoConnect("DIVERA-AP");

  Serial.println("Connected to WiFi");

  WebSerial.begin(&server); // Initialisieren von WebSerial
  WebSerial.msgCallback([](uint8_t *data, size_t len) {
    String msg = "";
    for (size_t i = 0; i < len; i++) {
      msg += char(data[i]);
    }
    Serial.println("Received: " + msg);
    WebSerial.println("Echo: " + msg);
  });

  server.on("/motion", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Motion detected");
  });

  server.begin();
}

void loop() {
  // Motion detection logic
}
