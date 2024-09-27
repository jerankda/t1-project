#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Wi-Fi settings (replace with your school network credentials)
#define EAP_ANONYMOUS_IDENTITY "YOUR_USERNAME"
#define EAP_IDENTITY "YOUR_USERNAME"
#define EAP_PASSWORD "YOUR_PASSWORD"
const char* ssid = "SSID";
const char* serverURL = "http://<your-server-ip>/data";  // Replace with your server IP

// Pin definitions
#define temperatureSensorPIN 32
#define moistureSensorPIN 34

// OneWire setup
OneWire oneWire(temperatureSensorPIN);
DallasTemperature temperatureSensor(&oneWire);

void setup() {
  Serial.begin(115200);

  // Initialize temperature sensor
  temperatureSensor.begin();

  // Connect to Wi-Fi (Enterprise WPA2)
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();

  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Get temperature data
  temperatureSensor.requestTemperatures();
  float temperature = temperatureSensor.getTempCByIndex(0);

  // Read soil moisture
  int moistureValue = analogRead(moistureSensorPIN);
  int moisturePercentage = map(moistureValue, 0, 4095, 0, 100);

  // Print values to Serial
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Moisture Level: ");
  Serial.print(moisturePercentage);
  Serial.println(" %");

  // Send data to server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"temperature\":";
    payload += temperature;
    payload += ",\"moisture\":";
    payload += moisturePercentage;
    payload += "}";

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Wait for 5 seconds before sending data again
  delay(5000);
}
