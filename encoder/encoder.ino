#define pinA 2
#define pinB 3

short rot_count = 0;  // 一周を300countとして状態が4ステップなので1200ステップに拡張。
int direction = 0;
int parse;

void setup()
{
  int current_a;
  int current_b;

  Serial.begin(9600);
  pinMode(pinA,INPUT);
  pinMode(pinB,INPUT);

  current_a = digitalRead(pinA);
  current_b = digitalRead(pinB);

//初期位置
  if(( current_a == 0 ) && ( current_b == 0 ))    // A,Bとも０
  {
    parse = 0;
  }
  if(( current_a == 1 ) && ( current_b == 0 ))    // A=1 B = 0 CCW
  {
    parse = 1;
  }
  if(( current_a == 1 ) && ( current_b == 1 ))    // A,Bとも1
  {
    parse = 2;
  }
  if(( current_a == 0 ) && ( current_b == 1 ))    // A,Bとも０
  {
    parse = 3;
  }

  attachInterrupt(pinA-2,rotary_changedPin,CHANGE);
  attachInterrupt(pinB-2,rotary_changedPin,CHANGE);
}

void loop()
{
  //シリアルコンソールに現在の値を出力。
  Serial.println(rot_count);
  delayMicroseconds(1000);
}

//pinの割り込み処理
void rotary_changedPin()
{
  int now_a;
  int now_b;
  now_a = digitalRead(pinA);
  now_b = digitalRead(pinB);

  if( parse == 0 )
  {
    if(( now_a == 1 ) && (now_b == 0 )) // reverse=CCW
    {
      rot_count--;
      direction = 0; //CCW
      parse = 3;
      return;
    } else if (( now_a == 0 ) && ( now_b == 1)) //foward = CW
    {
        rot_count++;
        direction = 1;    //CW
        parse = 1;
        return;
    } else {
         // fatal error
    }
  } 
  if( parse == 1 )
  {
    if(( now_a == 0 ) && (now_b == 0 )) // reverse = CCW
    {
      rot_count--;
      direction= 0;    //CCW
      parse = 3;
      return;
    } else if (( now_a == 1 ) && ( now_b == 1)) //foward = CW
    {
        rot_count++;
        direction = 1;    // CW
        parse = 2;
        return;
    } else {
       // fatal error
    }
  }
  if( parse == 2 )
  {
    if(( now_a == 1 ) && (now_b == 0 )) // reverse = CCW
    {
      rot_count--;
      direction= 0;    //CCW
      parse = 1;
      return;
    } else if (( now_a == 0 ) && ( now_b == 1)) //foward = CW
    {
        rot_count++;
        direction = 1;    // CW
        parse = 3;
        return;
    } else {
       // fatal error
    }
  }
  if( parse == 3 )
  {
    if(( now_a == 1 ) && (now_b == 1 )) // reverse = CCW
    {
      rot_count--;
      direction= 0;    //CCW
      parse = 2;
      return;
    } else if (( now_a == 0 ) && ( now_b == 0)) //foward = CW
    {
        rot_count++;
        direction = 1;    // CW
        parse = 0;
        return;
    } else {
       // fatal error
    }
  }
}