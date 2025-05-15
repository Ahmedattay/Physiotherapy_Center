#pragma once
#include "Patient.h"
#include <string>
#include "LinkedQueue.h"
using namespace std;
class Resource
{
protected:
    int resourceId;
    LinkedQueue<Patient*> patientQueue;
    bool available;
    int capacity;
    int currentPatients;

public:
    Resource(const int& id, int cap);
    virtual ~Resource() = default;

    // Core functionality
    virtual bool assignPatient(Patient* patient);
    virtual Patient* releasePatient();
    virtual void addPatient(Patient* p) = 0;

    // setters 
    void setResourceId(const int& id);
    void setCapacity(int cap);
    void setAvailable(bool state);

    // Getters
    int getId() const;
    bool isAvailable() const;
    int getCurrentPatients() const;
    int getCapacity() const;

    // Device type identification
    virtual char getResourceType() const = 0;
    void removePatient();

    // Status information
    virtual string getStatus() const;
};