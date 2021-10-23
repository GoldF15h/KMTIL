void setup() {
  Serial.begin(9600);
  Serial.println("Hello from arduino");
}

void loop() {
  if(Serial.available()) {
    Serial.println(Serial.readString());
  }
}
