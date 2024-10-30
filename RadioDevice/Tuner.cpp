#include "Tuner.h"
#include <Arduino.h>
#include <Si4703_Breakout.h>
#include <Wire.h>
Tuner::Tuner():radio(2,A4,A5)
{

}

void Tuner::init()
{

	int channel;
	int volume;
	char rdsBuffer[10];
	  Serial.begin(9600);
  Serial.println("\n\nSi4703_Breakout Test Sketch");
  Serial.println("===========================");  
  Serial.println("a b     Favourite stations");
  Serial.println("+ -     Volume (max 15)");
  Serial.println("u d     Seek up / down");
  Serial.println("r       Listen for RDS Data (15 sec timeout)");
  Serial.println("Send me a command letter.");
  

  radio.powerOn();
  radio.setVolume(0);
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
}