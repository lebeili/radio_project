#include "EventQueue.h"
#include "Potentiometer.h"
#include "RotaryEncoder.h"
#include "Display.h"
#include <VMA11.h>

int resetPin = 10;
int SDIO = A4;
int SCLK = A5;

VMA11 tuner2(resetPin, SDIO, SCLK);

char rdsname[9]="test";
char rdsrt[65]="testtestets";
char previousRadioText[65];
char previousChannelText[9] = "test";
uint8_t lastChar;

bool channelChangeTriggered = false;

void event2() {
    Serial.println("Event 2 executed");
    digitalWrite(13,HIGH);
}

Potentiometer audioVolume;
EventQueue eventQueue;
RotaryEncoder channelFrequency(8,9,event2);
Display* displayObj;
displayObj = new ST77XXAdapter();

struct {
  int volume;
  int frequency;
} Radio;

ISR (TIMER1_OVF_vect) {
    eventQueue.addEvent(event1);
    TCNT1 = 64750; // 50 ms for 16MHz clock
}

ISR (PCINT0_vect) {
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
  Radio.frequency = 0;
  // Set 5th data direction register of PORTB. A set value means output
  DDRB = (1 << DDB5);
  // 50 ms for 16MHz clock
  TCNT1 = 164755;
  // Set normal counter mode
  TCCR1A = 0x00;
  // Set 1024 pre-scaler
  TCCR1B = (1<<CS10) | (1<<CS12);
  // Set overflow interrupt enable bit
  TIMSK1 = (1 << TOIE1); 
  sei(); // Enable interrupts globally
  //tuner.init();
  tunerInit();
  displayObj.init();
  displayObj.updateMainInfo(Radio.frequency, rdsname);
}
void tunerInit()
{
  Serial.println("\n\nVMA11 Test Sketch");
  Serial.println("===========================");  
  Serial.println("a b     Favourite stations");
  Serial.println("+ -     Volume (max 15)");
  Serial.println("u d     Seek up / down");
  Serial.println("r       Listen for RDS Data (15 sec timeout)");
  Serial.println("R       Listen for RDS Data (15 sec timeout)");
  Serial.println("Send me a command letter.");
  

  tuner2.powerOn();
  tuner2.setVolume(3);
  tuner2.setChannel(1021);

  memset(previousRadioText,0,65);
  memset(rdsrt,0,65);
  memset(previousChannelText,0,9);
  //memset(rdsname,0,65);
}
void event1() {
    
    Serial.println("Event 1 executed");
    channelChangeTriggered = false;
    //Serial.println(digitalRead(8));
    audioVolume.poll();
    if(map(analogRead(A0),0,1024,0,15) != Radio.volume){
       Radio.volume = map(analogRead(A0),0,1024,0,15);
       Serial.println("Volume change");
       tuner2.setVolume(Radio.volume);
       eventQueue.addEvent(displayUpdateStatus);
    }

if(strcmp(rdsname,previousChannelText)) {
eventQueue.addEvent(displayUpdateMainInfo);
strcpy(previousChannelText,rdsname);
}


}

void displayUpdateMainInfo() {
    displayObj.updateMainInfo(Radio.frequency/10, rdsname);
}
void displayUpdateHeader() {
    displayObj.updateHeader(rdsrt);
}
void displayUpdateStatus() {
    displayObj.updateStatus(map(Radio.volume,0,15,0,100));
}
void changeChannelUp() {
    Radio.frequency = tuner2.seekUp();
    eventQueue.addEvent(displayUpdateMainInfo);
    
}
void changeChannelDown() {
    Radio.frequency = tuner2.seekDown();  
    eventQueue.addEvent(displayUpdateMainInfo);
  
}


void loop() {      
  if(tuner2.readRDSRadioText(rdsrt))
      {
    
        if(strcmp(rdsrt,previousRadioText))
          {
             displayUpdateHeader();
            strcpy(previousRadioText,rdsrt);
          }
    
      }  
     tuner2.readRDSRadioStation(rdsname);
    eventQueue.scheduler();  // Continuously handle events in the queue
}
