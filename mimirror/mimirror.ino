#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 3
#define SW 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined(__AVR_ATtiny85__)
    if (F_CPU == 16000000)
        clock_prescale_set(clock_div_1);
#endif
    // End of trinket special code

    pinMode(SW, INPUT_PULLUP);

    strip.begin();
    strip.setBrightness(50); //0~255?
    strip.show();            // Initialize all pixels to 'off'

}

short swFlag = 0;
bool ignoreFlag = true;
short tmpCnt = 0;

void loop()
{
    //on led tape
    onLed(swFlag);

    if (ignoreFlag)
    {
        if (digitalRead(SW) == LOW)
        {
            ignoreFlag = false;
            swFlag++;
            if (swFlag == 3)
                swFlag = 0;
        }
    }
    else
    {
        delay(500);
        ignoreFlag = true;
    }
}

void setAllPixel(short r, short g, short b)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
        strip.show();
    }
}

void onLed(short flag)
{
    switch (flag)
    {
    case 0:
        setAllPixel(0xFF, 0xD6, 0xA1);
        break;
    case 1:
        setAllPixel(0xFF, 0xEB, 0xCD);
        break;
    case 2:
        setAllPixel(0xFF, 0xFF, 0xFF);
        break;
    }
}
