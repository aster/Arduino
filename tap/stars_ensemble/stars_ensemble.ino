#include <MsTimer2.h>
#define R_LED 6
#define L_LED 5
#define SW 7
#define TAP_TIME 200

// ソレノイドのノイズがひどい
//フォトカプラを使用する

//solenoid connected pin
const short SOL[] = {4, 18, 3, 17, 2, 16, 1};
short SOL_count[] = {0,  0, 0,  0, 0,  0, 0};
short flag= 0;
short now_note = 0;
long cnt= 0;
const long score[100][2] = {{12455, 5}, {12456, 3}, {15115, 2}, {15132, 6}, {17768, 2}, {19050, 2}, {20438, 6}, {22891, 4}, {26782, 2}, {29510, 6}, {32059, 2}, {33407, 4}, {36069, 3}, {38652, 5}, {41346, 3}, {43993, 5}, {46646, 2}, {49286, 6}, {51933, 6}, {53357, 2}, {54736, 6}, {55882, 6}, {57691, 2}, {59650, 2}, {60305, 6}, {61092, 6}, {63252, 4}, {64471, 4}, {65290, 3}, {66381, 5}, {67902, 3}, {68547, 4}, {69837, 4}, {73130, 3}, {73153, 5}, {75783, 6}, {76027, 2}, {78203, 2}, {79598, 6}, {81024, 2}, {82268, 6}, {83685, 4}, {86371, 4}, {88978, 3}, {90324, 5}, {91606, 3}, {92785, 5}, {94586, 4}, {96729, 5}, {99360, 3}, {102056, 6}, {104661, 2}, {107325, 6}, {110140, 6}, {111430, 5}, {112536, 3}, {114033, 2}, {116035, 4}, {117317, 4}, {119150, 4}, {119954, 4}, {120629, 3}, {122566, 3}, {123274, 5}, {125084, 5}, {125584, 4}, {133806, 2}, {135003, 6}, {136388, 3}, {137041, 3}, {137725, 5}, {138369, 5}, {139125, 4}, {140216, 4}, {144243, 4}, {147001, 4}};

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
