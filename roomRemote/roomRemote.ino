#define receivePin 6 //receiver -> TSOP4838
#define test 7

void setup()
{
    pinMode(receivePin, INPUT);
    pinMode(test, OUTPUT);
}

short i = 0;
void loop()
{
    if (i < 10)
        i++;
    else
        i = 0;

    PORTD |= _BV(PD7);
    delayMicroseconds(1);

    PORTD &= ~_BV(PD7);
    delayMicroseconds(i);
}
