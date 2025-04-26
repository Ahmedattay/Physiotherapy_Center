#pragma once
#include "EU_Waitlist.h"
#include "Patient.h"


class X_WaitList : public EU_WaitList
{
public:
	bool cancel(int pid) {
		if (isEmpty()) return false;
		Node<Patient*>* current = frontPtr;
		Node<Patient*>* prev = nullptr;
		while (current != nullptr) {
			Patient* p = current->getItem();
			if (p->getPatientID() == pid) {
				if (prev) prev->setNext(current->getNext());
				else frontPtr = current->getNext();
				if (current == backPtr) backPtr = prev;
				Status status = FNSH;
				p->setStatus(status);
				delete current;
				return true;
			}
			prev = current;
			current = current->getNext();
		}
		return false;
	}

};

