#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "YOUR_SSID_HERE"; // Replace with your actual WiFi SSID
const char *password = "YOUR_PASSWORD_HERE"; // Replace with your actual WiFi password

int btnPin = 6;
int ledPin = 5;
int ledPin2 = 4;
int btnState = false;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(btnPin, INPUT_PULLDOWN);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);


  int tryDelay = 500;
  int numberOfTries = 20;

  while (true) {

    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL: Serial.println("[WiFi] SSID not found"); break;
      case WL_CONNECT_FAILED:
        Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
        return;
        break;
      case WL_CONNECTION_LOST: Serial.println("[WiFi] Connection was lost"); break;
      case WL_SCAN_COMPLETED:  Serial.println("[WiFi] Scan is completed"); break;
      case WL_DISCONNECTED:    Serial.println("[WiFi] WiFi is disconnected"); break;
      case WL_CONNECTED:
        Serial.println("[WiFi] WiFi is connected!");
        Serial.print("[WiFi] IP address: ");
        Serial.println(WiFi.localIP());
        return;
        break;
      default:
        Serial.print("[WiFi] WiFi Status: ");
        Serial.println(WiFi.status());
        break;

    }
    delay(tryDelay);

    if (numberOfTries <= 0) {
      Serial.print("[WiFi] Failed to connect to WiFi!");
      // Use disconnect function to force stop trying to connect
      WiFi.disconnect();
      return;
    } else {
      numberOfTries--;
    }
  }
}

void loop() {
  btnState = digitalRead(btnPin);

  if (btnState == HIGH) {
    // Disconnect from WiFi
    Serial.println("[WiFi] Disconnecting from WiFi!");
    // This function will disconnect and turn off the WiFi (NVS WiFi data is kept)
    if (WiFi.disconnect(true, false)) {
      Serial.println("[WiFi] Disconnected from WiFi!");
    }
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);

  } else {
    digitalWrite(ledPin, LOW);
    delay(500);
    digitalWrite(ledPin2, HIGH);
  }
}