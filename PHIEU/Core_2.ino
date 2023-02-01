void core_2()
{
   myStr = String(sophieu);
  String serverPath = serverName + myStr;
  http.begin(client, serverPath.c_str());
  int temp = http.GET();
  http.end();
  delay(100);
} 
