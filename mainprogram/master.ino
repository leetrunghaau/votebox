#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>
#define internalButton 0
#define internalLed 2
#define displayLed 26
#define bootButton 25
#define settingButton 24
#define ss1 7
#define ss2 8

TaskHandle_t localWork;
TaskHandle_t internetWork;
HTTPClient http;

// read efrom sta wifi đưa vào biến niếu trống thì bật cờ configured
char *sta_ssid = "3D Sinh vien";
char *sta_password = "17151032@@";
String ipServer = "192.168.50.99";
String idBox = "thung1";


int tempQueue[2] = {0, 0};
int8_t a, b;
int voteNumber = 0;
int reVoteNumber = 0;
int value = 0;
String serverPart = "http://" + ipServer + "/getvalue.php?id=" + idBox + "&value=";
char *ap_ssid = "vote box config";
char *ap_password = "12345679";

bool configured = false;

String htmlTxt = "<!DOCTYPE html><html lang=\"en\">\n" + "<head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title><style>\n" + "header .header {background-color: #fff;height: 45px;}\n" + "header a img {width: 134px;margin-top: 4px;}\n" + ".login-page {width: 360px;padding: 8% 0 0;margin: auto;}\n" + ".login-page .form .login {margin-top: -31px;margin-bottom: 26px;}\n" + ".form {position: relative;z-index: 1;background: #FFFFFF;max-width: 360px;margin: 0 auto 100px;padding: 45px;text-align: center;box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);}\n" + ".form input {font-family: \"Roboto\", sans-serif;outline: 0;background: #f2f2f2;width: 100%;border: 0;margin: 0 0 15px;padding: 15px;box-sizing: border-box;font-size: 14px;}\n" + ".form button {font-family: \"Roboto\", sans-serif;text-transform: uppercase;outline: 0;background-color: #328f8a;background-image: linear-gradient(45deg, #328f8a, #08ac4b);width: 100%;border: 0;padding: 15px;color: #FFFFFF;font-size: 14px;-webkit-transition: all 0.3 ease;transition: all 0.3 ease;cursor: pointer;}\n" + ".form .message {margin: 15px 0 0;color: #b3b3b3;font-size: 12px;}\n" + ".form .message a {color: #4CAF50;text-decoration: none;}\n" + ".container {position: relative;z-index: 1;max-width: 300px;margin: 0 auto;}\n" + "body {background-color: #328f8a;background-image: linear-gradient(45deg, #328f8a, #08ac4b);font-family: \"Roboto\", sans-serif;-webkit-font-smoothing: antialiased;-moz-osx-font-smoothing: grayscale;}\n" + "</style></head>\n" + "<body><div class=\"login-page\"><div class=\"form\"><div class=\"login\"><div class=\"login-header\"><h3>votes box setting</h3></div></div>\n" + "<form class=\"login-form\" method=\"get\" action=\"gethhh\"><input type=\"text\" placeholder=\"id\" name=\"id\"/><input type=\"text\" placeholder=\"SSID\" name=\"ssid\"/><input type=\"password\" placeholder=\"password\" name=\"passwd\"/><input type=\"text\" placeholder=\"IP\" name=\"ip\"/><button type=\"submit\">save</button></form>\n" + "</div></div></body></html>\n";

void ap_getSettingMode()
{
}
void io_init()
{
    Serial.begin(115200);
    pinMode(internalLed, OUTPUT);
    pinMode(displayLed, OUTPUT);
    pinMode(internalButton, INPUT);
    pinMode(bootButton, INPUT);
    pinMode(settingButton, INPUT);
}
void wifi_ap_init()
{
    Serial.print("ap WiFi with ");
    Serial.print(ap_ssid);
    Serial.print(" with password ");
    Serial.print(ap_password);
    Serial.print(" and ip is: ");
    WiFi.softAP(ap_ssid, ap_password);
    Serial.println(WiFi.softAPIP());
}
void wifi_sta_init()
{
    Serial.print("Connecting to WiFi ");
    Serial.print(sta_ssid);
    Serial.print(" with password ");
    Serial.print(sta_password);
    Serial.print(" and status is: ...");
    WiFi.begin(sta_ssid, sta_password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("done with ip: ");
    Serial.println(WiFi.localIP());
}
void voteCounterOfHau()
{
    int UpSideValue = digitalRead(ss1);
    Serial.print(UpSideValue);
    int downSideValue = digitalRead(ss2);
    Serial.print(downSideValue);
    if (UpSideValue == 1 && downSideValue == 1)
    {
        if (tempQueue[0] == 1 && tempQueue[1] == 2)
        {
            voteNumber++;
        }
        else if (tempQueue[0] == 2 && tempQueue[1] == 1)
        {
            voteNumber--;
        }

        tempQueue[0] = 0;
        tempQueue[1] = 0;
    }
    else if (UpSideValue == 1 && downSideValue == 0)
    {
        if (tempQueue[0] == 1 && tempQueue[1] == 0)
        {
            tempQueue[0] = 1;
            tempQueue[1] = 2;
        }
        else if (tempQueue[0] == 0 && tempQueue[1] == 0)
        {
            tempQueue[0] = 0;
            tempQueue[1] = 1;
        }
    }
    else if (UpSideValue == 0 && downSideValue == 1)
    {
        if (tempQueue[0] == 0 && tempQueue[1] == 1)
        {
            tempQueue[0] = 2;
            tempQueue[1] = 1;
        }
        else if (tempQueue[0] == 0 && tempQueue[1] == 0)
        {
            tempQueue[0] = 1;
            tempQueue[1] = 0;
        }
    }
    Serial.println(voteNumber);
}
void voteCounterOfThi()
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
        voteNumber++;
        value = 0;
        digitalWrite(displayLed, 0);
    }
    digitalWrite(displayLed, HIGH);
    Serial.println(voteNumber);
}
int httpSendValue()
{
    http.begin(serverPart + String(voteNumber));
    int httpCode = http.GET();
    http.end();
    return httpCode;
}


void setup()
{
    io_init();
    if (digitalRead(bootButton) == 1 || configured == false)
    {
        ap_getSettingMode();
    }
    wifi_sta_init();

   
}
void loop()
{
}