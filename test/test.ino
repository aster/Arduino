#include <avr/sleep.h>
#define SW PB3
#define LED PB4

void setup()
{
    DDRB = (1 << LED);   //LEDを出力
    PORTB = ~(1 << LED); //LEDをLOW その他をプルアップ

    //interrupt settings
    GIMSK = 0x20; //PCIE -> 1
    PCMSK = 0x8;  //PCINT3 -> 1
    sei();
}

ISR(PCINT0_vect)
{
}

void loop()
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    sleep_disable();

    //PORTB |= (_BV(LED));
    _delay_ms(3000);
    //PORTB &= ~(_BV(LED));

    /*
    if (!(PINB & _BV(SW)))
    {
        PORTB |= (1 << LED);
    }
    else
    {
        PORTB &= ~(1 << LED);
    } 
    */

    //PINB = (1 << LED);
}

void delay_us(short us)
{
}