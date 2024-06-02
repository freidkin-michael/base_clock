#include <WiFiManager.h>
#include <AsyncTimer.h>
#include <TimeLib.h>

#include <GyverMAX7219.h>

#include "utils.h"

#define CONFIG_PIN D3
time_t epoch_utc = 0;
AsyncTimer update_time;
char days[7][10]={"Вс", "Пн", "Вт", "Ср","Чт","Пт","Сб"};

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
    // Serial.printf("%d %d %02d   ", weekday(epoch_utc), day(epoch_utc), month(epoch_utc));
    // Serial.printf("%02d:%02d:%02d ", hour(epoch_utc), minute(epoch_utc), second(epoch_utc));
    // Serial.printf(" B%d L%d\n", g_config.brightness, g_config.language)
    char Time[10], Date[10];
    static int s = 1;
    s = ++s % 2;
    char* wday=days[weekday(epoch_utc)];
    if (s)
      sprintf(Time, "%02d %02d", hour(epoch_utc), minute(epoch_utc));
    else
      sprintf(Time, "%02d:%02d", hour(epoch_utc), minute(epoch_utc));
    sprintf(Date, "%s %02d", wday, day(epoch_utc));

    MatrixPrint(String(Time), String(Date));
//    uint8_t sec = second(epoch_utc)%15;
//    MatrixBrightness(sec);
//    char* day=days[weekday(epoch_utc)];
    Serial.printf("%s %s\n", Time, Date);
  }
}

void setup()
{
  Serial.begin(115200);

  MatrixBegin();

  pinMode(CONFIG_PIN, INPUT_PULLUP);

  InitConfig();

  SetupWiFi();

  // Initialize time
  epoch_utc = GetEpoch();
  // Setup each second update time handler
  update_time.setInterval(HandleTime, 1000);
}

void loop()
{
  // Each second update time handler
  update_time.handle();
  // If config portal started - just handle it
  if (wifiManager.getConfigPortalActive())
  {
    wifiManager.process();
  }
  else // If config porial is requested by config pin - start it
  {
    if (digitalRead(CONFIG_PIN) == LOW)
    {
      wifiManager.setConfigPortalBlocking(false);
      wifiManager.startConfigPortal("Config");
    }
  }
}