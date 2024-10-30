#include "EventQueue.h"

EventQueue::EventQueue() : head(0), tail(0) {}

// Check if the queue is empty
bool EventQueue::isEmpty() {
    return head == tail;
}

// Check if the queue is full
bool EventQueue::isFull() {
    return (tail + 1) % MAX_QUEUE_SIZE == head;
}

// Add an event to the queue
bool EventQueue::addEvent(EventCallback event) {
    if (isFull()) {
        return false;  // Queue is full
    }
    eventQueue[tail] = event;
    tail = (tail + 1) % MAX_QUEUE_SIZE;
    return true;
}

// Dispatch the first event in the queue
void EventQueue::dispatch() {
    if (!isEmpty()) {
        EventCallback event = eventQueue[head];
        head = (head + 1) % MAX_QUEUE_SIZE;
        if (event) {
            event();  // Execute the event function
        }
    }
}

// Scheduler to handle events in the queue
void EventQueue::scheduler() {
    while (!isEmpty()) {
        dispatch();
    }
}
