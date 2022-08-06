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