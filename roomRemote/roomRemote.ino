#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <avr/sleep.h>

#define Model "ATtiny85"
#define SW PB3
#define LED PB4
#define WLED PB1

void setup()
{

    //pin settings
    DDRB = (1 << LED) | (1 << WLED);     //LEDを出力
    PORTB = ~((1 << LED) | (1 << WLED)); //LEDをLOWに その他をプルアップ(SW)

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
short setFlag = 0; //turn on -> 1
char sbuf[40];
short i = 0;

void loop()
{
    //sleep settings
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    sleep_disable();

    //main process
    delay(10);             //チャタリング対策
    if(!setFlag)PORTB |= (1 << WLED);  //WLEDをHIGHに
    if (!(PINB & _BV(SW))) //ピン変化割り込み時,押下のみ実行
    {
        setFlag ^= 1;

        while (!(PINB & _BV(SW)))
        {
            lightSet(setFlag);
            delay(60);
        }
    }

    PORTB &= ~(1 << WLED); //WLEDをLOWに
    /*
    //i2c serial print
    sprintf(sbuf, "TinyWireM num=%d model=%s\n", num, Model);
    i2c_print(sbuf);
    */
}

short blink_margin = 70;

void startSignal()
{
    //3.2ms -> on  and  1.6ms -> off

    pwmOn();
    my_delay_us(3200 + blink_margin);
    pwmOff();
    my_delay_us(1600 - blink_margin);
}

void signalA()
{
    //0.4ms -> on  and  1.2ms -> off
    pwmOn();
    my_delay_us(400 + blink_margin);

    pwmOff();
    my_delay_us(1200 - blink_margin);
}

void signalB()
{
    //0.4ms -> on  and  0.4ms -> off
    pwmOn();
    my_delay_us(400 + blink_margin);

    pwmOff();
    my_delay_us(400 - blink_margin);
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

void my_delay_us(unsigned long d_time)
{
    unsigned long start_time = micros();
    while (micros() - start_time < d_time)
    {
    };

    //debug
    //i2c serial print
    //sprintf(sbuf, "%d\n", micros()- start_time;
    //i2c_print(sbuf);
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