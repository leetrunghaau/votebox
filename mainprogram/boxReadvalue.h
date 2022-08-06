#include "boxeeprom.h"
void voteter(uint ss1, uint8_t ss2, uint8_t pinLed)
{
    int value = 0;

    if (digitalRead(ss1) == 1 && digitalRead(ss2) == 1)
    {
        Serial.println("Sang sang");
        delay(0);
    }

    else if (digitalRead(ss1) == 0 && digitalRead(ss2) == 1)
    {
        Serial.println("dem 1");
        delay(0);
        value++;
        while (1)
        {
            Serial.println("dem 1TTTTTTTTTTTTTt");
            if (digitalRead(ss1) == 0 && digitalRead(ss2) == 0)
            {
                Serial.println("dem 2");
                delay(0);
                value++;
                while (1)
                {
                    Serial.println("dem 2TTTTTTTTTTTt");
                    delay(0);
                    if (digitalRead(ss1) == 1 && digitalRead(ss2) == 0)
                    {
                        Serial.println("dem 3");
                        delay(0);
                        value++;
                        while (1)
                        {
                            Serial.println("dem 4");
                            delay(0);
                            if (digitalRead(ss1) == 1 && digitalRead(ss2) == 1)
                            {
                                Serial.println("dem 5");
                                delay(0);
                                value++;
                                goto co1;
                            }
                        }
                    }
                    Serial.println("dem 6");
                    delay(0);
                    if (digitalRead(ss1) == 0 && digitalRead(ss2) == 1)
                    {
                        Serial.println("dem 7");
                        delay(0);
                        value--;
                        while (1)
                        {
                            Serial.println("dem 8");
                            delay(0);
                            if (digitalRead(ss1) == 1 && digitalRead(ss2) == 1)
                            {
                                Serial.println("dem 9");
                                delay(0);
                                value--;
                                goto co1;
                            }
                        }
                    }
                }
            }
        }
    }
co1:
    if (value == 4)
    {
        int tempvote = readVoteToEeprom();
        tempvote++;
        writeVoteToEeprom(tempvote);
        value = 0;
        digitalWrite(pinLed, 0);
    }
    digitalWrite(pinLed, HIGH);
    Serial.println(tempvote);
}