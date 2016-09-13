#include <Adafruit_SI1145.h>
Adafruit_SI1145 uv = Adafruit_SI1145();

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 1, NEO_GRB + NEO_KHZ800);

extern const uint8_t gamma8[];

void setup() {
  uv.begin();
  
  strip.begin();
  strip.setBrightness(128);
  strip.show();
}

void loop() {
  int r=0, g=0, b=0;

  float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  

  int UVint = round(UVindex);

  // https://www.epa.gov/sunsafety/uv-index-scale-1
  switch(UVint) {
    // 0-2 low
    case 0:
    case 1:
    case 2:
      g = 255;
      break;
    
    // 3-5 moderate
    case 3:
    case 4:
    case 5:
      r = 255;
      g = 255;
      break;

    // 6-7 high
    case 6:
    case 7:
      r = 255;
      g = 128;
      break;

    // 8-10 very high
    case 8:
    case 9:
    case 10:
      r = 255;
      break;

    // 11+ extreme
    default:
      r = 255;
      b = 255;
      break;
  }

  strip.setPixelColor(0, strip.Color(
    pgm_read_byte(&gamma8[r]),
    pgm_read_byte(&gamma8[g]),
    pgm_read_byte(&gamma8[b])
  ));

  strip.show();
  
  delay(1000);
}


const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};
