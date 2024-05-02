#pragma once
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define HEADER 0xDEADBEEF

struct config_t
{
  uint32_t header = HEADER;
  uint32_t language = 0; // English
  uint32_t brightness = 50;
  config_t()
  {
    header = HEADER;
  }
};

String GetName();

void InitConfig();
void SaveConfig(config_t config);

void SetupWiFi();

time_t GetEpoch();

extern config_t g_config;
