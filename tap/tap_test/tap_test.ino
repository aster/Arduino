#include <MsTimer2.h>
#define R_LED 6
#define L_LED 5
#define SW 7
#define TAP_TIME 80

// ソレノイドのノイズがひどい
//フォトカプラを使用する

//solenoid connected pin
const short SOL[] = {1, 18, 2, 17, 3, 16, 4};
short SOL_count[] = {0,  0, 0,  0, 0,  0, 0};
short flag= 0;
short now_note = 0;
long cnt= 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(L_LED, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  for (int i = 0; i < 7 ; i++)pinMode(SOL[i], OUTPUT);
}

void loop() {
  delay(3000);
  digitalWrite(SOL[0], HIGH);
  delay(50);
  digitalWrite(SOL[0], LOW);
  delay(1000);

  digitalWrite(SOL[1], HIGH);
  delay(50);
  digitalWrite(SOL[1], LOW);
  delay(1000);

  digitalWrite(SOL[2], HIGH);
  delay(50);
  digitalWrite(SOL[2], LOW);
  delay(1000);

  digitalWrite(SOL[3], HIGH);
  delay(50);
  digitalWrite(SOL[3], LOW);
  delay(1000);

  digitalWrite(SOL[4], HIGH);
  delay(50);
  digitalWrite(SOL[4], LOW);
  delay(1000);

  digitalWrite(SOL[5], HIGH);
  delay(50);
  digitalWrite(SOL[5], LOW);
  delay(1000);

  digitalWrite(SOL[6], HIGH);
  delay(50);
  digitalWrite(SOL[6], LOW);
  delay(1000);
}
