#ifndef UDEVICE_H
#define UDEVICE_H

#include "Resource.h"
using namespace std;

class UDevice : public Resource {
public:
    UDevice(const int& id);
     void addPatient(Patient* p) override;
    char getResourceType() const override { return 'U'; }
};

#endif // UDEVICE_H