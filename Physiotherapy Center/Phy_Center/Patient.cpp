#include "Patient.h"

Patient::Patient() : patientID(-1), type(NP), status(IDLE), Appoinment_Time(-1), Arrival_Time(-1), isCancelled(false), isResc(false), FinsihTime(-1), TotalTreatmenttime(-1), TotalWaittime(-1), currentTreatment(nullptr)
{
}
Patient::Patient(int pid, char ptype, int pt, int vt)
    : patientID(pid),
    type(ptype == 'N' ? NP : RP),  // N-Patient or R-Patient
    status(IDLE),                   // Initial status is IDLE
    Appoinment_Time(pt),
    Arrival_Time(vt),
    isCancelled(false),             // Default not cancelled
    isResc(false),           // Default not rescheduled
    FinsihTime(0),                  // Will be calculated later
    TotalWaittime(0),               // Initialize to 0
    TotalTreatmenttime(0),
    currentTreatment(nullptr)
    // Initialize to 0
{
}
int Patient::getPatientID() const {
    return patientID;
}
void Patient::setPatientID(int id)
{
    patientID = id;
}

Type Patient::getType() const {
    return type;
}
void Patient::setType(Type& typee) {
    type = typee;
}

Status Patient::getStatus() const {
    return status;
}
void Patient::setStatus(Status& st) {
    status = st;
}

int Patient::getArrival_Time() const {
    return Arrival_Time;
}
void Patient::setArrival_Time(int Vt)
{
    Arrival_Time = Vt;
}

int Patient::getAppoinment_Time()
{
    return Appoinment_Time;
}
void Patient::setAppoinment_Time(int Pt)
{
    Appoinment_Time = Pt;
}

LinkedQueue<Treatment*>  Patient::getTreatment()const
{
    return  treatments;
}
void  Patient::setRequiredTreatments(LinkedQueue<Treatment*> rt)
{
    treatments = rt;
}

bool Patient::getIsclosed()const {
    return isCancelled;
}
void Patient::setIsclosed(bool c) {
    isCancelled = c;
}

bool Patient::getIsResc()const {
    return isResc;
}
void Patient::setIsResc(bool r) {
    isResc = r;
}

int Patient::getFinsihTime()const
{
    return FinsihTime;
}
void Patient::setFinishTime(int F)
{
    FinsihTime = F;
}

int Patient::getTotalWaitTime()const
{
    return TotalWaittime;
}
void Patient::setTotalWaitTime(int TW)
{
    TotalWaittime = TW;
}
void Patient::setWaitingStartTime(int time) {
    waitingStartTime = time;
}
void Patient::addWaitingTime(int wt) { TotalWaittime += wt; }
int Patient::getWaitingStartTime() { return waitingStartTime; }
Treatment* Patient:: getCurrentTreatment() {
    
    if (treatments.isEmpty()) {
        return nullptr;
    }
    Treatment* t = nullptr;
    treatments.peek(t); // Get without removing
    return t;
}
void Patient::addTreatment(Treatment* treatment) {
    if (treatment) {
        treatments.enqueue(treatment);
    }
    if (!currentTreatment) {
        treatments.peek(currentTreatment); // Set first treatment
    }
}
int Patient::getTotalTreatmentTime()const
{
    return TotalTreatmenttime;
}
void Patient::setTotalTreatmentTime(int TT)
{
    TotalTreatmenttime = TT;
}

bool Patient::isFinished() const {
    return treatments.isEmpty();
}

int Patient::getRemainingTreatments() const {
    return treatments.size();
}
void Patient::setCurrentTreatment(Treatment* t) {
    currentTreatment = t;
}
bool Patient::moveToNextTreatment() {
    if (treatments.isEmpty()) {
        currentTreatment = nullptr;
        return false;
    }

    // Remove completed treatment
    Treatment* completed;
    treatments.dequeue(completed);
    delete completed;

    // Get next treatment if available
    if (!treatments.isEmpty()) {
        treatments.peek(currentTreatment);
        return true;
    }

    currentTreatment = nullptr;
    return false;
}
Patient::~Patient() {
}