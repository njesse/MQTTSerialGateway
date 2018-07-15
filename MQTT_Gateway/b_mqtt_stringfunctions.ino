String getMessage(String receivedString)
{
  int start = receivedString.lastIndexOf("[") + 1;
  int ende = receivedString.lastIndexOf("]");
  if (ende > start)
  {
    return receivedString.substring(start, ende);
  }
  else
  {
    return "no Message detected";
  }
}


String getTopic(String receivedString)
{
  // [Topic][Message]
  int start = 1;
  int ende = receivedString.indexOf("]");
  if (ende > start)
  {
    return receivedString.substring(start, ende);
  }
  else {
    return "no Topic detected";
  }
}

bool StringIsMQTTMessage(String string)
{
  bool isValid = true;
  if (!string.startsWith("[") )
  {
    isValid = false;
  }
  if (!string.endsWith("]"))
  {
    isValid = false;
  }

  if (getTopic(string) == "no Topic detected")
  {
    isValid = false;
  }
  if (getMessage(string) == "no Message detected")
  {
    isValid = false;
  }
  return isValid;
}

