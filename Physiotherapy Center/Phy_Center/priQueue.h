#pragma once
#include "priNode.h"

template <typename T>
class priQueue {
protected:
    priNode<T>* head;
    int count;

public:
    priQueue() : head(nullptr), count(0) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        count++;

        if (head == nullptr || priority > head->getPri()) {
            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();

        if (temp != nullptr) {
            temp->setNext(nullptr); // Break the link to avoid accidental access
            //delete temp;            // Safely delete the node
            //temp = nullptr;         // Nullify the pointer to prevent dangling
        }

        count--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);  // Fixed - now passing pri parameter
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }
};