// SLAVE ADDRESS: 98d3:32:216961


void setup()
{
  Serial.begin(9600);
  Serial3.begin(38400);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop()
{
  if (Serial3.available())
  {
    Serial.write(Serial3.read());
  }
  if (Serial.available())
  {
    Serial3.write(Serial.read());
  }
}
