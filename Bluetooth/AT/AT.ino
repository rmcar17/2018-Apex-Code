// SLAVE ADDRESS: 98d3:32:216961


void setup()
{
  Serial.begin(9600);
  Serial5.begin(38400);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop()
{
  if (Serial5.available())
  {
    Serial.write(Serial5.read());
  }
  if (Serial.available())
  {
    Serial5.write(Serial.read());
  }
}
