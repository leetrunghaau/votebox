#include <WiFi.h>
// io var
#define internalButton 0
#define internalLed 2
#define displayLed 26
#define bootButton 25
#define settingButton 24

// wifi config votebox
const char *ssid = "vote box config";
const char *password = "12345679";
WiFiServer server(80);
String header;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void io_init()
{
    Serial.begin(115200);
    pinMode(internalLed, OUTPUT);
    pinMode(displayLed, OUTPUT);
    pinMode(internalButton, INPUT);
    pinMode(bootButton, INPUT);
    pinMode(settingButton, INPUT);
}
void apWifi_init()
{

    Serial.print("ap WiFi with ");
    Serial.print(ssid);
    Serial.print(" with password ");
    Serial.print(password);
    Serial.print(" and ip is: ");
    WiFi.softAP(ssid, password);
    Serial.println(WiFi.softAPIP());
}
void myStringConvert(String rawvalue)
{

    String tempstr = "";
    String id = "";
    String ssid = "";
    String passwd = "";
    String ip = "";
    for (int i = rawvalue.indexOf("boxconfigappmanual"); i < rawvalue.indexOf("&endvalue=ghend") + 15; i++)
    {
        tempstr += rawvalue[i];
    }
    for (int i = tempstr.indexOf("?id") + 4; i < tempstr.indexOf("&ssid"); i++)
    {
        id += tempstr[i];
    }
    for (int i = tempstr.indexOf("&ssid") + 6; i < tempstr.indexOf("&passwd"); i++)
    {
        ssid += tempstr[i];
    }
    for (int i = tempstr.indexOf("&passwd") + 8; i < tempstr.indexOf("&ip"); i++)
    {
        passwd += tempstr[i];
    }
    for (int i = tempstr.indexOf("&ip") + 4; i < tempstr.indexOf("&endvalue=ghend"); i++)
    {
        ip += tempstr[i];
    }
    Serial.print("id is: ");
    Serial.println(id);
    Serial.print("ssid is: ");
    Serial.println(ssid);
    Serial.print("passwd is: ");
    Serial.println(passwd);
    Serial.print("ip is: ");
    Serial.println(ip);
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
            { // loop while the client's connected
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
                            myStringConvert(header);

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
                            client.println("<form class=\"login-form\" method=\"get\" action=\"boxconfigappmanual\"><input type=\"text\" placeholder=\"id\" name=\"id\"/><input type=\"text\" placeholder=\"SSID\" name=\"ssid\"/><input type=\"password\" placeholder=\"password\" name=\"passwd\"/><input type=\"text\" placeholder=\"IP\" name=\"ip\"/><input type=\"hidden\" name=\"endvalue\" value=\"ghend\"><button type=\"submit\">save</button></form>");
                            client.println("</div></div></body></html>");
                            client.println();
                            // Break out of the while loop
                            break;
                        }
                        else
                        { // if you got a newline, then clear currentLine
                            currentLine = "";
                        }
                    }
                    else if (c != '\r')
                    {                     // if you got anything else but a carriage return character,
                        currentLine += c; // add it to the end of the currentLine
                    }
                }
            }
            // Clear the header variable
            header = "";
            // Close the connection
            client.stop();
        }
    }
}

void setup()
{

    io_init();
    Serial.println(ssid);
    if (digitalRead(bootButton) == 0)
    {
        ap_getSettingMode();
    }
}

void loop()
{
    Serial.println("loooooooooooop");
    delay(500);
}