#include <cstddef>
#include "SinglyLinkedListInt.h"

SinglyLinkedListInt::SinglyLinkedListInt()      // Constructor to initialize member variables
{
    head = NULL;
    tail = NULL;
    size = 0;
}

SinglyLinkedListInt::~SinglyLinkedListInt()    // Destructor to clean up resources
{
    clear();
}

void SinglyLinkedListInt::insertLast(int value)   // Insert a new value at the end of the list  
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

int SinglyLinkedListInt::removeValue(int value)     // Remove the first occurrence of the specified value from the list, returning 1 if removed and 0 if not found
{
    Node *current = head;
    Node *previous = NULL;

    while (current != NULL)
    {
        if (current->value == value)
        {
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            if (current == tail)
            {
                tail = previous;
            }

            delete current;
            size--;
            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

int SinglyLinkedListInt::contains(int value) const     // Check if the list contains the specified value, returning 1 if found and 0 if not found
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->value == value)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void SinglyLinkedListInt::print() const     // Print the contents of the list to the console
{
    Node *current = head;
    if (current == NULL)
    {
        cout << "(empty)";
    }

    while (current != NULL)
    {
        cout << current->value;
        if (current->next != NULL)
        {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << endl;
}

void SinglyLinkedListInt::clear()      // Clear the list and free all resources
{
    Node *current = head;
    Node *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = NULL;
    tail = NULL;
    size = 0;
}

SinglyLinkedListInt::Node *SinglyLinkedListInt::getHead() const       // Get the head node of the list
{
    return head;
}

int SinglyLinkedListInt::getSize() const        // Get the current size of the list
{
    return size;
}