// Arduino Libraries
#include <Arduino.h>
#include <ArduinoJson.h>
#include <string.h>
// WiFi Libraries
#include <WiFiUdp.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
// Project Libraries
#include "ComponentManager.h"
#include "UdpCommunication.h"
#include "SendingService.h"
#include "ReceivingService.h"
#include "EepromString.h"
#include "ArduinoDataPacket.h"
// Data Models
#include "Board.h"

// Constants announcement
const char *ssid = "Simtimus Network";
const char *password = "ureshiumaewo";

const char *host = "192.168.142.239";
const uint16_t port = 8080;
const uint16_t localPort = 4210;

// Class announcement
WiFiUDP Udp;
WiFiMulti wifiMulti;
UdpCommunication UdpComm = UdpCommunication(Udp, host, port);
ComponentManager CompManager = ComponentManager();
EepromString Eeprom = EepromString(0, 37);

// Board announcement
String boardId = Eeprom.readGuid(); // max 37 characters
String boardName = "First Board"; // max 32 characters
String boardModel = "ESP32";      // max 32 characters
String boardDescription = "Room Light Manager"; // max 32 characters
Board thisBoard = Board(boardId, boardName, boardModel, boardDescription);

// ClientData announcement
ArduinoDataPacket DataPacket = ArduinoDataPacket(boardId);

// Services announcement
SendingService Sending = SendingService(UdpComm, CompManager, DataPacket, thisBoard);
ReceivingService Receiving = ReceivingService(UdpComm, Eeprom, thisBoard);

// Variables announcement
unsigned long ReadPinData = millis();

void setup()
{
  Serial.begin(115200);

  // --------------------------------------------------
  // Setting up components and pins
  
  CompManager.Initialize();

  // --------------------------------------------------
  // Starting WiFi

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (wifiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address = ");
  Serial.println(WiFi.localIP());

  Udp.begin(localPort);
  Udp.setTimeout(250);
}

void loop()
{
  Sending.runService();
  Receiving.runService();
  delay(500);
}