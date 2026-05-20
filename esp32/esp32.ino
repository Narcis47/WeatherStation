// ============================================================
//  WeatherStation — ESP32 + BMP280
//  Reads temperature & pressure and sends data to a backend.
//  Automatically connects to a predefined WiFi or scans for
//  open networks if no credentials are provided.
// ============================================================

#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <HTTPClient.h>

// ── Debug ────────────────────────────────────────────────────
#define DEBUG true
#define LOG(x) if (DEBUG) Serial.println(x)

// ── Sensor ───────────────────────────────────────────────────
Adafruit_BMP280 bmp;
const uint8_t I2C_ADDRESS = 0x76;   // BMP280 I2C address (0x76 or 0x77)

// ── Configuration ────────────────────────────────────────────
const String WIFI_SSID     = "";     // WiFi network name     (leave empty to auto-scan)
const String WIFI_PASSWORD = "";     // WiFi password         (leave empty for open networks)
const String BACKEND_URL   = "";     // Backend endpoint URL  (e.g. http://192.168.1.x:8082/api/data/add)
const String API_KEY       = "";     // Api Key

// ── Timing ───────────────────────────────────────────────────
const int SEND_INTERVAL_MS  = 30000; // Interval between data sends (ms)
const int WIFI_TIMEOUT_STEPS = 20;   // Max attempts when connecting to WiFi


// ============================================================
//  SETUP
// ============================================================
void setup() {
  Serial.begin(115200);
  LOG("=== WeatherStation Starting ===");

  // Initialize BMP280 sensor
  if (!bmp.begin(I2C_ADDRESS)) {
    LOG("[ERROR] BMP280 not found — check wiring or I2C address!");
    while (1) delay(1000);  // Halt if sensor is missing
  }
  LOG("[OK] BMP280 sensor initialized.");

  // Connect to WiFi
  connectToWiFi(WIFI_SSID, WIFI_PASSWORD);
}


// ============================================================
//  LOOP
// ============================================================
void loop() {
  // Reconnect if connection was lost
  if (WiFi.status() != WL_CONNECTED) {
    LOG("[WARN] WiFi connection lost — attempting to reconnect...");
    connectToWiFi(WIFI_SSID, WIFI_PASSWORD);
  }
  // Read sensor data
  float temperature = bmp.readTemperature();
  float pressure    = bmp.readPressure() / 100.0F;  // Convert Pa → hPa
  LOG("──────────────────────────");
  LOG("Temperature : " + String(temperature) + " °C");
  LOG("Pressure    : " + String(pressure)    + " hPa");
  // Send data to backend
  sendData(temperature, pressure, BACKEND_URL);
  delay(SEND_INTERVAL_MS);
}


// ============================================================
//  WIFI — Connect to a predefined network or scan for open ones
// ============================================================
void connectToWiFi(const String& ssid, const String& password) {
  if (!ssid.isEmpty()) {
    LOG("[WiFi] Connecting to: " + ssid);
    WiFi.begin(ssid, password);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < WIFI_TIMEOUT_STEPS) {
      delay(500);
      Serial.print(".");
      attempts++;
    }
    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {
      LOG("[WiFi] Connected! IP: " + WiFi.localIP().toString());
      if (hasInternet()) {
        LOG("[WiFi] Internet access confirmed.");
      } else {
          LOG("[WiFi] Connected but no internet — scanning for open networks...");
          scanAndConnectToOpenWiFi();
      }
    } else {
        LOG("[WiFi] Failed to connect — scanning for open networks...");
        scanAndConnectToOpenWiFi();
    }
  } else {
      LOG("[WiFi] No credentials provided — scanning for open networks...");
      scanAndConnectToOpenWiFi();
  }
}


// ============================================================
//  WIFI — Scan and connect to the first open network found
// ============================================================
void scanAndConnectToOpenWiFi() {
  LOG("[WiFi] Scanning for open networks...");
  int networksFound = WiFi.scanNetworks(false, true);
  LOG("[WiFi] Networks found: " + String(networksFound));

  for (int i = 0; i < networksFound; i++) {
    String networkName = WiFi.SSID(i);
    LOG("[WiFi] Found: " + networkName);

    if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN && !networkName.isEmpty()) {
      LOG("[WiFi] Trying open network: " + networkName);
      WiFi.begin(networkName.c_str(), "");

      int attempts = 0;
      while (WiFi.status() != WL_CONNECTED && attempts < WIFI_TIMEOUT_STEPS) {
        delay(500);
        Serial.print(".");
        attempts++;
      }
      Serial.println();

      if (WiFi.status() == WL_CONNECTED) {
        LOG("[WiFi] Connected to: " + networkName);
        LOG("[WiFi] IP: " + WiFi.localIP().toString());

        if (hasInternet()) {
            LOG("[WiFi] Internet access confirmed.");
            break;  // Stop scanning — we have internet
        } else {
            LOG("[WiFi] No internet on this network, trying next...");
            WiFi.disconnect();
        }
      }
    }
  }
}


// ============================================================
//  INTERNET — Check if the device has internet access
// ============================================================
bool hasInternet() {
  HTTPClient http;
  http.begin("http://www.google.com");
  int code = http.GET();
  http.end();
  return code > 0;
}


// ============================================================
//  HTTP — Send temperature and pressure to the backend
// ============================================================
void sendData(float temp, float pressure, const String& url) {
  if (url.isEmpty()) {
    LOG("[HTTP] Backend URL is not set — skipping data send.");
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    LOG("[HTTP] Not connected to WiFi — cannot send data.");
    return;
  }

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-KEY", API_KEY);

  String body = "{\"temp\":"     + String(temp, 2) + ",\"pressure\":" + String(pressure, 2) + "}";

  LOG("[HTTP] Sending: " + body);
  int code = http.POST(body);

  if (code == 200) {
    LOG("[HTTP] Data sent successfully.");
  } else if (code > 0) {
    LOG("[HTTP] Server responded with error: " + String(code));
  } else {
    LOG("[HTTP] Connection failed. Error: " + String(code));
  }

  http.end();
}
