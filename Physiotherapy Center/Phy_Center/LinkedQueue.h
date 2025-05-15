#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include "QueueADT.h"
#include <iostream>  // For cout in destructor

template <typename T>
class LinkedQueue : public QueueADT<T>
{
protected:
    Node<T>* backPtr;
    Node<T>* frontPtr;
    int count;  // Added member to track size

public:
    LinkedQueue();
    bool isEmpty() const;
    bool enqueue(const T& newEntry);
    bool dequeue(T& frntEntry);
    bool peek(T& frntEntry) const;
    int size() const;  // New function
    ~LinkedQueue();
};

// Constructor
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
    backPtr = nullptr;
    frontPtr = nullptr;
    count = 0;  // Initialize count
}

// isEmpty
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return (frontPtr == nullptr);
}

// enqueue
template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
    Node<T>* newNodePtr = new Node<T>(newEntry);
    if (isEmpty())
        frontPtr = newNodePtr;
    else
        backPtr->setNext(newNodePtr);

    backPtr = newNodePtr;
    count++;  // Increment count
    return true;
}

// dequeue
template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
    if (isEmpty())
        return false;

    Node<T>* nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();

    if (nodeToDeletePtr == backPtr)
        backPtr = nullptr;
    // Safeguard: Set the pointer to nullptr after deletion
  /*  delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;*/
    count--;
    return true;
}


// peek
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
    if (isEmpty())
        return false;

    frntEntry = frontPtr->getItem();
    return true;
}

// size - O(1) version
template <typename T>
int LinkedQueue<T>::size() const
{
    return count;
}

// Destructor
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    T temp;
    while (dequeue(temp));
}

#endif