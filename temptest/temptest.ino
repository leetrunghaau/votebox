#include <string.h>
char *stringToCharArray(String str)
{
    if (str.length() != 0)
    {
        char *p = const_cast<char *>(str.c_str());
        return p;
    }
}

String getStringFormatUriFormRawString(String rawString, int srcIndex, int dstIndex){
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
            i+=3;
        }
        else
        {
            resString += rawString[i];
            i++;
        }
    }
    return resString;
}
void setup()
{
    Serial.begin(115200);
    // String hexstring = "40";
    // uint8_t number = (uint8_t)strtol(hexstring, NULL, 16);
    // Serial.print("value is: ");
    // Serial.println(number);

    // String strss = "this is char array";
    // Serial.print("char array is: ");
    // Serial.println(strss);
    // strss[1] = number;
    // Serial.print("char array convert is: ");
    // Serial.println(strss);

    String stra = "lr%40va%26het%25"; //=lr@va&het%
    // String resString = "";

    // int i = 0;
    // while (i < rawString.length())
    // {
    //     if (rawString[i] == '%')
    //     {
    //         String strQueue = "";
    //         strQueue += rawString[i + 1];
    //         strQueue += rawString[i + 2];
    //         uint8_t tempInt = (uint8_t)strtol(stringToCharArray(strQueue), NULL, 16);
    //         Serial.print("strQueue is: ");
    //         Serial.println(strQueue);
    //         Serial.print("strQueue then char is: ");
    //         //Serial.println(char());

    //         resString += (char)tempInt;
    //         i+=3;
    //     }
    //     else
    //     {
    //         resString += rawString[i];
    //         i++;
    //     }
    // }
    // Serial.print("char array is: ");
    // Serial.println(rawString);
    // Serial.print("char array convert is: ");
    // Serial.println(resString);
    Serial.print("String pre format : ");
    Serial.println(getStringFormatUriFormRawString(stra, 0, stra.length()));
}

void loop()
{
}
