// called when packet received, forwarded to arduino
// Messages to MQTT_DEBUGTOPIC might be handled different
void callback(char* topic, byte* payload, unsigned int length) {
  String receivedMessage = "[";
  receivedMessage.concat(topic);
  receivedMessage.concat("][");
  for (int i = 0; i < length; i++) {
    receivedMessage.concat((char)payload[i]);
  }

  receivedMessage.concat("]");

  Serial.println(receivedMessage);

  if (receivedMessage.indexOf("Ping") >= 0)
  {
    MQTTclient.publish(MQTT_DEBUGTOPIC,  MQTT_CLIENT_ID " Pong");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!MQTTclient.connected()) {
    // Attempt to connect
    if (MQTTclient.connect(MQTT_CLIENT_ID, MQTT_USERNAME,  MQTT_PASSWORD)) {
      Serial.println("MQTT connected");
      // Once connected, publish an announcement...
      MQTTclient.publish(MQTT_DEBUGTOPIC, MQTT_CLIENT_ID " connected");
      // ... and resubscribe
      MQTTclient.subscribe(MQTT_DEBUGTOPIC);

      for (int i = 0; i < numbersoftopic; i++)
      {
        MQTTclient.subscribe(subscribedTopics[i].c_str());
      }

    } else {
     
      delay(5000);
    }
  }
}
