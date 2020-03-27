#include <MsTimer2.h>
#define R_LED 6
#define L_LED 5
#define SW 7
#define TAP_TIME 40

//solenoid connected pin
const short SOL[] = {0, 19, 1, 18, 2, 17, 3, 16, 4};
short SOL_count[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
short flag= 0;
short now_note = 0;
long cnt= 0;
long offset = 0;
const long score[100][2] = { {6107, 3}, {7325, 3}, {8726, 6}, {9977, 6}, {11254, 4}, {13903, 4}, {15113, 3}, {15122, 5}, {17737, 2}, {20396, 4}, {22950, 6}, {25412, 3}, {26707, 2}, {28834, 2}, {30111, 2}, {31440, 6}, {32709, 6}, {33970, 3}, {35300, 5}, {37015, 3}, {37016, 5}, {38292, 3}, {39728, 3}, {40830, 5}, {42335, 5}, {43447, 2}, {44741, 2}, {46053, 6}, {47498, 6}, {48644, 3}, {51302, 5}, {53893, 2}, {56530, 6}, {59580, 6}, {62137, 2}, {64743, 6}, {67237, 2}, {69267, 3}, {70545, 3}, {71832, 5}, {73135, 5}, {74404, 5}, {75857, 4}, {78316, 3}, {78324, 5}, {79567, 4}, {82200, 5}, {83460, 3}, {84782, 6}, {86173, 2}, {87372, 5}, {90032, 6}, {91152, 2}, {92473, 3}, {93820, 5}, {95134, 6}, {100303, 4}, {111923, 5}, {112179, 5}, {113115, 2}, {114436, 6}, {115075, 6}, {115705, 3}, {117210, 4}, {119667, 3}, {119667, 5}, {120903, 2}, {123489, 6}, {126139, 3}, {128693, 5}, {131269, 2}, {132514, 6}, {133748, 4}};


void timerInterrupt(){

  if(flag){
    cnt++;
    if (cnt == score[now_note][0]){

    }

  }else{
    if(digitalRead(SW) == LOW)flag=1;
  }

}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(L_LED, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  for (int i = 0; i < 9 ; i++)pinMode(SOL[i], OUTPUT);

  MsTimer2::set(1, timerInterrupt);
  MsTimer2::start();
}

void loop() {

  for (int i = 0; i < 9; i++) {
    digitalWrite(SOL[i], HIGH);
    delay(40);
    digitalWrite(SOL[i], LOW);
    delay(460);
  }
}
