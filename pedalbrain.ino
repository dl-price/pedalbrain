#include "PBController.h"

void setup() {
  // put your setup code here, to run once:

  PBController::getInstance()->setup();
}

void loop() {
  // put your main code here, to run repeatedly:

  PBController::getInstance()->loop();
}
