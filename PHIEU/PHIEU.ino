#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#define ss1 26
#define ss2 25
#define led 23
int8_t a, b;
int count = 0;
int value = 0;
int sophieu = 0;
int phieutruocdo = -1;
int guiphieu = -1;
TaskHandle_t Task1;
TaskHandle_t Task2;


const char *ssid = "3D Sinh vien";
const char *password = "17151032@@";
String myStr;
WiFiClient client;
HTTPClient http;
String serverName = "http://192.168.50.175/getvalue.php?id=thung1&value=";
int putData()
{

  myStr = String(sophieu);
  String serverPath = serverName + myStr;
  http.begin(client, serverPath.c_str());
  int temp = http.GET();
  http.end();
  return temp;
}
void setup()
{
  pinMode(ss1, INPUT_PULLUP);
  pinMode(ss2, INPUT_PULLUP);
  pinMode(led , OUTPUT);
  digitalWrite(led , LOW);
  Serial.begin(230400);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  digitalWrite(led , HIGH);
  while (putData() != 200);
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(100); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    5000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(100); 
}

void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
  core_2();
  } 
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    core_1();
  }

}
void loop(){


}
