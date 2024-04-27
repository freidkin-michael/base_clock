#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

time_t GetEpoch()
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

    return epoch_utc;
}
