#include "EventQueue.h"
#include "Potentiometer.h"
#include "RotaryEncoder.h"
#include "Tuner.h"

void event2() {
    Serial.println("Event 2 executed");
    digitalWrite(13,HIGH);
}

Potentiometer audioVolume;
EventQueue eventQueue;
RotaryEncoder channelFrequency(8,9,event2);
Tuner tuner;

struct {
  int volume;
}Radio;

ISR (TIMER1_OVF_vect) {
    eventQueue.addEvent(event1);
    TCNT1 = 647550; // 50 ms for 16MHz clock
}

void setup() {
  Serial.begin(9600);
  
  Radio.volume = 1;
    // Set 5th data direction register of PORTB. A set value means output
    DDRB = (1 << DDB5);
    // 50 ms for 16MHz clock
    TCNT1 = 64755;
    // Set normal counter mode
    TCCR1A = 0x00;
    // Set 1024 pre-scaler
    TCCR1B = (1<<CS10) | (1<<CS12);
    // Set overflow interrupt enable bit
    TIMSK1 = (1 << TOIE1); 
    sei(); // Enable interrupts globally
    tuner.init();
}

void event1() {
    Serial.println("Event 1 executed");
    //Serial.println(digitalRead(8));
    audioVolume.poll();
    if(map(analogRead(A1),0,1024,0,15) != Radio.volume){
       Radio.volume = map(analogRead(A1),0,1024,0,15);
       tuner.setVolume(Radio.volume);
    }
    
    if(digitalRead(7)==HIGH){
      tuner.seekUp();  
    }
    //delay(1000);
}


void loop() {
    eventQueue.scheduler();  // Continuously handle events in the queue
}
