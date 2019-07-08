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
    PINB = (1 << LED);
}

void loop()
{
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
    _delay_ms(100);
}

void delay_us(short us)
{
}