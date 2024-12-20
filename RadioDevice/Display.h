#include <Arduino.h>

class Display {
	public:
	  Display(); // Constructor
	  void init();
	  void drawGUI();
	  void updateHeader(String text);
	  void updateMainInfo(float frequency, String channel);
	  void updateStatus(int volume);

};


class ST77XXAdapter: public Display {
	public:
	  ST77XXAdapter(): Display(); // Constructor
	  void init();
	  void drawGUI();
	  void updateHeader(String text);
	  void updateMainInfo(float frequency, String channel);
	  void updateStatus(int volume);

};
