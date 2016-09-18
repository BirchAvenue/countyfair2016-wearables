// https://github.com/evilmachina/TinyLSM303
#include <Adafruit_TinyLSM303.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 1);
Adafruit_TinyLSM303 lsm;

#define THRESHOLD_TILT  1000

int start_x = 0;
int start_y = 0;
int start_z = 0;


void setup() {
  lsm.begin();

  start_x = abs(lsm.accelData.x);
  start_y = abs(lsm.accelData.y);
  start_z = abs(lsm.accelData.z);
  
  strip.begin();
  strip.show();
}



void loop() {
  lsm.read();
   
  int x = abs(lsm.accelData.x);
  int y = abs(lsm.accelData.y);
  int z = abs(lsm.accelData.z);

  int diff_x = abs(start_x-x);
  int diff_y = abs(start_y-y);
  int diff_z = abs(start_z-z);

  bool neopixel_on = false;
  if(diff_x>THRESHOLD_TILT)
    neopixel_on = true;

  if(diff_y>THRESHOLD_TILT)
    neopixel_on = true;

//  if(diff_z>THRESHOLD_TILT)
//    neopixel_on = true;
  
  int r = map(x, 0, 32768, 0, 255);
  int g = map(y, 0, 32768, 0, 255);
  int b = map(z, 0, 32768, 0, 255);

  if(neopixel_on)
    strip.setPixelColor(0, strip.Color(r, g, b));
  else
    strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();

  delay(10);
}


