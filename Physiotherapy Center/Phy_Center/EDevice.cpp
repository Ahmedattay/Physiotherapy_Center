#include "EDevice.h"
using namespace std;
EDevice::EDevice(const int& id)
    : Resource(id, 1) {
}
void EDevice::addPatient(Patient* p) {
    if (currentPatients < capacity) {
        currentPatients++;
        cout << "Patient " << p->getPatientID()
            << " assigned to E-device " << resourceId << endl;
    }
    else {
        throw std::runtime_error("EDevice at full capacity");
    }
}