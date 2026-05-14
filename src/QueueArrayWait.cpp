#include <iostream>
#include "QueueArrayWait.h"

// Constructor: Initialize queue with empty state and no allocated memory
QueueArrayWait::QueueArrayWait()
{
    data = NULL;
    capacity = 0;
    size = 0;
    front = 0;
    rear = -1;
}

// Destructor: Clean up allocated memory when queue is destroyed
QueueArrayWait::~QueueArrayWait()
{
    clear();
}

// Initialize queue: Allocate memory and set capacity for queue operations
void QueueArrayWait::init(int capacityValue)
{
    clear();

    capacity = capacityValue;
    if (capacity > 0)
    {
        data = new WaitRequest[capacity];
    }

    size = 0;
    front = 0;
    rear = -1;
}

// Enqueue: Add new wait request to rear of queue using circular array logic
int QueueArrayWait::enQueue(const WaitRequest &value)
{
    if (isFull())
    {
        return 0;
    }

    rear = (rear + 1) % capacity;
    data[rear] = value;
    size++;
    return 1;
}

// Dequeue: Remove and return wait request from front of queue
int QueueArrayWait::deQueue(WaitRequest &outValue)
{
    if (isEmpty())
    {
        return 0;
    }

    outValue = data[front];
    front = (front + 1) % capacity;
    size--;

    if (size == 0)
    {
        front = 0;
        rear = -1;
    }

    return 1;
}

// Peek: View front element without removing it from queue
int QueueArrayWait::peek(WaitRequest &outValue) const
{
    if (isEmpty())
    {
        return 0;
    }

    outValue = data[front];
    return 1;
}

// Check if queue is empty
int QueueArrayWait::isEmpty() const
{
    return size == 0;
}

// Check if queue has reached its maximum capacity
int QueueArrayWait::isFull() const
{
    return size == capacity;
}

// Print: Display all wait requests in queue from front to rear
void QueueArrayWait::print() const
{
    int i;
    int index;

    if (isEmpty())
    {
        cout << "(empty)" << endl;
        return;
    }

    for (i = 0; i < size; i++)
    {
        index = (front + i) % capacity;
        cout << data[index].name << " (" << data[index].seatsRequested << " seats)" << endl;
    }
}

// Clear: Deallocate memory and reset queue to initial empty state
void QueueArrayWait::clear()
{
    if (data != NULL)
    {
        delete[] data;
        data = NULL;
    }

    capacity = 0;
    size = 0;
    front = 0;
    rear = -1;
}

// Get the current number of wait requests in queue
int QueueArrayWait::getSize() const
{
    return size;
}

// Get the array index of the front element
int QueueArrayWait::getFrontIndex() const
{
    return front;
}

// Get the array index of the rear element
int QueueArrayWait::getRearIndex() const
{
    return rear;
}
