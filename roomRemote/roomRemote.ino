#define receivePin 6 //receiver -> TSOP4838
#define SW 8
#define PIN_NAME PD7

void setup()
{
    pinMode(receivePin, INPUT);
    pinMode(7, OUTPUT);
    Serial.begin(9600);
}

long onSignal = 8061411525;
long offSignal = 8347845;

void loop()
{
    delay(5000);
    lightSet(1);
    delay(5000);
    lightSet(0);
}

void startSignal()
{
    //3.2ms -> on  and  1.6ms -> off
    PORTD |= _BV(PIN_NAME); //on
    delayMicroseconds(3200);

    PORTD &= ~_BV(PIN_NAME); //off
    delayMicroseconds(1600);
}

void signalA()
{
    //0.4ms -> on  and  1.2ms -> off
    PORTD |= _BV(PIN_NAME); //on
    delayMicroseconds(400);

    PORTD &= ~_BV(PIN_NAME); //off
    delayMicroseconds(1200);
}

void signalB()
{
    //0.4ms -> on  and  0.4ms -> off
    PORTD |= _BV(PIN_NAME); //on
    delayMicroseconds(400);

    PORTD &= ~_BV(PIN_NAME); //off
    delayMicroseconds(400);
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
            Serial.print('A');
            signalA();
        }
        else
        {
            Serial.print('B');
            signalB();
        }
    }
    Serial.println(' ');
}
