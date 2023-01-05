#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Secrets.h"

#define VCC_SWITCH 2
#define REED_INPUT 3

ADC_MODE(ADC_VCC);

uint32_t getWifiChannel(String ssid)
{
  int networksFound = WiFi.scanNetworks();
  int i;
  for (i = 0; i < networksFound; i++)
  {
    if (ssid == WiFi.SSID(i))
    {
      return WiFi.channel(i);
    }
  }
  return -1;
}

void setupWiFi()
{
  // Serial.println("WiFi Setup...");
  IPAddress local_IP(192, 168, 178, 49);
  IPAddress gateway(192, 168, 178, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(HOSTNAME);

  int channel = getWifiChannel(WIFI_SSID);
  WiFi.begin(WIFI_SSID, PASSWORD, channel, bssid);
  WiFi.persistent(true);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
}

void sendState(int start)  
{
  HTTPClient http;
  String state = digitalRead(REED_INPUT) ? "closed" : "open";
  http.begin(callback + state + "/" + ESP.getVcc() + "/" + (millis() - start));
  http.GET();
  // Serial.println("Sent");
}

void setup()
{
  pinMode(VCC_SWITCH, OUTPUT);
  digitalWrite(VCC_SWITCH, LOW);
  pinMode(REED_INPUT, INPUT_PULLUP);
  // delay(5000);
  long st = millis();
  // Serial.begin(74880);
  
  if (WiFi.SSID() != WIFI_SSID)
  {
    setupWiFi();
  }

  if (WiFi.waitForConnectResult(6000) == WL_CONNECTED)
  {
    sendState(st);
  }
  else 
  {
    // channel changed
    // Serial.println("Could not connect to WiFi ...");
    setupWiFi();
    if (WiFi.waitForConnectResult(6000) == WL_CONNECTED)
    {
      sendState(st);
    }
  }

  digitalWrite(VCC_SWITCH, HIGH);
}

void loop()
{
  // Set GPIO 3 to high should cut VCC anyways
  ESP.deepSleep(10000000);
}