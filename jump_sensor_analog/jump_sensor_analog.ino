
void setup() {
  Serial.begin(9600);
}

void loop() {
    short val = Serial.println(analogRead(6));
    delay(100);
}
