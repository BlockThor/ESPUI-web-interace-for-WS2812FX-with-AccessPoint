#include "defs.h"

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  Lamp_StartUp();
  WiFi_StartUp();
  WebUI_StartUp();

}

void loop() {
  WiFi_Running();
  Lamp_Running();
}


// - - - - - - D E L A Y - - - - - -
boolean Delay(int interval) {
  unsigned long prevMillis = millis();
  long currMillis = millis();
  do {
    currMillis = millis();
    yield();
    Lamp_Running();
    yield();
  } while (currMillis - prevMillis < interval);
  return false;
}
