#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 1, NEO_GRB + NEO_KHZ800);

#include <Adafruit_TCS34725.h>
// https://learn.adafruit.com/adafruit-color-sensors/program-it
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup() {
  tcs.begin();
  strip.begin();
  strip.show();
}

void loop(void) {
  doSensor();
  delay(10000);
}


void doSensor() {
  uint16_t clear, red, green, blue;

  // Turn on sensor LED
  tcs.setInterrupt(false);

  // Wait for sensor to read
  delay(800);

  // Get data from sensor
  tcs.getRawData(&red, &green, &blue, &clear);

  // Turn off sensor LED
  tcs.setInterrupt(true);

  // Math
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  // Display on NeoPixel
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}

