#define PIN_BUTTON 0
#define PIN_PIXEL  6

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN_PIXEL, NEO_GRB + NEO_KHZ800);

#include <Adafruit_TCS34725.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

byte gammatable[256];

int rgb[3] = {0, 0, 0};


void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  
  tcs.begin();
  tcs.setInterrupt(true);

  strip.begin();
  strip.show();

  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    gammatable[i] = x;
  }
}


void loop() {
  bool button_press = digitalRead(PIN_BUTTON);

  if(button_press==1) {
    tcs.setInterrupt(false);
    delay(60);

    uint16_t clear, red, green, blue;
    tcs.getRawData(&red, &green, &blue, &clear);
    
    tcs.setInterrupt(true);

    uint32_t sum = clear;
    float r, g, b;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;

    rgb[0] = gammatable[(int)r];
    rgb[1] = gammatable[(int)g];
    rgb[2] = gammatable[(int)b];
  }

  strip.setPixelColor(0, strip.Color(rgb[0], rgb[1], rgb[2]));
  strip.show();
}
