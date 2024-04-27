#include <Arduino.h>
#include <EEPROM.h>
#include "utils.h"

config_t g_config;

#define SIZE sizeof(config_t)

void InitConfig()
{
  EEPROM.begin(SIZE);
  config_t tmp;

  EEPROM.get(0, tmp);
  if (tmp.header != HEADER)
  {
    Serial.printf("Init  Data\n");
    EEPROM.put(0, g_config);
    EEPROM.commit(); // для esp8266/esp32
  }
  EEPROM.get(0, g_config);
  Serial.printf("Get data B %d; L %d\n", g_config.brightness, g_config.language);
}

void HandleConfigData()
{
  EEPROM.get(0, g_config);
  g_config.data++;
  Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!");
  Serial.println(g_config.data);
  Serial.println(g_config.brightness);
  EEPROM.put(0, g_config);
  EEPROM.commit();
}

void SaveConfig(config_t config)
{
  g_config = config;
  Serial.printf("Save B %d; L %d\n", g_config.brightness, g_config.language);
  EEPROM.put(0, g_config);
  EEPROM.commit();
//  config_t tmp;
//  EEPROM.get(0, tmp);
//  Serial.printf("Saved data B %d; L %d\n", tmp.brightness, tmp.language);
}