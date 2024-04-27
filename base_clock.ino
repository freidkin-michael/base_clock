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
    if (second(epoch_utc) == 0)
    {
      epoch_utc = GetEpoch();
      Serial.printf("Update\n");
    }
    Serial.printf("%d %d %02d   ", weekday(epoch_utc), day(epoch_utc), month(epoch_utc));
    Serial.printf("%02d:%02d:%02d\n", hour(epoch_utc), minute(epoch_utc), second(epoch_utc));
    // Due run each second - update epoch time
    epoch_utc++;
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(CONFIG_PIN, INPUT_PULLUP);

  InitConfig();

  setupWiFi();

  epoch_utc = GetEpoch();
  update_time.setInterval(HandleTime, 1000);
}

void loop()
{
  if (digitalRead(CONFIG_PIN) == LOW)
  {
    ConfigPortal();
    ESP.reset();
  }
  update_time.handle();
}