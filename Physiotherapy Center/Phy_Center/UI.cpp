#include "UI.h"
#include <cstring> // for strstr

UI::UI(Schedular* sched) : schedular(sched) {}
bool UI::getSelectedMode()
{
    cout << "Select Mode: ['i' for interactive mode , Press any other key for silent mode]" << endl;
    char c;
    cin >> c;
    cin.get();
    return c == 'i';
}
void UI::WaitForUserKey() 
{
    cin.get();
}
void UI::clearScreen() const {
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}
void UI::PrintMessage(string message) 
{
    cout << message << endl;
}
void UI::displayCurrentStatus(int currentTime) const {
    clearScreen();

    // Header with current timestep
    std::cout << "Current Timestep: " << currentTime << "\n\n";

    // --- ALL List ---
    std::cout << "---\nALL List ---\n";
    std::cout << schedular->getAllPatients().size() << " patients remaining: ";
    LinkedQueue<Patient*> tempAll = schedular->getAllPatients();
    for (int i = 0; i < 10 && !tempAll.isEmpty(); i++) {
        Patient* p = nullptr;
        tempAll.dequeue(p);
        if (p) {
            std::cout << "P" << p->getPatientID() << "_" << p->getArrival_Time();
            if (i < 9 && !tempAll.isEmpty()) std::cout << ", ";
        }
    }
    if (schedular->getAllPatients().size() > 10) std::cout << ", ...";
    std::cout << "\n";

    // --- Waiting Lists ---
    std::cout << "\n--- Waiting Lists ---\n";
    printPatientList("E-therapy", schedular->getEWaiting());
    printPatientList("U-therapy", schedular->getUWaiting());
    printPatientList("X-therapy", schedular->getXWaiting());

    // --- Early/Late Lists ---
    printPriorityQueue("Early List", schedular->getEarlyPatients());
    printPriorityQueue("Late List", schedular->getLatePatients());

    // --- Resources ---
    printResourceList("Avail E-devices", schedular->getEDevices());
    printResourceList("Avail U-devices", schedular->getUDevices());
    printRoomList("Avail X-rooms", schedular->getXRooms());

    // --- In-Treatment ---
    std::cout << "--- In-treatment List ---\n";
    std::cout << schedular->getInTreatment().size() << " =>\n";
    priQueue<Patient*> tempInTreat = schedular->getInTreatment();
    Patient* p;
    int finishTime;
    while (tempInTreat.dequeue(p, finishTime)) {
        if (p && p->getCurrentTreatment()) {
            Resource* r = p->getCurrentTreatment()->GetResource();
            std::cout << "P" << p->getPatientID() << " in ";
            if (r) std::cout << "R" << r->getId() << "[" << r->getCurrentPatients()
                << "/" << r->getCapacity() << "]";
            else std::cout << "No Resource";
            std::cout << " finishes at " << finishTime << "\n";
        }
    }

    // --- Finished List ---
    std::cout << "--- Finished List ---\n";
    std::cout << schedular->getFinishedPatients().size() << " finished patients: ";
    ArrayStack<Patient*> tempFinished = schedular->getFinishedPatients();
    while (!tempFinished.isEmpty()) {
        Patient* p = nullptr;
        tempFinished.pop(p);
        if (p) std::cout << p->getPatientID();
        if (!tempFinished.isEmpty()) std::cout << ", ";
    }
    std::cout << " (Recently finished are patients printed first)\n";

    std::cout << "\nPress any key to display next timestep\n";
    std::cin.get();
}
void UI::printPatientList(const char* name, const LinkedQueue<Patient*>& list) const {
    std::cout << list.size() << " " << name << " patients: ";
    LinkedQueue<Patient*> temp = list;
    Patient* p;
    while (temp.dequeue(p)) {
        if (p) {
            std::cout << "P" << p->getPatientID();
            if (!temp.isEmpty()) std::cout << ", ";
        }
    }
    std::cout << "\n";
}

void UI::printPriorityQueue(const char* name, const priQueue<Patient*>& queue) const {
    std::cout << "--- " << name << " ---\n";
    std::cout << queue.size() << " patients: ";
    priQueue<Patient*> temp = queue;
    Patient* p;
    int priority;
    while (temp.dequeue(p, priority)) {
        if (p) {
            std::cout << "P" << p->getPatientID();
            if (!temp.isEmpty()) std::cout << ", ";
        }
    }
    std::cout << "\n";
}

void UI::printResourceList(const char* name, const LinkedQueue<Resource*>& list) const {
    std::cout << "--- " << name << " ---\n";
    std::cout << list.size() << " ";
    if (strstr(name, "E-devices")) std::cout << "Electro device: ";
    else if (strstr(name, "U-devices")) std::cout << "Ultra device: ";

    LinkedQueue<Resource*> temp = list;
    Resource* r;
    while (!temp.isEmpty()) {
        temp.dequeue(r);
        std::cout << r->getId();
        if (!temp.isEmpty()) std::cout << ", ";
    }
    std::cout << "\n";
}

void UI::printRoomList(const char* name, const LinkedQueue<Resource*>& list) const {
    std::cout << "--- " << name << " ---\n";

    // SAFE counting without dequeueing
    int totalRooms = list.size();  // Use size() if available

    std::cout << totalRooms << " rooms: ";

    // SAFE iteration without modifying the queue
    LinkedQueue<Resource*> temp = list;
    Resource* r = nullptr;
    bool first = true;

    while (temp.dequeue(r)) {
        if (r) {  // Always check pointer validity
            if (!first) std::cout << " ";
            std::cout << "R" << r->getId()
                << "[" << r->getCurrentPatients()
                << "/" << r->getCapacity() << "]";
            first = false;
        }
    }
    std::cout << "\n";
}