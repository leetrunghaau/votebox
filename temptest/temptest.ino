#include <string.h>

void setup()
{
    Serial.begin(115200);
    // String hexstring = "40";
    // uint8_t number = (uint8_t)strtol(hexstring, NULL, 16);
    // Serial.print("value is: ");
    // Serial.println(number);

    // String strss = "this is char array";
    // Serial.print("char array is: ");
    // Serial.println(strss);
    // strss[1] = number;
    // Serial.print("char array convert is: ");
    // Serial.println(strss);

    String rawString = "lr%40va%26het%25"; //=lr@va&het%
    String resString = "";

    int i = 0;
    while (i < rawString.length())
    {
        if (rawString[i] == '%')
        {
            String strQueue = "";
            strQueue += rawString[i + 1];
            strQueue += rawString[i + 2];
            //uint8_t tempInt = (uint8_t)strtol(strQueue, NULL, 16);
            Serial.print("strQueue is: ");
            Serial.print(strQueue);
            resString += 'x';
            i+=3;
        }
        else
        {
            resString += rawString[i];
            i++;
        }
    }
    Serial.print("char array is: ");
    Serial.println(rawString);
    Serial.print("char array convert is: ");
    Serial.println(resString);
}

void loop()
{
}
