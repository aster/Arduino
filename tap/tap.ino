#define R_LED 6
#define L_LED 5
#define SW 7

//solenoid connected pin
const short SOL[] = {0, 19, 1, 18, 2, 17, 3, 16, 4};
short cnt = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(L_LED, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  for (int i = 0; i < 9 ; i++)pinMode(SOL[i], OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  /*
    if (digitalRead(SW) == LOW) {
    digitalWrite(L_LED, HIGH);
    } else {
    digitalWrite(L_LED, LOW);
    }

    digitalWrite(SOL[cnt], HIGH);
    if (cnt == 0) {
    digitalWrite(SOL[8], LOW);
    } else {
    digitalWrite(SOL[cnt - 1], LOW);
    }
    delay(100);

    cnt > 8 ? cnt = 0 : cnt++;
  */
  for (int i = 0; i < 9; i++) {
    digitalWrite(SOL[i], HIGH);
    delay(40);
    digitalWrite(SOL[i], LOW);
    delay(460);
  }
}
