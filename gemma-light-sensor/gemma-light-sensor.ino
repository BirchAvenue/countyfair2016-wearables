#include <Adafruit_TSL2561_U.h>
#include <pgmspace.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

#define THRESHOLD_LUX 1000

void setup() {
  pinMode(1, INPUT);
  
  tsl.begin();
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

void loop() {
  sensors_event_t event;
  tsl.getEvent(&event);

  if(event.light==0)
    return;

  int mapped_lux = map(event.light, 0, THRESHOLD_LUX, 0, 255);
  mapped_lux = 255-mapped_lux;
  analogWrite(1, mapped_lux);
  delay(50);
}
