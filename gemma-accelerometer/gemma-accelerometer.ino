// https://github.com/evilmachina/TinyLSM303
#include <Adafruit_TinyLSM303.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 1);
Adafruit_TinyLSM303 lsm;


void setup() {
  lsm.begin();
  
  strip.begin();
  strip.show();
}



void loop() {
  lsm.read();
   
  int x = abs(lsm.accelData.x);
  int y = abs(lsm.accelData.y);
  int z = abs(lsm.accelData.z);

  int r = map(x, 0, 32768, 0, 255);
  int g = map(y, 0, 32768, 0, 255);
  int b = map(z, 0, 32768, 0, 255);

  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();

  delay(10);
}


