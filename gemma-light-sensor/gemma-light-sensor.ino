#include <Adafruit_TSL2561_U.h>
#include <pgmspace.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

#define THRESHOLD_LUX 70

int buffer_lux[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int buffer_index = 0;

void setup() {
  pinMode(1, INPUT);
  
  tsl.begin();
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

void loop() {
  int lsum = 0, lavg = 0, mapped_lux = 0;
  
  sensors_event_t event;
  tsl.getEvent(&event);
  buffer_lux[buffer_index] = event.light;
  buffer_index++;

  if(buffer_index>9)
    buffer_index = 0;
  
  for(int i=0; i<10; i++)
    lsum += buffer_lux[i];

  lavg = lsum/10;

  if(lavg>THRESHOLD_LUX)
    lavg = THRESHOLD_LUX;

  mapped_lux = map(lavg, 0, THRESHOLD_LUX, 0, 255);
  
  analogWrite(1, 255-mapped_lux);
  delay(10);
}
