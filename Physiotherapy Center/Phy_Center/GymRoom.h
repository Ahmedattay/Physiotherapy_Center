#ifndef GYMROOM_H
#define GYMROOM_H

#include "Resource.h"
using namespace std;

class GymRoom : public Resource {
public:
    GymRoom(const int& id, int capacity);

    char getResourceType() const override { return 'X'; }
    virtual void addPatient(Patient* p);
    string getStatus() const override;
};

#endif // GYMROOM_H