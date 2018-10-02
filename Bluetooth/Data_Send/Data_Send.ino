void setup() {
  Serial5.begin(38400);
}

void loop() {
  if(Serial5.available()){
    Serial.println(Serial5.read());
  }
  if(Serial.available()){
    Serial5.write(Serial.read());
  }
}
