
#define bootButton 0
#define internalLed 2
TaskHandle_t Task1;
TaskHandle_t Task2;
int state = 0;

void readButtonBoot()
{
    if (digitalRead(bootButton) == 0)
    {
        delay(50);
        if (digitalRead(bootButton) == 0)
        {
            while (digitalRead(bootButton) == 0)
                ;
            if (state == 0)
            {
                state = 1;
            }
            else
            {
                state = 0;
            }
        }
    }
}

void Task1code(void *pvParameters)
{
    Serial.print("Task1 running on core ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {
        Serial.print("read value in core:");
        Serial.print(xPortGetCoreID());
        readButtonBoot();
    }
}

// Task2code: blinks an LED every 700 ms
void Task2code(void *pvParameters)
{
    Serial.print("Task2 running on core ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {
        Serial.print("write value in core:");
        Serial.print(xPortGetCoreID());
        digitalWrite(internalLed, state);
    }
}
void setup()
{
    Serial.begin(115200);
    pinMode(bootButton, INPUT);
    pinMode(internalLed, OUTPUT);

    // create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
    xTaskCreatePinnedToCore(
        Task1code, /* Task function. */
        "Task1",   /* name of task. */
        10000,     /* Stack size of task */
        NULL,      /* parameter of the task */
        1,         /* priority of the task */
        &Task1,    /* Task handle to keep track of created task */
        0);        /* pin task to core 0 */
    delay(500);

    // create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
    xTaskCreatePinnedToCore(
        Task2code, /* Task function. */
        "Task2",   /* name of task. */
        10000,     /* Stack size of task */
        NULL,      /* parameter of the task */
        1,         /* priority of the task */
        &Task2,    /* Task handle to keep track of created task */
        1);        /* pin task to core 1 */
    delay(500);
}
void loop()
{   
}