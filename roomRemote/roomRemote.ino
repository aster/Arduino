#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <avr/sleep.h>

#define Model "ATtiny85"
#define SW PB3
#define LED PB4

void setup()
{

    //pin settings
    DDRB = (1 << LED);   //LEDを出力
    PORTB = ~(1 << LED); //LEDをLOWに その他をプルアップ(SW)

    //interrupt settings
    GIMSK = 0x20; //PCIE -> enable
    PCMSK = 0x8;  //PCINT3 -> set interrupt pin
    sei();        //whole permmit interrupt

    TCNT1 = 0;

    TinyWireM.begin(); // i2cの初期化、マスターとする
    delay(1000);
}

long onSignal = 8061411525;
long offSignal = 8347845;
short margin_us = 40;
short margin_delay = 0;

void loop()
{
    //sleep settings
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    sleep_disable();

    //main process
    delay(10);             //チャタリング対策
    if (!(PINB & _BV(SW))) //ピン変化割り込み時,押下のみ実行
    {
        //lightSet(1);
        //delay(2000);
        lightSet(0);
        delay(2000);
    }

    //i2c serial print
    static int num = 0;
    char sbuf[40];

    sprintf(sbuf, "TinyWireM num=%d model=%s\n", num, Model);
    num++;
    i2c_print(sbuf);
}

void startSignal()
{
    //3.2ms -> on  and  1.6ms -> off
    pwmOn();
    my_delay_us(3200);
    pwmOff();
    my_delay_us(1550);
}

void signalA()
{
    //0.4ms -> on  and  1.2ms -> off
    pwmOn();
    //delayMicroseconds(400 + margin_delay);
    my_delay_us(350);

    pwmOff();
    //delayMicroseconds(1227 - margin_us);
    my_delay_us(1150);
}

void signalB()
{
    //0.4ms -> on  and  0.4ms -> off
    pwmOn();
    //delayMicroseconds(400 + margin_delay);
    my_delay_us(350);

    pwmOff();
    //delayMicroseconds(429 - margin_us);
    my_delay_us(350);
}

//light on  onflag == 1
void lightSet(short onFlag)
{
    startSignal();
    long signalPattern = onFlag ? onSignal : offSignal;

    for (short i = 0; i < 33; i++)
    {
        if (bitRead(signalPattern, i))
        {
            signalA();
        }
        else
        {
            signalB();
        }
    }
}

void pwmOn()
{
    PORTB |= _BV(LED);
    TCCR1 = 0b10000100;
    GTCCR = 0b01100000;
    OCR1C = 25;
    OCR1B = 7;
}

void pwmOff()
{
    PORTB &= ~_BV(LED);
    GTCCR = 0;
    TCNT1 = 0;
}

//1MHz -> 64us 分解能
void my_delay_us(short d_time)
{
    short start_time = micros();
    short now_time = start_time;

    while (now_time - start_time < d_time){
        now_time = micros();
    }
    start_time = now_time = 0;

}

ISR(PCINT0_vect)
{
}

// 最大10文字にデータを分割してデータの送信
void i2c_print(char *str)
{
    int pnum;
    int jmax;
    pnum = (strlen(str) + 9) / 10; //パケット数
    for (int i = 0; i < pnum; i++)
    {
        jmax = i * 10 + 10;
        if (strlen(str) < jmax)
            jmax = strlen(str);
        TinyWireM.beginTransmission(8); // 通信の開始処理、スレーブのアドレスは８とする
        for (int j = i * 10; j < jmax; j++)
        {                           // 1パケットの最大文字数は10文字
            TinyWireM.send(str[j]); // 通信データ送信
        }
        TinyWireM.send(0); // 通信データ送信(終端文字)
        TinyWireM.endTransmission();
    }
}