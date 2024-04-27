#include <Arduino.h>
String GetName()
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
