#include <Arduino.h>


class Potentiometer {
public:
    Potentiometer(); // Constructor

    void poll();

private:
    int head;  // Index of the front of the queue
    int tail;  // Index of the rear of the queue

};


