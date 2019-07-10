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
        pwmOn();
        _delay_us(200);
        pwmOff();
        _delay_us(200);
        pwmOn();
        _delay_us(200);
        pwmOff();

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