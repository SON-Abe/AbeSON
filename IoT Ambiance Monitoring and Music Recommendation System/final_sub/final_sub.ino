#include <ArduinoMqttClient.h>
#include <WiFi101.h>
//#include "secret_arduino.h" //contained the ssid and password of the WiFi
//WiFi that you want to be connected
char ssid[] = "ssd"; // your network SSID
char pass[] = "pass"; // your network password
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
const char broker[] = "IP_Address"; //i'm not sharing my ip address
int port = 1883; //channel of the broker
//topics, you can change the name
const char topic[] = "tmp";
const char topic2[] = "hum";
//const char topic3[] = "real_unique_topic_3";
void setup() {
 //Initialize serial and wait for port to open:
 Serial.begin(57600);
 while (!Serial) {
 ; // wait for serial port to connect. Needed for native USB port only
 }
 // attempt to connect to Wifi network:
 Serial.print("Attempting to connect to SSID: ");
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
 // subscribe to a topic
 mqttClient.subscribe(topic);
 mqttClient.subscribe(topic2);
 mqttClient.onMessage(onMqttMessage);
}
void loop() {
 // call poll() regularly to allow the library to receive MQTT messages
and
 // send MQTT keep alive which avoids being disconnected by the broker
 mqttClient.poll();
}
//print the MQTT message
void onMqttMessage(int messageSize) {
 // we received a message, print out the topic and contents
 String topics = mqttClient.messageTopic();
 String values;
 //Serial.print(mqttClient.messageTopic());
 //Serial.print("', length ");
 //Serial.print(messageSize);
 //Serial.println(" bytes:");
 // use the Stream interface to print the contents
 while (mqttClient.available()) {
 Serial.println((int)mqttClient.read());
 }
 //Serial.println(values);
 Serial.println();
}