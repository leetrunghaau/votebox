#include <WiFi.h>
#include <string.h>
#include "EEPROM.h" // address 0 is configured, 1 - 4 is vote number, 5 -> id -> ip -> ssid -> password -> ip
#include "boxeeprom.h"
#include "boxUtil.h"

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
void wifi_sta_init(String ssid, String password)
{
    Serial.print("Connecting to WiFi ");
    Serial.print(ssid);
    Serial.print(" with password ");
    Serial.print(password);
    Serial.print(" and status is: ...");
    WiFi.begin(stringToCharArray(ssid), stringToCharArray(password));
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("done with ip: ");
    Serial.println(WiFi.localIP());
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

        if (millis() - ledTime > 500)
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
                            client.print(getBoxIdFormEeprom());
                            client.print("\"/><input type=\"text\" placeholder=\"SSID\" name=\"ssid\" value=\"");
                            client.print(getSSIDFormEeprom());
                            client.print("\"/><input type=\"text\" placeholder=\"password\" name=\"passwd\" value=\"");
                            client.print(getPassFormEeprom());
                            client.print("\"/><input type=\"text\" placeholder=\"IP\" name=\"ip\" value=\"");
                            client.print(getIpFormEeprom());
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
void boxWifi_init(String ssid, String password, uint8_t pinBoot, uint8_t pinLed)
{
    eeprom_init();
    if (digitalRead(pinBoot) == 0 || checkEeprom() == false)
    {
        ap_getSettingMode(ssid, password,pinLed);
    }
    wifi_sta_init(getSSIDFormEeprom(), getPassFormEeprom());
}
