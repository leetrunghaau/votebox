#include <stdio.h>



int main() {
    String a = "http://192.168.4.1/boxconfigappmanual?id=thung1&ssid=3dsinhvien&passwd=17151032@@&ip=192.168.50.99&endvalue=ghend"; 

    String tempstr = "";
    String test = "";
    String test4 = "";
    for (int i = a.indexOf("boxconfigappmanual"); i < a.indexOf("&endvalue=ghend")+15; i++)
    {
        tempstr += a[i];
    }
    Serial.println(tempstr);

    for (int i = tempstr.indexOf("?id") + 4; i < tempstr.indexOf("&ssid"); i++)
    {
        test += tempstr[i];
    }
    for (int i = tempstr.indexOf("&ip") + 4; i < tempstr.indexOf("&endvalue=ghend"); i++)
    {
        test4 += tempstr[i];
    }
    
    
    return 0;
}