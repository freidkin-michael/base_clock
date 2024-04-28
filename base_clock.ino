#include <WiFiManager.h>
#include "utils.h"

extern WiFiManager wifiManager;
#include "utils.h"
#include <AsyncTimer.h>
#include <TimeLib.h>

#define CONFIG_PIN D3
time_t epoch_utc = 0;
AsyncTimer update_time;

// Called each second
void HandleTime()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    // Once per minute update epoch from web
    if (second(epoch_utc) == 0)
    {
      epoch_utc = GetEpoch();
      Serial.printf("Update\n");
    }
    else // Otherwise - update epoch seconds manually
    {
      epoch_utc++;
    }
    Serial.printf("%d %d %02d   ", weekday(epoch_utc), day(epoch_utc), month(epoch_utc));
    Serial.printf("%02d:%02d:%02d ", hour(epoch_utc), minute(epoch_utc), second(epoch_utc));
    Serial.printf(" B%d L%d\n", g_config.brightness, g_config.language);
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(CONFIG_PIN, INPUT_PULLUP);

  InitConfig();

  setupWiFi();

  // Initialize time
  epoch_utc = GetEpoch();
  // Setup each second update time handler
  update_time.setInterval(HandleTime, 1000);
}

void loop()
{
  update_time.handle();
  // If config portal is stated - just handle it
  if (wifiManager.getConfigPortalActive())
  {
    wifiManager.process();
  }
  else // If config porial is requested - start if\t
  {
    if (digitalRead(CONFIG_PIN) == LOW)
    {
      wifiManager.setConfigPortalBlocking(false);
      wifiManager.startConfigPortal("Config");
    }
  }
}