//=======================================
//handle function: send webpage to client
//=======================================
void webpage()
{
  server.send(200,"text/html", webpageCode);
}

void changeLEDBrightness(int pinNumber, int brightness) {
  int mappedBrightness = map(brightness, 0, 100, 0, 255);
  analogWrite(pinNumber, mappedBrightness);
}

//=====================================================
//function process event: new data received from client
//=====================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);

  if(type == WStype_TEXT) //receive text from client
  {
    byte separator=payloadString.indexOf('=');
    String var = payloadString.substring(0,separator);
    Serial.print("var= ");
    Serial.println(var);
    String val = payloadString.substring(separator+1);
    Serial.print("val= ");
    Serial.println(val);
    Serial.println(" ");

    if(var == "LEDonoff")
    {
      LEDonoff = false;
      if(val == "ON") LEDonoff = true;

    }

    if(var == "RedLEDintensity") changeLEDBrightness(RGBLED_RED, val.toInt());
    if(var == "GreenLEDintensity") changeLEDBrightness(RGBLED_GREEN, val.toInt());
    if(var == "BlueLEDintensity") changeLEDBrightness(RGBLED_BLUE, val.toInt());

  }
}

void connect2Network() 
{
  WiFi.begin(ssid, password);
  Serial.println("Printing this device's details bellow...");
  Serial.print("MacAddress: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Device Name: ");
  Serial.println(WiFi.getHostname());
  Serial.print("Attempting to connect to " + String(ssid) + " network...");
  while(WiFi.status() != WL_CONNECTED){Serial.print("."); delay(500);}
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println("Successfully connected to network!");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  //-----------------------------------------------
  server.on("/", webpage);
  //-----------------------------------------------
  server.begin(); webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void sendMessage2Clients() {
  if(oldJSON != JSONtxt) webSocket.broadcastTXT(JSONtxt);
  oldJSON = JSONtxt;
}