#include <Arduino.h>
#include <Si4703_Breakout.h>
#include <Wire.h>

class Tuner {
public:
	Tuner(); // Constructor
    void init();
	void setChannel(int channel);  	// 3 digit channel number
	int seekUp(); 					// returns the tuned channel or 0
	int seekDown(); 				
	void setVolume(int volume); 	// 0 to 15
	void readRDS(char* message, long timeout);	
private:
    Si4703_Breakout radio;

};


