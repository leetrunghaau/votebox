#include <HTTPClient.h>
#include "boxeeprom.h"
String HTTPClientUrlPart = "";
String HTTPClientIdBox = "";
String HTTPClientIpServar = "";
void pushValue_init(String url)
{
    HTTPClientUrlPart = "https://";
    HTTPClientUrlPart += HTTPClientIpServar;
    HTTPClientUrlPart += "/getvalue.php?id=";
    HTTPClientUrlPart += HTTPClientIdBox;
    HTTPClientUrlPart += "&value=";
}
int pushValue()
{   
    HTTPClient http;
    String part = HTTPClientUrlPart;
    part += String(getVoteToEeprom());
    http.begin(part);
    int httpCode = http.GET();
    http.end();
    return httpCode;
}
