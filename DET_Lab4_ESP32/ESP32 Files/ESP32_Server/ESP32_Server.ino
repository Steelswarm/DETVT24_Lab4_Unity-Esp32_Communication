
//==================================
//ESP32 WebSocket Server: Toggle LED
//by: Ulas Dikme
//modified by: António Pinheiro Braga
//==================================
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
//-----------------------------------------------

const char* ssid = "dsv-extrality-lab";
const char* password = "expiring-unstuck-slider";

//-----------------------------------------------
#define BUILTIN_LED 13 //Default ESP32-S2 Sparkfun Built in LED
#define LED 10
#define POTENTIOMETER A5
#define RGBLED_RED A1
#define RGBLED_GREEN A2
#define RGBLED_BLUE A0
#define BUTTON 34
//-----------------------------------------------
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
//-----------------------------------------------
boolean LEDonoff=false; String JSONtxt; String oldJSON; int currentClientNumber; int currentpotVal; int oldpotVal; int mappedPotVal; bool buttonMessageSent; int buttonState;
//-----------------------------------------------
#include "html.h"
#include "header.h"
//====================================================================

void setup()
{
  Serial.begin(115200); pinMode(LED, OUTPUT); pinMode(BUILTIN_LED, OUTPUT); pinMode(RGBLED_RED, OUTPUT); pinMode(RGBLED_GREEN, OUTPUT); pinMode(RGBLED_BLUE, OUTPUT); pinMode(BUTTON, INPUT);
  //-----------------------------------------------
  connect2Network(); 

  buttonMessageSent = false;
}
//====================================================================

int mapPotentiometerValue(int potValue) {
  int mappedValue;
    // Ensure the potentiometer value is within the expected range (0-8191)
    if (potValue < 0) potValue = 0;
    if (potValue > 8191) potValue = 8191;

    // Map the value from the range [0, 8191] to [0, 100]
    mappedValue = (potValue * 100) / 8191;
    return mappedValue;
    
}

void loop()
{
  currentpotVal = analogRead(POTENTIOMETER);
  buttonState = digitalRead(BUTTON);
  //int brightness = currentpotVal / 4;
  // int brightness = map(currentpotVal, 0, 8191, 0, 255);
  // analogWrite(LED_ANALOG, brightness);

  mappedPotVal = mapPotentiometerValue(currentpotVal);
  int threshold = 2;
  int margin = 2;

  if(mappedPotVal <= margin) mappedPotVal = 0;
  if(mappedPotVal >= 100 - margin) mappedPotVal = 100;

  if(abs(mappedPotVal - oldpotVal) >= threshold)
  { 
  
  Serial.println("Pot value: " + String(mappedPotVal));
  webSocket.broadcastTXT("Pot value: " + String(mappedPotVal));
  oldpotVal = mappedPotVal;
  }

  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Lost connection to network! Attempting to reconnect...");
    connect2Network();
    return;
  }

  webSocket.loop(); server.handleClient();
  if(currentClientNumber != webSocket.connectedClients()){
    if(currentClientNumber < webSocket.connectedClients()) Serial.println("A new client has connected!");
    else Serial.println("A client has disconnected");
    Serial.print("Number of clients currently connected: ");
    Serial.println(webSocket.connectedClients());
    
    currentClientNumber = webSocket.connectedClients();
    webSocket.broadcastTXT(JSONtxt);
  }

  if(buttonState == HIGH && buttonMessageSent == false) {

    webSocket.broadcastTXT("Button Pressed: true");
    buttonMessageSent = true;

  } else if(buttonState == LOW) buttonMessageSent = false;

  //-----------------------------------------------
  if(LEDonoff == false) {digitalWrite(LED, LOW); digitalWrite(BUILTIN_LED, LOW);} 
  else {digitalWrite(LED, HIGH); digitalWrite(BUILTIN_LED, HIGH);} 
  //-----------------------------------------------
  String LEDstatus = "OFF";
  if(LEDonoff == true) LEDstatus = "ON";
  JSONtxt = "{\"LEDonoff\":\""+LEDstatus+"\"}";
  sendMessage2Clients();
  
} 