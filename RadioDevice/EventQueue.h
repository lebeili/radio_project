#include <Arduino.h>

#define MAX_QUEUE_SIZE 10

typedef void (*EventCallback)();  // Define a function pointer type for events

class EventQueue {
public:
    EventQueue(); // Constructor

    bool addEvent(EventCallback event); // Add an event to the queue
    void dispatch();                    // Dispatch the first event in the queue
    void scheduler();                   // Scheduler to handle events in queue

private:
    EventCallback eventQueue[MAX_QUEUE_SIZE]; // Array of function pointers for the queue
    int head;  // Index of the front of the queue
    int tail;  // Index of the rear of the queue
    bool isEmpty();  // Check if the queue is empty
    bool isFull();   // Check if the queue is full
};


