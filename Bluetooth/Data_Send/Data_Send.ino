void setup() {
  Serial3.begin(38400);
}

void loop() {
  if(Serial3.available()){
    Serial.println(Serial3.read());
  }
  if(Serial.available()){
    Serial3.write(Serial.read());
  }
}
