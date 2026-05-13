#ifndef SINGLYLINKEDLISTINT_H
#define SINGLYLINKEDLISTINT_H

#include <iostream>
using namespace std;

class SinglyLinkedListInt
{
public:
    struct Node
    {
        int value;
        Node *next;
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    SinglyLinkedListInt();
    ~SinglyLinkedListInt();

    void insertLast(int value);     // Insert a new value at the end of the list
    int removeValue(int value);     // Remove the first occurrence of the specified value from the list, returning 1 if removed and 0 if not found
    int contains(int value) const;  // Check if the list contains the specified value, returning 1 if found and 0 if not found
    void print() const;             // Print the contents of the list to the console
    void clear();                   // Clear the list and free all resources

    Node *getHead() const;         
    int getSize() const;
};

#endif