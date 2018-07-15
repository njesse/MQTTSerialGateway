/****************************

    MQTT_Gateway

    The gateway is connected to a second arduino via a serial connection
    Serial speed is set to 57600

   Serial Messages:
   Send MQTT Message (including the brackets): [Topic][Message]
   Subsribe to Topics: +Topic
   Unsubscribe: -Topic
   Get current Time: Time
   Received Messagesformat: [Topic][Message}

*/
// Libraries for WIFI
#include <ESP8266WiFi.h>

// Libraries for MQTT
#include "PubSubClient.h"

// Libraries for Time
#include <NTPClient.h>
#include <WiFiUdp.h>

// Signatures for functions used in this file
#include "definitions.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "YourWIFI"
#define WLAN_PASS       "YourPW"

/************************* MQTT Setup *********************************/

#define MQTT_SERVER "mqtt-host.de"  //change to your server
#define MQTT_PORT  1883                   
#define MQTT_USERNAME "MQTT_Username"
#define MQTT_PASSWORD "MQTT_Password"
#define MQTT_CLIENT_ID "MQTT_ClientID"
#define MQTT_DEBUGTOPIC "NodeMCU/Debug" // all received serial messages are send to this topic

#define MQTT_NUMBERSOFTOPIC 5  // Keeps a list of subscribed topics to re-subscribe after disconnect

/************************* NTP Server (Time) *********************************/

#define NTP_SERVER "de.pool.ntp.org" // change to a timerserver near you
#define NTP_CORRECTION_SECONDS 7200 // in my case:  1hour for germany  + 1h for summertime

/************************* Global Variables *********************************/


// Time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, NTP_CORRECTION_SECONDS);

// MQTT
WiFiClient WiFiclient;
PubSubClient MQTTclient(MQTT_SERVER, MQTT_PORT, callback, WiFiclient); 
String subscribedTopics[MQTT_NUMBERSOFTOPIC];
int numbersoftopic = 0; // current position in subsribedTopics

// Serial Connection
String serialInput;

/************************* Setup and Loop *********************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  delay(10);

  // Connect to WiFi access point.
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("WiFi connected");

  // Connect to MQTT
  while (!MQTTclient.connected()) {
    reconnect();

  }

  // Connect to NTP
  timeClient.begin();
}


void loop() {

  if (!MQTTclient.connected()) {
    reconnect();
  }
  MQTTclient.loop();

  while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      serialInput += c; //makes the string readString
    }
  }
  if (serialInput.length() > 0)
  {
    SerialMessageReceived(serialInput); 
    serialInput = "";
  }

}


