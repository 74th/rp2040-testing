#include <Arduino.h>

#define APP_BLINK 0
#define APP_INPUT_PULLUP 1
#define APP_NEOPIXEL 2
#define APP_SELECT APP_NEOPIXEL
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels(1, 24, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
#if APP_SELECT == APP_BLINK
    pinMode(24, OUTPUT);
    pinMode(25, OUTPUT);
#elif APP_SELECT == APP_INPUT_PULLUP
    pinMode(23, INPUT_PULLUP);
    pinMode(24, INPUT_PULLUP);
#elif APP_SELECT == APP_NEOPIXEL
    pinMode(25, OUTPUT);
    pixels.begin();
#endif
}

void loop_blink()
{
    digitalWrite(24, HIGH);
    digitalWrite(25, HIGH);
    Serial.println("H");
    delay(1000);

    digitalWrite(24, LOW);
    digitalWrite(25, LOW);
    Serial.println("L");
    delay(1000);
}

void loop_input_pullup()
{
    auto g23 = digitalRead(23);
    auto g24 = digitalRead(24);
    Serial.print("G23: ");
    Serial.print(g23);
    Serial.print(", G24: ");
    Serial.print(g24);
    Serial.println();

    delay(1000);
}

void loop_neopixel()
{
    pixels.clear();
    for (int i = 0; i < 1; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 150, 0));

        pixels.show();

        delay(500);
    }
}

void loop()
{
#if APP_SELECT == APP_BLINK
    loop_blink();
#elif APP_SELECT == APP_INPUT_PULLUP
    loop_input_pullup();
#elif APP_SELECT == APP_NEOPIXEL
    loop_neopixel();
#endif
}