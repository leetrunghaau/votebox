#include <WiFi.h>
#include <string.h>
#include "boxwifi.h"
#include "boxReadvalue.h"
#include "boxHTTPClient.h"

#define displayLed 26
#define bootButton 25
#define ss1 23
#define ss2 24
TaskHandle_t Task1;
TaskHandle_t Task2;

void io_init()
{
    Serial.begin(115200);
    pinMode(bootButton, INPUT);
    pinMode(displayLed, OUTPUT);
    digitalWrite(displayLed, 0);
}
// Task1code: blinks an LED every 1000 ms
void Task1code(void *pvParameters)
{
    Serial.print("Task1 running on core ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {
        voteter(ss1, ss2, displayLed);
    }
}

// Task2code: blinks an LED every 700 ms
void Task2code(void *pvParameters)
{
    Serial.print("Task2 running on core ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {

        while (pushValue() != 200)
            ;
    }
}
void setup()
{
    boxWifi_init("UTE BOX", "12345679", bootButton, displayLed);

    xTaskCreatePinnedToCore(
        Task1code,
        "Task1",
        10000,
        NULL,
        1,
        &Task1,
        0);
    delay(500);
    xTaskCreatePinnedToCore(
        Task2code,
        "Task2",
        10000,
        NULL,
        1,
        &Task2,
        1);
    delay(500);
}
void loop()
{
}