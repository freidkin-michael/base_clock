#include <WiFiManager.h>
#include "utils.h"

WiFiManager wifiManager;
// Custom HTML for brightness slider and language 
const char *bufferStr = R"(
  <br/>
  <label for='brightness'>Brightness</label>
  <input type="range" min="1" max="255" value="50" name='brightness'> 

  <br/>
  <label for='language'>Language</label>
  <select name="language" id="language" class="button">
  <option value="0" selected>English</option>
  <option value="1">Russian</option>
  <option value="2">Hebrew</option>
  </select>
  )";

WiFiManagerParameter custom_html_inputs(bufferStr);

String getParam(String name)
{
    // read parameter from server, for custom hmtl input
    String value = "Unknown";
    if (wifiManager.server->hasArg(name))
    {
        value = wifiManager.server->arg(name);
    }
    return value;
}
void saveParamCallback()
{
    String language = getParam("language");
    String brightness = getParam("brightness");
    Serial.printf("language: %s\n", language.c_str());
    Serial.printf("brightness: %s\n", brightness.c_str());

    config_t config;
    config.brightness = atoi(brightness.c_str());

    config.language = atoi(language.c_str());

    SaveConfig(config);
}

void setupWiFi()
{
    wifiManager.addParameter(&custom_html_inputs);

    wifiManager.setSaveParamsCallback(saveParamCallback);
    wifiManager.setClass("invert");
    wifiManager.autoConnect(("ClockAP_" + Utils::GetName()).c_str());
    Serial.println("Connected");
}
