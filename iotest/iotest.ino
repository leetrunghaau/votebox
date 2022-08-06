#define ss1 25
#define ss2 26
#define btn1 19
#define btn2 21
#define led 23
int trangthai = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(ss1, INPUT);
    pinMode(ss2, INPUT);
    pinMode(btn1, INPUT_PULLDOWN);
    pinMode(btn2, INPUT);
    pinMode(led, OUTPUT);
}
void loop()
{
    Serial.print(" ss1  : ss2 : btn1 : btn2 : ");
    Serial.print(digitalRead(ss1));
    Serial.print(digitalRead(ss2));
    Serial.print(digitalRead(btn1));
    Serial.println(digitalRead(btn2));

    if (trangthai == 0)
    {
        trangthai = 1;
    }
    else
    {
        trangthai = 0;
    }
    digitalWrite(led, trangthai);
    delay(500);
}