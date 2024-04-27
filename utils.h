#pragma once
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define HEADER 0xDEADBEE1

struct config_t
{
  uint32_t header = HEADER;
  char topic[40] = "common";
  uint32_t language = 1;
  uint32_t brightness = 50;
  uint32_t data = 0;
  config_t()
  {
    header = HEADER;
  }
};

void InitConfig();
void SaveConfig(config_t config);
void ConfigPortal();
void setupWiFi();

void HandleConfigData();
time_t GetEpoch();
extern config_t g_config;

class Utils
{
public:
  // Create unique name for clock based on chip id
  static String GetName()
  {
    static String Name = "";
    // First time initialize name
    if (Name == "")
    {
      int id = ESP.getChipId();
      char IdStr[5] = {0};
      for (int i = 0; i < sizeof(IdStr); ++i)
      {
        int seed = (id >> i) % 26;
        IdStr[i] = 'A' + seed;
      }
      IdStr[sizeof(IdStr)] = '\0';
      Name = String(IdStr);
    }
    return Name;
  }

  static time_t GetEpoch()
  {
    WiFiClient client;
    time_t epoch_utc = 0;

    HTTPClient http;
    String url = "http://worldtimeapi.org/api/timezone/Asia/Jerusalem";
    if (!http.begin(client, url))
      return epoch_utc;

    if (http.GET() != HTTP_CODE_OK)
      return epoch_utc;

    String payload = http.getString();
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    epoch_utc = doc["unixtime"].as<uint32_t>() +
                doc["raw_offset"].as<uint32_t>() +
                doc["dst_offset"].as<uint32_t>();

    http.end();

    // time_t time= (time_t)epoch_utc;

    // setTime(epoch_utc);

    return epoch_utc;
  }
};