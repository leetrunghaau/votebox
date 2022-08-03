#include "EEPROM.h"
char* sta_ssid     = "3D Sinh vien";
void setup()
{
    Serial.begin(115200);
    Serial.println("\nTesting EEPROM Library\n");
    if (!EEPROM.begin(1000))
    {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
    
    Serial.println("commit eeprom done !!!!!");
    String a = "chuoi thu 1";
    String b = "chuoi thu 2";
    EEPROM.writeString(0,a);
    EEPROM.writeString(a.length()+1,sta_ssid);
    EEPROM.commit();
    Serial.print("read value");
    String f = EEPROM.readString(0);
    Serial.println(f);
    Serial.print("read lan 2");
    Serial.println(f.length());
    Serial.println(EEPROM.readString(f.length()+1));

}

void loop()
{
}