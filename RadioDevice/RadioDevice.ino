#include "EventQueue.h"
#include "Potentiometer.h"
#include "RotaryEncoder.h"
#include "Tuner.h"
#include "Display.h"
bool channelChangeTriggered = false;
void event2() {
    Serial.println("Event 2 executed");
    digitalWrite(13,HIGH);
}

Potentiometer audioVolume;
EventQueue eventQueue;
RotaryEncoder channelFrequency(8,9,event2);
Tuner tuner;
Display displayObj;

struct {
  int volume;
  int frequency;
}Radio;

ISR (TIMER1_OVF_vect) {
    eventQueue.addEvent(event1);
    TCNT1 = 647550; // 50 ms for 16MHz clock
}
ISR (PCINT0_vect)
{
  if(!channelChangeTriggered){
    if(digitalRead(8)==HIGH && digitalRead(9)==LOW){
      eventQueue.addEvent(changeChannelUp);
    }else if(digitalRead(8)==LOW && digitalRead(9)==HIGH){
      eventQueue.addEvent(changeChannelDown);
    }
    
    channelChangeTriggered = true;
  }
  
}
void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  // Enable PCIE2 Bit3 = 1 (Port D)
  PCICR |= B00000001;
  // Select PCINT23 Bit7 = 1 (Pin D7)
  PCMSK0 |= B00000011;
  
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
    displayObj.init();
}

void event1() {
    Serial.println("Event 1 executed");
    channelChangeTriggered = false;
    //Serial.println(digitalRead(8));
    audioVolume.poll();
    if(map(analogRead(A1),0,1024,0,15) != Radio.volume){
       Radio.volume = map(analogRead(A1),0,1024,0,15);
       tuner.setVolume(Radio.volume);
       eventQueue.addEvent(displayRefresh);
    }
    

}

void displayRefresh() {
    displayObj.refresh();
}
void changeChannelUp() {

      tuner.seekUp();
eventQueue.addEvent(displayRefresh);
    
}
void changeChannelDown() {

      tuner.seekDown();  
    eventQueue.addEvent(displayRefresh);
    
}


void loop() {
    eventQueue.scheduler();  // Continuously handle events in the queue
}
