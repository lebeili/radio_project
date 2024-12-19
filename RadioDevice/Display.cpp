#include <Arduino.h>
#include "Display.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// pin definition for the Uno
#define TFT_CS   7
#define TFT_DC   5
#define TFT_RST  4
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
int channel = 1;           // Current channel
String currentSong = "Imagine - John Lennon"; // Example song name
// Colors for easy reference
#define BLACK     ST77XX_BLACK
#define WHITE     ST77XX_WHITE
#define RED       ST77XX_RED
#define GREEN     ST77XX_GREEN
#define BLUE      ST77XX_BLUE
#define CYAN      ST77XX_CYAN
#define YELLOW    ST77XX_YELLOW




Display::Display(){}

void Display::init()
{

  tft.initR(INITR_BLACKTAB);  // Initialize the display
  tft.setRotation(1);        // Landscape mode
  tft.fillScreen(BLACK);     // Clear screen with black

  drawGUI();  // Initial GUI layout
  Serial.println("Display initialized");
}
void Display::drawGUI() {
  // Draw header section
  tft.fillRect(0, 0, 160, 26, BLUE);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.print("Now Playing:");

  // Draw main info section
  tft.fillRect(0, 26, 160, 80, BLACK);
  tft.drawRect(0, 26, 160, 80, WHITE);

  // Draw status section
  tft.fillRect(0, 100, 160, 28, BLACK);
  tft.drawRect(0, 100, 160, 28, WHITE);

  // Labels
  tft.setCursor(10, 105);
  tft.setTextSize(1);
  tft.setTextColor(YELLOW);
  tft.print("Vol:");
}

void Display::updateHeader(String text) {
  // Clear the previous song name area
  tft.fillRect(80, 5, 80, 10, BLUE);
  tft.fillRect(1, 13, 75, 8, BLUE);

  // Display the new song name
  tft.setCursor(80, 5);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.print(text);
}

void Display::updateMainInfo(float frequency, String channel) {
  // Clear previous main info
  tft.fillRect(5, 28, 150, 70, BLACK);

  // Display Channel
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.setCursor(10, 40);
  tft.print("CH:");
  tft.setCursor(50, 40);
  tft.print(channel);

  // Display Frequency
  tft.setTextSize(2);
  tft.setCursor(10, 70);
  tft.print(frequency, 1); // One decimal place
  tft.print(" MHz");
}

void Display::updateStatus(int volume) {
  // Clear volume info
  tft.fillRect(40, 105, 30, 10, BLACK);

  // Display Volume
  tft.setCursor(40, 105);
  tft.setTextColor(GREEN);
  tft.setTextSize(1);
  tft.print(volume);
  tft.print("%");
}
