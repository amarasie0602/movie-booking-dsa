#include <cstring>
#include "BSTMovieTitle.h"

BSTMovieTitle::BSTMovieTitle() // Constructor to initialize the BST with default values
{
    root = NULL;
    size = 0;
}

BSTMovieTitle::~BSTMovieTitle() // Destructor to delete all nodes when the BST is destroyed
{
    clear();
}

void BSTMovieTitle::insert(int movieId, const std::string &title)// Insert a new movie into the BST 
{
    Node *newNode = new Node;
    newNode->movieId = movieId;
    newNode->title = title;
    newNode->titleLower = toLower(title); //convert title to lowercase for case-insensitive comparison
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    if (root == NULL)
    {
        root = newNode;
        size++;
        return;
    }

    Node *current = root;
    Node *parentNode = NULL;
    int compareResult = 0;

    while (current != NULL) // Traverse the BST
    {
        parentNode = current;
        if (newNode->titleLower < current->titleLower)
            compareResult = -1;
        else if (newNode->titleLower > current->titleLower)
            compareResult = 1;
        else
            compareResult = 0;

        if (compareResult < 0)
        {
            current = current->left;
        }
        else if (compareResult > 0)
        {
            current = current->right;
        }
        else
        {
            delete newNode; //duplicate title
            return;
        }
    }

    newNode->parent = parentNode;
    if (compareResult < 0)
    {
        parentNode->left = newNode;
    }
    else
    {
        parentNode->right = newNode;
    }

    size++;
}

int BSTMovieTitle::searchExact(const std::string &title) const // Search for a movie with an exact title match
{
    Node *current = root;
    std::string searchTitle = toLower(title);

    while (current != NULL)
    {
        if (searchTitle == current->titleLower)
        {
            return current->movieId;
        }
        if (searchTitle < current->titleLower)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return -1;
}

void BSTMovieTitle::inOrderList(int outIds[], int &count) const //in-order traversal to list all movie IDs
{
    count = 0;
    inOrderFill(root, outIds, count);
}

void BSTMovieTitle::clear() //delete all nodes in the BSST
{
    clearNode(root);
    root = NULL;
    size = 0;
}

int BSTMovieTitle::getSize() const 
{
    return size;
}

void BSTMovieTitle::clearNode(Node *node) 
{
    if (node == NULL)
    {
        return;
    }

    clearNode(node->left);
    clearNode(node->right);
    delete node;
}

void BSTMovieTitle::inOrderFill(Node *node, int outIds[], int &count) const //IN-order traversal to fill the output array with movie IDs
{
    if (node == NULL)
    {
        return;
    }

    inOrderFill(node->left, outIds, count);
    outIds[count] = node->movieId;
    count++;
    inOrderFill(node->right, outIds, count);
}
