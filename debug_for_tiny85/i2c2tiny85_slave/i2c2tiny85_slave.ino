//
// arduino I2Cスレーブ
//

#include <Wire.h>

char buf[100];
volatile boolean process_it;

// i2c受信関数
void receiveEvent(int howMany) 
{
  int n = 0;
  
  // 送信された全てのデータを受信
  while(Wire.available()) {
    buf[n++] = (char)Wire.read();    
  }
  buf[n] = '\0';
  process_it = true;
}

void setup() {
  Serial.begin (9600);
  process_it = false;
  Wire.begin(8) ;                    // i2cの初期化、自アドレスを８とする
  Wire.onReceive(receiveEvent) ;     // 受信関数の登録
}

void loop() {
  if (process_it) {
    Serial.print (buf);
    process_it = false;
  }  // end of flag set
}
