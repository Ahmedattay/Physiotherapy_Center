#include "Resource.h"
#include <sstream>
using namespace std;

Resource::Resource(const int& id, int cap)
    : resourceId(id), available(true), capacity(cap) {
}

bool Resource::assignPatient(Patient* patient) {
    if (!available || patientQueue.size() >= capacity) {
        return false;
    }
    if (patientQueue.enqueue(patient)) {
        available = (patientQueue.size() < capacity);
        currentPatients++;
        return true;
    }
    return false;
}

Patient* Resource::releasePatient() {
    Patient* releasedPatient = nullptr;
    if (patientQueue.dequeue(releasedPatient)) {
        available = (patientQueue.size() < capacity);
        return releasedPatient;
    }
    available = true;
    return nullptr;
}

// setters 
void Resource::setResourceId(const int& id) { resourceId = id; }
void Resource::setCapacity(int cap) {
    if (cap >= patientQueue.size()) {
        capacity = cap;
        available = (patientQueue.size() < capacity);
    }
}
void Resource::setAvailable(bool state) { available = state; }

// getters 
int Resource::getId() const { return resourceId; }
bool Resource::isAvailable() const { return available; }
int Resource::getCurrentPatients() const { return currentPatients; }
int Resource::getCapacity() const { return capacity; }

string Resource::getStatus() const {
    ostringstream oss;
    oss << resourceId << " [" << getCurrentPatients()
        << "/" << capacity << "] " << (available ? "(Available)" : "(In Use)");
    return oss.str();
}
void Resource::removePatient() {
    if (currentPatients > 0) {
        currentPatients--;
    }
}