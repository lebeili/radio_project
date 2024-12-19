/*#include "Tuner.h"
#include <Arduino.h>
#include <Si4703_Breakout.h>
//#include <VMA11.h>
#include <Wire.h>
int resetPin = 10;
int SDIO = A4;
int SCLK = A5;
Tuner::Tuner():radio(10,A4,A5)
{

}

void Tuner::init()
{

	int channel;
int volume;
char rdsname[9];
char rdsrt[65];
char previousRadioText[65];
uint8_t lastChar;
  Serial.println("\n\nVMA11 Test Sketch");
  Serial.println("===========================");  
  Serial.println("a b     Favourite stations");
  Serial.println("+ -     Volume (max 15)");
  Serial.println("u d     Seek up / down");
  Serial.println("r       Listen for RDS Data (15 sec timeout)");
  Serial.println("R       Listen for RDS Data (15 sec timeout)");
  Serial.println("Send me a command letter.");
  

  radio.powerOn();
  radio.setVolume(3);
  volume=1;
  radio.setChannel(1021);

  memset(previousRadioText,0,65);
  memset(rdsrt,0,65);
}

void Tuner::setChannel(int channel)
{
	radio.setChannel(channel);
}

int Tuner::seekUp()
{
	radio.seekUp();
}

int Tuner::seekDown()
{
	radio.seekDown();
}

void Tuner::setVolume(int volume)
{
  radio.setVolume(volume);
}*/