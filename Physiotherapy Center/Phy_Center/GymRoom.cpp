#include "GymRoom.h"
#include <sstream>
using namespace std;

GymRoom::GymRoom(const int& id, int capacity)
    : Resource(id, capacity) {
}

string GymRoom::getStatus() const {
    ostringstream oss;
    oss << "Room " << getId() << " [" << getCurrentPatients()
        << "/" << getCapacity() << "] " << (isAvailable() ? "(Available)" : "(In Use)");
    return oss.str();
}
void GymRoom::addPatient(Patient* p) {
    if (currentPatients < capacity) {
        currentPatients++;
        cout << "Patient " << p->getPatientID()
            << " assigned to GymRoom " << resourceId << endl;
    }
    else {
        throw std::runtime_error("GymRoom at full capacity");
    }
}