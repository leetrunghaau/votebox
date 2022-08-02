#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#define ss1 4
#define ss2 5
#define led 13
int8_t a, b;
int value = 0;
int sophieu = 0;
int sophieutruocdo = 0;


const char *ssid = "Young Union Office";
const char *password = "Lolamdi!";//Lolamdi!
String myStr;
WiFiClient client;
HTTPClient http;
String serverName = "http://192.168.1.110/getvalue.php?id=thung1&value=";

void setup()
{
    pinMode(ss1, INPUT_PULLUP);
    pinMode(ss2, INPUT_PULLUP);
    pinMode(led , OUTPUT);
      digitalWrite(led ,LOW);
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
      digitalWrite(led ,HIGH);
}
int putData()
{

    myStr = String(sophieu);
    String serverPath = serverName + myStr;
    http.begin(client, serverPath.c_str());
    int temp = http.GET();
    http.end();
    return temp;
}

void loop()
{

    a = digitalRead(ss1);
    b = digitalRead(ss2);
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
        sophieu++;
        value = 0;
          digitalWrite(led ,0);
        while (putData() != 200);
    }
      digitalWrite(led ,HIGH);
    Serial.println(sophieu); 
 }
