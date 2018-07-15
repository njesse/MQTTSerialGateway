void SerialMessageReceived(String message)
{
  //Message is send to debugtopic
  MQTTclient.publish(MQTT_DEBUGTOPIC"/"MQTT_USERNAME"/SerialInput", message.c_str());

  message.trim(); //remove any spaces

  if (StringIsMQTTMessage(message)) // Format [Topic][Message]
  {
    MQTTclient.publish(getTopic(message).c_str(), getMessage(message).c_str());
  }
  else if (message.startsWith("+"))
  {
    message.replace("+", "");
    subscribeTo(message);
  }
  else if (message.startsWith("-"))
  {
    message.replace("-", "");
    unsubscribeFrom(message);

  }
  else if (message.equals("time"))
  {
    timeClient.update();
    Serial.print("Time:");
    Serial.println(timeClient.getFormattedTime());
  }
  else if (message.equals("status"))
  {
    Serial.print("numbersoftopic: ");
    Serial.println(numbersoftopic);

    for (int i = 0; i < numbersoftopic; i++)
    {
      Serial.println(subscribedTopics[i]);
    }
  }
}

