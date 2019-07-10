#include <avr/sleep.h>
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
}

long onSignal = 8061411525;
long offSignal = 8347845;

void loop()
{
    //sleep settings
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    sleep_disable();

    //main process
    _delay_ms(10);         //チャタリング対策
    if (!(PINB & _BV(SW))) //ピン変化割り込み時,押下のみ実行
    {
        //memo 押しっぱなしでループ＆信号は１回だけ出すようにする
        delay(5000);
        lightSet(1);
        delay(5000);
        lightSet(0);
    }
}

void startSignal()
{
    //3.2ms -> on  and  1.6ms -> off
    pwmOn();
    _delay_us(3200);
    pwmOff();
    _delay_us(1600);
}

void signalA()
{
    //0.4ms -> on  and  1.2ms -> off
    pwmOn();
    _delay_us(400);

    pwmOff();
    _delay_us(1200);
}

void signalB()
{
    //0.4ms -> on  and  0.4ms -> off
    pwmOn();
    _delay_us(400);

    pwmOff();
    _delay_us(400);
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
    TCCR1 = 0b10000011;
    GTCCR = 0b01100000;
    OCR1C = 54;
    OCR1B = 12;
}

void pwmOff()
{
    PORTB &= ~_BV(LED);
    GTCCR = 0;
    TCNT1 = 0;
}

ISR(PCINT0_vect)
{
}