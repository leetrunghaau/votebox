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