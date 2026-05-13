#ifndef HASHTABLEINTTOINDEX_H
#define HASHTABLEINTTOINDEX_H

class HashTableIntToIndex  // Hash table mapping integer keys to integer indices
{
private:
    struct Node
    {
        int key;
        int index;
        Node *next;
    };

    Node **buckets;
    int bucketCount;
    int size;

    int hash(int key) const;

public:
    HashTableIntToIndex();
    ~HashTableIntToIndex();

    void init(int bucketCountValue);    // Initialize the hash table with a specified number of buckets
    void put(int key, int index);       // Add or update a key-index pair in the hash table
    int get(int key, int &outIndex) const;    // Retrieve the index associated with a key, returning 1 if found and 0 if not found
    int remove(int key);                // Remove a key-index pair from the hash table, returning 1 if removed and 0 if not found   
    void clear();                       // Clear the hash table and free all resources

    int getSize() const;
};

#endif