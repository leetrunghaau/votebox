#include <WiFi.h>
#define bootButton 0
#define internalLed 2
int state = 0;
char* sta_ssid     = "3D Sinh vien";
char* sta_password = "17151032@@";
char* ap_ssid     = "esp32";
char* ap_password = "12345679";

void staWifi_init() {
  Serial.print("Connecting to WiFi ");
  Serial.print(sta_ssid);
  Serial.print(" with password ");
  Serial.print(sta_password);
  Serial.print(" and status is: ...");
  WiFi.begin(sta_ssid, sta_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("done with ip: ");
  Serial.println(WiFi.localIP());

}

void apWifi_init() {

  Serial.print("ap WiFi with ");
  Serial.print(ap_ssid);
  Serial.print(" with password ");
  Serial.print(ap_password);
  Serial.print(" and ip is: ");
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println(WiFi.softAPIP());

}

void readButtonBoot() {
  if (digitalRead(bootButton) == 0) {
    delay(50);
    if (digitalRead(bootButton) == 0) {
      while (digitalRead(bootButton) == 0);
      if (state == 0) {
        state = 1;
      } else {
        state = 0;
      }
    }
  }
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_APSTA);
  staWifi_init();
  apWifi_init();
  
  pinMode(bootButton, INPUT);
  pinMode(internalLed, OUTPUT);

}
void loop() {
  readButtonBoot();
  digitalWrite(internalLed, state);
//  Serial.println(state);
}