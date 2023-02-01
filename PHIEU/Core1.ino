
void core_1() {
  switch (count)
  {
    case 0:
      if (digitalRead(ss1) == 0 ) count = 1;
    //  Serial.println ("D1");
      break;
    case 1:
      if (digitalRead(ss1) == 1 && digitalRead(ss2) == 0 ) count = 2;
    if (digitalRead(ss1) == 1 && digitalRead(ss2) == 1 ) count = 0;
      //Serial.println ("D2");
      break;
    case 2:
      if (digitalRead(ss2) == 1)  count = 3;
      //Serial.println ("D3");
      break;
  }
  if (count == 3)
  {
    sophieu++;
    count = 0;

  }
  //Serial.print ("        ");
  //Serial.println (sophieu);
}
