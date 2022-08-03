#include <string.h>

String a = "http://192.168.4.1/boxconfigappmanual?id=thung1&ssid=3dsinhvien&passwd=17151032@@&ip=192.168.50.99&endvalue=ghend";

void myStringConvert(String rawvalue)
{

    String tempstr = "";
    String id = "";
    String ssid = "";
    String passwd = "";
    String ip = "";
    for (int i = rawvalue.indexOf("boxconfigappmanual"); i < rawvalue.indexOf("&endvalue=ghend") + 15; i++)
    {
        tempstr += a[i];
    }
    for (int i = tempstr.indexOf("?id") + 4; i < tempstr.indexOf("&ssid"); i++)
    {
        id += tempstr[i];
    }
    for (int i = tempstr.indexOf("&ssid") + 6; i < tempstr.indexOf("&passwd"); i++)
    {
        if (tempstr[i] == " ")
        {
            ssid += " ";
        }else{
            ssid += tempstr[i];
        }
        
        
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
    Serial.print("ssid is: ");
    Serial.println(passwd);
    Serial.print("ssid is: ");
    Serial.println(ip);
}
void setup()
{
    Serial.begin(115200);
    myStringConvert(a);
}
void loop()
{
}