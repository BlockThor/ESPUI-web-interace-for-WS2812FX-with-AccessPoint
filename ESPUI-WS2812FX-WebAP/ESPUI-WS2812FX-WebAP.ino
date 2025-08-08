#include "defs.h"

void setup() {
  Lamp_StartUp();
  WiFi_StartUp();
  WebUI_StartUp();
}

void loop() {
  WiFi_Running();
  Lamp_Running();
}
