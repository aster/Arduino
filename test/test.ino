#define 

void setup()
{
    pinMode(2, OUTPUT);
}

void loop()
{

    if (digitalRead(3) == LOW)
    {
        digitalWrite(2, HIGH);
    }
    else
    {
        digitalWrite(2, LOW);
    }
}