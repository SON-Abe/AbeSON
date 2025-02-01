#include <ArduinoMqttClient.h>
#include <WiFi101.h>
#include "ThingSpeak.h"
#include <SPI.h>

#define tempPin A1 //pin to read tmp
#define HUMID_PIN A2 //pin to read humid

char ssid[] = "PAAL18"; // your network SSID (name), not sharing home network
char pass[] = "Nathan18"; // your network password, not sharing home wifi password

////////////////////////////////////////////////////////////////
unsigned long RH_Channel_No = 2762875;
const char * RH_WriteAPIKey = "VVXJEUB0OUPA5PH2";
unsigned long TMP_Channel_No = 2737117;
const char * TMP_WriteAPIKey = "Q68IWIYMTHIAA9RR";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.0.129"; //MQTT broker, not sharing home ip address
int port = 1883; //MQTT broker port

//MQTT topics
const char tempTopic[] = "temp";
const char humidTopic[] = "humid";

const long interval = 2000; //interval to send msg
unsigned long previousMillis = 0;


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  //connection to the broker
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  //connection to the broker failed
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;
    //record sensor valuse
    int heat = analogRead(tempPin); //analog read of tmp
    int v = heat * (3300/1024); //convert volt to K
    int Celsius =(v - 500 ) / 10; //temp in C

    int humid_val = 1023 - (analogRead(HUMID_PIN)+1000); //RH% calculation

    // Publish Temperature
    Serial.println(Celsius);
    mqttClient.beginMessage(tempTopic);
    mqttClient.println(Celsius);
    mqttClient.endMessage();

    // Publish Humidity
    Serial.println(humid_val);
    mqttClient.beginMessage(humidTopic);
    mqttClient.println(humid_val);
    mqttClient.endMessage();
    
    //ThingSpeak.setField(2, Celsius);/////////////////////////////
    //ThingSpeak.writeFields(TMP_Channel_No, TMP_WriteAPIKey);/////
    //ThingSpeak.setField(1, humid_val);////////////////////////
    //ThingSpeak.writeFields(RH_Channel_No, RH_WriteAPIKey);////
  }
}