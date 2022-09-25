#include <HTTPClient.h>
#include <WiFi.h>
#include <string.h>
#include "EEPROM.h" // address 0 is configured, 1 - 4 is vote number, 5 -> id -> ip -> ssid -> password -> ip

// main config
#define displayLed 23
#define bootButton 19
#define resetButton 21
#define ss1 26
#define ss2 25
HTTPClient http;
// dual coce config
TaskHandle_t voteCounter;
TaskHandle_t voteteSenter;
// sendter config
#include <HTTPClient.h>
String HTTPClientUrlPart = "";
int pevVoteNum = -1;
int sumVoteNum = 0;
int count = 0;
unsigned long pushterTime = millis();
// biến tạm
int stackValue = 0;

// util bog
char *stringToCharArray(String str)
{
    if (str.length() != 0)
    {
        char *p = const_cast<char *>(str.c_str());
        return p;
    }
}
String uriDecode(String rawString, int srcIndex, int dstIndex)
{
    int i = srcIndex;
    String resString = "";
    while (i < dstIndex)
    {
        if (rawString[i] == '%')
        {
            String strQueue = "";
            strQueue += rawString[i + 1];
            strQueue += rawString[i + 2];
            uint8_t tempInt = (uint8_t)strtol(stringToCharArray(strQueue), NULL, 16);
            resString += (char)tempInt;
            i += 3;
        }
        else if (rawString[i] == '+')
        {
            resString += ' ';
            i++;
        }
        else
        {
            resString += rawString[i];
            i++;
        }
    }
    return resString;
}

// wifi bog
void apWifi_init(String ssid, String password)
{

    Serial.print("ap WiFi with ");
    Serial.print(ssid);
    Serial.print(" with password ");
    Serial.print(password);
    Serial.print(" and ip is: ");
    WiFi.softAP(stringToCharArray(ssid), stringToCharArray(password));
    Serial.println(WiFi.softAPIP());
}
void wifi_sta_init(String ssid, String password, uint8_t pinled)
{
    Serial.print("Connecting to WiFi ");
    Serial.print(ssid);
    Serial.print(" with password ");
    Serial.print(password);
    Serial.print(" and status is: ...");
    WiFi.begin(stringToCharArray(ssid), stringToCharArray(password));
    byte ledStatus = LOW;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        ledStatus = !ledStatus;
        digitalWrite(pinled, ledStatus);
    }
    Serial.print("done with ip: ");
    Serial.println(WiFi.localIP());
    digitalWrite(pinled, 0);
}
void saveConfigFormHeader(String uri)
{

    String tempstr = "";
    for (int i = uri.indexOf("boxconfigappmanual"); i < uri.indexOf("&endvalue=ghend") + 15; i++)
    {
        tempstr += uri[i];
    }
    String id = uriDecode(tempstr, tempstr.indexOf("?id") + 4, tempstr.indexOf("&ssid"));
    String ssid = uriDecode(tempstr, tempstr.indexOf("&ssid") + 6, tempstr.indexOf("&passwd"));
    String passwd = uriDecode(tempstr, tempstr.indexOf("&passwd") + 8, tempstr.indexOf("&ip"));
    String ip = uriDecode(tempstr, tempstr.indexOf("&ip") + 4, tempstr.indexOf("&endvalue=ghend"));
    Serial.print("id is: ");
    Serial.println(id);
    Serial.print("ssid is: ");
    Serial.println(ssid);
    Serial.print("passwd is: ");
    Serial.println(passwd);
    Serial.print("ip is: ");
    Serial.println(ip);
    if (id != "" && ssid != "" && passwd != "" && ip != "")
    {
        writeConfigToEeprom(id, ssid, passwd, ip);
        Serial.println("this value save to eeprom done !!!!!!");
    }
    else
    {
        Serial.println("this value do not save to eeprom !!!");
    }
}
void ap_getSettingMode(String ssid, String pass, uint8_t pinled)
{
    WiFiServer server(80);
    String header;
    unsigned long currentTime = millis();
    unsigned long previousTime = 0;
    unsigned long ledTime = millis();
    byte ledStatus = LOW;
    const long timeoutTime = 2000;

    apWifi_init(ssid, pass);
    server.begin();
    for (;;)
    {

        if (millis() - ledTime > 2000)
        {
            ledTime = millis();
            ledStatus = !ledStatus;
            digitalWrite(pinled, ledStatus);
        }

        WiFiClient client = server.available();
        if (client)
        {
            currentTime = millis();
            previousTime = currentTime;
            Serial.println("New Client.");
            String currentLine = "";
            while (client.connected() && currentTime - previousTime <= timeoutTime)
            {
                currentTime = millis();
                if (client.available())
                {
                    char c = client.read();
                    Serial.write(c);
                    header += c;
                    if (c == '\n')
                    {
                        if (currentLine.length() == 0)
                        {
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-type:text/html");
                            client.println("Connection: close");
                            client.println();
                            // xử lý  hearder
                            saveConfigFormHeader(header);

                            // print http to slient
                            client.println("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
                            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                            client.println("<title>vote box</title><style>");
                            client.println("header .header {background-color: #fff;height: 45px;}");
                            client.println("header a img {width: 134px;margin-top: 4px;}");
                            client.println(".login-page {width: 360px;padding: 8% 0 0;margin: auto;}");
                            client.println(".login-page .form .login {margin-top: -31px;margin-bottom: 26px;}");
                            client.println(".form {position: relative;z-index: 1;background: #FFFFFF;max-width: 360px;margin: 0 auto 100px;padding: 45px;text-align: center;box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);}");
                            client.println(".form input {font-family: \"Roboto\", sans-serif;outline: 0;background: #f2f2f2;width: 100%;border: 0;margin: 0 0 15px;padding: 15px;box-sizing: border-box;font-size: 14px;}");
                            client.println(".form button {font-family: \"Roboto\", sans-serif;text-transform: uppercase;outline: 0;background-color: #328f8a;background-image: linear-gradient(45deg, #328f8a, #08ac4b);");
                            client.println("width: 100%;border: 0;padding: 15px;color: #FFFFFF;font-size: 14px;-webkit-transition: all 0.3 ease;transition: all 0.3 ease;cursor: pointer;margin-bottom: 20px;}");
                            client.println(".form .message {margin: 15px 0 0;color: #b3b3b3;font-size: 12px;}");
                            client.println("a {margin: 15px 0 0;color: #4CAF50;text-decoration: none;padding: 20px;}");
                            client.println(".container {position: relative;z-index: 1;max-width: 300px;margin: 0 auto;}  ");
                            client.println("body {background-color: #328f8a;background-image: linear-gradient(45deg, #328f8a, #08ac4b);font-family: \"Roboto\", sans-serif;-webkit-font-smoothing: antialiased;-moz-osx-font-smoothing: grayscale;}");
                            client.println("</style></head>");
                            client.println("<body><div class=\"login-page\"><div class=\"form\"><div class=\"login\"><div class=\"login-header\"><h3>UTE BOX SETTING</h3></div></div>");
                            client.println("<form class=\"login-form\" method=\"get\" action=\"boxconfigappmanual\">");
                            client.println("<p class=\"message\">Mã thùng phiếu</p>");
                            client.print("<input type=\"text\" placeholder=\"id\" name=\"id\" value=\"");
                            client.print(getBoxIdFormEeprom());
                            client.print("\"/>\n<p class=\"message\">Tên wifi</p>");
                            client.print("<input type=\"text\" placeholder=\"SSID\" name=\"ssid\" value=\"");
                            client.print(getSSIDFormEeprom());
                            client.print("\"/>\n<p class=\"message\">Mật khẩu wifi</p>");
                            client.print("<input type=\"text\" placeholder=\"password\" name=\"passwd\" value=\"");
                            client.print(getPassFormEeprom());
                            client.print("\"/>\n<p class=\"message\">Địa chỉ máy chủ</p>");
                            client.print("<input type=\"text\" placeholder=\"IP\" name=\"ip\" value=\"");
                            client.print(getIpFormEeprom());
                            client.println("\"/>\n<input type=\"hidden\" name=\"endvalue\" value=\"ghend\">");
                            client.println("<button type=\"submit\">lưu lại</button>");
                            client.println("<a href=\"#\" style=\"width: 100%; padding: 0%;\">Copyright By <br >Đại học Sư Phạm Kỹ Thuật tpHCM</a></form></div></div></body></html>");
                            client.println("</style></head>");
                            client.print("");
                            client.println();

                            break;
                        }
                        else
                        {
                            currentLine = "";
                        }
                    }
                    else if (c != '\r')
                    {
                        currentLine += c;
                    }
                }
            }

            header = "";

            client.stop();
        }
    }
}
void boxWifi_init(String ssid, String password, uint8_t pinBoot, uint8_t pinLed)
{
    eeprom_init();
    if (digitalRead(pinBoot) == 0)
    {
        ap_getSettingMode(ssid, password, pinLed);
    }
    wifi_sta_init(getSSIDFormEeprom(), getPassFormEeprom(), pinLed);
}

// eeprom bog
void eeprom_init()
{
    Serial.println("\neeprom init\n");
    if (!EEPROM.begin(1000))
    {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
}
bool checkEeprom()
{
    if (EEPROM.read(0) == 200)
    {
        return true;
    }
    else
    {
        return false;
    }
}
String getSSIDFormEeprom()
{
    String id = "";
    if (EEPROM.read(0) == 200)
    {
        int tempaddress = 0;
        id = EEPROM.readString(5);
        tempaddress = 6 + id.length();
        return EEPROM.readString(tempaddress);
    }
    else
    {
        return "null";
    }
}
String getBoxIdFormEeprom()
{
    if (EEPROM.read(0) == 200)
    {
        int tempaddress = 0;
        return EEPROM.readString(5);
    }
    else
    {
        return "null";
    }
}
String getPassFormEeprom()
{
    String id = "";
    String ssid = "";
    if (EEPROM.read(0) == 200)
    {
        int tempaddress = 0;
        id = EEPROM.readString(5);
        tempaddress = 6 + id.length();
        ssid = EEPROM.readString(tempaddress);
        tempaddress += ssid.length() + 1;
        return EEPROM.readString(tempaddress);
    }
    else
    {
        return "null";
    }
}
String getIpFormEeprom()
{
    String id = "";
    String ssid = "";
    String pass = "";
    if (EEPROM.read(0) == 200)
    {
        int tempaddress = 0;
        id = EEPROM.readString(5);
        tempaddress = 6 + id.length();
        ssid = EEPROM.readString(tempaddress);
        tempaddress += ssid.length() + 1;
        pass = EEPROM.readString(tempaddress);
        tempaddress += pass.length() + 1;
        return EEPROM.readString(tempaddress);
    }
    else
    {
        return "null";
    }
}
void writeVoteToEeprom(int voteValue)
{
    EEPROM.writeInt(1, voteValue);
    EEPROM.commit();
}
int getVoteToEeprom()
{
    return EEPROM.readInt(1);
}
void writeConfigToEeprom(String eId, String eSsid, String ePassword, String eIp)
{
    int address = 0;
    EEPROM.write(0, 200);
    EEPROM.writeString(5, eId);
    address = 6 + eId.length();
    EEPROM.writeString(address, eSsid);
    address += eSsid.length() + 1;
    EEPROM.writeString(address, ePassword);
    address += ePassword.length() + 1;
    EEPROM.writeString(address, eIp);
    EEPROM.commit();
}

// sendter bog
void pushter_init()
{
    HTTPClientUrlPart = "http://";
    HTTPClientUrlPart += getIpFormEeprom();
    HTTPClientUrlPart += "/getvalue.php?id=";
    HTTPClientUrlPart += getBoxIdFormEeprom();
    HTTPClientUrlPart += "&value=";
}
void pushValue()
{

    // int voteNum = getVoteToEeprom(); // số phiếu lấy từ eeprom
    int voteNum = sumVoteNum; // số phiếu lấy từ chương trình
    if (voteNum != pevVoteNum)
    {

        if (pushting(voteNum) != 200)
        {
            if (WiFi.status() != WL_CONNECTED)
            {
                WiFi.disconnect();
                WiFi.reconnect();
                digitalWrite(displayLed, 0);
                delay(5000);
                digitalWrite(displayLed, 1);
            }
            else
            {
                byte state = LOW;
                for (uint8_t i = 0; i < 20; i++)
                {
                    state = !state;
                    digitalWrite(displayLed, state);
                    delay(250);
                }
                digitalWrite(displayLed, 1);
            }
        }else{
            pevVoteNum = voteNum;
        }
        // if (pushting(voteNum) == 200)
        // {
        //     pevVoteNum = voteNum;
        // }
    }
}

int pushting(int value)
{
    
    String part = HTTPClientUrlPart;
    part += String(value);
    http.begin(part);
    int httpCode = http.GET();
    http.end();
    delay(500);
    return httpCode;
}

// dual coce bog
void voteFunction(void *pvParameters)
{
    Serial.print("Task1 running on core ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {
        voteCounterFormSS();
        delay(1);
    }
}
void sendFunction(void *pvParameters)
{
    Serial.print("Task2 running on core ");
    Serial.println(xPortGetCoreID());
    digitalWrite(displayLed, 1);
    for (;;)
    {
        pushValue();
    }
}
void dualCore_init()
{
    xTaskCreatePinnedToCore(
        voteFunction, /* Task function. */
        "Task1",      /* name of task. */
        10000,        /* Stack size of task */
        NULL,         /* parameter of the task */
        1,            /* priority of the task */
        &voteCounter, /* Task handle to keep track of created task */
        0);           /* pin task to core 0 */
    delay(500);

    // create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
    xTaskCreatePinnedToCore(
        sendFunction,  /* Task function. */
        "Task2",       /* name of task. */
        10000,         /* Stack size of task */
        NULL,          /* parameter of the task */
        1,             /* priority of the task */
        &voteteSenter, /* Task handle to keep track of created task */
        1);            /* pin task to core 1 */
    delay(500);
}

// counter bog

void voteCounterFormSS()
{
    switch (count)
    {
    case 0:
        if (digitalRead(ss1) == 0)
            count = 1;
        //  Serial.println ("D1");
        break;
    case 1:
        if (digitalRead(ss1) == 1 && digitalRead(ss2) == 0)
            count = 2;
        if (digitalRead(ss1) == 1 && digitalRead(ss2) == 1)
            count = 0;
        // Serial.println ("D2");
        break;
    case 2:
        if (digitalRead(ss2) == 1)
            count = 3;
        // Serial.println ("D3");
        break;
    }
    if (count == 3)
    {
        sumVoteNum++;
        count = 0;
    }
    // Serial.print ("        ");
    Serial.println(sumVoteNum);
}

// main bog
void io_init()
{
    Serial.begin(115200);
    pinMode(bootButton, INPUT);
    pinMode(resetButton, INPUT);
    pinMode(displayLed, OUTPUT);
    pinMode(ss1, INPUT_PULLUP);
    pinMode(ss2, INPUT_PULLUP);
    digitalWrite(displayLed, 0);
}

void setup()
{
    io_init();
    boxWifi_init("UTE BOX", "123456789", bootButton, displayLed);
    pushter_init();
    dualCore_init();
}

void loop()
{
}