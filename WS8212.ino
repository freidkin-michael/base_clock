#include "utils.h"
#include <AsyncTimer.h>
#include <TimeLib.h>

#define CONFIG_PIN D3
time_t epoch_utc = 0;
AsyncTimer update_time;
// Called each second
void HandleTime()
{
  // return;
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.printf("%d %d %02d   ", weekday(epoch_utc), day(epoch_utc), month(epoch_utc));
    Serial.printf("%02d:%02d:%02d\n", hour(epoch_utc), minute(epoch_utc), second(epoch_utc));
    if (second(epoch_utc) == 0)
    {
      epoch_utc = GetEpoch();
      Serial.printf("Update\n");
    }
    epoch_utc++;
    /*
    time_t now = Time::GetEpoch();
    struct tm *timeinfo;
    //time(&now);
    timeinfo = localtime(&now);
    String Hour = String(timeinfo->tm_hour);
    Serial.printf("%s   ", Hour.c_str());
    */
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
  // delay(1000);
  //  HandleConfigData();
  //  uint32_t epoch = Utils::GetEpoch();
  //  Serial.println(epoch);

  //  ESP.reset();
}