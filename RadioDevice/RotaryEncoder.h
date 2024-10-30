#include <Arduino.h>

class RotaryEncoder {
public:
    // Constructor that takes the pins connected to the RotaryEncoder
    RotaryEncoder(uint8_t pinA, uint8_t pinB, void (*interruptEvent)());

    // Initialize the RotaryEncoder and attach interrupts
    void begin();

    // Get the current position of the RotaryEncoder
    int32_t getPosition();

    // Reset the RotaryEncoder position to zero
    void reset();

    // Update method to be called by the interrupt service routine (ISR)
    void update();

private:
    uint8_t pinA, pinB;    // RotaryEncoder pins
	void (*interruptEvent)();
    volatile int32_t position; // Current position
    volatile int8_t lastState; // Last state of the RotaryEncoder

    // Static instance pointer to allow ISR access
    static RotaryEncoder* instance;
};