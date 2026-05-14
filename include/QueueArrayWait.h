#ifndef QUEUEARRAYWAIT_H
#define QUEUEARRAYWAIT_H

#include <iostream>
using namespace std;

#include "WaitRequest.h"

class QueueArrayWait
{
private:
    WaitRequest *data;
    int capacity;
    int size;
    int front;
    int rear;

public:
    // Constructor: Initialize queue with empty state and no allocated memory
    QueueArrayWait();
    // Destructor: Clean up allocated memory when queue is destroyed
    ~QueueArrayWait();

    // Initialize queue: Allocate memory and set capacity for queue operations
    void init(int capacityValue);
    // Enqueue: Add new wait request to rear of queue using circular array logic
    int enQueue(const WaitRequest &value);
    // Dequeue: Remove and return wait request from front of queue
    int deQueue(WaitRequest &outValue);
    // Peek: View front element without removing it from queue
    int peek(WaitRequest &outValue) const;
    // Check if queue is empty
    int isEmpty() const;
    // Check if queue has reached its maximum capacity
    int isFull() const;
    // Print: Display all wait requests in queue from front to rear
    void print() const;
    // Clear: Deallocate memory and reset queue to initial empty state
    void clear();

    // Get the current number of wait requests in queue
    int getSize() const;
    // Get the array index of the front element
    int getFrontIndex() const;
    // Get the array index of the rear element
    int getRearIndex() const;
};

#endif
