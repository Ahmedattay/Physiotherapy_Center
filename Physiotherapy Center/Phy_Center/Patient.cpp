#include "Patient.h"

Patient::Patient() : patientID(-1), type(NP), status(IDLE), Appoinment_Time(-1), Arrival_Time(-1), isCancelled(false), isResc(false), FinsihTime(-1), TotalTreatmenttime(-1), TotalWaittime(-1)
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
    TotalTreatmenttime(0)           // Initialize to 0
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
    return  Required_Treatments;
}
void  Patient::setRequiredTreatments(LinkedQueue<Treatment*> rt)
{
    Required_Treatments = rt;
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
    LinkedQueue<Treatment*> treatments;
    if (treatments.isEmpty()) {
        cerr << "Warning: No treatments for patient " << patientID << endl;
        return nullptr;
    }
    Treatment* t = nullptr;
    treatments.peek(t); // Get without removing
    return t;
}

int Patient::getTotalTreatmentTime()const
{
    return TotalTreatmenttime;
}
void Patient::setTotalTreatmentTime(int TT)
{
    TotalTreatmenttime = TT;
}
void Patient::addTreatment(Treatment* t) {
    Required_Treatments.enqueue(t);
}
bool Patient::isFinished() const {
    LinkedQueue<Treatment*> treatments;
    return treatments.isEmpty();
}

int Patient::getRemainingTreatments() const {
    LinkedQueue<Treatment*> treatments;
    return treatments.size();
}

bool Patient::moveToNextTreatment() 
{
        LinkedQueue<Treatment*> treatments;
        if (!treatments.isEmpty()) {
            Treatment* t;
            treatments.dequeue(t);
            delete t; // Clean up finished treatment
            return true;
        }
        return false;
    }
Patient::~Patient() {
}