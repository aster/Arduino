#include <CapacitiveSensor.h>
#define SW_PIN 9

CapacitiveSensor sensor = CapacitiveSensor(2,3); //(Send, Resieve)

void setup() {
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  delay(10);
  while(digitalRead(SW_PIN));
}

void loop() {
  long start = millis();
  long total =  sensor.capacitiveSensor(30);

  Serial.print(millis() - start);
  Serial.print("\t");
  Serial.print(total);
  Serial.print("\t");
  meter(total/20 < 40 ? total/20 : 40);

  delay(10) ;
}

void meter(short n){
  for(int i=0; i<n; i++){
    Serial.print('O');
  }
  Serial.println(' ');
}









