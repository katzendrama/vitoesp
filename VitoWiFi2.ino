#include <Arduino.h>
#include <VitoWiFi.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

String ssid = "HeimwehLAN";
String pass = "DiesesPasswortkenntnurdieKatze";

String MiniserverIP = "192.168.178.49";
unsigned int MiniserverPort = 3333;

float outsidetemp = 0;
float exhausttemp = 0;
float flowtemp = 0;
float roomtempset = 0;
float redroomtempset = 0;
float neigung = 0;
float niveau = 0;
float kessel = 0;
/*
float burnerstarts = 0;
float burnerhours = 0;
*/

float lastsending = 0;


WiFiUDP Udp;
unsigned int localUdpPort = 4210;
char incomingPacket[256];


VitoWiFi_setProtocol(KW);
//Außentemperatur
DPTemp outsideTemp("outsidetemp", "boiler", 0x5525);
//Abgastemperatur
DPTemp exhaustTemp("exhausttemp", "boiler", 0x0816);
//Vorlauftemperatur
DPTemp flowTemp("flowtemp", "boiler", 0x0810);
//Raumtemperatur
DPTempS roomTempSet("roomtempset", "heating", 0x2306);
//Red. Raumtemperatur
DPTempS redroomTempSet("redroomtempset", "heating", 0x2307);
//Neigung
DPTemp Neigung("neigung", "heating", 0x27D3);
//Niveau
DPTemp Niveau("niveau", "heating", 0x27D4);
//Kesseltemperatur
DPTemp Kessel("pumpe", "heating", 0x0810);
/*
//Brennerstarts
DPTemp burnerStarts("burnerstarts", "boiler", 0x088A);
//Brennerstunden
DPTemp burnerHours("burnerhours", "boiler", 0x08A7);
*/



void setup() {
  WiFi.hostname("VitoESP");
  WiFi.begin(ssid, pass);  
  //Serial.begin(115200);
  ArduinoOTA.setHostname("Viessmann-to-Loxone");
  ArduinoOTA.begin();

  //VitoWiFi.setLogger(&terminal);  // might be too verbose/fast for Blynk to handle  VitoWiFi.enableLogger();  // might be too verbose/fast for Blynk to handle
  outsideTemp.setCallback(getOutsideTemp);
  exhaustTemp.setCallback(getexhaustTemp);
  flowTemp.setCallback(getflowTemp);  
  Neigung.setCallback(getneigung);
  Niveau.setCallback(getniveau);
  Kessel.setCallback(getkessel);
  roomTempSet.setWriteable(true).setCallback(getRoomtempSet);
  redroomTempSet.setWriteable(true).setCallback(getredRoomtempSet);
  /*burnerStarts.setCallback(getburnerStarts);
  burnerHours.setCallback(getburnerhours);*/
  VitoWiFi.setGlobalCallback(globalCallbackHandler);
  VitoWiFi.setup(&Serial);

  Udp.begin(localUdpPort);
}

void loop() {
  VitoWiFi.loop();
  if(lastsending+5000 < millis()) {
    VitoWiFi.readAll();
    sendValue();
    lastsending= millis();
  }
  int packetSize = Udp.parsePacket();
  if(packetSize) {    
    // receive incoming UDP packets   
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    String input = String(incomingPacket);
    Udp.beginPacket("192.168.178.49", MiniserverPort);
    Udp.print("Empfangen: " + input);
    Udp.endPacket();    
     String recog = strtok(incomingPacket,":");
    if(recog == String("settemp")) {               
      String valuu = input.substring(8);   
      uint8_t valu = valuu.toInt();
      DPValue value(valu); 
      Udp.beginPacket("192.168.178.49", MiniserverPort);
      Udp.print("Eingestellte Innentemperatur: " + String(valuu));
      Udp.endPacket();    
      VitoWiFi.writeDatapoint(roomTempSet, value); 
      VitoWiFi.readAll();  
    } else if(recog == String("setredtemp")) {                       
      String valuu2 = input.substring(11);   
      uint8_t valu2 = valuu2.toInt();
      DPValue value(valu2); 
      Udp.beginPacket("192.168.178.49", MiniserverPort);
      Udp.print("Reduzierte Raumtemperatur: " + String(valu2));
      Udp.endPacket();    
      VitoWiFi.writeDatapoint(redroomTempSet, value); 
      VitoWiFi.readAll();  
    }   
  }
  ArduinoOTA.handle();
 }

void globalCallbackHandler(const IDatapoint& dp, DPValue value) {
  char value_str[15] = {0};
  value.getString(value_str, sizeof(value_str));
}

void getOutsideTemp(const IDatapoint& dp, DPValue value) {
  outsidetemp = value.getFloat();
}

void getexhaustTemp(const IDatapoint& dp, DPValue value) {
  exhausttemp = value.getFloat();
}

void getflowTemp(const IDatapoint& dp, DPValue value) {
  flowtemp = value.getFloat();
}

void getRoomtempSet(const IDatapoint& dp, DPValue value) {
  roomtempset = value.getU8();
}
void getredRoomtempSet(const IDatapoint& dp, DPValue value) {
  redroomtempset = value.getU8();
}
void getneigung(const IDatapoint& dp, DPValue value) {
  neigung = value.getFloat();
}
void getniveau(const IDatapoint& dp, DPValue value) {
  niveau = value.getFloat();
}
void getkessel(const IDatapoint& dp, DPValue value) {
  kessel = value.getFloat();
}


/*void getburnerStarts(const IDatapoint& dp, DPValue value) {
  burnerstarts = value.getFloat();
}

void getburnerhours(const IDatapoint& dp, DPValue value) {
  burnerhours = value.getFloat();
}*/

void sendValue() {
  VitoWiFi.readAll();   
  Udp.beginPacket("192.168.178.49", MiniserverPort);
  Udp.print("Aussentemperatur: " + String(outsidetemp));
  Udp.print("\0");
  Udp.print("Eingestellte Innentemperatur: " + String(roomtempset));
  Udp.print("\0");
  Udp.print("Abgastemperatur: " + String(exhausttemp));
  Udp.print("\0");
  Udp.print("Vorlauftemperatur: " + String(flowtemp));
  Udp.print("\0");
  Udp.print("Neigung: " + String(neigung));
  Udp.print("\0");
  Udp.print("Niveau: " + String(niveau));
  Udp.print("\0");
  Udp.print("Kesseltemperatur: " + String(kessel));
  Udp.print("\0");
  Udp.print("Reduzierte Raumtemperatur: " + String(redroomtempset));
  Udp.endPacket();
}








