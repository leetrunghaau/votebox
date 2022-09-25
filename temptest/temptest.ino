
#define ss1 26
#define ss2 25
int value = 0;

void hauCount()
{
    int temp = 0;
    Serial.print("poid 11111111111 : ");
    Serial.print(temp);
    if (digitalRead(ss1) == 0 && digitalRead(ss2) == 1) // vote start
    {
        temp++; // =1
        Serial.print("poid 222222222 : ");
        Serial.print(temp);
        for (;;)
        {
            if (digitalRead(ss1) == 0 && digitalRead(ss2) == 0)
            {
                temp++; //=2
                Serial.print("poid 3 : ");
                Serial.print(temp);
                for (;;)
                {
                    if (digitalRead(ss1) == 1 && digitalRead(ss2) == 0)
                    {
                        temp++; //=3
                        Serial.print("poid 4444444 : ");
                        Serial.print(temp);
                        for (;;)
                        {
                            if (digitalRead(ss1) == 1 && digitalRead(ss2) == 1) // done
                            {
                                temp++; //=4 phiếu ++ ; return
                                Serial.print("poid 5555 : ");
                                Serial.print(temp);
                                if (temp == 4)
                                    ;
                                {
                                    Serial.print("doneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee : ");
                                    Serial.println(value++);
                                    // writeVoteToEeprom(getVoteToEeprom() + 1);
                                    return;
                                }

                                break;
                            }
                        }
                    }
                }
            }
            else if (digitalRead(ss1) == 0 && digitalRead(ss2) == 1) // niếu bị lỗi thì cũng releve vòng lặp để đếm số mới
            {
                temp--;
                break;
            }
        }
    }
}
void setup()
{
    Serial.begin(115200);
    pinMode(ss1, INPUT_PULLUP);
    pinMode(ss2, INPUT_PULLUP);
}

void loop()
{
    hauCount();
    Serial.print("sophieu: ");
    Serial.println(value);
}
