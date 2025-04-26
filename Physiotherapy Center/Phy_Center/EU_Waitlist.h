#pragma once
#include "LinkedQueue.h"
#include "Patient.h"
class EU_WaitList : public LinkedQueue<Patient*>
{
private:
    int currentTimestep;
public:
    void insertSorted(Patient* patient)
    {
        Node<Patient*>* newNode = new Node<Patient*>(patient);
        if (isEmpty() || patient->getAppoinment_Time() < frontPtr->getItem()->getAppoinment_Time()) {
            newNode->setNext(frontPtr);
            frontPtr = newNode;
            if (backPtr == nullptr) backPtr = frontPtr;
            return;
        }
        Node<Patient*>* current = frontPtr;
        while (current->getNext() != nullptr &&
            current->getNext()->getItem()->getAppoinment_Time() <= patient->getAppoinment_Time()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        if (newNode->getNext() == nullptr) backPtr = newNode;
    }
    int calcTreatmentLatency() {
        if (isEmpty()) return 0;

        Patient* nextPatient = frontPtr->getItem();
        return nextPatient->getAppoinment_Time() - currentTimestep;
    }
};