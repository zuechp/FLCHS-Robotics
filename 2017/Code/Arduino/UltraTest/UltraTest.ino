#include "Ultrasonic.h"
// one sensor - trig 12, echo 13
Ultrasonic ultra1(12, 13);
// another sensor - trig 10, echo 11
Ultrasonic ultra2(10,11);

int range1;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  Serial.print(ultra1.Ranging(CM));
  Serial.print(' ');
  Serial.print(ultra2.Ranging(CM));
  Serial.println(' ');
  delay(100);
}
