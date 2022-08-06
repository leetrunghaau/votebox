#include <WiFi.h>
#include <string.h>
#include "EEPROM.h" // address 0 is configured, 1 - 4 is vote number, 5 -> id -> ip -> ssid -> password -> ip
// io var
#define internalButton 0
#define internalLed 2
#define displayLed 26
#define bootButton 25
#define settingButton 24

String sta_ssid = "";
String sta_password = "";
String ipServer = "";
String idBox = "";

// wifi config votebox
String ap_ssid = "vote box config";
String ap_password = "12345679";
WiFiServer server(80);
String header;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
bool configured = false;

char *stringToCharArray(String str)
{
    if (str.length() != 0)
    {
        char *p = const_cast<char *>(str.c_str());
        return p;
    }
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
void apWifi_init()
{

    Serial.print("ap WiFi with ");
    Serial.print(ap_ssid);
    Serial.print(" with password ");
    Serial.print(ap_password);
    Serial.print(" and ip is: ");
    WiFi.softAP(stringToCharArray(ap_ssid), stringToCharArray(ap_password));
    Serial.println(WiFi.softAPIP());
}
void wifi_sta_init()
{
    Serial.print("Connecting to WiFi ");
    Serial.print(sta_ssid);
    Serial.print(" with password ");
    Serial.print(sta_password);
    Serial.print(" and status is: ...");
    WiFi.begin(stringToCharArray(sta_ssid), stringToCharArray(sta_password));
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("done with ip: ");
    Serial.println(WiFi.localIP());
}
void getConfigformEeprom()
{
    if (EEPROM.read(0) == 200)
    {
        int tempaddress = 0;
        configured = true;
        idBox = EEPROM.readString(5);
        tempaddress = 6 + idBox.length();
        sta_ssid = EEPROM.readString(tempaddress);
        tempaddress += sta_ssid.length() + 1;
        sta_password = EEPROM.readString(tempaddress);
        tempaddress += sta_password.length() + 1;
        ipServer = EEPROM.readString(tempaddress);
    }
    else
    {
        configured = true;
    }
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
String getStringFormatUriFormRawString(String rawString, int srcIndex, int dstIndex)
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
void saveConfigFormHeader(String rawvalue)
{

    String tempstr = "";
    for (int i = rawvalue.indexOf("boxconfigappmanual"); i < rawvalue.indexOf("&endvalue=ghend") + 15; i++)
    {
        tempstr += rawvalue[i];
    }
    String id = getStringFormatUriFormRawString(tempstr, tempstr.indexOf("?id") + 4, tempstr.indexOf("&ssid"));
    String ssid = getStringFormatUriFormRawString(tempstr, tempstr.indexOf("&ssid") + 6, tempstr.indexOf("&passwd"));
    String passwd = getStringFormatUriFormRawString(tempstr, tempstr.indexOf("&passwd") + 8, tempstr.indexOf("&ip"));
    String ip = getStringFormatUriFormRawString(tempstr, tempstr.indexOf("&ip") + 4, tempstr.indexOf("&endvalue=ghend"));
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
void ap_getSettingMode()
{
    apWifi_init();
    server.begin();
    for (;;)
    {
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
                            client.println("<!DOCTYPE html><html lang=\"en\">");
                            client.println("<head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title><style>");
                            client.println("header .header {background-color: #fff;height: 45px;}");
                            client.println("header a img {width: 134px;margin-top: 4px;}\n");
                            client.println(".login-page {width: 360px;padding: 8% 0 0;margin: auto;}\n");
                            client.println(".login-page .form .login {margin-top: -31px;margin-bottom: 26px;}\n");
                            client.println(".form {position: relative;z-index: 1;background: #FFFFFF;max-width: 360px;margin: 0 auto 100px;padding: 45px;text-align: center;box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);}");
                            client.println(".form input {font-family: \"Roboto\", sans-serif;outline: 0;background: #f2f2f2;width: 100%;border: 0;margin: 0 0 15px;padding: 15px;box-sizing: border-box;font-size: 14px;}");
                            client.println(".form button {font-family: \"Roboto\", sans-serif;text-transform: uppercase;outline: 0;background-color: #328f8a;background-image: linear-gradient(45deg, #328f8a, #08ac4b);width: 100%;border: 0;padding: 15px;color: #FFFFFF;font-size: 14px;-webkit-transition: all 0.3 ease;transition: all 0.3 ease;cursor: pointer;}");
                            client.println(".form .message {margin: 15px 0 0;color: #b3b3b3;font-size: 12px;}");
                            client.println(".form .message a {color: #4CAF50;text-decoration: none;}\n");
                            client.println(".container {position: relative;z-index: 1;max-width: 300px;margin: 0 auto;}\n");
                            client.println("body {background-color: #328f8a;background-image: linear-gradient(45deg, #328f8a, #08ac4b);font-family: \"Roboto\", sans-serif;-webkit-font-smoothing: antialiased;-moz-osx-font-smoothing: grayscale;}");
                            client.println("</style></head>");
                            client.println("<body><div class=\"login-page\"><div class=\"form\"><div class=\"login\"><div class=\"login-header\"><h3>votes box setting</h3></div></div>");
                            client.println("<form class=\"login-form\" method=\"get\" action=\"boxconfigappmanual\">");
                            client.print("<input type=\"text\" placeholder=\"id\" name=\"id\" value=\"");
                            client.print(idBox);
                            client.print("\"/><input type=\"text\" placeholder=\"SSID\" name=\"ssid\" value=\"");
                            client.print(sta_ssid);
                            client.print("\"/><input type=\"text\" placeholder=\"password\" name=\"passwd\" value=\"");
                            client.print(sta_password);
                            client.print("\"/><input type=\"text\" placeholder=\"IP\" name=\"ip\" value=\"");
                            client.print(ipServer);
                            client.print("\"/>");
                            client.println("<input type=\"hidden\" name=\"endvalue\" value=\"ghend\"><button type=\"submit\">save</button></form>");
                            client.println("</div></div></body></html>");
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
void wifiConfig_init()
{
    eeprom_init();
    getConfigformEeprom();
    if (digitalRead(bootButton) == 0)
    {
        ap_getSettingMode();
    }
    wifi_sta_init();
}
void setup()
{
    io_init();
    wifiConfig_init();
}

void loop()
{
}