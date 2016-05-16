#include <Stepper.h>

Stepper racloir(48,2,3,4,5);

void setup() {
  // put your setup code here, to run once:
  racloir.setSpeed(1.2);
}

void loop() {
  // put your main code here, to run repeatedly:
  racloir.step(12);
  delay(500);
  racloir.step(-12);
  delay(500);
}
