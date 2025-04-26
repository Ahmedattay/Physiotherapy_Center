#pragma once
#include "priQueue.h"
#include "Patient.h"


class  EarlyPlist :public priQueue<Patient*>
{
public:

	bool reschedule(int pid, int newPT)
	{
		if (!head || newPT <= head->getItem(pid)->getAppoinment_Time())
			return false;
		priNode<Patient*>* current = head;
		priNode<Patient*>* prev = nullptr;
		while (current && current->getItem(pid)->getAppoinment_Time() != pid) {
			prev = current;
			current = current->getNext();
		}
		if (!current) return false;
		Patient* p = current->getItem(pid);
		if (prev) prev->setNext(current->getNext());
		else head = head->getNext();
		delete current;
		p->setAppoinment_Time(newPT);
		this->enqueue(p, newPT);
		return true;
	}
};