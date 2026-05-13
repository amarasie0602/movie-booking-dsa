#include <cstddef>
#include "HashTableIntToIndex.h"

HashTableIntToIndex::HashTableIntToIndex() 
{
    buckets = NULL;
    bucketCount = 0;
    size = 0;
}

// Destructor to clean up resources
HashTableIntToIndex::~HashTableIntToIndex()
{
    clear();
}

// Initialize the hash table with a specified number of buckets
void HashTableIntToIndex::init(int bucketCountValue)
{
    clear();

    // Ensure bucketCountValue is positive
    bucketCount = bucketCountValue;
    if (bucketCount > 0)
    {
        buckets = new Node *[bucketCount];
        for (int i = 0; i < bucketCount; i++)
        {
            buckets[i] = NULL;
        }
    }

    size = 0;
}

// Add or update a key-index pair in the hash table
void HashTableIntToIndex::put(int key, int index)
{
    if (buckets == NULL || bucketCount == 0)
    {
        return;
    }

    // Calculate the bucket index using the hash function
    int bucketIndex = hash(key);
    Node *current = buckets[bucketIndex];

    while (current != NULL)
    {
        if (current->key == key)
        {
            current->index = index;
            return;
        }
        current = current->next;
    }

    // If the key does not exist, create a new node and add it to the bucket
    Node *newNode = new Node;
    newNode->key = key;
    newNode->index = index;
    newNode->next = buckets[bucketIndex];
    buckets[bucketIndex] = newNode;
    size++;
}

// Retrieve the index associated with a key, returning 1 if found and 0 if not found
int HashTableIntToIndex::get(int key, int &outIndex) const
{
    if (buckets == NULL || bucketCount == 0)
    {
        return 0;
    }

    // Calculate the bucket index using the hash function
    int bucketIndex = hash(key);
    Node *current = buckets[bucketIndex];

    while (current != NULL)
    {
        if (current->key == key)
        {
            outIndex = current->index;
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// Remove a key-index pair from the hash table, returning 1 if removed and 0 if not found
int HashTableIntToIndex::remove(int key)
{
    if (buckets == NULL || bucketCount == 0)
    {
        return 0;
    }

    int bucketIndex = hash(key);
    Node *current = buckets[bucketIndex];
    Node *previous = NULL;

    while (current != NULL)
    {
        if (current->key == key)
        {
            if (previous == NULL)
            {
                buckets[bucketIndex] = current->next;
            }
            else
            {
                previous->next = current->next;
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

// Clear the hash table and free all resources
void HashTableIntToIndex::clear()
{
    if (buckets == NULL)
    {
        bucketCount = 0;
        size = 0;
        return;
    }

    for (int i = 0; i < bucketCount; i++)  // Iterate through each bucket
    {
        Node *current = buckets[i];
        Node *nextNode;

        while (current != NULL)
        {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Free the array of bucket pointers
    delete[] buckets;
    buckets = NULL;
    bucketCount = 0;
    size = 0;
}

int HashTableIntToIndex::getSize() const    // Return the number of key-index pairs currently stored in the hash table
{
    return size;
}

int HashTableIntToIndex::hash(int key) const    // Compute the hash value for a given key, ensuring it is non-negative and within the bounds of the bucket count
{
    if (key < 0)
    {
        key = -key;
    }
    return key % bucketCount;
}