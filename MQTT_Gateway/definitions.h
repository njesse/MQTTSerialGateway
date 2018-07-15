// a_mqtt
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

// b_mqtt_stringfunctions
String getMessage(String receivedString);
String getTopic(String receivedString);
bool StringIsMQTTMessage(String string);

// c_serialInput
void SerialMessageReceived(String message);

// d_subscribtions
void subscribeTo(String Topic);
void unsubscribeFrom(String Topic);
