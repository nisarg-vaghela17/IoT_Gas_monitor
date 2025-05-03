#define BLYNK_TEMPLATE_ID "TMPL3YjA5_Lrk"
#define BLYNK_TEMPLATE_NAME "Heart Rate Monitor"
#define BLYNK_AUTH_TOKEN "HFBh__aMVbZKfDZ6hjXX2ZxJrhbmqhls"

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char ssid[] = "Hello";
char pass[] = "qwertyuiop";

PulseOximeter pox;
float bpm, spo2;

#define HR_THRESHOLD 50
#define SPO2_THRESHOLD 92

BlynkTimer timer;

void onBeatDetected() {
  Serial.println("Beat Detected!");
}

void sendData() {
  bpm = pox.getHeartRate();
  spo2 = pox.getSpO2();

  Blynk.virtualWrite(V1, bpm);   // Heart rate to V1
  Blynk.virtualWrite(V2, spo2);  // SpO2 to V2

  if (bpm < HR_THRESHOLD) {
    Blynk.logEvent("low_heart_rate", "Heart rate is too low!");
  }

  if (spo2 < SPO2_THRESHOLD) {
    Blynk.logEvent("low_spo2", "Oxygen level is too low!");
  }

  Serial.print("HR: ");
  Serial.print(bpm);
  Serial.print(" bpm, SpO2: ");
  Serial.print(spo2);
  Serial.println(" %");
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Wire.begin();

  if (!pox.begin()) {
    Serial.println("Failed to initialize pulse oximeter");
    while (1);
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);

  timer.setInterval(1000L, sendData);  // every 1 second
}

void loop() {
  Blynk.run();
  timer.run();
  pox.update();
}