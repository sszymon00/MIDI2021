//Format wysylania wiadomosci midi

void MIDImessage(byte Status, byte data1, byte data2)
{
  Serial.write(Status);
  Serial.write(data1);
  Serial.write(data2);
}
