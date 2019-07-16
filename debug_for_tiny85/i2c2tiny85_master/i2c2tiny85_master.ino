//
// attiny I2Cマスタ
//

#include <TinyWireM.h> //https://github.com/adafruit/TinyWireM

#if defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  #if defined(__AVR_ATtiny44__)
    #define Model "ATtiny44"
  #else
    #define Model "ATtiny84"
  #endif  
#elif defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  #if defined(__AVR_ATtiny45__)
    #define Model "ATtiny45"
  #else
    #define Model "ATtiny85"
  #endif  
#elif defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny861__)
  #if defined(__AVR_ATtiny461__)
    #define Model "ATtiny461"
  #else
    #define Model "ATtiny861"
  #endif  
#elif defined(__AVR_ATtiny4313__)
  #define Model "ATtiny4313"
#endif


// 最大10文字にデータを分割してデータの送信
void i2c_print(char *str) {
  int pnum;
  int jmax;
  pnum = (strlen(str)+9)/10;  //パケット数
  for (int i=0;i<pnum;i++) {
    jmax = i*10+10;
    if (strlen(str) < jmax) jmax = strlen(str);
    TinyWireM.beginTransmission(8) ;  // 通信の開始処理、スレーブのアドレスは８とする
    for (int j=i*10;j<jmax;j++) {  // 1パケットの最大文字数は10文字
      TinyWireM.send(str[j]) ;  // 通信データ送信
    }
    TinyWireM.send(0) ;  // 通信データ送信(終端文字)
    TinyWireM.endTransmission();
  }
}

void setup()
{
  TinyWireM.begin() ;  // i2cの初期化、マスターとする
  delay(5000) ;        // ５秒後に開始
}

// 繰り返し実行されるメインの処理関数
void loop()
{
  static int num = 0;
  char sbuf[40];

  sprintf(sbuf,"TinyWireM num=%d model=%s\n",num,Model);
  num++;
  i2c_print(sbuf);
  delay(1000); 
}
