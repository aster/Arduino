#include <MsTimer2.h>
#define R_LED 6
#define L_LED 5
#define SW 7
#define TAP_TIME 200

//solenoid connected pin
const short SOL[] = {4, 18, 3, 17, 2, 16, 1};
short SOL_count[] = {0,  0, 0,  0, 0,  0, 0};
short flag= 0;
short now_note = 0;
long cnt= 0;
const long score[100][2] = {
  {2186, 3}, {2207, 5}, 
  {4932, 2}, {4933, 6}, 
  {7584, 2}, 
  {8904, 2}, 
  {10259, 6}, 
  //長押し
  {12708, 4}, 
  {14876, 4}, 
  {14979, 4}, 
  {15079, 4}, 

  {16600, 2}, 
  {19209, 6}, 
  {21942, 2}, 
  {23217, 4}, 
  {25904, 3}, 
  {28654, 5}, 
  {31082, 3}, 
  {33766, 5}, 
  {36450, 2}, 
  {39076, 6}, 
  {41656, 6}, 
  {43153, 2}, 
  {44500, 6}, 
  {45705, 6}, 
  //長押し
  {47517, 2}, 
  {48198, 2}, 
  {48824, 2}, 
  {49495, 2}, 

  //長押し
  {50152, 6}, 
  {50976, 6}, 

  {53059, 4}, 
  {54406, 4}, 
  {55063, 3}, 
  {56205, 5}, 
  {57689, 3}, 
  {58358, 4}, 
  {59731, 4}, 

  {63002, 3}, {63005, 5}, 
  {65600, 2}, {65615, 6}, 
  {68075, 2}, 
  {69425, 6}, 
  {70944, 2}, 
  {72037, 6}, 
  {73563, 4}, 
  {76175, 4}, 
  {78805, 3}, 
  {80157, 5}, 
  {81457, 3}, 
  {82588, 5}, 
  {84435, 4}, 
  {86575, 5}, 
  {89186, 3}, 
  {91903, 6}, 
  {94508, 2}, 
  {97152, 6}, 
  {99959, 6}, 
  {101179, 5}, 
  {102418, 3}, 
  {103900, 2}, 
  {105920, 4}, 
  {107200, 4}, 
  {109007, 4}, 
  {109829, 4}, 
  //長押し
  {110532, 3}, 
  {112504, 3}, 
  //長押し
  {113093, 5}, 
  {114939, 5}, 

  //キラキラ
  {115605, 4}, 

  {123683, 2}, 
  {124850, 6}, 
  {126280, 3}, 
  {126953, 3}, 
  {127568, 5}, 
  {128256, 5}, 
  {128934, 4}, 
  {130054, 4}, 
  //長押し
  {134124, 4}, 
  {136861, 4}};

// 最初のタップを基準にする
long offset = score[0][0];

// 1msごとに呼び出し
void timerInterrupt(){
  if(flag){
    if (cnt == score[now_note][0] - offset){
      SOL_count[ score[now_note][1] - 1 ] = TAP_TIME;
      now_note++;
    }
    //タップカウント減らしと通電処理
    allOparation();
    cnt++;
  }

  //最初の1タップ目を調整
  if(digitalRead(SW) == LOW){
    digitalWrite(R_LED, HIGH);
    flag=1;
  }
  else{
    digitalWrite(R_LED, LOW);
  }
}

void allOparation(){
  for(int i = 0; i < 7;i++){
    if(SOL_count[i]>0){
      digitalWrite(SOL[i], HIGH);
      digitalWrite(L_LED, HIGH);
      SOL_count[i]--;
    }else{
      digitalWrite(SOL[i], LOW);
      digitalWrite(L_LED, LOW);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(L_LED, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  for (int i = 0; i < 7 ; i++)pinMode(SOL[i], OUTPUT);

  MsTimer2::set(1, timerInterrupt);
  MsTimer2::start();
}

void loop() {
}
