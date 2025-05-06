#ifndef UI_H
#define UI_H

#include "Schedular.h"
#include <iostream>

class UI {
public:
    UI(Schedular* sched);
    void displayCurrentStatus(int currentTime) const;
    void PrintMessage(string message) ;
    void WaitForUserKey();
    bool getSelectedMode();
private:
    Schedular* schedular;
    void clearScreen() const;
    void printPatientList(const char* name, const LinkedQueue<Patient*>& list) const;
    void printPriorityQueue(const char* name, const priQueue<Patient*>& queue) const;
    void printResourceList(const char* name, const LinkedQueue<Resource*>& list) const;
    void printRoomList(const char* name, const LinkedQueue<Resource*>& list) const;
    
};

#endif