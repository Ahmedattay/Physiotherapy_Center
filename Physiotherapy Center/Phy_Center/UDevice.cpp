#include "UDevice.h"
using namespace std;

UDevice::UDevice(const int& id)
    : Resource(id, 1) {
}
void UDevice::addPatient(Patient* p) {
        if (currentPatients < capacity) {
            currentPatients++;
            cout << "Patient " << p->getPatientID()
                << " assigned to U-device " << resourceId << endl;
        }
        else {
            throw std::runtime_error("UDevice at full capacity");
        }
}