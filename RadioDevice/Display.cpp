#include <Arduino.h>
#include "Display.h"

Display::Display(){}

void Display::init()
{
  Serial.begin(9600);
  Serial.println("Display initialized");
}

void Display::refresh()
{
  Serial.println("Display refreshed");
}