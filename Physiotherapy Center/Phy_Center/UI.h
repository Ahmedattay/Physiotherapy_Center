#ifndef UI_H
#define UI_H

#include "Schedular.h"
#include <iostream>

class UI {
public:
    UI(Schedular* sched);
    char displayCurrentStatus(int currentTime) const;
    void clearScreen() const;

private:
    Schedular* schedular;

    void printPatientList(const char* name, const LinkedQueue<Patient*>& list) const;
    void printPriorityQueue(const char* name, const priQueue<Patient*>& queue) const;
    void printResourceList(const char* name, const LinkedQueue<Resource*>& list) const;
    void printRoomList(const char* name, const LinkedQueue<Resource*>& list) const;
};

#endif