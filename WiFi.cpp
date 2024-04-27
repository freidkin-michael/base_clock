#include <WiFiManager.h>
#include "utils.h"

WiFiManager wifiManager;
WiFiManagerParameter topicField("topic", "MQTT Topic", "fraddy", 40);
WiFiManagerParameter brightnessField("brightness", "Brightness %", "50", 3);
WiFiManagerParameter languageField("language", "Language", "Eng", 10);

void saveParamCallback()
{
    Serial.printf("\nSave Data: B %d\n", atoi(brightnessField.getValue()));
    config_t config;
    config.brightness = atoi(brightnessField.getValue());
    config.language = atoi(languageField.getValue());
    SaveConfig(config);
}

void setupWiFi()
{
    Serial.println("Start autoconnect");
    Serial.printf("Init start B %d; L %d\n", g_config.brightness, g_config.language);
    languageField.setValue(String(g_config.brightness).c_str(), 3);
    languageField.setValue(String(g_config.language).c_str(), 10);
    wifiManager.addParameter(&topicField);
    wifiManager.addParameter(&brightnessField);
    wifiManager.addParameter(&languageField);
    wifiManager.setClass("invert");
    wifiManager.autoConnect(("ClockAP_" + Utils::GetName()).c_str());
    Serial.println("Connected");
    wifiManager.setSaveParamsCallback(saveParamCallback);
}
void ConfigPortal()
{
    Serial.println("Start config");
    Serial.printf("Config \n");
    Serial.println(String(g_config.brightness));
    Serial.println(String(g_config.language));
    brightnessField.setValue(String(g_config.brightness).c_str(), 3);
    languageField.setValue(String(g_config.language).c_str(), 10);
    wifiManager.setConfigPortalBlocking(true);
    wifiManager.startConfigPortal("Config");
}
