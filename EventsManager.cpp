#include "EventsManager.h"
#include "Arduino.h"

EventsManager::EventsManager(){}

EventsManager::init(){
    Serial.begin(115000);
    Serial.println("Events manager initialized!");
}