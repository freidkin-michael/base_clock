#include <WiFiManager.h>
#include "utils.h"

WiFiManager wifiManager;
WiFiManagerParameter brightnessField("brightness", "Brightness %", "50", 3);
WiFiManagerParameter languageField("language", "Language", "Eng", 10);

void saveParamCallback()
{
    Serial.printf("\nSave Data: B %d\n", atoi(brightnessField.getValue()));
    config_t config;
    config.brightness = atoi(brightnessField.getValue());
    if (config.brightness < 0 || config.brightness > 100)
    {
        // If value not in the range - revert back value and return
        brightnessField.setValue(String(g_config.brightness).c_str(), 3);
        return;
    }

    config.language = atoi(languageField.getValue());

    brightnessField.setValue(String(g_config.brightness).c_str(), 3);
    languageField.setValue(String(g_config.language).c_str(), 10);
    SaveConfig(config);
}

void setupWiFi()
{
    brightnessField.setValue(String(g_config.brightness).c_str(), 3);
    languageField.setValue(String(g_config.language).c_str(), 10);
    wifiManager.addParameter(&brightnessField);
    wifiManager.addParameter(&languageField);

    wifiManager.setSaveParamsCallback(saveParamCallback);
    wifiManager.setClass("invert");
    wifiManager.autoConnect(("ClockAP_" + Utils::GetName()).c_str());
    Serial.println("Connected");
}
