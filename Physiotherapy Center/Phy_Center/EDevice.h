#ifndef EDEVICE_H
#define EDEVICE_H

#include "Resource.h"
using namespace std;

class EDevice : public Resource {
public:
    EDevice(const int& id);
    void addPatient(Patient* p) override;
    char getResourceType() const override { return 'E'; }
};

#endif // EDEVICE_H