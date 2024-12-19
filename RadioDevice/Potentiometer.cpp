#include "Potentiometer.h"
Potentiometer::Potentiometer() : head(0), tail(0) {}
void Potentiometer::poll() {
    Serial.println(analogRead(A0));
}
