#pragma once
#include "LinkedQueue.h"
#include "Patient.h"
class EU_WaitList : public LinkedQueue<Patient*>
{
private:
    int currentTimestep = 0;
public:
    void insertSorted(Patient* patient) {
        if (!patient) return;

        Node<Patient*>* newNode = new Node<Patient*>(patient);

        // Case 1: Empty list or new patient has earlier PT than front
        if (isEmpty() || patient->getAppoinment_Time() < frontPtr->getItem()->getAppoinment_Time()) {
            newNode->setNext(frontPtr);
            frontPtr = newNode;
            if (backPtr == nullptr) backPtr = frontPtr;
            /*itemCount++;*/
            return;
        }

        // Case 2: Find proper position in the list
        Node<Patient*>* current = frontPtr;
        while (current->getNext() != nullptr &&
            current->getNext()->getItem()->getAppoinment_Time() <= patient->getAppoinment_Time()) {
            current = current->getNext();
        }

        // Insert after current node
        newNode->setNext(current->getNext());
        current->setNext(newNode);

        // Update backPtr if inserting at end
        if (newNode->getNext() == nullptr) {
            backPtr = newNode;
        }

        /*itemCount++;*/
    }
    int calcTreatmentLatency() {
        if (isEmpty()) return 0;

        Patient* nextPatient = frontPtr->getItem();
        return nextPatient->getAppoinment_Time() - currentTimestep;
    }
};