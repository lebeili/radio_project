#include "RotaryEncoder.h"

// Initialize the static instance pointer
RotaryEncoder* RotaryEncoder::instance = nullptr;

// Constructor: initialize pins and default position
RotaryEncoder::RotaryEncoder(uint8_t pinA, uint8_t pinB, void (*interruptEvent)()) 
    : pinA(pinA), pinB(pinB),interruptEvent(interruptEvent), position(0), lastState(0) {}

// Initialize the RotaryEncoder and set up interrupts
void RotaryEncoder::begin() {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);

    // Set the initial state of the RotaryEncoder based on the pin readings
    lastState = (digitalRead(pinA) << 1) | digitalRead(pinB);

    // Set the instance pointer for ISR access
    instance = this;
	  // Enable PCIE2 Bit3 = 1 (Port D)
	  PCICR |= B00000111;
	  // Enable PCINT18  & PCINT23 (Pins D2 & D7)
	  PCMSK0 |= B11111111;
    // Attach interrupts to the RotaryEncoder pins
    attachInterrupt(digitalPinToInterrupt(pinA), []() { instance->update(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinB), []() { instance->update(); }, CHANGE);
}

// Get the current position
int32_t RotaryEncoder::getPosition() {
    noInterrupts();      // Disable interrupts temporarily to read the position safely
    int32_t pos = position;
    interrupts();        // Re-enable interrupts
    return pos;
}

// Reset the RotaryEncoder position to zero
void RotaryEncoder::reset() {
    noInterrupts();      // Disable interrupts to reset position safely
    position = 0;
    interrupts();        // Re-enable interrupts
}

// Interrupt-based update for the RotaryEncoder position
void RotaryEncoder::update() {
    // Read the current state of the RotaryEncoder pins
    int8_t currentState = (digitalRead(pinA) << 1) | digitalRead(pinB);

    // Determine direction based on state transition
    if ((lastState == 0b00 && currentState == 0b01) ||
        (lastState == 0b01 && currentState == 0b11) ||
        (lastState == 0b11 && currentState == 0b10) ||
        (lastState == 0b10 && currentState == 0b00)) {
        position++;  // Clockwise rotation
    } else if ((lastState == 0b00 && currentState == 0b10) ||
               (lastState == 0b10 && currentState == 0b11) ||
               (lastState == 0b11 && currentState == 0b01) ||
               (lastState == 0b01 && currentState == 0b00)) {
        position--;  // Counter-clockwise rotation
    }

    lastState = currentState;  // Update last state
	Serial.println("test");
	interruptEvent();
}