void subscribeTo(String Topic)
{
  MQTTclient.subscribe(Topic.c_str());

  // save subscriptions for reconnect

  bool alreadySubscribed = false;

  for (int i = 0; i < MQTT_NUMBERSOFTOPIC; i++)
  {
    if (subscribedTopics[i].equals(Topic))
    {
      alreadySubscribed = true;
    }
  }
  if (!alreadySubscribed)
  {
    if (numbersoftopic == MQTT_NUMBERSOFTOPIC)
    {
      Serial.print("Topic will not be resubscribed on reconnect! Maximum is ");
      Serial.print(MQTT_NUMBERSOFTOPIC);
    }
    else
    {
      subscribedTopics[numbersoftopic] = Topic;
      numbersoftopic++;
    }

  }
}

void unsubscribeFrom(String Topic) {
  MQTTclient.unsubscribe(Topic.c_str());


  int position = -1;
  for (int i = 0; i < MQTT_NUMBERSOFTOPIC; i++)
  {
    if (subscribedTopics[i].equals(Topic))
    {
      position = i;
    }
  }

  if (position>=0)  // if Topic is in list, overwrite it with the last Topic in list
  {
    numbersoftopic--;
    subscribedTopics[position]=subscribedTopics[numbersoftopic];
    subscribedTopics[numbersoftopic] = ""; // can be overwritten because it was copied to subscribedTopics[position]. 
  }
  
}

